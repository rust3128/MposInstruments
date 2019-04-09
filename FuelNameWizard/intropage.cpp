#include "intropage.h"
#include "ui_intropage.h"
#include <QGroupBox>

IntroPage::IntroPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::IntroPage)
{
    ui->setupUi(this);
    createUI();

    this->registerField("checkView", ui->radioButtonView);
    this->registerField("checkChange", ui->radioButtonChange);
}

IntroPage::~IntroPage()
{
    delete ui;
}

void IntroPage::createUI()
{
    this->setTitle("<html><head/><body><p><span style='font-size:18pt; font-weight:600;color:blue'>Шаг 1. Выбор действий.</span></p></body></html>");
    this->setSubTitle("<html><head/><body><p><span style='font-size:10pt; font-weight:600;'>Выберите действия которые необходимо произвести с наименованиями видов топлива на АЗС.</span></p></body></html>");
    this->setPixmap(QWizard::WatermarkPixmap, QPixmap(":/Icons/fuellogo.png"));

    ui->radioButtonView->setStyleSheet(
                "QRadioButton::indicator::checked { image: url(:/Icons/checked.png);}"
                "QRadioButton::indicator::unchecked { image: url(:/Icons/unchecked.png);}"
                );
    ui->radioButtonChange->setStyleSheet(
                "QRadioButton::indicator::checked { image: url(:/Icons/checked.png);}"
                "QRadioButton::indicator::unchecked { image: url(:/Icons/unchecked.png);}"
                );

}

void IntroPage::initializePage()
{
    ui->radioButtonView->setChecked(false);
    ui->radioButtonChange->setChecked(false);
}


bool IntroPage::isComplete() const
{
    if(ui->radioButtonView->isChecked())
        return true;
    if(ui->radioButtonChange->isChecked())
        return  true;

    return false;
}

void IntroPage::on_radioButtonView_clicked()
{
    emit this->completeChanged();
}

void IntroPage::on_radioButtonChange_clicked()
{
    emit this->completeChanged();
}
