#include <iostream>
#include <QApplication>
#include "guiwindow.h"
#include "analysis.h"

int main (int argc, char **argv)
{
    QApplication app (argc, argv);

    GuiWindow window;
    window.show();

    return app.exec();
}