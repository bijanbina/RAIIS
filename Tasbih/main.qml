import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 1.4

Window {
    id:page
    visible: false
    property alias miheight:page.width
    minimumHeight: 460//500
    minimumWidth: 700
    color:"#2F343F"
    //minimumHeight: 565
    //minimumWidth: 360

    onVisibleChanged: {
        x = x_base + (Screen.width  - minimumWidth)  / 2;
        y =y_base + (Screen.height - minimumHeight) / 2;
    }

    onFocusObjectChanged: {
        terminalPane.refreshFocus() //set active focus to terminal
    }

    signal start()

    //Properties:
    property string ipAddress: "192.168.1.101"
    property string counterNumber: "21"

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
    FontLoader { id: genomeLight ; source: "qrc:Resources/Fonts/Genome-Thin.otf" }

    FontLoader { id: consolas ; source: "qrc:Resources/Fonts/Consolas.ttf" }
    FontLoader { id: earlyTimes ; source: "qrc:Resources/Fonts/Early Times_light Demo.otf" }



    Rectangle{
        id: paneWindow
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        height: 200
        width: minimumWidth
        MouseArea {
            id: mouseArea
            anchors.fill: parent
        }

        color: page.color
        WifiIndicator{
            id: wifiStatus
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.bottom: parent.bottom
        }

        Rectangle{
                id: savedNumber
                anchors.top: parent.top
                anchors.left: wifiStatus.right
                anchors.bottom: parent.bottom
                width: 173
                //color: "#0F343F"
                color: parent.color

                Label
                {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    text : counterNumber
                    color: "#e8e9e3";
                    font.pixelSize: 102
                    font.family: genomeLight.name
                }
        }
        Rectangle
        {
            id: splitLine
            anchors.left: savedNumber.right
            anchors.leftMargin: 2
            anchors.verticalCenter: parent.verticalCenter
            height: 95
            width: 1
            color: "#e8e9e3";
        }
        Rectangle
        {
            id: infoPanel
            anchors.left: splitLine.right
            anchors.verticalCenter: parent.verticalCenter
            color: "#e8e9e3";
            SystemStatus
            {
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    Switcher{
        id: tabPane
        anchors.top: paneWindow.bottom
        anchors.topMargin: -9

        anchors.horizontalCenter: parent.horizontalCenter
        color: page.color

        onButton1Clicked: {
            if (terminalPane.opacity == 1)
            {
                changeTabAnime.from = 1
                changeTabAnime.to = 0;
                changeTabAnime.start()
            }
        }
        onButton2Clicked: {
            if (terminalPane.opacity == 0)
            {
                changeTabAnime.from = 0
                changeTabAnime.to = 1;
                changeTabAnime.start()
            }
        }
        onButton3Clicked: {
            if (terminalPane.opacity == 1)
            {
                changeTabAnime.from = 1
                changeTabAnime.to = 0;
                changeTabAnime.start()
            }
        }

    }
    Terminal{
        id: terminalPane
        anchors.top: tabPane.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        color: page.color
    }

    NumberAnimation {
        id: changeTabAnime
        target: terminalPane
        property: "opacity"
        duration: 300
        easing.type: Easing.InOutQuad
    }





    //properties


    property int x_base: 0
    property int y_base: 0

}
