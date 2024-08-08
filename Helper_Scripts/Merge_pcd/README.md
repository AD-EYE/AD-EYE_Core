
<br>

## Overview

This script processes a folder of PCD files filters out lines containing 'NaN' or similar values.   

Then it write the remaining unique lines into a new PCD file.  

The script also allows to customize the rounding precision of the point cloud values (see 'Statistics' section).  

Use this code to merge all the pcd files into one big one. It deletes similar values as well as nan values, which saves space.
<br>
<br>
## Steps to run the code

1. Use this code to merge all the pcd files into one big one.
2. Run the python script on the inside of the `'world folder'` but on the outside of the `'Pointcloud_Files'` folder.   
Ex: run into `/home/adeye08u/AD-EYE_Core/AD-EYE/Experiments/W01_Base_World`

&nbsp;&nbsp;&nbsp;&nbsp;***>>> COMMAND TO RUN***
```sh
python pcd_modifier.py
```

3. Check if there is now only one pcd file named 'pcd_file.pcd'  
&nbsp;&nbsp;&nbsp;&nbsp;

<center>!! After that, make sure YOU CREATE a 'tar.gz' file names 'pcd_file.pcd.tar.gz' inside 'Pointcloud_Files' folder !! </center>  

<br> 

## Usage

- Total line number before modification: Total number of lines read from all input files.
- Total line number after modification: Total number of unique lines written to the new file.
- Total saving: Difference between the total lines before and after processing.
- Total NaN: Number of lines containing 'nan' values before filtering.
- % NaN: Percentage of lines containing 'nan' values before filtering.
- % Similar lines: Percentage of duplicate lines before filtering.
- % Total saving: Percentage of lines saved after filtering.
<br>
<br>
## Output and Statistics  
------------------------------------------------------------------------------------------------------------------  
>&nbsp;&nbsp;&nbsp;&nbsp;__ROUNDIND to 0 decimal {:.0f} OUTPUT:__  
>
>##############  
>
>- Total line number before modification: 1716071  
>- Total line number after modification: 137282  
>- Total saving: 1578789  
>- Total NaN : 439059  
>- Total similar lines: 1139730  
>
>##############  
>
>- % NaN : 25.59%  
>- % Similar lines: 66.42%  
>- % Total saving: 92.00%  
>
>##############  
>
>- SIZE_BEFORE = 61,8MB  
>- SIZE_AFTER = 1,6MB  
>
------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------  
>&nbsp;&nbsp;&nbsp;&nbsp;__ROUNDIND to 1 decimal {:.1f} OUTPUT:__  
>
>
>##############  
>
>- Total line number before modification: 1716071  
>- Total line number after modification: 1133551  
>- Total saving: 582520  
>- Total NaN : 439059  
>- Total similar lines: 143461  
>
>##############  
>
>- % NaN : 25.59%  
>- % Similar lines: 8.36%  
>- % Total saving: 33.94%  
>
>##############  
>
>- SIZE_BEFORE = 61,8MB  
>- SIZE_AFTER = 22,5MB  
>
------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------  
>&nbsp;&nbsp;&nbsp;&nbsp;__ROUNDIND to 2 decimal {:.2f} OUTPUT:__  
>
>
>
>- Total line number before modification: 1716071  
>- Total line number after modification: 1276372  
>- Total saving: 439699  
>- Total NaN : 439059  
>- Total similar lines: 640  
>
>##############  
>
>- % NaN : 25.59%  
>- % Similar lines: 0.04%  
>- % Total saving: 25.62%  
>
>##############  
>
>- SIZE_BEFORE = 61,8MB  
>- SIZE_AFTER = 30,5MB  
>
------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------
>&nbsp;&nbsp;&nbsp;&nbsp;__ROUNDIND to 3 decimal {:.3f} OUTPUT:__  
>
>
>##############  
>
>- Total line number before modification: 1716071   
>- Total line number after modification: 1277010  
>- Total saving: 439061  
>- Total NaN : 439059  
>- Total similar lines: 2  
>
>##############  
>
>- % NaN : 25.59%  
>- % Similar lines: 0.00%  
>- % Total saving: 25.59%  
>
>##############  
>
>- SIZE_BEFORE = 61,8MB  
>- SIZE_AFTER = 35,6MB  
>
------------------------------------------------------------------------------------------------------------------  