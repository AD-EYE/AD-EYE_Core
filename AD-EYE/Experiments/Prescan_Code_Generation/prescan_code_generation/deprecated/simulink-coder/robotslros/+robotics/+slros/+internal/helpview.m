function helpview(topicId)
%This function is for internal use only. It may be removed in the future.

%helpview - Invoke Doc Browser for specified topicId

%   Copyright 2014 The MathWorks, Inc.

validateattributes(topicId, {'char'}, {'nonempty'});
helpview(fullfile(docroot, 'robotics', 'helptargets.map'), topicId);
