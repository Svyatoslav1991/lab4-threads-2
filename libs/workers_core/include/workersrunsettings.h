#ifndef WORKERSRUNSETTINGS_H
#define WORKERSRUNSETTINGS_H

#include <QtGlobal>

/**
 * @brief Параметры одного запуска набора Worker-объектов.
 *
 * @details
 * Структура объединяет значения, которые используются для подготовки
 * worker-объектов к очередному запуску:
 * - начальную общую координату X;
 * - количество шагов на один Worker;
 * - длину программной задержки.
 *
 * Это позволяет не передавать связанные параметры россыпью.
 */
struct WorkersRunSettings
{
    int startX = 0;                       ///< Начальное значение общей координаты X.
    int stepsPerWorker = 1;               ///< Количество шагов на один Worker.
    qsizetype delayIterations = 0;        ///< Длина программной задержки.
};

#endif // WORKERSRUNSETTINGS_H
