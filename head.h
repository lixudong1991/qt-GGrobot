#ifndef HEAD_H
#define HEAD_H
#include <QApplication>
#include <QDialog>
#include <QPoint>
#include <QWidget>
#include <QTabWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QDesktopWidget>
#include <QTranslator>
#include <QStackedWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QLabel>
#include <QPainter>
#include <QToolButton>
#include <QPainterPath>
#include <QDesktopWidget>
#include <QRect>
#include <QList>
#include <QMap>
#include <QStringList>
#include <QSignalMapper>
#include <QMenu>
#include <qmath.h>
#include <QAction>
#include <QLineEdit>
#include <QStackedLayout>
#include <QCheckBox>
#include <QComboBox>
#include <QComboBox>
#include <QListWidget>
#include <QLabel>
#include <QTimer>
#include <QTextBrowser>
#include <QImage>
#include <QPixmap>
#include <QIcon>
#include <QMessageBox>
#include <QButtonGroup>
#include <QFile>
#include <QRgb>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QComboBox>
#include <QDateTime>
#include <QUrl>
#include <QFile>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QThread>

#include "log4z.h"
#include "common.h"

#define CH(a) QString::fromLocal8Bit(a)
#define NTOS(a) QString::number(a)
#define DATEFORMAT "yyyy-MM-dd hh:mm:ss"
#define FILECACHEPATH    QString("cache/")
#define EXPORTPATH    QString("exportcache/")
#define SAVEVEDIO    QString("vedios/")
#define SAVEPICTURE    QString("pictures/")

using namespace zsummer::log4z;

#endif // HEAD_H
