#include "function.h"
#include <QString>
#include <QStringList>

QByteArray parse(QString msg,int fl)
{
    QStringList bufer = msg.split(" ");

    if(bufer[0] == "fun1")
    {

        return functuon1(bufer);
    }
    else if(bufer[0] == "fun2")
    {
        return functuon2(bufer);
    }
    else if(fl==0)
    {
       return 0;
    }
    else if(bufer[0] == "reg")
    {
        bufer.removeFirst();
        return sign_up(bufer).toUtf8();
    }
    else if(bufer[0] == "auth")
    {
        bufer.removeFirst();
        return sign_in(bufer).toUtf8();
    }
    else
    {
        return "Erorr";
    }
}

QByteArray functuon1(QStringList temp)
{
    return temp[0].toUtf8();
}

QByteArray functuon2(QStringList temp)
{
   return temp[0].toUtf8();
}
QString sign_in(QStringList temp)
{
    QStringList ans = singletonBD::getInstance()->getValue("select Login, Password from User where Login = " + temp[0]);
    //здесь у нас отправляется запрос на БД с проверкой существования пользователя

    if(ans.size()>0)//если хоть что-то пришло значит гуд
        return "auth&+";
    else    return "auth&-";
}

QString sign_up(QStringList temp)
{
    QStringList ans = singletonBD::getInstance()->getValue("INSERT INTO User(Login, Password, Mail, task1, task2, task3, task4) VALUES ('" + temp[0] + "','" + temp[1] + "','" + temp[2] + "',0,0,0,0)");
    if(ans.size()>0)//если пришла ошибка, то не гуд
    return "reg&-";
    else    return "reg&+";
}

QString get_tack(QStringList temp)
{
    QString ans = temp[0];

    return 0;
}

QString task_1(QStringList temp)
{
    QStringList ans = singletonBD::getInstance()->getValue("UPDATE User set task1 ="+temp[1]+" where login ="+ temp[0]+"");
    if(ans.size()==0)//если равна нулю то гуд
    return "task1&+";
    else    return "task1&-";
}

QString task_2(QStringList temp)
{
    QStringList ans = singletonBD::getInstance()->getValue("UPDATE User set task2 ="+temp[1]+" where login ="+ temp[0]+"");
    if(ans.size()==0)//если равна нулю то гуд
    return "task2&+";
    else    return "task2&-";
}

QString task_3(QStringList temp)
{
    QStringList ans = singletonBD::getInstance()->getValue("UPDATE User set task3 ="+temp[1]+" where login ="+ temp[0]+"");
    if(ans.size()==0)//если равна нулю то гуд
    return "task3&+";
    else    return "task3&-";
}
QString task_4(QStringList temp)
{
    QStringList ans = singletonBD::getInstance()->getValue("UPDATE User set task4 ="+temp[1]+" where login ="+ temp[0]+"");
    if(ans.size()==0)//если равна нулю то гуд
    return "task4&+";
    else    return "task4&-";
}


