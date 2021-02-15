function varargout = TSR_GUI(varargin)
%TSR_GUI M-file for TSR_GUI.fig
%      TSR_GUI, by itself, creates a new TSR_GUI or raises the existing
%      singleton*.
%
%      H = TSR_GUI returns the handle to a new TSR_GUI or the handle to
%      the existing singleton*.
%
%      TSR_GUI('Property','Value',...) creates a new TSR_GUI using the
%      given property value pairs. Unrecognized properties are passed via
%      varargin to TSR_GUI_OpeningFcn.  This calling syntax produces a
%      warning16 when there is an existing singleton*.
%
%      TSR_GUI('CALLBACK') and TSR_GUI('CALLBACK',hObject,...) call the
%      local function named CALLBACK in TSR_GUI.M with the given input
%      arguments.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help TSR_GUI

% Last Modified by GUIDE v2.5 25-Mar-2013 11:33:35

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @TSR_GUI_OpeningFcn, ...
                   'gui_OutputFcn',  @TSR_GUI_OutputFcn, ...
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


% --- Executes just before TSR_GUI is made visible.
function TSR_GUI_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   unrecognized PropertyName/PropertyValue pairs from the
%            command line (see VARARGIN)

% Choose default command line output for TSR_GUI
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes TSR_GUI wait for user response (see UIRESUME)
% uiwait(handles.TSR_GUI_window);


% --- Outputs from this function are returned to the command line.
function varargout = TSR_GUI_OutputFcn(hObject, eventdata, handles)
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;
