function varargout = PPS_radar_graph(varargin)
% VRU_radar_graph M-file for VRU_radar_graph.fig
%      VRU_radar_graph, by itself, creates a new VRU_radar_graph or raises the existing
%      singleton*.
%
%      H = VRU_radar_graph returns the handle to a new VRU_radar_graph or the handle to
%      the existing singleton*.
%
%      VRU_radar_graph('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in VRU_radar_graph.M with the given input arguments.
%
%      VRU_radar_graph('Property','Value',...) creates a new VRU_radar_graph or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before VRU_radar_graph_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to VRU_radar_graph_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help VRU_radar_graph

% Last Modified by GUIDE v2.5 30-Jul-2012 14:53:49

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @PPS_radar_graph_OpeningFcn, ...
                   'gui_OutputFcn',  @PPS_radar_graph_OutputFcn, ...
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


% --- Executes just before VRU_radar_graph is made visible.
function PPS_radar_graph_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to VRU_radar_graph (see VARARGIN)

% Choose default command line output for VRU_radar_graph
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes VRU_radar_graph wait for user response (see UIRESUME)
% uiwait(handles.VRU_GUI_radar);


% --- Outputs from this function are returned to the command line.
function varargout = PPS_radar_graph_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;
