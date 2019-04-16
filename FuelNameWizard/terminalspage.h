#ifndef TERMINALSPAGE_H
#define TERMINALSPAGE_H



#include <QWizardPage>
#include <QSqlQueryModel>
#include <QList>

namespace Ui {
class TerminalsPage;
}

class TerminalsPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit TerminalsPage(QWidget *parent = nullptr);
    ~TerminalsPage();

signals:
    void signalSendListTerm(QStringList lsTerm);
private:
    Ui::TerminalsPage *ui;
    QSqlQueryModel *modelTerminals;
    QSqlQueryModel *modelRegions;
    int regionID;
    QStringList listTerminals;
private:
    void createUI();
    void setupModels();
    void showSelectedTerm();
    void updateTerminalList();



    // QWizardPage interface
public:
    void initializePage();

private slots:

    void on_pushButtonAdd_clicked();
    void on_toolButtonSelectAll_clicked();
    void on_toolButtonSelectAllTargets_clicked();
    void on_pushButtonRemove_clicked();
    void on_comboBoxRegions_activated(int index);
    void on_toolButtonRegions_clicked();
    void on_toolButtonUnSelectAllSource_clicked();
    void on_toolButtonUnSelectAllTargets_clicked();

    // QWizardPage interface
public:
    int nextId() const;

   // QWizardPage interface
public:
    bool isComplete() const;
};

#endif // TERMINALSPAGE_H
