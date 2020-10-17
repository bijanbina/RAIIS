import QtQuick 2.0

Rectangle
{

    width: childrenRect.width
    height: childrenRect.height

    Rectangle
    {
        id: buttonPaneLeft
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.leftMargin: 20
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
