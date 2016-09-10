import QtQuick 2.3
import QtQuick.Window 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Window {
    id:page
    visible: true
    property alias miheight:page.width
    color:"#fff"
    minimumHeight: 620
    minimumWidth: 360
    //minimumHeight: 565
    //minimumWidth: 360

    //Properties:
    property string ipAddress: "192.168.1.101"
    property double ratio;

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

    Rectangle
    {
        id: main_window
        Image {
            id: back_image;
            anchors.fill: parent
            source: "qrc:Resources/Screens/start.jpg"
        }

        Rectangle
        {
            id: setting_button
            border.color: "#00f"
            x: 0
            y: 95
            width: 80
            height: 265
            color: "#00000000"

        }

        Rectangle
        {
            id: info_button
            border.color: "#00f"
            x: 85
            y: 165
            width: 95
            height: 105
            color: "#00000000"

        }

        Rectangle
        {
            id: lamp_button
            border.color: "#00f"
            x: 185
            y: 165
            width: 100
            height: 105
            color: "#00000000"

        }

        Rectangle
        {
            id: screen_button
            border.color: "#00f"
            x: 85
            y: 270
            width: 95
            height: 100
            color: "#00000000"

        }

        Rectangle
        {
            id: puzzle_button
            border.color: "#00f"
            x: 185
            y: 270
            width: 100
            height: 100
            color: "#00000000"

        }

        Rectangle
        {
            id: quit_button
            border.color: "#00f"
            x: 85
            y: 375
            width: 195
            height: 80
            color: "#00000000"

        }

        MouseArea {
            anchors.fill: parent
            onClicked: start();
        }
    }



    function start () {
    }

}
