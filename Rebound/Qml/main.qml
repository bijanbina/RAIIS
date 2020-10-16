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
    minimumHeight: 330//500
    minimumWidth: 700
    color:"#2F343F"
    //minimumHeight: 565
    //minimumWidth: 360
    flags: Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint// | Qt.SubWindow

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

    Rectangle
    {
        id: buttonPane
        anchors.top: tabPane.bottom
        anchors.horizontalCenter: parent.horizontalCenter
//        color: "red"
        color: "transparent"
        width: childrenRect.width
        height: childrenRect.height
        anchors.topMargin: 20


        Rectangle
        {
            id: buttonPaneLeft
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: 5
//            color: "red"
            color: "transparent"
            width: childrenRect.width
            height: childrenRect.height

            CommandButton
            {
                id: xbutton
                anchors.top: parent.top
                anchors.left: parent.left
                btn_id: "X"
                cmd_text: "Close Active Window"
            }

            CommandButton
            {
                id: ybutton
                anchors.top: xbutton.bottom
                anchors.left: parent.left
                btn_id: "Y"
                cmd_text: "Switch to firefox"
            }

            CommandButton
            {
                id: abutton
                anchors.top: ybutton.bottom
                anchors.left: parent.left
                btn_id: "A"
                cmd_text: "Switch to Spotify"
            }

            CommandButton
            {
                id: bbutton
                anchors.top: abutton.bottom
                anchors.left: parent.left
                btn_id: "B"
                cmd_text: "Open New Firefox Window"
            }

            CommandButton
            {
                id: s_button
                anchors.top: bbutton.bottom
                anchors.left: parent.left
                btn_id: "S"
                cmd_text: "Mute/UnMute"
            }
        }

        Rectangle
        {
            id: buttonPaneRight
            anchors.top: parent.top
            anchors.left: buttonPaneLeft.right
//            color: "red"
            color: "transparent"
            width: childrenRect.width
            height: childrenRect.height

            CommandButton
            {
                id: rt_button
                anchors.top: parent.top
                anchors.left: parent.left
                btn_id: "RT"
                cmd_text: "Swtich to book"
            }

            CommandButton
            {
                id: rb_button
                anchors.top: rt_button.bottom
                anchors.left: parent.left
                btn_id: "RB"
                cmd_text: "Switch to epub reader"
            }

            CommandButton
            {
                id: lt_button
                anchors.top: rb_button.bottom
                anchors.left: parent.left
                btn_id: "LT"
                cmd_text: "Switch to nautilus"
            }

            CommandButton
            {
                id: lb_button
                anchors.top: lt_button.bottom
                anchors.left: parent.left
                btn_id: "LB"
                cmd_text: "Put PC to sleep"
            }

            CommandButton
            {
                id: mbutton
                anchors.top: lb_button.bottom
                anchors.left: parent.left
                anchors.leftMargin: 4
                btn_id: "M"
                cmd_text: "Put PC to sleep"
            }
        }

    }

    //properties
    property int x_base: 0
    property int y_base: 0

    function uiToggle()
    {
        page.visible = !page.visible
    }

}
