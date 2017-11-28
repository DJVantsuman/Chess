import QtQuick 2.4
import QtQuick.Controls 1.3

ApplicationWindow {
    id: main

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

    Loader {
        source: "StartWindow.qml"
    }
}
