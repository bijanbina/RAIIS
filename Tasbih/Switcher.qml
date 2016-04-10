import QtQuick 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 1.4

Rectangle{
    id: switcher
    property color foreground_color: "#3a3b36"
    property color text_color: "#e8e9e3"

    property string button1_text: "WiFi"
    property string button2_text: "Terminal"
    property string button3_text: "Option"

    property int enabled_tab: 2

    signal button1Clicked
    signal button2Clicked
    signal button3Clicked

    height: 30
    width: 256
    radius: 5
    border.color: text_color;

    Rectangle
    {
        id: borders
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: button1.right
        width: parent.width / 3
        border.color: text_color;
        color: "transparent"
    }

    RoundButton
    {
        id: button1
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: parent.width / 3
        button_text: button1_text
        button_type: 0
        onButtonClicked: {
            onTabChanged(1)
            button1Clicked()
        }
        button_enabled: (enabled_tab == 1)
    }

    RoundButton
    {
        id: button2
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: button1.right
        width: parent.width / 3
        button_text: button2_text
        button_type: 1
        onButtonClicked: {
            onTabChanged(2)
            button2Clicked()
        }
        button_enabled: (enabled_tab == 2)
    }
    RoundButton
    {
        id: button3
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: button2.right
        width: parent.width / 3
        button_text: button3_text
        button_type: 2
        onButtonClicked: {
            onTabChanged(3)
            button3Clicked()
        }
        button_enabled: (enabled_tab == 3)
    }

    function onTabChanged(i)
    {
        enabled_tab = i;
    }
}
