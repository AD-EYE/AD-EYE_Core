# Copyright (c) 2018, NVIDIA CORPORATION.  All rights reserved.

@page dwx_canbus_logger_sample CAN Bus Message Logger Sample
@tableofcontents

@section dwx_canbus_logger_sample_description Description

The CAN Bus Message Logger sample is a simple CAN bus listener sample. All
messages received over the CAN bus are printed on the console. A valid SocketCAN
@if PX2_ONLY
or AurixCAN
@endif
device must be present in the system. Please refer to your platform datasheet for
a description of the available CAN devices and the corresponding connectors.

@section dwx_canbus_logger_sample_running Running the sample

The CAN Bus Message Logger sample, sample_canbus_logger, accepts the following parameters:

    ./sample_canbus_logger --driver=[can.virtual|can.socket|can.aurix]
                           --params=[comma/separated/key/value/pairs]
                           --filter=[id1:mask1,id2:mask2,..]
                           --hwtime=[0|1]
                           --send_i_understand_implications=[timeout]
                           --send_id=[message_ID]

Where:

    --driver=[can.virtual|can.socket|can.aurix]
        Allows to specify which CAN interface to use.
        Default value: can.virtual

    --params=[comma/separated/key/value/pairs]
        Different parameters are available for each CAN driver.
        Default value: file=path/to/data/samples/sfm/triangulation/canbus.can

    --filter=[id1:mask1,id2:mask2,..]
        The sample provides support to filter (i.e., pass) messages of certain IDs. A
        filter can be specified  by adding comma separated `id:mask` values to the
        `--filter=` argument. A message is considered passing if `<received_can_id> &
        mask == id & mask`.
        Example 1 - pass all messages between 201-2FF: `--filter=200:F00`
        Example 2 - pass only 100,110 and 301-31F: `--filter=100:FFF,110:FFF,300:FE0`
        Default value: 000:000

    --hwtime=[0|1]
        DriveWorks supports hardware timestamps of the CAN messages. Tegra provides a hardware-based counter
        timestamps all CAN messages on arrival directly on the SoC. For the case of AurixCAN,
        the messages are timestamped by Aurix on arrival and passed together with the CAN messages over UDP
        to DriveWorks. In order for hardware timestamps to work for SocketCAN, the application must run with
        root rights.
        Default value: 1

    --send_i_understand_implications=[timeout]
        Allows to generate a random CAN message each timeout ms
        Note that sending might interfere with real hardware; therefore, only
        use it if you know what you are doing.
        Default value: 0

    --send_id=[message_ID]
        Allows to send message with a custom ID.
        This is only applicable if --send_i_understand_implications is not 0.
        Default value: 6FF

@note For a full list of key/value pairs that can be passed to --params see @ref dwx_sensor_enum_sample .

@section dwx_canbus_logger_sample_examples Examples

#### Run with a Virtual CAN Device

Test the applications using either a real CAN device or a virtual one. Create a
virtual device using the following commands:

    sudo modprobe vcan
    sudo ip link add dev vcan0 type vcan
    sudo ip link set up vcan0

In order to send data from the console to the virtual CAN bus, use the `cansend`
tool (from the `can-utils` package).

    cansend vcan0 30B#1122334455667788

This example sends a CAN message with ID 0x30B and with 8-bytes containing:
0x11, ..., 0x88

If using the virtual CAN interface, the sample can be started with
`--driver=can.socket --params=device=vcan0` to listen on the virtual CAN
interface. Any message sent with `cansend vcan0` is displayed on the console.


#### Run with Real Hardware

If using real-hardware connected to the CAN bus, set the bitrate to 500 KB in
order to test the sample. The sample does not support changing of the bitrate.
Set the bitrate on the CAN device by executing:

    sudo ip link set can0 type can bitrate 500000
    sudo ip link set can0 up

The CAN interface used to listen on a real CAN bus must have SocketCAN driver
implementation in the system. A SocketCAN based driver can be identified easily
if `:> sudo ifconfig -a` returns the default network interfaces **and** a CAN
based interface (i.e., canX, slcanX, etc).

@if QNX
@note the virtual CAN interface is not available on QNX
@endif

##### SocketCAN

