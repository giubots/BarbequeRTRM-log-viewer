#include "headers/mainwindow.h"
#include <headers/parser.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    //    QCoreApplication app(argc, argv);
    //    QString fileName = "/home/giubots/Desktop/bbque.log";
    //    if (!fileName.isEmpty()) {
    //        QFile inputFile(fileName);
    //        if (inputFile.open(QIODevice::ReadOnly))
    //        {
    //            QTextStream in(&inputFile);
    //            auto c = Controller(in);
    //            inputFile.close();

    //            QSet<QString> l;
    //            l.insert("bq.plm");
    //            l.insert("bq.wm");
    //            for (LogEntry entry : c.getFiltered(Filter().onlyModules(l).contains("END"))) qDebug() << entry.dateTime << entry.level.getName() << entry.module << entry.text;
    //        } else qDebug() << "no file";
    //    }

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();


    //TODO: shortcuts, regex, exceptions, highlight/filter, deselect all, command line
}
