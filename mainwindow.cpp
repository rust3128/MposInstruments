#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "LoggingCategories/loggingcategories.h"
#include "FuelNameWizard/fuelnamewizard.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    qInfo(logInfo()) << tr("Заверешение работы.");
}


void MainWindow::on_actionFuelName_triggered()
{
    FuelNameWizard *fnDlg = new FuelNameWizard();
    this->setCentralWidget(fnDlg);
    fnDlg->exec();

}
