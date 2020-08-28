import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
 import QtQml 2.2
//https://developer.apple.com/healthkit/
//label sefid textbox abi
Label
{
    property date currentDate: new Date()
    property string time;
    property var locale: Qt.locale()

    anchors.leftMargin: 30
    text :
"Server Time   : %1
Signal level  : 20dBm
input voltade : 200mV
noise voltage : 723uV
system status : OK.
LED Light     : Green".arg(time)
    color: "#e8e9e3";
    font.pixelSize: 15
    font.family: consolas.name
    MouseArea{
        anchors.fill: parent
        onClicked: {
            console.log(parent.lineHeight)
        }
    }
    Timer
    {
        interval: 100
        running: true
        repeat: true
        onTriggered: test()
    }
    function test()
    {
        currentDate = new Date()
        time = currentDate.toLocaleString(locale,"HH:mm:ss");
    }
}
