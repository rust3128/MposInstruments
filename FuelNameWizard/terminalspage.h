#ifndef TERMINALSPAGE_H
#define TERMINALSPAGE_H



#include <QWizardPage>
#include <QSqlQueryModel>

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
    QSqlQueryModel *modelTerminals;
    QSqlQueryModel *modelRegions;
private:
    void createUI();
    void setupModels();
    void showSelectedTerm();


    // QWizardPage interface
public:
    void initializePage();
    bool isComplete() const;
    int regionID;
private slots:

    void on_pushButtonAdd_clicked();
    void on_toolButtonSelectAll_clicked();
    void on_toolButtonSelectAllTargets_clicked();
    void on_pushButtonRemove_clicked();
    void on_comboBoxRegions_activated(int index);
    void on_toolButtonRegions_clicked();
    void on_toolButtonUnSelectAllSource_clicked();
    void on_toolButtonUnSelectAllTargets_clicked();
};

#endif // TERMINALSPAGE_H
