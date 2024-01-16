

    ./camera_gmsl_publisher --camera-type=[camera_type]
                         --camera-port=[a|c|e|g]
                         --custom-board=[0|1]
                         --custom-config=[desAddr=0xNN,brdcstSerAddr=0xMM,i2cDevice=X]
                         --tegra-slave=[0|1]

Where:

    --camera-type=[camera name]
        Specifies the name of the camera in use.
        Default value: ar0231-rccb-bae-sf3324

    --camera-port=[a|c|e|g]
        Specifies to which port the camera is connected.
        Default value: a

    --custom-board=[0|1]
        Specifies if it's a custom board, in which case a config-file must be specified. 
        The other options will be ignored.
        Default value: 0

    --custom-config=[desAddr=0xNN,brdcstSerAddr=0xMM,i2cDevice=X]
        File specifying the details of the custom board.
        For the specific values to use, refer to the documentation of the camera.
        This is only applicable if --custom-board=1.
        Default value: none

    --tegra-slave=[0|1]
        Cameras can be captured on Tegra B in slave mode, i.e. when they are already captured
        by an application on Tegra A. In such case it is possible to specify the "tegra-slave" flag, 
        which can be 0 or 1. If slave is 1, then Tegra B will not be able to run cameras autonomously 
        but it requires that camera to run at the same time from Tegra A. If slave is false, 
        then Tegra B can control any camera that is not currently being used by Tegra A.
        Default value: 0


#### Run on Tegra B in slave mode
Cameras can be captured on Tegra B in slave mode, i.e. when they are already captured by an application on Tegra A. In such case it is possible to specify the "tegra-slave" flag, which can be 0 or 1. If slave is 1, then Tegra B will not be able to run cameras autonomously but it requires that camera to run at the same time from Tegra A. If slave is false, then Tegra B can control any camera that is not currently being used by Tegra A.

    ./camera_gmsl_publisher --camera-type=ar0231-rccb-bae-sf3324 --camera-port=c --tegra-slave=1

#### Run on custom board
It's possible to set addresses and other custom properties if the board is custom. In order to do so, the flag custom-board needs to be set to 1 and --custom-config needs to be set like the following way:

    ./camera_gmsl_publisher --custom-board=1 --custom-config="desAddr=0x48,brdcstSerAddr=0x40,i2cDevice=7"

Currently, the parameters metioned in the templated are the only ones customizable through this feature.



