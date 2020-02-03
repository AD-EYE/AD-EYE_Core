%% Initialisation
base = "\\192.168.122.1\Shared Drive\";
folderName = "localization_results";
folder = base + folderName;
initFolder = pwd;

cd(folder)

%% Configuration

config = table;
% The table config is organised with 2 colums :
%
% "configName"   :    "param"          "value"
%
% The 'configName' (rowName) is the value in the expDate.log
%     'param' tells what parameters it refers
%     'value' gives the value of the parameter for that 'configName'

config("AutowareConfig1.xlsx",:) = {"speed", 5};
config("AutowareConfig2.xlsx",:) = {"speed", 10};
config("AutowareConfig3.xlsx",:) = {"speed", 15};
config("KTH_car_osc1",:) = {"RainIntensity", 50};
config("KTH_car_osc2",:) = {"RainIntensity", 10};
config("KTH_car_osc3",:) = {"RainIntensity", 0};

config.Properties.VariableNames = ["param" "value"];

%% Opening Log

expLog = readtable("expDate.log", "FileType", "text");
expLog.Properties.VariableNames = ["Date" "config1" "config2"];

%% Analyzing bags

% Results table
% Run : param1 (speed) , param2 (trig dist) , collisionTime (-1 if not) ,
%                         position (collision or last) , collisionSpeed
results = table;

% Assuming there are in the right order
% They should be because of the timestamp
files = dir("*.bag");

run = 1;
for bagName = files'
    % Open bag and check for collision
    bag = rosbag(bagName.name);
   
    % Retrieve parameters
    expConfig = expLog(run, 2:end).Variables;
    param1 = config(expConfig(1), :).Variables;
    param2 = config(expConfig(2), :).Variables;

    fprintf("Run %d\n", run);
    % Calculating absolute position
    [gnssTime, gnssPose] = gnss_pose(bag);
    [ndtTime, ndtPose] = ndt_pose(bag);
    
    % Calculate absolute distance from origin
    gnssDist = sqrt(gnssPose(:,1).^2 + gnssPose(:, 2).^2);
    ndtDist = sqrt(ndtPose(:,1).^2 + ndtPose(:, 2).^2);
    
    % Plot graph
    
    figure
    plot(gnssTime, gnssDist, "b");
    hold on
    plot(ndtTime, ndtDist, "r");
    
    xlabel("Time [s]");
    ylabel("Distance towards origin [m]");
    if(param1(2) == "0")
        title("No Rain");
    else
        title("With Rain");
    end

    run = run + 1;
end

%% Exiting
cd(initFolder);

%% Functions

function [time, poseArray] = gnss_pose(bag)
    gnssSelect = select(bag, "Topic", "/gnss_pose");
    time = gnssSelect.MessageList.Time;
    gnssMsgs = gnssSelect.readMessages;
    poseArray = zeros(length(gnssMsgs), 2);
    for i = 1:length(gnssMsgs)
        position = gnssMsgs{i}.Pose.Position;
        poseArray(i,:) = [position.X position.Y];
    end
end

function [time, poseArray] = ndt_pose(bag)
    ndtSelect = select(bag, "Topic", "/ndt_pose");
    time = ndtSelect.MessageList.Time;
    ndtMsgs = ndtSelect.readMessages;
    poseArray = zeros(length(ndtMsgs), 2);
    for i = 1:length(ndtMsgs)
        position = ndtMsgs{i}.Pose.Position;
        poseArray(i,:) = [position.X position.Y];
    end
end
