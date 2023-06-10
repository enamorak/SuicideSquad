#include <QtTest>
#include <QString>
#include"../SERV_351_SS/function.h"

// add necessary includes here

class un1 : public QObject
{
    Q_OBJECT

private slots:
    void test_case1();
    void test_case2();
    void test_case3();
};

void un1::test_case1()
{
    QString str1 = "get task1";
    str1 = parse(str1,0);
    QStringList list = str1.split("||");

    QCOMPARE(QString("-1").toUtf8(), parse(QString("ans "+list[1]+" 0 "+"task1 "+" -/+1 " + "1"), 0));

    QCOMPARE(QString("+1").toUtf8(), parse(QString("ans "+list[1]+" "+list[1]+" task1 "+" -/+1 " + "1"), 0));
}

void un1::test_case2()
{
    QString str1 = "get task2";
    str1 = parse(str1,0);
    QStringList list = str1.split("||");

    QCOMPARE(QString("-1").toUtf8(), parse(QString("ans2 12434526 "+ list[1]+" task2 "+"-/+1 " + "1"), 0));

    QCOMPARE(QString("+1").toUtf8(), parse(QString("ans2 1234567891 "+ list[1]+" task2 "+"-/+1 " + "1"), 0));
}

void un1::test_case3()
{
    QString str1,otvet;
    QStringList list,buf_list,sub_buf;

    str1 = parse("get task3",0);
    list = str1.split("||");
    buf_list = list;
    buf_list.removeFirst();

    sub_buf=buf_list[1].split(" ");
    for(int i = 0;i < buf_list[0].toInt(); i++){
        otvet.append(QString::number(calc(sub_buf[0].toInt(),sub_buf[1].toInt()))+" ");
        sub_buf.removeAt(0);
        sub_buf.removeAt(0);
    }

    QCOMPARE(QString("-1").toUtf8(), parse(QString("ans3 "+list[1]+" "+list[2]+" -1 -1 -1 -1 -1 "+"task3 "+" -/+1 " + "1"), 0));

    QCOMPARE(QString("+1").toUtf8(), parse(QString("ans3 "+list[1]+" "+list[2]+" "+ otvet +"task3 "+" -/+1 " + "1"), 0));

 }
QTEST_APPLESS_MAIN(un1)

#include "tst_un1.moc"
