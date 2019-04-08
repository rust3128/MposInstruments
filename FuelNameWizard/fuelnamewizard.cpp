#include "fuelnamewizard.h"
#include "ui_fuelnamewizard.h"

#include "pagelist_def.h"


FuelNameWizard::FuelNameWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::FuelNameWizard)
{
    ui->setupUi(this);

    createUI();

}

FuelNameWizard::~FuelNameWizard()
{
    delete ui;
}

void FuelNameWizard::createUI()
{
    this->setPixmap(QWizard::WatermarkPixmap, QPixmap(":/Icons/fuellogo.png"));
    this->setPixmap(QWizard::LogoPixmap,QPixmap(":/Icons/fuel_big.png"));




    introPage = new IntroPage();

    this->setPage(INTRO_PAGE, introPage);

    this->setStartId(INTRO_PAGE);
}
