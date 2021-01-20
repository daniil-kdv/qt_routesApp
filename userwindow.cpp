#include "userwindow.h"
#include "ui_userwindow.h"
#include <QMessageBox>

userWindow::userWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userWindow)
{
    ui->setupUi(this);
    Login conn;

    if(!conn.connOpen2()){
        ui->label_sec_status->setText("Failed to open the DataBase");
    } else{
        ui->label_sec_status->setText("База данных подключена...");
    }

    QSqlQueryModel * modal = new QSqlQueryModel();

    conn.connOpen2();
    QSqlQuery* qry = new QSqlQuery(conn.mydb);

    qry->prepare("select * from routes");

    qry->exec();
    modal->setQuery(*qry);


    modal->setHeaderData(0, Qt::Horizontal, "number");
    modal->setHeaderData(1, Qt::Horizontal, "depTime");

    proxyRoutes = new QSortFilterProxyModel(this);
    proxyRoutes->setSourceModel(modal);
    proxyRoutes->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxyRoutes->setFilterKeyColumn(-1);

    ui->pushButton_schedule->hide();
    ui->cbColumns->addItems(QStringList()<<"Номер"<<"Время отпр." <<"Время прибыт."<<"Станция"<<"Дни недели"<<"Все");
    ui->cbColumns->setCurrentIndex(5);

    ui->tableView->setModel(proxyRoutes);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->setColumnHidden(7,true);

    completerRoutes = new QCompleter(modal, this);
    completerRoutes->setCaseSensitivity(Qt::CaseInsensitive);
    completerRoutes->setCompletionColumn(1);
    ui->lineEdit->setCompleter(completerRoutes);

    conn.connClose();
}

userWindow::~userWindow()
{
    delete ui;
}

void userWindow::on_lineEdit_textChanged(const QString &arg1)
{
    proxyRoutes->setFilterFixedString(arg1);
    int numcolumn = ui->cbColumns->currentIndex();
    if(numcolumn == 5){
        numcolumn = 1;
    }

    completerRoutes->setCompletionColumn(ui->cbColumns->currentIndex());
}

void userWindow::on_cbColumns_currentIndexChanged(int index)
{

    proxyRoutes->setFilterKeyColumn(index);
}

void userWindow::on_pushButton_schedule_clicked()
{

}

void userWindow::on_pushButton_5_clicked()
{

    QString str;
    str.append("<html><head></head><body><center>"+QString("Создание отчета"));
    str.append("<table border=1><tr>");
    str.append("<td>"+QString("Номер")+"</td>");
    str.append("<td>"+QString("Время отпр.")+"</td>");
    str.append("<td>"+QString("Время прибыт.")+"</td>");
    str.append("<td>"+QString("Станция")+"</td>");
    str.append("<td>"+QString("Дни недели")+"</td></tr>");


    QSqlQuery* qry = new QSqlQuery();

    qry->exec("select * from routes");

    while (qry->next())
    {
        str.append("<tr><td>");
        str.append(qry->value(0).toString());
        str.append("</td><td>");
        str.append(qry->value(1).toString());
        str.append("</td><td>");
        str.append(qry->value(2).toString());
        str.append("</td><td>");
        str.append(qry->value(3).toString());
        str.append("</td><td>");
        str.append(qry->value(4).toString());
        str.append("</td></tr>");
    }

    str.append("</table></center></body></html>");

    QPrinter printer;
    printer.setOrientation(QPrinter::Portrait);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);

    QString path = QFileDialog::getSaveFileName(NULL, "Сохранить в PDF", "Отчет", "PDF(*.pdf)");

    if(path.isEmpty()) return;

    printer.setOutputFileName(path);
    QTextDocument doc;
    doc.setHtml(str);
    doc.print(&printer);
}

void userWindow::on_toolButton_clicked()
{
    ui->lineEdit->setText(QFileDialog::getOpenFileName(0, "Выберите файл", "./", "*.html"));
}
