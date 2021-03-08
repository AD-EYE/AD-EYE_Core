classdef LogfileTopicSelector < handle
%This class is for internal use only. It may be removed in the future.
%
%  Sample use:
%   selector = robotics.slros.internal.dlg.LogfileTopicSelector(bagSelection,topic);
%   selector.openDialog(@(isAccepted,topicName) disp(topicName))

%   Copyright 2017-2018 The MathWorks, Inc.

    properties (SetAccess = protected)
        %DataObject Object containing or allowing for access to all
        %   logfile data
        DataObject = robotics.ros.BagSelection.empty;

        %TopicIdx Index indicating which topic in table is selected
        %   Zero-based for DDG dialog tables
        TopicIdx double = 0

        %TopicList Contents to be displayed in the list of topics
        TopicList = cell(0, 4);

        %DetailsTxt Contents to be displayed for the details of a selected
        %   topic
        DetailsTxt = ''

        %CloseFcnHandle Handle to function to be called when the dialog is
        %   closed
        CloseFcnHandle = function_handle.empty
    end

    methods

        %% Constructor and dialog setup
        function obj = LogfileTopicSelector(dataobj, topic)
        %LogfileTopicSelector Construct a dialog for selecting a logfile topic
        %   DATAOBJ - object containing or allowing access to logfile data
        %   TOPIC - character vector, currently selected topic, if any

        % Save data for use
            obj.DataObject = dataobj;

            % Determine currently-selected topic
            if nargin > 1 && ~isempty(topic) && ...
                    ~isempty(obj.DataObject.AvailableTopics.Row)
                idx = find(strcmp(topic,obj.DataObject.AvailableTopics.Row), 1);
                if ~isempty(idx)
                    obj.TopicIdx = idx-1;
                end
            end
        end

        function dlg = openDialog(obj, closeFcnHandle)
        %openDialog Create, lay out, and make visible the dialog window
        %   closeFcnHandle - Handle to function to be executed when the
        %   dialog is closed. This function must take three arguments.
        %   For example, a valid function definition may look like:
        %       closeFcn(isAcceptedSelection, topic, msgType)
        %           isAcceptedSelection - True of user clicked on 'ok',
        %           false if user clicked on 'cancel' or closed window
        %           topic - Last selected topic (character vector)
        %           msgType - Message type of last selected topic (character vector)

        % Handle input
            validateattributes(closeFcnHandle, {'function_handle'}, {'scalar'});
            obj.CloseFcnHandle = closeFcnHandle;

            % Prepare data to display in widgets
            updateTopicList(obj);
            if size(obj.DataObject.AvailableTopics, 1) ~= 0
                updateDetailsTxt(obj, obj.DataObject.AvailableTopics.Row{obj.TopicIdx+1});
            end

            % Open dialog
            dlg = DAStudio.Dialog(obj);
        end
    end

    methods(Hidden)

        %% Control callbacks
        function listClickCallback(obj, dlg, row)
        %listClickCallback Called when the user newly selects a topic
            obj.TopicIdx = row; % value is zero-based
            updateDetailsTxt(obj,obj.DataObject.AvailableTopics.Row{obj.TopicIdx+1});
            dlg.refresh;
        end

        function [shouldClose, errorMsg] = dlgApplyClose(obj)
        %dlgApplyClose Callback for when the 'OK' button is pressed, but before the dialog closes

            if ~isempty(obj.CloseFcnHandle)
                try
                    shouldClose = true;
                    errorMsg = '';
                    if size(obj.DataObject.AvailableTopics, 1) == 0
                        return;
                    end
                    topic = obj.DataObject.AvailableTopics.Row{obj.TopicIdx+1};

                    feval(obj.CloseFcnHandle, topic);
                catch ME
                    % No errors should occur, but need this to avoid
                    % crashing Simulink by passing on uncaught exceptions
                    shouldClose = false;
                    errorMsg = ME.message;
                end
            end
        end

        %% Refresh data for individual controls
        function updateTopicList(obj)
        %updateTopicList Determine the values for the list to topics to select from

        % No data in logfile
            if isempty(obj.DataObject)
                obj.TopicList = cell(0, 4);
                return
            end

            % Preallocate
            % Topic, Start Offset, Duration, Number of Messages
            nTopics = size(obj.DataObject.AvailableTopics, 1);
            obj.TopicList = cell(nTopics, 4);

            % Fill in the data
            for k = 1:nTopics
                topic = obj.DataObject.AvailableTopics.Row{k};
                S = select(obj.DataObject, 'Topic', topic);
                obj.TopicList{k, 1} = topic;
                obj.TopicList{k, 2} = ...
                    num2str(S.StartTime-obj.DataObject.StartTime, '%.2f');
                obj.TopicList{k, 3} = ...
                    num2str(S.EndTime-S.StartTime, '%.2f');
                obj.TopicList{k, 4} = num2str(S.NumMessages, '%d');
            end
        end

        function updateDetailsTxt(obj, topic)
        %updateDetailsTxt Determine the value for the text to go in the topic details pane

        % Prepare data for examination
            S = select(obj.DataObject, 'Topic', topic);
            sampleMsg = readMessages(S, 1, 'DataFormat', 'struct');
            lineFormattedStr = '<b>%s</b> %s<br />';
            obj.DetailsTxt = '';
            defaultStr = getString(message('robotics:robotslros:readlog:NotApplicableShorthand'));

            % Message type
            msgType = char(S.AvailableTopics{1, 'MessageType'});
            obj.DetailsTxt = [obj.DetailsTxt ...
                              sprintf(lineFormattedStr, ...
                                      getString(message('robotics:robotslros:readlog:MessageTypePrompt')), ...
                                      msgType)];

            % Number of messages
            obj.DetailsTxt = [obj.DetailsTxt ...
                              sprintf(lineFormattedStr, ...
                                      getString(message('robotics:robotslros:readlog:NumMessagesPrompt')), ...
                                      num2str(S.NumMessages, '%d'))];

            % Start time, end time, start offset, duration
            obj.DetailsTxt = [obj.DetailsTxt ...
                              sprintf(lineFormattedStr, ...
                                      getString(message('robotics:robotslros:readlog:StartTimePrompt')), ...
                                      num2str(S.StartTime, '%.9f'))];
            obj.DetailsTxt = [obj.DetailsTxt ...
                              sprintf(lineFormattedStr, ...
                                      getString(message('robotics:robotslros:readlog:EndTimePrompt')), ...
                                      num2str(S.EndTime, '%.9f'))];
            obj.DetailsTxt = [obj.DetailsTxt ...
                              sprintf(lineFormattedStr, ...
                                      getString(message('robotics:robotslros:readlog:StartOffsetPrompt')), ...
                                      num2str(S.StartTime-obj.DataObject.StartTime, '%.9f'))];
            obj.DetailsTxt = [obj.DetailsTxt ...
                              sprintf(lineFormattedStr, ...
                                      getString(message('robotics:robotslros:readlog:DurationPrompt')), ...
                                      num2str(S.EndTime-S.StartTime, '%.9f'))];

            % Minimum and median gaps between messages
            minGapTxt = defaultStr;     % Default values if messages all have same timestamps
            medGapTxt = defaultStr;
            minGap = robotics.slros.internal.block.ReadDataBlockMask.getMinNonzeroMsgGap(S);
            if ~isempty(minGap)
                minGapTxt = num2str(minGap, '%.4f');
                medGapTxt = minGapTxt;  % Default value if many messages with no time gap
                medGap = median(diff(S.MessageList.Time));
                if medGap ~= 0
                    medGapTxt = num2str(medGap, '%.4f');
                end
            end
            obj.DetailsTxt = [obj.DetailsTxt ...
                              sprintf(lineFormattedStr, ...
                                      getString(message('robotics:robotslros:readlog:MinMsgGapPrompt')), ...
                                      minGapTxt)];
            obj.DetailsTxt = [obj.DetailsTxt ...
                              sprintf(lineFormattedStr, ...
                                      getString(message('robotics:robotslros:readlog:MedianMsgGapPrompt')), ...
                                      medGapTxt)];

            % Source frame
            frameTxt = defaultStr;      % Default value if no frame listed
            if isfield(sampleMsg{1}, 'Header') && ...
                    isfield(sampleMsg{1}.Header, 'FrameId') && ...
                    ischar(sampleMsg{1}.Header.FrameId) && ...
                    ~isempty(sampleMsg{1}.Header.FrameId)
                frameTxt = sampleMsg{1}.Header.FrameId;
            end
            obj.DetailsTxt = [obj.DetailsTxt ...
                              sprintf(lineFormattedStr, ...
                                      getString(message('robotics:robotslros:readlog:SourceFramePrompt')), ...
                                      frameTxt)];
        end

        %% Dialog layout
        function dlgstruct = getDialogSchema(obj)
        %getDialogSchema Determine the dialog window layout

            msglist.Type = 'table';
            msglist.Grid = false;
            msglist.Tag = 'msglist';
            msglist.ColHeader = ...
                {getString(message('robotics:robotslros:readlog:SourceTitle')), ...
                 getString(message('robotics:robotslros:readlog:StartOffsetTitle')), ...
                 getString(message('robotics:robotslros:readlog:DurationTitle')), ...
                 getString(message('robotics:robotslros:readlog:NumMessagesTitle'))};
            msglist.HeaderVisibility = [0 1];   % View column headers, not row numbers
            msglist.Data = obj.TopicList;
            msglist.Size = size(msglist.Data);
            msglist.ColumnCharacterWidth = [16 10 10 10];
            msglist.ColumnStretchable = [0 1 1 1];
            msglist.SelectedRow = obj.TopicIdx;
            msglist.CurrentItemChangedCallback = ...
                @(hDlg, row, ~) listClickCallback(obj, hDlg, row);

            paramPrompt.Type = 'text';
            paramPrompt.Name = ...
                getString(message('robotics:robotslros:readlog:DetailsTitle'));

            paramList.Name = 'Parameters for source';
            paramList.NameLocation = 2; % top left
            paramList.FontFamily = 'Consolas';
            paramList.Type = 'textbrowser';
            paramList.Text = obj.DetailsTxt;
            paramList.MinimumSize = [400 100];

            groupBox.Type = 'group';
            groupBox.Items = {msglist,paramPrompt,paramList};
            groupBox.RowSpan = [1 1];
            groupBox.ColSpan = [1 1];
            groupBox.LayoutGrid = [1 1];

            % Main dialog
            dlgstruct.DialogTitle = ...
                getString(message('robotics:robotslros:readlog:SelectSourceTitle'));
            dlgstruct.HelpMethod = 'robotics.slros.internal.helpview';
            dlgstruct.HelpArgs =  {'rosLogfileTopicSelectorDlg'};       % doc topic id
            dlgstruct.PreApplyMethod = 'dlgApplyClose';

            % Make this dialog modal wrt to other DDG dialogs
            % (doesn't block MATLAB command line)
            dlgstruct.Sticky = true;

            % Buttons to show on dialog (these are options to pass to DDG,
            % not the final strings, so there is no need to use message
            % catalog)
            dlgstruct.StandaloneButtonSet =  ...
                {'Ok', 'Cancel', 'Help'}; % also available: 'Revert', 'Apply'

            dlgstruct.Items = {groupBox};
        end
    end

    methods (Access = ?matlab.unittest.TestCase)

        function setCloseFcnHandle(obj, closeFcnHandle)
        %setCloseFcnHandle Set the handle to call when closing the dialog
        %   Used only for testing purposes
            obj.CloseFcnHandle = closeFcnHandle;
        end

    end
end
