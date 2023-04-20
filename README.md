AD-EYE: Automated Driving simulations

This branch aimed to optimize the performance for running AD-EYE code on Nvidia Drive PX2.

This branch was created during Yuyang's internship at AD-EYE. Please go to his internship report to see the details.

The branch is modified in order to benchmark the performance based on the changes made. In general, the goal is to find out a good parameter set that could allow AD-EYE code run at a satisfying rate (FPS) on PX2, which has limited computational power. 

Briefing:
1. change to a smaller SSD model
2. For `vision_ssd_detection` node, use only camera_1 to benchmark the performance (FPS)
3. results recorded from different parameter set (see internship folder on OneDrive)
4. Exploration on modifiable parameters.
