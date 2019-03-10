#include "TaskWidget.hpp"
#include "ui_TaskWidget.h"


#include <algorithm>

#include <QInputDialog>


TaskWidget::TaskWidget(const QString& name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskWidget)
{
    ui->setupUi(this);
    setName(name);

    connect(ui->editButton, &QPushButton::clicked ,this, &TaskWidget::rename);
    connect(ui->removeButton, &QPushButton::clicked ,[this](){
        emit removed(this);
    });
    connect(ui->checkBox, &QCheckBox::toggled, this, &TaskWidget::checked);
}

TaskWidget::~TaskWidget()
{
    delete ui;
}

void TaskWidget::setName(const QString &name)
{
    ui->checkBox->setText(name);
}

QString TaskWidget::name() const
{
    return ui->checkBox->text();
}

bool TaskWidget::isChecked() const
{
    return ui->checkBox->isChecked();
}

void TaskWidget::rename()
{
    bool ok = false;
    QString name = QInputDialog::getText(this,
                                         tr("Edit task"),
                                         tr("Task name"),
                                         QLineEdit::Normal,
                                         this->name(),
                                         &ok);
    if (ok && !name.isEmpty()) {
        setName(name);
    }
}

void TaskWidget::checked(bool checked)
{
   QFont newFont (ui->checkBox->font());
   newFont.setStrikeOut(checked);
   ui->checkBox->setFont(newFont);
   emit statusChanged(this);
}


