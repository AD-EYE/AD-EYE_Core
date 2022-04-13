#!/usr/bin/env python
# coding: utf-8

# In[1]:


import sys
# print(sys.path)
sys.path.remove('/opt/ros/kinetic/lib/python2.7/dist-packages')


# In[2]:


import numpy as np 
import pandas as pd
import matplotlib.pyplot as plt
import tensorflow as tf

import cv2

from tensorflow.keras.models import Model
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report
from imutils import paths


# In[3]:


print(tf.__version__)


# In[1]:


import sys
# print(sys.path)
sys.path.remove('/opt/ros/kinetic/lib/python2.7/dist-packages')


# In[2]:



import os
import argparse
import numpy as np 
import pandas as pd
import matplotlib.pyplot as plt
import tensorflow as tf
print(tf.__version__)

import cv2

from tensorflow.keras.models import Model
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report
from imutils import paths


get_ipython().system('pip freeze > requirements_freeze.txt')
get_ipython().system('conda env export > environment.yml')
get_ipython().system('jupyter nbconvert --to script ad_22032022.ipynb')
get_ipython().system('pipreqs --force --encoding utf-8 "/home/adeye/AD-EYE_Core/AD-EYE/Anomaly_Detection/" ')


# In[ ]:


parser = argparse.ArgumentParser()


# ## Data Processing

# In[9]:


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


# In[65]:


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


# In[66]:





# In[67]:


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


# In[16]:


def getData(path_to_file, image_size, convert_color = 0):
    imagePaths = list(paths.list_images(path_to_file))
    data = []
    for imagePath in imagePaths:
        image = cv2.imread(imagePath)
        if convert_color == 1:
            image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        image = cv2.resize(image, (image_size, image_size))
        data.append(image)
    data = np.array(data).astype('float32') / 255.
    print("Done creating data for file {}".format(path_to_file))
    visualize_sample = 0
    if visualize_sample == 1:
        cv2.imshow("data", data[0])
        cv2.waitKey(0)
        cv2.destroyAllWindows()
    return data


# In[69]:


path_video_clean_data = '/home/adeye/AD-EYE_Core/AD-EYE/Experiments/SimpleExperiment/clean_output.avi'
path_video_anomaly_data = '/home/adeye/AD-EYE_Core/AD-EYE/Experiments/SimpleTestExperiment/anomaly_output.avi'

# showVideo(path_video_anomaly_data)
dataset_path, images_path, anomaly_images_path, models_path, autoencoder_path, supervised_model_path = createDirectories()

getImagesFromVideo(path_video_clean_data, path_video_anomaly_data, dataset_path, images_path, anomaly_images_path)


# ## Autoencoder

# In[41]:


class AnomalyDetector(Model):
    def __init__(self, image_size, hidden_layer_1, hidden_layer_2, channels):
        super(AnomalyDetector, self).__init__()
        self.encoder = tf.keras.Sequential([
            tf.keras.layers.InputLayer(input_shape = (image_size, image_size, channels)),
            tf.keras.layers.Conv2D(hidden_layer_1, (3, 3), padding = 'same', strides = 2), 
            # tf.keras.layers.BatchNormalization(),
            tf.keras.layers.LeakyReLU(),
            tf.keras.layers.Conv2D(hidden_layer_2, (3, 3), padding = 'same', strides = 2), 
            # tf.keras.layers.BatchNormalization(),
            tf.keras.layers.LeakyReLU(), 
        ])

        self.decoder = tf.keras.Sequential([
            tf.keras.layers.Conv2DTranspose(hidden_layer_2, kernel_size=3, padding = 'same', strides = 2), 
            tf.keras.layers.LeakyReLU(),
            tf.keras.layers.Conv2DTranspose(hidden_layer_1, kernel_size=3, padding = 'same', strides = 2),
            tf.keras.layers.LeakyReLU(),
            tf.keras.layers.Conv2DTranspose(channels, 3, padding = 'same', activation = 'sigmoid'),
            # tf.keras.layers.Conv2D(channels, (3, 3), activation = 'sigmoid', padding = 'same')
        ]) 

    def call(self, x):
        encoded = self.encoder(x)
        decoded = self.decoder(encoded)
        return decoded



