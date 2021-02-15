function msfun_decodeUDP(block)
%MSFUNTMPL_BASIC A Template for a Level-2 MATLAB S-Function
%   The MATLAB S-function is written as a MATLAB function with the
%   same name as the S-function. Replace 'msfuntmpl_basic' with the 
%   name of your S-function.
%
%   It should be noted that the MATLAB S-function is very similar
%   to Level-2 C-Mex S-functions. You should be able to get more
%   information for each of the block methods by referring to the
%   documentation for C-Mex S-functions.
%
%   Copyright 2003-2010 The MathWorks, Inc.

%%
%% The setup method is used to set up the basic attributes of the
%% S-function such as ports, parameters, etc. Do not add any other
%% calls to the main body of the function.
%%
setup(block);

%endfunction

%% Function: setup ===================================================
%% Abstract:
%%   Set up the basic characteristics of the S-function block such as:
%%   - Input ports
%%   - Output ports
%%   - Dialog parameters
%%   - Options
%%
%%   Required         : Yes
%%   C-Mex counterpart: mdlInitializeSizes
%%
function setup(block)

% Register number of ports
block.NumInputPorts  = 2;
block.NumOutputPorts = 1;

% Setup port properties to be inherited or dynamic
block.SetPreCompInpPortInfoToDynamic;
block.SetPreCompOutPortInfoToDynamic;

% Override input port properties
block.InputPort(1).Dimensions      = [24 1];
block.InputPort(1).DatatypeID  = 3;  % uint8
block.InputPort(1).Complexity  = 'Real';
block.InputPort(1).DirectFeedthrough = true;

block.InputPort(2).Dimensions      = 1;
block.InputPort(2).DatatypeID  = 5;  % double
block.InputPort(2).Complexity  = 'Real';
block.InputPort(2).DirectFeedthrough = true;

% Override output port properties
block.OutputPort(1).Dimensions       = [3 1];
block.OutputPort(1).DatatypeID  = 0; % double
block.OutputPort(1).Complexity  = 'Real';

% Register parameters
block.NumDialogPrms     = 0;

% Register sample times
%  [0 offset]            : Continuous sample time
%  [positive_num offset] : Discrete sample time
%
%  [-1, 0]               : Inherited sample time
%  [-2, 0]               : Variable sample time
block.SampleTimes = [-1, 0];

% Specify the block simStateCompliance. The allowed values are:
%    'UnknownSimState', < The default setting; warn and assume DefaultSimState
%    'DefaultSimState', < Same sim state as a built-in block
%    'HasNoSimState',   < No sim state
%    'CustomSimState',  < Has GetSimState and SetSimState methods
%    'DisallowSimState' < Error out when saving or restoring the model sim state
block.SimStateCompliance = 'DefaultSimState';

%% -----------------------------------------------------------------
%% The MATLAB S-function uses an internal registry for all
%% block methods. You should register all relevant methods
%% (optional and required) as illustrated below. You may choose
%% any suitable name for the methods and implement these methods
%% as local functions within the same file. See comments
%% provided for each function for more information.
%% -----------------------------------------------------------------

block.RegBlockMethod('Outputs', @Output); % Required
block.RegBlockMethod('Terminate', @Terminate); % Required
block.RegBlockMethod('InitializeConditions',    @InitConditions);  
block.RegBlockMethod('PostPropagationSetup',    @DoPostPropSetup);

function SetupDwork(block, index, name, dimensions)
  block.Dwork(index).Name = name;
  block.Dwork(index).Dimensions = dimensions;
  block.Dwork(index).DatatypeID = 0;
  block.Dwork(index).Complexity = 'Real';
  
%endfunction
  
function DoPostPropSetup(block)
   %% Setup Dwork
  block.NumDworks = 3;
  
  SetupDwork(block, 1, 'bdata_ldis', 1);
  SetupDwork(block, 2, 'bdata_rdis', 1);
  SetupDwork(block, 3, 'bdata_sysstate', 1);  
  

%end setup

function InitConditions(block)
  %%triggered variable
  block.Dwork(1).Data = 0;
  block.Dwork(2).Data = 0;
  block.Dwork(3).Data = 0;
  

%%
%% Update:
%%   Functionality    : Called to update discrete states
%%                      during simulation step
%%   Required         : No
%%   C-MEX counterpart: mdlUpdate
%%
function Output(block)

str2char = block.InputPort(1).Data;

if(block.InputPort(2).Data > 0.0)
     nullIndex = find(str2char == 0, 1, 'first');
     data =  str2char(1:nullIndex-1);   
     
     data = char(data');
     
     reply = regexp(data,',','split')
     
     if(size(reply,2) == 3)    
        block.Dwork(1).Data = str2double(reply(1,1));    
        block.Dwork(2).Data = str2double(reply(1,2));    
        block.Dwork(3).Data = str2double(reply(1,3));    
     end
    
end

block.OutputPort(1).Data = [ block.Dwork(1).Data;
                             block.Dwork(2).Data;
                             block.Dwork(3).Data ];      

%end
%%
%% Terminate:
%%   Functionality    : Called at the end of simulation for cleanup
%%   Required         : Yes
%%   C-MEX counterpart: mdlTerminate
%%
function Terminate(block)

%end Terminate
