#include "headers/parser.h"

#include <QRegularExpression>
#include <QDebug>

Parser::Parser()
    : levelLabels({BLV_ALWAYS_VISIBLE}) {}

const QVector<LogEntry> &Parser::getEntries() const {
    return entries;
}

const QVector<QString> &Parser::getLevelLables() const {
    return levelLabels;
}

const QSet<QString> &Parser::getModuleLables() const {
    return moduleLabels;
}

bool Parser::parse(QTextStream &logContents) {
    auto success = true;

    //Parse each line in the file
    while (!logContents.atEnd()) {
        auto line = logContents.readLine();

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
        QRegularExpression regExp("^(?<dateTime>\\d\\d\\d\\d.\\d\\d.\\d\\d.\\d\\d.\\d\\d.\\d\\d.\\d\\d\\d)\\s+.\\s+(?<level>\\w+)\\s+(?<module>[\\w.]+)\\s+:\\s+");//TODO: move
        auto match = regExp.match(line);

        if (!match.hasMatch()) {
            qDebug() << "Impossible to parse: " << line;
            success = false;
            continue;
        }

        auto dateTime = QDateTime::fromString(match.captured("dateTime"), Qt::ISODateWithMs);
        auto level = match.captured("level");
        auto module = match.captured("module");

        // Remove color formattation from the message if necessary: any char followed by [ then a not empty sequence of digits or ';' and an m
        auto text = line.mid(match.capturedLength(0)).remove(QRegularExpression(".\[[0-9;]+m")); //TODO: check

        entries << LogEntry{dateTime, level, module, text};
        if (!levelLabels.contains(level)) levelLabels << level;
        moduleLabels << module;
    }

    return success;
}
