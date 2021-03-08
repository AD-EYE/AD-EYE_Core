#!/usr/bin/env python3
import os

INFO_PS_LINUX_FILENAME = 'Experiment_cs_ps_rtw/info_ps_linux.mk'
MAKE_PS_LINUX_FILENAME = 'Experiment_cs_ps_rtw/make_ps_linux.mk'
ROSBRIDGE_FUNCTIONS_C_FILENAME = 'rosbridge_functions.c'

PRESCAN_SRCS_LINE_START = 'PRESCAN_SRCS'
PRESCAN_SRCS_NEW_CONTENT = 'PRESCAN_SRCS = model_main.c {}\n'.format(ROSBRIDGE_FUNCTIONS_C_FILENAME)

START_DIR_LINE_START = 'START_DIR            ='
RT_LOGGING_WRONG_PATH = 'C:\\Program\\ Files\\MATLAB\\R2019a\\rtw\\c\\src'
RT_LOGGING_CORRECT_PATH = '$(MATLAB_ROOT)/rtw/c/src'

EXPERIMENT_BUILD_RULE_LINE_START = '%.o : $(START_DIR)/Experiment_cs_ps_rtw/%.c'
ROSBRIDGE_BUILD_RULE = (
"""
%.o : $(START_DIR)/rosbridge_functions/%.c
    @$(GCC_TEST_CMD) "$<" $(GCC_TEST_OUT)
    $(CC) -c $(CFLAGS) $(GCC_WALL_FLAG_MAX) "$<"

"""
)

def format_info_ps_linux_file():
    add_rosbridge_to_prescan_sources()


def format_make_ps_linux_file():
    fix_start_dir_path()
    fix_rt_logging_path()
    add_rosbridge_build_rule()


def add_rosbridge_to_prescan_sources():
    with open(INFO_PS_LINUX_FILENAME, 'r') as f:
        data = f.readlines()

    for line_number, line in enumerate(list(data)):
        if line.startswith(PRESCAN_SRCS_LINE_START):
            data[line_number] = PRESCAN_SRCS_NEW_CONTENT
            break

    with open(INFO_PS_LINUX_FILENAME, 'w') as f:
        f.writelines(data)


def fix_start_dir_path():
    with open(MAKE_PS_LINUX_FILENAME, 'r') as f:
        data = f.readlines()

    script_path = os.path.dirname(os.path.realpath(__file__))
    start_dir_new_content = START_DIR_LINE_START + ' {}\n'.format(script_path)

    for line_number, line in enumerate(list(data)):
        if line.startswith(START_DIR_LINE_START):
            data[line_number] = start_dir_new_content
            break

    with open(MAKE_PS_LINUX_FILENAME, 'w') as f:
        f.writelines(data)


def fix_rt_logging_path():
    with open(MAKE_PS_LINUX_FILENAME, 'r') as f:
        data = f.readlines()

    for line_number, line in enumerate(list(data)):
        if RT_LOGGING_WRONG_PATH in line:
            data[line_number] = line.replace(
                RT_LOGGING_WRONG_PATH, RT_LOGGING_CORRECT_PATH
            )

    with open(MAKE_PS_LINUX_FILENAME, 'w') as f:
        f.writelines(data)


def add_rosbridge_build_rule():
    with open(MAKE_PS_LINUX_FILENAME, 'r') as f:
        data = f.readlines()

    for line_number, line in enumerate(list(data)):
        if line.startswith(EXPERIMENT_BUILD_RULE_LINE_START):
            data[line_number - 1] = ROSBRIDGE_BUILD_RULE

    with open(MAKE_PS_LINUX_FILENAME, 'w') as f:
        f.writelines(data)


if __name__ == '__main__':
    format_info_ps_linux_file()
    format_make_ps_linux_file()
