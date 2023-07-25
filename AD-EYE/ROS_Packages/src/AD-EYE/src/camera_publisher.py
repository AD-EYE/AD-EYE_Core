#!/usr/bin/env python

# source: https://github.com/stereolabs/zed-opencv-native/blob/master/python/zed_opencv_native.py

import numpy as np
import os
import ConfigParser
import sys
import cv2

import rospy
from cv_bridge import CvBridge
from sensor_msgs.msg import Image


# ZED1 SN:
#SERIAL_NUMBER = 21126

# ZED2 SN:
SERIAL_NUMBER = 23817167

def start_node():
    rospy.init_node('camera_pub')
    rospy.loginfo('camera_pub node started')


def load_calibration_file(serial_number) :
    calibration_file = "../AD-EYE_Core/AD-EYE/ROS_Packages/src/AD-EYE/src/" + 'SN' + str(serial_number) + '.conf'

    if os.path.isfile(calibration_file) == True:
        print("Calibration file found. Loading...")
    
    else:
        print("Calibration file \"" + calibration_file + "\" not found.")
        print("It can be downloaded from: calib.stereolabs.com/?SN=" + str(SERIAL_NUMBER))

    return calibration_file


def init_calibration(calibration_file, image_size) :

    cameraMarix_left = cameraMatrix_right = map_left_y = map_left_x = map_right_y = map_right_x = np.array([])

    config = ConfigParser.RawConfigParser()
    config.read(calibration_file)


    check_data = True
    resolution_str = ''
    if image_size.width == 2208 :
        resolution_str = '2K'
    elif image_size.width == 1920 :
        resolution_str = 'FHD'
    elif image_size.width == 1280 :
        resolution_str = 'HD'
    elif image_size.width == 672 : 
        resolution_str = 'VGA'
    else:
        resolution_str = 'HD'
        check_data = False


    T_ = np.array([config.getfloat('STEREO', 'Baseline'),
                   config.getfloat('STEREO', 'TY_' + resolution_str) if config.has_option('STEREO', 'TY_' + resolution_str) else 0.,
                   config.getfloat('STEREO', 'TZ_' + resolution_str) if config.has_option('STEREO', 'TZ_' + resolution_str) else 0.])

    left_cam_cx = config.getfloat('LEFT_CAM_' + resolution_str, 'cx') if config.has_option('LEFT_CAM_' + resolution_str, 'cx') else 0.
    left_cam_cy = config.getfloat('LEFT_CAM_' + resolution_str, 'cy') if config.has_option('LEFT_CAM_' + resolution_str, 'cy') else 0.
    left_cam_fx = config.getfloat('LEFT_CAM_' + resolution_str, 'fx') if config.has_option('LEFT_CAM_' + resolution_str, 'fx') else 0.
    left_cam_fy = config.getfloat('LEFT_CAM_' + resolution_str, 'fy') if config.has_option('LEFT_CAM_' + resolution_str, 'fy') else 0.
    left_cam_k1 = config.getfloat('LEFT_CAM_' + resolution_str, 'k1') if config.has_option('LEFT_CAM_' + resolution_str, 'k1') else 0.
    left_cam_k2 = config.getfloat('LEFT_CAM_' + resolution_str, 'k2') if config.has_option('LEFT_CAM_' + resolution_str, 'k2') else 0.
    left_cam_p1 = config.getfloat('LEFT_CAM_' + resolution_str, 'p1') if config.has_option('LEFT_CAM_' + resolution_str, 'p1') else 0.
    left_cam_p2 = config.getfloat('LEFT_CAM_' + resolution_str, 'p2') if config.has_option('LEFT_CAM_' + resolution_str, 'p2') else 0.
    left_cam_p3 = config.getfloat('LEFT_CAM_' + resolution_str, 'p3') if config.has_option('LEFT_CAM_' + resolution_str, 'p3') else 0.
    left_cam_k3 = config.getfloat('LEFT_CAM_' + resolution_str, 'k3') if config.has_option('LEFT_CAM_' + resolution_str, 'k3') else 0.

    right_cam_cx = config.getfloat('RIGHT_CAM_' + resolution_str, 'cx') if config.has_option('RIGHT_CAM_' + resolution_str, 'cx') else 0.
    right_cam_cy = config.getfloat('RIGHT_CAM_' + resolution_str, 'cy') if config.has_option('RIGHT_CAM_' + resolution_str, 'cy') else 0.
    right_cam_fx = config.getfloat('RIGHT_CAM_' + resolution_str, 'fx') if config.has_option('RIGHT_CAM_' + resolution_str, 'fx') else 0.
    right_cam_fy = config.getfloat('RIGHT_CAM_' + resolution_str, 'fy') if config.has_option('RIGHT_CAM_' + resolution_str, 'fy') else 0.
    right_cam_k1 = config.getfloat('RIGHT_CAM_' + resolution_str, 'k1') if config.has_option('RIGHT_CAM_' + resolution_str, 'k1') else 0.
    right_cam_k2 = config.getfloat('RIGHT_CAM_' + resolution_str, 'k2') if config.has_option('RIGHT_CAM_' + resolution_str, 'k2') else 0.
    right_cam_p1 = config.getfloat('RIGHT_CAM_' + resolution_str, 'p1') if config.has_option('RIGHT_CAM_' + resolution_str, 'p1') else 0.
    right_cam_p2 = config.getfloat('RIGHT_CAM_' + resolution_str, 'p2') if config.has_option('RIGHT_CAM_' + resolution_str, 'p2') else 0.
    right_cam_p3 = config.getfloat('RIGHT_CAM_' + resolution_str, 'p3') if config.has_option('RIGHT_CAM_' + resolution_str, 'p3') else 0.
    right_cam_k3 = config.getfloat('RIGHT_CAM_' + resolution_str, 'k3') if config.has_option('RIGHT_CAM_' + resolution_str, 'k3') else 0.

    R_zed = np.array([config.getfloat('STEREO', 'rx_' + resolution_str.lower()) if config.has_option('STEREO', 'rx_' + resolution_str.lower()) else 0.,
                   config.getfloat('STEREO', 'cv_' + resolution_str.lower()) if config.has_option('STEREO', 'cv_' + resolution_str.lower()) else 0.,
                   config.getfloat('STEREO', 'rz_' + resolution_str.lower()) if config.has_option('STEREO', 'rz_' + resolution_str.lower()) else 0.])


    R, _ = cv2.Rodrigues(R_zed)
    cameraMatrix_left = np.array([[left_cam_fx, 0, left_cam_cx],
                         [0, left_cam_fy, left_cam_cy],
                         [0, 0, 1]])

    cameraMatrix_right = np.array([[right_cam_fx, 0, right_cam_cx],
                          [0, right_cam_fy, right_cam_cy],
                          [0, 0, 1]])

    distCoeffs_left = np.array([[left_cam_k1], [left_cam_k2], [left_cam_p1], [left_cam_p2], [left_cam_k3]])

    distCoeffs_right = np.array([[right_cam_k1], [right_cam_k2], [right_cam_p1], [right_cam_p2], [right_cam_k3]])

    T = np.array([[T_[0]], [T_[1]], [T_[2]]])
    R1 = R2 = P1 = P2 = np.array([])

    R1, R2, P1, P2 = cv2.stereoRectify(cameraMatrix1=cameraMatrix_left,
                                       cameraMatrix2=cameraMatrix_right,
                                       distCoeffs1=distCoeffs_left,
                                       distCoeffs2=distCoeffs_right,
                                       R=R, T=T,
                                       flags=cv2.CALIB_ZERO_DISPARITY,
                                       alpha=0,
                                       imageSize=(image_size.width, image_size.height),
                                       newImageSize=(image_size.width, image_size.height))[0:4]

    map_left_x, map_left_y = cv2.initUndistortRectifyMap(cameraMatrix_left, distCoeffs_left, R1, P1, (image_size.width, image_size.height), cv2.CV_32FC1)
    map_right_x, map_right_y = cv2.initUndistortRectifyMap(cameraMatrix_right, distCoeffs_right, R2, P2, (image_size.width, image_size.height), cv2.CV_32FC1)

    cameraMatrix_left = P1
    cameraMatrix_right = P2

    return cameraMatrix_left, cameraMatrix_right, map_left_x, map_left_y, map_right_x, map_right_y


