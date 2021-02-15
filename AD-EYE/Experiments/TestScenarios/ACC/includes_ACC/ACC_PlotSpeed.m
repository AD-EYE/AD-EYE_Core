function varargout = ACC_PlotSpeed(varargin)
%PLOTSPEED M-file for ACC_PlotSpeed.fig
%      ACC_PLOTSPEED, by itself, creates a new ACC_PLOTSPEED or raises the existing
%      singleton*.
%
%      H = ACC_PLOTSPEED returns the handle to a new ACC_PLOTSPEED or the handle to
%      the existing singleton*.
%
%      ACC_PLOTSPEED('Property','Value',...) creates a new ACC_PLOTSPEED using the
%      given property value pairs. Unrecognized properties are passed via
%      varargin to ACC_PlotSpeed_OpeningFcn.  This calling syntax produces a
%      acc_panel when there is an existing singleton*.
%
%      ACC_PLOTSPEED('CALLBACK') and ACC_PLOTSPEED('CALLBACK',hObject,...) call the
%      local function named CALLBACK in ACC_PLOTSPEED.M with the given input
%      arguments.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help ACC_PlotSpeed

% Last Modified by GUIDE v2.5 23-Jan-2012 19:24:16

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @ACC_PlotSpeed_OpeningFcn, ...
                   'gui_OutputFcn',  @ACC_PlotSpeed_OutputFcn, ...
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


% --- Executes just before ACC_PlotSpeed is made visible.
function ACC_PlotSpeed_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   unrecognized PropertyName/PropertyValue pairs from the
%            command line (see VARARGIN)

% Choose default command line output for ACC_PlotSpeed
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes ACC_PlotSpeed wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = ACC_PlotSpeed_OutputFcn(hObject, eventdata, handles)
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in acc_button.
function acc_button_Callback(hObject, eventdata, handles)
% hObject    handle to acc_button (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of acc_button
guidata(hObject, handles);
% end function
