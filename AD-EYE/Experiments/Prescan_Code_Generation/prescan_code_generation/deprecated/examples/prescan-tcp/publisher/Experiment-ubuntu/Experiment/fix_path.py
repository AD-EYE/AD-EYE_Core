#!/usr/bin/env python3
import os
import sys

MAKE_PS_LINUX_FILENAME = 'Experiment_cs_ps_rtw/make_ps_linux.mk'
RT_LOGGING_WRONG_PATH = 'C:\\Program\\ Files\\MATLAB\\R2019a\\rtw\\c\\src'


def format_make_ps_linux_file():
    fix_start_dir_path()
    remove_windows_library_include()
    add_rosbridge_include_path()
    add_rosbridge_build_rule()
    fix_rt_logging_path()


def fix_start_dir_path():
    START_DIR_LINE_START = 'START_DIR            ='

    script_path = os.path.dirname(os.path.realpath(__file__))
    start_dir_new_content = START_DIR_LINE_START + ' {}\n'.format(script_path)

    condition_func = lambda line: line.startswith(START_DIR_LINE_START)
    new_content_func = lambda line: start_dir_new_content
    modify_line_in_make_ps(condition_func, new_content_func, add_break=True)


def remove_windows_library_include():
    WINDOWS_LIBRARY_LINE_START = 'S_FUNCTIONS_LIB      ='

    condition_func = lambda line: line.startswith(WINDOWS_LIBRARY_LINE_START)
    new_content_func = lambda line: WINDOWS_LIBRARY_LINE_START + '\n'
    modify_line_in_make_ps(condition_func, new_content_func, add_break=True)


def add_rosbridge_include_path():
    EXPERIMENT_INCLUDE_RULE = '-I$(START_DIR)/Experiment_cs_ps_rtw'
    EXPERIMENT_AND_ROSBRIDGE_INCLUDE_RULE = (
        '\t-I$(START_DIR)/Experiment_cs_ps_rtw \\\n'
        '\t-I$(START_DIR)/rosbridge/include \\\n'
    )

    condition_func = lambda line: EXPERIMENT_INCLUDE_RULE in line
    new_content_func = lambda line: EXPERIMENT_AND_ROSBRIDGE_INCLUDE_RULE
    modify_line_in_make_ps(condition_func, new_content_func, add_break=True)


def add_rosbridge_build_rule():
    EXPERIMENT_BUILD_RULE_FIRST_LINE = '%.o : $(START_DIR)/Experiment_cs_ps_rtw/%.c'
    ROSBRIDGE_AND_EXPERIMENT_BUILD_RULE = (
        '%.o : $(START_DIR)/rosbridge/%.c\n'
        '\t@$(GCC_TEST_CMD) "$<" $(GCC_TEST_OUT)\n'
        '\t$(CC) -c $(CFLAGS) $(GCC_WALL_FLAG_MAX) "$<"\n'
        '\n'
        '%.o : $(START_DIR)/Experiment_cs_ps_rtw/%.c'
    )

    condition_func = lambda line: line.startswith(EXPERIMENT_BUILD_RULE_FIRST_LINE)
    new_content_func = lambda line: ROSBRIDGE_AND_EXPERIMENT_BUILD_RULE
    modify_line_in_make_ps(condition_func, new_content_func, add_break=True)


def fix_rt_logging_path():
    RT_LOGGING_CORRECT_PATH = '$(MATLAB_ROOT)/rtw/c/src'

    condition_func = lambda line: RT_LOGGING_WRONG_PATH in line
    new_content_func = lambda line: line.replace(RT_LOGGING_WRONG_PATH, RT_LOGGING_CORRECT_PATH)
    modify_line_in_make_ps(condition_func, new_content_func, add_break=False)


def modify_line_in_make_ps(condition_func, new_content_func, add_break):
    modify_line_in_file(MAKE_PS_LINUX_FILENAME, condition_func, new_content_func, add_break)


def modify_line_in_file(filename, condition_func, new_content_func, add_break):
    with open(filename, 'r') as f:
        data = f.readlines()

    for line_number, line in enumerate(list(data)):
        if condition_func(line):
            data[line_number] = new_content_func(line)

            if add_break:
                break

    with open(filename, 'w') as f:
        f.writelines(data)


def is_file_already_fixed(filename):
    with open(filename, 'r') as f:
        for line in f:
            if RT_LOGGING_WRONG_PATH in line:
                return False

    return True


if __name__ == '__main__':
    if is_file_already_fixed(MAKE_PS_LINUX_FILENAME):
        print(
            'File {} has already been fixed. Won\'t do anything...'
            .format(MAKE_PS_LINUX_FILENAME)
        )
        sys.exit()

    format_make_ps_linux_file()
