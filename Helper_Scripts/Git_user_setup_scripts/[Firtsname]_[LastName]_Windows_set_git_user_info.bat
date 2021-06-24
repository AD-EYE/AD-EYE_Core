::Change the name of the file with your name: [FirtsName]_[LastName]_windows_set_git_user_id

::Put your name between the quotation mark
set Name=""
::Put your email adresse between the quotation mark
set Email=""

@if %Name%=="" @echo Your name is empty, you have to edit your script

@cd C:\Users\adeye\AD-EYE_Core
git config --global user.name %Name%
git config --global user.email %Email%
git config --local user.name %Name%
git config --local user.email %Email%
PAUSE
