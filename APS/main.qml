import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    GridLayout{
        anchors.fill: parent
        columns: 2
        Label{
            Layout.alignment: Qt.AlignHCenter
            text: gyro_str
        }
        Label{
            Layout.alignment: Qt.AlignHCenter
            text: mag_str
        }
        Label{
            Layout.alignment: Qt.AlignHCenter
            text: aux_str
        }
        Label{
            Layout.alignment: Qt.AlignHCenter
            text: acc_str
        }
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
