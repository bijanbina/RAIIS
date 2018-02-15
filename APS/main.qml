import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    color: "#444444"
    /*GridLayout{
        anchors.fill: parent
        columns: 2
    }*/

    Label{
        x: 120;y:100
        Layout.alignment: Qt.AlignHCenter
        text: gyro_str
        color: "#eeeeee"
    }
    Label{
        x: 420;y:100
        Layout.alignment: Qt.AlignHCenter
        text: mag_str
        color: "#eeeeee"
    }
    Label{
        x: 120;y:350
        Layout.alignment: Qt.AlignHCenter
        text: aux_str
        color: "#eeeeee"
    }
    Label{
        x: 420;y:350
        Layout.alignment: Qt.AlignHCenter
        text: acc_str
        color: "#eeeeee"
    }

    function addLast()
    {
        sprite.context = sprite.context + messageNxt;
    }

    //Variables
    property var component;
    property var sprite;


    //Signals:
    signal newMessage(string message)

    //Property

    //these values get updated inside c sources code
    property bool isConnected: false
    property string gyro_str: "Gyro Data"
    property string mag_str: "Mag Data"
    property string aux_str: "Aux Data"
    property string acc_str: "Acc Data"
}
