# Original file grt_unix.tmf Copyright 1994-2010 The MathWorks, Inc.
#
#-------------------------------------------------------------------------------
##### Prescan Linux variant of Mathworks' R2010bSP2 grt_unix.tmf
#####
##### Implements hints from article:
#####   http://nl.mathworks.com/help/rtw/ug/cross-compiling-code-generated-on-a-microsoft-windows-system.html 
#####
##### Note: Lines removed from the original grt_unix.tmf are commented out with #####
#####       TMF tokens in these lines are enclosed by #> and <#
#####       in order to suppress expansion by simulink coder.
#####       The Prescan build process injects new symbols via the file ps_linux.mk 
#####       generated by <target>_make_rtw_hook.m
#####
##### Note: This make file is based on R2010bSP2 grt_unix.tmf and therefore expects the classic GRT interface.
#####       Prescan symbol PRESCAN_MAIN (defined in ps_linux.mk) will be set to:
#####       * grt_main.c for MATLAB versions <= R2012a
#####       * classic_main.c for MATLAB versions > R2012a
#-------------------------------------------------------------------------------
# Abstract:
#	Real-Time Workshop template makefile for building a UNIX-based
#	stand-alone generic real-time version of Simulink model using
#	generated C code.
#
# 	This makefile attempts to conform to the guidelines specified in the
# 	IEEE Std 1003.2-1992 (POSIX) standard. It is designed to be used
#       with GNU Make which is located in matlabroot/rtw/bin.
#
# 	Note that this template is automatically customized by the Real-Time
#	Workshop build procedure to create "<model>.mk"
#
#       The following defines can be used to modify the behavior of the
#	build:
#	  OPT_OPTS       - Optimization options. Default is -O.
#	  CPP_OPTS       - C++ compiler options.
#	  OPTS           - User specific compile options.
#	  USER_SRCS      - Additional user sources, such as files needed by
#			   S-functions.
#	  USER_INCLUDES  - Additional include paths
#			   (i.e. USER_INCLUDES="-Iwhere-ever -Iwhere-ever2")
#
#       To enable debugging:
#         set DEBUG_BUILD = 1 below, which will trigger OPTS=-g and
#          LDFLAGS += -g (may vary with compiler version, see compiler doc) 
#
#       This template makefile is designed to be used with a system target
#       file that contains 'rtwgensettings.BuildDirSuffix' see grt.tlc

#####--------------------- ps_linux target symbols (fixed) -------------------

ARCH                 = glnxa64
COMPUTER             = GLNXA64
MEXEXT               = mexa64
MATLAB_ROOT          = ../../matlab
ALT_MATLAB_ROOT      = ../../matlab
MATLAB_BIN           = ../../matlab/bin

#####---------------------- ps_linux target symbols (injected) --------------
#
# OPTIMIZATION_FLAGS   - Compiler Optimization Flags
# MODELLIB             - Name of compiled model library
#
# PRESCANCORE          - Parent of Prescan bin and lib folders
# PRESCANHEADERS       - Prescan main include folder
# PRESCANMODULES       - Prescan modules folder
# PRESCANPLUGINS       - Prescan plugins folder
#
# PRESCAN_INCLUDES     - List of all Prescan folders to include in the compilation
# PRESCAN_SRCS         - List of additional Prescan source files on which PRESCAN_MAIN depends
# PRESCAN_LIBS         - List of all Prescan libraries to be included
# PRESCAN_MAIN         - Main program
# MAKEFILE             - The name of the make file

include info_ps_linux.mk

#------------------------ Macros read by make_rtw ------------------------------
#
# The following macros are read by the Real-Time Workshop build procedure:
#
#  MAKECMD         - This is the command used to invoke the make utility
#  HOST            - What platform this template makefile is targeted for
#                    (i.e. PC or UNIX)
#  BUILD           - Invoke make from the Real-Time Workshop build procedure
#                    (yes/no)?
#  SYS_TARGET_FILE - Name of system target file.

