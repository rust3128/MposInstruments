#include "intropage.h"
#include "ui_intropage.h"
#include <QGroupBox>

IntroPage::IntroPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::IntroPage)
{
    ui->setupUi(this);
    createUI();
}

IntroPage::~IntroPage()
{
    delete ui;
}

void IntroPage::createUI()
{
    this->setSubTitle("Этот мастер позволить просмотреть наименования активных видов топлива в кассом аппатее ИКС на АЗС, а также "
                      "изменять эти наименования.");

    ui->radioButtonView->setStyleSheet(
                "QRadioButton::indicator::checked { image: url(:/Icons/checked.png);}"
                "QRadioButton::indicator::unchecked { image: url(:/Icons/unchecked.png);}"
                );
    ui->radioButtonChange->setStyleSheet(
                "QRadioButton::indicator::checked { image: url(:/Icons/checked.png);}"
                "QRadioButton::indicator::unchecked { image: url(:/Icons/unchecked.png);}"
                );

}
