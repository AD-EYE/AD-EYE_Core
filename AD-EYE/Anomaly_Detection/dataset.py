import sys
# print(sys.path)
if '/opt/ros/kinetic/lib/python2.7/dist-packages' in sys.path:
    sys.path.remove('/opt/ros/kinetic/lib/python2.7/dist-packages')
# sys.path.remove('/opt/ros/kinetic/lib/python2.7/dist-packages')


import os
import argparse
# import numpy as np 
# import pandas as pd
# import matplotlib.pyplot as plt
import tensorflow as tf
print(tf.__version__)

import cv2

# from tensorflow.keras.models import Model
# from sklearn.model_selection import train_test_split
# from sklearn.metrics import classification_report
# from imutils import paths

def showVideo(path_to_file):
    clean_video = cv2.VideoCapture(path_to_file)

    if clean_video.isOpened() == False:
        print("Error opening video stream or file")

    while clean_video.isOpened():
        ret, frame = clean_video.read()
        if ret:
            cv2.imshow('Frame', frame)
            if cv2.waitKey(25) & 0xFF == ord('q'):
                break
        else:
            break
    cv2.destroyAllWindows()


def createDirectories():
    path_to_working_directory = os.getcwd()
    if os.path.exists(os.path.join(path_to_working_directory,'dataset')):
        pass  
    else:
        os.mkdir(os.path.join(path_to_working_directory, 'dataset'))

    dataset_path = os.path.join(path_to_working_directory, 'dataset')

    if os.path.exists(os.path.join(dataset_path, 'images')):
        pass
    else: 
        os.mkdir(os.path.join(dataset_path, 'images'))
    images_path = os.path.join(dataset_path, 'images')

    if os.path.exists(os.path.join(dataset_path, 'anomaly_images')):
        pass
    else: 
        os.mkdir(os.path.join(dataset_path, 'anomaly_images'))
    anomaly_images_path = os.path.join(dataset_path, 'anomaly_images')

    if os.path.exists(os.path.join(path_to_working_directory, "models")):
        pass
    else:
        os.mkdir(os.path.join(path_to_working_directory, "models"))
    models_path = os.path.join(path_to_working_directory, "models")

    if os.path.exists(os.path.join(models_path, "autoencoder")):
        pass
    else:
        os.mkdir(os.path.join(models_path, "autoencoder"))
    autoencoder_path = os.path.join(models_path, "autoencoder")

    if os.path.exists(os.path.join(models_path, "supervised_model")):
        pass
    else:
        os.mkdir(os.path.join(models_path, "supervised_model"))
    supervised_model_path = os.path.join(models_path, "supervised_model")

    return dataset_path, images_path, anomaly_images_path, models_path, autoencoder_path, supervised_model_path

def getImagesFromVideo(path_to_clean_images, path_to_anomaly_images, dataset_path, images_path, anomaly_images_path):

    clean_video = cv2.VideoCapture(path_to_clean_images)
    ret, frame = clean_video.read()
    count = 0
    while ret:

        cv2.imwrite(os.path.join(images_path, "images{}.jpg".format(count)), frame)
        ret, frame = clean_video.read()
        count += 1
    print("Done reading {} frames from file {}".format(count, path_to_clean_images))

    anomalous_video = cv2.VideoCapture(path_to_anomaly_images)
    ret, frame = anomalous_video.read()
    count = 0
    while ret:
        cv2.imwrite(os.path.join(anomaly_images_path, "anomaly_images{}.jpg".format(count)), frame)
        ret, frame = anomalous_video.read()
        count += 1
    print("Done reading {} frames from file {}".format(count, path_to_anomaly_images))


def main():

    parser = argparse.ArgumentParser(description="paths to each dataset")
    parser.add_argument('--clean_path', type = str, help = 'path to clean dataset')
    parser.add_argument('--anomaly_path', type = str, help = 'path to anomolous dataset')
    args = parser.parse_args()


    if args.clean_path:
        path_video_clean_data = args.clean_path
        path_video_anomaly_data = args.anomaly_path
    else:
        path_video_clean_data = '/home/adeye/AD-EYE_Core/AD-EYE/Experiments/SimpleExperiment/clean_output.avi'
        path_video_anomaly_data = '/home/adeye/AD-EYE_Core/AD-EYE/Experiments/SimpleTestExperiment/anomaly_output.avi'

    # showVideo(path_video_anomaly_data)
    dataset_path, images_path, anomaly_images_path, models_path, autoencoder_path, supervised_model_path = createDirectories()

    getImagesFromVideo(path_video_clean_data, path_video_anomaly_data, dataset_path, images_path, anomaly_images_path)

if __name__=='__main__':
    main()
