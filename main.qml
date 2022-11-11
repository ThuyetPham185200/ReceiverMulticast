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
        text: qsTr("224.1.1.6")
    }
    TextField {
        id: textPort
        x: 113
        y: 108
        width: 284
        height: 40
        text: qsTr("10669")
    }
    Button {
        id: choosebtn
        x: 447
        y: 168
        text: qsTr("Start")
        onClicked: {
            receiver.getInfor(textGroupAddr.text, textPort.text);
        }
    }


}
