# -*- coding: utf-8 -*-

import os

pcd_folder = 'Pointcloud_Files' 
new_pcd_file = 'Pointcloud_Files/pcd_file.pcd' 

set_of_pcd = set()
total_length = 0
total_non_nan = 0

for file_name in os.listdir(pcd_folder):
    if file_name.endswith('.pcd'):
        file_path = os.path.join(pcd_folder, file_name)
        with open(file_path, 'r') as current_pcd_file:
            for current_line in current_pcd_file:
                total_length += 1
                current_line = current_line.strip()  # Clean the spaces at the beginning and at the end
                current_values = current_line.split() # Split the line into a list of 4 values
                if len(current_values) == 4 and not any(val == 'nan' for val in current_values):
                    total_non_nan += 1
                    current_values_rounded = ["{:.2f}".format(float(val)) for val in current_values] # Change .1f for .2 if you want to keep more decimals
                    current_line_rounded = ' '.join(current_values_rounded)
                    set_of_pcd.add(current_line_rounded)
    
        os.remove(file_path) # Uncomment if you want to delete the original pcd files after creating the new one

total_nan=total_length-total_non_nan
total_new_file=len(set_of_pcd)

with open(new_pcd_file, 'w') as new_pcd_file:
    # HEADER:
    new_pcd_file.write("""# This PCD file was generated using the MATLAB® pcwrite function
# from Computer Vision System Toolbox®.
# .PCD v.7 - Point Cloud Data file format
VERSION .7\nFIELDS x y z intensity\nSIZE 4 4 4 4\nTYPE F F F F\nCOUNT 1 1 1 1
WIDTH """+str(total_new_file)+'\nHEIGHT 1\nVIEWPOINT 0 0 0 1 0 0 0\nPOINTS '+str(total_new_file)+'\nDATA ascii\n')
    #POINTS:
    for current_line in set_of_pcd:
        new_pcd_file.write(current_line + '\n')
    print("\n##############\n\nAll single lines have been written to {}\n".format(new_pcd_file))


print("##############\n\nTotal line number before modification: {}".format(total_length))
print("Total line number after modification: {}".format(total_new_file))
print("Total saving: {}".format(total_length - total_new_file))
print("Total NaN : {}".format(total_nan))
print("Total similar lines: {}\n\n##############\n".format(total_length-total_new_file-total_nan))

total_new_file = float(total_new_file)
total_length = float(total_length)
total_nan = float(total_nan)

print("% NaN : {:.2f}%".format((((total_nan / total_length)) * 100)))
print("% Similar lines: {:.2f}%".format(((((total_length-total_nan-total_new_file) / total_length)) * 100)))
print("% Total saving: {:.2f}%\n\n##############\n".format(100-(((total_new_file / total_length)) * 100)))
