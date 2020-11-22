#include "headers/controller.h"

#include <QDebug>
#include <QRegularExpression>

Controller::Controller(QTextStream &logContents) : entries(), moduleLabels(), levelLabels() {parse(logContents);}

QList<LogEntry> Controller::getFiltered(const Filter &filter) {
    QList<LogEntry> answer;
    for (LogEntry entry : entries) {
        if ((filter.startDateTime.isValid() && entry.dateTime < filter.startDateTime)
                || (filter.endDateTime.isValid() && entry.dateTime > filter.endDateTime)
                || (!filter.levels.isEmpty() && !filter.levels.contains(entry.level))
                || (!filter.modules.isEmpty() && !filter.modules.contains(entry.module))
                || (!filter.text.isEmpty() && !entry.text.contains(filter.text)))
            continue;
        answer.append(entry);
    }
    return answer;
}

QSet<QString> Controller::getModules() {return moduleLabels;}

QSet<QString> Controller::getLevels() {return levelLabels;}

void Controller::parse(QTextStream &logContents) {
    qDebug() << "Starting to parse";

    //Parse each line in the file
    while (!logContents.atEnd()) {
        QString line = logContents.readLine();

        // Log entry format: yyyy-MM-dd HH:mm:ss,fff - LEVEL module  : Text
        // dateTime: a sequence DDDDxDDxDDxDDxDDxDDxDDD where D is any digit, x is any char
        // follows a sequence of space or tab
        // follows any char
        // follows a sequence of space or tab
        // level: a sequence of letters or numbers
        // follows a sequence of space or tab
        // module: a sequence of letters, numbers, dots
        // follows a sequence of space or tab
        // follows any char
        // follows a sequence of space or tab
        // the remaining text is the message (to be filtered)
        QRegularExpression regExp("^(?<dateTime>\\d\\d\\d\\d.\\d\\d.\\d\\d.\\d\\d.\\d\\d.\\d\\d.\\d\\d\\d)\\s+.\\s+(?<level>\\w+)\\s+(?<module>[\\w.]+)\\s+:\\s+");
        QRegularExpressionMatch match = regExp.match(line);

        if (!match.hasMatch()) {
            qDebug() << "Impossible to parse: " << line;
            continue;
        }

        QDateTime dateTime = QDateTime::fromString(match.captured("dateTime"), Qt::ISODateWithMs);
        LogLevel level = LogLevel::fromString(match.captured("level"));
        QString module = match.captured("module");

        // Remove color formattation from the message if necessary: any char followed by [ then a not empty sequence of digits and an m
        QString message = line.mid(match.capturedLength(0)).replace(QRegularExpression(".\[[0-9]+m"), "");

        entries << LogEntry({dateTime, level, module, message});
        moduleLabels << module;
        levelLabels << level.getName();
    }
}
