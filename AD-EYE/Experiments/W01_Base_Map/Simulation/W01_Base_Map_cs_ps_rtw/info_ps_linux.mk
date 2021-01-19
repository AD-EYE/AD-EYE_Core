#  Symbols injected by Prescan
#  WARNING do not use spaces in path strings!
#

PRESCANCORE = /usr/local/Prescan_2020.1.0
PRESCANHEADERS = /usr/local/Prescan_2020.1.0/include
PRESCANMODULES = /usr/local/Prescan_2020.1.0/modules
OPTIMIZATION_FLAGS = -O0 -fPIC
MODELLIB = W01_Base_Map_cs.a
PRESCANMAKEFILE = make_ps_linux.mk
PRESCAN_MAIN = ps_main.c
PRESCAN_SRCS = model_main.c

PRESCAN_LIB_PATH = $(PRESCANCORE)/lib

PRESCAN_INCLUDES = \
  -I$(PRESCANHEADERS)/platform \
  -I$(PRESCANHEADERS)/sensors/InterfaceRTW \
  -I$(PRESCANMODULES)/AIR/include_interface \
  -I$(PRESCANMODULES)/ALMS/include_interface \
  -I$(PRESCANMODULES)/Annotations/include_interface \
  -I$(PRESCANMODULES)/Apollo/include_interface \
  -I$(PRESCANMODULES)/BRS/include_interface \
  -I$(PRESCANMODULES)/Camera/include_interface \
  -I$(PRESCANMODULES)/CollisionDetection/include_interface \
  -I$(PRESCANMODULES)/Communication/include_interface \
  -I$(PRESCANMODULES)/GPS/include_interface \
  -I$(PRESCANMODULES)/GenericModel/include_interface \
  -I$(PRESCANMODULES)/GraphBasedRoads/include_interface \
  -I$(PRESCANMODULES)/LaneMarker/include_interface \
  -I$(PRESCANMODULES)/Lidar/include_interface \
  -I$(PRESCANMODULES)/OCS/include_interface \
  -I$(PRESCANMODULES)/ObjectListProvider/include_interface \
  -I$(PRESCANMODULES)/OpenDriveImporter/include_interface \
  -I$(PRESCANMODULES)/OpenScenarioImporter/include_interface \
  -I$(PRESCANMODULES)/PCS/include_interface \
  -I$(PRESCANMODULES)/PhysicsBasedCamera/include_interface \
  -I$(PRESCANMODULES)/ProtobufScalarReader/include_interface \
  -I$(PRESCANMODULES)/Radar/include_interface \
  -I$(PRESCANMODULES)/ResultWriter/include_interface \
  -I$(PRESCANMODULES)/ScannerSensor/include_interface \
  -I$(PRESCANMODULES)/SimulationControl/include_interface \
  -I$(PRESCANMODULES)/TIS/include_interface \
  -I$(PRESCANMODULES)/TestAutomation/include_interface \
  -I$(PRESCANMODULES)/Trajectory/include_interface \
  -I$(PRESCANMODULES)/TunableData/include_interface \
  -I$(PRESCANMODULES)/UltraSonic/include_interface \
  -I$(PRESCANMODULES)/UserData/include_interface \
  -I$(PRESCANMODULES)/ViewerProxy/include_interface \
  -I$(PRESCANMODULES)/WheelContacts/include_interface \
  -I$(PRESCANMODULES)/WorldModelActuators/include_interface \
  -I$(PRESCANMODULES)/WorldModelSensors/include_interface \
  -I$(PRESCANMODULES)/WorldViewer/include_interface
PRESCAN_LIBS = \
  -lplatform \
  -linterface_TunableData \
  -linterface_TestAutomation \
  -linterface_AIR \
  -linterface_ALMS \
  -linterface_Annotations \
  -linterface_BRS \
  -linterface_Camera \
  -linterface_CollisionDetection \
  -linterface_Communication \
  -linterface_GPS \
  -linterface_LaneMarker \
  -linterface_Lidar \
  -linterface_OCS \
  -linterface_ObjectListProvider \
  -linterface_PCS \
  -linterface_PhysicsBasedCamera \
  -linterface_ProtobufScalarReader \
  -linterface_Radar \
  -linterface_ResultWriter \
  -linterface_SimulationControl \
  -linterface_TIS \
  -linterface_Trajectory \
  -linterface_UltraSonic \
  -linterface_WheelContacts \
  -linterface_WorldModelActuators \
  -linterface_WorldModelSensors \
  -linterface_WorldViewer
