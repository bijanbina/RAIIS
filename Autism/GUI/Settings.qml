import QtQuick 2.3
import QtQuick.Window 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Rectangle {
    id:page
    visible: true
    property alias miheight:page.width
    color:"#171717"
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
       }
    }

}
