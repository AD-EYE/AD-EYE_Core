%SIMULATION CONTINUE FUNCTION%
function Sim_Continue()

    h_dlg              = AP_PlotSpeed;

    h_start = findobj(h_dlg, 'Tag', 'start');
    h_pause = findobj(h_dlg, 'Tag', 'pause');
    h_stop =  findobj(h_dlg, 'Tag', 'stop');
    h_continue = findobj(h_dlg, 'Tag', 'pushbutton12');
    h_bay = findobj(h_dlg, 'Tag', 'text_bay');
    h_parallel = findobj(h_dlg, 'Tag', 'text_parallel');
    h_left = findobj(h_dlg, 'Tag', 'text_left');
    h_right = findobj(h_dlg, 'Tag', 'text_right');
    h_text_init_vel    = findobj(h_dlg, 'Tag', 'text_init_vel');
    h_text_des_vel     = findobj(h_dlg, 'Tag', 'text_des_vel');

    myArray = [h_start h_continue h_bay h_parallel h_left h_right h_text_init_vel h_text_des_vel];
    set(myArray, 'Enable', 'Off');

    myArray = [h_pause h_stop];
    set(myArray, 'Enable', 'On');
end