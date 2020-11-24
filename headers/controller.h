#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "dataModel.h"

#include <QTextStream>

class Controller {
private:
    QList<LogEntry> entries;
    QSet<QString> moduleLabels;
    QSet<QString> levelLabels;
public:
    Controller(QTextStream &logContents);
    virtual QList<LogEntry> getFiltered(const Filter &filter = Filter());
    virtual QSet<QString> getModules();
    virtual QSet<QString> getLevels();
    QStringList getLevelLables();
    QStringList getModuleLables();
protected:
    Controller();
private:
    void parse(QTextStream &logContents);
};

class EmptyController : public Controller {
public:
    EmptyController();
    QList<LogEntry> getFiltered(const Filter &filter) override;
    QSet<QString> getModules() override;
    QSet<QString> getLevels() override;
};

#endif // CONTROLLER_H
