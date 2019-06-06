#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include "RegisterDialog.h"
#include "StudentManage.h"
#include "TeacherManage.h"
#include <QDebug>
#include <QDialog>
#include <QPalette>
#include <QButtonGroup>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlRecord>
namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
    void clearAll();
    bool judgeEmpty();
private:
    Ui::LoginDialog *ui;
    QButtonGroup *radiogroup;
    QSqlTableModel *model;
    StudentManage *student;
    TeacherManage *teacher;
signals:
    void toStudentManage(QString,QString);
    void toTeacherManage(QString,QString);
private slots:
    void exitbtnSlot();
    void registerbtnSlot();
    void loginbtnSlot();
    void loginbtnSetSlot(QString);
};

#endif // LOGINDIALOG_H
