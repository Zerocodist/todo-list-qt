import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import TodoList

Item {

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 15

        TaskInput {
                id: input
                Layout.fillWidth: true
        }

        RowLayout {

        CustomButton {
               text: "Clear All"
               onClicked: ListModelCpp.clearAll()
        }

        CustomButton {
                text: "Search"
                onClicked: ProxyModel.setSearchText(input.text)
        }
    }

        ListView {
            Layout.fillWidth: true
            Layout.fillHeight:  true

            spacing: 10
            clip: true

            model: ProxyModel

            delegate: TaskCard {

            }
        }
    }

    Toast {
        id: toast
    }

    Connections {
                target: ListModelCpp

                function onStatus(message) {
                        toast.show(message)
                }
        }
}