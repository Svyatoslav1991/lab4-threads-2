#include "mainwindow.h"

#include <QApplication>

/**
 * @brief Точка входа в приложение.
 * @param argc Количество аргументов командной строки.
 * @param argv Массив аргументов командной строки.
 * @return Код завершения приложения.
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}
