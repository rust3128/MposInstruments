#include "showpage.h"
#include "ui_showpage.h"
#include "LoggingCategories/loggingcategories.h"


static const QStringList TABLE_COLUMN_LABELS = QStringList() << "АЗС" << "IP" << "Статус" << "Результат";
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

void ShowPage::slotGetListTerminals(QList<int> lsTerm)
{
    m_listTerminals = lsTerm;
}

void ShowPage::createUI()
{
    this->setTitle("<html><head/><body><p><span style='font-size:18pt; font-weight:600;color:blue'>Наименования топлива на АЗС.</span></p></body></html>");
    this->setSubTitle("<html><head/><body><p><span style='font-size:10pt; font-weight:600;'>Наименования видов таоплива в базе данных АЗС с указанием резервуаров.</span></p></body></html>");


}



void ShowPage::initializePage()
{
    qInfo(logInfo()) << "List" << m_listTerminals;
    createView();

}

void ShowPage::createView()
{
    modelConnections = new QSqlQueryModel();
    QSqlDatabase db = QSqlDatabase::database();
    QString inStr;
    QListIterator<int> i(m_listTerminals);
    while (i.hasNext())
        inStr+=QString::number(i.next())+",";
    QString strSQL = QString("SELECT c.TERMINAL_ID, c.SERVER_NAME, c.DB_NAME, c.CON_PASSWORD from CONNECTIONS c "
                             "WHERE c.TERMINAL_ID IN (%1) and c.CONNECT_ID = 2 "
                             "ORDER BY c.TERMINAL_ID")
            .arg(inStr);
    qInfo(logInfo()) << "SQL" << strSQL;

    ui->tableWidget->setColumnCount(COLUMN_COUNT);
    ui->tableWidget->setHorizontalHeaderLabels(TABLE_COLUMN_LABELS);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setItemDelegateForColumn(1, new ProgressBarDelegate);


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
    progressBarOption.maximum = MAX_PROGRESS_VALUE;
    progressBarOption.progress = progress;
    progressBarOption.text = QString::number( progress ) + "%";
    progressBarOption.textVisible = true;

    QStyledItemDelegate::paint( painter, option, QModelIndex() );
    QApplication::style()->drawControl( QStyle::CE_ProgressBar, &progressBarOption, painter );
}
