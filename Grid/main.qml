import QtQuick 2.1
import QtQuick.Window 2.0

Window {
    id:page
    visible: true
    property alias miheight:page.width
    color:"#171717"
    minimumHeight: 405
    minimumWidth: 720
    //Properties
    property string ipAddress: "192.168.1.101"

    //Signals:
    signal mousePressed(real x, real y)
    signal mouseReleased(real x, real y)

    MouseArea{
        id: screen_area
        anchors.fill: parent
        z: 1
        onPressed: mousePressed(mouseX/page.width,mouseY/page.height)
        onReleased: mouseReleased(mouseX/page.width,mouseY/page.height)
    }

    Rectangle{
        id: pageOverlay
        anchors.fill: parent

        CamLCD{}
    }
}
