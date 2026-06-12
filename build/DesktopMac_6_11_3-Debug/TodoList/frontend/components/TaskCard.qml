import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    width: ListView.view.width
    height: 60
    radius: 12

    color: "#2c2c2c"

    RowLayout {
        anchors.fill: parent
        anchors.margins: 15

        CheckBox {
            id: cb
            Layout.alignment: Qt.AlignVCenter

            checked: model.completed

            indicator: Rectangle {
                height: 25
                width: 20
                radius: 4

                color: cb.checked ? "#4CAF50" : "#444444"

                border.width: 1
                border.color: "#888888"

                Behavior on color {
                    ColorAnimation {duration: 200}
                }

                Text {
                    anchors.centerIn: parent
                    text: cb.checked ? "✓" : ""
                    color: "white"
                }
            }

            onCheckedChanged: {
                ListModelCpp.updateModel(model.id, cb.checked)
            }
        }


    Item {
        id: root
        Layout.fillWidth: true
        Layout.fillHeight: true

        property bool editing: false

        Label {
            anchors.fill: parent

            visible: !root.editing

            text: model.title

            color: "white"
            font.bold: true
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width
            height: contentHeight
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter


            MouseArea {
                anchors.fill: parent
                onDoubleClicked: root.editing = true
            }
        }

        TextField {
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width
            height: 36
            visible: root.editing
            text: model.title
            focus: root.editing
            opacity: visible ? 1 : 0

            Behavior on opacity {
                NumberAnimation { duration: 200; easing.type: Easing.InOutQuad }
            }

            onAccepted: {
                ListModelCpp.updateTitle(model.id, text)
                root.editing = false
            }

            onActiveFocusChanged: {
                if(!activeFocus && root.editing) {
                    ListModelCpp.updateTitle(model.id, text)
                    root.editing = false
                }
            }

            onEditingFinished: {
                root.editing = false
            }
        }
    }
        Button {
            text: "Delete"
            implicitHeight: 36
            Layout.alignment: Qt.AlignCenter
            onClicked: ListModelCpp.deleteTask(model.id)
        }
    }
}
