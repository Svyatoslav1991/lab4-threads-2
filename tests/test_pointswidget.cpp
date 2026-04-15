#include <QtTest/QtTest>

#include <QBrush>
#include <QColor>
#include <QImage>
#include <QPalette>

#include "mypoint.h"
#include "pointswidget.h"

class TestPointsWidget : public QObject
{
    Q_OBJECT

private slots:
    void constructor_initialState_isEmpty();
    void addPoint_storesPointAndIncreasesCount();
    void clearPoints_removesAllPoints();
    void clearPoints_whenAlreadyEmpty_remainsEmpty();
    void render_afterAddingPoint_drawsVerticalLineWithExpectedColor();
};

//--------------------------------------------------------------------------

void TestPointsWidget::constructor_initialState_isEmpty()
{
    PointsWidget widget;

    QCOMPARE(widget.pointCount(), 0);
    QVERIFY(widget.points().isEmpty());
}

//--------------------------------------------------------------------------

void TestPointsWidget::addPoint_storesPointAndIncreasesCount()
{
    PointsWidget widget;

    const MyPoint first(QPoint(3, 10), Qt::red);
    const MyPoint second(QPoint(7, 20), Qt::blue);

    widget.addPoint(first);
    widget.addPoint(second);

    QCOMPARE(widget.pointCount(), 2);
    QCOMPARE(widget.points().size(), 2);
    QCOMPARE(widget.points().at(0), first);
    QCOMPARE(widget.points().at(1), second);
}

//--------------------------------------------------------------------------

void TestPointsWidget::clearPoints_removesAllPoints()
{
    PointsWidget widget;

    widget.addPoint(MyPoint(QPoint(1, 5), Qt::red));
    widget.addPoint(MyPoint(QPoint(2, 6), Qt::green));
    QCOMPARE(widget.pointCount(), 2);

    widget.clearPoints();

    QCOMPARE(widget.pointCount(), 0);
    QVERIFY(widget.points().isEmpty());
}

//--------------------------------------------------------------------------

void TestPointsWidget::clearPoints_whenAlreadyEmpty_remainsEmpty()
{
    PointsWidget widget;

    widget.clearPoints();

    QCOMPARE(widget.pointCount(), 0);
    QVERIFY(widget.points().isEmpty());
}

//--------------------------------------------------------------------------

void TestPointsWidget::render_afterAddingPoint_drawsVerticalLineWithExpectedColor()
{
    PointsWidget widget;
    widget.resize(40, 40);

    QPalette palette = widget.palette();
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    widget.setPalette(palette);

    widget.addPoint(MyPoint(QPoint(5, 7), Qt::red));

    QImage image(widget.size(), QImage::Format_ARGB32);
    image.fill(Qt::black);

    widget.render(&image);

    for (int y = 7; y <= 27; ++y) {
        QCOMPARE(image.pixelColor(5, y), QColor(Qt::red));
    }

    QCOMPARE(image.pixelColor(0, 0), QColor(Qt::white));
    QCOMPARE(image.pixelColor(20, 20), QColor(Qt::white));
}

QTEST_MAIN(TestPointsWidget)
#include "test_pointswidget.moc"
