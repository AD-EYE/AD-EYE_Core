#!/usr/bin/expect -f


echo "Checking common:"
cd ../autoware.ai/src/autoware/common/
git checkout dev
git pull

echo "Checking core_perception:"
cd ../core_perception/
git checkout dev
git pull

echo "Checking core_planning:"
cd ../core_planning/
git checkout dev
git pull


## More repositories can be added as needed

# echo "Checking documentation:"
# cd ../documentation/
# git pull

# echo "Checking messages:"
# cd ../messages/
# git pull

# echo "Checking simulation:"
# cd ../simulation/
# git pull

# echo "Checking utilities:"
# cd ../utilities/
# git pull

# echo "Checking visualization:"
# cd ../visualization/
# git pull



