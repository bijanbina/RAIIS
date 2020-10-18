import QtQuick 2.0

Rectangle
{

    property string cntName: "" //Controller name
    property string axisState: "1"

    color: "transparent"
//    color: "red"
    width: 300
    height: 200

    ReCircle
    {
        id: gerdali
        anchors.centerIn: parent
        axisName: cntName
    }

    Rectangle
    {
        id: axis_top_label
        anchors.bottom: gerdali.top
        anchors.bottomMargin: 13
        anchors.horizontalCenter: gerdali.horizontalCenter
        width: axis_top_label_c.width
        height: axis_top_label_f.height
        color: parent.color

        Text
        {
            id: axis_top_label_c
            text:
            {
                if(cntName==="L")
                {
                    if(axisState==="1")
                    {
                        "Win   #1"
                    }
                }
                else if(cntName==="R")
                {
                    if(axisState==="1")
                    {
                        "Win   Monitor"
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
            id: axis_top_label_f
            text:
            {
                if(cntName==="L")
                {
                    if(axisState==="1")
                    {
                        "\uf061"
                    }
                }
                else if(cntName==="R")
                {
                    if(axisState==="1")
                    {
                        "\uf061"
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
                        3
                    }
                }
                else if(cntName==="R")
                {
                    if(axisState==="1")
                    {
                        -12
                    }
                }
            }
        }
    }

    Rectangle
    {
        id: axis_left_label
        anchors.right: gerdali.left
        anchors.rightMargin: 13
        anchors.verticalCenter: gerdali.verticalCenter
        width: axis_left_label_c.width
        height: axis_left_label_f.height
        color: parent.color

        Text
        {
            id: axis_left_label_c
            text:
            {
                if(cntName==="L")
                {
                    if(axisState==="1")
                    {
                        "Win   #4"
                    }
                }
                else if(cntName==="R")
                {
                    if(axisState==="1")
                    {
                        "    + Left"
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
            id: axis_left_label_f
            text:
            {
                if(cntName==="L")
                {
                    if(axisState==="1")
                    {
                        "\uf061"
                    }
                }
                else if(cntName==="R")
                {
                    if(axisState==="1")
                    {
                        "\uf17a"
                    }
                }
            }
            font.family:
            {
                if(cntName==="L")
                {
                    if(axisState==="1")
                    {
                        fontAwesome.name
                    }
                }
                else if(cntName==="R")
                {
                    if(axisState==="1")
                    {
                        fontAwesome_brand.name
                    }
                }
            }
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
                        3
                    }
                }
                else if(cntName==="R")
                {
                    if(axisState==="1")
                    {
                        -18
                    }
                }
            }
        }
    }

    Rectangle
    {
        id: axis_down_label
        anchors.top: gerdali.bottom
        anchors.topMargin: 13
        anchors.horizontalCenter: gerdali.horizontalCenter
        width: axis_down_label_c.width
        height: axis_down_label_f.height
        color: parent.color

        Text
        {
            id: axis_down_label_c
            text:
            {
                if(cntName==="L")
                {
                    if(axisState==="1")
                    {
                        "Win   #3"
                    }
                }
                else if(cntName==="R")
                {
                    if(axisState==="1")
                    {
                        "Monitor   Win"
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
            id: axis_down_label_f
            text:
            {
                if(cntName==="L")
                {
                    if(axisState==="1")
                    {
                        "\uf061"
                    }
                }
                else if(cntName==="R")
                {
                    if(axisState==="1")
                    {
                        "\uf060"
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
                        3
                    }
                }
                else if(cntName==="R")
                {
                    if(axisState==="1")
                    {
                        11
                    }
                }
            }
        }
    }

    Rectangle
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
            }
            else if(cntName==="R")
            {
                if(axisState==="1")
                {
                    10
                }
            }
        }
        anchors.verticalCenter: gerdali.verticalCenter
        width: axis_right_label_c.width
        height: axis_right_label_f.height
        color: parent.color

        Text
        {
            id: axis_right_label_c
            text:
            {
                if(cntName==="L")
                {
                    if(axisState==="1")
                    {
                        "Win   #2"
                    }
                }
                else if(cntName==="R")
                {
                    if(axisState==="1")
                    {
                        "    + Right"
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
            id: axis_right_label_f
            text:
            {
                if(cntName==="L")
                {
                    if(axisState==="1")
                    {
                        "\uf061"
                    }
                }
                else if(cntName==="R")
                {
                    if(axisState==="1")
                    {
                        "\uf17a"
                    }
                }
            }
            font.family:
            {
                if(cntName==="L")
                {
                    if(axisState==="1")
                    {
                        fontAwesome.name
                    }
                }
                else if(cntName==="R")
                {
                    if(axisState==="1")
                    {
                        fontAwesome_brand.name
                    }
                }
            }
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
                        3
                    }
                }
                else if(cntName==="R")
                {
                    if(axisState==="1")
                    {
                        -20
                    }
                }
            }
        }
    }

}
