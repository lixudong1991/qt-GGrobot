#include "main_widget.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ILog4zManager::getRef().start();
    MainWidget w;
    w.show();
    return a.exec();
}
