#include <QApplication>
#include <windows.h>
#include "widget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
     HANDLE hMutex = CreateMutex(NULL, TRUE, L"RobotOperation");
     if(hMutex != NULL)
      {
          if(GetLastError() == ERROR_ALREADY_EXISTS)
          {
              QMessageBox::critical(qApp->activeWindow(), QObject::tr("An instance of this application has been run!"), QObject::tr("Only one instance can be run at a time!"));
              return 0;
          }
     }
    ILog4zManager::getRef().setLoggerDisplay(LOG4Z_MAIN_LOGGER_ID,false);
    ILog4zManager::getRef().start();
    Widget loginwid;
    loginwid.show();
    return a.exec();
}
