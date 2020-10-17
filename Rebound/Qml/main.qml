import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 1.4
import "qrc:/"

Window {
    id:page
    visible: false
    property alias miheight:page.width
    minimumHeight: 400//500
    minimumWidth: 1200
    color:"#2F343F"
    //minimumHeight: 565
    //minimumWidth: 360
    flags: Qt.FramelessWindowHint //| Qt.WindowStaysOnTopHint// | Qt.SubWindow

    onVisibleChanged: {
        x = x_base + (Screen.width  - minimumWidth)  / 2;
        y =y_base + (Screen.height - minimumHeight) / 2;
    }

    onFocusObjectChanged: {
        //terminalPane.refreshFocus() //set active focus to terminal
    }

    signal start()

    //Properties:
    property string ipAddress: "192.168.154.25"
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
    FontLoader { id: robotoMediumFont ; source: "qrc:Fonts/Roboto-Medium.ttf" }
    FontLoader { id: robotoRegularFont ; source: "qrc:Fonts/Roboto-Regular.ttf" }
    FontLoader { id: robotoBoldFont ; source: "qrc:Fonts/Roboto-Bold.ttf" }
    FontLoader { id: gnomeLight ; source: "qrc:Fonts/Gnome-Thin.otf" }

    FontLoader { id: consolas ; source: "qrc:Fonts/Consolas.ttf" }
    FontLoader { id: earlyTimes ; source: "qrc:Fonts/EarlyTimesLight.otf" }
    FontLoader { id: fontAwesome ; source: "qrc:/Fonts/Fa-Solid.ttf" }
    FontLoader { id: fontAwesome_brand ; source: "qrc:/Fonts/Fa-Brands.ttf" }


    Rectangle
    {
        id: paneWindow
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        height: 100
        width: minimumWidth
        MouseArea
        {
            id: mouseArea
            anchors.fill: parent
        }

        color: page.color

        Label
        {
                id: savedNumber
                anchors.verticalCenter: parent.verticalCenter
                //color: "#0F343F"

                anchors.horizontalCenter: parent.horizontalCenter
                text : "Please Enter Your Command..."
                color: "#e8e9e3";
                font.pixelSize: 28
                font.family: robotoMediumFont.name
        }
        Rectangle
        {
            id: splitLine
            anchors.top: parent.bottom
            anchors.topMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter
            height: 1
            width: 500
            color: "#e8e9e3";
        }
    }

    Switcher
    {
        id: tabPane
        anchors.top: paneWindow.bottom
        anchors.topMargin: -9

        anchors.horizontalCenter: parent.horizontalCenter
        color: page.color

        onButton1Clicked:
        {
            if (terminalPane.opacity == 1)
            {
                changeTabAnime.from = 1
                changeTabAnime.to = 0;
                changeTabAnime.start()
            }
        }
        onButton2Clicked:
        {
            if (terminalPane.opacity == 0)
            {
                changeTabAnime.from = 0
                changeTabAnime.to = 1;
                changeTabAnime.start()
            }
        }
        onButton3Clicked:
        {
            if (terminalPane.opacity == 1)
            {
                changeTabAnime.from = 1
                changeTabAnime.to = 0;
                changeTabAnime.start()
            }
        }
    }

    ReController
    {
        id: buttonPane
        anchors.top: tabPane.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    //        color: "red"
        color: "transparent"
        anchors.topMargin: 20
    }

    ReAxis
    {
        id: axis_left
        cntName: "L"
        anchors.left: parent.left
        anchors.bottom: bottomBar.top
        anchors.bottomMargin: 25
        anchors.leftMargin: 47
    }

    ReAxis
    {
        id: axis_right
        cntName: "R"
        anchors.right: parent.right
        anchors.bottom: bottomBar.top
        anchors.bottomMargin: axis_left.anchors.bottomMargin
        anchors.rightMargin: 40
    }


    ReBottomBar
    {
        id: bottomBar
        width: parent.width
        height: 44
        anchors.bottom: parent.bottom
        anchors.left: parent.left
    }

    //properties
    property int x_base: 0
    property int y_base: 0

    function uiToggle()
    {
        page.visible = !page.visible
    }

}
