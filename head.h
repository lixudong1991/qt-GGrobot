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


#define STATUS_DAIJI "status_to_daiji" //����ģʽ����
#define STATUS_STARTAUTO "status_to_kaishizixun" //��ʼ�Զ�Ѳ��
#define STATUS_PAUSEAUTO "status_to_zantingzixun" //��ͣ�Զ�Ѳ��
#define STATUS_CONTINUEAUTO "status_to_jixuzixun" //�����Զ�Ѳ��
#define STATUS_QUICKBACK "status_to_fanhang" //���ٷ�����ֹͣ�Զ�Ѳ�죩
#define STATUS_DEBUG "statusto_tiaoshi" //����ģʽ����
#define CTR_GOROWARD "ctr_goforward" //ǰ��
#define CTR_GOBACK "ctr_goback" //����
#define XCTR_GOBACK "xctr_stop" //����
#define CTR_GOLEFT "ctr_goleft" //��ת
#define CTR_GORIGHT "ctr_goright" //��ת




using namespace zsummer::log4z;

#endif // HEAD_H
