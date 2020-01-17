#! /usr/bin/env python3
#-*-coding: utf-8-*-

from sys import argv, exit
from os import chdir, walk, stat

# This script reads the ~/.ros/log files and the expDate.log file provided by Matlab
# To extract collision information regarding parameters

# /!\ This script is way messy and has been made for a specific solution
#       on reading specific logs for a specific purposes
#       There is a lot of NON-GENERIC HARDCODED messy stuff in here

if len(argv) > 1: # Get the expDate.log file from arguments
    expDate_log = argv[1]
else:
    expDate_log = "./expDate.log" # if not provided, assuming it is here

try: # Reading the log file
    with open(expDate_log, 'r') as log:
        expInfos = log.read().split("\n")
except FileNotFoundError:
    print("ERROR : Cannot found the expDate.log file")
    print("At location {}".format(expDate_log))
    exit(1)

expInfos = list(filter(None, expInfos)) # Remove empty lines if any
for i in range(len(expInfos)):
    expInfos[i] = expInfos[i].split(", ")

# Configuration (Very shitty and not generic for now)
# I assume there are two things in the log : autowareConfig file and oscExperiment file (I ignore the date info)
# For each of these things, I give the parameters it indicates ("param") and the corresponding value ("value")
# regarding the number following the name of the file
autowareConfig_param = {
    "param": "speed",
    "values": [3, 6, 8, 11]
}

oscName_param = {
    "param": "triggerDistance",
    "values": [i for i in range(10, 61, 10)]
}
# A more generic approach (but not cleaner) is to put these two dicts into another dict
# That associate a pattern to match with the information read in the log file (e.g a file name: "autowareConfig")

chdir("/home/adeye/.ros/log") # Going through ros logs
logFiles = []

# Get all the log folders
for dir in walk('.'):
    if dir[0] not in ['.', '..']:
        for fileName in dir[2]: # For each files in the folder (os.walk documentation)
            if 'collisiondetector' in fileName.lower(): # Selecting the collisionDetector log
                logFiles.append(dir[0] + '/' + fileName)
                break

# If it is not corresponding, something has to be done (manually) to
# make the number of lines of the expDate.log and the number of ros log folders both the same
if len(logFiles) != len(expInfos):
    print("ERROR: The number of log folder in ~/.ros ({}) doesn't match with the number " \
        "of expDate.log entries ({}).".format(len(logFiles), len(expInfos)))
    print("Please, manually remove the log folder that do not correspond to any of " \
        "experiments listed in the expDate.log file.")
    exit(1)

# Sort the collision logs by date
logFiles.sort(key = lambda x: stat(x).st_mtime)


# Reading the results
output = []

# I also assumes there are only two things in the expDate.log regardless of the date (not generic)
for i, exp in enumerate(expInfos):

    # Reading parameters
    oscNum = exp[1].lower().replace("kth_truck_osc", "").replace(".xosc", "")
    autowareConf = exp[2].lower().replace("autowareconfig", "").replace(".xlsx", "")
    autowareConf = int(autowareConf) -1
    oscNum = int(oscNum) -1

    param1 = autowareConfig_param["param"]
    val1 = autowareConfig_param["values"][autowareConf]
    param2 = oscName_param["param"]
    val2 = oscName_param["values"][oscNum]

    params = {param1: val1, param2: val2}

    # Reading the result
    with open(logFiles[i], "r") as f:
        data = f.read()

    if 'Collision detected' in data:
        data = data.split("\n")
        data = [d.split("]: ", 1)[-1] for d in data] # Removing the ros log beginning ("[INFO] [*big number stuff*]: ")
        # Getting position
        pos = data[2].replace("Position (x,y) = (", "").replace(")", "") # Removing useless chars
        pos = pos.split(", ")
        pos = float(pos[0]), float(pos[1])
        # Getting collision speed
        speed = data[3].replace("Car Velocity   = ", "")
        speed = float(speed[:-4]) # Also removing the color formatting chars

        #Storing results
        results = {"collision": True, "X" : pos[0], "Y": pos[1], "speed": speed}
    else:
        results = {"collision": False, "X" : 0, "Y": 0, "speed": 0}

    # Maybe the data needs to be stored in a better way
    output.append([params, results])

# Writing and displaying results
with open("./output", "w") as f:
    params = list(output[0][0].keys())
    results = list(output[0][1].keys())
    # Writing in a csv format
    # Column titles (not in the right order btw)
    line = ",".join(params + results)
    print(line)
    f.write(line)
    for out in output:
        line = ",".join([str(out[0][x]) for x in params] + [str(out[1][y]) for y in results])
        print(line)
        f.write(line + "\n")
