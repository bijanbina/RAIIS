import QtQuick 2.5

Rectangle
{
    id: container

    property string text_id: ""
    property string text_title: "Firefox: Chevron Right Icon"
    property color color_text: "#e8e9e3"

    Text
    {
        id: process_id
        anchors.left: parent.left
        anchors.leftMargin: 80
        anchors.verticalCenter: parent.verticalCenter
        text: text_id
        font.family: robotoBoldFont.name
        font.pixelSize: 40
        font.weight: Font.Bold
        color: color_text

        visible: process_title.text.length
    }

    Text
    {
        id: process_title
        anchors.left: process_id.right
        anchors.leftMargin: 40
        anchors.verticalCenter: parent.verticalCenter
        text: text_title
        font.family: robotoRegularFont.name
        font.pixelSize: 20
        color: color_text
    }

}
