#ifndef FUNCTION_H
#define FUNCTION_H
#include <QByteArray>
#include "singletonbd.h"

/**
 * @brief parse функция парса
 * @param msg сообщение полученное сервером от пользователя обрабатывающиеся вв это фукнции
 * @param fl тот самый флаг решающий проблему пустой строки
 * @return возвращает QByteArray с ответом
 */
QByteArray parse(QString msg,int fl);

QString sign_in(QStringList temp);//фукция входа
QString sign_up(QStringList temp);//функция регистрации
QString get_tack(QStringList temp);//функция выдачи task
QString task_1(QStringList temp);//функции занесения в БД резултата task_1
QString task_2(QStringList temp);//функции занесения в БД резултата task_2
QString task_3(QStringList temp);//функции занесения в БД резултата task_3
QString task_4(QStringList temp);//функции занесения в БД резултата task_4
QByteArray functuon1(QStringList temp);//тестовые функции
QByteArray functuon2(QStringList temp);//тестовые функции

#endif // FUNCTION_H
