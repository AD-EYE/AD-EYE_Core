
import sys
# print(sys.path)
if '/opt/ros/kinetic/lib/python2.7/dist-packages' in sys.path:
    sys.path.remove('/opt/ros/kinetic/lib/python2.7/dist-packages')


import os
import dataset
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



def main():

    parser = argparse.ArgumentParser(description="list the content of a folder")
    parser.add_argument('execute', type = str, help = 'what to do with the model examples: train/ test')
    parser.add_argument('--image_size', type = int, help = 'rescale the images to size', default=128)
    parser.add_argument('--epochs', type = int, help = 'number of epochs to train', default = 10)
    parser.add_argument('--batch_size', type = int, help = 'number of batch_size to train', default=16)
    parser.add_argument('--loss', type = str, help = 'loss for training', default='binary_crossentropy')
    parser.add_argument('--conv_1', type = int, help = 'number of neurons for convolutional_layer_1 to train', default=8)
    parser.add_argument('--conv_2', type = int, help = 'number of neurons for convolutional_layer_2 to train', default=4)
    parser.add_argument('--dense_1', type = int, help = 'number of neurons for dense_layer_1 to train', default=16)
    parser.add_argument('--optimizer', type = str, help = 'optimizer used to train. can be: adam, adagrad, sgd', default='adam')
    parser.add_argument('--metrics', type = str, help = 'metrics to use for evaluating the trained model', default='accuracy')
    parser.add_argument('--force', '-f', help = 'force model to train', default=False, action="store_true")
    parser.add_argument('--verbose', '-v', help = 'verbosity level', default=False, action="store_true")

    args = parser.parse_args()

    dataset_path, images_path, anomaly_images_path, models_path, autoencoder_path, supervised_model_path = dataset.createDirectories()

    image_size = args.image_size
    data = getData(images_path, image_size, convert_color=0)
    data_anomaly = getData(anomaly_images_path, image_size, convert_color=0)



    X = np.concatenate((data, data_anomaly), axis = 0)
    y = np.concatenate((np.zeros((len(data))), np.ones((len(data_anomaly)))), axis = 0)

    X_train, X_aux, y_train, y_aux = train_test_split(X, y, shuffle=True, stratify=y, test_size=0.3, random_state = 42)
    X_val, X_test, y_val, y_test = train_test_split(X_aux, y_aux, shuffle=True, stratify=y_aux, test_size=0.2, random_state = 42)

    if args.execute == 'train':

        hidden_convlayer_1 = args.conv_1 
        hidden_convlayer_2 = args.conv_2
        hidden_denselayer_3 = args.dense_1
        optimizer = args.optimizer
        loss = args.loss
        metrics = [args.metrics]
        epochs = args.epochs
        batch_size = args.batch_size
        channels = data.shape[-1]


        supervised_model_dir = os.listdir(supervised_model_path)


        if len(supervised_model_dir) == 0 or args.force:
            history_supervised, supervised_model = trainModelSL(hidden_convlayer_1, hidden_convlayer_2, hidden_denselayer_3, optimizer, loss, metrics, epochs, batch_size, X_train, X_val, y_train, y_val, image_size, channels)
            if args.verbose:

                plt.plot(history_supervised.history["loss"], label="Training Loss")
                plt.plot(history_supervised.history["val_loss"], label="Validation Loss")
                plt.legend()
                plt.show()

                plt.plot(history_supervised.history["accuracy"], label="Training accuracy")
                plt.plot(history_supervised.history["val_accuracy"], label="Validation accuracy")
                plt.legend()
                plt.show()

                print(supervised_model.summary())

            supervised_model.save(supervised_model_path)
        else:
            supervised_model = tf.keras.models.load_model(supervised_model_path)
    elif args.execute == 'test':
        supervised_model_dir = os.listdir(supervised_model_path)
        if len(supervised_model_dir) == 0:
            print("Autoencoder model does not exist, please run the train file first")
        else:
            supervised_model = tf.keras.models.load_model(supervised_model_path)
            test_loss, test_acc = supervised_model.evaluate(X_test, y_test)
            print("Test loss: {}".format(test_loss))
            print("Test accuracy: {}".format(test_acc))
            y_test_pred = supervised_model.predict(X_test)
            print(classification_report(y_test, np.round(y_test_pred)))
            if args.verbose: 
                plotPredictions(supervised_model, X_test, y_test, 10, 40, 6)
    else:
        print("command not found. use train or test to execute the code accordingly ")







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

def trainModelSL(hidden_convlayer_1, hidden_convlayer_2, hidden_denselayer_3, optimizer, loss, metrics, epochs, batch_size, X_train, X_val, y_train, y_val, image_size, channels):
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


    return history_sup, supervised_model


def plotPredictions(supervised_model, X_test, y_test, n, width = 20, height = 4):
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

if __name__ == '__main__':
    main()