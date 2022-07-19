#!/bin/sh
cd ~/AD-EYE_Core || git config --global --remove-section user || git config --local --remove-section user
cd ~/AD-EYE_Core/autoware.ai/src/autoware/common || git config --local --remove-section user 
cd ~/AD-EYE_Core/autoware.ai/src/autoware/core_perception || git config --local --remove-section user
cd ~/AD-EYE_Core/autoware.ai/src/autoware/core_planning || git config --local --remove-section user
cd ~/AD-EYE_Core/autoware.ai/src/autoware/documentation || git config --local --remove-section user
cd ~/AD-EYE_Core/autoware.ai/src/autoware/messages || git config --local --remove-section user
cd ~/AD-EYE_Core/autoware.ai/src/autoware/simulation ||git config --local --remove-section user
cd ~/AD-EYE_Core/autoware.ai/src/autoware/utilities ||git config --local --remove-section user
cd ~/AD-EYE_Core/autoware.ai/src/autoware/visualization || git config --local --remove-section user
cd ~/AD-EYE_Core/Pex_Data_Extraction || git config --local --remove-section user
cd ~
