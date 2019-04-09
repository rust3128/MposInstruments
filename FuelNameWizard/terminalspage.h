#ifndef TERMINALSPAGE_H
#define TERMINALSPAGE_H

#include "FuelNameWizard/terminals.h"
#include "FuelNameWizard/modelterminals.h"

#include <QWizardPage>

namespace Ui {
class TerminalsPage;
}

class TerminalsPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit TerminalsPage(QWidget *parent = nullptr);
    ~TerminalsPage();

private:
    Ui::TerminalsPage *ui;
    QVector<Terminals> terminalsList;
private:
    void createUI();
    QVector<Terminals> terminals;
    ModelTerminals *modelTerminals;

    // QWizardPage interface
public:
    void initializePage();
    bool isComplete() const;
};

#endif // TERMINALSPAGE_H
