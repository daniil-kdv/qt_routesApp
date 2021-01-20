#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include "employeeinfo.h"
#include "userwindow.h"
#include <QMessageBox>

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase mydb;
    void connClose()
    {
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }

    bool connOpen()
    {
        mydb = QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("C:/sqlite2/data.db");

        if(!mydb.open()){
            qDebug()<<"Failed to open the database";
            return false;
        } else{
            qDebug()<<"Connected...";
            return true;
        }
    }
    bool connOpen2()
    {
        mydb = QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("C:/sqlite2/routes.db");

        if(!mydb.open()){
            qDebug()<<"Failed to open the database";
            return false;
        } else{
            qDebug()<<"Connected...";
            return true;
        }
    }

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_user_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
