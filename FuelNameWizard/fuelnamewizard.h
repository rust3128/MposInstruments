#ifndef FUELNAMEWIZARD_H
#define FUELNAMEWIZARD_H

#include <QWizard>

#include "FuelNameWizard/intropage.h"
#include "FuelNameWizard/terminalspage.h"
#include "FuelNameWizard/finalpage.h"

namespace Ui {
class FuelNameWizard;
}

class FuelNameWizard : public QWizard
{
    Q_OBJECT

public:
    explicit FuelNameWizard(QWidget *parent = nullptr);
    ~FuelNameWizard();

private slots:
    void slotCancelWizard();
private:
    Ui::FuelNameWizard *ui;
    IntroPage *introPage;
    TerminalsPage *termsPage;
    FinalPage *finalPage;
private:
    void createUI();
};

#endif // FUELNAMEWIZARD_H
