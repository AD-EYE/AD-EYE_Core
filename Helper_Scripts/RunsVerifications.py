# This script is used to find which runs from test automation failed to ran.
# It outputs the runs that are missing in the recorded data.

import csv



# individual parameter values
RAIN_INTENSITIES = [1, 5, 8, 10, 12, 15, 20, 30, 40]
REFLECTIONS = [round(0.2 * i, 2) for i in range(1, 6)]
TRIGGER_DISTANCES = [round(20 + 5 * i, 2) for i in range(0, 5)]
EGO_SPEEDS = [round(8.8889 + 0.5555 * i, 2) for i in range(0, 7)]


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


print(index)

# update the counters based on the recorded data
with open('/home/adeye/Downloads/ExperimentA_it1.csv', newline='') as csvfile:
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
                if parameter_set[trigger_ditance][speed][intensity][reflectivity][0] != 1 and index >= 1 and index <= 1575:
                    run_string = "{:<15}".format("Run " + str(index)) + "{:<20}".format("Occurences " + str(parameter_set[trigger_ditance][speed][intensity][reflectivity][0]))
                    param_string = "Set speed, " + str(speed) + " , Set rain intensity, " + str(intensity) + " , Set reflectivity, " + str(reflectivity) + " , Set trigger distance, "+str(trigger_ditance)
                    print(run_string + param_string)
