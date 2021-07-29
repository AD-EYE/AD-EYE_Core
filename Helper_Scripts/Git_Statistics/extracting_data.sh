##Extracting data from a git repository

#Check if needed packages are already installed
REQUIRED_PKG="expect"
PKG_OK=$(dpkg-query -W --showformat='${Status}\n' $REQUIRED_PKG|grep "install ok installed")
echo Checking for $REQUIRED_PKG: $PKG_OK
if [ "" = "$PKG_OK" ]; then
  echo "$REQUIRED_PKG is not installed. Install it using : sudo apt-get install expect."
  exit 1
fi

REQUIRED_PKG="gitstats"
PKG_OK=$(dpkg-query -W --showformat='${Status}\n' $REQUIRED_PKG|grep "install ok installed")
echo Checking for $REQUIRED_PKG: $PKG_OK
if [ "" = "$PKG_OK" ]; then
  echo "$REQUIRED_PKG is not installed. Install it using : sudo apt-get install gitstats."
  exit 1
fi

PIP_OK=$(pip3 list | grep -F labours)
echo Checking for labours:
if [ "" = "$PIP_OK" ]; then
  echo "labours package is not installed. Install it using : pip3 install labours."
  exit 1
else
    echo "install ok installed"
fi

#Initialisation of the passphrase
#!/bin/bash
echo
echo "Enter the passphrase : "
read -s GIT_STAT_PASSPHRASE
export GIT_STAT_PASSPHRASE

#Working directory
export WORKING_PATH=~

#Installation of deploy key for AD-EYE_Core
cd
mkdir .ssh/
cd .ssh/
rm id_ed25519 id_ed25519.pub known_hosts
echo "-----BEGIN OPENSSH PRIVATE KEY-----
b3BlbnNzaC1rZXktdjEAAAAACmFlczI1Ni1jYmMAAAAGYmNyeXB0AAAAGAAAABDj3zTKII
iYssl2azW9zs8yAAAAEAAAAAEAAAAzAAAAC3NzaC1lZDI1NTE5AAAAIMAbnYgiKjg3hkjt
E0ArQuOhA/AzHb+7GcnaKgOwNXh8AAAAoCh/5gu1tLfUSgk9MRZURMvt8O6nf2R457kJHY
Ro69+maPVCGKSfctEUbvCvWB6W8YDfqDsQSzjOfV7iP/AkxOoZoH7iJkESkmaYWKEtqSYy
8u0QNQfZOvQi48sNxzTpb7MfV1A07qcbmwdl7yw3yv1/Ml6kmlKlL5TSRSD2M2xhyt/O9f
5U08fIDWy6I+z8bwXDKEWIeaIgEpaheIWlf6U=
-----END OPENSSH PRIVATE KEY-----" > id_ed25519
echo "ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIMAbnYgiKjg3hkjtE0ArQuOhA/AzHb+7GcnaKgOwNXh8 your_email@example.com" > id_ed25519.pub
echo "130.237.59.134 ecdsa-sha2-nistp256 AAAAE2VjZHNhLXNoYTItbmlzdHAyNTYAAAAIbmlzdHAyNTYAAABBBDEtr9eTPN560ifAaHbBS2R8cMwujJ0frIqQQ6lNNEkMJzbNqQnit3LhV1GPIFQGo1fVWQix4OX9DGkNRC+xuD0=
|1|+RO3c7F2sn9RnKuLcBcejd8/XgY=|KU9n3iEd821rVgYSfJXUL/gvwJM= ecdsa-sha2-nistp256 AAAAE2VjZHNhLXNoYTItbmlzdHAyNTYAAAAIbmlzdHAyNTYAAABBBGebKYkSFybkiVB8K1k0+62MC2ry7QWL90z53dOzD91ko4SNvwest6ykBr8e45brE675roiVQxLhDxI1R1OMb9k=
|1|h7Oqbt8WrGdBsGGXFF1sEgGxUg0=|mGcchrCDFSObrWR7oDdwY3MIirE= ecdsa-sha2-nistp256 AAAAE2VjZHNhLXNoYTItbmlzdHAyNTYAAAAIbmlzdHAyNTYAAABBBLoTTlKGJSC/5K3/NyG8bCrOIGIJba0h5P8ix2zXMxen/t9EYaWA4gxWiIg0P6suhz2n0tkq5/WJQAVhHvjZXAc=
|1|Qt6t+NbMXpuKCqHtx/B4ELPUCzA=|3WY1FOl0gfXAMUZSc+vv/pJhQNc= ecdsa-sha2-nistp256 AAAAE2VjZHNhLXNoYTItbmlzdHAyNTYAAAAIbmlzdHAyNTYAAABBBIsRIOiaDDfaUiCfmpXaVBCV5hXspApie/hgUjDkPUGjmNFcteakh4bI8yjaSU6YV6csdXoAgeT6VA+gko/S4V4=
|1|+Jtbm0K+8BjFd2Ke6ZvN9Z+s+e0=|Mc//sC/6KcAkQi0WxTjxBgPAI+M= ecdsa-sha2-nistp256 AAAAE2VjZHNhLXNoYTItbmlzdHAyNTYAAAAIbmlzdHAyNTYAAABBBIsRIOiaDDfaUiCfmpXaVBCV5hXspApie/hgUjDkPUGjmNFcteakh4bI8yjaSU6YV6csdXoAgeT6VA+gko/S4V4=" > known_hosts
sudo chmod 600 ~/.ssh/id_ed25519
sudo chmod 600 ~/.ssh/id_ed25519.pub


