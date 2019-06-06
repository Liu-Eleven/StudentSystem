#ifndef STUDENTSOCRE_H
#define STUDENTSOCRE_H

#include <QWidget>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QDebug>
namespace Ui {
class StudentSocre;
}

class StudentSocre : public QWidget
{
    Q_OBJECT

public:
    explicit StudentSocre(QWidget *parent = 0);
    ~StudentSocre();
    QString studentnum;
private slots:
    void comeStudentManage(QString);
    void returnbtnSlot();
signals:
    void EmitToStuManage();
private:
    Ui::StudentSocre *ui;
    QSqlTableModel *model;
};

#endif // STUDENTSOCRE_H
