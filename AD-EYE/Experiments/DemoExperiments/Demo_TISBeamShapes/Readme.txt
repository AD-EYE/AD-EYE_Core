% ================================================================================================================
% Follow the next steps to create your own experiment with the Demo_TISBeamShapes
% ================================================================================================================

Step 1.	Open the Prescan GUI and open the Demo_TISBeamShapes.pex file.

Step 2. click on the Invoke Simulation Run Mode Button and Matlab will be opened.

Step 3. Check if Matlab opened the directory where the experiment was saved. Then open the simulink file
	Demo_TISBeamShapes_cs.slx file using Matlab.

Step 4. Start the Simulink model and wait until the simulation is completely finished. This generates the
        five output files required for steps 5 and 6.

Step 5. Use the function 'plotBeams' to illustrate the four beam shapes as function of time. For more
        information type 'help plotBeams' or refer to the Prescan Help Manual for more details. To show
        the plot in the Prescan Help Manual type:

        >> plotBeams

Step 6. Use the function 'plotBeam' for a more detailed plot of a single beam. Various way to call this 
        function are implemented. For more information type 'help plotBeam' or refer to the Prescan Help
        Manual for more details. As an example, to create the plot in the Prescan Help Manual type
        
        >> plotBeam(2,7,5)

        To animate the first beam type:

        >> plotBeam(1)


Steps 5 and 6 can be repeated without re-running the simulation unless the experiment has been changed.