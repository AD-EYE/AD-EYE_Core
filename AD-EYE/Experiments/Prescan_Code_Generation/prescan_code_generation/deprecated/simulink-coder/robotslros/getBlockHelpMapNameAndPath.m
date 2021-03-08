function [varargout] = getBlockHelpMapNameAndPath(block_type)
%getBlockHelpMapNameAndPath  Returns the mapName and the relative path to the maps file for this block_type

% Copyright 2017 The MathWorks, Inc.

varargout = cell(1, nargout);
[varargout{:}] = robotics.slcore.internal.block.getHelpMapNameAndPath(block_type, {
    'robotics.slros.internal.block.ReadImage'       'rosReadImBlock';
    'robotics.slros.internal.block.ReadPointCloud'  'rosReadPCBlock';
    });
