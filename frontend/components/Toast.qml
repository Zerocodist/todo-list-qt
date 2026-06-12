import QtQuick

Item  {
  id: root
  width: parent ? parent.width : 200
  height: 40

  property string message: ""
  opacity: 0

  anchors.horizontalCenter: parent.horizontalCenter
  anchors.bottom: parent.bottom
  anchors.bottomMargin: 80

  Behavior on opacity {
      NumberAnimation { duration: 200 }
  }

  Text {
      anchors.centerIn: parent
      text: root.message
      color: "white"
      font.bold: true
  }

  Timer {
      id: t
      repeat: false
      interval: 1200
      onTriggered: root.opacity = 0
  }

  function show(msg) {
      message = msg
      opacity = 1
      t.restart()
  }

}