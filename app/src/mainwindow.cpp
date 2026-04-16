#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "pointswidget.h"

#include <QColor>
#include <QHBoxLayout>
#include <QStatusBar>
#include <QThread>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qRegisterMetaType<MyPoint>("MyPoint");

    initializeUi_();
    initializeRunSettings_();
}

//--------------------------------------------------------------------------

MainWindow::~MainWindow()
{
    waitForRunningThreads_();
    delete ui;
}

//--------------------------------------------------------------------------

void MainWindow::slotAddPoint(MyPoint point)
{
    if (!m_pointsWidget) {
        return;
    }

    m_pointsWidget->addPoint(point);
}

//--------------------------------------------------------------------------

void MainWindow::slotQThread()
{
    cleanupNullPointers_();

    if (hasRunningThreads_()) {
        showStatusText_(QStringLiteral("Потоки ещё работают. Дождись завершения текущего запуска."));
        return;
    }

    resetForNewRun_();

    const int workerCount = workerCountForRun_();
    m_workers.reserve(workerCount);
    m_threads.reserve(workerCount);

    for (int index = 0; index < workerCount; ++index) {
        createAndStartWorkerThreadPair_(index);
    }

    showStatusText_(QStringLiteral("Запущено потоков: %1").arg(workerCount));
}

//--------------------------------------------------------------------------

void MainWindow::slotClear()
{
    cleanupNullPointers_();

    if (hasRunningThreads_()) {
        showStatusText_(QStringLiteral("Очистка недоступна во время работы потоков."));
        return;
    }

    resetForNewRun_();
    showStatusText_(QStringLiteral("Сцена очищена."));
}

//--------------------------------------------------------------------------

void MainWindow::on_actionQThread_triggered()
{
    slotQThread();
}

//--------------------------------------------------------------------------

void MainWindow::on_actionClear_triggered()
{
    slotClear();
}

//--------------------------------------------------------------------------

void MainWindow::initializeUi_()
{
    setupPointsWidget_();

    showStatusText_(
        QStringLiteral("QThread::idealThreadCount()=%1").arg(QThread::idealThreadCount()));
}

//--------------------------------------------------------------------------

void MainWindow::setupPointsWidget_()
{
    auto *layout = new QHBoxLayout(ui->centralwidget);
    layout->setContentsMargins(0, 0, 0, 0);

    m_pointsWidget = new PointsWidget(ui->centralwidget);
    layout->addWidget(m_pointsWidget);
}

//--------------------------------------------------------------------------

void MainWindow::initializeRunSettings_()
{
    m_runSettings.startX = 0;
    m_runSettings.stepsPerWorker = 120;
    m_runSettings.delayIterations = Worker::kDefaultDelayIterations / 5;
}

//--------------------------------------------------------------------------

void MainWindow::resetForNewRun_()
{
    m_X = m_runSettings.startX;

    if (m_pointsWidget) {
        m_pointsWidget->clearPoints();
    }

    m_workers.clear();
    m_threads.clear();
}

//--------------------------------------------------------------------------

void MainWindow::showStatusText_(const QString &text)
{
    statusBar()->showMessage(text);
}

//--------------------------------------------------------------------------

int MainWindow::workerCountForRun_() const noexcept
{
    return qMax(1, QThread::idealThreadCount() + 1);
}

//--------------------------------------------------------------------------

int MainWindow::yForWorker_(int index) const noexcept
{
    constexpr int startY = 20;
    constexpr int deltaY = 25;

    return startY + index * deltaY;
}

//--------------------------------------------------------------------------

QColor MainWindow::colorForWorker_(int index) const
{
    constexpr int hueStep = 45;
    constexpr int saturation = 220;
    constexpr int value = 200;

    return QColor::fromHsv((index * hueStep) % 360, saturation, value);
}

//--------------------------------------------------------------------------

void MainWindow::createAndStartWorkerThreadPair_(int index)
{
    auto *worker = new Worker(yForWorker_(index),
                              &m_X,
                              colorForWorker_(index),
                              m_runSettings.stepsPerWorker,
                              m_runSettings.delayIterations);

    auto *thread = new QThread;

    worker->moveToThread(thread);

    connect(worker,
            &Worker::signalAddPoint,
            this,
            &MainWindow::slotAddPoint,
            Qt::QueuedConnection);

    connect(thread,
            &QThread::started,
            worker,
            &Worker::doWork);

    connect(worker,
            &Worker::endWork,
            thread,
            &QThread::quit);

    connect(thread,
            &QThread::finished,
            worker,
            &QObject::deleteLater);

    connect(thread,
            &QThread::finished,
            thread,
            &QObject::deleteLater);

    connect(thread,
            &QThread::finished,
            this,
            [this]()
            {
                cleanupNullPointers_();

                if (!hasRunningThreads_()) {
                    showStatusText_(QStringLiteral("Все потоки завершили работу."));
                }
            });

    m_workers.push_back(worker);
    m_threads.push_back(thread);

    thread->start();
}

//--------------------------------------------------------------------------

bool MainWindow::hasRunningThreads_() const noexcept
{
    for (const QPointer<QThread> &thread : m_threads) {
        if (thread && thread->isRunning()) {
            return true;
        }
    }

    return false;
}

//--------------------------------------------------------------------------

void MainWindow::cleanupNullPointers_()
{
    for (int index = m_workers.size() - 1; index >= 0; --index) {
        if (m_workers.at(index).isNull()) {
            m_workers.removeAt(index);
        }
    }

    for (int index = m_threads.size() - 1; index >= 0; --index) {
        if (m_threads.at(index).isNull()) {
            m_threads.removeAt(index);
        }
    }
}

//--------------------------------------------------------------------------

void MainWindow::waitForRunningThreads_()
{
    cleanupNullPointers_();

    for (const QPointer<QThread> &thread : m_threads) {
        if (!thread) {
            continue;
        }

        if (thread->isRunning()) {
            thread->quit();
            thread->wait();
        }
    }
}
