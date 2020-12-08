import laspy
import os
import sys
import subprocess

PRINT_REGULARITY = 100000 # will print every PRINT_REGULARITY points
SEPARATION_CHAR = " "
WRITE_ALL = True
WRITE_INTENSITY = False
FILE_LIMIT = True
FILE_READ_AMT = 5
FILE_NAME_NR = 1
POINTS_THRESHOLD = 1e10
READ_FREQUENCY = 1 # Read every x points. Use for testing and to reduce cloud size.

def scaled_x_dimension(las_file):
    x_dimension = las_file.X
    scale = las_file.header.scale[0]
    offset = las_file.header.offset[0]
    return(x_dimension*scale + offset)
def scaled_y_dimension(las_file):
    y_dimension = las_file.Y
    scale = las_file.header.scale[1]
    offset = las_file.header.offset[1]
    return(y_dimension*scale + offset)
def scaled_z_dimension(las_file):
    z_dimension = las_file.Z
    scale = las_file.header.scale[2]
    offset = las_file.header.offset[2]
    return(z_dimension*scale + offset)

# Voxel filtering function. Requires pcd_filter.cpp file to be compiled and ready to go.
def voxel_filter():
    try:
        data, temp = os.pipe() 
        os.write(temp, bytes("5 10\n", "utf-8")); 
        os.close(temp)
        
        input_file=path+str(filename[:filename_size-4])+".pcd"
        print(input_file)
        subprocess.check_call(["/home/adeye/Projects/AD-EYE_Core/Point-cloud-mapper/build/pcd_filter","-f",input_file],  stdin = data)

        print("Filtered map " + input_file+ " saved.")
    
    except:
        print("Voxel filter error. Moving on. Make sure the pcd filter path is correct (default: /home/adeye/Projects/AD-EYE_Core/Point-cloud-mapper/build/pcd_filter)")    
        

path="/media/adeye/Ny volym/3D_interactive_map/"
files = []
files_partial = []
dirpaths = []
idx_list = []
idx = 0

# Extract all possible paths to files from input path:  
for (dirpath, dirnames, filenames) in os.walk(path):
    if dirpath != path:
        dirpaths.append(dirpath + "/")
        idx_list.append(idx)
        idx += 1

# For every possible path, make a list of files in that path. Ignore any .pcd files.
for dpath in dirpaths:
    for (dirpath, dirnames, filenames) in os.walk(dpath):
        files_partial.extend(filenames)
        # Remove any pcd files from read list:
        for item in files_partial:
            if ".pcd" in item:
                files_partial.remove(item)
        files.append(files_partial)
        files_partial = []

# Make a copy. Use "files" variable for one batch of files at a time.
files_copy = files

# Declare offsets
x_offset = 0
y_offset = 0
z_offset = 0
offsets_set = False

# Keep only x many folders. Useful for testing/debugging.
if FILE_LIMIT:
    files = files[:FILE_READ_AMT]

for i in idx_list:

    idx = 0
    
    path = dirpaths[i]
    files = files_copy[i]

    print(path)
    print(files)

    # Safety precaution. The script sometimes doesn't want to write the last few points.
    try:

        for file in files:

            # Reset vars:
            x_points_shrunk = []
            y_points_shrunk = []
            z_points_shrunk = []
            reds_shrunk = []
            greens_shrunk = []
            blues_shrunk = []
            intensities_shrunk = []

	    # Sometimes fails during the last few points. Try statement acts as a rough fix.
            inFile = laspy.file.File(path+file, mode="r")

            scaled_x = scaled_x_dimension(inFile)
            scaled_y = scaled_y_dimension(inFile)
            scaled_z = scaled_z_dimension(inFile)

            if not offsets_set:
                x_offset = scaled_x[0]
                y_offset = scaled_y[0]
                z_offset = scaled_z[0]
                offsets_set = True

            centered_x = scaled_x - x_offset
            centered_y = scaled_y - y_offset
            centered_z = scaled_z - z_offset


            x_points = centered_x
            y_points = centered_y
            z_points = centered_z
            reds = inFile.red
            greens = inFile.green
            blues = inFile.blue
            intensities = inFile.intensity


            i=0
            index=0
            while i<len(x_points) and index < POINTS_THRESHOLD:

                #if z_points[index]>-10: # Use if there is noise below ground level.
                i+=1
                if i%PRINT_REGULARITY==0:
                    print("Reading file " + file + ": " +str(i) + " / " + str(len(x_points)))
		#Read every READ_FREQUENCY times. Acts as a very rough filter for basic testing. Set 			 to 1 to turn off.
                if i%READ_FREQUENCY == 0:    
                    x_points_shrunk.append(x_points[index])
                    y_points_shrunk.append(y_points[index])
                    z_points_shrunk.append(z_points[index])
                    reds_shrunk.append(reds[index]/256)
                    greens_shrunk.append(greens[index]/256)
                    blues_shrunk.append(blues[index]/256)
                    intensities_shrunk.append(intensities[index])
                    index+=1


            filename = files[idx]
            filename_size = len(filename)
            f = open(path+"/"+str(filename[:filename_size-4])+".pcd", "w") # Note, the "-4" is to remove the .las extension 
            idx += 1
            f.write("# .PCD v0.7 - Point Cloud Data file format\n")
            f.write("VERSION 0.7\n")
            f.write("FIELDS x y z r g b intensity\n")
            f.write("SIZE 4 4 4 4 4 4 4\n")
            f.write("TYPE F F F F F F F\n")
            f.write("COUNT 1 1 1 1 1 1 1\n")
            f.write("WIDTH "+ str(len(x_points_shrunk)) +"\n")
            f.write("HEIGHT 1\n")
            f.write("VIEWPOINT 0 0 0 1 0 0 0\n")
            f.write("POINTS " + str(len(x_points_shrunk)) + "\n")
            f.write("DATA ascii\n")

            for i in range(len(x_points_shrunk)):
                if i%PRINT_REGULARITY==0:
                    print ("Writing output file: " + str(i) + " / " + str(len(x_points_shrunk)))
                if WRITE_ALL:
                    f.write(str(x_points_shrunk[i])+ SEPARATION_CHAR + str(y_points_shrunk[i]) + SEPARATION_CHAR + str(z_points_shrunk[i]) + SEPARATION_CHAR + str(reds_shrunk[i])+ SEPARATION_CHAR + str(greens_shrunk[i]) + SEPARATION_CHAR + str(blues_shrunk[i]) + SEPARATION_CHAR + str(intensities_shrunk[i]) + "\n")
                elif WRITE_INTENSITY:
                    f.write(str(x_points_shrunk[i])+ SEPARATION_CHAR + str(y_points_shrunk[i]) + SEPARATION_CHAR + str(z_points_shrunk[i]) + SEPARATION_CHAR + str(intensities_shrunk[i]) + "\n")
                else:
                    f.write(str(x_points_shrunk[i])+ SEPARATION_CHAR + str(y_points_shrunk[i]) + SEPARATION_CHAR + str(z_points_shrunk[i]) + "\n")        
            f.close()

            # If no error, voxel filter as normal:
            voxel_filter()
    except:
        print("Writing error. Moving on to voxel filter.")
        voxel_filter() # If writing fails, try to move on to .pcd voxel filter and filter whatever you have
        

print("Finished!")
