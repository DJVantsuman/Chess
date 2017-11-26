import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Window 2.2

Window {
    id: loadWindow
    title: qsTr("Chess")
    visible: true
    width: 800
    height: 600
    maximumHeight: height
    maximumWidth: width
    minimumHeight: height
    minimumWidth: width

    property int squareSize: 70

    property var images: [
      {'imgPath' : "/images/white_pawn.svg"},
      {'imgPath' : "/images/white_knight.svg"},
      {'imgPath' : "/images/white_bishop.svg"},
      {'imgPath' : "/images/white_rook.svg"},
      {'imgPath' : "/images/white_queen.svg"},
      {'imgPath' : "/images/white_king.svg"},
      {'imgPath' : "/images/black_pawn.svg"},
      {'imgPath' : "/images/black_knight.svg"},
      {'imgPath' : "/images/black_bishop.svg"},
      {'imgPath' : "/images/black_rook.svg"},
      {'imgPath' : "/images/black_queen.svg"},
      {'imgPath' : "/images/black_king.svg"},
    ]

    Item {
      id: gameBoard
      visible: true
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

   /*       MouseArea {
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
              else {
                  playerNamber == 1 ? number1.text = "Player 2" : number1.text = "Player 1";
                  playerNamber = playerNamber == 1 ? 2 : 1;
              }
            }
          } */
        }
      }
    }

    Button {
      id: prevButton
      text: "Prev"
      width: 80
      height: 40
      anchors.right: parent.right
      anchors.top: parent.top
      anchors.rightMargin: 120
      anchors.topMargin: 20

      onClicked: {

      }
    }

    Button {
      id: nextButton
      text: "Next"
      width: 80
      height: 40
      anchors.right: parent.right
      anchors.top: parent.top
      anchors.rightMargin: 20
      anchors.topMargin: 20

      onClicked: {

      }
    }

    Button {
      id: startButton
      text: "Start"
      width: 180
      height: 50
      anchors.right: parent.right
      anchors.top: parent.top
      anchors.rightMargin: 20
      anchors.topMargin: 80

      onClicked: {
        logicWindow.show()
        loadWindow.hide()
      }
    }

    Button {
      id: exitButton
      text: "Stop"
      width: 180
      height: 50
      anchors.right: parent.right
      anchors.bottom: parent.bottom
      anchors.rightMargin: 20
      anchors.bottomMargin: 40

      onClicked: {
        startWindow.show()
        loadWindow.hide()
      }
    }
}
