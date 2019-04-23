#include "azsfuellist.h"
#include "passconv.h"
#include "LoggingCategories/loggingcategories.h"


#include <QSqlRecord>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

AzsFuelList::AzsFuelList(QSqlRecord conRec, QObject *parent) :
    QObject(parent),
    m_connRecord(conRec)
{

}

void AzsFuelList::slotGetList()
{


    LisstFuelClass lf;

    typedef QVector<LisstFuelClass> vek;
    qRegisterMetaType<vek>("fuels");


    QSqlDatabase db = QSqlDatabase::addDatabase("QIBASE","azs"+m_connRecord.value(0).toString());

    qInfo(logInfo()) << "Hi from thread";

    db.setHostName(m_connRecord.value(1).toString());
    db.setDatabaseName(m_connRecord.value(2).toString());
    db.setUserName("SYSDBA");
    db.setPassword(passConv(m_connRecord.value(3).toString()));

    if(!db.open()) {
        qCritical(logCritical()) << Q_FUNC_INFO << "Не могу подключится к центральной базе"
                                 << endl << db.lastError().text();
        return;
    }

    QSqlQuery q = QSqlQuery(db);
    if(!q.exec("SELECT t.TANK_ID, f.SHORTNAME, f.NAME FROM fuels f "
           "LEFT JOIN tanks t ON t.FUEL_ID = f.FUEL_ID "
           "WHERE f.ISACTIVE = 'T' "
               "order by t.TANK_ID")) {
        qInfo(logInfo()) << Q_FUNC_INFO << "ERROR FUEL List" << q.lastError().text();
    }

    while(q.next()){
        lf.setTankID(q.value(0).toInt());
        lf.setShortName(q.value(1).toString());
        lf.setFuelName(q.value(2).toString());
        flVector.append(lf);
        qInfo(logInfo()) << q.value(0).toInt() << q.value(1).toString() << q.value(2).toString();
    }
    emit signalSendFuelsList(flVector);
    emit signalFinish();
}
