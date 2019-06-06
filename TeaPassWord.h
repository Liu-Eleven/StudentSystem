#ifndef TEAPASSWORD_H
#define TEAPASSWORD_H

#include <QWidget>
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QTime>
#include <QMessageBox>
namespace Ui {
class TeaPassWord;
}

class TeaPassWord : public QWidget
{
    Q_OBJECT

public:
    explicit TeaPassWord(QWidget *parent = 0);
    ~TeaPassWord();
    void setyanzheng();
    void clearAll();
    bool judgeEmpty();
private:
    Ui::TeaPassWord *ui;
    QString teachernum;
    int yanzheng;
    QSqlTableModel *model;

private slots:
    void comeTeacherManage(QString);
    void confirmbtnSlot();
    void returnbtnSlot();
signals:
    void EmitToTeacherManage();
};

#endif // TEAPASSWORD_H
