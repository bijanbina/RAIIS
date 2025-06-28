import QtQuick 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 1.4

Rectangle
{
    property bool   button_enabled: true
    property color  color_enabled : "#ffffff"
    property color  color_stroke  : "#e8e9e3"
    property color  color_disabled: "#3a3b36"
    property int    button_radius : 5
    property string button_text
    property int    button_type: 0 // 0 : left, 1: center, 2:right

    signal buttonClicked

    color: "transparent"

    Rectangle
    {
        id: rnd1
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left:  (button_type != 2) ? parent.left : undefined
        anchors.right: (button_type == 2) ? parent.right : undefined
        width: parent.width - button_radius
        radius: (button_type == 1) ? 0 : button_radius
        color: color_enabled
        visible: button_enabled
    }

    Rectangle
    {
        id: rnd2
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left:  (button_type != 2) ? parent.left : undefined
        anchors.right: (button_type == 2) ? parent.right : undefined
        anchors.leftMargin:  (button_type != 2) ? parent.width - 2 * button_radius : 0
        anchors.rightMargin: (button_type == 2) ? parent.width - 2 * button_radius : undefined
        width: 2 * button_radius
        color: color_enabled
        visible: button_enabled
    }

    Label
    {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 7
        text : button_text
        color: ( button_enabled ) ? color_disabled : color_stroke;
        font.pixelSize: 16
        font.weight: Font.Light
        font.family: earlyTimes.name
        antialiasing: true
    }

    MouseArea
    {
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        onClicked:
        {
            console.log("sag berine be internet");
            //button_enabled = ! button_enabled;
            buttonClicked();
        }
    }
}

