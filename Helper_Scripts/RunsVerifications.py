# This script is used to find which runs from test automation failed to ran.
# It outputs the runs that are missing in the recorded data.

import csv



# individual parameter values
RAIN_INTENSITIES = [0.5, 1.5, 3.5, 7.5, 15, 40]
REFLECTIONS = [round(0.05 * i, 2) for i in range(1, 20)]
TRIGGER_DISTANCES = [round(20 + 2 * i, 2) for i in range(0, 11)]
EGO_SPEEDS = [round(5.5 + 0.56 * i, 2) for i in range(0, 6)]


parameter_set = {} # contains all the parameters configurations of the set (four dimensional dictionary)

# initialize the counter for each parameter configuration
index = 0
for trigger_ditance in TRIGGER_DISTANCES:
    parameter_set[trigger_ditance] = {}
    for speed in EGO_SPEEDS:
        parameter_set[trigger_ditance][speed] = {}
        for intensity in RAIN_INTENSITIES:
            parameter_set[trigger_ditance][speed][intensity] = {}
            for reflectivity in REFLECTIONS:
                index += 1
                param_string = str(trigger_ditance) + ", " + str(speed) + ", " + str(intensity) + ", " + str(reflectivity)
                parameter_set[trigger_ditance][speed][intensity][reflectivity] = [0, index]





# update the counters based on the recorded data
with open('Experiment_Results/ExperimentA.csv', newline='') as csvfile:
    reader = csv.reader(csvfile, delimiter=',')
    for row in reader:
        # print(row)
        speed = round(float(row[1]), 2)
        intensity = round(float(row[3]), 2)
        reflectivity = round(float(row[5]), 2)
        distance = round(float(row[7]), 2)
        parameter_set[distance][speed][intensity][reflectivity][0] += 1




index = 0
# check which one are missing or present more than once
for trigger_ditance in TRIGGER_DISTANCES:
    for speed in EGO_SPEEDS:
        for intensity in RAIN_INTENSITIES:
            for reflectivity in REFLECTIONS:
                index += 1
                if parameter_set[trigger_ditance][speed][intensity][reflectivity][0] != 1 and index < 1500:
                    param_string = "Run " + str(index) + ",   Set speed, " + str(speed) + " , Set rain intensity, " + str(intensity) + " , Set reflectivity, " + str(reflectivity) + " , Set trigger distance, "+str(trigger_ditance)
                    print(param_string)
