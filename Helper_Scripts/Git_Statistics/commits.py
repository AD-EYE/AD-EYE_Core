import matplotlib.pyplot as plt
import numpy as np

# This script generates graphs with data provided by gitstats files for each repository and then for the combined
# repositories

# Generation of the list of working repositories
repositories_names = ["AD-EYE_Core", "AD-EYE_GUI", "android_app", "AR_room", "getting_familiar_TCP",
                      "infrastructure_database", "Pex_Data_Extraction", "world_creation"]


def GenerateDateStringList():
    commit_data_file = open("/home/adeye/Stats_results/AD-EYE_Core_stats/commits_by_year_month.dat", 'r')
    file_lines = commit_data_file.readlines()
    result_dates = []
    last_line = file_lines[len(file_lines) - 1]
    last_date = last_line.split()[0]
    last_year = int(last_date[0:4])
    print("Last year: " + str(last_year))
    # To use integer we have to remove 0 in month numbers which are before october, because the format is a 2
    # characters string
    if last_date[5] == '0':
        last_month = int(last_date[6])
    else:
        last_month = int(last_date[5:7])

    # For months after october the format is already good so we had the integer as a 2 characters string
    # We start at 2018-10 because it is the oldest date of the whole project (in Pex_Data_Extraction)
    for month in range(10, 13):
        result_dates.append('2018-' + str(month))
    for year in range(2019, last_year + 1):
        # For months before october, we have to add a 0 string to respect the format of the dates
        for month in range(1, 10):
            result_dates.append(str(year) + '-0' + str(month))
        for month in range(10, 13):
            result_dates.append(str(year) + '-' + str(month))
    # We still have to separate the cases where the month number is 1 character and the cases where it is 2 characters
    if last_date[5] == '0':
        for month in range(1, last_month + 1):
            result_dates.append(str(last_year) + '-0' + str(month))
    else:
        for month in range(1, 10):
            result_dates.append(str(year) + '-0' + str(month))
        for month in range(10, last_month + 1):
            result_dates.append(str(year) + '-' + str(month))
    return result_dates


# Creation of a common dates list for combined graphs which starts from the oldest date and finish at the current month
dates_strings = GenerateDateStringList()

# Creation of variables for combined repositories graphs
# time is a list of the indexes to match graph legend with the dates
combined_values, time = [0 for k in range(len(dates_strings))], [k for k in range(len(dates_strings))]
nb_commits_per_date = [0 for k in range(len(dates_strings))]


def plot_and_save_accumulated_commits(dates, x_legend_strings, number_of_commits, repo_name):
    plt.xticks(dates, x_legend_strings, rotation=60)
    plt.plot(dates, number_of_commits)
    plt.title(repo_name + "_Accumulated commits over time")
    plt.subplots_adjust(bottom=0.15)
    plt.savefig("/home/adeye/Stats_results/Graphs/" + repo_name + "_accumulated_commits.png")
    plt.clf()


def plot_and_save_non_accumulated_commits(dates, x_legend_strings, hist_values, repo_name):
    plt.xticks(dates, x_legend_strings, rotation=60)
    plt.hist(hist_values, bins=range(len(dates) + 1))
    plt.title(repo_name + "_Non-accumulated commits")
    plt.subplots_adjust(bottom=0.15)
    plt.savefig("/home/adeye/Stats_results/Graphs/" + repo_name + "_non_accumulated_commits.png")
    plt.clf()

## smoothing by taking a moving avarage of three
## special case for the first and third element and if there is less than one element
def averageThree(values):
    if(len(values) <= 1):
        return values
    result = []
    for(i in range(len(values))):
        if(i == 0):
            results.append((values[i] + values[i + 1]) / 3)
        elif(i == len(values) - 1):
            results.append((values[i - 1] + values[1]) / 3)
        else:
            
            results.append((values[i - 1] + values[1] + values[i + 1]) / 3)
    return results
        
# Because of the way to make a histogram with Python, hist_values is a list where each index of date appears as
# many times as there were commits in that month
def valuesToIndices(values):
    hist = []
    for(i in range(len(values))):
        for(j in range(len(values(i)))):
            hist.append(i)
    return hist

# Extraction of data from generated text files
for repo_name in repositories_names:
    # Initialisation of variables for each repository
    date_value_strings = []
    # x_legend_strings is a list of the dates in a string type to add them as the legend of the graph
    date_indices, cumulated_number_of_commits, x_legend_strings = [], [], []
    hist_values = []
    path = "/home/adeye/Stats_results/" + repo_name + "_stats/commits_by_year_month.dat"
    commit_data_file = open(path, 'r')
    file_lines = commit_data_file.readlines()
    commit_per_month = []

    # date_indices is a list of the indexes and cumulated_number_of_commits is a list of the date_value_strings
    for line_index in range(len(file_lines)):
        date_value_strings.append(file_lines[line_index].split())
        date_indices.append(line_index)
        x_legend_strings.append(date_value_strings[line_index][0])
        
        commits_per_month.append(date_value_strings[line_index][1])
            
        if line_index == 0:
            cumulated_number_of_commits.append(int(date_value_strings[line_index][1]))
        else:
            cumulated_number_of_commits.append(
                cumulated_number_of_commits[line_index - 1] + int(date_value_strings[line_index][1]))
        # nb_commits_per_date has the same format as hist_values but for all the repositories combined
        found = False
        for i in range(len(dates_strings)):
            if x_legend_strings[line_index] == dates_strings[i]:
                found = True
                nb_commits_per_date[i] += int(date_value_strings[line_index][1])
        if not found:
            print("not found" + x_legend_strings[line_index])

    hist_values = valuesToIndices(averageThree(commit_per_month))

    # Generation of the graphs for each repository
    if len(date_value_strings) != 1:
        plot_and_save_accumulated_commits(date_indices, x_legend_strings, cumulated_number_of_commits, repo_name)
    plot_and_save_non_accumulated_commits(date_indices, x_legend_strings, hist_values, repo_name)

# Generation of the combined repositories graphs
commits_indices = []

# For both configurations graphs date_value_strings are histogram date_value_strings accumulated over time
combined_values[0] = nb_commits_per_date[0]
for k in range(1, len(nb_commits_per_date)):
    combined_values[k] = combined_values[k - 1] + nb_commits_per_date[k]

for j in range(len(nb_commits_per_date)):
    for l in range(nb_commits_per_date[j]):
        commits_indices.append(time[j])

dates = np.array(time)
number_of_commits = np.array(combined_values)

plot_and_save_accumulated_commits(dates, dates_strings, number_of_commits, "AD-EYE_repos_combined")
plot_and_save_non_accumulated_commits(dates, dates_strings, commits_indices, "AD-EYE_repos_combined")
