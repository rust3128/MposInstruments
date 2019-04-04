#include "fuelnamedialog.h"
#include "ui_fuelnamedialog.h"
#include "LoggingCategories/loggingcategories.h"

#include <QCheckBox>
#include <QTableWidgetItem>

FuelNameDialog::FuelNameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FuelNameDialog)
{
    ui->setupUi(this);
    setupModels();
    createUI();
}

FuelNameDialog::~FuelNameDialog()
{
    delete ui;
}



void FuelNameDialog::setupModels()
{
    modelTerminals = new QSqlQueryModel();
    QSqlDatabase db = QSqlDatabase::database("central");

    modelTerminals->setQuery("SELECT DISTINCT t.TERMINAL_ID, t.NAME, t.OWNER_ID FROM TERMINALS t "
                             "INNER JOIN shifts s ON s.TERMINAL_ID=t.TERMINAL_ID "
                             "WHERE t.TERMINALTYPE = 3 "
                             "ORDER BY t.TERMINAL_ID",db);
    if (modelTerminals->lastError().isValid()) {
        qCritical(logCritical()) <<Q_FUNC_INFO << "Ошибка создания модели." <<  modelTerminals->lastError().text();
    }

}

void FuelNameDialog::createUI()
{
    ui->tableWidgetSource->setColumnCount(modelTerminals->columnCount()+1);
    ui->tableWidgetSource->setHorizontalHeaderLabels(QStringList()<<""<<"АЗС"<<"Адрес");
    for(int i=0;i<modelTerminals->rowCount();++i){
        ui->tableWidgetSource->insertRow(i);
        QWidget *checkBoxWidget = new QWidget();
        QCheckBox *checkBox = new QCheckBox();
        QHBoxLayout *layoutCheckBox = new QHBoxLayout(checkBoxWidget);
        layoutCheckBox->addWidget(checkBox);
        layoutCheckBox->setAlignment(Qt::AlignCenter);
        layoutCheckBox->setContentsMargins(0,0,0,0);
        checkBox->setChecked(false);

        ui->tableWidgetSource->setCellWidget(i,0,checkBoxWidget);

        ui->tableWidgetSource->setItem(i,1,new QTableWidgetItem(modelTerminals->data(modelTerminals->index(i,0,QModelIndex())).toString() ));
        ui->tableWidgetSource->setItem(i,2,new QTableWidgetItem(modelTerminals->data(modelTerminals->index(i,1,QModelIndex())).toString() ));
        ui->tableWidgetSource->setItem(i,3,new QTableWidgetItem(modelTerminals->data(modelTerminals->index(i,2,QModelIndex())).toString() ));

    }
    ui->tableWidgetSource->hideColumn(3);
    ui->tableWidgetSource->resizeColumnsToContents();
}

void FuelNameDialog::on_pushButtonAdd_clicked()
{
    bool dublicate;

    ui->tableWidgetTarget->setColumnCount(modelTerminals->columnCount());
    ui->tableWidgetTarget->setHorizontalHeaderLabels(QStringList()<<""<<"АЗС"<<"Адрес");

    for(int i = 0; i < ui->tableWidgetSource->rowCount();++i){
        dublicate = false;
        QWidget *item = ui->tableWidgetSource->cellWidget(i,0);
        QCheckBox *checkBox = qobject_cast<QCheckBox*>(item->layout()->itemAt(0)->widget());
        if(checkBox->isChecked()){
            int rowCount = ui->tableWidgetTarget->rowCount();

            for(int j=0;j<rowCount;++j){
                if(ui->tableWidgetTarget->item(j,1)->text() == ui->tableWidgetSource->item(i,1)->text()){
                    dublicate = true;
                    continue;
                }
            }
            if(dublicate)
                continue;

            ui->tableWidgetTarget->insertRow(rowCount);

            QWidget *checkBoxWidget = new QWidget();
            QCheckBox *checkBox = new QCheckBox();
            QHBoxLayout *layoutCheckBox = new QHBoxLayout(checkBoxWidget);
            layoutCheckBox->addWidget(checkBox);
            layoutCheckBox->setAlignment(Qt::AlignCenter);
            layoutCheckBox->setContentsMargins(0,0,0,0);
            checkBox->setChecked(false);

            ui->tableWidgetTarget->setCellWidget(rowCount,0,checkBoxWidget);
            ui->tableWidgetTarget->setItem(rowCount,1,new QTableWidgetItem(ui->tableWidgetSource->item(i,1)->text()));
            ui->tableWidgetTarget->setItem(rowCount,2,new QTableWidgetItem(ui->tableWidgetSource->item(i,2)->text()));

            ui->tableWidgetSource->cellWidget(i,0)->setDisabled(true);
            ui->tableWidgetSource->item(i,1)->setBackgroundColor("#62E285");
            ui->tableWidgetSource->item(i,2)->setBackgroundColor("#62E285");

        }
    }
    ui->tableWidgetTarget->resizeColumnsToContents();
    ui->tableWidgetTarget->sortItems(1,Qt::AscendingOrder);
}


void FuelNameDialog::on_toolButtonSelectAll_clicked()
{
    for(int i=0;i<ui->tableWidgetSource->rowCount();++i){
        QWidget *item = ui->tableWidgetSource->cellWidget(i,0);
        QCheckBox *checkBox = qobject_cast<QCheckBox*>(item->layout()->itemAt(0)->widget());
        checkBox->setChecked(true);
    }
}

void FuelNameDialog::on_toolButtonSelectAllTargets_clicked()
{
    for(int i=0;i<ui->tableWidgetTarget->rowCount();++i){
        QWidget *item = ui->tableWidgetTarget->cellWidget(i,0);
        QCheckBox *checkBox = qobject_cast<QCheckBox*>(item->layout()->itemAt(0)->widget());
        checkBox->setChecked(true);
    }
}

void FuelNameDialog::on_pushButtonRemove_clicked()
{
    QList<QString> rowDeleted;
    for(int i = 0; i < ui->tableWidgetTarget->rowCount(); ++i){
        QWidget *item = ui->tableWidgetTarget->cellWidget(i,0);
        QCheckBox *checkBox = qobject_cast<QCheckBox*>(item->layout()->itemAt(0)->widget());
        if(checkBox->isChecked()){
            for(int j = 0; j<ui->tableWidgetSource->rowCount();++j){
                if(ui->tableWidgetTarget->item(i,1)->text() == ui->tableWidgetSource->item(j,1)->text()){

                    ui->tableWidgetSource->cellWidget(j,0)->setDisabled(false);
                    ui->tableWidgetSource->item(j,1)->setBackgroundColor("#FFFFFF");
                    ui->tableWidgetSource->item(j,2)->setBackgroundColor("#FFFFFF");

                    QWidget *item = ui->tableWidgetSource->cellWidget(j,0);
                    QCheckBox *checkBoxSource = qobject_cast<QCheckBox*>(item->layout()->itemAt(0)->widget());
                    checkBoxSource->setChecked(false);
                    rowDeleted.append(ui->tableWidgetTarget->item(i,1)->text());
                    break;
                }
            }

        }
    }
    for(int i=0;i<rowDeleted.size();++i){
        for(int j=0;j<ui->tableWidgetTarget->rowCount();++j){
            if(rowDeleted.at(i)==ui->tableWidgetTarget->item(j,1)->text()) {
                ui->tableWidgetTarget->removeRow(j);
            }
        }
    }
}
