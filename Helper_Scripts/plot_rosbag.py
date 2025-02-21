#!/usr/bin/env python3
"""Plots data from rosbag for given keywords."""

import argparse
import yaml
import pandas as pd
import matplotlib.pyplot as plt

def rosbag_to_df(filename) -> pd.DataFrame:
    """Convert a rosbag txt to a DataFrame."""

    dict_list = []
    with open(filename) as stream:
        yaml_stream = yaml.safe_load_all(stream)
        while True:
            single_dict = next(yaml_stream)
            if single_dict is None:
                break
            else:
                dict_list.append(single_dict)

    rosbag_df = pd.DataFrame(dict_list)
    return rosbag_df

def plot_df(rosbag_df: pd.DataFrame, y_axes: list, x_axes: list = []):
    """Plot given DataFrame."""
    _fig, axs = plt.subplots(len(y_axes),1)

    for idx, y_key in enumerate(y_axes):
        if len(x_axes) == len(y_axes):
            x_axis = rosbag_df[x_axes[idx]]
        elif len(x_axes) == 1:
            x_axis = rosbag_df[x_axes[0]]
        else:
            x_axis = rosbag_df.index

        axs[idx].plot(x_axis, rosbag_df[y_key], label=y_key)
        axs[idx].legend()

    plt.show()




def unpack_and_plot_df(args: argparse.Namespace):
    """Wrapper to unpack and plot a rosbag."""
    rosbag_df = rosbag_to_df(filename=args.filename)
    plot_df(rosbag_df=rosbag_df, y_axes=args.y_axes, x_axes=args.x_axes, )

if __name__ == "__main__":

    PARSER = argparse.ArgumentParser()

    PARSER.add_argument("-f", "--filename", type=str, required=True, help="Path to logfile to be read.")
    PARSER.add_argument("-y", "--y_axes", nargs="+", required=True, help="Categories to plot on the y axis.")
    PARSER.add_argument("-x", "--x_axes", nargs="+", required=False, default=[], help="Categories to plot on the x axis.")

    ARGS = PARSER.parse_args()

    unpack_and_plot_df(ARGS)