#ifndef ____QT_LOGGER_H__INCLUDED____
#define ____QT_LOGGER_H__INCLUDED____

#include <QDebug>
#include <QDateTime>
#include <QFileInfo>
#include <stdio.h>
#include <stdarg.h>
#include <string>

#define LOG_LEVEL_BY_PRIORITET 1

#define _EXCEPT      0x10
#define _LOG_EXCEPT  _EXCEPT
#define _ERROR       0x20
#define _LOG_ERROR   _ERROR
#define _LOG_ERROR_S _ERROR
#define _CRITICAL    _ERROR
#define _WARNING     0x30
#define _LOG_WARNING _WARNING
#define _NOTICE      0x40
#define _LOG_NOTICE  _NOTICE
#define _INFO        0x41
#define _LOG_INFO    _INFO
#define _DEBUGGER    0x50
#define _LOG_DEBUG   _DEBUGGER
#define _NOTSET      0x61
#define _LOG_NOTSET  _NOTSET
#define _LOG_TRACE   0x60

#ifdef _UNICODE
#define S_FMT "%S"
#elif defined UNICODE
#define S_FMT "%S"
#else
#define S_FMT "%s"
#endif

extern int debug_level;
extern int & iDebugLevel;
extern int max_files_log;
extern qint64 max_file_size;
extern bool is_lable_used;

#define ctr1(a) QString("[%1]").arg(a).toUtf8().data()
#define ctr2(a,b) QString("[%1;%2]").arg(a).arg(b).toUtf8().data()
#define _fline_ QString("{%1;%2}").arg(QFileInfo(__FILE__).fileName()).arg(QString::number(__LINE__).rightJustified(4, ' ')).toUtf8().data()

#define __DATETIME_LABEL__ QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss.zzz").toUtf8().data()

#define __FATAL_LABEL__  " (Ftl) "
#define __EXCEPT_LABEL__ " (Exc) "
#define __ERROR_LABEL__  " (Err) "
#define __WARNG_LABEL__  " (Wrn) "
#define __NOTE_LABEL__   " (Ntc) "
#define __INFO_LABEL__   " (Inf) "
#define __DEBUG_LABEL__  " (Dbg) "
#define __TRACE_LABEL__  " (Trc) "
#define __NOTSET_LABEL__ "       "

#ifdef LOG_LEVEL_BY_PRIORITET

#define log_except      if(debug_level >= 1) is_lable_used = true, qDebug() << __DATETIME_LABEL__ << __EXCEPT_LABEL__ << _fline_
#define log_error       if(debug_level >= 2) is_lable_used = true, qCritical() << __DATETIME_LABEL__ << __ERROR_LABEL__ << _fline_
#define log_warning     if(debug_level >= 3) is_lable_used = true, qWarning() << __DATETIME_LABEL__ << __WARNG_LABEL__ << _fline_
#define log_note        if(debug_level >= 4) is_lable_used = true, qDebug() << __DATETIME_LABEL__ << __NOTE_LABEL__ << _fline_
#define log_info        if(debug_level >= 4) is_lable_used = true, qDebug() << __DATETIME_LABEL__ << __INFO_LABEL__ << _fline_
#define log_debug       if(debug_level >= 5) is_lable_used = true, qDebug() << __DATETIME_LABEL__ << __DEBUG_LABEL__ << _fline_
#define log_trace       if(debug_level >= 6) is_lable_used = true, qDebug() << __DATETIME_LABEL__ << __TRACE_LABEL__ << _fline_

#define log_1          log_except
#define log_2          log_error
#define log_3          log_warning
#define log_4          log_note
#define log_5          log_debug
#define log_6          log_trace

#define log_except_1   log_except
#define log_error_1    log_error
#define log_warning_1  log_warning
#define log_note_1     log_note
#define log_info_1     log_info
#define log_debug_1    log_debug
#define log_trace_1    log_trace

#define log_except_2   log_except
#define log_error_2    log_error
#define log_warning_2  log_warning
#define log_note_2     log_note
#define log_info_2     log_info
#define log_debug_2    log_debug
#define log_trace_2    log_trace

#define log_except_3   log_except
#define log_error_3    log_error
#define log_warning_3  log_warning
#define log_note_3     log_note
#define log_info_3     log_info
#define log_debug_3    log_debug
#define log_trace_3    log_trace

#define log_except_4   log_except
#define log_error_4    log_error
#define log_warning_4  log_warning
#define log_note_4     log_note
#define log_info_4     log_info
#define log_debug_4    log_debug
#define log_trace_4    log_trace

#define log_except_5   log_except
#define log_error_5    log_error
#define log_warning_5  log_warning
#define log_note_5     log_note
#define log_info_5     log_info
#define log_debug_5    log_debug
#define log_trace_5    log_trace

#define log_except_6   log_except
#define log_error_6    log_error
#define log_warning_6  log_warning
#define log_note_6     log_note
#define log_info_6     log_info
#define log_debug_6    log_debug
#define log_trace_6    log_trace

#else

