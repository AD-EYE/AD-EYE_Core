function varargout = PPS_PlotSpeed(varargin)
%VRU_PlotSpeed M-file for VRU_PlotSpeed.fig
%      VRU_PlotSpeed, by itself, creates a new VRU_PlotSpeed or raises the existing
%      singleton*.
%
%      H = VRU_PlotSpeed returns the handle to a new VRU_PlotSpeed or the handle to
%      the existing singleton*.
%
%      VRU_PlotSpeed('Property','Value',...) creates a new VRU_PlotSpeed using the
%      given property value pairs. Unrecognized properties are passed via
%      varargin to VRU_PlotSpeed_OpeningFcn.  This calling syntax produces a
%      warning16 when there is an existing singleton*.
%
%      VRU_PlotSpeed('CALLBACK') and VRU_PlotSpeed('CALLBACK',hObject,...) call the
%      local function named CALLBACK in VRU_PlotSpeed.M with the given input
%      arguments.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help VRU_PlotSpeed

% Last Modified by GUIDE v2.5 23-Jul-2012 13:19:58

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @PPS_PlotSpeed_OpeningFcn, ...
                   'gui_OutputFcn',  @PPS_PlotSpeed_OutputFcn, ...
                   'gui_LayoutFcn',  [], ...
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


% --- Executes just before VRU_PlotSpeed is made visible.
function PPS_PlotSpeed_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   unrecognized PropertyName/PropertyValue pairs from the
%            command line (see VARARGIN)

% Choose default command line output for VRU_PlotSpeed
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes VRU_PlotSpeed wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = PPS_PlotSpeed_OutputFcn(hObject, eventdata, handles)
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;
