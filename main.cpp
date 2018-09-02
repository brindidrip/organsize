#include <iostream>
#include <QApplication>
#include "gui.h"
#include "analysis.h"

int main (int argc, char **argv)
{
    QApplication app (argc, argv);

    Gui window;
    window.show();

    return app.exec();
}