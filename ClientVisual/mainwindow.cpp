#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui_auth = new regauth;
    ui_task = new TaskForm;
    connect(ui_auth, &regauth::closed, this, &MainWindow::slot_on_auth_closed);
    connect(this,&MainWindow::go,ui_task,&TaskForm::open);
    connect(ui_task,&TaskForm::back, this, &MainWindow::slot_on_auth_closed);
    ui_auth->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
int MainWindow::check_point(QString task)
{
    //тут функция запроса к бд но пока заглушка c task
    srand(time(NULL));
    int otvet = rand()%1000;
    if (task=="task1")
    {
        otvet = 1;
    }

    return otvet;
}

void MainWindow::slot_on_auth_closed(QString log)
{

    ui->Label_login->setText(log);
    ui->Label_point1->setText(QString::number(check_point(ui->Label_point1->text()))); //здесь вообще чтото сложное если вкратце мы считываем название lable он назван taskN,
    //N - это числа от 1 до 4 и кидаем запрос к БД на проврерку сколько баллов по этому task пользователь имеет и возвращаем число конвертируя его в QString
    ui->Label_point2->setText(QString::number(check_point(ui->Label_point2->text())));
    ui->Label_point3->setText(QString::number(check_point(ui->Label_point3->text())));
    ui->Label_point4->setText(QString::number(check_point(ui->Label_point4->text())));
    this->show();
}


void MainWindow::on_Exit_button_clicked()
{

    this->close();
}


void MainWindow::go_task(QString task_num)
{

    emit go(task_num,ui->Label_login->text());
    this->close();
}

void MainWindow::on_Task1_Button_clicked()
{
    go_task("task1");
}


void MainWindow::on_Task2_Button_clicked()
{
    go_task("task2");
}


void MainWindow::on_Task3_Button_clicked()
{
    go_task("task3");
}


void MainWindow::on_Task4_Button_clicked()
{
    go_task("task4");
}