#####MAKECMD         = #>MATLAB_BIN<#/#>ARCH<#/gmake
MAKECMD              = gmake
HOST                 = UNIX
BUILD                = no
SYS_TARGET_FILE      = ps.tlc
MAKEFILE_FILESEP     = /
COMPILER_TOOL_CHAIN  = unix


#---------------------- Tokens expanded by make_rtw ----------------------------
#
# The following tokens, when wrapped with "|>" and "<|" are expanded by the
# Real-Time Workshop build procedure.
#
#  MODEL_NAME          - Name of the Simulink block diagram
#  MODEL_MODULES       - Any additional generated source modules
#  MAKEFILE_NAME       - Name of makefile created from template makefile <model>.mk
#  MATLAB_ROOT         - Path to where MATLAB is installed.
#  S_FUNCTIONS         - List of S-functions.
#  S_FUNCTIONS_LIB     - List of S-functions libraries to link.
#  SOLVER              - Solver source file name
#  NUMST               - Number of sample times
#  TID01EQ             - yes (1) or no (0): Are sampling rates of continuous task
#                        (tid=0) and 1st discrete task equal.
#  NCSTATES            - Number of continuous states
#  COMPUTER            - Computer type. See the MATLAB computer command.
#  BUILDARGS           - Options passed in at the command line.
#  MULTITASKING        - yes (1) or no (0): Is solver mode multitasking
#  EXT_MODE            - yes (1) or no (0): Build for external mode
#  TMW_EXTMODE_TESTING - yes (1) or no (0): Build ext_test.c for external mode
#                        testing.
#  EXTMODE_TRANSPORT   - Index of transport mechanism (e.g. tcpip, serial) for extmode
#  EXTMODE_STATIC      - yes (1) or no (0): Use static instead of dynamic mem alloc.
#  EXTMODE_STATIC_SIZE - Size of static memory allocation buffer.
#  GEN_MDLREF_SFCN     - (1/0): are we generating model reference wrapper s-function
#  TGT_FCN_LIB         - Target Funtion library to use
#  MODELREFS           - List of referenced models

MODEL                = Experiment_cs
MODULES              = rt_logging.c Experiment_cs_capi.c Experiment_cs_data.c Experiment_cs_prescan.c detect_tunability_loss.c rtGetInf.c rtGetNaN.c rt_nonfinite.c prescan_LogHandler.c prescan_ErrorHandler.c prescan_Modify.c
MAKEFILE             = $(PRESCANMAKEFILE)
##### MAKEFILE             = #>MAKEFILE_NAME<#

##### MATLAB_ROOT          = #>MATLAB_ROOT<#
##### ALT_MATLAB_ROOT      = #>ALT_MATLAB_ROOT<#
##### MATLAB_BIN           = #>MATLAB_BIN<#

MASTER_ANCHOR_DIR    = 
#START_DIR            = C:/Users/adeye/prescan_code_generation/examples/prescan-ros/Experiment
START_DIR            = /home/adeye/prescan_code_generation/examples/prescan-ros/Experiment-ubuntu/Experiment
S_FUNCTIONS          = 
S_FUNCTIONS_LIB      = 
SOLVER               = 
NUMST                = 2
TID01EQ              = 1
NCSTATES             = 0
#####COMPUTER             = #>COMPUTER<#
BUILDARGS            =  MODELLIB=Experiment_cslib.lib MAT_FILE=1 COMBINE_OUTPUT_UPDATE_FCNS=0 INCLUDE_MDL_TERMINATE_FCN=1 MULTI_INSTANCE_CODE=0 ISPROTECTINGMODEL=NOTPROTECTING
MULTITASKING         = 0
EXT_MODE             = 0
TMW_EXTMODE_TESTING  = 0
EXTMODE_TRANSPORT    = 0
EXTMODE_STATIC       = 0
EXTMODE_STATIC_SIZE  = 1000000
#####MEXEXT               = #>MEXEXT<#
TGT_FCN_LIB          = C89/C90 (ANSI)
MODELREFS            = 
SHARED_SRC           = 
SHARED_SRC_DIR       = 
SHARED_BIN_DIR       = 
SHARED_LIB           = 
TARGET_LANG_EXT      = c
#####OPTIMIZATION_FLAGS   = #>OPTIMIZATION_FLAGS<#
ADDITIONAL_LDFLAGS   = 

