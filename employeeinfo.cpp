#include "employeeinfo.h"
#include "ui_employeeinfo.h"
#include <QMessageBox>

EmployeeInfo::EmployeeInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmployeeInfo)
{
    ui->setupUi(this);
    Login conn;

    if(!conn.connOpen2()){
        ui->label_sec_status->setText("Failed to open the DataBase");
    } else{
        ui->label_sec_status->setText("База данных подключена...");
    }
}

EmployeeInfo::~EmployeeInfo()
{
    delete ui;
}

void EmployeeInfo::on_pushButton_clicked()
{
    Login conn;

    QString number,depTime,arrTime, station, days;
    number = ui->txt_number->text();
    depTime = ui->txt_deptime->text();
    arrTime = ui->txt_arrtime->text();
    station = ui->txt_station->text();
    days = ui->txt_days->text();

    if(!conn.connOpen2()){
        qDebug()<<"Failed to open the database";
        return;
    }

    conn.connOpen2();
    QSqlQuery qry;
    qry.prepare("insert into routes (number, depTime, arrTime, station, days) values('"+number+"','"+depTime+"','"+arrTime+"', '"+station+"', '"+days+"')");

    if(qry.exec( ))
    {
        QMessageBox::information(this, tr("Save"),tr("Сохранено"));
        conn.connClose();
    } else {
        QMessageBox::critical(this, tr("error::"),qry.lastError().text());
    }
}

void EmployeeInfo::on_pushButton_Edit_clicked()
{
    Login conn;

    QString number,depTime,arrTime, station, days;
    number = ui->txt_number->text();
    depTime = ui->txt_deptime->text();
    arrTime = ui->txt_arrtime->text();
    station = ui->txt_station->text();
    days = ui->txt_days->text();

    if(!conn.connOpen2()){
        qDebug()<<"Failed to open the database";
        return;
    }

    conn.connOpen2();
    QSqlQuery qry;
    qry.prepare("update routes set number='"+number+"', depTime='"+depTime+"', arrTime='"+arrTime+"',station='"+station+"', days='"+days+"' where number='"+number+"'");

    if(qry.exec( ))
    {
        QMessageBox::information(this, tr("Edit"),tr("Изменения сохранены"));
        conn.connClose();
    } else {
        QMessageBox::critical(this, tr("error::"),qry.lastError().text());
    }
}

void EmployeeInfo::on_pushButton_delete_clicked()
{
    Login conn;

    QString number;
    number = ui->txt_number->text();

    if(!conn.connOpen2()){
        qDebug()<<"Failed to open the database";
        return;
    }

    conn.connOpen2();
    QSqlQuery qry;
    qry.prepare("Delete from routes where number='"+number+"'");

    if(qry.exec( ))
    {
        QMessageBox::information(this, tr("Delete"),tr("Удалено..."));
        conn.connClose();
    } else {
        QMessageBox::critical(this, tr("error::"),qry.lastError().text());
    }
}

void EmployeeInfo::on_pushButton_load_tbl_clicked()
{
    Login conn;
    QSqlQueryModel * modal = new QSqlQueryModel();

    conn.connOpen2();
    QSqlQuery* qry = new QSqlQuery(conn.mydb);

    qry->prepare("select * from routes");

    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);

    conn.connClose();

}

