
from rosbag import Bag
with Bag('cam_si_ri_l.bag', 'w') as Y:
	for topic, msg, t in Bag('cam_side_right_lidar.bag'):
    		if topic == '/a2d2/20180810_150607_cam_side_right/lidar':
       			 Y.write('/scan', msg, t)
    		else:
       			 Y.write(topic, msg, t)
