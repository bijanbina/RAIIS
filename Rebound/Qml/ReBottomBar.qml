import QtQuick 2.0

Rectangle
{

    property string text_work1: page.left_action
    property string text_work2: page.up_action
    property string text_work3: page.down_action
    property string text_work4: page.right_action

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
            width: 116
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            btn_id: "left"
            cmd_text: text_work1
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
            width: 116
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            btn_id: "up"
            cmd_text: text_work2
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
            width: 116
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            btn_id: "down"
            cmd_text: text_work3
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
            width: 116
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            btn_id: "right"
            cmd_text: text_work4
        }

    }

}
