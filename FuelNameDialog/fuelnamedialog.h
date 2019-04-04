#ifndef FUELNAMEDIALOG_H
#define FUELNAMEDIALOG_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QSqlError>

namespace Ui {
class FuelNameDialog;
}

class FuelNameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FuelNameDialog(QWidget *parent = nullptr);
    ~FuelNameDialog();

private slots:
    void on_pushButtonAdd_clicked();
    void on_toolButtonSelectAll_clicked();

    void on_toolButtonSelectAllTargets_clicked();

    void on_pushButtonRemove_clicked();

private:
    Ui::FuelNameDialog *ui;
    QSqlQueryModel *modelTerminals;

private:
    void createUI();
    void setupModels();
};

#endif // FUELNAMEDIALOG_H
