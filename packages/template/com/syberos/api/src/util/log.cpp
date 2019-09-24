#include "log.h"
#include <QDebug>
#include <QDateTime>
#include <QtGlobal>
#include <qlogging.h>
#include <QMutexLocker>
#include <stdio.h>

#define DATETIME_FMT "yyyy-MM-dd HH:mm:ss"

Log* Log::logger = NULL;

static QMap<Log::Level, QString> levelNameMap;
// qDebug 打印的日志级别，默认为info
static Log::Level qDebugLevel;
// 当前日志级别
static Log::Level currentLevel;

static QMutex mutex;

void output(QtMsgType type, const QMessageLogContext &context, const QString &msg){
    Q_UNUSED(type);

    if(qDebugLevel < currentLevel){
        return;
    }
    QString levelName = Log::levelName(qDebugLevel);
    QString datetime = QDateTime::currentDateTime().toString(DATETIME_FMT);
    fprintf(stderr, "%4s | %s - [%5d] %s | %s\n",
            levelName.toLocal8Bit().constData(),
            datetime.toLocal8Bit().constData(),
            context.line,
            context.function,
            msg.toUtf8().constData());
    // 修改qDebug打印的日志级别为默认的info级别
    qDebugLevel = Log::INFO;
}

Log::Log(QObject *parent) : QObject(parent){
    qInstallMessageHandler(output);

    levelNameMap.insert(Log::VERBOSE, "VERB");
    levelNameMap.insert(Log::INFO, "INFO");
    levelNameMap.insert(Log::WARNING, "WARN");
    levelNameMap.insert(Log::ERROR, "ERR");

    currentLevel = Log::INFO;
    qDebugLevel = Log::INFO;
}

Log::~Log(){
    levelNameMap.clear();
    delete logger;
}

Log* Log::instance(){
    if(logger==NULL){
        logger = new Log();
    }
    return logger;
}

QString Log::levelName(Level level){
    return levelNameMap.value(level);
}

void Log::setLevel(Log::Level level){
    mutex.lock();
    currentLevel = level;
    mutex.unlock();
}

void Log::setLevel(const QString &level){
    QString lev = level.toLower();
    if(lev==LOG_VERBOSE){
        setLevel(Log::VERBOSE);
    }else if(lev==LOG_INFO){
        setLevel(Log::INFO);
    }else if(lev==LOG_WARN || lev==LOG_WARNING){
        setLevel(Log::WARNING);
    }else if(lev==LOG_ERROR){
        setLevel(Log::ERROR);
    }
}

bool Log::isVerboseEnabled(){
    return currentLevel >= Log::VERBOSE;
}

bool Log::isInfoEnabled(){
    return currentLevel >= Log::INFO;
}

bool Log::isWarningEnabled(){
    return currentLevel >= Log::WARNING;
}

bool Log::isErrorEnabled(){
    return currentLevel >= Log::ERROR;
}

QDebug Log::verbose(){
    setQDebugLevel(Log::VERBOSE);
    return qDebug();
}

QDebug Log::info(){
    setQDebugLevel(Log::INFO);
    return qDebug();
}

QDebug Log::warn(){
    setQDebugLevel(Log::WARNING);
    return qDebug();
}

QDebug Log::error(){
    setQDebugLevel(Log::ERROR);
    return qDebug();
}



QDebug Log::black(){
    return qDebug() << "\033[30m";
}

QDebug Log::red(){
    return qDebug() << "\033[31m";
}

QDebug Log::green(){
    return qDebug() << "\033[32m";
}

QDebug Log::yellow(){
    return qDebug() << "\033[33m";
}

QDebug Log::blue(){
    return qDebug() << "\033[34m";
}

QDebug Log::violet(){
    return qDebug() << "\033[35m";
}

QDebug Log::skyBlue(){
    return qDebug() << "\033[36m";
}

QDebug Log::white(){
    return qDebug() << "\033[37m";
}

const char* Log::end(){
    return "\033[0m";
}



void Log::setQDebugLevel(Log::Level qDebugLev){
    mutex.lock();
    qDebugLevel = qDebugLev;
    mutex.unlock();
}