# To enable debugging:
# set DEBUG_BUILD = 1
DEBUG_BUILD          = 0

#--------------------------- Model and reference models -----------------------
##### MODELLIB                  = #>MODELLIB<#
MODELREF_LINK_LIBS        = 
MODELREF_INC_PATH         = 
RELATIVE_PATH_TO_ANCHOR   = ..
# NONE: standalone, SIM: modelref sim, RTW: modelref rtw
MODELREF_TARGET_TYPE       = NONE

#-- In the case when directory name contains space ---
ifneq ($(MATLAB_ROOT),$(ALT_MATLAB_ROOT))
MATLAB_ROOT := $(ALT_MATLAB_ROOT)
endif

#--------------------------- Tool Specifications -------------------------------

include $(MATLAB_ROOT)/rtw/c/tools/unixtools.mk

#------------------------------ Include Path -----------------------------------

MATLAB_INCLUDES = \
	-I$(MATLAB_ROOT)/simulink/include \
	-I$(MATLAB_ROOT)/extern/include \
	-I$(MATLAB_ROOT)/rtw/c/src \
	-I$(MATLAB_ROOT)/rtw/c/src/ext_mode/common

# Additional file include paths
ADD_INCLUDES = \
	-I$(START_DIR) \
	-I$(START_DIR)/Experiment_cs_ps_rtw \
	-I$(MATLAB_ROOT)/extern/include \
	-I$(MATLAB_ROOT)/simulink/include \
	-I$(MATLAB_ROOT)/rtw/c/src \
	-I$(MATLAB_ROOT)/rtw/c/src/ext_mode/common \


SHARED_INCLUDES =
ifneq ($(SHARED_SRC_DIR),)
SHARED_INCLUDES = -I$(SHARED_SRC_DIR) 
endif

##### Extra includes for Prescan
INCLUDES = -I. -I$(RELATIVE_PATH_TO_ANCHOR) $(PRESCAN_INCLUDES) $(MATLAB_INCLUDES) $(ADD_INCLUDES) $(USER_INCLUDES) \
	$(INSTRUMENT_INCLUDES)  $(MODELREF_INC_PATH) $(SHARED_INCLUDES)

#----------------------------- External mode -----------------------------------
# Uncomment -DVERBOSE to have information printed to stdout
# To add a new transport layer, see the comments in
#   <matlabroot>/toolbox/simulink/simulink/extmode_transports.m
ifeq ($(EXT_MODE),1)
  EXT_CC_OPTS = -DEXT_MODE -D$(COMPUTER) #-DVERBOSE
  EXT_LIB     =
  EXT_SRC     =
  LINT_EXT_COMMON_SRC =
  LINT_EXT_TCPIP_SRC  =
  ifeq ($(EXTMODE_TRANSPORT),0) #tcpip
    EXT_SRC = ext_svr.c updown.c ext_work.c rtiostream_interface.c \
	rtiostream_tcpip.c
    LINT_EXT_COMMON_SRC = ext_svr.c updown.c ext_work.c \
	rtiostream_interface.c
    LINT_EXT_TCPIP_SRC  = rtiostream_tcpip.c
  endif
  ifeq ($(EXTMODE_TRANSPORT),1) #serial_win32
    err:
	@echo
	@echo "### ERROR: External mode serial transport only available on win32"
	@echo
  endif
  ifeq ($(TMW_EXTMODE_TESTING),1)
    EXT_SRC     += ext_test.c
    EXT_CC_OPTS += -DTMW_EXTMODE_TESTING
  endif
  ifeq ($(EXTMODE_STATIC),1)
    EXT_SRC             += mem_mgr.c
    LINT_EXT_COMMON_SRC += mem_mgr.c
    EXT_CC_OPTS         += -DEXTMODE_STATIC -DEXTMODE_STATIC_SIZE=$(EXTMODE_STATIC_SIZE)
  endif
  ifeq ($(COMPUTER),SOL64)
    EXT_LIB = -lsocket -lnsl
  endif
