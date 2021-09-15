adeye_base = "C:\Users\adeye\AD-EYE_Core\AD-EYE\";
cd(adeye_base+"OpenSCENARIO\OpenSCENARIO_experiments");

% Go in the folder where scenarios are stored and get the number of
% scenarios into
SCENARIOS = dir(fullfile(adeye_base+"OpenSCENARIO\OpenSCENARIO_experiments", '*.xosc'));
NUM = size(SCENARIOS,1);

cd(adeye_base + "OpenSCENARIO\Code");
% Adapt current codes for the tests;

cd(adeye_base + "OpenSCENARIO");
fclose('all');
delete scenario_review.txt;

for i=1:NUM % Loop for each scenario
    
    % get the name of the next scenario to test
    experimentFile = SCENARIOS(i);
    experimentFile = experimentFile.name;
    experimentName = experimentFile(1:end-5);
    experimentNameChar = convertStringsToChars(experimentName);
    
    % Read the code
    cd(adeye_base + "OpenSCENARIO");
    file = fopen('TA_OpenSCENARIO_interface_tests.m');
    line = fgetl(file);
    k = 1;
    while k<204
       out3{k,1}=line;
       line=fgetl(file);
       k=k+1;
    end
    fclose(file);
    
    % Change the name of the next scenario
    FINDSTART = strfind(out3{23,1}, '[');
    FINDEND = strfind(out3{23,1}, ']');
    out3{23,1} = replaceBetween(out3{23,1}, FINDSTART +2, FINDEND-2, experimentNameChar);
    
    FINDSTART = strfind(out3{24,1}, '[');
    FINDEND = strfind(out3{24,1}, ']');
    out3{24,1} = replaceBetween(out3{24,1}, FINDSTART +2, FINDEND-2, experimentNameChar);
    
    % Do only one simulation
    out3{142,1} = "TA('Configurations/TAOrder.xlsx', 1, 1, 0,true)";
    
    % Write the new code in the old one
    file= fopen('TA_OpenSCENARIO_interface_tests.m','w');
    for k=1:numel(out3)
       fprintf(file,'%s\n',out3{k});
    end
    fclose(file);
    
    % Add the name of this scenario to the text file
    fid = fopen('scenario_review.txt', 'a');
    fprintf(fid, strcat('\nScenario: ', experimentName, '\n'));
    fclose(fid);
    
    try
        % Launch the simulation
        TA_OpenSCENARIO_interface_tests;
    catch
        % Add the error of this scenario to the text file
        cd(adeye_base + "OpenSCENARIO");
        fid = fopen('scenario_review.txt', 'a');
        fprintf(fid, 'Error launching TA_OpenSCENARIO_interface_tests');
        fclose(fid);
    end
    
    
end% Loop for each scenario
