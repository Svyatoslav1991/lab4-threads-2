#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "mypoint.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class PointsWidget;

/**
 * @brief Главное окно приложения для демонстрации работы потоков через QThread.
 *
 * @details
 * На данном шаге окно подготавливается к отображению работы потоков:
 * - хранит общую координату X;
 * - содержит виджет визуализации точек;
 * - принимает точки от worker-объектов;
 * - очищает отображение;
 * - обрабатывает команды меню.
 *
 * Важно:
 * контейнер точек и отрисовка не дублируются в MainWindow,
 * так как уже реализованы в классе PointsWidget из библиотеки workers_widgets.
 */
class MainWindow final : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Создаёт главное окно приложения.
     * @param parent Родительский виджет.
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Уничтожает главное окно приложения.
     */
    ~MainWindow() override;

private slots:
    /**
     * @brief Добавляет новую точку на сцену отображения.
     * @param point Точка, полученная от worker-объекта.
     */
    void slotAddPoint(MyPoint point);

    /**
     * @brief Очищает текущее отображение точек.
     */
    void slotClear();

    /**
     * @brief Обрабатывает команду запуска через QThread.
     *
     * @details
     * Пока на данном шаге выполняется только подготовка состояния окна.
     * Полный запуск потоков будет добавлен следующим этапом.
     */
    void on_actionQThread_triggered();

    /**
     * @brief Обрабатывает команду очистки.
     */
    void on_actionClear_triggered();

private:
    /**
     * @brief Выполняет начальную настройку интерфейса.
     */
    void initializeUi_();

    /**
     * @brief Создаёт и размещает виджет отображения точек в centralwidget.
     */
    void setupPointsWidget_();

    /**
     * @brief Обновляет текст в status bar с числом рекомендованных потоков.
     */
    void updateStatusBarText_();

    /**
     * @brief Сбрасывает общую координату X в начальное состояние.
     */
    void resetSharedX_() noexcept;

private:
    Ui::MainWindow *ui = nullptr;              ///< Объект интерфейса, сгенерированный из .ui.
    PointsWidget *m_pointsWidget = nullptr;    ///< Виджет отображения точек.
    int m_X = 0;                               ///< Общая для всех потоков координата X.
};

#endif // MAINWINDOW_H
