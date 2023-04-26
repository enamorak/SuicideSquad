#ifndef REGAUTH_H
#define REGAUTH_H

#include <QWidget>
#include <QMessageBox>
#include <QString>
namespace Ui {
class regauth;
}

class regauth : public QWidget
{
    Q_OBJECT

public:
    explicit regauth(QWidget *parent = nullptr);
    ~regauth();

private slots:
    void on_Swap_Button_clicked();

    void on_Reg_Button_clicked();

    void on_Auth_Button_clicked();

private:
    Ui::regauth *ui;
    void swap_mode(bool);
signals:
    void closed(QString login);
};

#endif // REGAUTH_H
