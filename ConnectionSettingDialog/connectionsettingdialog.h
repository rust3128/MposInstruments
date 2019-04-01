#ifndef CONNECTIONSETTINGDIALOG_H
#define CONNECTIONSETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class ConnectionSettingDialog;
}

class ConnectionSettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionSettingDialog(QWidget *parent = nullptr);
    ~ConnectionSettingDialog();

private:
    Ui::ConnectionSettingDialog *ui;
};

#endif // CONNECTIONSETTINGDIALOG_H