# 2K: 2208.1242; FHD: 1920.1080; HD: 1280.720
class Resolution :
    def __init__(self, width, height):
        self.width = width
        self.height = height


def main() :

    try:
        start_node()
    except rospy.ROSInterruptException:
        pass

    # Open the ZED camera
    cap = cv2.VideoCapture(0)

    # Check for correct initialization
    if cap.isOpened() == 0:
        print("Video capture initialization fail")
        exit(-1)
    else :
        print("Starting video capture")

    # Set the video resolution
    image_size = Resolution(1920, 1080)
    cap.set(cv2.CAP_PROP_FRAME_WIDTH, image_size.width * 2)
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, image_size.height)

    print("Image resolution set to " + str(image_size.width) + "*" + str(image_size.height))

    # Open calibration file
    calibration_file = load_calibration_file(SERIAL_NUMBER)

    # Compute calibration
    camera_matrix_left, camera_matrix_right, map_left_x, map_left_y, map_right_x, map_right_y = init_calibration(calibration_file, image_size)

    print("Calibration initiated")

    bridge = CvBridge()
    left_pub = rospy.Publisher('/camera_1/image_raw', Image, queue_size=10)
    right_pub = rospy.Publisher('/camera_2/image_raw', Image, queue_size=10)

    while not rospy.is_shutdown():
        # Get a new frame from camera
        retval, frame = cap.read()
        # Extract left and right images from side-by-side
        left_right_image = np.split(frame, 2, axis=1)

        # Raw images
        #cv2.imshow("left RAW", left_right_image[0])
        #cv2.imshow("right RAW", left_right_image[1])

        # Rectified images
        left_rect = cv2.remap(left_right_image[0], map_left_x, map_left_y, interpolation=cv2.INTER_LINEAR)
        right_rect = cv2.remap(left_right_image[1], map_right_x, map_right_y, interpolation=cv2.INTER_LINEAR)

        # Converting OpenCV image to ROS image message
        left_msg = bridge.cv2_to_imgmsg(left_rect, "bgr8")
        right_msg = bridge.cv2_to_imgmsg(right_rect, "bgr8")

        # Publishing both frames
        left_pub.publish(left_msg)
        right_pub.publish(right_msg)


if __name__ == "__main__":
    main()
