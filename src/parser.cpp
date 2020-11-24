#include "headers/parser.h"

#include <QRegularExpression>
#include <QDebug>

Parser::Parser(QTextStream &logContents)
    : moduleLabels({BLV_ALWAYS_VISIBLE}) {
    parse(logContents);
}

QVector<LogEntry> &Parser::getEntries() {
    return entries;
}

QSet<QString> &Parser::getLevelLables() {
    return levelLabels;
}

QSet<QString> &Parser::getModuleLables() {
    return moduleLabels;
}

void Parser::parse(QTextStream &logContents) {
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
            continue;
        }

        auto dateTime = QDateTime::fromString(match.captured("dateTime"), Qt::ISODateWithMs);
        auto level = match.captured("level");
        auto module = match.captured("module");

        // Remove color formattation from the message if necessary: any char followed by [ then a not empty sequence of digits or ';' and an m
        auto text = line.mid(match.capturedLength(0)).remove(QRegularExpression(".\[[0-9;]+m"));

        entries << LogEntry{dateTime, level, module, text};
        moduleLabels << module;
        levelLabels << level;
    }
}
