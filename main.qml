import QtQuick 2.9
import QtQuick.Window 2.1
import QtQuick.Controls 1.0
import thuyet.receiver.com 1.0

Window {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("Receiver")


    Receiver {
        id: receiver
    }


    TextField {
        id: textGroupAddr
        x: 113
        y: 168
        width: 284
        height: 40
        text: qsTr("239.255.43.21")
    }
    TextField {
        id: textPort
        x: 113
        y: 108
        width: 284
        height: 40
        text: qsTr("45454")
    }
    TextField {
        id: textData
        x: 113
        y: 228
        width: 284
        height: 40
        text: qsTr("Show data")
    }
    Button {
        id: choosebtn
        x: 447
        y: 168
        text: qsTr("Chosen")
        onClicked: {
            receiver.getInfor(textGroupAddr.text, textPort.text);
        }
    }

    Button {
        id: uploadbtn
        x: 447
        y: 108
        text: qsTr("Start")
        onClicked: {
        }
    }
}
