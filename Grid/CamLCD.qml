import QtQuick 2.0
import QtMultimedia 5.1

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

        imageProcessing.whiteBalanceMode: CameraImageProcessing.WhiteBalanceFlash


        exposure {
            exposureCompensation: -1.0
            exposureMode: Camera.ExposurePortrait
        }


        imageCapture {
            resolution: "1920x1080"
            onImageCaptured: {
                photoPreview.source = preview  // Show the preview in an Image
            }
        }
    }

    //MediaPlayer {
    VideoOutput{
    id: mediaplayer
        //source: loloArea.videoLocation
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
