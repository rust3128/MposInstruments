#include "terminalspage.h"
#include "ui_terminalspage.h"
#include "passconv.h"
#include "LoggingCategories/loggingcategories.h"
#include <QSqlQuery>
#include <QSqlError>

TerminalsPage::TerminalsPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::TerminalsPage)
{
    ui->setupUi(this);

    createUI();
}

TerminalsPage::~TerminalsPage()
{
    delete ui;
}

void TerminalsPage::createUI()
{
    this->setTitle("<html><head/><body><p><span style='font-size:18pt; font-weight:600;color:blue'>Шаг 2. Выбор АЗС.</span></p></body></html>");
    this->setSubTitle("<html><head/><body><p><span style='font-size:10pt; font-weight:600;'>Выберите АЗС (терминалы) для дальнейших действий.</span></p></body></html>");
}


void TerminalsPage::initializePage()
{
    Terminals tr;

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery q = QSqlQuery(db);

    QString strSQL = "SELECT DISTINCT t.terminal_id, TRIM(t.name), c.SERVER_NAME, c.DB_NAME, c.CON_PASSWORD FROM TERMINALS t "
            "LEFT JOIN CONNECTIONS c ON t.TERMINAL_ID = c.TERMINAL_ID "
            "LEFT JOIN SHIFTS s ON s.TERMINAL_ID = t.TERMINAL_ID "
            "WHERE t.TERMINALTYPE=3 and s.SHIFT_ID>0 "
            "ORDER BY t.TERMINAL_ID";
    if(!q.exec(strSQL)) {
        qInfo(logInfo()) << Q_FUNC_INFO << "Ошибка получения списка терминалов." << q.lastError().text();
        return;
    }

    while (q.next()){
        tr.setIsCheked(0);
        tr.setTerminal(q.value(0).toInt());
        tr.setName(q.value(1).toString());
        tr.setServerName(q.value(2).toString());
        tr.setDatabase(q.value(3).toString());
        tr.setPassword(passConv(q.value(4).toString()));
        terminals.append(tr);
    }
    modelTerminals = new ModelTerminals(terminals);
    ui->tableViewTerminals->setModel(modelTerminals);
    ui->tableViewTerminals->verticalHeader()->hide();
    ui->tableViewTerminals->alternatingRowColors();
    ui->tableViewTerminals->resizeColumnsToContents();
    ui->tableViewTerminals->verticalHeader()->setDefaultSectionSize(ui->tableViewTerminals->verticalHeader()->minimumSectionSize());

}

bool TerminalsPage::isComplete() const
{
    return false;
}
