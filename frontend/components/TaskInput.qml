import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

RowLayout {
id: row

    property alias text: taskField.text

    TextField {
        id: taskField
        placeholderText: "Enter task..."
        Layout.fillWidth: true
        focus: true

        onAccepted: {
            ListModelCpp.addTask(taskField.text)
            clear()
        }
    }

    Button {
        text: "add"
        onClicked: {
            ListModelCpp.addTask(taskField.text)
            taskField.text = ""
        }
    }
}

