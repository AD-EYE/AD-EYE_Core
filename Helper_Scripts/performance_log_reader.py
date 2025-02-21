#!/usr/bin/env python3
"""
Tool to plot logs taken with the top tool. Collect logs by running:
'top -b -c -w 10000 > [path to log file]'
"""

import argparse
import pandas as pd
import matplotlib.pyplot as plt

def file_to_lines(filename) -> list:
    """Open a given text file and split into single lines."""
    with open(filename) as file_handle:
        lines = file_handle.read().split("\n")
    return lines


def read_line(line: str) -> list:
    """Read and translate a single log line into a list."""
    words = line.split()
    if len(words):
        if words[0] == "PID":
            return ["NEWFRAME"]

        elif words[0].isnumeric():
            command = words[11]
            cpu = float(words[8].replace(",","."))
            mem = float(words[9].replace(",","."))

            if cpu > 0.0:
                return [command, cpu, mem]

    return [""]


def log_to_dataframe(filename: str, max_traces: int = 5, plot_total: bool = False, plot_rest: bool = False) -> pd.DataFrame:
    """Wrapper that opens a given text file and spits out a formatted DataFrame."""
    lines = file_to_lines(filename)

    frame = -1
    traces_count = 0
    rest_trace = ["other", 0.0, 0.0]
    total_trace = ["total", 0.0, 0.0]
    all_lists = []

    for line in lines:
        out_list = read_line(line)

        if out_list[0] == "NEWFRAME":
            frame += 1
            traces_count = 0

            if plot_total:
                all_lists.append([frame] + total_trace)
                total_trace = ["total", 0.0, 0.0]

            if plot_rest:
                all_lists.append([frame] + rest_trace)
                rest_trace = ["other", 0.0, 0.0]

        elif out_list[0] != "":
            total_trace[1] += out_list[1]
            total_trace[2] += out_list[2]
            if traces_count < max_traces:
                traces_count += 1
                all_lists.append([frame] + out_list)
            else:
                rest_trace[1] += out_list[1]
                rest_trace[2] += out_list[2]

    columns_list = ["frame", "command", "cpu", "mem"]
    log_data_df = pd.DataFrame(data=all_lists, columns=columns_list)

    print("Number of frames: ", frame)

    return log_data_df

def plot_log_dataframe(args: argparse.Namespace):
    """Plot points from dataframe."""

    log_data_df = log_to_dataframe(filename=args.filename,
                                   max_traces=args.max_traces,
                                   plot_total=args.plot_total,
                                   plot_rest=args.plot_rest)

    _fig, axs = plt.subplots(2,1)

    all_commands = log_data_df["command"].unique()
    for command in all_commands:
        temp_df = log_data_df.loc[log_data_df["command"] == command]
        x_axis = temp_df["frame"]
        y1_axis = temp_df["cpu"]
        axs[0].plot(x_axis, y1_axis, label=command)
        y2_axis = temp_df["mem"]
        axs[1].plot(x_axis, y2_axis, label=command)

    #TODO: make the legends show up in a nicer spot so they don't block the graphs...
    axs[0].legend()
    axs[1].legend()
    plt.show()


if __name__ == "__main__":

    PARSER = argparse.ArgumentParser()

    PARSER.add_argument("-f", "--filename", type=str, required=True, help="Path to logfile to be read.")
    PARSER.add_argument("-m", "--max_traces", type=int, required=False, default=5, help="Amount of traces to plot per frame.")
    PARSER.add_argument("-t", "--plot_total", action="store_true", help="Also plot a trace for total cpu/mem load.")
    PARSER.add_argument("-r", "--plot_rest", action="store_true", help="Also plot a trace for the sum of other cpu/mem load.")

    ARGS = PARSER.parse_args()

    plot_log_dataframe(ARGS)