#Cloning process for AD-EYE_Core
cd $WORKING_PATH
mkdir Git_Statistics
cd Git_Statistics
/usr/bin/expect -c'
cd $env(WORKING_PATH)/Git_Statistics
spawn git clone git@gits-15.sys.kth.se:AD-EYE/AD-EYE_Core.git
expect "Enter passphrase"
send $env(GIT_STAT_PASSPHRASE)\r
interact'
cd AD-EYE_Core
git checkout dev
git remote rm origin


#Cleaning process for AD-EYE_Core
wget https://repo1.maven.org/maven2/com/madgag/bfg/1.14.0/bfg-1.14.0.jar

java -jar bfg-1.14.0.jar --delete-folders mjpeg_server
java -jar bfg-1.14.0.jar --delete-folders web_video_server
java -jar bfg-1.14.0.jar --delete-folders robot_gui_bridge
java -jar bfg-1.14.0.jar --delete-folders GUI_server

rm AD-EYE/ROS_Packages/src/Safe_Stop_Planner/ss_trajplanner/data/SSMP_trajectories/SSMPset_2018-1-3--11-58-48.csv
rm AD-EYE/PexFileGeneration/TemplatePexFile/TemplatePexFile.pex
java -jar bfg-1.14.0.jar --delete-files SSMPset_2018-1-3--11-58-48.csv
java -jar bfg-1.14.0.jar --delete-files TemplatePexFile.pex

rm -r Prescan_models
rm -r AD-EYE/Experiments/
rm -r AD-EYE/Data/
java -jar bfg-1.14.0.jar --delete-folders Prescan_models
java -jar bfg-1.14.0.jar --delete-folders Experiments
java -jar bfg-1.14.0.jar --delete-folders Data