endif

#----------------------------- Real-Time Model ---------------------------------
RTM_CC_OPTS = -DUSE_RTMODEL

#-------------------------------- C Flags --------------------------------------

# Optimization Options
ifndef OPT_OPTS
OPT_OPTS = $(DEFAULT_OPT_OPTS)
endif

# General User Options
ifeq ($(DEBUG_BUILD),0)
OPTS =
else
#   Set OPTS=-g and any additional flags for debugging
OPTS = -g
LDFLAGS += -g
endif

# Compiler options, etc:
ifneq ($(OPTIMIZATION_FLAGS),)
CC_OPTS = $(OPTS) $(EXT_CC_OPTS) $(RTM_CC_OPTS) $(OPTIMIZATION_FLAGS)
else
CC_OPTS = $(OPT_OPTS) $(OPTS) $(EXT_CC_OPTS) $(RTM_CC_OPTS)
endif


CPP_REQ_DEFINES = -DMODEL=$(MODEL) -DRT -DNUMST=$(NUMST) \
                  -DTID01EQ=$(TID01EQ) -DNCSTATES=$(NCSTATES) -DUNIX \
                  -DMT=$(MULTITASKING) -DHAVESTDIO 


CFLAGS   = $(ANSI_OPTS) $(CC_OPTS) $(CPP_REQ_DEFINES) $(INCLUDES)
CPPFLAGS = $(CPP_ANSI_OPTS) $(CPP_OPTS) $(CC_OPTS) $(CPP_REQ_DEFINES) $(INCLUDES)
#-------------------------- Additional Libraries ------------------------------

##### add Prescan libraries
SYSLIBS = $(EXT_LIB) -lm -L$(PRESCAN_LIB_PATH) $(PRESCAN_LIBS)  -Wl,--unresolved-symbols=ignore-in-shared-libs,-rpath-link=$(PRESCAN_LIB_PATH)

LIBS =
 
LIBS += $(S_FUNCTIONS_LIB) $(INSTRUMENT_LIBS)

#----------------------------- Source Files ------------------------------------

USER_OBJS       = $(addsuffix .o, $(basename $(USER_SRCS)))
LOCAL_USER_OBJS = $(notdir $(USER_OBJS))


SRCS = $(MODULES) $(S_FUNCTIONS)

ifeq ($(MODELREF_TARGET_TYPE), NONE)
    PRODUCT            = $(RELATIVE_PATH_TO_ANCHOR)/$(MODEL)
    BIN_SETTING        = $(LD) $(LDFLAGS) $(ADDITIONAL_LDFLAGS) -o $(PRODUCT)
    BUILD_PRODUCT_TYPE = "executable"
##### Prescan injected main for classic GRT interface
    SRCS               += $(MODEL).$(TARGET_LANG_EXT) $(PRESCAN_SRCS) $(PRESCAN_MAIN) rt_sim.c $(EXT_SRC) $(SOLVER)
else
    # Model reference rtw target
    PRODUCT            = $(MODELLIB)
    BUILD_PRODUCT_TYPE = "library"
endif

ifneq ($(findstring .cpp,$(suffix $(SRCS), $(USER_SRCS))),)
  LD = $(CPP)
endif

OBJS      = $(addsuffix .o, $(basename $(SRCS))) $(USER_OBJS)
LINK_OBJS = $(addsuffix .o, $(basename $(SRCS))) $(LOCAL_USER_OBJS)

SHARED_SRC := $(wildcard $(SHARED_SRC))
SHARED_OBJS = $(addsuffix .o, $(basename $(SHARED_SRC)))

