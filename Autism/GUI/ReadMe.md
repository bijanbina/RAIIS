# Getting Started

1. Download [Android SDK](https://developer.android.com/studio/index.html)
2. Download [Android NDK](https://developer.android.com/ndk/index.html)
3. Download and install [Ant Project](ant.apache.org/)
4. Download [Android version of Qt](https://www.qt.io/download-open-source/)
5. Follow [This guide](doc.qt.io/qt-5/androidgs.html) on configuring Qt for developing Android applications.
6. Download Resource file available on dropbox [shared folder](https://www.dropbox.com/sh/fisonmauag8j8az/AAAmAukgyog1Ddv0FIbjIv-la?dl=0) and put them inside [Resources](https://github.com/bijanbina/RAIIS/tree/master/Autism/GUI/Resources) folder on your local repo.

# Code Overview
This project written by C++, qml and built on top of Qt Libraries. A prior comprehend of qml - c++ binding concept is crucial to understand the written codes  which can be learn through simple STFG, BTW [Interacting with QML Objects from C++](http://doc.qt.io/qt-5/qtqml-cppintegration-interactqmlfromcpp.html) can be a good starting point. 

Preparing the environment is the next step which is well documented in "Getting Started" section.

In the following, short reportage of codes represented. This is not meant to be comprehensive by any means.  Rather it is meant as just a brief overview of some of the bigger structures and files, with guides for a variety of task categories providing places to start looking in the code and things to look for. For any further question please don't hesitate to contact me on my mail address.

## Jobs of various files

| Filename | Description |
| -- | --|
|main.cpp| main.cpp is a best starting point. main function, call for qml rendering engine and load the qml data. to bind qml to c++ and vise versa signal coming through qml D-Bus connect to c++ functions.|
|Transmission.cpp,</br>Transmission.h| All communications to ESP8266 are implemented in Transmission.cpp file,  These files in addition contain UI Slot which should ported to "uihandler" in future releases.|
|main.qml| Unfortunately this file is not realy on good structure. All UI stuff are happening here and you have to give it some time to get familiar to it. For more information check UI Structures section. |
|AndroidSlider.qml,</br> Cell.qml,</br>Joystick.qml,</br>LampCell,</br> 	Settings.qml| Deprecated and should be removed in next cleanup |

## UI Structures
