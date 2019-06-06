#include "Logger.h"

#include <QtCore/QDir>
#include <QtCore/QCoreApplication>
#include <QtCore/QTextStream>
#include <QtCore/QFile>
#include <QtCore/QString>
#include <QtCore/QTextCodec>

#ifdef Q_OS_WIN
#include <Windows.h>
#endif

#ifdef Q_OS_UNIX
#include <unistd.h>
#endif

#ifdef _MSC_VER
#pragma warning( disable : 49960 )
#endif


inline int ___get_module_file_name(char * desStr, int size)
{
    if(desStr == 0) return 0;
#ifdef Q_OS_UNIX
    char szPid[64];
    char * szLink = new char[size];
    sprintf(szPid, "%d", getpid());
    char * l = szLink;
    l += sprintf(l, "%s", "/proc/");
    l += sprintf(l, "%s", szPid);
    l += sprintf(l, "%s", "/exe");
    size_t szt = readlink( szLink, desStr, size );
    desStr[szt] = 0;
    delete[] szLink;
    return (int)szt;
#endif
#ifdef Q_OS_WIN
    DWORD szt = ::GetModuleFileName(::GetModuleHandle(NULL), (LPTSTR)desStr, size);
    if(szt == 0) { qDebug() << qt_error_string(GetLastError()); }
    return (int)szt;
#endif
    return 0;
}

QString modulefilePath()
{
    static char module_name[16384 + 1];
    int size = sizeof(module_name);
    memset(module_name, 0, size);
    size = ___get_module_file_name(module_name, size);
    QString filePath;
#ifdef _UNICODE
    filePath = QString::fromWCharArray((const wchar_t*)module_name, size);
#elif defined UNICODE
    filePath = QString::fromWCharArray((const wchar_t*)module_name, size);
#else
    filePath = QString::fromLocal8Bit(module_name, size);
#endif
    return filePath;
}

QFile * log_file = 0;
QTextStream * out_stream = 0;
bool is_file_opened = false;
bool is_log_to_file = false;
bool is_out_in_console = false;
QString log_dir_or_file_name = QString::null;
QString log_base_name = QString::null;
QString log_dir_name = QString::null;


int    debug_level = 2;
int &  iDebugLevel = debug_level;
int    max_files_log = 16;
bool   is_lable_used = false;
qint64 max_file_size = 4 * 1024 * 1024;

char    __message[16384];
va_list arg_ptr;

#ifdef Q_OS_WIN
#define __OUT_TO_TRACE(a) OutputDebugStringA(a), OutputDebugStringA("\n")
#else
#define __OUT_TO_TRACE(a)
//fprintf(stderr, "%s\n", a), fflush(stderr)
#endif

#define PARSE_ARGUMENTS \
    va_start(arg_ptr, szFormat);\
    vsprintf(__message, szFormat, arg_ptr);\
    va_end(arg_ptr);

#define MESSAGE(a) QString(a).toUtf8().data()

#define LOG_QT_STREAM(a) \
    switch(priority)\
    {\
    case _EXCEPT:    is_lable_used = true, qCritical() << __DATETIME_LABEL__ << __EXCEPT_LABEL__ << MESSAGE(a); break;\
    case _ERROR:     is_lable_used = true, qCritical() << __DATETIME_LABEL__ << __ERROR_LABEL__ << MESSAGE(a); break;\
    case _WARNING:   is_lable_used = true, qWarning() << __DATETIME_LABEL__ << __WARNG_LABEL__  << MESSAGE(a); break;\
    case _NOTICE:    is_lable_used = true, qDebug() << __DATETIME_LABEL__ << __NOTE_LABEL__ << MESSAGE(a); break;\
    case _INFO:      is_lable_used = true, qDebug() << __DATETIME_LABEL__ << __INFO_LABEL__ << MESSAGE(a); break;\
    case _DEBUGGER:  is_lable_used = true, qDebug() << __DATETIME_LABEL__ << __DEBUG_LABEL__ << MESSAGE(a); break;\
    case _LOG_TRACE: is_lable_used = true, qDebug() << __DATETIME_LABEL__ << __TRACE_LABEL__ << MESSAGE(a); break;\
    case _NOTSET:    is_lable_used = true, qDebug() << __DATETIME_LABEL__ << __NOTSET_LABEL__ << MESSAGE(a); break;\
    default:break;\
    }

#ifdef LOG_LEVEL_BY_PRIORITET
#define CHECK_DEBUG_LEVEL(a) \
    if(debug_level < (priority >> 4)) return;
#else
#define CHECK_DEBUG_LEVEL(a) \
    if(debug_level < a) return;
#endif


