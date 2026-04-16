#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "pointswidget.h"

#include <QHBoxLayout>
#include <QStatusBar>
#include <QThread>
#include <QWidget>

//--------------------------------------------------------------------------

/**
 * @brief Создаёт главное окно и подготавливает интерфейс.
 * @param parent Родительский виджет.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qRegisterMetaType<MyPoint>("MyPoint");

    initializeUi_();
}

//--------------------------------------------------------------------------

/**
 * @brief Освобождает ресурсы главного окна.
 */
MainWindow::~MainWindow()
{
    delete ui;
}

//--------------------------------------------------------------------------

/**
 * @brief Добавляет новую точку на сцену отображения.
 * @param point Точка, полученная от worker-объекта.
 */
void MainWindow::slotAddPoint(MyPoint point)
{
    if (!m_pointsWidget) {
        return;
    }

    m_pointsWidget->addPoint(point);
}

//--------------------------------------------------------------------------

/**
 * @brief Очищает текущее отображение точек.
 */
void MainWindow::slotClear()
{
    resetSharedX_();

    if (!m_pointsWidget) {
        return;
    }

    m_pointsWidget->clearPoints();
    updateStatusBarText_();
}

//--------------------------------------------------------------------------

/**
 * @brief Обрабатывает команду запуска через QThread.
 *
 * @details
 * На текущем этапе подготавливается только состояние окна:
 * - очищается предыдущая визуализация;
 * - сбрасывается общая координата X.
 *
 * Полноценный запуск QThread будет реализован следующим шагом.
 */
void MainWindow::on_actionQThread_triggered()
{
    slotClear();

    statusBar()->showMessage(
        QStringLiteral("Подготовка под запуск QThread выполнена. Реализацию потоков добавим следующим шагом."));
}

//--------------------------------------------------------------------------

/**
 * @brief Обрабатывает команду очистки.
 */
void MainWindow::on_actionClear_triggered()
{
    slotClear();
}

//--------------------------------------------------------------------------

/**
 * @brief Выполняет начальную настройку интерфейса.
 */
void MainWindow::initializeUi_()
{
    setupPointsWidget_();
    resetSharedX_();
    updateStatusBarText_();
}

//--------------------------------------------------------------------------

/**
 * @brief Создаёт и размещает виджет отображения точек в centralwidget.
 */
void MainWindow::setupPointsWidget_()
{
    auto *layout = new QHBoxLayout(ui->centralwidget);
    layout->setContentsMargins(0, 0, 0, 0);

    m_pointsWidget = new PointsWidget(ui->centralwidget);
    layout->addWidget(m_pointsWidget);
}

//--------------------------------------------------------------------------

/**
 * @brief Обновляет текст в status bar с числом рекомендованных потоков.
 */
void MainWindow::updateStatusBarText_()
{
    statusBar()->showMessage(
        QStringLiteral("QThread::idealThreadCount()=%1").arg(QThread::idealThreadCount()));
}

//--------------------------------------------------------------------------

/**
 * @brief Сбрасывает общую координату X в начальное состояние.
 */
void MainWindow::resetSharedX_() noexcept
{
    m_X = 0;
}
