#include "showpage.h"
#include "ui_showpage.h"
#include "LoggingCategories/loggingcategories.h"
#include "azsfuellist.h"
#include <QThread>
#include <QDateTime>
#include <QProgressBar>
#include <QProgressDialog>
#include <QIcon>
#include <QSqlRecord>
#include <functional>



static const QStringList TABLE_COLUMN_LABELS = QStringList() << "АЗС" << "IP" << "Статус" << "Прогресс" <<  "Результат";
static const int COLUMN_COUNT = TABLE_COLUMN_LABELS.size();

static const int PROGRESS_STEP = 5;
static const int PROGRESS_DELAY_MSEC = 100;
static const int MAX_PROGRESS_VALUE = 100;

static const int PROGRESS_BAR_HEIGHT_PX = 20;


ShowPage::ShowPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::ShowPage)
{
    ui->setupUi(this);
    createUI();
}

ShowPage::~ShowPage()
{
    delete ui;
}



void ShowPage::slotGetListTerminals(QStringList lsTerm)
{
    m_listTerminals = lsTerm;
}

void ShowPage::createUI()
{
    this->setTitle("<html><head/><body><p><span style='font-size:18pt; font-weight:600;color:blue'>Наименования топлива на АЗС.</span></p></body></html>");
    this->setSubTitle("<html><head/><body><p><span style='font-size:10pt; font-weight:600;'>Наименования видов топлива в базе данных АЗС с указанием резервуаров.</span></p></body></html>");
}

void ShowPage::initializePage()
{

    createView();
}

void ShowPage::createView()
{
    modelConnections = new QSqlQueryModel();
    QString inStr = m_listTerminals.join(",");



    QString strSQL = QString("SELECT c.TERMINAL_ID, c.SERVER_NAME, c.DB_NAME, c.CON_PASSWORD from CONNECTIONS c "
                             "WHERE c.TERMINAL_ID IN (%1) and c.CONNECT_ID = 2 "
                             "ORDER BY c.TERMINAL_ID")
            .arg(inStr);
    modelConnections->setQuery(strSQL);


    ui->tableWidget->clearContents();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    m_listIP.clear();
    ui->tableWidget->setColumnCount(COLUMN_COUNT);
    ui->tableWidget->setHorizontalHeaderLabels(TABLE_COLUMN_LABELS);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->verticalHeader()->hide();

    for(int i = 0; i<modelConnections->rowCount();++i){
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(modelConnections->data(modelConnections->index(i,0,QModelIndex())).toString()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(modelConnections->data(modelConnections->index(i,1,QModelIndex())).toString()));
        m_listIP.append(modelConnections->data(modelConnections->index(i,1,QModelIndex())).toString());


        ui->tableWidget->setItem(i,2, new QTableWidgetItem("Выполняется...."));
//        ui->tableWidget->setCellWidget(i,3,progress);

    }
    ui->tableWidget->hideColumn(3);
    ui->tableWidget->hideColumn(4);

    ui->tableWidget->resizeColumnsToContents();

//    ui->tableWidget->verticalHeader()->setDefaultSectionSize(ui->tableWidget->verticalHeader()->minimumSectionSize());

    ui->tableWidget->setItemDelegateForColumn(3, new ProgressBarDelegate);
//////// qThread
//    for(int i = 0; i < modelConnections->rowCount(); ++i){
//        CheckAzsStatus *checkStatus = new CheckAzsStatus(i, modelConnections->data(modelConnections->index(i,1,QModelIndex())).toString());
//        QThread *thread = new QThread(this);

//        checkStatus->moveToThread(thread);

//        connect(thread,&QThread::started, this, &ShowPage::slotStartExecute,Qt::DirectConnection);
//        connect(thread,&QThread::started, checkStatus, &CheckAzsStatus::slotCheckAzsStatus,Qt::DirectConnection);

//        connect(checkStatus,&CheckAzsStatus::signalSendResult,this,&ShowPage::slotGetAzsStatus);

//        connect(checkStatus,&CheckAzsStatus::finished,this,&ShowPage::slotStopExecute);
//        connect(checkStatus,&CheckAzsStatus::finished,thread,&QThread::quit);
//        connect(checkStatus,&CheckAzsStatus::finished,checkStatus,&CheckAzsStatus::deleteLater);
//        connect(thread,&QThread::finished, thread, &QThread::deleteLater);

//        thread->start();

//    }
//////////
    checkOnline = new QFutureWatcher<bool>(this);
    connect(checkOnline,&QFutureWatcher<bool>::started, this, &ShowPage::slotStartExecute);
    connect(checkOnline,&QFutureWatcher<bool>::resultReadyAt,this,&ShowPage::slotStopExecute);
    connect(checkOnline,  &QFutureWatcher<bool>::progressRangeChanged, ui->progressBarOnline, &QProgressBar::setRange);
    connect(checkOnline, &QFutureWatcher<void>::progressValueChanged,  ui->progressBarOnline, &QProgressBar::setValue);

    connect(checkOnline,&QFutureWatcher<bool>::finished,this,&ShowPage::slotFinished);



    std::function<bool(QString)> getOnline = [] (const QString ipAZS){
        QTcpSocket tcpSocket;
        tcpSocket.connectToHost(ipAZS,3050);
        return tcpSocket.waitForConnected(30000);
    };

    checkOnline->setFuture(QtConcurrent::mapped(m_listIP,getOnline));
}



