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
    QList<LogEntry> getFiltered(const Filter &filter = Filter());
    QSet<QString> getModules();
    QSet<QString> getLevels();
private:
    void parse(QTextStream &logContents);
};

#endif // CONTROLLER_H
