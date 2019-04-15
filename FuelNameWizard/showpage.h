#ifndef SHOWPAGE_H
#define SHOWPAGE_H

#include <QWizardPage>
#include <QStyledItemDelegate>

#include <QSqlQueryModel>
#include <QSqlError>

namespace Ui {
class ShowPage;
}

class ShowPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit ShowPage(QWidget *parent = nullptr);
    ~ShowPage();

public slots:
    void slotGetListTerminals(QList<int> lsTerm);
private:
    Ui::ShowPage *ui;
    QList<int> m_listTerminals;
    QSqlQueryModel *modelConnections;
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
