import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Todo List")

    Material.theme: Material.Dark
    Material.accent: Material.Blue

    HomePage {
        anchors.fill: parent
    }


}
