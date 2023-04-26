#include "regauth.h"
#include "ui_regauth.h"

regauth::regauth(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::regauth)
{
    ui->setupUi(this);
    this->swap_mode(true);

}

void regauth::swap_mode(bool m)
{
    ui->label_3->setVisible(!m);
    ui->lineEdit_mail->setVisible(!m);
    ui->Reg_Button->setVisible(!m);

    ui->Auth_Button->setVisible(m);
    if(m)
    {
        ui->Swap_Button->setText("To sing up");
    }
    else
    {
        ui->Swap_Button->setText("Cansel");
    }
}

regauth::~regauth()
{
    delete ui;
}

void regauth::on_Swap_Button_clicked()
{
    this->swap_mode(ui->label_3->isVisible());
    ui->lineEdit_log->clear();
    ui->lineEdit_pass->clear();
    ui->lineEdit_mail->clear();
}


void regauth::on_Reg_Button_clicked()
{
    if(ui->lineEdit_log->text().isEmpty() || ui->lineEdit_pass->text().isEmpty() || ui->lineEdit_mail->text().isEmpty())
    {
       QMessageBox::critical(this,"Ошибка","Не заполнены или логин, или пароль, или мейл");
    }
    else if(false)// здесь будет проврека можно ли за регестрировать
    {
        //здесь будет функция на чек есть что есть и потом же будет выведено чтото
        if(true)
        {
             QMessageBox::critical(this,"Ошибка","Логин уже занят");
        }
        else
        {
            QMessageBox::critical(this,"Ошибка","Почта уже занята");
        }

    }
    else
    {
        qDebug() << "reg";
        ui->lineEdit_mail->clear();
        on_Swap_Button_clicked();
    }

}

void regauth::on_Auth_Button_clicked()
{
    if(ui->lineEdit_log->text().isEmpty() || (ui->lineEdit_pass->text().isEmpty()))
    {
       QMessageBox::critical(this,"Ошибка","Не заполнены или логин, или пароль");
    }
    else if(true)//тут будет запрос на авторизацию
    {
        //сюда сделаем фукнцию проверки есть ли такой пользователь и если она равна true мы ее
        emit closed(ui->lineEdit_log->text());
        this->close();
    }

}

