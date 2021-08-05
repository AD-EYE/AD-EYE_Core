function DatabaseConnection()

    %connect to the mysql database
    conn = actxserver('ADODB.Connection');
    conn.Open('driver={MySQL ODBC 5.3 Unicode Driver}; server=130.237.59.134; port=3306; dns=mydb; uid=adeye; pwd=AdeyeSQL05');
    conn.Execute('use adeye');
    r = conn.Execute('select precipitation_amount_name from weather_information');
    rows = r.GetRows();
    
    % Create a table to write on the xlsx file
    T = ["FolderExpName" "W01_Base_Map/Simulation"; ...
         "PrescanExpName" "W01_Base_Map"; ...
         "EgoName" "BMW_X5_SUV_1"; ...
         "AutowareConfig" "AutowareConfigTemplate.xlsx"; ...
         "SimulinkConfig" "SimulinkConfigExample.xlsx"; ...
         "TagsConfig" ""; ...
         "SHHConfig" "Configurations/SSHConfig.csv"];
     
    for i = 1:size(rows,2)
        if rows(i) == "Kraftigt regn"
            T(6,2) = "weather_type=Rain/rain_density=452000/rain_size=1.23000";
        end
    end
    T
    oldfolder = pwd;
    cd ..;
    cd TA/Configurations;
    writematrix(T,'TAOrderDatabase.xlsx')
    cd ..;
    TA("Configurations/TAOrderDatabase.xlsx",1,1,1)
    %conn.close();
    clearvars conn;
    cd(oldfolder);
end