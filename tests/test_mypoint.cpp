#include <QtTest/QtTest>

#include <QColor>
#include <QPoint>

#include "mypoint.h"

class TestMyPoint : public QObject
{
    Q_OBJECT

private slots:
    void defaultConstructor_initializesOriginAndBlackColor();
    void constructor_storesPointAndColor();
    void equalityOperator_comparesPointAndColor();
};

//--------------------------------------------------------------------------

void TestMyPoint::defaultConstructor_initializesOriginAndBlackColor()
{
    const MyPoint point;

    QCOMPARE(point.point(), QPoint(0, 0));
    QCOMPARE(point.color(), QColor(Qt::black));
}

//--------------------------------------------------------------------------

void TestMyPoint::constructor_storesPointAndColor()
{
    const MyPoint point(QPoint(10, 20), Qt::red);

    QCOMPARE(point.point(), QPoint(10, 20));
    QCOMPARE(point.color(), QColor(Qt::red));
}

//--------------------------------------------------------------------------

void TestMyPoint::equalityOperator_comparesPointAndColor()
{
    const MyPoint first(QPoint(3, 7), Qt::blue);
    const MyPoint second(QPoint(3, 7), Qt::blue);
    const MyPoint third(QPoint(4, 7), Qt::blue);
    const MyPoint fourth(QPoint(3, 7), Qt::green);

    QVERIFY(first == second);
    QVERIFY(first != third);
    QVERIFY(first != fourth);
}

QTEST_MAIN(TestMyPoint)
#include "test_mypoint.moc"