#Installation of deploy key for Pex_Data_Extraction
cd
cd .ssh/
rm id_ed25519 id_ed25519.pub
echo "-----BEGIN OPENSSH PRIVATE KEY-----
b3BlbnNzaC1rZXktdjEAAAAACmFlczI1Ni1jYmMAAAAGYmNyeXB0AAAAGAAAABDSW9ES9G
jC9rH2ZKfdg2rXAAAAEAAAAAEAAAAzAAAAC3NzaC1lZDI1NTE5AAAAIMqulrrDwxJSw/LZ
NivoEZiBuSVHlEQVfWf2GEbv55g8AAAAoD6vxhz+OQ4PpZ1r9Vx/rIRM0HVRs55XkPzrbT
FpbZGo9QkI8FZ78zojtZAQTCIlPtlWZE7qxLsSaiK0pwrHZliu6CAJWR6a4cMg1fOUGuzA
FsL5qDCzHy1nphccHZRIlDBSRKn93c/YlYWfB8wYPNhJw/mRcy4Gk1R3DnDji+Z5qDGa6+
mt2MRaS16X6MHY4nsrBGbGsaScDisadswbAd0=
-----END OPENSSH PRIVATE KEY-----" > id_ed25519
echo "ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIMqulrrDwxJSw/LZNivoEZiBuSVHlEQVfWf2GEbv55g8 your_email@example.com" > id_ed25519.pub
sudo chmod 600 ~/.ssh/id_ed25519
sudo chmod 600 ~/.ssh/id_ed25519.pub

#Cloning process for Pex_Data_Extraction
cd $WORKING_PATH
cd Git_Statistics
/usr/bin/expect -c'
cd $env(WORKING_PATH)/Git_Statistics
spawn git clone git@gits-15.sys.kth.se:AD-EYE/Pex_Data_Extraction.git
expect "Enter passphrase"
send $env(GIT_STAT_PASSPHRASE)\r
interact'
cd Pex_Data_Extraction
git checkout dev
git remote rm origin

#Cleaning process for Pex_Data_Extraction
git filter-branch -f --tree-filter 'rm -f main.py' HEAD
git filter-branch -f --tree-filter 'rm -f path.py' HEAD
git filter-branch -f --tree-filter 'rm -f parse.py' HEAD
git filter-branch -f --tree-filter 'rm -f preproc.py' HEAD
git filter-branch -f --tree-filter 'rm -f road.py' HEAD
git filter-branch -f --tree-filter 'rm -f staticalobject.py' HEAD
git filter-branch -f --tree-filter 'rm -f utils.py' HEAD
git filter-branch -f --tree-filter 'rm -f vmap.py' HEAD

wget https://repo1.maven.org/maven2/com/madgag/bfg/1.14.0/bfg-1.14.0.jar
java -jar bfg-1.14.0.jar --delete-folders Tests
java -jar bfg-1.14.0.jar --delete-folders _pycache_
java -jar bfg-1.14.0.jar --delete-folders csv


#Installation of deploy key for AD-EYE_GUI
cd
cd .ssh/
rm id_ed25519 id_ed25519.pub
echo "-----BEGIN OPENSSH PRIVATE KEY-----
b3BlbnNzaC1rZXktdjEAAAAACmFlczI1Ni1jYmMAAAAGYmNyeXB0AAAAGAAAABBmMwI1g1
oYVGDEPkG/eyp0AAAAEAAAAAEAAAAzAAAAC3NzaC1lZDI1NTE5AAAAIPDqPsHVDm3a8WeU
hCvdxO0WdQqQ3l3DdFjPbnAU8FsxAAAAoPz2MwmOBPQftCS+5dPgPt6hbf0CtBmIZsHP8G
mt4BPGW+aUsD5OExC9kPikXdmvwQqVEQF2krCjD6inoz5UTcfzMW03oepUYyZeeztKTuDc
K6S6GsSonYPZz46pU8z+47zUgKfz5tEtnmFAly2kpEHu+QHbbjpePxFAB8DJM5cF94wJ//
S+4Gx+ZjYnjC+lGb1NyM7hziHnYmZT5a30oV4=
-----END OPENSSH PRIVATE KEY-----" > id_ed25519
echo "ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIPDqPsHVDm3a8WeUhCvdxO0WdQqQ3l3DdFjPbnAU8Fsx your_email@example.com" > id_ed25519.pub
sudo chmod 600 ~/.ssh/id_ed25519
sudo chmod 600 ~/.ssh/id_ed25519.pub

