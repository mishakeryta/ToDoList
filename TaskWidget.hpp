#ifndef TASKWIGET_H
#define TASKWIGET_H

#include <QWidget>
#include <QString>

namespace Ui {
class TaskWidget;
}

class TaskWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TaskWidget(const QString& name,QWidget *parent = nullptr);
    ~TaskWidget();
    void setName(const QString& name);
    QString name() const;
    bool isChecked() const;
public slots:
    void rename();
signals:
    void removed(TaskWidget* task);
    void statusChanged(TaskWidget* task);

private slots:
    void checked(bool checked);
private:
    Ui::TaskWidget *ui;
};

#endif // TASKWIGET_H
