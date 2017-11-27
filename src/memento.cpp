#include "memento.h"

Memento::Memento() {

}

Memento::~Memento() {

}

void Memento::loadHistory() {
    QFile in("history.bin");
    if( in.open( QIODevice::ReadOnly ) ) {
        int t, x, y;
        QDataStream stream( &in );
        for (int i = 0; !in.atEnd(); i += 3) {
            stream >> t >> x >> y;
             _state << t;
             _state << x;
             _state << y;
        }
        in.close();
        }
}

void Memento::setState(QList<int> log, int playerNamber) {
        QFile file("history.bin");
        if(file.open(QIODevice::WriteOnly)) {
            QDataStream stream(&file);
            stream. setVersion(QDataStream::Qt_5_6);
            for (int i = 0; i < log.size(); i++)
                stream << log[i];
            stream << playerNamber << playerNamber << playerNamber;
        }
        file.close();
}

QList<int> Memento::getState() {
    loadHistory();
    return _state;
}
