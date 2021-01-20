#ifndef PRINT_H
#define PRINT_H

#include <QWidget>
#include <QAxObject>
#include <QSqlQuery>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

namespace Ui {
class Print;
}

class Print : public QWidget
{
    Q_OBJECT

public:
    explicit Print(QWidget *parent = 0);
    ~Print();

private:
    Ui::Print *ui;
};

#endif // PRINT_H
