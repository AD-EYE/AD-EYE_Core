import matplotlib.pyplot as plt
import numpy as np

#This script generates graphs with data provided by gitstats files for each repository and then for the combined repositories
#AD-EYE_Core

#Generation of variables for working repositories
repositories_names = ["AD-EYE_Core","AD-EYE_GUI","android_app","AR_room","getting_familiar_TCP","infrastructure_database","Pex_Data_Extraction","world_creation"]

#Creation of dates list for combined graphs
all_dates = []
textfile = open("/home/adeye/Stats_results/AD-EYE_Core_stats/commits_by_year_month.dat",'r')
file_data = textfile.readlines()
last_line = file_data [len(file_data)-1]
last_date = last_line.split()[0]
last_year = int(last_date[0:4])

if last_date[5] == '0':
    last_month = int(last_date[6])
else:
    last_month = int(last_date[5:7])

for month in range (10,13):
    all_dates.append('2018-'+str(month))
for year in range (2019,last_year):
    for month in range (1,10):
        all_dates.append(str(year)+'-0'+str(month))
    for month in range (10,13):
        all_dates.append(str(year)+'-'+str(month))
if last_date[5] == '0':
    for month in range (1,last_month+1):
        all_dates.append(str(last_year)+'-0'+str(month))
else:
    for month in range (1,10):
        all_dates.append(str(year)+'-0'+str(month))
    for month in range (10,last_month+1):
        all_dates.append(str(year)+'-'+str(month))

#Creation of variables for combined graphs
combined_values, time = [0 for k in range (len(all_dates))],[k for k in range (len(all_dates))]
combined_hist_values,final_hist = [0 for k in range (len(all_dates))],[]

#Extraction of datas from generated text file
for index in range (len(repositories_names)) :
    #Initialisation of variables for each repository
    values=[]
    X,Y,my_xticks = [],[],[]
    hist_values = []
    path = "/home/adeye/Stats_results/"+repositories_names[index]+"_stats/commits_by_year_month.dat"
    textfile = open(path,'r')
    file_data = textfile.readlines()

    for text_element in file_data:
        values.append(text_element.split())
    for i in range (len(values)):
        if i==0:
            X.append(i)
            my_xticks.append(values[i][0])
            Y.append(int(values[i][1]))
            for j in range (int(values[i][1])):
                hist_values.append(i)
        else:
            X.append(i)
            my_xticks.append(values[i][0])
            Y.append(Y[i-1]+int(values[i][1]))
            for j in range (int(values[i][1])):
                hist_values.append(i)
        
    for i in range(len(all_dates)):
        for j in range (len(my_xticks)):
            if my_xticks[j]==all_dates[i]:
                combined_hist_values[i]+=Y[j]

    #Generation of the graphs for each repository
    dates = np.array(X)
    number_of_commits = np.array(Y)
    plt.xticks(dates,my_xticks,rotation=45)
    plt.plot(dates,number_of_commits)
    plt.title(repositories_names[index]+"_Accumulated commits over time")
    plt.savefig("/home/adeye/Stats_results/Graphs/"+repositories_names[index]+"_accumulated_commits.png")
    plt.clf()
    plt.xticks(dates,my_xticks,rotation=45)
    plt.hist(hist_values)
    plt.title(repositories_names[index]+"_Non-accumulated commits")
    plt.savefig("/home/adeye/Stats_results/Graphs/"+repositories_names[index]+"_non_accumulated_commits.png")
    plt.clf()

#Generation of the combined graphs
for k in range (len(combined_hist_values)):
    if k==0:
        combined_values[k]=combined_hist_values[k]
    else:
        combined_values[k]=combined_values[k-1]+combined_hist_values[k]
  
for j in range (len(combined_hist_values)):
    for l in range (combined_hist_values[j]):
        final_hist.append(time[j])

dates = np.array(time)
number_of_commits = np.array(combined_values)
plt.xticks(dates,all_dates,rotation=60)
plt.plot(dates,number_of_commits)
plt.title("Combined accumulated commits over time")
plt.savefig("/home/adeye/Stats_results/Graphs/combined_accumulated_commits.png")
plt.clf()
plt.xticks(dates,all_dates,rotation=45)
plt.hist(final_hist)
plt.title("Combined non-accumulated commits over time")
plt.savefig("/home/adeye/Stats_results/Graphs/combined_non_accumulated_commits.png")
plt.clf()