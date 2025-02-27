#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(850,600);
    w.setWindowTitle("ImageToolkits v1.2.0");
    w.show();
    return a.exec();
}
