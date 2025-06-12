#!/usr/bin/env python3
"""
Tool to plot logs taken with the top tool. Collect logs by running:
'top -b -c -w 10000 -o "%CPU" > [path to log file]'
"""

import os
import argparse
import pandas as pd
import matplotlib.pyplot as plt

def file_to_lines(filename) -> list:
    """Open a given text file and split into single lines."""
    with open(filename) as file_handle:
        lines = file_handle.read().split("\n")
    return lines


def read_line(line: str, simple_names: bool = False) -> list:
    """Read and translate a single log line into a list."""

    words = line.split()

    if line.startswith("top -"):
        return ["NEWFRAME", words[2]]

    elif len(words) and words[0].isnumeric():
        pid = words[0]
        command = words[11]
        if "python" in command and len(words) > 12:
            command += " " + words[12]


        if simple_names and not command.startswith("["):
            if "python" in command:
                split_command = command.split(" ")
                split_path = split_command[1].split("/")
                command = split_command[0] + " " + split_path[-1]
            else:
                split_path = command.split("/")
                command = split_path[-1]

        cpu = float(words[8].replace(",","."))
        mem = float(words[9].replace(",","."))

        if cpu > 0.0 or mem > 0.0:
            return [pid, cpu, mem, command]

    return [""]

def timestr2seconds(time_str: str, start_time: str) -> float:
    """Converts a 'timestring' of format HH:MM:SS to just seconds relative to earlier starting time."""

    start_split = start_time.split(":")
    time_split = time_str.split(":")

    hours = (float(time_split[0]) - float(start_split[0])) % 24
    minutes = float(time_split[1]) - float(start_split[1])
    seconds = float(time_split[2]) - float(start_split[2])

    total_seconds = seconds + 60 * minutes + 3600 * hours
    return total_seconds

def log_to_dataframe(filename: str, simple_names: bool = False) -> pd.DataFrame:
    """Wrapper that opens a given text file and spits out a formatted DataFrame."""
    lines = file_to_lines(filename)

    start_time = ""
    current_time = 0.0
    total_trace = ["total", 0.0, 0.0]
    all_lists = []
    trace_list = {}
    pid_lut = {}

    for line in lines:
        out_list = read_line(line=line, simple_names=simple_names)
        if out_list[0] == "NEWFRAME":
            if start_time == "":
                start_time = out_list[1]
            else:
                all_lists.append([current_time] + total_trace)
                total_trace = ["total", 0.0, 0.0]
                current_time = timestr2seconds(out_list[1], start_time)


        elif out_list[0] != "":
            if out_list[0] not in trace_list:
                trace_list[out_list[0]] = 0.0
                pid_lut[out_list[0]] = out_list[3]
            trace_list[out_list[0]] += out_list[1]

            all_lists.append([current_time] + out_list[0:2])
            total_trace[1] += out_list[1]
            total_trace[2] += out_list[2]

    all_lists.append([current_time] + total_trace) # last frame total
    columns_list = ["frame", "pid", "cpu", "mem"]
    log_data_df = pd.DataFrame(data=all_lists, columns=columns_list)

    trace_list = sorted(trace_list.items(), reverse=True, key=lambda kv: kv[1])

    return log_data_df, trace_list, pid_lut


def plot_log_dataframe(filename: str, max_traces: int, plot_total: bool = False, simple_names: bool = False):
    """Plot points from dataframe."""

    log_data_df, all_traces, pid_lut = log_to_dataframe(filename=filename, simple_names=simple_names)

    fig, axs = plt.subplots(2,1)

    if plot_total:
        temp_df = log_data_df.loc[log_data_df["pid"] == "total"]
        x_axis = temp_df["frame"]
        y1_axis = temp_df["cpu"]
        axs[0].plot(x_axis, y1_axis, label="total")
        y2_axis = temp_df["mem"]
        axs[1].plot(x_axis, y2_axis, label="total")

    traces = 0
    for trace in all_traces:
        pid = trace[0]
        command = pid_lut[pid]
        temp_df = log_data_df.loc[log_data_df["pid"] == pid]
        x_axis = temp_df["frame"]
        y1_axis = temp_df["cpu"]
        axs[0].plot(x_axis, y1_axis, label=command)
        y2_axis = temp_df["mem"]
        axs[1].plot(x_axis, y2_axis, label=command)
        traces += 1
        if traces >= max_traces:
            break

    fig.suptitle(filename)
    axs[0].set_title("CPU usage")
    axs[0].set_xlabel("time (s)")
    axs[0].set_ylabel("percentage (1 CPU core equivalent)")
    axs[1].set_title("Memory usage")
    axs[1].set_xlabel("time (s)")
    axs[1].set_ylabel("percentage total")
    axs[1].legend(loc="upper right")

def plot_performance_logs_wrapper(args: argparse.Namespace):
    """Wrapper for plotting performance logs."""

    if args.folder == "":
        plot_log_dataframe(filename=args.filename,
                           max_traces=args.max_traces,
                           plot_total=args.plot_total,
                           simple_names=args.simple_names)
        plt.show()
    else:
        entries = os.scandir(args.folder)
        sorted_entries = sorted(entries, key=lambda entry: entry.name)

        for file in sorted_entries:
            if file.name.endswith(".log"):
                plot_log_dataframe(filename=file.path,
                                   max_traces=args.max_traces,
                                   plot_total=args.plot_total,
                                   simple_names=args.simple_names)
        plt.show()

if __name__ == "__main__":

    PARSER = argparse.ArgumentParser()

    PARSER.add_argument("-f", "--filename", type=str, required=True, help="Path to logfile to be read.")
    PARSER.add_argument("-F", "--folder", type=str, required=False, default="", help="Path to the folder containing multiple logs. Special case.")
    PARSER.add_argument("-m", "--max_traces", type=int, required=False, default=5, help="Amount of traces to plot per frame.")
    PARSER.add_argument("-t", "--plot_total", action="store_true", help="Also plot a trace for total cpu/mem load.")
    PARSER.add_argument("-s", "--simple_names", action="store_true", help="Simplify trace names by only showing the last part of path.")

    ARGS = PARSER.parse_args()

    plot_performance_logs_wrapper(ARGS)
