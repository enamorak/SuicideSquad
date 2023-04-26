#ifndef TASKFORM_H
#define TASKFORM_H

#include <QWidget>
#include <QDateTime>
#include <time.h>
#include <QMessageBox>
#include <QString>
namespace Ui {
class TaskForm;
}

class TaskForm : public QWidget
{
    Q_OBJECT

public:
    explicit TaskForm(QWidget *parent = nullptr);
    ~TaskForm();

private slots:

    void on_BackButton_clicked();

    void on_EnterButton_clicked();

private:
    Ui::TaskForm *ui;
    void generatVar(QString);
signals:
    void back(QString);
public slots:
    void open(QString,QString);
};

#endif // TASKFORM_H
