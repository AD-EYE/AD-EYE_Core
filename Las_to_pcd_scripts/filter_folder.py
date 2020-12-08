#import laspy
import os
import sys
import subprocess

#path="/mnt/d/3D_interactive_map/"
path="/media/adeye/Ny volym/3D_interactive_map/"
files = []
files_partial = []
dirpaths = []
idx_list = []
idx = 0

# Extract all possible paths to files from input path:  
for (dirpath, dirnames, filenames) in os.walk(path):
   for dname in dirnames:
      dirpaths.append(path+dname+'/')
   break

# For every possible path, make a list of files in that path. Ignore any .pcd files.
for dpath in dirpaths:
   for (dirpath, dirnames, filenames) in os.walk(dpath):
      files_partial.extend(filenames)
      for item in files_partial:
         if ".pcd" not in item:
            files_partial.remove(item)
      files.append(files_partial)
      files_partial =[]
i=0

# For each batch of files in "files".
for folder in files:
   # For each file in file batch.
   for f in folder:

      # Filter using the pcd_filter.cpp compiled file.
      data, temp = os.pipe() 
  
      # write to STDIN as a byte object(convert string 
      # to bytes with encoding utf8) 
      os.write(temp, bytes("5 10\n", "utf-8")); 
      os.close(temp)
      
      input_file=dirpaths[i]+f
      print(input_file)
      subprocess.check_call(["./pcd_filter" ,"-f", input_file],  stdin = data)
      print("Filtered map " + input_file+ " saved.")
   i+=1
