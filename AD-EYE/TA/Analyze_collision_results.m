%% Initialisation
base = "\\192.168.122.1\Shared_Drive\collision_results_narrow\";
folderName = "Rain1";
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
config("AutowareConfig2.xlsx",:) = {"speed", 7.5};
config("AutowareConfig3.xlsx",:) = {"speed", 10};
config("AutowareConfig4.xlsx",:) = {"speed", 12.5};
config("AutowareConfig5.xlsx",:) = {"speed", 15};
config("KTH_car_osc1",:) = {"triggerDistance", 15};
config("KTH_car_osc2",:) = {"triggerDistance", 17.5};
config("KTH_car_osc3",:) = {"triggerDistance", 20};
config("KTH_car_osc4",:) = {"triggerDistance", 22.5};
config("KTH_car_osc5",:) = {"triggerDistance", 25};

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
    [collision, collisionTime, collisionSpeed, pose] = checkCollision(bag);
    
    % Retrieve parameters
    expConfig = expLog(run, 2:end).Variables;
    param1 = config(expConfig(1), :).Variables;
    param2 = config(expConfig(2), :).Variables;

    fprintf("Run %d\n", run);
    if(collision)
        fprintf("Collision occurs at %f\n", collisionTime);
        fprintf("%s = %s  ;  %s = %s\n", param1, param2);
        fprintf("Collision speed : %f\n", collisionSpeed);
        fprintf("Position (x, y) = (%f, %f)\n", pose);
    else
        pose = lastPose(bag);
        fprintf("Last Position (x, y) = (%f, %f)\n", pose);
    end
    % Storing results
    results(run, :) = {str2double(param1(2)), str2double(param2(2)), ...
        collisionTime, pose, collisionSpeed};

    run = run + 1;
end

results.Properties.VariableNames = [param1(1), param2(1), "collisionTime", ...
    "position", "collisionSpeed"];

%% Tracing graphs

dist = results.triggerDistance;
carSpeed = results.speed;
collisionSpeed = results.collisionSpeed;

xlin = linspace(min(dist), max(dist));
ylin = linspace(min(carSpeed), max(carSpeed));
[X, Y] = meshgrid(xlin, ylin);

f = scatteredInterpolant(dist, carSpeed, collisionSpeed);

Z = f(X,Y);

figure;
surf(X, Y, Z, "EdgeColor", "none", "FaceAlpha", 0.9);
hold on;
stem3(dist, carSpeed, collisionSpeed, "filled", "MarkerFaceColor", "g");

xlabel("Trigger distance [m]");
ylabel("Car maximum speed [m/s]");
zlabel("Collision Speed [m/s]");


%% Saving results table

cd(base)

save(folderName, "results");

%% Exiting
cd(initFolder);

%% Functions
function [collision, time, speed, pose] = checkCollision(bag)
    collision = false;
    
    collisionSelect = select(bag, "Topic", "/collision");
    collisionMsgs = collisionSelect.readMessages;
    
    % Detect if collision occurs
    for i = 1:length(collisionMsgs)
        if(collisionMsgs{i}.Data == 1)
            collision = true;
            break
        end
    end
    
    % Find the collision speed
    if(collision)
        time = collisionSelect.MessageList.Time(i); % Collision time
        % Selecting topics
        poseSelect = select(bag, "Topic", "/gnss_pose", "Time", [time bag.EndTime]);
        velocitySelect = select(bag, "Topic", "/current_velocity", "Time", [time bag.EndTime]);
        % Reading the first message at the right time
        poseStamped = poseSelect.readMessages{1};
        twistStamped = velocitySelect.readMessages{1};
        % Extracting values
        position = poseStamped.Pose.Position;
        pose = [position.X position.Y];
        speed = twistStamped.Twist.Linear.X;
    else
        speed = 0;
        time = -1;
        pose = [nan, nan];
    end
end

function pose = lastPose(bag)
    poseSelect = select(bag, "Topic", "/gnss_pose",...
        "Time", [bag.EndTime-1 bag.EndTime]);
    lastElt = height(poseSelect.MessageList);
    poseStamped = poseSelect.readMessages{lastElt};
    position = poseStamped.Pose.Position;
    pose = [position.X position.Y];
end