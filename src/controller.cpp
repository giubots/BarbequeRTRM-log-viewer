#include "headers/controller.h"
#include<iostream>
#include<QDebug>
Controller::Controller(QTextStream &logContents) {this->parse(logContents);}

void Controller::parse(QTextStream &logContents) {
    qDebug() << "hi";
    while (!logContents.atEnd()) {
       QString line = logContents.readLine();

       //TODO: parse line
       qDebug() << "You have obtained" << line;

    }
}
