#include "connectionsettingdialog.h"
#include "ui_connectionsettingdialog.h"
#include "LoggingCategories/loggingcategories.h"
#include <QPushButton>

ConnectionSettingDialog::ConnectionSettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionSettingDialog)
{
    ui->setupUi(this);

    readConnData();
    qInfo(logInfo()) << "Открытие диалога настройки подключения.";
}

ConnectionSettingDialog::~ConnectionSettingDialog()
{
    delete ui;
}

void ConnectionSettingDialog::readConnData()
{
    QSettings settings("MposInstruments.cfg",QSettings::IniFormat);
    settings.beginGroup("DATABASE");
    ui->lineEditServer->setText(settings.value("HostName").toString());
    ui->lineEditDatabase->setText(settings.value("DataBase").toString());
    ui->lineEditUser->setText(settings.value("User").toString());
    ui->lineEditPassword->setText(settings.value("Password").toString());
    settings.endGroup();

}

void ConnectionSettingDialog::saveConnData()
{
    QSettings settings("MposInstruments.cfg",QSettings::IniFormat);
    settings.beginGroup("DATABASE");
    settings.setValue("HostName",ui->lineEditServer->text().trimmed());
    settings.setValue("DataBase",ui->lineEditDatabase->text().trimmed());
    settings.setValue("User",ui->lineEditUser->text().trimmed());
    settings.setValue("Password",ui->lineEditPassword->text().trimmed());
    settings.endGroup();


}


void ConnectionSettingDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    switch (ui->buttonBox->standardButton(button)) {
    case QDialogButtonBox::Save:
        saveConnData();
        this->accept();
        break;
    case QDialogButtonBox::Close:
        this->reject();
        break;
    default:
        break;
    }
}
