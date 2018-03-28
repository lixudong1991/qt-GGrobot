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
    // ���õ�ַ�Ͷ˿�
    void setHostPort(const QString &host, int port = 21)
    {
        m_pUrl.setHost(host);
        m_pUrl.setPort(port);
    }
    // ���õ�¼ FTP ���������û���������
    void setUserInfo(const QString &userName, const QString &password);

    // �����ļ�
    void get(const QString &fileName);

    void setFilename(const QString &n)
    {
         name=n;
    }

signals:
    void error(QNetworkReply::NetworkError);
    // �ϴ�����
    void uploadProgress(qint64 bytesSent, qint64 bytesTotal);
    // ���ؽ���
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);

    void finishe(QString);
private slots:
    // ���ع�����д�ļ�
    void finished();
private:
    QUrl m_pUrl;
    QFile m_file;
    QNetworkAccessManager m_manager;
    QString name;
};


#endif // FTPMANAGER_H
