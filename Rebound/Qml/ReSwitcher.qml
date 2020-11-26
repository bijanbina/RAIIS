import QtQuick 2.5
import QtQuick.Window 2.0
import QtQml 2.2
import "qrc:/"

Window
{
    id: window_switcher
    objectName: "switcher"

    minimumWidth: 900
    minimumHeight: 430
    width: 900
    height: 430
    color:"#2F343F"
    visible: false
    x: (Screen.width  - minimumWidth )/ 2
    y: (Screen.height - minimumHeight)/ 2
//    flags: Qt.FramelessWindowHint //| Qt.WindowStaysOnTopHint// | Qt.SubWindow
    flags: Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint// | Qt.SubWindow

    //Properties:
    property int height_rect_process: 50
    property color color_background1: "#373e4b"
    property color color_background2: "#3c4351"
    property color color_background_active: "#4b556b"
    property int process_id: 1
    property string process_title: ""
    property int active_process: 1
    property int max_timer: 900

    //Signals:
    signal selectWindow(int activeProcessId)

    //Fonts:
    FontLoader { id: robotoMediumFont ; source: "qrc:Fonts/Roboto-Medium.ttf" }
    FontLoader { id: robotoRegularFont ; source: "qrc:Fonts/Roboto-Regular.ttf" }
    FontLoader { id: robotoBoldFont ; source: "qrc:Fonts/Roboto-Bold.ttf" }
    FontLoader { id: gnomeLight ; source: "qrc:Fonts/Gnome-Thin.otf" }

    FontLoader { id: consolas ; source: "qrc:Fonts/Consolas.ttf" }
    FontLoader { id: earlyTimes ; source: "qrc:Fonts/EarlyTimesLight.otf" }
    FontLoader { id: fontAwesome ; source: "qrc:/Fonts/Fa-Solid.ttf" }
    FontLoader { id: fontAwesome_brand ; source: "qrc:/Fonts/Fa-Brands.ttf" }

    onActive_processChanged:
    {
        label_timer.text = max_timer
    }

    onVisibleChanged:
    {
        if(visible)
        {
            label_timer.text = max_timer
        }
    }

    Rectangle
    {
        id: rect_title
        width: parent.width
        height: 40
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 20
        color: "transparent"

        Text
        {
            id: label_title
            text: "Select Your Application"
            anchors.centerIn: parent
            font.family: robotoRegularFont.name
            font.pixelSize: 28
            color: "#e8e9e3"
        }

        Text
        {
            id: label_timer
            anchors.right: parent.right
            anchors.top: label_title.top
            anchors.rightMargin: 30
            text: "0"
            font.family: robotoRegularFont.name
            font.pixelSize: 30
            color: "#e8e9e3"
        }

        Timer
        {
            id: timer
            interval: 50
            running: true
            repeat: true
            onTriggered:
            {
//                console.log("triggered")
                var value_time = parseInt(label_timer.text) - interval
                if(value_time>0)
                {
                    label_timer.text = value_time
                }
                else if(value_time===0)
                {
                    label_timer.text = 0
                    selectWindow(active_process)
                    window_switcher.visible = false
                }
            }
        }

    }

    Rectangle
    {
        width: parent.width
        height: height_rect_process*6
        anchors.top: rect_title.bottom
        anchors.topMargin: 25
        anchors.left: parent.left
        color: "transparent"

        ReSwitchElement
        {
            id: process1
            width: parent.width
            height: height_rect_process
            anchors.left: parent.left
            anchors.top: parent.top
            text_id: "1"
            color:
            {
                if(active_process===parseInt(text_id))
                {
                    color_background_active
                }
                else
                {
                    color_background1
                }
            }
        }

        ReSwitchElement
        {
            id: process2
            width: parent.width
            height: height_rect_process
            anchors.left: parent.left
            anchors.top: process1.bottom
            text_id: "2"
            color:
            {
                if(active_process===parseInt(text_id))
                {
                    color_background_active
                }
                else
                {
                    color_background2
                }
            }
        }

        ReSwitchElement
        {
            id: process3
            width: parent.width
            height: height_rect_process
            anchors.left: parent.left
            anchors.top: process2.bottom
            text_id: "3"
            color:
            {
                if(active_process===parseInt(text_id))
                {
                    color_background_active
                }
                else
                {
                    color_background1
                }
            }
        }

        ReSwitchElement
        {
            id: process4
            width: parent.width
            height: height_rect_process
            anchors.left: parent.left
            anchors.top: process3.bottom
            text_id: "4"
            color:
            {
                if(active_process===parseInt(text_id))
                {
                    color_background_active
                }
                else
                {
                    color_background2
                }
            }
        }

        ReSwitchElement
        {
            id: process5
            width: parent.width
            height: height_rect_process
            anchors.left: parent.left
            anchors.top: process4.bottom
            text_id: "5"
            color:
            {
                if(active_process===parseInt(text_id))
                {
                    color_background_active
                }
                else
                {
                    color_background1
                }
            }
        }

        ReSwitchElement
        {
            id: process6
            width: parent.width
            height: height_rect_process
            anchors.left: parent.left
            anchors.top: process5.bottom
            text_id: "6"
            color:
            {
                if(active_process===parseInt(text_id))
                {
                    color_background_active
                }
                else
                {
                    color_background2
                }
            }
        }

    }

    ReBottomBar
    {
        id: bottomBar
        width: parent.width
        height: 44
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        text_work1: "Move to #1"
        text_work2: "Move to #2"
        text_work3: "Move to #3"
        text_work4: "Move to #4"
    }

    function updateProcessTitle()
    {
        if(process_id === 1)
        {
            process1.text_title = process_title
        }
        else if(process_id === 2)
        {
            process2.text_title = process_title
        }
        else if(process_id === 3)
        {
            process3.text_title = process_title
        }
        else if(process_id === 4)
        {
            process4.text_title = process_title
        }
        else if(process_id === 5)
        {
            process5.text_title = process_title
        }
        else if(process_id === 6)
        {
            process6.text_title = process_title
        }
    }

    function activeNextProcess()
    {
        active_process += 1

        if ( active_process==2 )
        {
            if ( process2.text_title.length==0 )
            {
                active_process = 1;
            }
        }
        if ( active_process==3 )
        {
            if ( process3.text_title.length==0 )
            {
                active_process = 1;
            }
        }
        if ( active_process==4 )
        {
            if ( process4.text_title.length==0 )
            {
                active_process = 1;
            }
        }
        if ( active_process==5 )
        {
            if ( process5.text_title.length==0 )
            {
                active_process = 1;
            }
        }
        if ( active_process==6 )
        {
            if ( process6.text_title.length==0 )
            {
                active_process = 1;
            }
        }

        if(active_process>6)
        {
            active_process = 1
        }
    }

}
