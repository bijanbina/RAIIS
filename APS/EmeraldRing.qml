import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

Rectangle {
    width: 300
    height: 300
    color: "#444444"

    property string centre_str: "Data"
    property real value_x: 30.0
    property real value_y: 50.0
    property real value_z: 80.0
    Label{
        anchors.centerIn: parent
        text: centre_str
        color: "#eeeeee"
        z:3
    }
    Canvas {
        id: canvas_x
        anchors.fill: parent
        onPaint: {
            var ctx = getContext("2d");
            //ctx.fillStyle = Qt.rgba(1, 0, 0, 1);
            ctx.beginPath();
            ctx.arc(150, 150, 85, -value_x*Math.PI/180.0/2-Math.PI/2, value_x*Math.PI/180.0/2-Math.PI/2, false)
            ctx.strokeStyle="#00ffc5";
            ctx.lineWidth=5;
            ctx.stroke();
            //ctx.fillRect(0, 0, width, height);
        }
        z:1
    }

    Canvas {
        id: canvas_y
        anchors.fill: parent
        onPaint: {
            var ctx = getContext("2d");
            //ctx.fillStyle = Qt.rgba(1, 0, 0, 1);
            ctx.beginPath();
            ctx.arc(150, 150, 100, -value_y*Math.PI/180.0/2-Math.PI/2, value_y*Math.PI/180.0/2-Math.PI/2, false)
            ctx.strokeStyle="#00ffc5";
            ctx.lineWidth=5;
            ctx.stroke();
            //ctx.fillRect(0, 0, width, height);
        }
        z:1
    }
    Canvas {
        id: canvas_z
        anchors.fill: parent
        onPaint: {
            var ctx = getContext("2d");
            //ctx.fillStyle = Qt.rgba(1, 0, 0, 1);
            ctx.beginPath();
            ctx.arc(150, 150, 115, -value_z*Math.PI/180.0/2-Math.PI/2, value_z*Math.PI/180.0/2-Math.PI/2, false)
            ctx.strokeStyle="#00ffc5";
            ctx.lineWidth=5;
            ctx.stroke();
            //ctx.fillRect(0, 0, width, height);
        }
        z:1
    }
}
