# Emotion-recognition-through-SVM-and-dlib
This project is realized by OpenCV and Dlib library and it is primarily divided into two modules (training and testing modules) for recognizing three different facial expressions(happy, disgust and calm).

## Getting Started

These instructions will give you a copy of the project up and running on
your local machine for development and testing purposes. 

### Prerequisites

Requirements for the software and other tools to build, test and push 
- [OpenCV](https://opencv.org/)
- [Dlib](http://dlib.net/)
- Python3.5 or later（Anaconda recommended）

### Installing

Dlib

    pip install dlib

Anaconda(if used)

    conda create -n expression_recognition python==3.10


Download project in Windos

    Download the zip file and unzip

## Running the tests

Explain how to run the tests for this system(OpenCV and Dlib need to be installed before following steps)

### Feature Collect

Extract Dlib feature points and normalize them after a person makes a specific facial expression.Store 136-dimensional data for each image in a specific TXT file for easy retrieval.

### Data Training

Use an SVM classifier for classification and train it to create an XML file.
## Facial Expression Recognition

Read the trained XML file, classify each frame's image, and display the results.
