#include "startwindow.h"
#include <iostream>
#include <QLabel>

StartWindow::StartWindow()
{
    QLabel *wellcom = new QLabel;
    wellcom->setText("Wellcom to Chess pro game");
    wellcom->show();
   // std::cout << "Wellcom to Chess pro game" << std::endl;
}
