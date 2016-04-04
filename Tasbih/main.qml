import QtQuick 2.3
import QtQuick.Window 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Window {
    id:page
    visible: false
    property alias miheight:page.width
    minimumHeight: 500
    minimumWidth: 700
    color:"#2F343F"
    x:x_base + (Screen.width  - minimumWidth)  / 2
    y:y_base + (Screen.height - minimumHeight) / 2
    //minimumHeight: 565
    //minimumWidth: 360

    //Properties:
    property string ipAddress: "192.168.1.101"

    //Signals:
    signal morabaSignal
    signal mosalasSignal
    signal dayereSignal
    signal zarbdarSignal
    signal startSignal(string IP)
    signal keySignal(string key)
    signal noneSignal

    //Fonts:
    FontLoader { id: robotoMediumFont ; source: "qrc:Resources/Fonts/Roboto-Medium.ttf" }
    FontLoader { id: robotoRegularFont ; source: "qrc:Resources/Fonts/Roboto-Regular.ttf" }
    //FontLoader { id: robotoBoldFont ; source: "qrc:Resources/Fonts/Roboto-Bold.ttf" }
    FontLoader { id: genomeLight ; source: "qrc:Resources/Fonts/Genome-Thin.otf" }

    FontLoader { id: consolas ; source: "qrc:Resources/Fonts/Consolas.ttf" }



    Rectangle{
        id: paneWindow
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        height: 200
        width: minimumWidth

        color: page.color
        Rectangle{
                id: wifiStatus
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                width: 175
                //color: "#0F343F"
                color: parent.color

                Canvas {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    width: 75
                    height: 75
                    onPaint: {
                        var ctx = getContext("2d");
                        ctx.reset();

                        //ctx.fillStyle = "#0F34FF";
                        //ctx.fillRect(0, 0, width, height);

                        var xStart = width / 2;
                        var yStart = height * 0.9;

                        ctx.beginPath();
                        ctx.fillStyle = "#e8e9e3";
                        ctx.moveTo(xStart, yStart);
                        ctx.arc(xStart, yStart, width/1.25, Math.PI * 5.25 / 4, Math.PI * 6.75 / 4, false);
                        ctx.lineTo(xStart, yStart);
                        ctx.fill();
                    }
                }
        }
        Rectangle{
                id: savedNumber
                anchors.top: parent.top
                anchors.left: wifiStatus.right
                anchors.bottom: parent.bottom
                width: 173
                //color: "#0F343F"
                color: parent.color

                Label
                {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    text : "42"
                    color: "#e8e9e3";
                    font.pixelSize: 102
                    font.family: genomeLight.name
                }
        }
        Rectangle
        {
            id: splitLine
            anchors.left: savedNumber.right
            anchors.leftMargin: 2
            anchors.verticalCenter: parent.verticalCenter
            height: 95
            width: 1
            color: "#e8e9e3";
        }
        Rectangle
        {
            id: infoPanel
            anchors.left: splitLine.right
            anchors.verticalCenter: parent.verticalCenter
            color: "#e8e9e3";
            Label
            {
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                anchors.leftMargin: 30
                text :
"Server Time   : 24:15:33
Signal level  : 20dBm
input voltade : 200mV
noise voltage : 723uV
system status : OK.
LED Light     : Green"
                color: "#e8e9e3";
                font.pixelSize: 15
                font.family: consolas.name
            }
        }
    }

    Rectangle{
        id: tabPane
        anchors.top: paneWindow.bottom
        anchors.topMargin: -9

        anchors.horizontalCenter: parent.horizontalCenter
        color: page.color
        //color:  "#0F34FF";
        height: 30
        width: 256

        Canvas {
            anchors.fill: parent
            onPaint: {
                var ctx = getContext("2d");
                ctx.reset();

                //ctx.fillStyle = "#0F34FF";
                //ctx.fillRect(0, 0, width, height);

                var rect_width  = width-1;
                var rect_height = height-1;
                var rect_radius = 5;
                var xStart = 1;
                var yStart = 1;



                ctx.beginPath();
                ctx.strokeStyle = "#e8e9e3";
                ctx.lineWidth=0.9;
                ctx.moveTo(xStart+rect_radius, yStart);
                ctx.lineTo(xStart+rect_width-rect_radius, yStart);
                ctx.quadraticCurveTo(xStart+rect_width, yStart, rect_width, yStart + rect_radius);
                ctx.lineTo(rect_width, rect_height-rect_radius );
                ctx.quadraticCurveTo(rect_width, rect_height, rect_width - rect_radius, rect_height);
                ctx.lineTo(xStart+rect_radius, rect_height);
                ctx.quadraticCurveTo(xStart, rect_height, xStart, rect_height-rect_radius);
                ctx.lineTo(xStart, yStart+rect_radius);
                ctx.quadraticCurveTo(xStart, yStart, xStart+rect_radius, yStart);
                ctx.stroke();

            }

            MouseArea {
                anchors.fill: parent

                onClicked: console.log("hi")
            }
        }
    }

    Rectangle{
        id: terminalPane
        anchors.top: tabPane.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        color: page.color
    }



    //properties

    property int x_base: 0
    property int y_base: 0

}
