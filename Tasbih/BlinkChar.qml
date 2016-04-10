import QtQuick 2.5

Rectangle {
    id: redSquare
    color: "transparent"
    width: 10
        Rectangle {
            id: rect2
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 1
            anchors.left: parent.left
            width: 10
            height: 3
            /*transitions: Transition {
                NumberAnimation {
                    loops: Animation.Infinite
                    from: 0
                    to: 1
                    properties: "opacity"
                    easing.type: Easing.InOutQuad;
                    duration: 1000
                }
                reversible: true
            }
            states: State {
                name: "shownd"; when: mouseArea.pressed
                PropertyChanges { target: rect2; opacity: 1; }
            }*/
            SequentialAnimation on opacity {
                id: xAnim
                // Animations on properties start running by default
                running: true
                loops: Animation.Infinite // The animation is set to loop indefinitely
                NumberAnimation { from: 1; to: 0; duration: 500; easing.type: Easing.InOutQuad }
                NumberAnimation { from: 0; to: 1; duration: 500; easing.type: Easing.InOutQuad }
                PauseAnimation { duration: 250 } // This puts a bit of time between the loop
            }
        }
}
