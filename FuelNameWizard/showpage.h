#ifndef SHOWPAGE_H
#define SHOWPAGE_H

#include "FuelNameWizard/checkazsstatus.h"

#include <QWizardPage>
#include <QStyledItemDelegate>

#include <QSqlQueryModel>
#include <QSqlError>
#include <QtConcurrent>
#include <QTcpSocket>

namespace Ui {
class ShowPage;
}

class ShowPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit ShowPage(QWidget *parent = nullptr);
    ~ShowPage();
    bool isOnline;
private slots:
    void slotStartExecute();
    void slotStopExecute(int term);
    void slotGetAzsStatus(bool res);
    void slotFinished();
public slots:
    void slotGetListTerminals(QStringList lsTerm);
private:
    Ui::ShowPage *ui;
    QStringList m_listTerminals;
    QSqlQueryModel *modelConnections;
    CheckAzsStatus *chkAzs;

    QFutureWatcher<bool> *checkOnline;
    QStringList m_listIP;

private:
    void createUI();
    void createView();

    // QWizardPage interface
public:
    void initializePage();
};

class ProgressBarDelegate : public QStyledItemDelegate {
public:
    ProgressBarDelegate( QObject* parent = 0 );
    void paint( QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const;
};
#endif // SHOWPAGE_H
