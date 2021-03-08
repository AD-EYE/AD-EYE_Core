ZIP_FILEPATH="$1"
PRESCAN_EXPERIMENT_FOLDER="Experiment"
EXPERIMENT_NAME="Experiment"
PRESCANRUN_PATH="/usr/local/Prescan_2020.1.0/bin/"

Help()
{
   # Display Help
   echo "Unzips and builds the experiment (first build or if there are modifications). "
   echo "Then, runs the experiment"
   echo
   echo "Syntax: build_and_run_experiment [ZIP_FILEPATH] [-h]"
   echo "options:"
   echo "h     Print help."
   echo
}

if [ "$1" == "-h" ] ; then
    Help
    exit 0
fi

original_path=(`pwd`)
path=(`dirname "${ZIP_FILEPATH}"`)
filename=(`basename "${ZIP_FILEPATH}"`)

cd ${path}

if [ -d ${PRESCAN_EXPERIMENT_FOLDER} ]
then
    echo "Seems like the directories already exist. Won't unzip..."
else
    unzip ${filename}
fi

cd ${PRESCAN_EXPERIMENT_FOLDER}
cp -a ${original_path}/fix_path.py .
./fix_path.py --experiment-name ${EXPERIMENT_NAME}

cd ${EXPERIMENT_NAME}_cs_ps_rtw
make -f make_ps_linux.mk
cd ../
${PRESCANRUN_PATH}./prescanrun ./${EXPERIMENT_NAME}_cs
