import QtQuick 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 1.4

Rectangle{
    property string cmd_text: "WiFi"
    property string btn_id: "A"

    property int enabled_tab: 2

    signal buttonClicked

    height: if( btn_id=="RT" || btn_id=="RB" || btn_id=="LB" || btn_id=="LT" )
                r_btn.height+16
            else
                cmd_btn.height+10

//    width: childrenRect.width
    width: 250
    color: "transparent"

    XboxButton
    {
        id: cmd_btn
        anchors.top: parent.top
        anchors.left: parent.left
        text_color: {
                        if( btn_id == "A" )
                            "#ace932"
                        else if( btn_id == "B" )
                            "#ff422a"
                        else if( btn_id == "X" )
                            "#2d90b7"
                        else if( btn_id == "Y" )
                            "#fced00"
                        else if( btn_id == "M" ) //Menu
                            "#aaaaaa"
                        else if( btn_id == "S" ) //Select
                            "#aaaaaa"
                        else if( btn_id == "left" )
                            "#e8e9e3"
                        else if( btn_id == "up" )
                            "#e8e9e3"
                        else if( btn_id == "down" )
                            "#e8e9e3"
                        else if( btn_id == "right" )
                            "#e8e9e3"
                        else
                            "#2d90b7"

                    }

        visible: ( btn_id=="A" || btn_id=="B" || btn_id=="X" || btn_id=="Y" ||
                   btn_id=="M" || btn_id=="S" || btn_id=="left" || btn_id=="up" ||
                   btn_id=="down" || btn_id=="right")

        button_text: btn_id
    }



    RButton
    {
        height: 24
        id: r_btn
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        text_color: "#ffffff"

        visible: ( btn_id=="RT" || btn_id=="RB" || btn_id=="LB" || btn_id=="LT" )

        button_text: btn_id
    }

    Label
    {
        anchors.left: r_btn.right
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -2
        text : cmd_text
        color: "#e8e9e3";
        font.pixelSize: 14
        font.family: consolas.name
        visible: ( btn_id=="RT" || btn_id=="RB" || btn_id=="LB" || btn_id=="LT" )
    }

    Label
    {
        anchors.left: cmd_btn.right
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: 0
        text : cmd_text
        color: "#e8e9e3";
        font.pixelSize: 14
        font.family: consolas.name
        visible: ( btn_id=="A" || btn_id=="B" || btn_id=="X" || btn_id=="Y" ||
                   btn_id=="M" || btn_id=="S" || btn_id=="left" || btn_id=="up" ||
                   btn_id=="down" || btn_id=="right" )
    }
}
