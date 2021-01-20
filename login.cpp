#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    if(!connOpen()){
        ui->label->setText("Failed to open the DataBase");
    } else{
        ui->label->setText("База данных подключена...");
    }
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
    QString username,password;
    username = ui->lineEdit_username->text();
    password = ui->lineEdit_Password->text();

    if(!connOpen()){
        qDebug()<<"Failed to open the database";
        return;
    }

    connOpen();
    QSqlQuery qry;
    qry.prepare("select * from employees where username='"+username+"' and password='"+password+"'");

    if(qry.exec( ))
    {
        int count=0;
        while(qry.next())
        {
           count++;
        }
        if(count == 1){
            QMessageBox::warning(this, tr("Админ-панель"),tr("Вы вошли в админ-панель"));
            connClose();
            this->hide();
            EmployeeInfo employeeinfo;
            employeeinfo.setModal(true);
            employeeinfo.exec();
        }
        if(count > 1)
            ui->label->setText("Duplicate username and password");
        if(count < 1)
            QMessageBox::critical(this, tr("Ошибка"),tr("Введен неверный логин и/или пароль"));
    }
}

void Login::on_pushButton_user_clicked()
{
    connClose();
    this->hide();
    userWindow userW;
    userW.setModal(true);
    userW.exec();

}
