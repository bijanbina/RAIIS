import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

Window {
    visible: true
    width: 600
    height: 600
    title: qsTr("Hello World")
    color: "#444444"
    /*GridLayout{
        anchors.fill: parent
        columns: 2
    }*/

    EmeraldRing{
        x: 0;y:0
        value_x: gyro_x
        value_y: gyro_y
        value_z: gyro_z
        centre_str: gyro_str
    }
    EmeraldRing{
        x: 300;y:0
        value_x: mag_x
        value_y: mag_y
        value_z: mag_z
        centre_str: mag_str
    }
    EmeraldRing{
        x: 0;y:300
        value_x: aux_x
        value_y: aux_y
        value_z: aux_z
        centre_str: aux_str
    }
    EmeraldRing{
        x: 300;y:300
        //Layout.alignment: Qt.AlignHCenter
        centre_str: acc_str
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
    property real gyro_x: 130
    property real gyro_y: 100
    property real gyro_z: 80
    property real mag_x: 45
    property real mag_y: 70
    property real mag_z: 80
    property real aux_x: 21
    property real aux_y: 66
    property real aux_z: 170
    property string gyro_str: "Gyro Data"
    property string mag_str: "Mag Data"
    property string aux_str: "Aux Data"
    property string acc_str: "Acc Data"
}
