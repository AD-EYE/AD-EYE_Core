import laspy
import os
import sys

PRINT_REGULARITY = 100000 # will print every PRINT_REGULARITY points
SEPARATION_CHAR = " "
WRITE_ALL = False
WRITE_INTENSITY = True
FILE_LIMIT = True
FILE_READ_AMT = 5
POINTS_THRESHOLD = 1e10
READ_FREQUENCY = 1 # Read every x points. Use to reduce cloud size.

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

x_points_shrunk = []
y_points_shrunk = []
z_points_shrunk = []
reds_shrunk = []
greens_shrunk = []
blues_shrunk = []
intensities_shrunk = []
x_offset = 0
y_offset = 0
z_offset = 0
offsets_set = False

# Possibly automate this bit?
path="/media/adeye/Ny volym/3D_interactive_map/ITM kortera parkeringen/"
files = []

# Extract file names from input directory: 
for (dirpath, dirnames, filenames) in os.walk(path):
    files.extend(filenames)
    break

if FILE_LIMIT:
    files = files[:FILE_READ_AMT]

for file in files:
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

        #if z_points[index]>-10: #we do not want underground
        i+=1
        if i%PRINT_REGULARITY==0:
            print("reading file" + file + ": " +str(i) + " / " + str(len(x_points)))
        if i%READ_FREQUENCY == 0:    
            x_points_shrunk.append(x_points[index])
            y_points_shrunk.append(y_points[index])
            z_points_shrunk.append(z_points[index])
            reds_shrunk.append(reds[index]/256)
            greens_shrunk.append(greens[index]/256)
            blues_shrunk.append(blues[index]/256)
            intensities_shrunk.append(intensities[index])
            index+=1

# Saves all read .las files in one large .pcd
filesize = len(file)
f = open(path+"/"+str(file[:filesize-4]) + ".pcd", "w")
f.write("# .PCD v0.7 - Point Cloud Data file format\n")
f.write("VERSION 0.7\n")
f.write("FIELDS x y z intensity\n")
f.write("SIZE 4 4 4 4\n")
f.write("TYPE F F F F\n")
f.write("COUNT 1 1 1 1\n")
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
