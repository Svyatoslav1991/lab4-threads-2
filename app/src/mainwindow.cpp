#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * @brief Создаёт главное окно и инициализирует интерфейс.
 * @param parent Родительский виджет.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

//--------------------------------------------------------------------------

/**
 * @brief Освобождает ресурсы главного окна.
 */
MainWindow::~MainWindow()
{
    delete ui;
}
