#include "fuelnamewizard.h"
#include "ui_fuelnamewizard.h"

#include <QAbstractButton>
#include <QMessageBox>

#include "pagelist_def.h"


FuelNameWizard::FuelNameWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::FuelNameWizard)
{
    ui->setupUi(this);

    createUI();

    disconnect( button( QWizard::CancelButton ), &QAbstractButton::clicked, this, &QDialog::reject );
    connect(button(QWizard::CancelButton),&QAbstractButton::clicked, this, &FuelNameWizard::slotCancelWizard);
    connect(termsPage,&TerminalsPage::signalSendListTerm, showPage, &ShowPage::slotGetListTerminals);

}

FuelNameWizard::~FuelNameWizard()
{
    delete ui;
}

void FuelNameWizard::slotCancelWizard()
{
    if( QMessageBox::question( this, "Завершить работу мастера",
                               "Вы дейстивельно хотите завершить работу мастера?",
                               QMessageBox::Yes | QMessageBox::No ) == QMessageBox::Yes ) {
        this->reject();
    }
}

void FuelNameWizard::createUI()
{

    this->setPixmap(QWizard::LogoPixmap,QPixmap(":/Icons/fuel_big.png"));

    introPage = new IntroPage();
    termsPage = new TerminalsPage();
    showPage = new ShowPage();
    finalPage = new FinalPage();

    this->setPage(INTRO_PAGE, introPage);
    this->setPage(SELECT_AZS_PAGE,termsPage);
    this->setPage(FINAL_PAGE,finalPage);
    this->setPage(SHOW_FUELNAME_PAGE, showPage);

    this->setStartId(INTRO_PAGE);
}
