:: This script reset the git id of AD-EYE_Core repository

:: ------ Instruction ------::

:: It has to be launched every time we log on, log out: To set it up, follow this step:
:: Put this script at this location (a new folder might be created): C:\Users\adeye\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\adeye
:: Follow this tutorial and the instructions below: https://winaero.com/run-app-or-script-at-logon-with-task-scheduler-in-windows-10/
:: In step 4, the name of the task should be: git_reset_id_AD-EYE-Core
:: Don't follow the step 5
:: In step 6,7,8,9, add 5 triggers : At log on, On connection to user session, On disconnect from user session, on workstation lock, on workstation unlock
:: In step 11, put this script as the program to run


::----- Command line -----::
@cd C:\Users\adeye\AD-EYE_Core
git config --global --remove-section user
git config --local --remove-section user
cd C:\Users\adeye\AD-EYE_Core\Pex_Data_Extraction
git config --local --remove-section user
