import matplotlib.pyplot as plt
import numpy as np

#This script generates graphs with data provided by gitstats files for each repository and then for the combined repositories
#AD-EYE_Core

#Generation of the list of working repositories
repositories_names = ["AD-EYE_Core","AD-EYE_GUI","android_app","AR_room","getting_familiar_TCP","infrastructure_database","Pex_Data_Extraction","world_creation"]
#Creation of a common dates list for combined graphs which starts from the oldest date and finish at the current month
all_dates = []
commit_data_file = open("/home/adeye/Stats_results/AD-EYE_Core_stats/commits_by_year_month.dat",'r')
file_lines = commit_data_file.readlines()
last_line = file_lines [len(file_lines)-1]
last_date = last_line.split()[0]
last_year = int(last_date[0:4])

def GenerateDataList():
    #To use integer we have to remove 0 in month numbers which are before october, because the format is a 2 characters string
    if last_date[5] == '0':
        last_month = int(last_date[6])
    else:
        last_month = int(last_date[5:7])

    #For months after october the format is already good so we had the integer as a 2 characters string
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
    return(all_dates)

all_dates = GenerateDataList()

#Creation of variables for combined repositories graphs
#time is a list of the indexes to make graph legend match with the dates
combined_values, time = [0 for k in range (len(all_dates))],[k for k in range (len(all_dates))]
nb_commits_per_date = [0 for k in range (len(all_dates))]

#Extraction of datas from generated text files
for index in range (len(repositories_names)) :
    #Initialisation of variables for each repository
    date_value_strings=[]
    #x_legend_strings is a list of the dates in a string type to add them as the legend of the graph
    date_indices,cumulated_number_of_commits,x_legend_strings = [],[],[]
    hist_values = []
    path = "/home/adeye/Stats_results/"+repositories_names[index]+"_stats/commits_by_year_month.dat"
    commit_data_file = open(path,'r')
    file_lines = commit_data_file.readlines()

#date_indices is a list of the indexes and cumulated_number_of_commits is a list of the date_value_strings
    for text_element in file_lines:
        date_value_strings.append(text_element.split())
    #First value must be added separately
    date_indices.append(0)
    x_legend_strings.append(date_value_strings[0][0])
    cumulated_number_of_commits.append(int(date_value_strings[0][1]))
    
    # Because of the way to make a histogram with Python, hist_values is a list where each index of date appears as many times as there were commits in that month
    for j in range (int(date_value_strings[0][1])):
        hist_values.append(0)
    for i in range (1,len(date_value_strings)):
        date_indices.append(i)
        x_legend_strings.append(date_value_strings[i][0])
        cumulated_number_of_commits.append(cumulated_number_of_commits[i-1]+int(date_value_strings[i][1]))
        for j in range (int(date_value_strings[i][1])):
            hist_values.append(i)
    # nb_commits_per_date has the same format as hist_values but for all the repositories combined    
    for i in range(len(all_dates)):
        for j in range (len(x_legend_strings)):
            if x_legend_strings[j]==all_dates[i]:
                nb_commits_per_date[i]+=int(date_value_strings[j][1])

    #Generation of the graphs for each repository
    dates = np.array(date_indices)
    number_of_commits = np.array(cumulated_number_of_commits)
    if len(date_value_strings)!= 1:
        plt.xticks(dates,x_legend_strings,rotation=60)
        plt.plot(dates,number_of_commits)
        plt.title(repositories_names[index]+"_Accumulated commits over time")
        plt.subplots_adjust(bottom=0.15)
        plt.savefig("/home/adeye/Stats_results/Graphs/"+repositories_names[index]+"_accumulated_commits.png")
        plt.clf()
    plt.xticks(dates,x_legend_strings,rotation=60)
    plt.hist(hist_values,bins=range(len(dates)+1))
    plt.title(repositories_names[index]+"_Non-accumulated commits")
    plt.subplots_adjust(bottom=0.15)
    plt.savefig("/home/adeye/Stats_results/Graphs/"+repositories_names[index]+"_non_accumulated_commits.png")
    plt.clf()

#Generation of the combined repositories graphs
commits_indices = []

#For both configurations graphs date_value_strings are histogram date_value_strings accumulated over time
combined_values[0]=nb_commits_per_date[0]
for k in range (1,len(nb_commits_per_date)):
    combined_values[k]=combined_values[k-1]+nb_commits_per_date[k]
  
for j in range (len(nb_commits_per_date)):
    for l in range (nb_commits_per_date[j]):
        commits_indices.append(time[j])

dates = np.array(time)
number_of_commits = np.array(combined_values)
plt.xticks(dates,all_dates,rotation=60)
plt.plot(dates,number_of_commits)
plt.title("Combined accumulated commits over time")
plt.subplots_adjust(bottom=0.15)
plt.savefig("/home/adeye/Stats_results/Graphs/combined_accumulated_commits.png")
plt.clf()
plt.xticks(dates,all_dates,rotation=60)
plt.hist(commits_indices,bins=range(len(all_dates)+1))
plt.title("Combined non-accumulated commits over time")
plt.subplots_adjust(bottom=0.15)
plt.savefig("/home/adeye/Stats_results/Graphs/combined_non_accumulated_commits.png")
plt.clf()