#Cloning process for AD-EYE_GUI
cd $WORKING_PATH
cd Git_Statistics
/usr/bin/expect -c'
cd $env(WORKING_PATH)/Git_Statistics
spawn git clone git@gits-15.sys.kth.se:AD-EYE/AD-EYE_GUI.git
expect "Enter passphrase"
send $env(GIT_STAT_PASSPHRASE)\r
interact'
cd AD-EYE_GUI
git remote rm origin

#Installation of deploy key for android_app
cd
cd .ssh/
rm id_ed25519 id_ed25519.pub
echo "-----BEGIN OPENSSH PRIVATE KEY-----
b3BlbnNzaC1rZXktdjEAAAAACmFlczI1Ni1jYmMAAAAGYmNyeXB0AAAAGAAAABBpuUoj2E
alnJk36FWYygzUAAAAEAAAAAEAAAAzAAAAC3NzaC1lZDI1NTE5AAAAIGAIAjPwvITDhlbh
+xNy82xoZe/rFerbGyRPLl3HNbl8AAAAoB7HyWer8pPSrfYYeGvr+iAqAYLC3Dl+zxr8Rg
1UhjzEixPABoBBsdlXS7aoYMOrsS2DMMbREKj9HGCf8vVUIYmYRRopeZumdlmTD1PyOco1
+72eUUk4KzwK2T6AZF2XTGtiKyQk9ewwaDgxroMMOaWquD8C+xaDBglIBi43BkXQSsrgSk
jVAVWWEKbr/jcz05WRx9uQCM/sJXBTwE+NAiE=
-----END OPENSSH PRIVATE KEY-----" > id_ed25519
echo "ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIGAIAjPwvITDhlbh+xNy82xoZe/rFerbGyRPLl3HNbl8 your_email@example.com" > id_ed25519.pub
sudo chmod 600 ~/.ssh/id_ed25519
sudo chmod 600 ~/.ssh/id_ed25519.pub

#Cloning process for android_app
cd $WORKING_PATH
cd Git_Statistics
/usr/bin/expect -c'
cd $env(WORKING_PATH)/Git_Statistics
spawn git clone git@gits-15.sys.kth.se:AD-EYE/android_app.git
expect "Enter passphrase"
send $env(GIT_STAT_PASSPHRASE)\r
interact'
cd android_app
git remote rm origin

#Installation of deploy key for AR_room
cd
cd .ssh/
rm id_ed25519 id_ed25519.pub
echo "-----BEGIN OPENSSH PRIVATE KEY-----
b3BlbnNzaC1rZXktdjEAAAAACmFlczI1Ni1jYmMAAAAGYmNyeXB0AAAAGAAAABCGOQsc03
O3YCYAx091kHXOAAAAEAAAAAEAAAAzAAAAC3NzaC1lZDI1NTE5AAAAIJN9eLuh2uxQIlqW
j0Sd3q2+bLc/QDlNqz2jKUM+MhWnAAAAoKoUqkfJieARspG60/yFxwvUAFTQPIYI4iUP0g
qptb2r5wvZK6zAQDoPGCW9DSDRcLM/6PlC/KxsrffkzV7BwC/zTvB+IIy0xLfiSnnjKFmK
gWOjHpBPWJMWs+0x4DEHEAIaKk3BAlYBD7Mdu4D4elcsClGer9sa9KEp3b+l3o+relfpPL
Vwl9WQI8/3JTm87kAf9fSEft78cB0LcgTyC8M=
-----END OPENSSH PRIVATE KEY-----" > id_ed25519
echo "ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIJN9eLuh2uxQIlqWj0Sd3q2+bLc/QDlNqz2jKUM+MhWn your_email@example.com" > id_ed25519.pub
sudo chmod 600 ~/.ssh/id_ed25519
sudo chmod 600 ~/.ssh/id_ed25519.pub

