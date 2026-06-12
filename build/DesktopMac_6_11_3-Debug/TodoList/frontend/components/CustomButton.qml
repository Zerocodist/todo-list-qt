import QtQuick
import QtQuick.Controls

Button {

    background: Rectangle {
        radius: 10
        color: "#3b82f6"
    }

    contentItem: Text {
        text: parent.text
        color: "white"

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

}
