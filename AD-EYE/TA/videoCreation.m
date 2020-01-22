
base_folder = "\\192.168.122.1\Shared_Drive\OpenScenario_Results\KTH_car_Rain0";

cd(base_folder)

N = 12;

f = waitbar(0, "Processing Run", "Name", "Creating Videos");

for run = 1:N
    waitbar(run/N, f, sprintf("Processing Run %d", run));
    folder = "Run_" + run;
    cd(folder);
    createVideo(folder)
    cd ../
end

close(f)

%%

function createVideo(name)
    f = waitbar(0, "Processing image", 'Name', "Creating Video " + name); 
    N = 100;
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