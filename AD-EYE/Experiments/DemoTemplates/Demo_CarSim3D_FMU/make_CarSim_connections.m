function make_CarSim_connections(actorName)
    dynamicsName      = 'CarSim_Vehicle';
    
    if nargin < 1
        dynamicsUBI = find_system(bdroot,'LookUnderMasks','all','SearchDepth',3,'Name',dynamicsName);
        if iscell(dynamicsUBI) && ~isempty(dynamicsUBI)
            dynamicsUBI = dynamicsUBI{1};
        end
        if isempty(dynamicsUBI)
            error(['Did not find actor with CarSim dynamics (looking for block name ''' dynamicsName ''')']);
        end
        actorFullName = dynamicsUBI(1:end-length(dynamicsName)-1);
    else
        if ~startsWith(actorName,bdroot)
            actorFullName = [bdroot '/' actorName];
        else
            actorFullName = actorName;
        end        
        if ~endsWith(actorFullName,'/ENABLED')
            actorFullName =[actorFullName '/ENABLED'];
        end
        dynamicsUBI       = [actorFullName,'/',dynamicsName];
    end
    
    
    % Position CarSim imported blocks and make refs to its inports and outports
    carSimBlock = find_system(dynamicsUBI,'LookUnderMasks','all','SearchDepth',1,'BlockType','S-Function');
    carSimBlock_X = 370;
    carSimBlock_Y = 130;
    carSimBlock_W = 160;
    carSimBlock_H = 160;
    if ~isempty(carSimBlock)
        [~,base,ext] = fileparts(carSimBlock{1});
        carSimBlockName = [base ext];
        carSimBlock_UBI = [dynamicsUBI '/' carSimBlockName];
        carSimBlock_Pos = [carSimBlock_X, carSimBlock_Y, carSimBlock_X + carSimBlock_W, carSimBlock_Y + carSimBlock_H];
        set_param(carSimBlock_UBI,'Position',carSimBlock_Pos);
        carSimBlockInport  = [carSimBlockName '/1'];
        carSimBlockOutport = [carSimBlockName '/1'];
    else
        error('Did not find CarSim block');
    end
    
    CarSim2PreScanState_Name = 'CarSim2PreScanSTATE';
    CarSim2PreScanBus_Name = 'CarSim2PreScan_BUS';
    
    % Add mux to connect inputs to CarSim
    carSimMux_Name = 'CarSimMux';
    carSimMux_UBI = [dynamicsUBI '/' carSimMux_Name];
    if ~hasBlock(carSimMux_UBI)
        carSimMux_W = 5;
        carSimMux_H = 250;
        carSimMux_X = carSimBlock_X - carSimMux_W - 40;
        carSimMux_Y = carSimBlock_Y + carSimBlock_H / 2 - carSimMux_H /2;
        carSimMux_Pos = [carSimMux_X, carSimMux_Y, carSimMux_X + carSimMux_W, carSimMux_Y + carSimMux_H];
        add_block('simulink/Signal Routing/Mux',carSimMux_UBI,'Position',carSimMux_Pos,'Inputs','3');
    end
    
    UserParameters_In_Name = 'PathFollower_In';
    UserParameters_In_muxPort = 1;
    
    Contact_In_muxPort = 2;
    
    % Contact to Road information conversion block CarSim to PreScan
    Contact2Road_Name = 'TyreContact To Road Information';
    Contact2Road_UBI  = [dynamicsUBI, '/', Contact2Road_Name];
    Contact2Road_Pos = get_param(Contact2Road_UBI,'Position');
    
    % Friction values required in CarSim 2017 (Optional in 2016 and earlier)
    FrictionConstants_Name = 'Friction';
    FrictionConstants_UBI = [dynamicsUBI '/' FrictionConstants_Name];
    FrictionConstants_muxPort = 3;
    if ~hasBlock(FrictionConstants_UBI)
        FrictionValue = '0.85 * ones(8,1)';
        add_block('simulink/Sources/Constant',FrictionConstants_UBI,'Value',FrictionValue);
        fric_W = 80;
        fric_H = 15;
        muxPortHandles = get_param(carSimMux_UBI,'PortHandles');
        muxPortPos     = get_param(muxPortHandles.Inport(FrictionConstants_muxPort),'Position');
        % align vertically with mux port, and horizontally with Contact2Road block
        fricPos = [Contact2Road_Pos(3) - fric_W, muxPortPos(2) - fric_H/2, Contact2Road_Pos(3), muxPortPos(2) + fric_H/2];
        set_param(FrictionConstants_UBI,'Position',fricPos);
    end
    
    % Add lines last, so autorouting can go around the blocks
    % CarSim input connections
    add_line_safe(dynamicsUBI,[carSimMux_Name '/1'],carSimBlockInport);
    add_line_safe(dynamicsUBI,[UserParameters_In_Name '/1'],[carSimMux_Name '/' num2str(UserParameters_In_muxPort)]);
    add_line_safe(dynamicsUBI,[Contact2Road_Name '/1']     ,[carSimMux_Name '/' num2str(Contact_In_muxPort)]);
    add_line_safe(dynamicsUBI,[FrictionConstants_Name '/1'],[carSimMux_Name '/' num2str(FrictionConstants_muxPort)]);
    
    % CarSim output connections
    add_line_safe(dynamicsUBI,carSimBlockOutport,[CarSim2PreScanState_Name '/1']);
    add_line_safe(dynamicsUBI,carSimBlockOutport,[CarSim2PreScanBus_Name '/1']);
    
    % Connect outside line from PathFollower to CarSim_Vehicle block
    add_line_safe(actorFullName,'CarSim_UserMux/1',[dynamicsName '/1']);
    
end
        
function [tf] = hasBlock(blockFullName)
    try
        h = get_param(blockFullName,'Handle');
        tf = ~isempty(h);
    catch
        tf = false;
    end
end 

function [h] = add_line_safe(sys,fromPort,toPort)
    remove_terminator_line(sys,fromPort);
    remove_ground_line(sys,toPort);
    try
        h = add_line(sys,fromPort,toPort,'autorouting','on');
    catch
        h = [];
    end
end

function tf = remove_terminator_line(sys,fromPortOrLine)
tf = false;
try
    if ischar(fromPortOrLine)
        fromPort = fromPortOrLine;
        [outBlockName, outPortNr] = strtok(fromPort,'/');
        outPortNr = str2double(outPortNr(2:end));
        Port_Handles = get_param([sys '/' outBlockName],'PortHandles');
        hPort = Port_Handles.Outport(outPortNr);
        hLines = get_param(hPort,'Line');
    elseif ishandle(fromPortOrLine(1))
        hLines = fromPortOrLine;
    end
    if ~any(hLines ~= -1)
        return;
    end

    % first loop over children lines (to remove bottom-up)
    for ii = 1:length(hLines)
        hLine = hLines(ii);
        children = get_param(hLine,'LineChildren');
        if ~isempty(children)
            remove_terminator_line(sys,children);
        end
    end

    % now loop over current lines
    ii = 1;
    while ii <= length(hLines)
        hLine = hLines(ii);
        hDstBlocks = get_param(hLine,'DstBlockHandle');
        if length(hDstBlocks) == 1
            if hDstBlocks ~= -1
                bt = get_param(hDstBlocks,'BlockType');
                if strcmpi(bt,'terminator')
                    delete_block(hDstBlocks);
                    delete_line(hLine);
                    hLines(ii) = [];
                    ii = ii - 1;
                    tf = true;
                end
            else %line without destination
                delete_line(hLine);
                hLines(ii) = [];
                ii = ii - 1;
                tf = true;
            end
        end
        ii = ii + 1;
    end

catch
    return;
end
end

function tf = remove_ground_line(sys,toPort)
tf = false;
try
    [inBlockName, inPortNr] = strtok(toPort,'/');
    inPortNr = str2double(inPortNr(2:end));
    Port_Handles = get_param([sys '/' inBlockName],'PortHandles');
    hPort = Port_Handles.Inport(inPortNr);
    hLine = get_param(hPort,'Line');
    if ~any(hLine ~= -1)
        return;
    end
    
    hSrcBlock = get_param(hLine,'SrcBlockHandle');
    if length(hSrcBlock) == 1
        if hSrcBlock ~= -1
            bt = get_param(hSrcBlock,'BlockType');
            if strcmpi(bt,'ground')
                delete_block(hSrcBlock);
                delete_line(hLine);
                tf = true;
            end
        else
            delete_line(hLine);
            tf = true;
        end
    end
catch
    return;
end
end

function [tf] = startsWith(s1,s2)
    tf = strncmp(s1,s2,length(s2));
end

function [tf] = endsWith(s1,s2)
    n1 = length(s1);
    n2 = length(s2);
    if n1 >= n2
        tf = strcmp(s1(end-n2:end),s2);
    else 
        tf = false;
    end
end