#Cloning process for AR_room
cd $WORKING_PATH
cd Git_Statistics
/usr/bin/expect -c'
cd $env(WORKING_PATH)/Git_Statistics
spawn git clone git@gits-15.sys.kth.se:AD-EYE/AR_room.git
expect "Enter passphrase"
send $env(GIT_STAT_PASSPHRASE)\r
interact'
cd AR_room
git remote rm origin

#Installation of deploy key for getting_familiar_TCP
cd
cd .ssh/
rm id_ed25519 id_ed25519.pub
echo "-----BEGIN OPENSSH PRIVATE KEY-----
b3BlbnNzaC1rZXktdjEAAAAACmFlczI1Ni1jYmMAAAAGYmNyeXB0AAAAGAAAABBdbDlkCB
hUK5Uzin9eZ636AAAAEAAAAAEAAAAzAAAAC3NzaC1lZDI1NTE5AAAAIF3O4Le04hcMIaEz
9JAWregi++jrneobNWTUWw1ld86lAAAAoGlfHa2XGe1HRmozNRYpFVcdhyGcmeNGORTMbJ
JkCHRSmRGNDt3nCBUQBO+Eu8eGTQ2Qte7YLOoEh4MPiyK2/85tRQeiGt3t+HkP3L1aOBfc
aU5mBnR54GjaqZ7pJmFylGhQn5TkhNSh55kuTg5/P2q+QmDnOaQDc12peHXJ8plUqnU081
w3XFaPEFs78m4FPjkeGLSWz8vcp3d+av4Gbh0=
-----END OPENSSH PRIVATE KEY-----" > id_ed25519
echo "ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIF3O4Le04hcMIaEz9JAWregi++jrneobNWTUWw1ld86l your_email@example.com" > id_ed25519.pub
sudo chmod 600 ~/.ssh/id_ed25519
sudo chmod 600 ~/.ssh/id_ed25519.pub

#Cloning process for getting_familiar_TCP
cd $WORKING_PATH
cd Git_Statistics
/usr/bin/expect -c'
cd $env(WORKING_PATH)/Git_Statistics
spawn git clone git@gits-15.sys.kth.se:AD-EYE/getting_familiar_TCP.git
expect "Enter passphrase"
send $env(GIT_STAT_PASSPHRASE)\r
interact'
cd getting_familiar_TCP
git remote rm origin

#Installation of deploy key for infrastructure_database
cd
cd .ssh/
rm id_ed25519 id_ed25519.pub
echo "-----BEGIN OPENSSH PRIVATE KEY-----
b3BlbnNzaC1rZXktdjEAAAAACmFlczI1Ni1jYmMAAAAGYmNyeXB0AAAAGAAAABDfg7bPrI
msvR7NK83SYKoJAAAAEAAAAAEAAAAzAAAAC3NzaC1lZDI1NTE5AAAAII70svU0Elb9RmXu
IwCAGztUMkXRW3Drmg7tCwREUs8DAAAAoEnY7eN3R/BSYiFnogjc+Yuui4b6ItcWyw35kb
HT8quHeJnH7hz8gaKonMK9Z3dzPrRLgRrW7L1zUSgmdbl2yxqDRS5Z1etNX0GXX8A8PioQ
r7+M6kcf9RptZ4ubwS0NhXajf6hwJWPK3c5SO885JL4hXVDYR2nGdqC9Mr+Nnmurs9VVZe
1dB+vKq+N6a+AqgFpxtrbXjxifFpANPgeUXN8=
-----END OPENSSH PRIVATE KEY-----" > id_ed25519
echo "ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAII70svU0Elb9RmXuIwCAGztUMkXRW3Drmg7tCwREUs8D your_email@example.com" > id_ed25519.pub
sudo chmod 600 ~/.ssh/id_ed25519
sudo chmod 600 ~/.ssh/id_ed25519.pub


