#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>


class TaskWidget;
class QVBoxLayout;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void addTask();
    void removeTask(TaskWidget * task);
    void updateStatus();
private:
    Ui::MainWindow *ui;
    QVector<TaskWidget*> m_tasks;
    QVBoxLayout* m_tasksLayout;
};

#endif // MAINWINDOW_H
