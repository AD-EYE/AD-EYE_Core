function RebuildingTrafficScenario()
% =========================================================================
% This demo creates .png files which can be used to make a movie.
%
% Author:   Erik Vermeer
% Company:  TNO Automotive, Helmond, the Netherlands.
% Date:     30 november 2006.
%
% This demo plot tool is based on the simulation Demo_RebuildingTrafficScenario.mdl
%
% Default TIS settings: #Beams              = 20
%                       Sweep rate [Hz]     = 10
%                       Beam Type           = Pencil
%                       FoV in Azimuth [deg]= 45
%                       Range [m]           = 50
% =========================================================================

%clear all
close all
clc


% =========================================================================
%
% Simulation Settings and Parameters
%
% =========================================================================

StartTime           = 0;            % in seconds (min 0 as default)
StopTime            = 13.5;         % in seconds (max 13.5 as default)
Outputfilename      = 'simout';     % .png filename and .avi filename
OutputDir = sprintf('Results/Results_%04.0f%02.0f%02.0f_%02.0f%02.0f%02.0f',clock);
mkdir(OutputDir);

% Note: To make the movie set the parameter GenerateMovie to 1
% or use the program pjBmp2Avi in the folder bmp2avi.
GenerateMovie=0;



% Fixed settings, need to be changed if other TIS settings are
% made in the PreScan GUI
NumBeams            = 20;
SweepRate           = 10;
NumSweeps           = (StopTime-StartTime)*SweepRate;%last sweep is not finished, therefore there is not an extra sweep added here






% =========================================================================
%
% POST PROCESSING (make .png output files)
%
% Load the simulation data of the TIS and AIR sensor and create a .png file
% for every sweep of the TIS sensor
%
% =========================================================================

% Load simulation output files
BeamsData       = load('TIS_Output.mat');
TrajectoryData  = load('AIR_Output.mat');

