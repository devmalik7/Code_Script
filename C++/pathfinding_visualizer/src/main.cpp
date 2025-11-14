#include <QApplication>
#include <QMetaType>
#include <QVector>
#include <QPoint>
#include "MainWindow.hpp"

// Register meta types used in queued connections
Q_DECLARE_METATYPE(QVector<QVector<int>>)

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    qRegisterMetaType<QVector<QVector<int>>>("QVector<QVector<int>>");
    qRegisterMetaType<QPoint>("QPoint");

    MainWindow w;
    w.show();
    return app.exec();
}
