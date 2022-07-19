function DatabaseConnection()

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Connect to the mysql database %
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    conn = actxserver('ADODB.Connection');
    conn.Open('driver={MySQL ODBC 5.3 Unicode Driver}; server=IP-address; port=3306; dns=mydb; uid=adeye; pwd=password');
    conn.Execute('use adeye');
    % Query to the database. 
    % In this query, we will be able to restric the data on a location and a time
    r = conn.Execute('select precipitation_amount_name from weather_information');
    rows = r.GetRows();
    
    %%%%%%%%%%%%%%%%%%%%%
    % Check the weather %
    %%%%%%%%%%%%%%%%%%%%%
    
    % Create a table to write on an xlsx file.
    T = ["FolderExpName" "W01_Base_World/Simulation"; ...
         "PrescanExpName" "W01_Base_World"; ...
         "EgoName" "BMW_X5_SUV_1"; ...
         "AutowareConfig" "AutowareConfigTemplate.xlsx"; ...
         "SimulinkConfig" "SimulinkConfigExample.xlsx"; ...
         "TagsConfig" ""; ...
         "SHHConfig" "Configurations/SSHConfig.csv"];
     
    %Check the weather conditions on the downloaded data from the database
    for i = 1:size(rows,2)
        if rows(i) == "Kraftigt regn" % If there is rain, add it on the simulation thank to TagsConfig
            T(6,2) = "weather_type=Rain/rain_density=452000/rain_size=1.23000";
        end
    end
    
    %%%%%%%%%%%%%%%%%%%%%%
    % Run the simulation %
    %%%%%%%%%%%%%%%%%%%%%%
    oldfolder = pwd;
    cd ..;
    cd TA/Configurations;
    writematrix(T,'TAOrderDatabase.xlsx')
    cd ..;
    TA("Configurations/TAOrderDatabase.xlsx",1,1,1)
    cd(oldfolder);
    
    clearvars conn;
end
