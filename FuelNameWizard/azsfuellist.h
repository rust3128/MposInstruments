#ifndef AZSFUELLIST_H
#define AZSFUELLIST_H
#include "lisstfuelclass.h"
#include <QObject>
#include <QSqlRecord>
#include <QVector>

class AzsFuelList : public QObject
{
    Q_OBJECT
public:
    explicit AzsFuelList(QSqlRecord conRec, QObject *parent = nullptr);

signals:
    void signalSendFuelsList(QVector<LisstFuelClass>);
    void signalFinish();

public slots:
    void slotGetList();
private:
    QSqlRecord m_connRecord;
    QVector<LisstFuelClass> flVector;
};

#endif // AZSFUELLIST_H
