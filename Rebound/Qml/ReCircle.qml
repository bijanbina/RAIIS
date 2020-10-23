import QtQuick 2.0

Rectangle
{

    property string axisName: ""

    color: "transparent"
    width: 134
    height: width


    Rectangle
    {
        id: c_outer
        width: 85
        height: width
        radius: width/2
        color: parent.color

        border.width: 2
        border.color: "#e8e9e3"
        anchors.centerIn: parent
    }

    Rectangle
    {
        id: c_inner
        width: 71
        height: width
        radius: width/2
        color: parent.color

        border.width: 2
        border.color: "#e8e9e3"
        anchors.centerIn: parent
    }

    Rectangle
    {
        id: c_dashed
        width: 102
        height: width
        anchors.centerIn: parent
        color: parent.color

        Canvas
        {
            id: canvas
            anchors.fill: parent

            onPaint:
            {
                const ctx = canvas.getContext('2d')
                ctx.beginPath()
                ctx.strokeStyle = "#8e939e"
//                ctx.setLineDash([2, 1])
                ctx.arc(canvas.width/2, canvas.height/2, canvas.width/2-1, 0, 2*Math.PI)
                ctx.stroke()
            }
        }

    }

    Text
    {
        id: axis_label
        text: axisName
        font.family: robotoBoldFont.name
        font.pixelSize: 24
        font.weight: Font.Bold
        color: "#e8e9e3"
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Text
    {
        id: axis_label_up
        text: "\uf0d8"
        font.family: fontAwesome.name
        font.pixelSize: 16
        font.weight: Font.Bold
        color: "#e8e9e3"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: -6
    }

    Text
    {
        id: axis_label_left
        text: "\uf0d9"
        font.family: fontAwesome.name
        font.pixelSize: 16
        font.weight: Font.Bold
        color: "#e8e9e3"
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: -2
    }

    Text
    {
        id: axis_label_down
        text: "\uf0d7"
        font.family: fontAwesome.name
        font.pixelSize: 16
        font.weight: Font.Bold
        color: "#e8e9e3"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -5
    }

    Text
    {
        id: axis_label_right
        text: "\uf0da"
        font.family: fontAwesome.name
        font.pixelSize: 16
        font.weight: Font.Bold
        color: "#e8e9e3"
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
    }

}