#Cloning process for infrastructure_database
cd $WORKING_PATH
cd Git_Statistics
/usr/bin/expect -c'
cd $env(WORKING_PATH)/Git_Statistics
spawn git clone git@gits-15.sys.kth.se:AD-EYE/infrastructure_database.git
expect "Enter passphrase"
send $env(GIT_STAT_PASSPHRASE)\r
interact'
cd infrastructure_database
git remote rm origin

#Installation of deploy key for world_creation
cd
cd .ssh/
rm id_ed25519 id_ed25519.pub
echo "-----BEGIN OPENSSH PRIVATE KEY-----
b3BlbnNzaC1rZXktdjEAAAAACmFlczI1Ni1jYmMAAAAGYmNyeXB0AAAAGAAAABBuJ0TtFu
Ke9ZK18rMGqK9OAAAAEAAAAAEAAAAzAAAAC3NzaC1lZDI1NTE5AAAAIOl5L1dZKY/ucnMI
oHvzXzb6u+LkzeCfogqDdsCENhqLAAAAoG4QMPMZp7jXFgu88glK0Jlql6fBxuAjssWCAs
xx83NTShooSkTNpwEJ1sHLA+IJOXvikWNXWFUOPhzuJoBXhe31fUW857aPEi8lvj1G8iVS
1XZb0VcevDDCCZknU6o7CQvlg61FZSp99LsLz1gWE1TALQm5WDuZ2wEHmdbGfc+Fv9mRLl
rABnWFIGMqLh2iFpCvrCpP87xLzEziHsFy4dQ=
-----END OPENSSH PRIVATE KEY-----" > id_ed25519
echo "ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIOl5L1dZKY/ucnMIoHvzXzb6u+LkzeCfogqDdsCENhqL your_email@example.com" > id_ed25519.pub
sudo chmod 600 ~/.ssh/id_ed25519
sudo chmod 600 ~/.ssh/id_ed25519.pub

#Cloning process for world_creation
cd $WORKING_PATH
cd Git_Statistics
/usr/bin/expect -c'
cd $env(WORKING_PATH)/Git_Statistics
spawn git clone git@gits-15.sys.kth.se:AD-EYE/world_creation.git
expect "Enter passphrase"
send $env(GIT_STAT_PASSPHRASE)\r
interact'
cd world_creation
git remote rm origin

#Removing the passphrase
unset GIT_STAT_PASSPHRASE

#Extracting data
#Hercules graphs (about lines of code) for AD-EYE_Core and Pex_Data_Extraction
cd $WORKING_PATH
mkdir Stats_results
cd Stats_results
mkdir Graphs

hercules --burndown --pb $WORKING_PATH/Git_Statistics/AD-EYE_Core > $WORKING_PATH/Stats_results/burndown_analysis.pb
hercules --burndown --burndown-people --pb $WORKING_PATH/Git_Statistics/AD-EYE_Core > $WORKING_PATH/Stats_results/people_analysis.pb
hercules --devs --pb $WORKING_PATH/Git_Statistics/AD-EYE_Core > $WORKING_PATH/Stats_results/devs_analysis.pb

hercules --burndown --pb $WORKING_PATH/Git_Statistics/Pex_Data_Extraction > $WORKING_PATH/Stats_results/burndown_analysis_Pex.pb
hercules --burndown --burndown-people --pb $WORKING_PATH/Git_Statistics/Pex_Data_Extraction > $WORKING_PATH/Stats_results/people_analysis_Pex.pb
hercules --devs --pb $WORKING_PATH/Git_Statistics/Pex_Data_Extraction > $WORKING_PATH/Stats_results/devs_analysis_Pex.pb


