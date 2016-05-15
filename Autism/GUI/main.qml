import QtQuick 2.3
import QtQuick.Window 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Window {
    id:page
    visible: true
    property alias miheight:page.width
    color:"#171717"
    minimumHeight: 500
    minimumWidth: 280
    //minimumHeight: 565
    //minimumWidth: 360

    //Properties:
    property string ipAddress: "192.168.1.101"

    //Signals:
    signal morabaSignal
    signal mosalasSignal
    signal dayereSignal
    signal zarbdarSignal
    signal startSignal(string IP)
    signal keySignal(string key)
    signal noneSignal

    //Fonts:
    FontLoader { id: robotoMediumFont ; source: "qrc:Resources/Fonts/Roboto-Medium.ttf" }
    FontLoader { id: robotoRegularFont ; source: "qrc:Resources/Fonts/Roboto-Regular.ttf" }
    //FontLoader { id: robotoBoldFont ; source: "qrc:Resources/Fonts/Roboto-Bold.ttf" }

    Rectangle{
        id: appMenubar
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: page.height * 0.1
        color: "#607e89"

        Image
         {
             z:1
             anchors.left: parent.left
             anchors.verticalCenter: appMenubar.verticalCenter
             anchors.leftMargin: appMenubar.height * 0.3
             source: "qrc:Resources/icon_menu.png"
             id:menubtn
             height : appMenubar.height * 0.42
             width: menubtn.height
             property bool isStarted: false
             MouseArea
             {
                 id:menubtn_mousearea
                 anchors.fill: parent
                 onClicked: {
                         if (menubtn.isStarted)
                         {
                             menubtn.source= "qrc:Resources/more_icon.png"
                             menubtn.isStarted = false
                         }
                         else
                         {
                             menubtn.source= "qrc:Resources/light_bulbs_on.png"
                             menubtn.isStarted = true
                         }
                     }
             }
         }

        Image
         {
             z:1
             anchors.right: parent.right
             anchors.verticalCenter: appMenubar.verticalCenter
             anchors.rightMargin: appMenubar.height * 0.15
             source: "qrc:Resources/more_icon.png"
             id:morebtn
             height : appMenubar.height * 0.45
             width: morebtn.height
             property bool isStarted: false
             MouseArea
             {
                 id:morebtn_mousearea
                 anchors.fill: parent
                 onClicked: {
                         if (menubtn.isStarted)
                         {
                             menubtn.source= "qrc:Resources/more_icon.png"
                             menubtn.isStarted = false
                         }
                         else
                         {
                             menubtn.source= "qrc:Resources/light_bulbs_on.png"
                             menubtn.isStarted = true
                         }
                     }
             }
         }

        Label
        {
            text : "Healer"
            color: "#fff";
            font.pixelSize: appMenubar.height * 0.35
            font.family: robotoRegularFont.name
            font.weight: Font.Medium
            anchors.left: menubtn.right
            anchors.leftMargin: page.width * 0.09
            anchors.verticalCenter: appMenubar.verticalCenter
        }
    }

    Rectangle{
        id: paneWindow
        anchors.top: appMenubar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        color: "#eee"


       LampCell
       {
            id:loloTest1
            anchors.right: parent.right
            anchors.top: parent.top
       }
       LampCell
       {
            id:loloTest2
            anchors.right: loloTest1.left
            anchors.top: parent.top
       }
       LampCell
       {
            id:loloTest3
            anchors.right: loloTest2.left
            anchors.top: parent.top
       }
       LampCell
       {
            id:loloTest4
            anchors.right: parent.right
            anchors.top: loloTest1.bottom
       }
       LampCell
       {
            id:loloTest5
            anchors.right: loloTest4.left
            anchors.top: loloTest1.bottom
       }
       LampCell
       {
            id:loloTest6
            anchors.right: loloTest5.left
            anchors.top: loloTest1.bottom
       }
       Rectangle
       {
           anchors.top: loloTest5.bottom
           anchors.left: parent.left
           anchors.bottom: parent.bottom
           anchors.leftMargin: page.width * 0.1
           anchors.topMargin: page.width * 0.1
           width: paneWindow.width * 0.78
           id: mainPanel
           color: paneWindow.color
           Label
           {
               text : "Controller"
               color: "#000";
               id: primaryctl_text
               font.pixelSize: page.height * 0.035
               font.family: robotoMediumFont.name
               anchors.top: parent.top
               anchors.left: parent.left
               opacity: 0.87
           }
           Label
           {
               text : "Media Volume"
               color: "#000";
               id: volume_text
               font.pixelSize: page.height * 0.025
               font.family: robotoRegularFont.name
               anchors.top: primaryctl_text.bottom
               anchors.left: parent.left
               anchors.topMargin: page.width * 0.1
               opacity: 0.57
           }
           AndroidSlider{
               id: volumeSlider
               anchors.right: parent.right
               anchors.top: volume_text.bottom
               anchors.left: volumeimg.right
               anchors.leftMargin: page.width * 0.05
               anchors.topMargin: page.width * 0.07
           }

           Image
           {
                anchors.left: primaryctl_text.left
                anchors.verticalCenter: volumeSlider.verticalCenter
                z:1
                source: "qrc:Resources/icon_volume.png"
                id:volumeimg
                height : appMenubar.height * 0.5
                width: morebtn.height
                opacity: 0.5
           }
           Rectangle
           {
               anchors.top: volumeimg.bottom
               anchors.bottom: mainPanel.bottom
               anchors.left: mainPanel.left
               anchors.right: mainPanel.right
               color: mainPanel.color

               BusyIndicator
               {
                   anchors.centerIn: parent
                   running: true
               }
           }
           ListModel {
               id: easingTypes
               ListElement { name: "Easing.Linear"; type: Easing.Linear; ballColor: "DarkRed" }
               ListElement { name: "Easing.InQuad"; type: Easing.InQuad; ballColor: "IndianRed" }
               ListElement { name: "Easing.OutQuad"; type: Easing.OutQuad; ballColor: "Salmon" }
               ListElement { name: "Easing.InOutQuad"; type: Easing.InOutQuad; ballColor: "Tomato" }
               ListElement { name: "Easing.OutInQuad"; type: Easing.OutInQuad; ballColor: "DarkOrange" }
               ListElement { name: "Easing.InCubic"; type: Easing.InCubic; ballColor: "Gold" }
               ListElement { name: "Easing.OutCubic"; type: Easing.OutCubic; ballColor: "Yellow" }
               ListElement { name: "Easing.InOutCubic"; type: Easing.InOutCubic; ballColor: "PeachPuff" }
               ListElement { name: "Easing.OutInCubic"; type: Easing.OutInCubic; ballColor: "Thistle" }
               ListElement { name: "Easing.InQuart"; type: Easing.InQuart; ballColor: "Orchid" }
               ListElement { name: "Easing.OutQuart"; type: Easing.OutQuart; ballColor: "Purple" }
               ListElement { name: "Easing.InOutQuart"; type: Easing.InOutQuart; ballColor: "SlateBlue" }
               ListElement { name: "Easing.OutInQuart"; type: Easing.OutInQuart; ballColor: "Chartreuse" }
               ListElement { name: "Easing.InQuint"; type: Easing.InQuint; ballColor: "LimeGreen" }
               ListElement { name: "Easing.OutQuint"; type: Easing.OutQuint; ballColor: "SeaGreen" }
               ListElement { name: "Easing.InOutQuint"; type: Easing.InOutQuint; ballColor: "DarkGreen" }
               ListElement { name: "Easing.OutInQuint"; type: Easing.OutInQuint; ballColor: "Olive" }
               ListElement { name: "Easing.InSine"; type: Easing.InSine; ballColor: "DarkSeaGreen" }
               ListElement { name: "Easing.OutSine"; type: Easing.OutSine; ballColor: "Teal" }
               ListElement { name: "Easing.InOutSine"; type: Easing.InOutSine; ballColor: "Turquoise" }
               ListElement { name: "Easing.OutInSine"; type: Easing.OutInSine; ballColor: "SteelBlue" }
               ListElement { name: "Easing.InExpo"; type: Easing.InExpo; ballColor: "SkyBlue" }
               ListElement { name: "Easing.OutExpo"; type: Easing.OutExpo; ballColor: "RoyalBlue" }
               ListElement { name: "Easing.InOutExpo"; type: Easing.InOutExpo; ballColor: "MediumBlue" }
               ListElement { name: "Easing.OutInExpo"; type: Easing.OutInExpo; ballColor: "MidnightBlue" }
               ListElement { name: "Easing.InCirc"; type: Easing.InCirc; ballColor: "CornSilk" }
               ListElement { name: "Easing.OutCirc"; type: Easing.OutCirc; ballColor: "Bisque" }
               ListElement { name: "Easing.InOutCirc"; type: Easing.InOutCirc; ballColor: "RosyBrown" }
               ListElement { name: "Easing.OutInCirc"; type: Easing.OutInCirc; ballColor: "SandyBrown" }
               ListElement { name: "Easing.InElastic"; type: Easing.InElastic; ballColor: "DarkGoldenRod" }
               ListElement { name: "Easing.OutElastic"; type: Easing.OutElastic; ballColor: "Chocolate" }
               ListElement { name: "Easing.InOutElastic"; type: Easing.InOutElastic; ballColor: "SaddleBrown" }
               ListElement { name: "Easing.OutInElastic"; type: Easing.OutInElastic; ballColor: "Brown" }
               ListElement { name: "Easing.InBack"; type: Easing.InBack; ballColor: "Maroon" }
               ListElement { name: "Easing.OutBack"; type: Easing.OutBack; ballColor: "LavenderBlush" }
               ListElement { name: "Easing.InOutBack"; type: Easing.InOutBack; ballColor: "MistyRose" }
               ListElement { name: "Easing.OutInBack"; type: Easing.OutInBack; ballColor: "Gainsboro" }
               ListElement { name: "Easing.OutBounce"; type: Easing.OutBounce; ballColor: "Silver" }
               ListElement { name: "Easing.InBounce"; type: Easing.InBounce; ballColor: "DimGray" }
               ListElement { name: "Easing.InOutBounce"; type: Easing.InOutBounce; ballColor: "SlateGray" }
               ListElement { name: "Easing.OutInBounce"; type: Easing.OutInBounce; ballColor: "DarkSlateGray" }
               ListElement { name: "Easing.Bezier"; type: Easing.Bezier; ballColor: "Chartreuse"; }
           }
           Component {
               id: delegate

               Item {
                   height: 56; width: window.width

                   Text { text: name; anchors.centerIn: parent; color: "White" }

                   Rectangle {
                       id: slot1; color: "#121212"; x: 30; height: 46; width: 46
                       border.color: "#343434"; border.width: 1; radius: 12; antialiasing: true
                       anchors.verticalCenter: parent.verticalCenter
                   }

                   Rectangle {
                       id: slot2; color: "#121212"; x: window.width - 76; height: 46; width: 46
                       border.color: "#343434"; border.width: 1; radius: 12; antialiasing: true
                       anchors.verticalCenter: parent.verticalCenter
                   }

                   Rectangle {
                       id: rect; x: 30; color: "#454545"
                       border.color: "White"; border.width: 2
                       height: 46; width: 46; radius: 12; antialiasing: true
                       anchors.verticalCenter: parent.verticalCenter

                       MouseArea {
                           onClicked: if (rect.state == '') rect.state = "right"; else rect.state = ''
                           anchors.fill: parent
                           anchors.margins: -5 // Make MouseArea bigger than the rectangle, itself
                       }

                       states : State {
                           name: "right"
                           PropertyChanges { target: rect; x: window.width - 76; color: ballColor }
                       }

                       transitions: Transition {
                           NumberAnimation { properties: "x"; easing.type: type; easing.bezierCurve: getBezierCurve(name); duration: 1000 }
                           ColorAnimation { properties: "color"; easing.type: type; easing.bezierCurve: getBezierCurve(name); duration: 1000 }
                       }
                   }
               }
           }

           Flickable {
               anchors.fill: parent
               contentHeight: layout.height
               Column {
                   id: layout
                   Repeater { model: easingTypes; delegate: delegate }
               }
           }
       }
    }

}
