#ifndef WORKER_H
#define WORKER_H

#include <QColor>
#include <QObject>

#include "mypoint.h"

/**
 * @brief Рабочий объект, формирующий точки для отображения.
 *
 * @details
 * В соответствии с лабораторной работой объект:
 * - использует общую координату X;
 * - имеет собственные Y и цвет;
 * - формирует заданное количество точек;
 * - отправляет каждую сформированную точку в GUI-поток через сигнал;
 * - по завершении работы генерирует сигнал endWork().
 *
 * Класс не владеет общей координатой X: указатель на неё передаётся извне.
 */
class Worker final : public QObject
{
    Q_OBJECT

public:
    /// Значение задержки по умолчанию, близкое к примеру из методички.
    static constexpr qsizetype kDefaultDelayIterations = 1'000'000;

    /**
     * @brief Создаёт рабочий объект.
     * @param y Фиксированная координата Y для этого worker'а.
     * @param sharedX Указатель на общую координату X.
     * @param color Цвет точек данного worker'а.
     * @param steps Количество итераций формирования точек.
     * @param delayIterations Количество итераций программной задержки.
     * @param parent Родительский QObject.
     */
    explicit Worker(int y,
                    int *sharedX,
                    const QColor &color,
                    int steps,
                    qsizetype delayIterations = kDefaultDelayIterations,
                    QObject *parent = nullptr);

    /**
     * @brief Возвращает фиксированную координату Y.
     */
    int y() const noexcept;

    /**
     * @brief Возвращает адрес общей координаты X.
     */
    int *sharedX() const noexcept;

    /**
     * @brief Возвращает цвет worker'а.
     */
    const QColor &color() const noexcept;

    /**
     * @brief Возвращает число шагов.
     */
    int steps() const noexcept;

    /**
     * @brief Возвращает число итераций программной задержки.
     */
    qsizetype delayIterations() const noexcept;

    /**
     * @brief Устанавливает количество шагов.
     * @param steps Новое количество шагов.
     */
    void setSteps(int steps) noexcept;

    /**
     * @brief Устанавливает число итераций программной задержки.
     * @param delayIterations Новое значение задержки.
     */
    void setDelayIterations(qsizetype delayIterations) noexcept;

public slots:
    /**
     * @brief Выполняет полезную работу worker'а.
     *
     * @details
     * На каждом шаге:
     * - формируется текущая точка;
     * - генерируется сигнал signalAddPoint(MyPoint);
     * - инкрементируется общая координата X;
     * - выполняется программная задержка.
     *
     * После завершения цикла генерируется сигнал endWork().
     */
    void doWork();

signals:
    /**
     * @brief Сигнал о формировании новой точки.
     * @param point Новая точка для отображения.
     */
    void signalAddPoint(MyPoint point);

    /**
     * @brief Сигнал о завершении работы worker'а.
     */
    void endWork();

private:
    /**
     * @brief Проверяет, доступна ли общая координата X.
     */
    bool hasSharedX() const noexcept;

    /**
     * @brief Выполняет один шаг работы.
     */
    void performStep();

    /**
     * @brief Создаёт очередную точку на основе текущего состояния.
     */
    MyPoint makeCurrentPoint() const;

    /**
     * @brief Инкрементирует общую координату X.
     */
    void incrementSharedX() noexcept;

    /**
     * @brief Выполняет программную задержку.
     *
     * @note Нужна именно для визуализации конкуренции потоков в лабораторной.
     */
    void busyDelay() const noexcept;

private:
    int *m_pX = nullptr;                ///< Указатель на общий X.
    int m_Y = 0;                        ///< Фиксированная координата Y.
    QColor m_color = Qt::black;         ///< Цвет worker-а.
    int m_steps = 0;                    ///< Количество шагов.
    qsizetype m_delayIterations = 0;    ///< Длина программной задержки.
};

#endif // WORKER_H
