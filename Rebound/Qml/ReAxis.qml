import QtQuick 2.0

Rectangle
{

    property string a_cntName: "" //Controller name
    property string a_axisState: "1"
    property string textUp: ""
    property string textDown: ""
    property string textLeft: ""
    property string textRight: ""

    color: "transparent"
//    color: "red"
    width: 300
    height: 200

    ReCircle
    {
        id: gerdali
        anchors.centerIn: parent
        axisName: a_cntName
    }

    ReAxisLabel
    {
        id: axis_top_label
        anchors.bottom: gerdali.top
        anchors.bottomMargin: 13
        anchors.horizontalCenter: gerdali.horizontalCenter
        text_cl: "Win   #1"
        text_cr: "Win   Monitor"
        text_fl: "\uf061"
        text_fr: "\uf061"
        text_norm: textUp
        text_margin_l: 3
        text_margin_r: -12
        axisState: a_axisState
        cntName: a_cntName
    }

    ReAxisLabel
    {
        id: axis_left_label
        anchors.right: gerdali.left
        anchors.rightMargin: 13
        anchors.verticalCenter: gerdali.verticalCenter
        text_cl: "Win   #4"
        text_cr: "    + Left"
        text_fl: "\uf061"
        text_fr: "\uf17a"
        text_norm: textLeft
        text_margin_l: 3
        text_margin_r: -18
        axisState: a_axisState
        cntName: a_cntName
    }

    ReAxisLabel
    {
        id: axis_down_label
        anchors.top: gerdali.bottom
        anchors.topMargin: 13
        anchors.horizontalCenter: gerdali.horizontalCenter
        text_cl: "Win   #3"
        text_cr: "Monitor   Win"
        text_fl: "\uf061"
        text_fr: "\uf061"
        text_norm: textDown
        text_margin_l: 3
        text_margin_r: 11
        axisState: a_axisState
        cntName: a_cntName
    }

    ReAxisLabel
    {
        id: axis_right_label
        anchors.left: gerdali.right
        anchors.leftMargin:
        {
            if(cntName==="L")
            {
                if(axisState==="1")
                {
                    13
                }
                else
                {
                    10
                }
            }
            else if(cntName==="R")
            {
                10
            }
        }
        anchors.verticalCenter: gerdali.verticalCenter
        text_cl: "Win   #2"
        text_cr: "    + Right"
        text_fl: "\uf061"
        text_fr: "\uf17a"
        text_norm: textRight
        text_margin_l: 3
        text_margin_r: -20
        axisState: a_axisState
        cntName: a_cntName
    }

}
