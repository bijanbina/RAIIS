import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Slider {
    value: 0.4
    style: SliderStyle
    {
       groove: Rectangle {
           anchors.right: parent.right
           implicitHeight: 4
           opacity: 1
           color: paneWindow.color
           Rectangle{
               id: rect1
               color: "#607e89"
               opacity: 1
               anchors.left: parent.left
               anchors.top: parent.top
               anchors.leftMargin: 5
               height: 4
               width: styleData.handlePosition - 5
               radius: 4
           }
           Rectangle{
               color: "#000"
               id: rect2
               opacity: 0.26
               anchors.left: rect1.right
               anchors.top: parent.top
               height: 4
               width: parent.width - styleData.handlePosition - 5
               radius: 4
           }

       }
       handle: Rectangle {
           anchors.centerIn: parent
           color: {
               if (control.pressed)
               {
                   "#90a4ae"
               }
               else
               {
                   "#607e89"
               }
           }
           implicitWidth: 15
           implicitHeight: 15
           radius: width*0.5
       }
   }
}
