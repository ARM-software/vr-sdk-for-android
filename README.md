# VR SDK for Android

![VR SDK banner](https://user-images.githubusercontent.com/11390552/27234633-9fa8905e-52b5-11e7-896b-90e6ca555bdb.jpg)

## Introduction
Software Development Kit for VR applications on Android

The VR Software Development Kit for Android is a collection of resources to help you build VR applications for a platform with a Mali GPU and an ARM processor.
You can use it for creating new applications, training, and exploration of implementation possibilities.
You can use the VR SDK for Android to produce applications that will run on any devices that run Android on an ARM processor.

## Requirements

To build and run the VR SDK sample applications you will need:
-  An ARM based device with a Mali series GPU running Android.
-  Android Studio
-  The latest Android SDK ( can be installed from Android Studio )
-  The latest Android NDK ( can be installed from Android Studio )

## License

The software is provided under an MIT license. Contributions to this project are accepted under the same license.

## Building and Development

#### Directories structure

The VR SDK for Android contains 2 folders. The "doxygen" folder contains all the files used by the build_documentation.sh
script to create the documentation files. The documentation will be created in a separate folder called "docs" at the root of 
the VR SDK folder. The "samples" folder contains a subfolder for each sample of the SDK which can be opened in Android Studio
independently.

#### Tools

The VR SDK uses Android Studio to build the samples provided. Please download the latest version of Android Studio
from https://developer.android.com/studio/index.html

#### Development instructions

To work with the sample codes, follow the Getting Started Guide section of the documentation.

#### Documentation

You can find an online version of the documentation at https://arm-software.github.io/vr-sdk-for-android/
or you can build the Doxygen documentation with `./build_documentation.sh`.
This requires Doxygen to be installed on your machine.
