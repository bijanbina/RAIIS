import QtQuick 2.0
import QtMultimedia 5.0

Item {
    anchors.fill: parent
    MouseArea
    {
    id :loloArea
    anchors.fill: parent
    property string videoLocation
    videoLocation : "http://192.168.1.2:8080/video"

    Camera {
        id: camera

    }

    VideoOutput{
        id: mediaplayer
        source :camera
        anchors.fill : parent

    }
    //

    VideoOutput {
        source: mediaplayer
        anchors.fill: parent
        focus : visible // to receive focus and capture key events when visible
    }
}



}
