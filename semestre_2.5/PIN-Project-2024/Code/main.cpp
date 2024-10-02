#include "robotsui.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    RobotsUI w;
    w.setWindowTitle("PIN-2024");
    w.show();
    return a.exec();
}
