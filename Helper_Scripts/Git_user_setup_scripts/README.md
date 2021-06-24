# The git helper scripts

To avoid identity theft on git when committing and pushing files, bash scripts have been created for the Ubuntu and Windows computers.



## Presentation of the scripts

### Windows :
 
- Windows_clear_git_user_info.bat			: This script is used to reset the name and email of every repository of the AD-EYE project. It has to be setup to be launched automatically at every log in. See below for instructions on how to set it up.

- [Firtsname]_[LastName]_Windows_set_git_user_info.bat	: This script is used to quickly change your git name. Your name must be edited in the file. This script has to be run manually, and you must not set it to run automatically. If the name and email are not filled, these will be set to an empty string and prevent you from commiting and pushing.




### Ubuntu :

- Ubuntu_clear_git_user_info.sh 			: This script is used to reset the name and email of every repository of the AD-EYE project. It has to be setup to be launched automatically at every log in. See below for instructions on how to set it up.

- [Firtsname]_[LastName]_Ubuntu_set_git_user_info.sh 	: This script is used to quickly change your git name. Your name must be edited in the file. This script has to be run manually, and you must not set it to run automatically. If the name and email are not filled, these will be set to an empty string and prevent you from commiting and pushing.





## How to setup the scripts to run on each login :

### Windows :

1. Put the script at this location (a new folder might be created): C:\Users\adeye\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\adeye
2. Follow this tutorial and the instructions [here](https://winaero.com/run-app-or-script-at-logon-with-task-scheduler-in-windows-10/).
3. In step 4, the name of the task should be: git_reset_id_AD-EYE-Core
4. Don't follow the step 5
5. In step 6,7,8,9, add 5 triggers : At log on, On connection to user session, On disconnect from user session, on workstation lock, on workstation unlock
6. In step 11, put this script as the program to run


### Ubuntu :

1. Put the file in the directory /etc/profile.d with administrative rights. This can be done in the terminal by using the keyword `sudo` before the move or copy command.
2. Make sure that the file is executable by running the command `sudo chmod u+x <path>/[name.sh]`

##### NOTE :
For all of the ubuntu scripts, the `chmod` command should be used to make the script executable.
