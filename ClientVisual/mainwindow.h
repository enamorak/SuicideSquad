#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include "regauth.h"
#include "taskform.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    regauth *ui_auth;
    TaskForm *ui_task;
    void go_task(QString);
    int check_point(QString);
signals:
    void go(QString, QString);
private slots:
    void slot_on_auth_closed(QString);

    void on_Exit_button_clicked();

    void on_Task1_Button_clicked();
    void on_Task2_Button_clicked();
    void on_Task3_Button_clicked();
    void on_Task4_Button_clicked();
};
#endif // MAINWINDOW_H
