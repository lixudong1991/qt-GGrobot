#include <QFileInfo>
#include "ftpmanager.h"
#include <QProcess>
FtpManager::FtpManager(QObject *parent)
    : QObject(parent)
{
    // ����Э��
    m_pUrl.setScheme("ftp");
}

// ���õ�ַ�Ͷ˿�
// inline


// ���õ�¼ FTP ���������û���������
void FtpManager::setUserInfo(const QString &userName, const QString &password)
{
    m_pUrl.setUserName(userName);
    m_pUrl.setPassword(password);
}


// �����ļ�
void FtpManager::get(const QString &fileName)
{

    m_file.setFileName(fileName);
    m_pUrl.setPath(name);

    QNetworkReply *pReply = m_manager.get(QNetworkRequest(m_pUrl));
    connect(pReply, SIGNAL(finished()), this, SLOT(finished()));
    connect(pReply, SIGNAL(downloadProgress(qint64, qint64)), this, SIGNAL(downloadProgress(qint64, qint64)));
    connect(pReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SIGNAL(error(QNetworkReply::NetworkError)));

}

// ���ع�����д�ļ�
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

