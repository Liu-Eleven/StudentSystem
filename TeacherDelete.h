#ifndef TEACHERDELETE_H
#define TEACHERDELETE_H

#include <QWidget>
#include <QDebug>
#include <QSqlTableModel>
#include <QMessageBox>
namespace Ui {
class TeacherDelete;
}

class TeacherDelete : public QWidget
{
    Q_OBJECT

public:
    explicit TeacherDelete(QWidget *parent = 0);
    ~TeacherDelete();

private:
    Ui::TeacherDelete *ui;
    QSqlTableModel *model;
private slots:
    void delbtnSlot();
    void returnbtnSlot();
    void comeStudentManage();
signals:
    void EmitToTeacherManage();
};

#endif // TEACHERDELETE_H
