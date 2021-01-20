#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QDialog>
#include "login.h"
#include "print.h"
#include "ui_print.h"
#include <QSortFilterProxyModel>
#include <QSqlRelationalDelegate>
#include <QCompleter>
#include <QPrinter>
#include <QTextDocument>
#include <QFileDialog>

namespace Ui {
class userWindow;
}

class userWindow : public QDialog
{
    Q_OBJECT

public:
    explicit userWindow(QWidget *parent = 0);
    ~userWindow();
    QSortFilterProxyModel * proxyRoutes;
    QCompleter *completerRoutes;
    Print *printIt;

private slots:
    void on_pushButton_schedule_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_cbColumns_currentIndexChanged(int index);

    void on_pushButton_5_clicked();

    void on_toolButton_clicked();

private:
    Ui::userWindow *ui;
};

#endif // USERWINDOW_H

