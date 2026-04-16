#include "mainwindow.h"

#include <QApplication>

#ifdef Q_OS_WIN
#include <windows.h>
#endif

int main(int argc, char *argv[])
{
#ifdef Q_OS_WIN
    SetProcessAffinityMask(GetCurrentProcess(), 1);
#endif

    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}
