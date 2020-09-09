import QtQuick 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 1.4

Rectangle{
    property color foreground_color: "#2d2e2a"
    property color text_color: "#e8e9e3"
    property string button_text: "WiFi"

    property int enabled_tab: 2

    signal buttonClicked

    height: 25
    width: 40
    radius: 5
    color: foreground_color

    anchors.margins: height/5


    Label
    {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenterOffset: 1
        text : button_text
        color: text_color;
        font.pixelSize: 14
        font.family: robotoBoldFont.name
        font.weight: Font.Bold
    }

    MouseArea
    {
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        onClicked:
        {
            buttonClicked();
        }
    }
}
