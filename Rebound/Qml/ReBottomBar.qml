import QtQuick 2.0

Rectangle
{

    color: "transparent"

    Rectangle
    {
        id: splitLine
        height: 1
        width: parent.width
        anchors.top: parent.top
        anchors.left: parent.left
        color: "#e8e9e3"
    }

    Rectangle
    {
        id: work1_rect
        width: parent.width/4
        height: parent.height
        anchors.left: parent.left
        anchors.top: parent.top
        color: parent.color

        CommandButton
        {
            id: work1
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            btn_id: "left"
            cmd_text: "Switch to Workspace #1"
        }

    }

    Rectangle
    {
        id: work2_rect
        width: parent.width/4
        height: parent.height
        anchors.left: work1_rect.right
        anchors.top: parent.top
        color: parent.color

        CommandButton
        {
            id: work2
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            btn_id: "up"
            cmd_text: "Switch to Workspace #2"
        }

    }

    Rectangle
    {
        id: work3_rect
        width: parent.width/4
        height: parent.height
        anchors.left: work2_rect.right
        anchors.top: parent.top
        color: parent.color

        CommandButton
        {
            id: work3
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            btn_id: "down"
            cmd_text: "Switch to Workspace #3"
        }

    }

    Rectangle
    {
        id: work4_rect
        width: parent.width/4
        height: parent.height
        anchors.left: work3_rect.right
        anchors.top: parent.top
        color: parent.color

        CommandButton
        {
            id: work4
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            btn_id: "right"
            cmd_text: "Switch to Workspace #4"
        }

    }

}
