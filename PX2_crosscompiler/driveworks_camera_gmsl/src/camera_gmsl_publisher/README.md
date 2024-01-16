# Copyright (c) 2018, NVIDIA CORPORATION.  All rights reserved.

@page dwx_camera_gmsl_sample GMSL Camera Capture Sample
@tableofcontents

@section dwx_camera_gmsl_sample_description Description

The GMSL Camera Capture sample uses the GMSL camera interface, if available, on
NVIDIA DRIVE<sup>&trade;</sup> platforms. The sample opens a window
showing the input from the first camera on the selected CSI port.

@subsection dwx_camera_gmsl_sample_setup Setting Up The Cameras
For information about the physical location of the ports on NVIDIA DRIVE
platforms, see "Camera Setup under Configuration and Setup" in _NVIDIA DRIVE 5.0
Development Guide_. Please also see *Camera Setup* in *NVIDIA DRIVE 5.0 Linux PDK Development Guide*.

@note After running camera applications on Tegra A and before running on Tegra B (not slave), you must disable FRSYNC and the forward/reverse control channel of the Tegra A aggregator (see documents mentioned above). This is due to the fact that running camera applications on Tegra A re-enables the forward/reverse control channel and FRSYNC from MAX9286.

@section dwx_camera_gmsl_sample_running Running the sample

A camera must be connected to one of the NVIDIA DRIVE platform CSI ports.
The GMSL Camera Capture sample, sample_camera_gmsl, accepts the following parameters:

    ./sample_camera_gmsl --camera-type=[camera_type]
                         --camera-port=[a|c|e|g]
                         --write-file=[path/to/output/file]
                         --serializer-type=[h264|h265]
                         --serializer-bitrate=[integer]
                         --serializer-framerate=[integer]
                         --custom-board=[0|1]
                         --custom-config=[desAddr=0xNN,brdcstSerAddr=0xMM,i2cDevice=X]
                         --use-custom-ipp-callback=[0|1]
                         --tegra-slave=[0|1]

Where:

    --camera-type=[camera name]
        Specifies the name of the camera in use.
        Default value: ar0231-rccb-bae-sf3324

    --camera-port=[a|c|e|g]
        Specifies to which port the camera is connected.
        Default value: a

    --write-file=[path/to/output/file]
        Specifies the output file.
        If --write-file is not provided, no file is written out on disk.
        Default value: none

    --serializer-type=[h264|h265]
        Represents the format of the video with two possible options:
        h264 or uncompressed.
        Default value: h264

    --serializer-bitrate=[integer]
        Allows to override the bitrate of the recorded video.
        Note that an exact bitrate cannot be enforced, so the actual bitrate might
        differ from the proposed one.
        Default value: 8000000

    --serializer-framerate=[integer]
        Allows to override frame rate of the recorded video.
        Default value: 30

    --custom-board=[0|1]
        Specifies if it's a custom board, in which case a config-file must be specified. 
        The other options will be ignored.
        Default value: 0

    --custom-config=[desAddr=0xNN,brdcstSerAddr=0xMM,i2cDevice=X]
        File specifying the details of the custom board.
        For the specific values to use, refer to the documentation of the camera.
        This is only applicable if --custom-board=1.
        Default value: none

    --use-custom-ipp-callback=[0|1]
        Allows the custom defined callback function customNvMediaCallback() for NvMedia IPP 
        events handling (by default events are handled by the Camera module). 
        For details refer to the NvMedia Documentation.
        Default value: 0

    --tegra-slave=[0|1]
        Cameras can be captured on Tegra B in slave mode, i.e. when they are already captured
        by an application on Tegra A. In such case it is possible to specify the "tegra-slave" flag, 
        which can be 0 or 1. If slave is 1, then Tegra B will not be able to run cameras autonomously 
        but it requires that camera to run at the same time from Tegra A. If slave is false, 
        then Tegra B can control any camera that is not currently being used by Tegra A.
        Default value: 0

Screenshots can be captured by pressing **s** while the sample is running.

@note see @ref camera_mainsection_gmsl_supported_sensors for a complete list of supported sensors.

@section dwx_camera_gmsl_sample_examples Examples

#### Run on Tegra B in slave mode
Cameras can be captured on Tegra B in slave mode, i.e. when they are already captured by an application on Tegra A. In such case it is possible to specify the "tegra-slave" flag, which can be 0 or 1. If slave is 1, then Tegra B will not be able to run cameras autonomously but it requires that camera to run at the same time from Tegra A. If slave is false, then Tegra B can control any camera that is not currently being used by Tegra A.

    ./sample_camera_gmsl --camera-type=ar0231-rccb-bae-sf3324 --camera-port=c --tegra-slave=1

#### Run on custom board
It's possible to set addresses and other custom properties if the board is custom. In order to do so, the flag custom-board needs to be set to 1 and --custom-config needs to be set like the following way:

    ./sample_camera_gmsl --custom-board=1 --custom-config="desAddr=0x48,brdcstSerAddr=0x40,i2cDevice=7"

Currently, the parameters metioned in the templated are the only ones customizable through this feature.

@section dwx_camera_gmsl_sample_output Output

The sample creates a window and displays the input from the camera.

![Single OV10640 camera capturing](sample_camera_gmsl.png)

@section dwx_camera_gmsl_sample_more Additional information

For more details see @ref camera_mainsection .
