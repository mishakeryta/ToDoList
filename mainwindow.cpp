#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include <algorithm>

#include <QPushButton>
#include <QInputDialog>
#include <QString>
#include <QVector>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QSpacerItem>

#include "TaskWidget.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_tasks()
{
    ui->setupUi(this);

    QWidget* scrollAreaContent = new QWidget();
    m_tasksLayout =  new QVBoxLayout();
    m_tasksLayout->setDirection(QBoxLayout::BottomToTop);
    QSpacerItem* spacer = new QSpacerItem(1, 1, QSizePolicy::Fixed, QSizePolicy::Expanding);
    m_tasksLayout->addSpacerItem(spacer);


    scrollAreaContent->setLayout( m_tasksLayout);

    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy (Qt::ScrollBarAsNeeded);
    scrollArea->setWidgetResizable (true);
    scrollArea->setWidget(scrollAreaContent);

    ui->tasksLayout->addWidget(scrollArea);


    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::addTask);
    updateStatus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addTask()
{
    bool ok = false;
    QString name = QInputDialog::getText(this,
                                         tr("Add task"),
                                         tr("Task name"),
                                         QLineEdit::Normal,
                                         tr("Untitled task"),
                                         &ok);
    if(ok && !name.isEmpty()) {
        TaskWidget* task = new TaskWidget(name);
        m_tasks.append(task);
        m_tasksLayout->addWidget(task);

        connect(task, &TaskWidget::removed, this, &MainWindow::removeTask);
        connect(task, &TaskWidget::statusChanged, this, &MainWindow::updateStatus);
        updateStatus();
    }
}

void MainWindow::removeTask(TaskWidget *task)
{
    m_tasks.removeOne(task);
    m_tasksLayout->removeWidget(task);
    task->setParent(nullptr);
    delete task;
    updateStatus();
}

void MainWindow::updateStatus()
{
    auto doneCount = std::count_if(std::begin(m_tasks), std::end(m_tasks), [](TaskWidget* task){
        return task->isChecked();
    });
    ui->statusLabel->setText(tr("Statis: %0 done / %1 all").arg(doneCount).arg(m_tasks.size()));
}