To execute the sample to listen on the SocketCAN connectors, use:

    --driver=can.socket --params=device=can0

@if PX2_ONLY
##### AurixCAN

On NVIDIA DRIVE<sup>&trade;</sup> PX2 ACH and ACR, the CAN connectors marked with CAN-1..CAN-4 are reachable through Aurix by the Tegras.
For this to work, a proper setup of the Aurix needs to be made prior to running the application. Please
refer to the EasyCAN user guide provided as part of PDK documentation to set up Aurix to filter
and pass a selected subset of CAN messages. In order to connect to AurixCAN, use the following arguments:

On DRIVE PX2:
    --driver=can.aurix --params=ip=10.42.0.83,bus=a

On ACR:
    --driver=can.aurix --params=ip=127.0.0.1,aport=50000,bport=50103,bus=a

Where `ip` is the IP address from which the CAN messages are forwarded (by default, set to 10.42.0.83)
and `bus` points to the corresponding CAN bus connector, i.e., CAN-1->a, ..., CAN-4->d.

The connection to AurixCAN happens using UDP sockets. Additional arguments for the remote (`aport`) and
local (`bport`) UDP port can be specified if AurixCAN is working in a non-default configuration. By
default, on DRIVE PX2, AurixCAN is reachable over `aport=50000` and communicates with the Tegra over
`bport=60395`. On ACR however, AurixCAN is reachable over `aport=50000` and communicates with
the Tegra over `bport=50103`.
@endif

#### Message Sending

Additionally, the sample can be used as a CAN message generator:

    ./sample_canbus_logger --send_i_understand_implications=100

in this case itgenerates a random CAN message each 100ms. 
Note that sending might interfere with real hardware; therefore, only
use it if you know what you are doing.

@section dwx_canbus_logger_sample_output Output

The sample prints on console the received CAN messages:

    5651471936 -> 100  [5] 7E BB 02 00 00 
    5651471936 (dt=0) -> 200  [5] 80 57 02 00 00 
    5651474567 (dt=2631) -> 100  [5] A0 C1 02 00 00 
    5651474567 (dt=0) -> 200  [5] 80 57 02 00 00 
    5651477205 (dt=2638) -> 100  [5] A0 C1 02 00 00 
    5651477205 (dt=0) -> 200  [5] 80 57 02 00 00 
    5651479850 (dt=2645) -> 100  [5] A0 C1 02 00 00 
    5651479850 (dt=0) -> 200  [5] 80 57 02 00 00 
    5651482733 (dt=2883) -> 100  [5] A0 C1 02 00 00 
    5651482733 (dt=0) -> 200  [5] 80 57 02 00 00 
    5651485391 (dt=2658) -> 100  [5] 02 C9 02 00 00 
    5651485391 (dt=0) -> 200  [5] 11 65 02 00 00 
    5651487984 (dt=2593) -> 100  [5] 02 C9 02 00 00 
    5651487984 (dt=0) -> 200  [5] 11 65 02 00 00 
    5651490645 (dt=2661) -> 100  [5] 02 C9 02 00 00 
    5651490645 (dt=0) -> 200  [5] 11 65 02 00 00 
    5651493322 (dt=2677) -> 100  [5] 02 C9 02 00 00 
    5651493322 (dt=0) -> 200  [5] 11 65 02 00 00 
    5651496024 (dt=2702) -> 100  [5] 5A D0 02 00 00 
    5651496024 (dt=0) -> 200  [5] 11 65 02 00 00 
    5651498602 (dt=2578) -> 100  [5] 5A D0 02 00 00 
    5651498602 (dt=0) -> 200  [5] 11 65 02 00 00 
    5651501306 (dt=2704) -> 100  [5] 5A D0 02 00 00 
    5651501306 (dt=0) -> 200  [5] 11 65 02 00 00 
    5651504039 (dt=2733) -> 100  [5] 5A D0 02 00 00 
    5651504039 (dt=0) -> 200  [5] 11 65 02 00 00 
    5651506639 (dt=2600) -> 100  [5] 7C D6 02 00 00 

@section dwx_canbus_logger_sample_more Additional Information

For more details see @ref canbus_mainsection .
