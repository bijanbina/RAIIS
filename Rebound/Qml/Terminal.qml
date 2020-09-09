import QtQuick 2.5
import "qrc:/"

Rectangle{

    function refreshFocus()
    {
        terminalEditor.forceActiveFocus();
    }


    TextEdit
    {
        id: terminalOutput
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.leftMargin: 30
        text : "$ git push origin master
Warning: Permanently added the RSA host key for IP address '192.30.252.122'.
Counting objects: 20, done."
        color: "#e8e9e3";
        selectionColor : "#4C5466"
        selectByMouse: true;
        font.pixelSize: 14
        font.family: consolas.name
        readOnly: true
        MouseArea
        {
            anchors.fill: parent
            cursorShape: Qt.IBeamCursor
            acceptedButtons: Qt.NoButton
        }
    }

    TextEdit
    {
        id: commandSymbol
        anchors.left: parent.left
        anchors.top: terminalOutput.bottom
        anchors.leftMargin: 30
        text : "$ "
        color: "#e8e9e3";
        selectionColor : "#4C5466"
        selectByMouse: true;
        font.pixelSize: 14
        font.family: consolas.name
        readOnly: true
        MouseArea
        {
            anchors.fill: parent
            cursorShape: Qt.IBeamCursor
            acceptedButtons: Qt.NoButton
        }
    }

    TextEdit{
        id: terminalEditor
        anchors.left: commandSymbol.right
        anchors.top: terminalOutput.bottom
        //anchors.topMargin: 35
        text : ""
        color: "#e8e9e3";
        selectionColor : "#4C5466"
        //selectedTextColor : "#00FF00"
        font.pixelSize: 14
        font.family: consolas.name
        inputMethodHints: Qt.ImhMultiLine
        cursorDelegate: Rectangle{}
        selectByMouse: true;
        cursorPosition: terminalEditor.text.length
        focus: true
    }
//    BlinkChar
//    {
//        anchors.left: terminalEditor.right
//        anchors.top: terminalEditor.top
//        anchors.bottom: terminalEditor.bottom
//    }
}
