# This script is used to find which runs from test automation failed to ran.
# It outputs the runs that are missing in the recorded data.

import csv
import os



# individual parameter values
EGO_SPEEDS = [round(5.5 + 1.4 * i, 2) for i in range(0, 7)]
MAP = 2
GOALS_X = [ [] , [208,110,103] , [] ]
RAIN_INTENSITIES = [0.5, 1.5, 3.5, 7.5, 15, 40]
REFLECTIONS = [round(0.05 + 0.2 * i, 2) for i in range(0, 5)]


parameter_set = {} # contains all the parameters configurations of the set (four dimensional dictionary)

# initialize the counter for each parameter configuration
index = 0
for speed in EGO_SPEEDS:
    parameter_set[speed] = {}
    for goal_x in GOALS_X[MAP-1]:
        parameter_set[speed][goal_x] = {}
        for intensity in RAIN_INTENSITIES:
            parameter_set[speed][goal_x][intensity] = {}
            for reflectivity in REFLECTIONS:
                index += 1
                param_string = "Set speed, " + str(speed) + " , Set rain intensity, " + str(intensity) + " , Set reflectivity, " + str(reflectivity) + " , goal x," + str(goal_x)
                parameter_set[speed][goal_x][intensity][reflectivity] = [0, index]





# update the counters based on the recorded data
folder = "/home/adeye/Experiment_Results/ExperimentB"
files = os.listdir(folder)
for file in files:
    with open(folder+"/"+file, newline='') as csvfile:
    # with open('/home/adeye/Experiment_Results/ExperimentA.csv', newline='') as csvfile:
        reader = csv.reader(csvfile, delimiter=',')
        row = next(reader)
        # print(row)
        speed = round(float(row[1]), 2)
        intensity = round(float(row[3]), 2)
        reflectivity = round(float(row[5]), 2)
        goal_x = round(float(row[7]), 1)

        param_string = "Set speed, " + str(speed) + " , Set rain intensity, " + str(intensity) + " , Set reflectivity, " + str(reflectivity) + " , goal x," + str(goal_x)
        # print(param_string)
        parameter_set[speed][goal_x][intensity][reflectivity][0] += 1




# check which one are missing or present more than once
index = 0
for speed in EGO_SPEEDS:
    for goal_x in GOALS_X[MAP-1]:
        for intensity in RAIN_INTENSITIES:
            for reflectivity in REFLECTIONS:
                index += 1
                if parameter_set[speed][goal_x][intensity][reflectivity][0] != 1 and index >= 1 and index < 110:
                    run_string = "{:<15}".format("Run " + str(index)) + "{:<20}".format("Occurences " + str(parameter_set[speed][goal_x][intensity][reflectivity][0]))
                    param_string = "Set speed, " + str(speed) + " , Set rain intensity, " + str(intensity) + " , Set reflectivity, " + str(reflectivity) + " , goal x," + str(goal_x)
                    print(run_string + param_string)
