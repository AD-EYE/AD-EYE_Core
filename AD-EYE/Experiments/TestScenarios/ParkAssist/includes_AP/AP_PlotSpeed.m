function varargout = AP_PlotSpeed(varargin)
%PLOTSPEED M-file for AP_PlotSpeed.fig
%      AP_PLOTSPEED, by itself, creates a new AP_PLOTSPEED or raises the existing
%      singleton*.
%
%      H = AP_PLOTSPEED returns the handle to a new AP_PLOTSPEED or the handle to
%      the existing singleton*.
%
%      AP_PLOTSPEED('Property','Value',...) creates a new AP_PLOTSPEED using the
%      given property value pairs. Unrecognized properties are passed via
%      varargin to AP_PlotSpeed_OpeningFcn.  This calling syntax produces a
%      AP_panel when there is an existing singleton*.
%
%      AP_PLOTSPEED('CALLBACK') and AP_PLOTSPEED('CALLBACK',hObject,...) call the
%      local function named CALLBACK in AP_PLOTSPEED.M with the given input
%      arguments.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help AP_PlotSpeed

% Last Modified by GUIDE v2.5 14-Feb-2014 14:26:32

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @AP_PlotSpeed_OpeningFcn, ...
                   'gui_OutputFcn',  @AP_PlotSpeed_OutputFcn, ...
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


% --- Executes just before AP_PlotSpeed is made visible.
function AP_PlotSpeed_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   unrecognized PropertyName/PropertyValue pairs from the
%            command line (see VARARGIN)

% Choose default command line output for AP_PlotSpeed
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes AP_PlotSpeed wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = AP_PlotSpeed_OutputFcn(hObject, eventdata, handles)
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;

% --- Executes on button press in start.
function start_Callback(hObject, eventdata, handles)
% hObject    handle to start (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set_param(bdroot, 'SimulationCommand', 'start')

% --- Executes on button press in pause.
function pause_Callback(hObject, eventdata, handles)
% hObject    handle to pause (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set_param(bdroot, 'SimulationCommand', 'pause')

% --- Executes on button press in continue.
function pushbutton12_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton12 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% --- Executes on button press in stop.
set_param(bdroot, 'SimulationCommand', 'continue')

% --- Executes on button press in stop.
function stop_Callback(hObject, eventdata, handles)
% hObject    handle to stop (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set_param(bdroot, 'SimulationCommand', 'stop')

function text_init_vel_Callback(hObject, eventdata, handles)
% hObject    handle to text_init_vel (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of text_init_vel as text
%        str2double(get(hObject,'String')) returns contents of text_init_vel as a double

b = (str2num(get(hObject,'String'))/3.6);
if (b<0 | b>5)
    ed = errordlg('Vehicle Initial Velocity must be a number between 0 - 18 km/h','Error');
    set(ed, 'WindowStyle', 'modal');
    uiwait(ed);
elseif isempty(b)
    ed = errordlg('Vehicle Initial Velocity must be a number between 0 - 18 km/h','Error');
    set(ed, 'WindowStyle', 'modal');
    uiwait(ed);
end

% --- Executes during object creation, after setting all properties.
function text_init_vel_CreateFcn(hObject, eventdata, handles)
% hObject    handle to text_init_vel (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.

if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

b = (str2num(get(hObject,'String'))/3.6);
if (b<0 | b>5)
    ed = errordlg('Vehicle Initial Velocity must be a number between 0 - 18 km/h','Error');
    set(ed, 'WindowStyle', 'modal');
    uiwait(ed);
elseif isempty(b)
    ed = errordlg('Vehicle Initial Velocity must be a number between 0 - 18 km/h','Error');
    set(ed, 'WindowStyle', 'modal');
    uiwait(ed);
end

function text_des_vel_Callback(hObject, eventdata, handles)
% hObject    handle to text_des_vel (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of text_des_vel as text
%        str2double(get(hObject,'String')) returns contents of text_des_vel as a double
b = (str2num(get(hObject,'String'))/3.6);
if (b<1 | b>5)
    ed = errordlg('Vehicle Desired Velocity must be a number between 3.6 - 18 km/h','Error');
    set(ed, 'WindowStyle', 'modal');
    uiwait(ed);
elseif isempty(b)
    ed = errordlg('Vehicle Desired Velocity must be a number between 3.6 - 18 km/h','Error');
    set(ed, 'WindowStyle', 'modal');
    uiwait(ed);
end

% --- Executes during object creation, after setting all properties.
function text_des_vel_CreateFcn(hObject, eventdata, handles)
% hObject    handle to text_des_vel (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

b = (str2num(get(hObject,'String'))/3.6);
if (b<1 | b>5)
    ed = errordlg('Vehicle Desired Velocity must be a number between 3.6 - 18 km/h','Error');
    set(ed, 'WindowStyle', 'modal');
    uiwait(ed);
elseif isempty(b)
    ed = errordlg('Vehicle Desired Velocity must be a number between 3.6 - 18 km/h','Error');
    set(ed, 'WindowStyle', 'modal');
    uiwait(ed);
end

% --- Executes when selected object is changed in uipanel14.
function uipanel14_SelectionChangeFcn(hObject, eventdata, handles,VehName)
Path = find_system(bdroot,'Regexp','on','LookUnderMasks','all','Name','AP_DEMO');
switch get(eventdata.NewValue,'Tag') % Get Tag of selected object.% hObject    handle to the selected object in uipanel14 
    case 'text_bay'
%         set_param('Simple_Parallel_And_Bay_Parking_SHOW_cs/Ford_FocusWagon_1/AP_DEMO/MainSwitch','sw','1');
        set_param([Path{1} '/MainSwitch'],'sw','1');
        
    case 'text_parallel'
%         set_param('Simple_Parallel_And_Bay_Parking_SHOW_cs/Ford_FocusWagon_1/AP_DEMO/MainSwitch','sw','0');
        set_param([Path{1} '/MainSwitch'],'sw','0');
        
end
% eventdata  structure with the following fields (see UIBUTTONGROUP)
%	EventName: string 'SelectionChanged' (read only)
%	OldValue: handle of the previously selected object or empty if none was selected
%	NewValue: handle of the currently selected object
% handles    structure with handles and user data (see GUIDATA)

% --- Executes when selected object is changed in uipanel15.
function uipanel15_SelectionChangeFcn(hObject, eventdata, handles,VehName)
Path = find_system(bdroot,'Regexp','on','LookUnderMasks','all','Name','AP_DEMO');
switch get(eventdata.NewValue,'Tag') % Get Tag of selected object.% hObject    handle to the selected object in uipanel14 
    case 'text_left'
        set_param([Path{1} '/Braking_&_Graph_Subsystem/Braking_Control_Subsystem/LeftRight'],'Value','1');
       
    case 'text_right'
        set_param([Path{1} '/Braking_&_Graph_Subsystem/Braking_Control_Subsystem/LeftRight'],'Value','-1');
end
% hObject    handle to the selected object in uipanel15 
% eventdata  structure with the following fields (see UIBUTTONGROUP)
%	EventName: string 'SelectionChanged' (read only)
%	OldValue: handle of the previously selected object or empty if none was selected
%	NewValue: handle of the currently selected object
% handles    structure with handles and user data (see GUIDATA)
