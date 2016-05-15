import QtQuick 2.0

Image
 {
     z:1
     anchors.topMargin: page.width * 0.07
     anchors.rightMargin: page.width * 0.25 - setting_image.height *0.75
     source: "qrc:Resources/light_bulbs_off.png"
     id:setting_image
     height : page.height * 0.15
     width: setting_image.height
     property bool isStarted: false
     MouseArea
     {
         id:setting_mousearea
         anchors.fill: parent
         onClicked: {
                 if (setting_image.isStarted)
                 {
                     setting_image.source= "qrc:Resources/light_bulbs_off.png"
                     setting_image.isStarted = false
                 }
                 else
                 {
                     setting_image.source= "qrc:Resources/light_bulbs_on.png"
                     setting_image.isStarted = true
                 }
             }
     }
 }