% For every IndexSweeps calculate the output data per beam IndexBeams
for IndexSweeps = 1:NumSweeps

    % Calculate the time based on the sweeprate of the TIS sensor
    t = (IndexSweeps-1)/SweepRate+StartTime;

    % Set all indices to 0
    i=0;
    k=0;
    m=0;
    n=0;

    % Create a new figure for the next TIS Sensor sweep
    scrsz = get(0,'ScreenSize');
    figure1 = figure('Color',[1 1 1]);%('Position',[1 scrsz(4) scrsz(3)/2 scrsz(4)/2],'Color',[1 1 1]);
    AxesHandelGeneral = axes('Position',[0.15 0.1 0.8 0.8]);
    axis([0 50 -20 20]);


    for IndexBeams = 1 : NumBeams

        % TIS sensor data
        RangeDataSensor(IndexBeams,IndexSweeps)  = BeamsData.ans(3,IndexBeams+((IndexSweeps-1)*NumBeams));
        AziDataSensor(IndexBeams,IndexSweeps)    = -(BeamsData.ans(4,IndexBeams+((IndexSweeps-1)*NumBeams))/180)*pi;
        ElevDataSensor(IndexBeams,IndexSweeps)   = (BeamsData.ans(5,IndexBeams+((IndexSweeps-1)*NumBeams))/180)*pi;
        ID(IndexBeams,IndexSweeps)               = BeamsData.ans(6,IndexBeams+((IndexSweeps-1)*NumBeams));

        % Air Sensor data
        vxID1(IndexBeams,IndexSweeps)            = TrajectoryData.ans(6,IndexBeams+((IndexSweeps-1)*NumBeams));
        vxID2(IndexBeams,IndexSweeps)            = TrajectoryData.ans(7,IndexBeams+((IndexSweeps-1)*NumBeams));
        vxID3(IndexBeams,IndexSweeps)            = TrajectoryData.ans(8,IndexBeams+((IndexSweeps-1)*NumBeams));
        vxID4(IndexBeams,IndexSweeps)            = TrajectoryData.ans(9,IndexBeams+((IndexSweeps-1)*NumBeams));

        HID1(IndexBeams,IndexSweeps)             = TrajectoryData.ans(10,IndexBeams+((IndexSweeps-1)*NumBeams));
        HID2(IndexBeams,IndexSweeps)             = TrajectoryData.ans(11,IndexBeams+((IndexSweeps-1)*NumBeams));
        HID3(IndexBeams,IndexSweeps)             = TrajectoryData.ans(12,IndexBeams+((IndexSweeps-1)*NumBeams));
        HID4(IndexBeams,IndexSweeps)             = TrajectoryData.ans(13,IndexBeams+((IndexSweeps-1)*NumBeams));

        % Spherical to Cartesian transformation, xID = cos(AziAngle).*Range,
        % yID =sin(AziAngle).*Range
        AziDataPlot(IndexBeams,IndexSweeps)      = AziDataSensor(IndexBeams,IndexSweeps);
        RangeDataPlot(IndexBeams,IndexSweeps)    = RangeDataSensor(IndexBeams,IndexSweeps);

        [xID(IndexBeams,IndexSweeps),yID(IndexBeams,IndexSweeps)] = pol2cart(AziDataPlot(IndexBeams,IndexSweeps),RangeDataPlot(IndexBeams,IndexSweeps));

        % Plot the sensor data points of each ID in a different color

        if ID(IndexBeams,IndexSweeps) == 2

            i=i+1;

            % Calculate the data properties of ID 1 and calculate
            % the values of the nearest point of ID 1 to the sensor
            ID1.RangeDataSensor(i,1)= RangeDataSensor(IndexBeams,IndexSweeps);
            ID1.MinRange            = min(ID1.RangeDataSensor);
            ID1.AziDataSensor(i,1)  = AziDataSensor(IndexBeams,IndexSweeps);
            ID1.MeanAzi             = mean(ID1.AziDataSensor);
            ID1.ElevData(i,1)       = ElevDataSensor(IndexBeams,IndexSweeps);
            ID1.MeanElev            = mean(ID1.ElevData);
            ID1.vxData(i,1)         = vxID1(IndexBeams,IndexSweeps);
            ID1.HData(i,1)          = HID1(IndexBeams,IndexSweeps);

            ID1.ID                  = 2;

            % Plot the data points of ID 1 in cartesian coordinates
            plot(xID(IndexBeams,IndexSweeps),yID(IndexBeams,IndexSweeps),'b.')
            hold on
            axis([0 50 -20 20]);


        end

        if ID(IndexBeams,IndexSweeps) == 3

            k=k+1;

            % Calculate the data properties of ID 2 and calculate
            % the values of the nearest point of ID 2 to the sensor
            ID2.RangeDataSensor(k,1)= RangeDataSensor(IndexBeams,IndexSweeps);
            ID2.MinRange            = min(ID2.RangeDataSensor);
            ID2.AziDataSensor(k,1)  = AziDataSensor(IndexBeams,IndexSweeps);
            ID2.MeanAzi             = mean(ID2.AziDataSensor);
            ID2.ElevData(k,1)       = ElevDataSensor(IndexBeams,IndexSweeps);
            ID2.MeanElev            = mean(ID2.ElevData);
            ID2.vxData(k,1)         = vxID2(IndexBeams,IndexSweeps);
            ID2.HData(k,1)          = HID2(IndexBeams,IndexSweeps);

            ID2.ID                  = 3;

            % Plot the data points of ID 2 in cartesian coordinates

            plot(xID(IndexBeams,IndexSweeps),yID(IndexBeams,IndexSweeps),'g.')
            hold on
            axis([0 50 -20 20]);

        end

        if ID(IndexBeams,IndexSweeps) == 4

            m=m+1;

            % Calculate the data properties of ID 1 and calculate
            % the values of the nearest point of ID 1 to the sensor
            ID3.RangeDataSensor(m,1)= RangeDataSensor(IndexBeams,IndexSweeps);
            ID3.MinRange            = min(ID3.RangeDataSensor);
            ID3.AziDataSensor(m,1)  = AziDataSensor(IndexBeams,IndexSweeps);
            ID3.MeanAzi             = mean(ID3.AziDataSensor);
            ID3.ElevData(m,1)       = ElevDataSensor(IndexBeams,IndexSweeps);
            ID3.MeanElev            = mean(ID3.ElevData);
            ID3.vxData(m,1)         = vxID3(IndexBeams,IndexSweeps);
            ID3.HData(m,1)          = HID3(IndexBeams,IndexSweeps);

            ID3.ID                  = 4;

            % Plot the data points of ID 1 in cartesian coordinates
            plot(xID(IndexBeams,IndexSweeps),yID(IndexBeams,IndexSweeps),'y.')
            hold on
            axis([0 50 -20 20]);


        end

        if ID(IndexBeams,IndexSweeps) == 5

            n=n+1;

            % Calculate the data properties of ID 1 and calculate
            % the values of the nearest point of ID 1 to the sensor
            ID4.RangeDataSensor(n,1)= RangeDataSensor(IndexBeams,IndexSweeps);
            ID4.MinRange            = min(ID4.RangeDataSensor);
            ID4.AziDataSensor(n,1)  = AziDataSensor(IndexBeams,IndexSweeps);
            ID4.MeanAzi             = mean(ID4.AziDataSensor);
            ID4.ElevData(n,1)       = ElevDataSensor(IndexBeams,IndexSweeps);
            ID4.MeanElev            = mean(ID4.ElevData);
            ID4.vxData(n,1)         = vxID4(IndexBeams,IndexSweeps);
            ID4.HData(n,1)          = HID4(IndexBeams,IndexSweeps);

            ID4.ID                  = 5;

            % Plot the data points of ID 1 in cartesian coordinates
            plot(xID(IndexBeams,IndexSweeps),yID(IndexBeams,IndexSweeps),'r.')
            hold on
            axis([0 50 -20 20]);

        end

    end

    if exist('ID1') == 1

        ID1.RangeDataPlot=ID1.RangeDataSensor;
        ID1.AziDataPlot=ID1.AziDataSensor;
        [xCogID1,yCogID1] = pol2cart(mean(ID1.AziDataPlot),mean(ID1.RangeDataPlot));
        vxCogID1 = mean(ID1.vxData);
        HCogID1  = mean(ID1.HData);
        text(xCogID1+1,yCogID1,{...
            ['ID = ',num2str(ID1.ID)],...
            ['v_{rel} = ',num2str(round(vxCogID1))],...
            ['H_{rel} = ',num2str(round(HCogID1))]},...
            'FontSize',6,'Color',[0 0 0])

    end

    if exist('ID2') == 1

        ID2.RangeDataPlot=ID2.RangeDataSensor;
        ID2.AziDataPlot=ID2.AziDataSensor;
        [xCogID2,yCogID2] = pol2cart(mean(ID2.AziDataPlot),mean(ID2.RangeDataPlot));
        vxCogID2 = mean(ID2.vxData);
        HCogID2  = mean(ID2.HData);
        text(xCogID2+1,yCogID2,{...
            ['ID = ',num2str(ID2.ID)],...
            ['v_{rel} = ',num2str(round(vxCogID2))],...
            ['H_{rel} = ',num2str(round(HCogID2))]},...
            'FontSize',6,'Color',[0 0 0])

    end

    if exist('ID3') == 1

        ID3.RangeDataPlot=ID3.RangeDataSensor;
        ID3.AziDataPlot=ID3.AziDataSensor;
        [xCogID3,yCogID3] = pol2cart(mean(ID3.AziDataPlot),mean(ID3.RangeDataPlot));
        vxCogID3 = mean(ID3.vxData);
        HCogID3  = mean(ID3.HData);
        text(xCogID3+1,yCogID3,{...
            ['ID = ',num2str(ID3.ID)],...
            ['v_{rel} = ',num2str(round(vxCogID3))],...
            ['H_{rel} = ',num2str(round(HCogID3))]},...
            'FontSize',6,'Color',[0 0 0])

    end

    if exist('ID4') == 1

        ID4.RangeDataPlot=ID4.RangeDataSensor;
        ID4.AziDataPlot=ID4.AziDataSensor;
        [xCogID4,yCogID4] = pol2cart(mean(ID4.AziDataPlot),mean(ID4.RangeDataPlot));
        vxCogID4 = mean(ID4.vxData);
        HCogID4  = mean(ID4.HData);
        text(xCogID4+1,yCogID4,{...
            ['ID = ',num2str(ID4.ID)],...
            ['v_{rel} = ',num2str(round(vxCogID4))],...
            ['H_{rel} = ',num2str(round(HCogID4))]},...
            'FontSize',6,'Color',[0 0 0])

    end


    % Add axis arrows
    xlabel('Boresight [m]','Position',[45 -1 0],'FontSize',12)
    ylabel('Side [m]','Position',[-1.25 5 0],'FontSize',12,'Rotation',90)

    annotation1 = annotation(...
        figure1,'textarrow',...
        [0.15 0.25],[0.50 0.50],...
        'String',{});

    annotation2 = annotation(...
        figure1,'textarrow',...
        [0.15 0.15],[0.5 0.6],...
        'String',{});

    annotation3 = annotation(...
        'textbox',...
        'Position',[0.175 0.825 0.4 0.05],...
        'FontSize',14,...
        'FontWeight','bold',...
        'LineStyle','none',...
        'String',{['t = ',num2str(t),' s']},...
        'FitHeightToText','on');

    % Plot the sensor limits
    plot([0 40],[0 20],'r--')
    hold on
    plot([0 40],[0 -20],'r--')
    hold on
    plot([0 50],[0 0],'Color',[0 0 0])
    hold on
    grid on

    % Add Mazda picture
    AxesHandleCar = axes('Position',[0.05 0.478 0.1 ((0.1/4.425)*1.86)]);
    I=imread('mazda_RX8_top.bmp');
    hi=imagesc(I);
    set(AxesHandleCar,'Visible','off')

    set(AxesHandelGeneral,'Color',[0.7 0.7 0.7]);

    % Set that the background is copied to .bmp as well
    set(gcf, 'InvertHardCopy', 'off');

    % Make a screen shot and save as a .png file
    fileout = sprintf([OutputDir '/' Outputfilename,'_%06d.png'], IndexSweeps-1);
    disp(['Creating: ',fileout])
    res = [480 400];
    set(gcf, 'Position', [10 400 res(1) res(2)], ...
        'PaperUnits', 'inches', 'PaperPosition', [0 0 res(1) res(2)]);
    frame = getframe(gcf);
    imwrite(frame.cdata, fileout);

    % Clear the IDs
    clear ID1
    clear ID2
    clear ID3
    clear ID4

    % Close figure 1 and go to the next sensor sweep
    close(figure1)

end


% Note: To make the movie choose eiher MovieGenerator or use the program
% pjBmp2Avi in the folder bmp2avi.
