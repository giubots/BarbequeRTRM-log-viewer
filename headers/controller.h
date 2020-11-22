#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QList>
#include <QTextStream>

#include "dataModel.h"

class Controller {
private:
    QList<LogEntry> entries;
    QSet<QString> moduleLabels;
    QSet<QString> levelLabels;
public:
    Controller(QTextStream &logContents);
    QList<LogEntry> getFiltered(Filter filter);
    QSet<QString> getModules();
    QSet<QString> getLevels();
private:
    void parse(QTextStream &logContents);
};

#endif // CONTROLLER_H
