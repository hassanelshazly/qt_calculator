#include "mainwindow.h"
#include <QApplication>
#include <QFont>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont font("Courier New");
    font.setStyleHint(QFont::Monospace);
    a.setFont(font);
    MainWindow w;
    w.show();

    return a.exec();
}
