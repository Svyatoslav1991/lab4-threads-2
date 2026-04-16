#define private public
#include "mainwindow.h"
#undef private

#include "pointswidget.h"

#include <QAction>
#include <QStatusBar>
#include <QThread>
#include <QtTest/QtTest>

/**
 * @brief Юнит-тесты для класса MainWindow.
 *
 * @details
 * Тесты покрывают:
 * - корректную инициализацию окна и базовых UI-элементов;
 * - добавление точки через slotAddPoint();
 * - очистку сцены через slotClear();
 * - запуск worker-объектов через QThread;
 * - повторный запуск после завершения предыдущего.
 *
 * Для доступа к приватным полям и методам используется тестовый seam
 * через временное раскрытие private в public.
 */
class TestMainWindow : public QObject
{
    Q_OBJECT

private slots:
    /**
     * @brief Проверяет корректную инициализацию главного окна.
     */
    void constructor_initializesUiState();

    /**
     * @brief Проверяет, что slotAddPoint() добавляет точку в PointsWidget.
     */
    void slotAddPoint_addsPointToPointsWidget();

    /**
     * @brief Проверяет, что slotClear() очищает точки и сбрасывает m_X.
     */
    void slotClear_clearsPointsAndResetsSharedX();

    /**
     * @brief Проверяет, что slotQThread() запускает worker-объекты и приводит к появлению точек.
     */
    void slotQThread_startsWorkersAndCollectsPoints();

    /**
     * @brief Проверяет возможность повторного запуска после завершения потоков.
     */
    void slotQThread_allowsRepeatedLaunchAfterCompletion();
};

//--------------------------------------------------------------------------

/**
 * @brief Проверяет корректную инициализацию главного окна.
 */
void TestMainWindow::constructor_initializesUiState()
{
    MainWindow window;
    window.show();
    QVERIFY(QTest::qWaitForWindowExposed(&window));

    QVERIFY(window.ui != nullptr);
    QVERIFY(window.m_pointsWidget != nullptr);

    const QAction *qThreadAction = window.findChild<QAction*>("actionQThread");
    const QAction *clearAction = window.findChild<QAction*>("actionClear");

    QVERIFY(qThreadAction != nullptr);
    QVERIFY(clearAction != nullptr);

    QCOMPARE(qThreadAction->text(), QStringLiteral("QThread"));
    QCOMPARE(clearAction->text(), QStringLiteral("Clear"));

    QCOMPARE(window.m_X, 0);
    QCOMPARE(window.m_pointsWidget->pointCount(), 0);

    QCOMPARE(window.statusBar()->currentMessage(),
             QStringLiteral("QThread::idealThreadCount()=%1").arg(QThread::idealThreadCount()));
}

//--------------------------------------------------------------------------

/**
 * @brief Проверяет, что slotAddPoint() добавляет точку в PointsWidget.
 */
void TestMainWindow::slotAddPoint_addsPointToPointsWidget()
{
    MainWindow window;

    const MyPoint point(QPoint(15, 30), Qt::red);

    window.slotAddPoint(point);

    QCOMPARE(window.m_pointsWidget->pointCount(), 1);
    QCOMPARE(window.m_pointsWidget->points().at(0), point);
}

//--------------------------------------------------------------------------

/**
 * @brief Проверяет, что slotClear() очищает точки и сбрасывает m_X.
 */
void TestMainWindow::slotClear_clearsPointsAndResetsSharedX()
{
    MainWindow window;

    window.m_X = 123;
    window.slotAddPoint(MyPoint(QPoint(10, 20), Qt::green));
    window.slotAddPoint(MyPoint(QPoint(11, 21), Qt::blue));

    QCOMPARE(window.m_pointsWidget->pointCount(), 2);

    window.slotClear();

    QCOMPARE(window.m_X, window.m_runSettings.startX);
    QCOMPARE(window.m_pointsWidget->pointCount(), 0);
    QCOMPARE(window.statusBar()->currentMessage(), QStringLiteral("Сцена очищена."));
}

//--------------------------------------------------------------------------

/**
 * @brief Проверяет, что slotQThread() запускает worker-объекты и приводит к появлению точек.
 */
void TestMainWindow::slotQThread_startsWorkersAndCollectsPoints()
{
    MainWindow window;

    window.m_runSettings.startX = 0;
    window.m_runSettings.stepsPerWorker = 3;
    window.m_runSettings.delayIterations = 1000;

    const int workerCount = window.workerCountForRun_();
    const int expectedPointCount = workerCount * window.m_runSettings.stepsPerWorker;

    window.slotQThread();

    QTRY_VERIFY(window.m_pointsWidget->pointCount() > 0);
    QTRY_COMPARE(window.m_pointsWidget->pointCount(), expectedPointCount);
    QTRY_VERIFY(!window.hasRunningThreads_());
    QTRY_COMPARE(window.statusBar()->currentMessage(), QStringLiteral("Все потоки завершили работу."));
}

//--------------------------------------------------------------------------

/**
 * @brief Проверяет возможность повторного запуска после завершения потоков.
 */
void TestMainWindow::slotQThread_allowsRepeatedLaunchAfterCompletion()
{
    MainWindow window;

    window.m_runSettings.startX = 0;
    window.m_runSettings.stepsPerWorker = 2;
    window.m_runSettings.delayIterations = 1000;

    const int workerCount = window.workerCountForRun_();
    const int expectedPointCount = workerCount * window.m_runSettings.stepsPerWorker;

    window.slotQThread();

    QTRY_COMPARE(window.m_pointsWidget->pointCount(), expectedPointCount);
    QTRY_VERIFY(!window.hasRunningThreads_());

    window.slotQThread();

    QTRY_COMPARE(window.m_pointsWidget->pointCount(), expectedPointCount);
    QTRY_VERIFY(!window.hasRunningThreads_());
    QTRY_COMPARE(window.statusBar()->currentMessage(), QStringLiteral("Все потоки завершили работу."));
}

//--------------------------------------------------------------------------

QTEST_MAIN(TestMainWindow)
#include "test_mainwindow.moc"
