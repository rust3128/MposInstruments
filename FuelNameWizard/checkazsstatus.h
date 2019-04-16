#ifndef CHECKAZSSTATUS_H
#define CHECKAZSSTATUS_H

#include <QObject>

class CheckAzsStatus : public QObject
{
    Q_OBJECT
public:
    explicit CheckAzsStatus(int term, QString ip, QObject *parent = nullptr);

signals:
    void signalSendResult(bool status);
    void finished(int term);

public slots:
    void slotCheckAzsStatus();
private:
    QString m_serverName;
    int m_terminalID;
};

#endif // CHECKAZSSTATUS_H
