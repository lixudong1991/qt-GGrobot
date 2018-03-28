#ifndef FTPMANAGER_H
#define FTPMANAGER_H

#include <QNetworkAccessManager>
#include <QFile>
#include<QUrl>
#include<QNetworkRequest>
#include<QNetworkReply>
#include "head.h"
class FtpManager : public QObject
{
    Q_OBJECT

public:
    explicit FtpManager(QObject *parent = 0);
    // 设置地址和端口
    void setHostPort(const QString &host, int port = 21)
    {
        m_pUrl.setHost(host);
        m_pUrl.setPort(port);
    }
    // 设置登录 FTP 服务器的用户名和密码
    void setUserInfo(const QString &userName, const QString &password);

    // 下载文件
    void get(const QString &fileName);

    void setFilename(const QString &n)
    {
         name=n;
    }

signals:
    void error(QNetworkReply::NetworkError);
    // 上传进度
    void uploadProgress(qint64 bytesSent, qint64 bytesTotal);
    // 下载进度
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);

    void finishe(QString);
private slots:
    // 下载过程中写文件
    void finished();
private:
    QUrl m_pUrl;
    QFile m_file;
    QNetworkAccessManager m_manager;
    QString name;
};


#endif // FTPMANAGER_H
