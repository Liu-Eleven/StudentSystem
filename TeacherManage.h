#ifndef TEACHERMANAGE_H
#define TEACHERMANAGE_H

#include "TeaPassWord.h"
#include "TeacherSearch.h"
#include "TeacherChangeScore.h"
#include "TeacherInsert.h"
#include "TeacherDelete.h"
#include <QWidget>
#include <QDebug>
#include <QTimer>
#include <QDatetime>

namespace Ui {
class TeacherManage;
}

class TeacherManage : public QWidget
{
    Q_OBJECT

public:
    explicit TeacherManage(QWidget *parent = 0);
    ~TeacherManage();
    void setbtntrue();
    void setbtnfalse();
private:
    Ui::TeacherManage *ui;
    QString teachername;
    QString teachernum;
    QTimer *timelinetimer;
    TeaPassWord *teapassword;
    TeacherSearch *teachersearch;
    TeacherChangeScore *teacherchangescore;
    TeacherInsert *teacherinsert;
    TeacherDelete *teacherdelete;
private slots:
    void comeLoginDialog(QString,QString);
    void settimeline();
    void exitbtnSlot();
    void returnbtnSlot();
    void passwordbtnSlot();
    void searchbtnSlot();
    void changebtnSlot();
    void insertbtnSlot();
    void deletebtnSlot();
    void setbtnEnableSlot();
    void tosetStack();
signals:
    void toLoginDialog();
    void toTeaPassWord(QString);
    void toTeacherSearch();
    void toTeacherChangeScore();
    void toTeacherDelete();
};

#endif // TEACHERMANAGE_H
