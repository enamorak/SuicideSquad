#include "taskform.h"
#include "ui_taskform.h"

TaskForm::TaskForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskForm)
{
    ui->setupUi(this);
}

TaskForm::~TaskForm()
{
    delete ui;
}


void TaskForm::generatVar(QString task_num)
{
    srand(time(NULL));
    if(task_num=="task1")
    {
        ui->VarNum->setText(QString::number(rand()%10000));
    }
    else if(task_num=="task2")
    {
        ui->VarNum->setText(QString::number(rand()%2312));
    }
    else if(task_num=="task3")
    {
        ui->VarNum->setText(QString::number(rand()%2300));
    }
    else if(task_num=="task4")
    {
        ui->VarNum->setText(QString::number(rand()%1520));
    }
}

void TaskForm::open(QString task_num,QString log)
{

    ui->NumTask->setText(task_num);
    ui->Login->setText(log);
    ui->lineEdit->setReadOnly(false);
    ui->EnterButton->setEnabled(true);
    generatVar(task_num);
    this->show();
}



void TaskForm::on_BackButton_clicked()
{
    emit back(ui->Login->text());
    ui->YourTask_2->setText("YourAnswer");
    ui->RightTask_3->setText("RightAnsewer");
    ui->label_2->setText("SAM TASK OPIC");
    ui->lineEdit->clear();
    this->close();
}


void TaskForm::on_EnterButton_clicked()
{

    if(ui->lineEdit->text().isEmpty()||ui->lineEdit->text().count(" ")==ui->lineEdit->text().size())
    {
        QMessageBox::critical(this,"Ошибка","EMPTY");
    }
    else
    {
        ui->YourTask_2->setText(ui->lineEdit->text());
        QString otvet="RIGHT";
        //здесь будет фукнция для передачи значения на обработку на сервер otvet=function(ui->Login->text(), ui->VarNum->text(), ui->lineEdit->text())
        ui->RightTask_3->setText(otvet);
        ui->lineEdit->setReadOnly(true);
        ui->EnterButton->setEnabled(false);
        ui->lineEdit->clear();
    }
}

