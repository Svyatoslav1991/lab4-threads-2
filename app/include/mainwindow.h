#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @brief Главное окно приложения.
 *
 * @details
 * Пока это минимальный каркас окна для проверки,
 * что приложение собирается и запускается.
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

private:
    Ui::MainWindow *ui = nullptr; ///< Объект интерфейса, сгенерированный из .ui.
};

#endif // MAINWINDOW_H