# In[42]:


def splitDataAutoencoder(data):
    train_data, test_data = train_test_split(data, test_size = 0.2, random_state=42)
    train_data = tf.cast(train_data, tf.float32)
    test_data = tf.cast(test_data, tf.float32)
    if data.shape[-1] != 3:
        train_data = train_data[..., tf.newaxis]
        test_data = test_data[..., tf.newaxis]
    return train_data, test_data

    


# In[43]:


def trainModel(model, epochs, batch_size, optimizer, loss, metrics):
    model.compile(
        optimizer=optimizer,
        loss=loss,
        metrics=metrics,
    )
    history = model.fit(
        normal_train_data, normal_train_data,
        epochs=epochs,
        batch_size=batch_size,
        validation_data=(normal_test_data, normal_test_data),
        shuffle=True
    )
    plt.plot(history.history["loss"], label="Training Loss")
    plt.plot(history.history["val_loss"], label="Validation Loss")
    plt.legend()
    plt.show()

    print(model.encoder.summary())
    print(model.decoder.summary())

    return history


# In[44]:


def plotDifferences(test_data, test_anomaly_data, n):
    encoded_data = autoencoder.encoder(test_data).numpy()
    decoded_data = autoencoder.decoder(encoded_data).numpy()

    encoded_anomaly_data = autoencoder.encoder(test_anomaly_data).numpy()
    decoded_anomaly_data = autoencoder.decoder(encoded_anomaly_data).numpy()

    

    plt.figure(figsize=(20, 8))
    for i in range(n):
        ax = plt.subplot(4, n, i + 1)
        plt.imshow(tf.squeeze(test_data[i]))
        plt.gray()
        ax.get_xaxis().set_visible(False)
        ax.get_yaxis().set_visible(False)
        ax.set_title("SSIMLoss {:.3f}".format(SSIMLoss(test_data[i], test_data[i])))

        bx = plt.subplot(4, n, i + n + 1)
        plt.imshow(tf.squeeze(decoded_data[i]))
        plt.gray()
        bx.get_xaxis().set_visible(False)
        bx.get_yaxis().set_visible(False)
        bx.set_title("SSIMLoss {:.3f}".format(SSIMLoss(test_data[i], decoded_data[i])))

        cx = plt.subplot(4, n, i + 2*n + 1)
        plt.imshow(tf.squeeze(test_anomaly_data[i]))
        plt.gray()
        cx.get_xaxis().set_visible(False)
        cx.get_yaxis().set_visible(False)
        cx.set_title("SSIMLoss {:.3f}".format(SSIMLoss(test_anomaly_data[i], test_anomaly_data[i])))
        
        
        dx = plt.subplot(4, n, i + 3*n + 1)
        plt.imshow(tf.squeeze(decoded_anomaly_data[i]))
        plt.gray()
        dx.get_xaxis().set_visible(False)
        dx.get_yaxis().set_visible(False)
        dx.set_title("SSIMLoss {:.3f}".format(SSIMLoss(test_anomaly_data[i], decoded_anomaly_data[i])))
    plt.show()


# In[45]:


# structural similarity between two images in terms of luminance, contrast and structure./
# A value of 1 indicates identical images -> SSIMLoss needs to be minimum (as close as possible to 0)
def SSIMLoss(y_true, y_pred):
    return 1 - tf.reduce_mean(tf.image.ssim(y_true, y_pred, 1.0))


# In[46]:


def calculateLossesMEAN(data, show_plots):
    reconstruction = autoencoder.predict(data)
    train_loss = tf.keras.losses.mae(reconstruction, data)

    train_loss_image = []
    for i in range(len(train_loss)):
        loss_image = np.sum(train_loss[i]) / 255
        train_loss_image.append(loss_image)

    if show_plots == 1:
        plt.hist(train_loss_image, bins=50)
        plt.xlabel("Train loss")
        plt.ylabel("No of examples")
        plt.show()
    return train_loss_image


# In[47]:


def calculateLossesSSIM(data):
    predicted = autoencoder.predict(data)
    array_losses = []
    for i in range(len(predicted)):
        loss = SSIMLoss(predicted[i], data[i]).numpy()
        array_losses.append(loss)

    return array_losses


