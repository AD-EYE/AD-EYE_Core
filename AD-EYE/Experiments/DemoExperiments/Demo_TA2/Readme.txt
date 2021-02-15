% ================================================================================================================
% Follow the next steps to perform test automation of experiment Demo_TA2 in which rebuilds are required.
% It is recommended to first inspect Demo_TA2 in the Experiment Editor.
% ================================================================================================================

Step 1.	Open the Prescan GUI and invoke Simulink Run Mode to open MATLAB.

Step 2. Within MATLAB, navigate to the Demo_TA2 directory.

Step 3. Run Demo_TA2_Runscript.m to start the simulations. For each simulation the following steps are performed:
	CommandLineInterface:
		- Clone original (Demo_TA2) experiment.
		- Modify Experiment
		- Build Experiment
	MATLAB:
		- Update compilation sheet
		- Run simulation

Afterwards, for each simulation, the number of detections per TIS beam is displayed.
Explore the Demo_TA2\Results directory for general gathered data. Specific points of interest are:
	- Demo_TA2\Results\TA_<date>\Run_<Nr>\settings.txt
	- Demo_TA2\Results\TA_<date>\Run_<Nr>\Results\simout.mat