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


#define STATUS_DAIJI "status_to_daiji" //待机模式设置
#define STATUS_STARTAUTO "status_to_kaishizixun" //开始自动巡检
#define STATUS_PAUSEAUTO "status_to_zantingzixun" //暂停自动巡检
#define STATUS_CONTINUEAUTO "status_to_jixuzixun" //继续自动巡检
#define STATUS_QUICKBACK "status_to_fanhang" //快速返航（停止自动巡检）
#define STATUS_DEBUG "statusto_tiaoshi" //调试模式设置
#define CTR_GOROWARD "ctr_goforward" //前进
#define CTR_GOBACK "ctr_goback" //后退
#define XCTR_GOBACK "xctr_stop" //后退
#define CTR_GOLEFT "ctr_goleft" //左转
#define CTR_GORIGHT "ctr_goright" //右转




using namespace zsummer::log4z;

#endif // HEAD_H
