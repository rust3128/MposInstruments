#ifndef FUELNAMEWIZARD_H
#define FUELNAMEWIZARD_H

#include <QWizard>

#include "FuelNameWizard/intropage.h"

namespace Ui {
class FuelNameWizard;
}

class FuelNameWizard : public QWizard
{
    Q_OBJECT

public:
    explicit FuelNameWizard(QWidget *parent = nullptr);
    ~FuelNameWizard();

private:
    Ui::FuelNameWizard *ui;
    IntroPage *introPage;
private:
    void createUI();
};

#endif // FUELNAMEWIZARD_H
