function varargout = PlotLaneDeparture(varargin)
% PLOTLANEDEPARTURE M-file for PlotLaneDeparture.fig
%      PLOTLANEDEPARTURE, by itself, creates a new PLOTLANEDEPARTURE or raises the existing
%      singleton*.
%
%      H = PLOTLANEDEPARTURE returns the handle to a new PLOTLANEDEPARTURE or the handle to
%      the existing singleton*.
%
%      PLOTLANEDEPARTURE('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in PLOTLANEDEPARTURE.M with the given input arguments.
%
%      PLOTLANEDEPARTURE('Property','Value',...) creates a new PLOTLANEDEPARTURE or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before PlotLaneDeparture_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to PlotLaneDeparture_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help PlotLaneDeparture

% Last Modified by GUIDE v2.5 04-Feb-2011 10:56:23

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @PlotLaneDeparture_OpeningFcn, ...
                   'gui_OutputFcn',  @PlotLaneDeparture_OutputFcn, ...
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


% --- Executes just before PlotLaneDeparture is made visible.
function PlotLaneDeparture_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to PlotLaneDeparture (see VARARGIN)

% Choose default command line output for PlotLaneDeparture
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes PlotLaneDeparture wait for user response (see UIRESUME)
% uiwait(handles.lane_departure_dialog);


% --- Outputs from this function are returned to the command line.
function varargout = PlotLaneDeparture_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;
