#include "inc/JJDisplayOutput.h"
//#include "JJTestOutput.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    JJDisplayOutput w;

    return a.exec();
}