#------------- Test Compile using gcc -Wall to look for warnings ---------------
#
# DO_GCC_TEST=1 runs gcc with compiler warning flags on all the source files
# used in this build. This includes the generated code, and any user source
# files needed for the build and placed in this directory.
#
# WARN_ON_GLNX=1 runs the linux compiler with warnings flags. On hand-written
# code we use the max amount of flags availabe while on the generated code, a
# few less.
#
# See rtw/c/tools/unixtools.mk for the definition of GCC_WARN_OPTS
GCC_TEST_CMD  := echo
GCC_TEST_OUT  := > /dev/null
ifeq ($(DO_GCC_TEST), 1)
  GCC_TEST := gcc -c -o /dev/null $(GCC_WARN_OPTS_MAX) $(CPP_REQ_DEFINES) \
                                     $(INCLUDES)
  GCC_TEST_CMD := echo; echo "\#\#\# GCC_TEST $(GCC_TEST) $<"; $(GCC_TEST)
  GCC_TEST_OUT := ; echo
endif

#----------------------------- Lint (sol2 only) --------------------------------

#### Prescan defined main for classic GRT interface
LINT_SRCS = $(MATLAB_ROOT)/rtw/c/grt/$(PRESCAN_MAIN) \
	    $(MATLAB_ROOT)/rtw/c/src/rt_sim.c
ifneq ($(SOLVER), )
  LINT_SRCS += $(MATLAB_ROOT)/rtw/c/src/$(SOLVER)
endif
ifneq ($(LINT_EXT_COMMON_SRC), )
  LINT_SRCS += $(MATLAB_ROOT)/rtw/c/src/ext_mode/common/$(LINT_EXT_COMMON_SRC)
endif
ifneq ($(LINT_EXT_TCPIP_SRC), )
  LINT_SRCS += $(MATLAB_ROOT)/rtw/c/src/rtiostream/rtiostreamtcpip/$(LINT_EXT_TCPIP_SRC)
endif
LINT_SRCS += $(MODEL).$(TARGET_LANG_EXT) $(MODULES) $(USER_SRCS) $(S_FUNCTIONS)
LINTOPTSFILE = $(MODEL).lintopts

LINT_ERROFF1 = E_NAME_DEF_NOT_USED2,E_NAME_DECL_NOT_USED_DEF2
LINT_ERROFF2 = $(LINT_ERROFF1),E_FUNC_ARG_UNUSED
LINT_ERROFF  = $(LINT_ERROFF2),E_INDISTING_FROM_TRUNC2,E_NAME_USED_NOT_DEF2

#--------------------------------- Rules ---------------------------------------
ifeq ($(MODELREF_TARGET_TYPE),NONE)
$(PRODUCT) : $(OBJS) $(SHARED_LIB) $(LIBS) $(MODELREF_LINK_LIBS)
	$(BIN_SETTING) $(LINK_OBJS) $(MODELREF_LINK_LIBS) $(SHARED_LIB) $(LIBS) $(SYSLIBS)
	@echo "### Created $(BUILD_PRODUCT_TYPE): $@"
else
$(PRODUCT) : $(OBJS) $(SHARED_LIB)
	@rm -f $(MODELLIB)
	ar ruvs $(MODELLIB) $(LINK_OBJS)
	@echo "### Created $(MODELLIB)"
	@echo "### Created $(BUILD_PRODUCT_TYPE): $@"
endif

ifneq ($(SHARED_SRC_DIR),)
$(SHARED_BIN_DIR)/%.o : $(SHARED_SRC_DIR)/%.c
	cd $(SHARED_BIN_DIR); $(CC) -c $(CFLAGS) $(GCC_WALL_FLAG_MAX) $(notdir $?)

$(SHARED_BIN_DIR)/%.o : $(SHARED_SRC_DIR)/%.cpp
	cd $(SHARED_BIN_DIR); $(CPP) -c $(CPPFLAGS) $(GCC_WALL_FLAG_MAX) $(notdir $?)
endif

