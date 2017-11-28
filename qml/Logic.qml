import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2

Window {
    id: logicWindow
    title: qsTr("Chess")
    visible: true
    width: 800
    height: 600
    maximumHeight: height
    maximumWidth: width
    minimumHeight: height
    minimumWidth: width

    Item {
      id: gameBoard
      x: 0
      y: 0
      width : logic.boardSize * squareSize
      height: logic.boardSize * squareSize

      Image {
        source: "/images/chess_board.jpg"
        height: gameBoard.height
        width: gameBoard.width
      }

      Repeater {
        model: logic

        Image {
          id: image
          height: squareSize
          width : squareSize

          x: squareSize * positionX
          y: squareSize * positionY

          source: images[type].imgPath

          MouseArea {
            anchors.fill: parent
            drag.target: parent

            property int startX: 0
            property int startY: 0

            onPressed: {
              startX = parent.x;
              startY = parent.y;
            }

            onReleased: {
              var fromX = startX / squareSize;
              var fromY = startY / squareSize;
              var toX   = (parent.x + mouseX) / squareSize;
              var toY   = (parent.y + mouseY) / squareSize;

              if (!logic.move(fromX, fromY, toX, toY)) {
                parent.x = startX;
                parent.y = startY;
              }
              else
                  logic.saveStep();
            }
          }
        }
      }
    }

    Button {
      id: saveButton
      width: 180
      height: 50
      anchors.right: parent.right
      anchors.top: parent.top
      anchors.rightMargin: 20
      anchors.topMargin: 40
      text: "Save game"

      onClicked: {
        logic.saveGame();
      }
    }

    Button {
      id: exitButton
      width: 180
      height: 50
      anchors.right: parent.right
      anchors.bottom: parent.bottom
      anchors.rightMargin: 20
      anchors.bottomMargin: 40
      text: "Stop"

      onClicked: {
         logic.startNewGame();
         logicWindow.close()
         startWindow.show()
      }
    }
}
