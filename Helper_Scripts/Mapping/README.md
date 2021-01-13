This script automates the process of generating pcd maps from rosbags.
To do so, it runs ndt_mapping.

The script can be called with the following arguments:

| Argument | Description |
| -- | -- |
| `--rosbag-folder` | Path to the folder containing the rosbag files |
| `--output-dir` | Path to PCD output directory |

One limitation concerning ROS (messages must be less than 1GB) and ndt_mapping implementation (the map is published as a message) mean that if the rosbag is too big the process will fail.