#define log_except      is_lable_used = true, qDebug() << __DATETIME_LABEL__ << __EXCEPT_LABEL__ << _fline_
#define log_error       is_lable_used = true, qCritical() << __DATETIME_LABEL__ << __ERROR_LABEL__ << _fline_
#define log_warning     is_lable_used = true, qWarning() << __DATETIME_LABEL__ << __WARNG_LABEL__ << _fline_
#define log_note        is_lable_used = true, qDebug() << __DATETIME_LABEL__ << __NOTE_LABEL__ << _fline_
#define log_info        is_lable_used = true, qDebug() << __DATETIME_LABEL__ << __INFO_LABEL__ << _fline_
#define log_debug       is_lable_used = true, qDebug() << __DATETIME_LABEL__ << __DEBUG_LABEL__ << _fline_
#define log_trace       is_lable_used = true, qDebug() << __DATETIME_LABEL__ << __TRACE_LABEL__ << _fline_

#define log_except_1   if(debug_level >= 1)log_except
#define log_trace_1    if(debug_level >= 1)log_trace
#define log_warning_1  if(debug_level >= 1)log_warning
#define log_error_1    if(debug_level >= 1)log_error
#define log_debug_1    if(debug_level >= 1)log_debug
#define log_info_1     if(debug_level >= 1)log_info
#define log_note_1     if(debug_level >= 1)log_note

#define log_except_2   if(debug_level >= 2)log_except
#define log_trace_2    if(debug_level >= 2)log_trace
#define log_warning_2  if(debug_level >= 2)log_warning
#define log_error_2    if(debug_level >= 2)log_error
#define log_debug_2    if(debug_level >= 2)log_debug
#define log_info_2     if(debug_level >= 2)log_info
#define log_note_2     if(debug_level >= 2)log_note

#define log_except_3   if(debug_level >= 3)log_except
#define log_trace_3    if(debug_level >= 3)log_trace
#define log_warning_3  if(debug_level >= 3)log_warning
#define log_error_3    if(debug_level >= 3)log_error
#define log_debug_3    if(debug_level >= 3)log_debug
#define log_info_3     if(debug_level >= 3)log_info
#define log_note_3     if(debug_level >= 3)log_note

#define log_except_4   if(debug_level >= 4)log_except
#define log_trace_4    if(debug_level >= 4)log_trace
#define log_warning_4  if(debug_level >= 4)log_warning
#define log_error_4    if(debug_level >= 4)log_error
#define log_debug_4    if(debug_level >= 4)log_debug
#define log_info_4     if(debug_level >= 4)log_info
#define log_note_4     if(debug_level >= 4)log_note

#define log_except_5   if(debug_level >= 5)log_except
#define log_trace_5    if(debug_level >= 5)log_trace
#define log_warning_5  if(debug_level >= 5)log_warning
#define log_error_5    if(debug_level >= 5)log_error
#define log_debug_5    if(debug_level >= 5)log_debug
#define log_info_5     if(debug_level >= 5)log_info
#define log_note_5     if(debug_level >= 5)log_note

#define log_except_6   if(debug_level >= 6)log_except
#define log_trace_6    if(debug_level >= 6)log_trace
#define log_warning_6  if(debug_level >= 6)log_warning
#define log_error_6    if(debug_level >= 6)log_error
#define log_debug_6    if(debug_level >= 6)log_debug
#define log_info_6     if(debug_level >= 6)log_info
#define log_note_6     if(debug_level >= 6)log_note

#endif

namespace Logger {

bool initializeLogger();
bool initializeLogger(const QString & dirOrFileName, int debugLevel, bool isOutToConsole = false);
void setDebugLevel(int level);
void setMaxFileSize(qint64 fileSize);
void setMaxFileCount(int count);
void shutdownLogger();
void restart(const QString & fileName, int debugLevel, bool isOutInConsole = false);
void setLogRotateParams(int max_size, int max_count, int max_days_to_keep);
void logToFile();
void logToConsole();
bool isLogToFile();
int  debugLevel();
QString baseName();
QString directoryPath();

void InitializeLogger( const std::string & dirOrFileName, int debugLevel, bool isOutInConsole = false);
void ShutDownLogger();
void SetDebugLevel(int level);
int  GetDebugLevel();
void Restart(const std::string & fileName, int debugLevel, bool isOutInConsole = false);
void SetLogRotateParams(int max_size, int max_count, int max_days_to_keep);
bool LogOpened();

void Log  (int priority, const std::string & message);
void Log  (int priority, const char * szFormat, ... );
void Log_ (int priority, const std::string & message);
void Log_ (int priority, const char * szFormat, ... );
void Log_1(int priority, const std::string & message);
void Log_1(int priority, const char * szFormat, ... );
void Log_2(int priority, const std::string & message);
void Log_2(int priority, const char * szFormat, ... );
void Log_3(int priority, const std::string & message);
void Log_3(int priority, const char * szFormat, ... );
void Log_4(int priority, const std::string & message);
void Log_4(int priority, const char * szFormat, ... );
void Log_5(int priority, const std::string & message);
void Log_5(int priority, const char * szFormat, ... );

}

using namespace Logger;

#endif //____QT_LOGGER_H__INCLUDED____