void makeDirAndLogName(QString & out_dir_name, QString & out_log_name)
{
    if(log_dir_or_file_name.contains(".log"))
    {
        if(log_dir_or_file_name.contains("/"))
        {
            out_dir_name = log_dir_or_file_name;
            out_dir_name = out_dir_name.remove(out_dir_name.lastIndexOf("/"), out_dir_name.length());
            out_log_name = log_dir_or_file_name;
            out_log_name = out_log_name.remove(out_dir_name + "/");
        }
        else
        {
            out_log_name = log_dir_or_file_name;
        }

        out_log_name = out_log_name.remove(".log");
    }
    else
    {
        out_dir_name = log_dir_or_file_name;
    }

    QDir dir(out_dir_name);

    QFileInfo info(modulefilePath());

    if(out_dir_name.isEmpty()) {
        out_dir_name = info.absolutePath() + "/log";
        dir.setPath(out_dir_name);
    }

    if(!dir.exists()) {
        dir.mkdir(dir.path());
    }

    if( out_log_name.isEmpty() ) {
        out_log_name = info.completeBaseName();
    }
}

void rollOver(const QDir & dir, const QString & log_name)
{
    static QFile file;

    QStringList files = dir.entryList(QStringList() << (log_name + "*.log"), QDir::Files, QDir::Name);

    while(files.count() >= max_files_log)
    {
        file.setFileName(dir.path() + "/" + files.first());
        file.remove();
        files.removeFirst();
    }
}

void qLogFileOutput(QtMsgType type, const QMessageLogContext &/*context*/, const QString &msg)
{
    if( debug_level <= 0 ) return;
    if(!out_stream) {  initializeLogger(); if(!out_stream) { shutdownLogger(); return; }  }

    if(log_file->size() >= max_file_size) {
        shutdownLogger();
        initializeLogger();
    }

    switch (type)
    {
    case QtDebugMsg:
        if(is_lable_used) {
            *out_stream << msg; endl(*out_stream); }
        else if(debug_level > 4) {
            *out_stream << __DATETIME_LABEL__  << " " << __DEBUG_LABEL__  << " " << msg; endl(*out_stream); }
        is_lable_used = false;
        if(is_out_in_console) { __OUT_TO_TRACE(msg.toLocal8Bit()); }
        break;
    case QtWarningMsg:
        if(is_lable_used) {
            *out_stream << msg; endl(*out_stream); }
        else if(debug_level > 2) {
            *out_stream << __DATETIME_LABEL__ << " " << __WARNG_LABEL__ << " " << msg; endl(*out_stream); }
        is_lable_used = false;
        if(is_out_in_console) { __OUT_TO_TRACE(msg.toLocal8Bit()); }
        break;
    case QtCriticalMsg:
    {
        if(is_lable_used) {
            *out_stream << msg; endl(*out_stream); }
        else if(debug_level > 1) {
            *out_stream << __DATETIME_LABEL__ << " " << __ERROR_LABEL__ << " " << msg; endl(*out_stream); }
        is_lable_used = false;
        if(is_out_in_console) { __OUT_TO_TRACE(msg.toLocal8Bit()); }
        break;
    }
    case QtFatalMsg:
        is_lable_used ? *out_stream << msg : *out_stream << __DATETIME_LABEL__ << " " << __FATAL_LABEL__ << " " << msg; endl(*out_stream);
        is_lable_used = false;
        if(is_out_in_console) { __OUT_TO_TRACE(msg.toLocal8Bit()); }
        abort(); break;
    default: break;
    }
}

void Logger::logToFile()
{
    is_file_opened ? (qInstallMessageHandler(qLogFileOutput), is_log_to_file = true) : (qInstallMessageHandler(0), is_log_to_file = false);
}

void Logger::logToConsole()
{
    qInstallMessageHandler(0);
    is_log_to_file = false;
}

bool Logger::isLogToFile()
{
    return is_log_to_file;
}

int Logger::debugLevel()
{
    return debug_level;
}

QString Logger::baseName()
{
    return log_base_name;
}

QString Logger::directoryPath()
{
    return log_dir_name;
}

bool Logger::initializeLogger()
{
    if( debug_level <= 0 ) return true;
    if(!log_file)
    {
        if(log_dir_name.isEmpty() || log_base_name.isEmpty()) {
            makeDirAndLogName(log_dir_name, log_base_name);
        }

        QDir dir(log_dir_name);
        rollOver(dir, log_base_name);

        log_file = new QFile(QString("%1/%2%3.log").arg(dir.path()).arg(log_base_name)
                             .arg(QDateTime::currentDateTime().toString("___yyyy-MM-dd___hh-mm-ss-zzz")) );
        log_file->open(QIODevice::Text | QIODevice::ReadWrite);
        log_file->close();
    }

    if(!out_stream && log_file)
    {
        out_stream = new QTextStream(log_file);
        out_stream->setCodec("UTF-8");
    }

    is_file_opened = log_file->open(QIODevice::Text | QIODevice::ReadWrite);
    log_file->seek(log_file->size());

    Logger::logToFile();

    return is_file_opened;
}

