import matplotlib.pyplot as plt
import numpy as np

#This script generates graphs with data provided by gitstats files for each repository and then for the combined repositories
#AD-EYE_Core

#Generation of the list of working repositories
repositories_names = ["AD-EYE_Core","AD-EYE_GUI","android_app","AR_room","getting_familiar_TCP","infrastructure_database","Pex_Data_Extraction","world_creation"]
#Creation of a common dates list for combined graphs which starts from the oldest date and finish at current month
all_dates = []
text_file = open("/home/adeye/Stats_results/AD-EYE_Core_stats/commits_by_year_month.dat",'r')
file_data = text_file.readlines()
last_line = file_data [len(file_data)-1]
last_date = last_line.split()[0]
last_year = int(last_date[0:4])

#To use integer we have to remove 0 in month numbers which are before october, because format is a 2 characters string
if last_date[5] == '0':
    last_month = int(last_date[6])
else:
    last_month = int(last_date[5:7])

#For month after october the format is already good so we had the integer as a 2 characters string
#We start at 2018-10 because it is the oldest date of the whole project (in Pex_Data_Extraction)
for month in range (10,13):
    all_dates.append('2018-'+str(month))
for year in range (2019,last_year):
    #For months before october, we have to add a 0 string to respect the format of the dates
    for month in range (1,10):
        all_dates.append(str(year)+'-0'+str(month))
    for month in range (10,13):
        all_dates.append(str(year)+'-'+str(month))
#We still have to separate the cases where the month number is 1 character and the cases where it is 2 characters
if last_date[5] == '0':
    for month in range (1,last_month+1):
        all_dates.append(str(last_year)+'-0'+str(month))
else:
    for month in range (1,10):
        all_dates.append(str(year)+'-0'+str(month))
    for month in range (10,last_month+1):
        all_dates.append(str(year)+'-'+str(month))

#Creation of variables for combined repositories graphs
#time is a list of the indexes for 
combined_values, time = [0 for k in range (len(all_dates))],[k for k in range (len(all_dates))]
combined_hist_values,final_hist = [0 for k in range (len(all_dates))],[]

#Extraction of datas from generated text files
for index in range (len(repositories_names)) :
    #Initialisation of variables for each repository
    values=[]
    #my_xticks is list of the dates in a string type to add them as legend of the graph
    X,Y,my_xticks = [],[],[]
    hist_values = []
    path = "/home/adeye/Stats_results/"+repositories_names[index]+"_stats/commits_by_year_month.dat"
    text_file = open(path,'r')
    file_data = text_file.readlines()

#X is a list of the indexes and Y is a list of the values
    for text_element in file_data:
        values.append(text_element.split())
    #First value must be added separately
    X.append(0)
    my_xticks.append(values[0][0])
    Y.append(int(values[0][1]))
    
    # Because of the way to make an histogram with Python, hist_values is a list where each index of a date appears as many time as there were commits in that month
    for j in range (int(values[0][1])):
        hist_values.append(0)
    for i in range (1,len(values)):
        X.append(i)
        my_xticks.append(values[i][0])
        Y.append(Y[i-1]+int(values[i][1]))
        for j in range (int(values[i][1])):
            hist_values.append(i)
    # combined_hist_values has the same format as hist_values but for all the repositories combined    
    for i in range(len(all_dates)):
        for j in range (len(my_xticks)):
            if my_xticks[j]==all_dates[i]:
                combined_hist_values[i]+=int(values[j][1])

    #Generation of the graphs for each repository
    dates = np.array(X)
    number_of_commits = np.array(Y)
    if len(values)!= 1:
        plt.xticks(dates,my_xticks,rotation=60)
        plt.plot(dates,number_of_commits)
        plt.title(repositories_names[index]+"_Accumulated commits over time")
        plt.subplots_adjust(bottom=0.15)
        plt.savefig("/home/adeye/Stats_results/Graphs/"+repositories_names[index]+"_accumulated_commits.png")
        plt.clf()
    plt.xticks(dates,my_xticks,rotation=60)
    plt.hist(hist_values,bins=range(len(dates)+1))
    plt.title(repositories_names[index]+"_Non-accumulated commits")
    plt.subplots_adjust(bottom=0.15)
    plt.savefig("/home/adeye/Stats_results/Graphs/"+repositories_names[index]+"_non_accumulated_commits.png")
    plt.clf()

#Generation of the combined repositories graphs
#For both configurations graphs values are histogram values accumulated over time
combined_values[0]=combined_hist_values[0]
for k in range (1,len(combined_hist_values)):
    combined_values[k]=combined_values[k-1]+combined_hist_values[k]
  
for j in range (len(combined_hist_values)):
    for l in range (combined_hist_values[j]):
        final_hist.append(time[j])

dates = np.array(time)
number_of_commits = np.array(combined_values)
plt.xticks(dates,all_dates,rotation=60)
plt.plot(dates,number_of_commits)
plt.title("Combined accumulated commits over time")
plt.subplots_adjust(bottom=0.15)
plt.savefig("/home/adeye/Stats_results/Graphs/combined_accumulated_commits.png")
plt.clf()
plt.xticks(dates,all_dates,rotation=60)
plt.hist(final_hist,bins=range(len(all_dates)+1))
plt.title("Combined non-accumulated commits over time")
plt.subplots_adjust(bottom=0.15)
plt.savefig("/home/adeye/Stats_results/Graphs/combined_non_accumulated_commits.png")
plt.clf()