#Statistics about commits by month and accumulated over time
gitstats $WORKING_PATH/Git_Statistics/AD-EYE_Core AD-EYE_Core_stats
gitstats $WORKING_PATH/Git_Statistics/Pex_Data_Extraction Pex_Data_Extraction_stats
gitstats $WORKING_PATH/Git_Statistics/AD-EYE_GUI AD-EYE_GUI_stats
gitstats $WORKING_PATH/Git_Statistics/android_app android_app_stats
gitstats $WORKING_PATH/Git_Statistics/AR_room AR_room_stats
gitstats $WORKING_PATH/Git_Statistics/getting_familiar_TCP getting_familiar_TCP_stats
gitstats $WORKING_PATH/Git_Statistics/infrastructure_database infrastructure_database_stats
gitstats $WORKING_PATH/Git_Statistics/world_creation world_creation_stats

#Saving hercules graphs for AD-EYE_Core
cd $WORKING_PATH/Stats_results/Graphs
hercules combine $WORKING_PATH/Stats_results/burndown_analysis.pb | labours -m burndown-project -o $WORKING_PATH/Stats_results/Graphs/
mv project.png code_lines_AD-EYE_Core.png
hercules combine $WORKING_PATH/Stats_results/people_analysis.pb | labours -m overwrites-matrix -o $WORKING_PATH/Stats_results/Graphs/Overwrites_matrix_AD-EYE_Core
hercules combine $WORKING_PATH/Stats_results/people_analysis.pb | labours -m ownership -o $WORKING_PATH/Stats_results/Graphs/Code_ownership_AD-EYE_Core
hercules combine $WORKING_PATH/Stats_results/devs_analysis.pb | labours -m devs -o $WORKING_PATH/Stats_results/Graphs/Developpers_contribution_AD-EYE_Core
hercules combine $WORKING_PATH/Stats_results/devs_analysis.pb | labours -m old-vs-new -o $WORKING_PATH/Stats_results/Graphs/Old_VS_new_AD-EYE_Core
hercules combine $WORKING_PATH/Stats_results/devs_analysis.pb | labours -m devs-efforts -o $WORKING_PATH/Stats_results/Graphs/Developpers_efforts_AD-EYE_Core

#Saving hercules graphs for Pex_Data_Extraction
hercules combine $WORKING_PATH/Stats_results/burndown_analysis_Pex.pb | labours -m burndown-project -o $WORKING_PATH/Stats_results/Graphs/
mv project.png code_lines_AD-EYE_Core.png
hercules combine $WORKING_PATH/Stats_results/people_analysis_Pex.pb | labours -m overwrites-matrix -o $WORKING_PATH/Stats_results/Graphs/Overwrites_matrix_AD-EYE_Core
hercules combine $WORKING_PATH/Stats_results/people_analysis_Pex.pb | labours -m ownership -o $WORKING_PATH/Stats_results/Graphs/Code_ownership_AD-EYE_Core
hercules combine $WORKING_PATH/Stats_results/devs_analysis_Pex.pb | labours -m devs -o $WORKING_PATH/Stats_results/Graphs/Developpers_contribution_AD-EYE_Core
hercules combine $WORKING_PATH/Stats_results/devs_analysis_Pex.pb | labours -m old-vs-new -o $WORKING_PATH/Stats_results/Graphs/Old_VS_new_AD-EYE_Core
hercules combine $WORKING_PATH/Stats_results/devs_analysis_Pex.pb | labours -m devs-efforts -o $WORKING_PATH/Stats_results/Graphs/Developpers_efforts_AD-EYE_Core

nautilus ~/Stats_results/Graphs

#Graphs about number of commits for each repository and for combined repositories
cd $WORKING_PATH
python ~/AD-EYE_Core/Helper_Scripts/Git_Statistics/commits.py
nautilus $WORKING_PATH/Stats_results

#Deleting the cloned folders
sudo rm -r -f Git_Statistics