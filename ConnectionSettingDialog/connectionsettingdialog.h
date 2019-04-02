#ifndef CONNECTIONSETTINGDIALOG_H
#define CONNECTIONSETTINGDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <QSettings>

namespace Ui {
class ConnectionSettingDialog;
}

class ConnectionSettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionSettingDialog(QWidget *parent = nullptr);
    ~ConnectionSettingDialog();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::ConnectionSettingDialog *ui;


private:
    void readConnData();
    void saveConnData();
};

#endif // CONNECTIONSETTINGDIALOG_H
