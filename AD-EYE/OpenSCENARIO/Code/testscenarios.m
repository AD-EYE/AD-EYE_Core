adeye_base = "C:\Users\adeye\AD-EYE_Core\AD-EYE\";
cd(adeye_base+"OpenSCENARIO\OpenSCENARIO_experiments");

%Go in the folder where scenarios are stored and get the number of
%scenarios into
SCENARIOS = dir(fullfile(adeye_base+"OpenSCENARIO\OpenSCENARIO_experiments", '*.xosc'));
NUM = size(SCENARIOS,1);

%Adapt current codes for the tests
rewriteTA();
rewritetrajectorydynamics();
rewriteAPImain();

cd(adeye_base + "OpenSCENARIO");
fclose('all');
delete scenario_review.txt;

for i=1:NUM %Loop for each scenario
    
    %get the name of the next scenario to test
    experimentFile = SCENARIOS(i);
    experimentFile = experimentFile.name;
    experimentName = experimentFile(1:end-5);
    experimentNameChar = convertCharsToStrings(experimentName);
    
    % Read the code
    cd(adeye_base + "OpenSCENARIO");
    file = fopen('TA_OpenSCENARIO_interface2.m');
    line = fgetl(file);
    k = 1;
    while k<204
       out3{k,1}=line;
       line=fgetl(file);
       k=k+1;
    end
    fclose(file);
    
    %Change the name of the next scenario
    FINDSTART = strfind(out3{23,1}, '[');
    FINDEND = strfind(out3{23,1}, ']');
    out3{23,1} = replaceBetween(out3{23,1}, FINDSTART +2, FINDEND-2, experimentNameChar);
    
    FINDSTART = strfind(out3{24,1}, '[');
    FINDEND = strfind(out3{24,1}, ']');
    out3{24,1} = replaceBetween(out3{24,1}, FINDSTART +2, FINDEND-2, experimentNameChar);
    
    %Change API_main function
    out3{79,1} = "API_main2(name_ego,name_prescan_experiment,listOfNames2(i))";
    %Do only one simulation
    out3{142,1} = "TA2('Configurations/TAOrder.xlsx', 1, 1)";
    
    %Write the new code in the old one
    file= fopen('TA_OpenSCENARIO_interface2.m','w');
    for k=1:numel(out3)-1
       fprintf(file,'%s\n',out3{k});
    end
    fclose(file);
    
    %Add the name of this scenario to the text file
    fid = fopen('scenario_review.txt', 'a');
    fprintf(fid, strcat('\nScenario: ', experimentName, '\n'));
    fclose(fid);
    
    %Launch the simulation
    TA_OpenSCENARIO_interface2;
    
end%Loop for each scenario
