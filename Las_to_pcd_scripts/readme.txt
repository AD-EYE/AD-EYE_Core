
Name: las_2_txt.py

Description: 

	- Original file. 
	- Reads all .las files in a path (even if path contains several folders with .las files)
	- Outputs ONE .pcd containing all the .las information


Name: las_2_txt_multifolder.py

Description:

	- Reads all .las files in a path 
	  (even if path contains several folders with .las files)
	- Outputs one .pcd per .las file in the location of the .las file. Works with multiple 		  folders.
	- Some compatibility issues between laspy and python (suboptimally) can be solved with 		  try/except statements, as implemented in las_2_txt_multifolder_voxelfilter.py


Name: filter_folder.py

Description:

	- Uses pcd_filter.cpp (remember to build/compile first!) to apply voxel filtering to .pcds


Name: las_2_txt_multifolder_voxelfilter.py

Description:

	- A rough stitching of las_2_txt_multifolder.py and filter_folder.py
	- Converts a series of .las files to .pcds and downsamples them using a voxel filter
	- Has the same compatibility issues as las_2_txt_multifolder.py, but they are (badly) 		  resolved using try/except statements.
	- Tested on large sets of .las files on long overnight runs - proven to work.
