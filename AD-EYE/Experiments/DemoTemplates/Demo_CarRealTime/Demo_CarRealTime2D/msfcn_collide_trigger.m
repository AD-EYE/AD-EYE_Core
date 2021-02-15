function msfcn_collide_trigger(block)
% Level-2 MATLAB file S-Function which calculates a trigger signal 
% such that actor A collides with actor B. A is moved by means of 
% an trajectory. The other is moved by means of trajectory or by 
% vehicle dynamics. For both actors constant speed is assumed. The speed
% level can be set per actor.
% 
% Example created by Jeroen van der Waal

  setup(block);
  
%endfunction


function setup(block)
  %% distance_actor_1, velocity_actor_2, distance_actor_2
  block.NumDialogPrms  = 3;
  
  %% Register number of input and output ports
  block.NumInputPorts  = 1; 
  block.NumOutputPorts = 1;

  %% Setup functional port properties to dynamically
  %% inherited.
  block.SetPreCompInpPortInfoToDynamic;
  block.SetPreCompOutPortInfoToDynamic;
 
  %% Velocity of actor 2, when at distance_actor_2
  block.InputPort(1).Dimensions = 1;
  
  %% Trigger output, to trigger actor 2
  block.OutputPort(1).Dimensions = 1;
  
  %% Set block sample time to inherited
  block.SampleTimes = [-1 0];
  
  %% Set the block simStateCompliance to default 
  %% (i.e., same as a built-in block)
  block.SimStateCompliance = 'DefaultSimState';

  %% Register methods
  block.RegBlockMethod('PostPropagationSetup',    @DoPostPropSetup);
  block.RegBlockMethod('InitializeConditions',    @InitConditions);  
  block.RegBlockMethod('Outputs',                 @Output);   

%endfunction

function SetupDwork(block, index, name, dimensions)
  block.Dwork(index).Name = name;
  block.Dwork(index).Dimensions = dimensions;
  block.Dwork(index).DatatypeID = 0;
  block.Dwork(index).Complexity = 'Real';
  
%endfunction
  
function DoPostPropSetup(block)
   %% Setup Dwork
  block.NumDworks = 2;
  
  SetupDwork(block, 1, 'triggered', 1);
  SetupDwork(block, 2, 'time_to_trigger', 1);
  
%endfunction

function InitConditions(block)
  %%triggered variable
  block.Dwork(1).Data = 0;
  
  %%time_to_trigger
  block.Dwork(2).Data = 0;
  
%endfunction

function Output(block)
  triggered = block.Dwork(1).Data;
  time_to_trigger = block.Dwork(2).Data;
    
  if (~triggered)
      velocity_actor_1 = block.InputPort(1).Data;
      if (velocity_actor_1 > 0)
          %% triggered
          block.Dwork(1).Data = 1;
          
          %% calculate time_to_trigger for collision
          distance_actor_1 = block.DialogPrm(1).Data;
          velocity_actor_2 = block.DialogPrm(2).Data;
          distance_actor_2 = block.DialogPrm(3).Data;
          
          time_actor_1 = distance_actor_1 / velocity_actor_1;
          time_actor_2 = distance_actor_2 / velocity_actor_2; 
          
          delta = time_actor_1 - time_actor_2;
          if( delta < 0)
              error('The velocity of actor 1 is to slow to collide with actor 2');
          end
          
          %% store time to trigger
          block.Dwork(2).Data = block.CurrentTime + delta;
      end    
  else %%if (~triggered) 
    output = double(block.CurrentTime >= time_to_trigger);
    c = block.CurrentTime;
    block.OutputPort(1).Data = output;
  end
%endfunction
