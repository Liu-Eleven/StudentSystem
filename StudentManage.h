#ifndef STUDENTMANAGE_H
#define STUDENTMANAGE_H
#include <QWidget>
#include <QDebug>
#include <QPalette>
#include <QDateTime>
#include <QTimer>
#include "StuPassWord.h"
#include "StuInfo.h"
#include "StuInfoSearch.h"
#include "StudentSocre.h"
namespace Ui {
class StudentManage;
}

class StudentManage : public QWidget
{
    Q_OBJECT

public:
    explicit StudentManage(QWidget *parent = 0);
    ~StudentManage();
    void btnsettrue();
    void btnsetfalse();
private slots:
    void comeLoginDialog(QString,QString);
    void settimeline();
    void passwordbtnSlot();
    void infobtnSlot();
    void searchbtnSlot();
    void exitbtnSlot();
    void setbtnEnable();
    void returnbtnSlot();
    void scorebtnSlot();
    void stuinfosearchSlot();
signals:
    void tostudentname(QString);
    void toStuInfoSearch(QString);
    void toLoginDialog();
    void toStudentScore(QString);
private:
    Ui::StudentManage *ui; 
    QString studentname,studentnum;
    QTimer *timelinetimer;
    StuPassWord *stupassword;
    StuInfo *stuinfo;
    StuInfoSearch *stuinfosearch;
    StudentSocre *studentscore;
};

#endif // STUDENTMANAGE_H
