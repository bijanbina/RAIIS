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
| -------- | ----------- |
|main.cpp| main.cpp is a best starting point. main function, call for qml rendering engine and load the qml data. to bind qml to c++ and vise versa signal coming through qml D-Bus connect to c++ functions.|
|Transmission.cpp,</br>Transmission.h| All communications to ESP8266 are implemented in Transmission.cpp file,  These files in addition contain UI Slot which should ported to "uihandler" in future releases.|
|main.qml| Unfortunately this file is not realy on good structure. All UI stuff are happening here and you have to give it some time to get familiar to it. For more information check UI Structures section. |
| ColorCell.qml  | ColorCell.qml implement a row of color chooser. This widget create  create a table of colors which can be seen in the screenshot. 
|AndroidSlider.qml,</br> Cell.qml,</br>Joystick.qml,</br>LampCell,</br> 	Settings.qml| Deprecated and should be removed in next cleanup |

## UI Structures
UI implemented based on raw images. A bare background used as platform to draw things on top of it. main.qml is a simple container for all pages

* Main Window: starting window that user can choose pages from it
* Lamp Window: page that let user to connect to the lamp and manipulate it.
* Puzzle Window: this page named from the fact that the designed material used puzzle as a background. check Resources directory for more info. you can ignore codes of this page.
* Screen Window: like Puzzle Window.
* Setting Window:  I'm still not sure what this page should do. ask Dr. Moradi please.

As a last note scale_x and scale_y used to scale coordinate system to match various screen resolutions. check widget position assignment for more info.
## Connecting Process

1. Connecting to 192.168.1.1:7778
2. Ask for number of devices (NOD)
3. Show lamps based upon returned data
4. If user click on a lamp connect to IP+ID which ID is the ID of lamp that user tapped on.

## Communication Protocol

| Command | Description | Example |
| ------- | ----------- |:-------:|
| 1 | Turn on lamp | - |
| 2 | Play music (FIXME: force to play first track) |-|
| 3 | Set color | 3222000111 should set to #de006f (need calibration) |
| 4 | Change track | 42 set track number to 2 |
| 5 | Go to sleep mode ( Disable music + light) | - |
| 6 | Stop music | - |
| 7 | Turn off light | - |
| 8 | Active Rainbow mode (need deactivation) | - |
| n | New device get into the chain | - |
| q | Report NOD | - |

# Screenshot
![GUI screenshot](http://s8.iranxm.com/up/709909b1ea5c.png)