%.o : %.c
	@$(GCC_TEST_CMD) "$<" $(GCC_TEST_OUT)
	$(CC) -c $(CFLAGS) $(GCC_WALL_FLAG) "$<"

%.o : %.cpp
	@$(GCC_TEST_CMD) "$<" $(GCC_TEST_OUT)
	$(CPP) -c $(CPPFLAGS) $(GCC_WALL_FLAG) "$<"

%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	@$(GCC_TEST_CMD) "$<" $(GCC_TEST_OUT)
	$(CC) -c $(CFLAGS) $(GCC_WALL_FLAG) "$<"

%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.cpp
	@$(GCC_TEST_CMD) "$<" $(GCC_TEST_OUT)
	$(CPP) -c $(CPPFLAGS) "$<"

##### Prescan target installation source files -- begin

%.o : $(PRESCANHEADERS)/platform/grt/%.c
	@$(GCC_TEST_CMD) "$<" $(GCC_TEST_OUT)
	$(CC) -c $(CFLAGS) $(GCC_WALL_FLAG) "$<"

%.o : $(PRESCANHEADERS)/platform/grt/%.cpp
	@$(GCC_TEST_CMD) "$<" $(GCC_TEST_OUT)
	$(CPP) -c $(CPPFLAGS) "$<"

##### Prescan target installation source files -- end

ifeq ($(TARGET_LANG_EXT),cpp)
%.o : $(MATLAB_ROOT)/rtw/c/grt/%.c
	@$(GCC_TEST_CMD) "$<" $(GCC_TEST_OUT)
	$(CPP) -c $(CPPFLAGS) $(GCC_WALL_FLAG_MAX) "$<"
else
%.o : $(MATLAB_ROOT)/rtw/c/grt/%.c
	@$(GCC_TEST_CMD) "$<" $(GCC_TEST_OUT)
	$(CC) -c $(CFLAGS) $(GCC_WALL_FLAG_MAX) "$<"
endif

%.o : $(MATLAB_ROOT)/rtw/c/src/%.c
	@$(GCC_TEST_CMD) "$<" $(GCC_TEST_OUT)
	$(CC) -c $(CFLAGS) $(GCC_WALL_FLAG_MAX) "$<"

%.o : $(MATLAB_ROOT)/rtw/c/src/ext_mode/common/%.c
	@$(GCC_TEST_CMD) "$<" $(GCC_TEST_OUT)
	$(CC) -c $(CFLAGS) $(GCC_WALL_FLAG_MAX) "$<"

%.o : $(MATLAB_ROOT)/rtw/c/src/rtiostream/rtiostreamtcpip/%.c
	@$(GCC_TEST_CMD) "$<" $(GCC_TEST_OUT)
	$(CC) -c $(CFLAGS) $(GCC_WALL_FLAG_MAX) "$<"

%.o : $(MATLAB_ROOT)/rtw/c/src/ext_mode/custom/%.c
	@$(GCC_TEST_CMD) "$<" $(GCC_TEST_OUT)
	$(CC) -c $(CFLAGS) $(GCC_WALL_FLAG_MAX) "$<"

%.o : $(START_DIR)/Experiment_cs_ps_rtw/%.c
	@$(GCC_TEST_CMD) "$<" $(GCC_TEST_OUT)
	$(CC) -c $(CFLAGS) $(GCC_WALL_FLAG_MAX) "$<"

%.o : $(MATLAB_ROOT)/rtw/c/src/%.c
	@$(GCC_TEST_CMD) "$<" $(GCC_TEST_OUT)
	$(CC) -c $(CFLAGS) $(GCC_WALL_FLAG_MAX) "$<"

%.o : $(MATLAB_ROOT)/simulink/src/%.c
	@$(GCC_TEST_CMD) "$<" $(GCC_TEST_OUT)
	$(CC) -c $(CFLAGS) $(GCC_WALL_FLAG_MAX) "$<"

