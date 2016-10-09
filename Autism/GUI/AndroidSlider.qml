import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Slider {
    value: 0.4
    property string handle_image: "qrc:Resources/redGrip.png"
    style: SliderStyle
    {
       groove: Rectangle {
           anchors.right: parent.right
           implicitHeight: 4
           opacity: 1
           color: "transparent"

       }
       handle: Rectangle {
           anchors.centerIn: parent
           width: parent.parent.height
           height: parent.parent.height
           color: "transparent"

           Image {
               id: back_image;
               anchors.fill: parent
               source: handle_image
           }
       }
   }
}
