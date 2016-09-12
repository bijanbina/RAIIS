import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Window {
    id:page
    visible: true
    property alias miheight:page.width
    color:"#fff"
    minimumHeight: 600
    minimumWidth: 360
    //minimumHeight: 565
    //minimumWidth: 360

    //Properties:
    property string ipAddress: "192.168.1.101"
    property string message
    property real scale_x : width/minimumWidth
    property real scale_y : height/620


    signal set_lamp(int id);
    signal change_color(int id);
    signal music_random;
    signal music_play;

    //Fonts:
    FontLoader { id: robotoMediumFont ; source: "qrc:Resources/Fonts/Roboto-Medium.ttf" }
    FontLoader { id: robotoRegularFont ; source: "qrc:Resources/Fonts/Roboto-Regular.ttf" }
    //FontLoader { id: robotoBoldFont ; source: "qrc:Resources/Fonts/Roboto-Bold.ttf" }

    Rectangle
    {
        anchors.fill: parent
        id: main_window
        Image {
            id: back_image;
            anchors.fill: parent
            source: "qrc:Resources/Screens/start.jpg"
        }

        MouseArea
        {
            onClicked: {
                setting_window.visible = true;
                main_window.visible = false;
                setting_window.forceActiveFocus()
            }
            id: setting_button
            x: 0 * scale_x
            y: 95 * scale_y
            width: 80 * scale_x
            height: 265 * scale_y
        }


        /*Rectangle
        {
            color: "#00000000"
            border.color: "#00f"
            id: setting_rec
            x: 0 * scale_x
            y: 95 * scale_y
            width: 80 * scale_x
            height: 265 * scale_y
        }*/

        MouseArea
        {
            onClicked: {
                info_window.visible = true;
                main_window.visible = false;
                info_window.forceActiveFocus()
            }
            id: info_button
            x: 85 * scale_x
            y: 165 * scale_y
            width: 95 * scale_x
            height: 105 * scale_y

        }

        MouseArea
        {
            onClicked: {
                lamp_window.visible = true;
                main_window.visible = false;
                lamp_window.forceActiveFocus()
            }
            id: lamp_button
            x: 185 * scale_x
            y: 165 * scale_y
            width: 100 * scale_x
            height: 105 * scale_y

        }

        MouseArea
        {
            onClicked: {
                screen_window.visible = true;
                main_window.visible = false;
                screen_window.forceActiveFocus()
            }
            id: screen_button
            x: 85 * scale_x
            y: 270 * scale_y
            width: 95 * scale_x
            height: 100 * scale_y

        }

        MouseArea
        {
            id: puzzle_button
            x: 185 * scale_x
            y: 270 * scale_y
            width: 100 * scale_x
            height: 100 * scale_y
            onClicked: {
                puzzle_window.visible = true;
                main_window.visible = false;
                puzzle_window.forceActiveFocus()
            }

        }

        MouseArea
        {
            onClicked: page.close()
            id: quit_button
            x: 85 * scale_x
            y: 375 * scale_y
            width: 195 * scale_x
            height: 80 * scale_y
        }

        Keys.onReleased:
        {
            if (event.key === Qt.Key_Back || event.key=== Qt.Key_Backspace)
            {
                event.accepted=true;
                page.close();
            }
        }
    }

    Rectangle
    {
        visible: false;
        anchors.fill: parent
        id: lamp_window
        Image {
            id: back_image_lamp;
            anchors.fill: parent
            source: "qrc:Resources/Screens/lamp.jpg"
        }

        MouseArea
        {
            id: green_button
            x: 100 * scale_x
            y: 225 * scale_y
            width: 215 * scale_x
            height: 30 * scale_y
            onClicked: change_color(0)
        }

        MouseArea
        {
            id: blue_button
            x: 100 * scale_x
            y: 280 * scale_y
            width: 215 * scale_x
            height: 30 * scale_y
            onClicked: change_color(1)
        }

        MouseArea
        {
            id: red_button
            x: 100 * scale_x
            y: 335 * scale_y
            width: 215 * scale_x
            height: 30 * scale_y
            onClicked: change_color(2)
        }

        MouseArea
        {
            id: music_button
            x: 100 * scale_x
            y: 385 * scale_y
            width: 215 * scale_x
            height: 30 * scale_y
            onClicked: music_play()
        }

        MouseArea
        {
            id: random_button
            x: 100 * scale_y
            y: 425 * scale_y
            width: 215 * scale_y
            height: 45 * scale_y
            onClicked: music_random()
        }

        MouseArea
        {
            id: lamp1_button
            x: 0 * scale_x
            y: 120 * scale_y
            width: 125 * scale_x
            height: 105 * scale_y
            onClicked: set_lamp(0)
        }

        MouseArea
        {
            id: lamp2_button
            x: 245 * scale_x
            y: 100 * scale_y
            width: 115 * scale_x
            height: 105 * scale_y
            onClicked: set_lamp(1)
        }

        MouseArea
        {
            id: lamp3_button
            x: 0 * scale_x
            y: 450 * scale_y
            width: 125 * scale_x
            height: 110 * scale_y
            onClicked: set_lamp(2)
        }

        MouseArea
        {
            id: lamp4_button
            x: 245 * scale_x
            y: 495 * scale_y
            width: 115 * scale_x
            height: 100 * scale_y
            onClicked: set_lamp(3)
        }

        Text
        {
            id: debug_label
            y: 10;
            x: 10;
            text: "Warning: Debug mode is enabled"
            color: "#f00"
            font.pixelSize: 9 * scale_x

        }
        Keys.onReleased:
        {
            if (event.key === Qt.Key_Back || event.key=== Qt.Key_Backspace)
            {
                event.accepted=true;
                main_window.visible = true;
                lamp_window.visible = false;
                main_window.forceActiveFocus();
            }
        }
    }

    Rectangle
    {
        visible: false;
        anchors.fill: parent
        id: puzzle_window
        Image {
            id: back_image_puzzle;
            anchors.fill: parent
            source: "qrc:Resources/Screens/rahnema.jpg"
        }
        Keys.onReleased:
        {
            if (event.key === Qt.Key_Back || event.key=== Qt.Key_Backspace)
            {
                event.accepted=true;
                main_window.visible = true;
                puzzle_window.visible = false;
                main_window.forceActiveFocus();
            }
        }
    }

    Rectangle
    {
        visible: false;
        anchors.fill: parent
        id: info_window
        Image {
            id: back_image_info;
            anchors.fill: parent
            source: "qrc:Resources/Screens/about.jpg"
        }
        Keys.onReleased:
        {
            if (event.key === Qt.Key_Back || event.key=== Qt.Key_Backspace)
            {
                event.accepted=true;
                main_window.visible = true;
                info_window.visible = false;
                main_window.forceActiveFocus();
            }
        }
    }

    Rectangle
    {
        visible: false;
        anchors.fill: parent
        id: screen_window
        Image {
            id: back_image_screen;
            anchors.fill: parent
            source: "qrc:Resources/Screens/aboutAutism.jpg"
        }
        Keys.onReleased:
        {
            if (event.key === Qt.Key_Back || event.key=== Qt.Key_Backspace)
            {
                event.accepted=true;
                main_window.visible = true;
                screen_window.visible = false;
                main_window.forceActiveFocus();
            }
        }
    }

    Rectangle
    {
        id: setting_window
        visible: false
        anchors.fill: parent
        Settings
        {
            anchors.fill: parent
        }
        Keys.onReleased:
        {
            if (event.key === Qt.Key_Back || event.key=== Qt.Key_Backspace)
            {
                event.accepted=true;
                main_window.visible = true;
                setting_window.visible = false;
                main_window.forceActiveFocus();
            }
        }
    }

    function tof_on_screen () {
        debug_label.text += message;
    }


}
