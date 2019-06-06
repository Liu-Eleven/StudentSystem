#ifndef STUINFOSEARCH_H
#define STUINFOSEARCH_H

#include <QWidget>
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QMessageBox>
namespace Ui {
class StuInfoSearch;
}

class StuInfoSearch : public QWidget
{
    Q_OBJECT

public:
    explicit StuInfoSearch(QWidget *parent = 0);
    ~StuInfoSearch();
private slots:
    void comeStudentManage(QString);
    void returnbtnSlot();
private:
    Ui::StuInfoSearch *ui;
    QString studentnum;
    QSqlTableModel *model;
signals:
    void EmitToStuManage();
    void EimtToStudengStack();
};

#endif // STUINFOSEARCH_H
