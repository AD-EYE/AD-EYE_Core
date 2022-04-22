import sys
# print(sys.path)
if '/opt/ros/kinetic/lib/python2.7/dist-packages' in sys.path:
    sys.path.remove('/opt/ros/kinetic/lib/python2.7/dist-packages')

import dataset
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


#!pip freeze > requirements_freeze.txt
#!conda env export > environment.yml
#!jupyter nbconvert --to script ad_22032022.ipynb
# !pipreqs --force --encoding utf-8 "/home/adeye/AD-EYE_Core/AD-EYE/Anomaly_Detection/" 

def main():
    parser = argparse.ArgumentParser(description="list the content of a folder")
    parser.add_argument('execute', type = str, help = 'what to do with the model examples: train/ test')
    parser.add_argument('--image_size', type = int, help = 'rescale the images to size', default=128)
    parser.add_argument('--epochs', type = int, help = 'number of epochs to train', default = 10)
    parser.add_argument('--batch_size', type = int, help = 'number of batch_size to train', default=8)
    parser.add_argument('--hidden_1', type = int, help = 'number of neurons for hidden_layer_1 to train', default=256)
    parser.add_argument('--hidden_2', type = int, help = 'number of neurons for hidden_layer_2 to train', default=128)
    parser.add_argument('--optimizer', type = str, help = 'optimizer used to train. can be: adam, adagrad, sgd', default='adam')
    parser.add_argument('--metrics', type = str, help = 'metrics to use for evaluating the trained model', default='mse')
    parser.add_argument('--force', '-f', help = 'force model to train', default=False, action="store_true")
    parser.add_argument('--verbose', '-v', help = 'verbosity level', default=False, action="store_true")

    
    

    args = parser.parse_args()
    if args.execute == "train":
        # pass
        dataset_path, images_path, anomaly_images_path, models_path, autoencoder_path, supervised_model_path = dataset.createDirectories()

        image_size =  args.image_size

        data = getData(images_path, image_size, convert_color = 1)
        data_anomaly = getData(anomaly_images_path, image_size, convert_color = 1)

        normal_train_data, normal_test_data = splitDataAutoencoder(data)
        anomalous_train_data, anomalous_test_data = splitDataAutoencoder(data_anomaly)

        epochs = args.epochs

        batch_size = args.batch_size
        hidden_layer_1 = args.hidden_1
        hidden_layer_2 = args.hidden_2
        optimizer = args.optimizer
        loss = SSIMLoss
        metrics = [args.metrics]
        if data.shape[-1] != 3:
            channels = 1
        else:
            channels = 3

        autoencoder_dir = os.listdir(autoencoder_path)
        if len(autoencoder_dir) == 0 or args.force:
            autoencoder = AnomalyDetector(image_size=image_size, hidden_layer_1 = hidden_layer_1, hidden_layer_2 = hidden_layer_2, channels=channels)
            history_autoencoder = trainModel(autoencoder, epochs=epochs, batch_size=batch_size, optimizer=optimizer, loss = loss, metrics = metrics, normal_train_data=normal_train_data, normal_test_data=normal_test_data)
            autoencoder.save(autoencoder_path)
        else:
            autoencoder = tf.keras.models.load_model(autoencoder_path, compile = False)




    elif args.execute == "test":

        dataset_path, images_path, anomaly_images_path, models_path, autoencoder_path, supervised_model_path = dataset.createDirectories()
        autoencoder_dir = os.listdir(autoencoder_path)
        if len(autoencoder_dir) == 0:
            print("Autoencoder model does not exist, please run the train file first")
        else:
            autoencoder = tf.keras.models.load_model(autoencoder_path, compile = False)
            image_size =  args.image_size
            data = getData(images_path, image_size, convert_color = 1)
            data_anomaly = getData(anomaly_images_path, image_size, convert_color = 1)

            normal_train_data, normal_test_data = splitDataAutoencoder(data)
            anomalous_train_data, anomalous_test_data = splitDataAutoencoder(data_anomaly)
            if args.verbose:
                plotDifferences(autoencoder, normal_test_data, anomalous_test_data, 10)
            print("Evaluating model using SSIM metric...")
            evaluateLossesSSIM(autoencoder, normal_train_data, anomalous_test_data)
            print("Evaluating model using STD and Mean metric...")
            evaluateLossesMEAN(autoencoder, normal_train_data, anomalous_test_data, show_plots=args.verbose)
    else:
        print("command not found. use train or test to execute the code accordingly")




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


