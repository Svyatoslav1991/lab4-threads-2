#ifndef MYPOINT_H
#define MYPOINT_H

#include <QColor>
#include <QMetaType>
#include <QPoint>

/**
 * @brief Лёгкий объект-значение для хранения данных о цветной метке.
 *
 * @details
 * Класс инкапсулирует только данные:
 * - координату метки;
 * - её цвет.
 *
 * Отрисовка намеренно не входит в ответственность MyPoint.
 * Это позволяет использовать класс в не-UI слое и выносить его
 * в библиотеку общего назначения.
 */
class MyPoint
{
public:
    /**
     * @brief Создаёт метку с заданными координатой и цветом.
     * @param pt Координата метки.
     * @param color Цвет метки.
     */
    explicit MyPoint(const QPoint &pt = QPoint(), const QColor &color = Qt::black);

    /**
     * @brief Возвращает координату метки.
     */
    const QPoint &point() const noexcept;

    /**
     * @brief Возвращает цвет метки.
     */
    const QColor &color() const noexcept;

    friend bool operator==(const MyPoint &lhs, const MyPoint &rhs) noexcept
    {
        return lhs.m_point == rhs.m_point && lhs.m_color == rhs.m_color;
    }

    friend bool operator!=(const MyPoint &lhs, const MyPoint &rhs) noexcept
    {
        return !(lhs == rhs);
    }

private:
    QPoint m_point;   ///< Координата метки.
    QColor m_color;   ///< Цвет метки.
};

Q_DECLARE_METATYPE(MyPoint)

#endif // MYPOINT_H