# In[48]:


def evaluateLossesMEAN(normal_train_data, anomalous_test_data, show_plots = 0):
    normal_loss_image_mean = calculateLossesMEAN(normal_train_data, show_plots)
    threshold = np.mean(normal_loss_image_mean) + 2 * np.std(normal_loss_image_mean)
    anomalous_loss_image_mean = calculateLossesMEAN(anomalous_test_data, show_plots)
    if show_plots == 1:
        print("Mean + 2 * STD threshold = {}, while the min value of the anomalous loss is {}".format(threshold, np.min(anomalous_loss_image_mean)))

    preds = tf.math.less(normal_loss_image_mean, threshold)
    preds_a = tf.math.greater_equal(anomalous_loss_image_mean, threshold)
    
    print("Correctly evaluated normal data: {} out of {}".format(tf.math.count_nonzero(preds).numpy(), len(normal_loss_image_mean)))
    print("Correctly evaluated anomalous data: {} out of {}".format(tf.math.count_nonzero(preds_a).numpy(), len(anomalous_loss_image_mean)))


# In[49]:


def evaluateLossesSSIM(normal_train_data, anomalous_test_data): 
    normal_loss_image_ssim = calculateLossesSSIM(normal_train_data)
    anomalous_loss_image_ssim = calculateLossesSSIM(anomalous_test_data)
    threshold = np.min(anomalous_loss_image_ssim)
    preds = tf.math.less(normal_loss_image_ssim, threshold)
    preds_a = tf.math.greater_equal(anomalous_loss_image_ssim, threshold)
    
    print("Correctly evaluated normal data: {} out of {}".format(tf.math.count_nonzero(preds).numpy(), len(normal_loss_image_ssim)))
    print("Correctly evaluated anomalous data: {} out of {}".format(tf.math.count_nonzero(preds_a).numpy(), len(anomalous_loss_image_ssim)))


# In[50]:


image_size = 128
data = getData(images_path, image_size, convert_color = 1)
data_anomaly = getData(anomaly_images_path, image_size, convert_color = 1)

normal_train_data, normal_test_data = splitDataAutoencoder(data)
anomalous_train_data, anomalous_test_data = splitDataAutoencoder(data_anomaly)

epochs = 10
batch_size = 8
hidden_layer_1 = 256
hidden_layer_2 = 128
optimizer = 'adam'
loss = SSIMLoss
metrics = ['mse']
if data.shape[-1] != 3:
    channels = 1
else:
    channels = 3


autoencoder_dir = os.listdir(autoencoder_path)
train = False
if len(autoencoder_dir) == 0 or train == True:
    autoencoder = AnomalyDetector(image_size=image_size, hidden_layer_1 = hidden_layer_1, hidden_layer_2 = hidden_layer_2, channels=channels)
    history_autoencoder = trainModel(autoencoder, epochs=epochs, batch_size=batch_size, optimizer=optimizer, loss = loss, metrics = metrics)
    autoencoder.save(autoencoder_path)
else:
    autoencoder = tf.keras.models.load_model(autoencoder_path, compile = False)


# In[33]:


plotDifferences(normal_test_data, anomalous_test_data, 10)


# In[53]:


evaluateLossesSSIM(normal_train_data, anomalous_test_data)


# In[54]:


evaluateLossesMEAN(normal_train_data, anomalous_test_data, show_plots=0)


# ## Supervised Learning

# In[57]:


image_size = 128
data = getData(path_clean_images, image_size, convert_color=0)
data_anomaly = getData(path_anomalous_images, image_size, convert_color=0)
X = np.concatenate((data, data_anomaly), axis = 0)
y = np.concatenate((np.zeros((len(data))), np.ones((len(data_anomaly)))), axis = 0)


# In[58]:


X_train, X_aux, y_train, y_aux = train_test_split(X, y, shuffle=True, stratify=y, test_size=0.3, random_state = 42)
X_val, X_test, y_val, y_test = train_test_split(X_aux, y_aux, shuffle=True, stratify=y_aux, test_size=0.2, random_state = 42)


# In[59]:


