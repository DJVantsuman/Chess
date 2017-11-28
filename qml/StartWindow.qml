import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2

Window {
    id: startWindow
    visible: true
    width: 800
    height: 600
    maximumHeight: height
    maximumWidth: width
    minimumHeight: height
    minimumWidth: width

    Image {
      source: "/images/chess_board.jpg"
      height: startWindow.height
      width: startWindow.width
    }

        Button {
            id: startButton
            text: qsTr("New Game")
            width: 180
            height: 50
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.topMargin: 50
            anchors.rightMargin: startWindow.width/2 - width/2

            onClicked: {
                logic.startNewGame()
                logicWindow.show()
                startWindow.hide()
            }
        }

        Button {
            id: loadButton
            text: qsTr("Load Game")
            width: 180
            height: 50
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.topMargin: 110
            anchors.rightMargin: startWindow.width/2 - width/2

            onClicked: {
                logic.loadGame();
                loadWindow.show()
                startWindow.hide()
            }
        }

        Button {
          id: exitButton
          text: "Exit"
          width: 180
          height: 50
          anchors.right: parent.right
          anchors.bottom: parent.bottom
          anchors.rightMargin: startWindow.width/2 - width/2
          anchors.bottomMargin: 50

          onClicked: {
            startWindow.close()
          }
        }

    Logic {
        id: logicWindow
        visible: false
    }

    LoadWindow {
        id: loadWindow
        visible: false
    }
}
