#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont font("汉仪旗黑-55S");
    a.setFont(font);
    MainWindow w;
    w.show();
    return a.exec();
}
