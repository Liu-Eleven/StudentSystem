#ifndef TEACHERINSERT_H
#define TEACHERINSERT_H

#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlRecord>
namespace Ui {
class TeacherInsert;
}

class TeacherInsert : public QWidget
{
    Q_OBJECT

public:
    explicit TeacherInsert(QWidget *parent = 0);
    ~TeacherInsert();
    bool judgeEmpty();
    void clearAll();
private:
    Ui::TeacherInsert *ui;
    QSqlTableModel *model;
private slots:
    void returnbtnSlot();
    void confirmbtnSlot();
signals:
    void EmitToTeacherManage();
};

#endif // TEACHERINSERT_H
