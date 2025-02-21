//В Qt поддерживаются различные уровни логирования для удобного отслеживания и отладки выполнения программ. Вот основные уровни логирования и примеры их использования:
// URL - https://doc.qt.io/qt-6/qtlogging.html
//Уровни логирования
//QtDebugMsg: Используется для отладочных сообщений, которые полезны при разработке и отладке программного обеспечения.
//QtInfoMsg: Используется для информационных сообщений, которые предоставляют информацию о ходе выполнения программы.
//QtWarningMsg: Используется для предупреждений о потенциальных проблемах, которые не являются критическими.
//QtCriticalMsg: Используется для сообщений о критических ошибках, которые требуют немедленного внимания.
//QtFatalMsg: Используется для сообщений о фатальных ошибках, которые приводят к аварийному завершению программы.

#include <QCoreApplication>
#include <QDebug>
#include <QFile>
//#include <QtLogging>  // This is a problem specific to official Debian 12 dpkg packages. <QtLogging> is a very recent addition introduced somewhere between Qt 6.4.2 and Qt 6.5, and Debian 12 ships Qt 6.4.2.
#include <QDateTime>

QtMessageHandler originalHandler = nullptr;

void logToFile(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString message = qFormatLogMessage(type, context, msg);
    static FILE *f = fopen("logFile.txt", "a");
    fprintf(f, "%s\n", qPrintable(message));
    fflush(f);

    if (originalHandler)
        (*originalHandler)(type, context, msg);
}

// Пользовательский обработчик сообщений
// файл логов сохраняется в той же директории, где находится исполняемый файл программы.
// например, build-01-logging-Desktop_Qt_5_15_2_MinGW_64_bit-Debug
// Таким образом, путь к файлу логов будет относительным путем к исполняемому файлу.
// Если, например, исполняемый файл находится в папке C:\MyApp\logs, то файл логов будет сохранен по пути C:\MyApp\logs\log.txt.
// Если нужно изменить путь, вы можете указать полный путь к файлу при открытии QFile.

void customMessageHandlerToFile(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    static QFile logFile("log.txt");
    if (!logFile.isOpen()) {
        logFile.open(QIODevice::WriteOnly | QIODevice::Append);
    }

    QTextStream stream(&logFile);
    QByteArray localMsg = msg.toLocal8Bit();
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";

    QString message;
    switch (type) {
    case QtDebugMsg:
        message = QString("Debug: %1 (%2:%3, %4)").arg(localMsg.constData()).arg(file).arg(context.line).arg(function);
        break;
    case QtInfoMsg:
        message = QString("Info: %1 (%2:%3, %4)").arg(localMsg.constData()).arg(file).arg(context.line).arg(function);
        break;
    case QtWarningMsg:
        message = QString("Warning: %1 (%2:%3, %4)").arg(localMsg.constData()).arg(file).arg(context.line).arg(function);
        break;
    case QtCriticalMsg:
        message = QString("Critical: %1 (%2:%3, %4)").arg(localMsg.constData()).arg(file).arg(context.line).arg(function);
        break;
    case QtFatalMsg:
        message = QString("Fatal: %1 (%2:%3, %4)").arg(localMsg.constData()).arg(file).arg(context.line).arg(function);
        abort();
    }

    // Выводим сообщение в файл
    stream << message << '\n';
    logFile.flush();

    // Выводим сообщение в консоль
    fprintf(stderr, "%s\n", message.toLocal8Bit().constData());
}

void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    QByteArray localMsg = msg.toLocal8Bit();
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtInfoMsg:
        fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        abort();
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//=== 1) выводим сообщения просто в консоль

    qDebug() << "Debug msg (QtDebugMsg)";
    qInfo() << "Info msg (QtInfoMsg)";
    qWarning() << "Warning msg (QtWarningMsg)";
    qCritical()<<"Critical msg (QtCriticalMsg)\n";

//=== 2) выводим сообщения в файл
//    // Обработчик сообщений. Установим собственный обработчик сообщений для управления логированием в Qt - customMessageHandler
//    originalHandler = qInstallMessageHandler(logToFile);

//    qDebug() << "Debug msg (QtDebugMsg)";
//    qInfo() << "Info msg (QtInfoMsg)";
//    qWarning() << "Warning msg (QtWarningMsg)";
//    qCritical()<<"Critical msg (QtCriticalMsg)";

//    // эта строка завершит программу. У и нее иной синтаксис!
//    // qFatal( "Fatal msg (QtFatalMsg)");

//   // эта строка завершит программу. У и нее иной синтаксис!
//   // qFatal( "Fatal msg (QtFatalMsg)");

// //=== 3) выводим сообщения в консоль, но уже с указанием типа сообщения
//    originalHandler = qInstallMessageHandler(customMessageHandler);

//    qDebug() << "Debug msg (QtDebugMsg)";
//    qInfo() << "Info msg (QtInfoMsg)";
//    qWarning() << "Warning msg (QtWarningMsg)";
//    qCritical()<<"Critical msg (QtCriticalMsg)";

//    // эта строка завершит программу. У и нее иной синтаксис!
//    // qFatal( "Fatal msg (QtFatalMsg)");

// //=== 4) выводим сообщения в файл и на консоль с указанием типа сообщения
//    originalHandler = qInstallMessageHandler(customMessageHandlerToFile);
//       qDebug() << "Debug msg (QtDebugMsg)";
//       qInfo() << "Info msg (QtInfoMsg)";
//       qWarning() << "Warning msg (QtWarningMsg)";
//       qCritical()<<"Critical msg (QtCriticalMsg)";

//        эта строка завершит программу. У и нее иной синтаксис!
//        qFatal( "Fatal msg (QtFatalMsg)");


    return a.exec();
}
