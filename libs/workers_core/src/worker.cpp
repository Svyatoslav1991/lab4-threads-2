#include "worker.h"

#include <QPoint>

#include <algorithm>

namespace
{
int normalizeSteps(int steps) noexcept
{
    return std::max(0, steps);
}

qsizetype normalizeDelayIterations(qsizetype delayIterations) noexcept
{
    return std::max<qsizetype>(0, delayIterations);
}

constexpr int kSharedXStep = 1;
constexpr int kBusyDelayIncrement = 1;
}

//--------------------------------------------------------------------------

Worker::Worker(int y,
               int *sharedX,
               const QColor &color,
               int steps,
               qsizetype delayIterations,
               QObject *parent)
    : QObject(parent)
    , m_pX(sharedX)
    , m_Y(y)
    , m_color(color)
{
    setSteps(steps);
    setDelayIterations(delayIterations);
}

//--------------------------------------------------------------------------

int Worker::y() const noexcept
{
    return m_Y;
}

//--------------------------------------------------------------------------

int *Worker::sharedX() const noexcept
{
    return m_pX;
}

//--------------------------------------------------------------------------

const QColor &Worker::color() const noexcept
{
    return m_color;
}

//--------------------------------------------------------------------------

int Worker::steps() const noexcept
{
    return m_steps;
}

//--------------------------------------------------------------------------

qsizetype Worker::delayIterations() const noexcept
{
    return m_delayIterations;
}

//--------------------------------------------------------------------------

void Worker::setSteps(int steps) noexcept
{
    m_steps = normalizeSteps(steps);
}

//--------------------------------------------------------------------------

void Worker::setDelayIterations(qsizetype delayIterations) noexcept
{
    m_delayIterations = normalizeDelayIterations(delayIterations);
}

//--------------------------------------------------------------------------

void Worker::doWork()
{
    if (!hasSharedX()) {
        emit endWork();
        return;
    }

    if (m_steps <= 0) {
        emit endWork();
        return;
    }

    for (int step = 0; step < m_steps; ++step) {
        performStep();
    }

    emit endWork();
}

//--------------------------------------------------------------------------

bool Worker::hasSharedX() const noexcept
{
    return m_pX != nullptr;
}

//--------------------------------------------------------------------------

void Worker::performStep()
{
    emit signalAddPoint(makeCurrentPoint());
    incrementSharedX();
    busyDelay();
}

//--------------------------------------------------------------------------

MyPoint Worker::makeCurrentPoint() const
{
    return MyPoint(QPoint(*m_pX, m_Y), m_color);
}

//--------------------------------------------------------------------------

void Worker::incrementSharedX() noexcept
{
    *m_pX += kSharedXStep;
}

//--------------------------------------------------------------------------

void Worker::busyDelay() const noexcept
{
    volatile int sink = 0;

    for (qsizetype i = 0; i < m_delayIterations; ++i) {
        sink += kBusyDelayIncrement;
    }

    (void)sink;
}
