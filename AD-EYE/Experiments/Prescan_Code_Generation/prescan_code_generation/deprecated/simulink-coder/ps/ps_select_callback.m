function ps_select_callback(hSrc, hDlg) 
%PS_SELECT_CALLBACK  Set code generation option at ps target selection

    % set Code Generation Only; we will generate PackNGo zip for
    % compilation elsewhere
    hCS = hSrc.getConfigSet();
    hCS.setProp('GenCodeOnly','on');
    hCS.setPropEnabled('GenCodeOnly','off');

    % Set automatic packNGo off, we'll do custom packing in the make_rtw_hook
    % (PackageGeneratedCodeAndArtifacts property only exists in newer versions)
    if(~verLessThan('matlab','8.0'))
        hCS.setProp('PackageGeneratedCodeAndArtifacts','off');
        hCS.setPropEnabled('PackageGeneratedCodeAndArtifacts','off');
    end
    
    % Enable C API Parameter access
    slConfigUISetVal(hDlg, hSrc, 'RTWCAPIParams','on');

    % We need to force "classic" call interface for GRT since our target 
    % makefile is based on R2010bSP2
    slConfigUISetVal(hDlg, hSrc, 'GRTInterface','on');
    slConfigUISetEnabled(hDlg, hSrc, 'GRTInterface', false);

    % Use ANSI C89/90 target function library
    slConfigUISetVal(hDlg, hSrc, 'TargetFunctionLibrary','ANSI_C');
    

end