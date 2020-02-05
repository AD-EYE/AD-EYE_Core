%% Config

% Output folder (Where all the Run_XX folders and the videos will be created
dest = "\\192.168.122.1\Shared_Drive\collision_results_narrow\Rain5";
% Experiment folder (Where the script will find the Experiments as
% created by the TA_OpenSCENARIO_interface.m script
expDir = dest + "\Experiments\";

% The number of frame in each videos
FrameNumber = 75;

%%  Extract Images in  Run folders
cd(expDir);

files = dir;

N = 0;

% Going through each experiments
for file = files'
    if(file.isdir && file.name ~= "." && file.name ~= "..")
        cd(file.folder + "\" + file.name + "\Simulation\Results");
        results = dir;
        % Going through each results dir
        for res = results'
            if(res.name ~= "." && res.name ~= "..")
                N = N + 1;
                cd (res.folder + "\" + res.name);
                run = dir;
                run = run(3).name; % Getting the index of the run
                
                fprintf("Extracting images of  %s\n", run);
                
                cd(run + "\Results\");
                lastFolder = dir;
                lastFolder = lastFolder(3).name; % One last dir
                cd(lastFolder + "\HumViewCamera");

                %Copy images to destination
                mkdir(dest, run);

                copyfile("*", dest + "\" + run + "\");
            end
        end
    end
end

cd(dest);

%% Create all the videos

base_folder = dest;

cd(base_folder)

f = waitbar(0, "Processing Run", "Name", "Creating Videos");

for run = 1:N
    waitbar(run/N, f, sprintf("Processing Run %d", run));
    folder = "Run_" + run;
    cd(folder);
    createVideo(folder, FrameNumber)
    cd ../
end

close(f)


%%

function createVideo(name, frameNumber)
    f = waitbar(0, "Processing image", 'Name', "Creating Video " + name); 
    N = frameNumber;
    writerObj = VideoWriter(char("../" +  name));
    writerObj.FrameRate=5;
    open(writerObj);
    for K = 0 : N
        waitbar(K/N, f, sprintf("Processing image %d/%d", K, N));
        filename = sprintf('HumViewCamera_%05d.png', K);
        png = imread(filename);
        writeVideo(writerObj, png);
    end
    close(writerObj);
    close(f);
end