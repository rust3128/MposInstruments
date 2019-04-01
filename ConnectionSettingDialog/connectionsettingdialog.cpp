#include "connectionsettingdialog.h"
#include "ui_connectionsettingdialog.h"

ConnectionSettingDialog::ConnectionSettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionSettingDialog)
{
    ui->setupUi(this);
}

ConnectionSettingDialog::~ConnectionSettingDialog()
{
    delete ui;
}
