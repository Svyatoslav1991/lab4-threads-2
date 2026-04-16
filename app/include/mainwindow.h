#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPointer>
#include <QVector>

#include "worker.h"
#include "workersrunsettings.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class PointsWidget;
class QThread;

/**
 * @brief Главное окно приложения для демонстрации работы Worker + QThread.
 *
 * @details
 * Окно:
 * - хранит общую координату X;
 * - запускает набор рабочих объектов Worker в отдельных экземплярах QThread;
 * - получает точки от worker-объектов и передаёт их в PointsWidget;
 * - выполняет очистку сцены;
 * - аккуратно завершает активные потоки при закрытии приложения.
 *
 * Контейнер точек и отрисовка находятся в PointsWidget и здесь не дублируются.
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
     *
     * @details
     * Перед уничтожением окна ожидает завершения активных потоков.
     */
    ~MainWindow() override;

private slots:
    /**
     * @brief Добавляет новую точку на сцену.
     * @param point Точка, полученная от worker-объекта.
     */
    void slotAddPoint(MyPoint point);

    /**
     * @brief Запускает набор worker-объектов через QThread.
     */
    void slotQThread();

    /**
     * @brief Очищает текущую сцену.
     */
    void slotClear();

    /**
     * @brief Обрабатывает action запуска через QThread.
     */
    void on_actionQThread_triggered();

    /**
     * @brief Обрабатывает action очистки.
     */
    void on_actionClear_triggered();

private:
    /**
     * @brief Выполняет начальную настройку интерфейса.
     */
    void initializeUi_();

    /**
     * @brief Создаёт и размещает PointsWidget в centralwidget.
     */
    void setupPointsWidget_();

    /**
     * @brief Настраивает параметры запуска worker-объектов.
     */
    void initializeRunSettings_();

    /**
     * @brief Сбрасывает сцену перед новым запуском.
     */
    void resetForNewRun_();

    /**
     * @brief Обновляет текст status bar.
     * @param text Текст для отображения.
     */
    void showStatusText_(const QString &text);

    /**
     * @brief Возвращает количество worker-объектов для запуска.
     */
    int workerCountForRun_() const noexcept;

    /**
     * @brief Возвращает координату Y для worker-а с заданным индексом.
     * @param index Индекс worker-а.
     */
    int yForWorker_(int index) const noexcept;

    /**
     * @brief Возвращает цвет для worker-а с заданным индексом.
     * @param index Индекс worker-а.
     */
    QColor colorForWorker_(int index) const;

    /**
     * @brief Создаёт worker и поток для заданного индекса и запускает их.
     * @param index Индекс worker-а.
     */
    void createAndStartWorkerThreadPair_(int index);

    /**
     * @brief Возвращает true, если хотя бы один поток ещё работает.
     */
    bool hasRunningThreads_() const noexcept;

    /**
     * @brief Удаляет из контейнеров уже уничтоженные объекты.
     */
    void cleanupNullPointers_();

    /**
     * @brief Ожидает завершения всех ещё работающих потоков.
     */
    void waitForRunningThreads_();

private:
    Ui::MainWindow *ui = nullptr;                 ///< Объект интерфейса, сгенерированный из .ui.
    QPointer<PointsWidget> m_pointsWidget;        ///< Виджет отображения точек.
    int m_X = 0;                                  ///< Общая координата X для всех worker-объектов.
    WorkersRunSettings m_runSettings;             ///< Параметры одного запуска worker-объектов.
    QVector<QPointer<Worker>> m_workers;          ///< Контейнер рабочих объектов.
    QVector<QPointer<QThread>> m_threads;         ///< Контейнер потоков.
};

#endif // MAINWINDOW_H