# def augmentImages(image, flip = False, rotation = False):
#     if flip == True:
#         data_augmentation = tf.keras.layers.experimental.preprocessing.RandomFlip()
#         return data_augmentation(image)
#     elif rotation == True:
#         data_augmentation = tf.keras.layers.experimental.preprocessing.RandomRotation(0.2)
#         return data_augmentation(image)

# augmented_data_flip = augmentImages(X_train, flip = True)
# augmented_data_rotation = augmentImages(X_train, rotation = True)
# X_train_augmented = np.concatenate((X_train, augmented_data_flip, augmented_data_rotation), axis = 0)
# y_train = np.concatenate((np.zeros((len(data))), np.ones((len(data_anomaly)))), axis = 0) 


# In[60]:


def trainModelSL(hidden_convlayer_1, hidden_convlayer_2, hidden_denselayer_3, optimizer, loss, metrics, epochs, batch_size):
    supervised_model = tf.keras.Sequential([
        tf.keras.layers.experimental.preprocessing.RandomFlip(),
        tf.keras.layers.experimental.preprocessing.RandomRotation(0.2),
        tf.keras.layers.InputLayer(input_shape=(
            image_size, image_size, channels)),
        tf.keras.layers.Conv2D(hidden_convlayer_1, 3,
                               padding='same', strides=2, activation='relu'),
        tf.keras.layers.MaxPooling2D(),
        tf.keras.layers.Conv2D(hidden_convlayer_2, 3,
                               padding='same', strides=2, activation='relu'),
        tf.keras.layers.MaxPooling2D(),
        tf.keras.layers.Flatten(),
        tf.keras.layers.Dense(hidden_denselayer_3, activation='relu'),
        tf.keras.layers.Dense(1, activation='sigmoid')
    ])

    supervised_model.compile(
        optimizer=optimizer,
        loss=loss,
        metrics=metrics
    )
    history_sup = supervised_model.fit(
        X_train, y_train,
        epochs=epochs,
        batch_size=batch_size,
        shuffle=True,
        validation_data=(X_val, y_val),
    )

    plt.plot(history_sup.history["loss"], label="Training Loss")
    plt.plot(history_sup.history["val_loss"], label="Validation Loss")
    plt.legend()
    plt.show()

    plt.plot(history_sup.history["accuracy"], label="Training accuracy")
    plt.plot(history_sup.history["val_accuracy"], label="Validation accuracy")
    plt.legend()
    plt.show()

    print(supervised_model.summary())

    return history_sup, supervised_model


# In[61]:


def plotPredictions(X_test, y_test, n, width = 20, height = 4):
    y_test_pred = supervised_model.predict(X_test)
    plt.figure(figsize=(width, height))
    if n > len(X_test):
        n = len(X_test)
    for i in range(n):
        ax = plt.subplot(1, n, i + 1)
        plt.imshow(tf.squeeze(X_test[i]))
        plt.gray()
        ax.get_xaxis().set_visible(False)
        ax.get_yaxis().set_visible(False)
        ax.set_title("True: {}, \n Predicted: {}".format(y_test[i], np.round(y_test_pred[i])[0]))

    plt.show()


# In[62]:


hidden_convlayer_1 = 8 
hidden_convlayer_2 = 4
hidden_denselayer_3 = 16
optimizer = 'adam'
loss = tf.keras.losses.BinaryCrossentropy()
metrics = ['accuracy']
epochs = 10
batch_size = 16
channels = data.shape[-1]


supervised_model_dir = os.listdir(supervised_model_path)
train = False


if len(supervised_model_dir) == 0 or train == True:
    history_supervised, supervised_model = trainModelSL(hidden_convlayer_1, hidden_convlayer_2, hidden_denselayer_3, optimizer, loss, metrics, epochs, batch_size)
    supervised_model.save(supervised_model_path)
else:
    supervised_model = tf.keras.models.load_model(supervised_model_path)


# In[63]:


test_loss, test_acc = supervised_model.evaluate(X_test, y_test, verbose = 2)


# In[64]:


y_test_pred = supervised_model.predict(X_test)
print(classification_report(y_test, np.round(y_test_pred)))
plotPredictions(X_test, y_test, 10, 40, 6)


# In[ ]:




