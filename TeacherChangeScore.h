#ifndef TEACHERCHANGESCORE_H
#define TEACHERCHANGESCORE_H

#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlRecord>
namespace Ui {
class TeacherChangeScore;
}

class TeacherChangeScore : public QWidget
{
    Q_OBJECT

public:
    explicit TeacherChangeScore(QWidget *parent = 0);
    ~TeacherChangeScore();

private:
    Ui::TeacherChangeScore *ui;
    QSqlTableModel *model;
    int judge;
private slots:
    void comeTeacherManage();
    void confirmbtnSlot();
    void returnbtnSlot();
    void judgeSlot(QModelIndex,QModelIndex);
signals:
    void EmitToTeacherManage();
    void EmitToTeacherManageToChangeStack();
};

#endif // TEACHERCHANGESCORE_H
