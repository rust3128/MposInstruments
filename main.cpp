#include "mainwindow.h"
#include "LoggingCategories/loggingcategories.h"
#include "DataBases/databases.h"
#include <QApplication>
#include <QFile>
#include <QDateTime>
#include <QTranslator>
#include <QLibraryInfo>

// Умный указатель на файл логирования
static QScopedPointer<QFile>   m_logFile;

// Объявляение обработчика
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Устанавливаем файл логирования,
    // внимательно сверьтесь с тем, какой используете путь для файла
    m_logFile.reset(new QFile("MposInstruments.log"));
    // Открываем файл логирования
    m_logFile.data()->open(QFile::Append | QFile::Text);
    // Устанавливаем обработчик
    qInstallMessageHandler(messageHandler);

#ifndef QT_NO_TRANSLATION
    QString translatorFileName = QLatin1String("qt_");
    translatorFileName += QLocale::system().name();
    QTranslator *translator = new QTranslator(&a);
    if (translator->load(translatorFileName, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
        a.installTranslator(translator);
    else
        qWarning(logWarning()) << "Не удалось загрузить языковый файл.";
#endif

    DataBases *db = new DataBases();
    if(!db->connectCentralDatabase()){
        qCritical(logCritical()) << "Ошибка открытия баз данных.";
        qInfo(logInfo()) << "Аварийное завершение работы.";
        return 1;
    }

    qInfo(logInfo()) << QObject::tr("Запуск программы.");
    MainWindow w;
    w.show();

    return a.exec();
}

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // Открываем поток записи в файл
    QTextStream out(m_logFile.data());
    QTextStream console(stdout);


    // Записываем дату записи
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");
    // По типу определяем, к какому уровню относится сообщение
    switch (type)
    {
#ifdef QT_DEBUG
    case QtInfoMsg:     out << "[INF] "; console << "Info:     " << msg << endl; break;
    case QtDebugMsg:    out << "[DBG] "; console << "Debug:    " << msg << endl; break;
    case QtWarningMsg:  out << "[WRN] "; console << "Warning:  " << msg << endl; break;
    case QtCriticalMsg: out << "[CRT] "; console << "Critical: " << msg << endl; break;
    case QtFatalMsg:    out << "[FTL] "; console << "Fatality: " << msg << endl; break;
#else
    case QtInfoMsg:     out << "[INF] "; break;
    case QtDebugMsg:    out << "[DBG] "; break;
    case QtWarningMsg:  out << "[WRN] "; break;
    case QtCriticalMsg: out << "[CRT] "; break;
    case QtFatalMsg:    out << "[FTL] "; break;
#endif

    }
    // Записываем в вывод категорию сообщения и само сообщение
    out << context.category << ": "
        << msg << endl;
    out.flush();
    // Очищаем буферизированные данные
    console.flush();
}
