import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 1.4
import "qrc:/"

Window
{
    id: page
//    objectName: "Rebound" //FIXME: A bug lies in here

    visible: false
    property alias miheight:page.width
    minimumHeight: 400
    minimumWidth: 1200
    color:"#2F343F"
    //minimumHeight: 565
    //minimumWidth: 360
    flags: Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint // | Qt.SubWindow

    onVisibleChanged:
    {
        x = x_base + (Screen.width  - minimumWidth)  / 2;
        y =y_base + (Screen.height - minimumHeight) / 2;
    }

    onFocusObjectChanged:
    {
        //terminalPane.refreshFocus() //set active focus to terminal
    }

    signal start()

    //Properties:
    property string ipAddress: "192.168.154.25"
    property string counterNumber: "21"
    property string x_action: "Close Active Window"
    property string y_action: "Switch to Firefox"
    property string a_action: "Switch to Spotify"
    property string b_action: "Open New Firefox Window"
    property string m_action: "Exit Super Mode"
    property string s_action: "Mute/UnMute"
    property string r1_action: "Switch to Book"
    property string r2_action: "Switch to EPUB Reader"
    property string l1_action: "Switch to Nautilus"
    property string l2_action: "Put PC to Sleep"
    property string lau_action: "1"
    property string lad_action: "1"
    property string lal_action: "1"
    property string lar_action: "1"
    property string rau_action: "1"
    property string rad_action: "1"
    property string ral_action: "1"
    property string rar_action: "1"
    property string left_action: "Switch to Workspace #1"
    property string up_action: "Switch to Workspace #2"
    property string down_action: "Switch to Workspace #3"
    property string right_action: "Switch to Workspace #4"
    property string axis_state: "1"

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
        a_cntName: "L"
        a_axisState: page.axis_state
        anchors.left: parent.left
        anchors.bottom: bottomBar.top
        anchors.bottomMargin: 20
        anchors.leftMargin: 23
        textUp: lau_action
        textDown: lad_action
        textLeft: lal_action
        textRight: lar_action
    }

    ReAxis
    {
        id: axis_right
        a_cntName: "R"
        a_axisState: page.axis_state
        anchors.right: parent.right
        anchors.bottom: bottomBar.top
        anchors.bottomMargin: axis_left.anchors.bottomMargin
        anchors.rightMargin: 15
        textUp: rau_action
        textDown: rad_action
        textLeft: ral_action
        textRight: rar_action
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