def splitDataAutoencoder(data):
    train_data, test_data = train_test_split(data, test_size = 0.2, random_state=42)
    train_data = tf.cast(train_data, tf.float32)
    test_data = tf.cast(test_data, tf.float32)
    if data.shape[-1] != 3:
        train_data = train_data[..., tf.newaxis]
        test_data = test_data[..., tf.newaxis]
    return train_data, test_data


def trainModel(model, epochs, batch_size, optimizer, loss, metrics, normal_train_data, normal_test_data):
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

def plotDifferences(autoencoder, test_data, test_anomaly_data, n):
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

# structural similarity between two images in terms of luminance, contrast and structure./
# A value of 1 indicates identical images -> SSIMLoss needs to be minimum (as close as possible to 0)
def SSIMLoss(y_true, y_pred):
    return 1 - tf.reduce_mean(tf.image.ssim(y_true, y_pred, 1.0))


def calculateLossesMEAN(autoencoder, data, show_plots):
    reconstruction = autoencoder.predict(data)
    train_loss = tf.keras.losses.mae(reconstruction, data)

    train_loss_image = []
    for i in range(len(train_loss)):
        loss_image = np.sum(train_loss[i]) / 255
        train_loss_image.append(loss_image)

    if show_plots:
        plt.hist(train_loss_image, bins=50)
        plt.xlabel("Train loss")
        plt.ylabel("No of examples")
        plt.show()
    return train_loss_image


def calculateLossesSSIM(autoencoder, data):
    predicted = autoencoder.predict(data)
    array_losses = []
    for i in range(len(predicted)):
        loss = SSIMLoss(predicted[i], data[i]).numpy()
        array_losses.append(loss)

    return array_losses


def evaluateLossesMEAN(autoencoder, normal_train_data, anomalous_test_data, show_plots):
    normal_loss_image_mean = calculateLossesMEAN(autoencoder, normal_train_data, show_plots)
    threshold = np.mean(normal_loss_image_mean) + 2 * np.std(normal_loss_image_mean)
    anomalous_loss_image_mean = calculateLossesMEAN(autoencoder, anomalous_test_data, show_plots)
    if show_plots:
        print("Mean + 2 * STD threshold = {}, while the min value of the anomalous loss is {}".format(threshold, np.min(anomalous_loss_image_mean)))

    preds = tf.math.less(normal_loss_image_mean, threshold)
    preds_a = tf.math.greater_equal(anomalous_loss_image_mean, threshold)
    
    print("Correctly evaluated normal data: {} out of {}".format(tf.math.count_nonzero(preds).numpy(), len(normal_loss_image_mean)))
    print("Correctly evaluated anomalous data: {} out of {}".format(tf.math.count_nonzero(preds_a).numpy(), len(anomalous_loss_image_mean)))


def evaluateLossesSSIM(autoencoder, normal_train_data, anomalous_test_data): 
    normal_loss_image_ssim = calculateLossesSSIM(autoencoder, normal_train_data)
    anomalous_loss_image_ssim = calculateLossesSSIM(autoencoder, anomalous_test_data)
    threshold = np.min(anomalous_loss_image_ssim)
    preds = tf.math.less(normal_loss_image_ssim, threshold)
    preds_a = tf.math.greater_equal(anomalous_loss_image_ssim, threshold)
    
    print("Correctly evaluated normal data: {} out of {}".format(tf.math.count_nonzero(preds).numpy(), len(normal_loss_image_ssim)))
    print("Correctly evaluated anomalous data: {} out of {}".format(tf.math.count_nonzero(preds_a).numpy(), len(anomalous_loss_image_ssim)))


if __name__ =='__main__':
    main()

