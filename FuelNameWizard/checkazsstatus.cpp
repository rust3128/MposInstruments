#include "checkazsstatus.h"
#include "LoggingCategories/loggingcategories.h"
#include <QTcpSocket>

CheckAzsStatus::CheckAzsStatus(int term, QString ip, QObject *parent) : QObject(parent)
{
    m_serverName = ip;
    m_terminalID = term;

}

void CheckAzsStatus::slotCheckAzsStatus()
{

    bool status;
    QTcpSocket *tcpSocket = new QTcpSocket();
    tcpSocket->connectToHost(m_serverName, 3050);
    if(tcpSocket->waitForConnected(30000)){
        status = true;
    } else {
        status = false;
    }
    emit signalSendResult(status);
    emit finished(m_terminalID);
}