rt_logging.o : /home/adeye/prescan_code_generation/examples/prescan-ros/Experiment-ubuntu/matlab/rtw/c/src/rt_logging.c
	@$(GCC_TEST_CMD) /home/adeye/prescan_code_generation/examples/prescan-ros/Experiment-ubuntu/matlab/rtw/c/src/rt_logging.c $(GCC_TEST_OUT)
	$(CC) -c $(CFLAGS) $(GCC_WALL_FLAG_MAX) /home/adeye/prescan_code_generation/examples/prescan-ros/Experiment-ubuntu/matlab/rtw/c/src/rt_logging.c



%.o : $(START_DIR)/Experiment_cs_ps_rtw/%.cpp
	@$(GCC_TEST_CMD) "$<" $(GCC_TEST_OUT)
	$(CPP) -c $(CPPFLAGS) "$<"
%.o : $(MATLAB_ROOT)/rtw/c/src/%.cpp
	@$(GCC_TEST_CMD) "$<" $(GCC_TEST_OUT)
	$(CPP) -c $(CPPFLAGS) "$<"
%.o : $(MATLAB_ROOT)/simulink/src/%.cpp
	@$(GCC_TEST_CMD) "$<" $(GCC_TEST_OUT)
	$(CPP) -c $(CPPFLAGS) "$<"


%.o : $(MATLAB_ROOT)/simulink/src/%.c
	@$(GCC_TEST_CMD) "$<" $(GCC_TEST_OUT)
	$(CC) -c $(CFLAGS) $(GCC_WALL_FLAG_MAX) "$<"

%.o : $(MATLAB_ROOT)/simulink/src/%.cpp
	@$(GCC_TEST_CMD) "$<" $(GCC_TEST_OUT)
	$(CPP) -c $(CPPFLAGS) "$<"

#------------------------------- Libraries -------------------------------------





#----------------------------- Dependencies ------------------------------------

##### $(OBJS) : $(MAKEFILE) rtw_proj.tmw ##### Remove rtw_proj dependency; on host, this forces rebuild if model has changed
$(OBJS) : $(MAKEFILE)

$(SHARED_LIB) : $(SHARED_OBJS)
	@echo "### Creating $@ "
	ar ruvs $@ $(SHARED_OBJS)
	@echo "### $@ Created  "


#--------- Miscellaneous rules to purge, clean and lint (sol2 only) ------------

purge : clean
	@echo "### Deleting the generated source code for $(MODEL)"
	@\rm -f $(MODEL).c $(MODEL).h $(MODEL)_types.h $(MODEL)_data.c \
	        $(MODEL)_private.h $(MODEL).rtw $(MODULES) rtw_proj.tmw $(MAKEFILE)

clean :
	@echo "### Deleting the objects and $(PRODUCT)"
	@\rm -f $(LINK_OBJS) $(PRODUCT)

lint  : rtwlib.ln
	@lint -errchk -errhdr=%user -errtags=yes -F -L. -lrtwlib -x -Xc \
	      -erroff=$(LINT_ERROFF) \
	      -D_POSIX_C_SOURCE $(CFLAGS) $(LINT_SRCS)
	@\rm -f $(LINTOPTSFILE)
	@echo
	@echo "### Created lint output only, no executable"
	@echo

rtwlib.ln : $(MAKEFILE) rtw_proj.tmw
	@echo
	@echo "### Linting ..."
	@echo
	@\rm -f llib-lrtwlib.ln $(LINTOPTSFILE)
	@echo "-dirout=. -errchk -errhdr=%user " >> $(LINTOPTSFILE)
	@echo "-errtags -F -ortwlib -x -Xc " >> $(LINTOPTSFILE)
	@echo "-erroff=$(LINT_ERROFF) " >> $(LINTOPTSFILE)
	@echo "-D_POSIX_C_SOURCE $(CFLAGS) " >> $(LINTOPTSFILE)
	@for file in $(MATLAB_ROOT)/rtw/c/libsrc/*.c; do \
	  echo "$$file " >> $(LINTOPTSFILE); \
	done
	lint -flagsrc=$(LINTOPTSFILE)

# EOF: grt_unix.tmf