void ShowPage::slotStartExecute()
{
   qInfo(logInfo()) << Q_FUNC_INFO << QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss.zzz") <<  "Thread started";
}

void ShowPage::slotStopExecute(int row)
{
    term = row;
    if(checkOnline->resultAt(term)) {
        ui->tableWidget->item(term, 2)->setText("ON LINE");
        ui->tableWidget->item(term,2)->setTextColor("Green");
        ui->tableWidget->item(term, 2)->setIcon(QIcon(":/Icons/connect.png"));
        getFuelsList(term);
    } else {
        ui->tableWidget->item(term, 2)->setText("OFF LINE");
        ui->tableWidget->item(term, 2)->setTextColor("Red");
        ui->tableWidget->item(term, 2)->setIcon(QIcon(":/Icons/disconnect.png"));
    }
}

void ShowPage::slotGetAzsStatus(bool res)
{
    isOnline = res;
}

void ShowPage::slotFinished()
{
    qInfo(logInfo()) << "QtConcurent finished";
    ui->groupBox->hide();
    ui->tableWidget->showColumn(3);
    ui->tableWidget->showColumn(4);
}


void ShowPage::getFuelsList(int idx)
{
//    qInfo(logInfo()) << Q_FUNC_INFO  << modelConnections->record(idx);

    AzsFuelList * azsFuels = new AzsFuelList(modelConnections->record(idx));

    QThread *th = new QThread();

    azsFuels->moveToThread(th);

    connect(th,&QThread::started,azsFuels,&AzsFuelList::slotGetList);

    connect(azsFuels,&AzsFuelList::signalSendFuelsList,this,&ShowPage::slotGetFuellist,Qt::DirectConnection);
    connect(azsFuels,&AzsFuelList::signalFinish, th, &QThread::quit);
    connect(azsFuels,&AzsFuelList::signalFinish, azsFuels, &AzsFuelList::deleteLater);
    connect(th, &QThread::finished,th, &QThread::deleteLater);

    ///connect(azsFuels,&AzsFuelList::signalFinished,this,&ShowPage::slotStopExecute);
    //        connect(checkStatus,&CheckAzsStatus::finished,thread,&QThread::quit);
    //        connect(checkStatus,&CheckAzsStatus::finished,checkStatus,&CheckAzsStatus::deleteLater);
    //        connect(thread,&QThread::finished, thread, &QThread::deleteLater);

    th->start();

}


void ShowPage::slotGetFuellist(QVector<LisstFuelClass> lfVec)
{
    QWidget *tableListWidget = new QWidget();

    QTableWidget *m_fTable = new QTableWidget;



    m_fTable->setColumnCount(3);
    m_fTable->setHorizontalHeaderLabels(QStringList() << "Резервуар" << "Кратко" << "Полное");
    m_fTable->horizontalHeader()->setStretchLastSection(true);
    m_fTable->verticalHeader()->hide();
    for(int i=0; i<lfVec.size(); ++i){
        m_fTable->insertRow(i);
        m_fTable->setItem(i, 0, new QTableWidgetItem(QString::number(lfVec.at(i).tankID())));
        m_fTable->setItem(i, 1, new QTableWidgetItem(lfVec.at(i).shortName()));
        m_fTable->setItem(i, 2, new QTableWidgetItem(lfVec.at(i).fuelName()));
    }

    ui->tableWidget->setCellWidget( term, 4, m_fTable);

}


ProgressBarDelegate::ProgressBarDelegate( QObject* parent ) : QStyledItemDelegate( parent ) {
}

void ProgressBarDelegate::paint(
    QPainter* painter,
    const QStyleOptionViewItem& option,
    const QModelIndex& index
) const {
    int progress = index.data().toInt();

    QStyleOptionProgressBar progressBarOption;
    QRect r = option.rect;
    r.setHeight( PROGRESS_BAR_HEIGHT_PX );
    r.moveCenter( option.rect.center() );
    progressBarOption.rect = r;
    progressBarOption.textAlignment = Qt::AlignCenter;
    progressBarOption.minimum = 0;
    progressBarOption.maximum = 100;
    progressBarOption.progress = progress;
    progressBarOption.text = "Проверка...";
    progressBarOption.textVisible = true;

    QStyledItemDelegate::paint( painter, option, QModelIndex() );
    QApplication::style()->drawControl( QStyle::CE_ProgressBar, &progressBarOption, painter );
}
