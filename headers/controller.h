#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "dataModel.h"

#include <QList>
#include <QTextStream>

class Controller
{
public:
    Controller(QTextStream &logContents);
    QList<LogEntry> getFiltered(Filter filter);
    QList<QString> getModules();
    QList<QString> getLevels();
private:
    QList<LogEntry> entries;
    QList<QString> modules;
    void parse(QTextStream &logContents);
};
#endif // CONTROLLER_H
