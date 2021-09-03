adeye_base = "C:\Users\adeye\AD-EYE_Core\AD-EYE\";
cd(adeye_base+"OpenSCENARIO\OpenSCENARIO_experiments");

%Go in the folder where scenarios are stored and get the number of
%scenarios into
SCENARIOS = dir(fullfile(adeye_base+"OpenSCENARIO\OpenSCENARIO_experiments", '*.xosc'));
NUM = size(SCENARIOS,1);

cd(adeye_base + "OpenSCENARIO");
delete scenario_review.txt;

for i=1:NUM%Loop for each scenario
    
    %get the name of the next scenario to test
    experimentFile = SCENARIOS(i);
    experimentFile = experimentFile.name;
    experimentName = experimentFile(1:end-5);
    experimentNameChar = convertCharsToStrings(experimentName);
    
    % Read the code
    file = fopen('TA_OpenSCENARIO_interface2.m');
    line = fgetl(file);
    k = 1;
    while k<204
       out{k,1}=line;
       line=fgetl(file);
       k=k+1;
    end
    fclose(file);
    
    %Change the name of the next scenario
    FINDSTART = strfind(out{23,1}, '[');
    FINDEND = strfind(out{23,1}, ']');
    out{23,1} = replaceBetween(out{23,1}, FINDSTART +2, FINDEND-2, experimentNameChar);
    
    FINDSTART = strfind(out{24,1}, '[');
    FINDEND = strfind(out{24,1}, ']');
    out{24,1} = replaceBetween(out{24,1}, FINDSTART +2, FINDEND-2, experimentNameChar);
    
    %Write the new code in the old one
    file= fopen('TA_OpenSCENARIO_interface2.m','w');
    for k=1:numel(out)-1
       fprintf(file,'%s\n',out{k});
    end
    fclose(file);
    
    fid = fopen('scenario_review.txt', 'a');
    fprintf(fid, strcat('Scenario: ', experimentName, '\n'));
    fclose(fid);
    
    TA_OpenSCENARIO_interface2;
    
end%Loop for each scenario
