#include "logic.h"
#include "chess.h"
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Logic logic;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("logic", &logic);
    engine.load(QUrl(QStringLiteral("qrc:/qml/StartWindow.qml")));

    return app.exec();
}
