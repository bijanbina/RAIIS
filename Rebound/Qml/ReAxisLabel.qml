import QtQuick 2.0

Rectangle
{
    property string axisState: "1"
    property string cntName: "L" //controller name
    property string text_cl: "Win   #1"
    property string text_cr: ""
    property string text_fl: ""
    property string text_fr: ""
    property string text_norm: ""
    property int text_margin_r: 0
    property int text_margin_l: 0

    width: label_c.width
    height: label_f.height
    color: "transparent"

    Text
    {
        id: label_c
        text:
        {
            if(cntName==="L")
            {
                if(axisState==="1")
                {
                    text_cl
                }
                else
                {
                    text_norm
                }
            }
            else if(cntName==="R")
            {
                if(axisState==="1")
                {
                    text_cr
                }
                else
                {
                    text_norm
                }
            }
        }
        font.family: consolas.name
        font.pixelSize: 10
        color: "#e8e9e3"
        anchors.left: parent.left
        anchors.top: parent.top
    }

    Text
    {
        id: label_f
        text:
        {
            if(cntName==="L")
            {
                if(axisState==="1")
                {
                    text_fl
                }
                else
                {
                    ""
                }
            }
            else if(cntName==="R")
            {
                if(axisState==="1")
                {
                    text_fr
                }
                else
                {
                    ""
                }
            }
        }
        font.family: fontAwesome.name
        font.pixelSize: 11
        color: "#e8e9e3"
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset:
        {
            if(cntName==="L")
            {
                if(axisState==="1")
                {
                    text_margin_l
                }
                else
                {
                    0
                }
            }
            else if(cntName==="R")
            {
                if(axisState==="1")
                {
                    text_margin_r
                }
                else
                {
                    0
                }
            }
        }
    }

}
