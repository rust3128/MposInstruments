#include "finalpage.h"
#include "ui_finalpage.h"

FinalPage::FinalPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::FinalPage)
{
    ui->setupUi(this);

    this->setFinalPage(true);
}

FinalPage::~FinalPage()
{
    delete ui;
}
