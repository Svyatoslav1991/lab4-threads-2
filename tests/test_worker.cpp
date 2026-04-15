#include <QtTest/QtTest>
#include <QSignalSpy>
#include <QColor>
#include <QPoint>
#include <QVariant>

#include "worker.h"
#include "mypoint.h"

class TestWorker : public QObject
{
    Q_OBJECT

private slots:
    void constructor_storesParameters();
    void doWork_emitsPointForEachStepAndUpdatesSharedX();
    void doWork_emitsEndWorkExactlyOnce();
    void doWork_withZeroSteps_emitsNoPointsButFinishes();
    void doWork_withNullSharedX_emitsNoPointsButFinishes();
};

void TestWorker::constructor_storesParameters()
{
    int sharedX = 10;

    const Worker worker(25, &sharedX, Qt::red, 7, 0);

    QCOMPARE(worker.y(), 25);
    QCOMPARE(worker.sharedX(), &sharedX);
    QCOMPARE(worker.color(), QColor(Qt::red));
    QCOMPARE(worker.steps(), 7);
    QCOMPARE(worker.delayIterations(), qsizetype(0));
}

void TestWorker::doWork_emitsPointForEachStepAndUpdatesSharedX()
{
    qRegisterMetaType<MyPoint>("MyPoint");

    int sharedX = 3;
    Worker worker(20, &sharedX, Qt::blue, 4, 0);

    QSignalSpy pointSpy(&worker, &Worker::signalAddPoint);
    QSignalSpy endSpy(&worker, &Worker::endWork);

    worker.doWork();

    QCOMPARE(pointSpy.count(), 4);
    QCOMPARE(endSpy.count(), 1);
    QCOMPARE(sharedX, 7);

    const QList<QVariant> firstArgs = pointSpy.at(0);
    const QList<QVariant> secondArgs = pointSpy.at(1);
    const QList<QVariant> thirdArgs = pointSpy.at(2);
    const QList<QVariant> fourthArgs = pointSpy.at(3);

    QVERIFY(firstArgs.size() == 1);
    QVERIFY(secondArgs.size() == 1);
    QVERIFY(thirdArgs.size() == 1);
    QVERIFY(fourthArgs.size() == 1);

    const MyPoint firstPoint = firstArgs.at(0).value<MyPoint>();
    const MyPoint secondPoint = secondArgs.at(0).value<MyPoint>();
    const MyPoint thirdPoint = thirdArgs.at(0).value<MyPoint>();
    const MyPoint fourthPoint = fourthArgs.at(0).value<MyPoint>();

    QCOMPARE(firstPoint.point(), QPoint(3, 20));
    QCOMPARE(secondPoint.point(), QPoint(4, 20));
    QCOMPARE(thirdPoint.point(), QPoint(5, 20));
    QCOMPARE(fourthPoint.point(), QPoint(6, 20));

    QCOMPARE(firstPoint.color(), QColor(Qt::blue));
    QCOMPARE(secondPoint.color(), QColor(Qt::blue));
    QCOMPARE(thirdPoint.color(), QColor(Qt::blue));
    QCOMPARE(fourthPoint.color(), QColor(Qt::blue));
}

void TestWorker::doWork_emitsEndWorkExactlyOnce()
{
    int sharedX = 0;
    Worker worker(15, &sharedX, Qt::green, 2, 0);

    QSignalSpy endSpy(&worker, &Worker::endWork);

    worker.doWork();

    QCOMPARE(endSpy.count(), 1);
}

void TestWorker::doWork_withZeroSteps_emitsNoPointsButFinishes()
{
    qRegisterMetaType<MyPoint>("MyPoint");

    int sharedX = 11;
    Worker worker(30, &sharedX, Qt::black, 0, 0);

    QSignalSpy pointSpy(&worker, &Worker::signalAddPoint);
    QSignalSpy endSpy(&worker, &Worker::endWork);

    worker.doWork();

    QCOMPARE(pointSpy.count(), 0);
    QCOMPARE(endSpy.count(), 1);
    QCOMPARE(sharedX, 11);
}

void TestWorker::doWork_withNullSharedX_emitsNoPointsButFinishes()
{
    qRegisterMetaType<MyPoint>("MyPoint");

    Worker worker(12, nullptr, Qt::magenta, 5, 0);

    QSignalSpy pointSpy(&worker, &Worker::signalAddPoint);
    QSignalSpy endSpy(&worker, &Worker::endWork);

    worker.doWork();

    QCOMPARE(pointSpy.count(), 0);
    QCOMPARE(endSpy.count(), 1);
}

QTEST_GUILESS_MAIN(TestWorker)
#include "test_worker.moc"
