function varargout = AEBS_radar_graph(varargin)
% RADAR_GRAPH M-file for radar_graph.fig
%      RADAR_GRAPH, by itself, creates a new RADAR_GRAPH or raises the existing
%      singleton*.
%
%      H = RADAR_GRAPH returns the handle to a new RADAR_GRAPH or the handle to
%      the existing singleton*.
%
%      RADAR_GRAPH('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in RADAR_GRAPH.M with the given input arguments.
%
%      RADAR_GRAPH('Property','Value',...) creates a new RADAR_GRAPH or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before radar_graph_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to radar_graph_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help radar_graph

% Last Modified by GUIDE v2.5 23-Nov-2012 14:41:54

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @AEBS_radar_graph_OpeningFcn, ...
                   'gui_OutputFcn',  @AEBS_radar_graph_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before radar_graph is made visible.
function AEBS_radar_graph_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to radar_graph (see VARARGIN)

% Choose default command line output for radar_graph
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes radar_graph wait for user response (see UIRESUME)
% uiwait(handles.GUI_radar);


% --- Outputs from this function are returned to the command line.
function varargout = AEBS_radar_graph_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;
