#include <QFileInfo>
#include "ftpmanager.h"
#include <QProcess>
FtpManager::FtpManager(QObject *parent)
    : QObject(parent)
{
    // 设置协议
    m_pUrl.setScheme("ftp");
}

// 设置地址和端口
// inline


// 设置登录 FTP 服务器的用户名和密码
void FtpManager::setUserInfo(const QString &userName, const QString &password)
{
    m_pUrl.setUserName(userName);
    m_pUrl.setPassword(password);
}


// 下载文件
void FtpManager::get(const QString &fileName)
{

    m_file.setFileName(fileName);
    m_pUrl.setPath(name);

    QNetworkReply *pReply = m_manager.get(QNetworkRequest(m_pUrl));
    connect(pReply, SIGNAL(finished()), this, SLOT(finished()));
    connect(pReply, SIGNAL(downloadProgress(qint64, qint64)), this, SIGNAL(downloadProgress(qint64, qint64)));
    connect(pReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SIGNAL(error(QNetworkReply::NetworkError)));

}

// 下载过程中写文件
void FtpManager::finished()
{
    QNetworkReply *pReply = qobject_cast<QNetworkReply *>(sender());
    switch (pReply->error())
    {
    case QNetworkReply::NoError :
    {
        m_file.open(QIODevice::WriteOnly | QIODevice::Append);
        m_file.write(pReply->readAll());
        m_file.flush();
        m_file.close();
    }
        break;
    default:
        LOGE("QNetworkReply::Error:"<<pReply->error());
        break;
    } 
     LOGI("Ftpmanager emit finishe:"<<name.toStdString());
    emit finishe(name);
    pReply->deleteLater();   
}

