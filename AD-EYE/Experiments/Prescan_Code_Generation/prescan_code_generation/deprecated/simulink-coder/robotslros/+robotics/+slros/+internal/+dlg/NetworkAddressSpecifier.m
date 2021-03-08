classdef NetworkAddressSpecifier < handle
    %This class is for internal use only. It may be removed in the future.
    
    %  NetworkAddressSpecifier opens a DDG dialog that lets the user inspect
    %  and modify the network addresses for ROS Master and Node Host that
    %  are used in Simulation. Once the user accepts the changes, the
    %  information is saved in MATLAB Preferences.
    % 
    %  Sample use:
    %   addr = robotics.slros.internal.dlg.NetworkAddressSpecifier;
    %   addr.openDialog
    
    %   Copyright 2014-2018 The MathWorks, Inc.
        
    properties(SetAccess=private)
        NetAddrStore
        Profile = robotics.slros.internal.sim.NetworkAddrProfile.empty
    end    
    
    methods
       
         function obj = NetworkAddressSpecifier
             obj.NetAddrStore = robotics.slros.internal.sim.NetworkAddrStore;             
             obj.Profile = obj.NetAddrStore.getProfile();
             
             if isempty(obj.Profile.MasterHost)
                 obj.Profile.MasterHost = obj.Profile.getDefaultMasterHost();
             end
             
             if isempty(obj.Profile.NodeHost)
                 obj.Profile.NodeHost = obj.Profile.getDefaultNodeHost();
             end
         end
         
         function dlg = openDialog(obj)
            dlg = DAStudio.Dialog(obj);
         end
        
        function dlgClose(obj, closeaction)
            % closeaction is
            %   'ok' if user clicked OK
            %   'cancel' if user clicked cancel or closed window
            try
                isAcceptedSelection = strcmpi(closeaction, 'ok');
                if isAcceptedSelection
                    obj.NetAddrStore.setProfile(obj.Profile);
                    obj.NetAddrStore.updateStore();
                end
            catch ME
                disp(ME.getReport);
                % Absorb all errors. If they are propagated back to
                % DDG, this causes MATLAB to crash, (Can't convert to
                % warnings are not as they are not displayed either).
            end                
        end
        
        
        function hostSelectionChanged(obj, dlg, tag, value)
            % value: 0 (Default), 1 (Custom)
            if strcmpi(tag, 'masterhost')
                obj.Profile.MasterUseDefault = (value == 0);
            else % strcmpi(tag, 'nodehost')
                obj.Profile.NodeUseDefault = (value == 0);
            end
            dlg.refresh;
        end
                   
        function hostNameChanged(obj, dlg, tag, value)
            if strcmpi(tag, 'masterHostName')   
                oldStr = obj.Profile.MasterHost;
            else % strcmpi(tag, 'nodeHostName')
                oldStr = obj.Profile.NodeHost;
            end

            newStr = obj.convertStrToHostName(value);
            if isempty(newStr)
                dlg.setWidgetValue(tag, oldStr);
                return;
            end
            
            if strcmpi(tag, 'masterHostName')   
                obj.Profile.MasterHost = newStr;
            else % strcmpi(tag, 'nodeHostName')
                obj.Profile.NodeHost = newStr;
            end
            
            dlg.setWidgetValue(tag, newStr);
        end

        function portChanged(obj, dlg, tag, value)             
             [num, numIsValid] = obj.convertStrToPortNum(value);
             if numIsValid                 
                 obj.Profile.MasterPort = num;
             end
             valueStr = sprintf('%d', obj.Profile.MasterPort);
             dlg.setWidgetValue(tag, valueStr);
        end
        
        function testMasterConnection(obj, dlg, tag) %#ok<INUSD>
            dlgTitle = message('robotics:robotslros:netaddrdlg:TestMasterDlgTitle').getString;            
            successImage = fullfile(matlabroot, 'toolbox', 'robotics', 'robotsimulink', 'robotslros', 'resources', 'success_32.png');
            errorImage = fullfile(matlabroot, 'toolbox', 'robotics', 'robotsimulink', 'robotslros', 'resources', 'error_32.png');
            
            dp = DAStudio.DialogProvider;
            dp.DialogImage = errorImage; % by default, show error icon
            
            waitingDlg = [];
            try
                % ROSMaster constructor can take a while since it attempts
                % to resolve hostname  (and throws error if it cannot). So,
                % put up the waiting dialog before invoking ROSMaster
                % Note -- MSGBOX ignores dp.DialogImage
                
                waitingDlg = dp.msgbox(...
                    message('robotics:robotslros:netaddrdlg:TestMasterChecking').getString, ...
                    dlgTitle, true);
                rosMaster = robotics.slros.internal.sim.ROSMaster(obj.Profile);                
                isReachable = rosMaster.isReachable();
                delete(waitingDlg);
                if isReachable
                    dp.DialogImage = successImage;
                    dp.errordlg(...
                        message('robotics:robotslros:netaddrdlg:TestMasterSuccess', ...
                        rosMaster.MasterURI).getString, ...
                        dlgTitle, true);
                else                    
                    dp.errordlg(...
                        message('robotics:robotslros:netaddrdlg:TestMasterFailure', ...
                        rosMaster.MasterURI).getString, ...
                        dlgTitle, true);                    
                end                
            catch ME
                if isa(waitingDlg, 'DAStudio.Dialog') && ishandle(waitingDlg)
                   delete(waitingDlg); 
                end
                if strcmpi(ME.identifier, 'robotics:ros:util:HostInvalid') || ...
                    strcmpi(ME.identifier, 'robotics:ros:util:InvalidRosMasterURIEnv') || ...
                    strcmpi(ME.identifier, 'robotics:ros:util:URIInvalid')
                    % Error thrown by ROSMaster constructor. It is messy to
                    % provide a customized message as we don't want to
                    % retrieve the ROS_MASTER_uri environment variable
                    % (adds unnecessary coupling). So, just display the
                    % message but suppress the stack.
                     dp.errordlg(ME.message, dlgTitle, true);
                else
                    dp.errordlg(ME.getReport('basic'), dlgTitle, true);
                end
            end
        end
        
        
        function dlgstruct = getDialogSchema(obj)             
            %% "ROS Master" section
            
            row=1;                        
            
            masterHostLabel.Name = message('robotics:robotslros:netaddrdlg:NetworkAddress').getString;
            masterHostLabel.Type  = 'text';
            masterHostLabel.Alignment  = 7;
            masterHostLabel.RowSpan = [row row];
            masterHostLabel.ColSpan = [1 1];
            masterHostLabel.Visible = true;
            
            masterHostSelection.Name = '';
            masterHostSelection.NameLocation = 6;
            masterHostSelection.Type  = 'combobox';
            masterHostSelection.Alignment = 0;
            masterHostSelection.RowSpan = [row row];
            masterHostSelection.ColSpan = [2 2];
            masterHostSelection.Entries = {
                message('robotics:robotslros:netaddrdlg:NetAddrDefault').getString
                message('robotics:robotslros:netaddrdlg:NetAddrCustom').getString
                };
            if obj.Profile.MasterUseDefault
                masterHostSelection.Value = 0;
            else
                masterHostSelection.Value = 1;
            end
            masterHostSelection.ObjectMethod = 'hostSelectionChanged'; % call method on UDD source object
            masterHostSelection.MethodArgs = {'%dialog', '%tag', '%value'}; % '%handle ' is implicit as first arg
            masterHostSelection.ArgDataTypes = {'handle', 'string', 'mxArray'};            
            masterHostSelection.Tag = 'masterhost';

            masterTestBtn.Name = message('robotics:robotslros:netaddrdlg:TestConnection').getString;
            masterTestBtn.Type = 'pushbutton';
            masterTestBtn.RowSpan = [row row];
            masterTestBtn.ColSpan = [3 3];            
            masterTestBtn.Alignment = 6; % top-left
            masterTestBtn.Tag = 'masterTestBtn';
            masterTestBtn.ObjectMethod = 'testMasterConnection'; % call method on UDD source object
            masterTestBtn.MethodArgs = {'%dialog', '%tag'}; % '%handle ' is implicit as first arg
            masterTestBtn.ArgDataTypes = {'handle', 'string'};
            
            row = row+1; 

            masterHostNameLabel.Name = message('robotics:robotslros:netaddrdlg:HostOrIPAddr').getString;
            masterHostNameLabel.Type  = 'text';
            masterHostNameLabel.Alignment  = 7;
            masterHostNameLabel.RowSpan = [row row];
            masterHostNameLabel.ColSpan = [1 1];
            masterHostNameLabel.Visible = ~obj.Profile.MasterUseDefault;
            
            masterHostName.Name = '';
            masterHostName.Type  = 'edit';
            masterHostName.Value = obj.Profile.MasterHost;
            masterHostName.RowSpan = [row row];
            masterHostName.ColSpan = [2 2];
            masterHostName.Alignment = 0; % top-left
            masterHostName.Tag = 'masterHostName';
            masterHostName.ObjectMethod = 'hostNameChanged'; % call method on UDD source object
            masterHostName.MethodArgs = {'%dialog', '%tag', '%value'}; % '%handle ' is implicit as first arg
            masterHostName.ArgDataTypes = {'handle', 'string', 'mxArray'};                        
            masterHostName.Visible = ~obj.Profile.MasterUseDefault;
            
            row = row+1;
            
            masterPortNumLabel.Name = message('robotics:robotslros:netaddrdlg:Port').getString;
            masterPortNumLabel.Type  = 'text';
            masterPortNumLabel.Alignment  = 7;
            masterPortNumLabel.RowSpan = [row row];
            masterPortNumLabel.ColSpan = [1 1];
            masterPortNumLabel.Visible = ~obj.Profile.MasterUseDefault;
            
            masterPortNum.Name = '';
            masterPortNum.Type = 'edit';
            masterPortNum.Value = sprintf('%d', obj.Profile.MasterPort);
            masterPortNum.RowSpan = [row row];
            masterPortNum.ColSpan = [2 2];
            masterPortNum.Alignment = 0; % top-left
            masterPortNum.Tag = 'masterPortNum';            
            masterPortNum.ObjectMethod = 'portChanged'; % call method on UDD source object
            masterPortNum.MethodArgs = {'%dialog', '%tag', '%value'}; % '%handle ' is implicit as first arg
            masterPortNum.ArgDataTypes = {'handle', 'string', 'mxArray'};              
            masterPortNum.Visible = ~obj.Profile.MasterUseDefault;                     

            row = row + 1;            
            
            masterDefaultHelp.Name = message('robotics:robotslros:netaddrdlg:MasterDefaultHelp').getString;            
            masterDefaultHelp.Type = 'text';
            masterDefaultHelp.Italic = 0;
            masterDefaultHelp.WordWrap = true;
            masterDefaultHelp.RowSpan = [row row]; 
            masterDefaultHelp.ColSpan = [1 3];
            masterDefaultHelp.Visible = obj.Profile.MasterUseDefault;               
                        
            row = row+1;             %#ok<NASGU>
            % container
            masterContainer.Type = 'group'; % can be 'panel', in which case, case use .Flat = true
            masterContainer.Name = message('robotics:robotslros:netaddrdlg:ROSMaster').getString;
            masterContainer.Flat = false;
            masterContainer.LayoutGrid = [4 3]; % [numrows numcolumns]
            masterContainer.ColStretch = [2 2 1];
            masterContainer.Items = {masterDefaultHelp, masterHostLabel, masterHostSelection, masterHostNameLabel,...
                masterHostName, masterPortNumLabel, masterPortNum, masterTestBtn};
            masterContainer.Visible = true;
            
            %% "Node Host" section
            
            row=1;
            nodeHelp.Name = message('robotics:robotslros:netaddrdlg:NodeHelp').getString;
            nodeHelp.Type = 'text';
            nodeHelp.Italic = 0;
            nodeHelp.WordWrap = true;
            nodeHelp.RowSpan = [row row]; 
            nodeHelp.ColSpan = [1 3];            

            row = row+1;                       

            nodeHostLabel.Name = message('robotics:robotslros:netaddrdlg:NetworkAddress').getString;
            nodeHostLabel.Type  = 'text';
            nodeHostLabel.Alignment  = 7;
            nodeHostLabel.RowSpan = [row row];
            nodeHostLabel.ColSpan = [1 1];
            nodeHostLabel.Visible = true;             
            
            nodeHostSelection.Name = '';
            nodeHostSelection.Type = 'combobox';
            nodeHostSelection.Alignment = 0;
            nodeHostSelection.RowSpan = [row row]; 
            nodeHostSelection.ColSpan = [2 2];
            nodeHostSelection.Entries = {
                message('robotics:robotslros:netaddrdlg:NetAddrDefault').getString
                message('robotics:robotslros:netaddrdlg:NetAddrCustom').getString
                };
            if obj.Profile.NodeUseDefault
                nodeHostSelection.Value = 0;
            else
                nodeHostSelection.Value = 1;
            end            
            nodeHostSelection.ObjectMethod = 'hostSelectionChanged'; % call method on UDD source object
            nodeHostSelection.MethodArgs = {'%dialog', '%tag', '%value'}; % '%handle ' is implicit as first arg
            nodeHostSelection.ArgDataTypes = {'handle', 'string', 'mxArray'};             
            nodeHostSelection.Tag = 'nodehost';

            row=row+1;
            
            nodeHostNameLabel.Name = message('robotics:robotslros:netaddrdlg:HostOrIPAddr').getString;
            nodeHostNameLabel.Type  = 'text';
            nodeHostNameLabel.Alignment  = 7;
            nodeHostNameLabel.RowSpan = [row row]; 
            nodeHostNameLabel.ColSpan = [1 1];
            nodeHostNameLabel.Visible = ~obj.Profile.NodeUseDefault;
            
            nodeHostName.Name = '';
            nodeHostName.Type  = 'edit';
            nodeHostName.Value = obj.Profile.NodeHost;
            nodeHostName.RowSpan = [row row]; 
            nodeHostName.ColSpan = [2 2];
            nodeHostName.Alignment = 0; % top-left
            nodeHostName.ObjectMethod = 'hostNameChanged'; % call method on UDD source object
            nodeHostName.MethodArgs = {'%dialog', '%tag', '%value'}; % '%handle ' is implicit as first arg
            nodeHostName.ArgDataTypes = {'handle', 'string', 'mxArray'};             
            nodeHostName.Tag = 'nodeHostName';
            nodeHostName.Visible = ~obj.Profile.NodeUseDefault;
            
            row = row+1;            
            
            nodeDefaultHelp.Name = message('robotics:robotslros:netaddrdlg:NodeDefaultHelp').getString;
            nodeDefaultHelp.Type = 'text';
            nodeDefaultHelp.Italic = 0;
            nodeDefaultHelp.WordWrap = true;
            nodeDefaultHelp.RowSpan = [row row]; 
            nodeDefaultHelp.ColSpan = [1 3];            
            nodeDefaultHelp.Visible = obj.Profile.NodeUseDefault;         
         
            % container
            nodeContainer.Type = 'group'; % can be 'panel', in which case, case use .Flat = true
            nodeContainer.Name =  message('robotics:robotslros:netaddrdlg:NodeHost').getString;
            nodeContainer.Flat = false;
            nodeContainer.LayoutGrid = [4 3]; % [numrows numcolumns]
            nodeContainer.ColStretch = [2 2 1];
            nodeContainer.Items = {nodeHelp, nodeHostLabel, nodeHostSelection, ...
                nodeHostNameLabel, nodeHostName, nodeDefaultHelp};
            nodeContainer.Visible = true;

            
            %% Main Dialog
            
            helptext.Name = message('robotics:robotslros:netaddrdlg:HelpText').getString;
            helptext.Type  = 'text';
            helptext.WordWrap = false;
            helptext.RowSpan = [1 1];
            helptext.ColSpan = [1 2];
            helptext.Tag = 'helptext';
            helptext.Visible = true;
            
            topLevelContainer.Type = 'group'; % can be 'panel', in which case, case use .Flat = true
            topLevelContainer.Name = '';
            topLevelContainer.Items = {helptext, masterContainer, nodeContainer};
            topLevelContainer.Visible = true;
            
            %% Main dialog struct
            
            dlgstruct.DialogTitle = message('robotics:robotslros:netaddrdlg:DialogTitle').getString;
            dlgstruct.HelpMethod = 'robotics.slros.internal.helpview';
            dlgstruct.HelpArgs =  {'rosConfigNetAddrDlg'}; % doc topic id
            dlgstruct.CloseMethod = 'dlgClose';            
            dlgstruct.CloseMethodArgs = {'%closeaction'};
            dlgstruct.CloseMethodArgsDT = {'string'};            
            
            %Make the dialog non-modal like other dialogs
            %there will be only one dialog
            dlgstruct.Sticky = false; 
            
            % Buttons to show on dialog (these are options to pass to DDG,
            % not the final strings, so there is no need to use message
            % catalog)
            dlgstruct.StandaloneButtonSet =  ...
                {'Ok', 'Cancel', 'Help'}; % also available: 'Revert', 'Apply'            
            
            dlgstruct.Items = {topLevelContainer};
            dlgstruct.DialogTag = robotics.slros.internal.dlg.NetworkAddressSpecifier.getDialogTag();
        end
    end
    
    %%
    methods(Static)
        function launch()
            % Convenience function for opening the dialog
            addr  = robotics.slros.internal.dlg.findAndBringToFront('robotics.slros.internal.dlg.NetworkAddressSpecifier', ...
                robotics.slros.internal.dlg.NetworkAddressSpecifier.getDialogTag(),...
                @(x)~isempty(x));
            if isempty(addr)
                addr = robotics.slros.internal.dlg.NetworkAddressSpecifier;
                addr.openDialog();
            end
        end
        
        function tag = getDialogTag()
            tag = 'slros_networksaddress';
        end

        
        function str = convertStrToHostName(str)
            % Attempt to enforce some basic hostname constraints
            str = regexprep(str, '[^0-9a-z-\.]', ''); % remove non alphanumeric chars
            str = regexprep(str, '\.+', '\.');  % remove sequences of periods
            str = regexprep(str, '(^\.|\.$)', ''); % remove prefixed & suffixed periods
        end
        
        function [num, isValid] = convertStrToPortNum(str)
            % str2double returns NaN if unable to convert
            num = str2double(str); 
            isValid = ~isnan(num);
            if isValid
                num = abs(fix(num));
                num = min(num, 65535);
                num = max(num, 1);
            end
        end
    end
    
end

