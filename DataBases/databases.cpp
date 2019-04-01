#include "databases.h"
#include "LoggingCategories/loggingcategories.h"
#include "ConnectionSettingDialog/connectionsettingdialog.h"
#include <QSettings>
#include <QFile>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>


DataBases::DataBases(QObject *parent) : QObject(parent)
{

}

bool DataBases::connectCentralDatabase()
{
    bool result = true;
    QSettings settings("MposInstruments.cfg", QSettings::IniFormat);

    QSqlDatabase db = QSqlDatabase::addDatabase("QIBASE","cental");

    settings.beginGroup("DATABASE");
    db.setHostName(settings.value("HostName").toString());
    db.setDatabaseName(settings.value("DataBase").toString());
    db.setUserName(settings.value("User").toString());
    db.setPassword(settings.value("Password").toString());
    settings.endGroup();

    if(!db.open()) {
        qCritical(logCritical()) <<  "Не возможно подключиться к базе данных." << endl << "Причина:" << db.lastError().text();
        int rez = QMessageBox::question(nullptr, QObject::tr("Ошибка подключения"),
                              QString("Не могу установить соединение с базой данных.\nПричина: %1\nПроверить настройки подключения?").arg(db.lastError().text()),
                              QMessageBox::Yes | QMessageBox::No);
        if(rez == QMessageBox::Yes) {
            ConnectionSettingDialog *connDlg = new ConnectionSettingDialog();
            connDlg->exec();
        }
        result = false;
    }


    return result;
}