bool Logger::initializeLogger(const QString & dirOrFileName, int debugLevel, bool _isOutToConsole)
{
    debug_level = debugLevel;
    log_dir_or_file_name = dirOrFileName;
    log_dir_or_file_name = log_dir_or_file_name.replace('\\', '/');
    log_base_name = QString::null;
    log_dir_name = QString::null;
    is_out_in_console = _isOutToConsole;
    return Logger::initializeLogger();
}

void Logger::shutdownLogger()
{
    if(log_file)   { log_file->close();  delete log_file; log_file = 0; }
    if(out_stream) { delete out_stream; out_stream = 0; }

    is_file_opened = false;

    Logger::logToConsole();
}

void Logger::setDebugLevel  (int level)       { debug_level   = level;    }

void Logger::setMaxFileSize (qint64 fileSize) { max_file_size = fileSize; }

void Logger::setMaxFileCount(int count)       { max_files_log = count;    }

void Logger::InitializeLogger( const std::string & dirOrFileName, int debugLevel, bool _isOutInConsole )
{
    debug_level = debugLevel;
    log_dir_or_file_name = QString::fromStdString(dirOrFileName);
    is_out_in_console = _isOutInConsole;
    log_dir_or_file_name = log_dir_or_file_name.replace('\\', '/');
    log_base_name = QString::null;
    log_dir_name = QString::null;
    Logger::initializeLogger();
}

void Logger::SetDebugLevel(int level)         { debug_level   = level;    }

int  Logger::GetDebugLevel()                  { return debug_level;       }

void Logger::Restart(const std::string & _fileName, int debugLevel, bool isOutInConsole)
{
    Logger::shutdownLogger();
    Logger::InitializeLogger(_fileName, debugLevel, isOutInConsole);
}

void Logger::restart(const QString & _fileName, int debugLevel, bool isOutInConsole)
{
    Logger::shutdownLogger();
    Logger::initializeLogger(_fileName, debugLevel, isOutInConsole);
}

void Logger::SetLogRotateParams(int max_size, int max_count, int /*max_days_to_keep*/)
{
    max_file_size = max_size * 1024;
    max_files_log = max_count;
}

void Logger::setLogRotateParams(int max_size, int max_count, int /*max_days_to_keep*/)
{
    max_file_size = max_size * 1024;
    max_files_log = max_count;
}

void Logger::ShutDownLogger() { Logger::shutdownLogger(); }

bool Logger::LogOpened()      { return is_file_opened;    }




void Logger::Log  (int priority, const std::string & __message)
{
    CHECK_DEBUG_LEVEL(0)
    LOG_QT_STREAM(__message.c_str())
}

void Logger::Log  (int priority, const char * szFormat, ... )
{
    CHECK_DEBUG_LEVEL(0)
    PARSE_ARGUMENTS
    LOG_QT_STREAM(__message)
}

void Logger::Log_ (int priority, const std::string & __message)
{
    CHECK_DEBUG_LEVEL(0)
    LOG_QT_STREAM(__message.c_str())
}

void Logger::Log_ (int priority, const char * szFormat, ... )
{
    CHECK_DEBUG_LEVEL(0)
    PARSE_ARGUMENTS
    LOG_QT_STREAM(__message)
}

void Logger::Log_1(int priority, const std::string & __message)
{
    CHECK_DEBUG_LEVEL(1)
    LOG_QT_STREAM(__message.c_str())
}

void Logger::Log_1(int priority, const char * szFormat, ... )
{
    CHECK_DEBUG_LEVEL(1)
    PARSE_ARGUMENTS
    LOG_QT_STREAM(__message)
}

void Logger::Log_2(int priority, const std::string & __message)
{
    CHECK_DEBUG_LEVEL(2)
    LOG_QT_STREAM(__message.c_str())
}

void Logger::Log_2(int priority, const char * szFormat, ... )
{
    CHECK_DEBUG_LEVEL(2)
    PARSE_ARGUMENTS
    LOG_QT_STREAM(__message)
}

void Logger::Log_3(int priority, const std::string & __message)
{
    CHECK_DEBUG_LEVEL(3)
    LOG_QT_STREAM(__message.c_str())
}

void Logger::Log_3(int priority, const char * szFormat, ... )
{
    CHECK_DEBUG_LEVEL(3)
    PARSE_ARGUMENTS
    LOG_QT_STREAM(__message)
}

void Logger::Log_4(int priority, const std::string & __message)
{
    CHECK_DEBUG_LEVEL(4)
    LOG_QT_STREAM(__message.c_str())
}

void Logger::Log_4(int priority, const char * szFormat, ... )
{
    CHECK_DEBUG_LEVEL(4)
    PARSE_ARGUMENTS
    LOG_QT_STREAM(__message)
}

void Logger::Log_5(int priority, const std::string & __message)
{
    CHECK_DEBUG_LEVEL(5)
    LOG_QT_STREAM(__message.c_str())
}

void Logger::Log_5(int priority, const char * szFormat, ... )
{
    CHECK_DEBUG_LEVEL(5)
    PARSE_ARGUMENTS
    LOG_QT_STREAM(__message)
}
