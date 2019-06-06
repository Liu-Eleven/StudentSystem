#include "StudentManage.h"
#include "ui_StudentManage.h"

StudentManage::StudentManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudentManage)
{
    ui->setupUi(this);
    //设置学生成绩管理界面背景
    QPalette p;
    p.setBrush(QPalette::Background,QBrush(QPixmap(":/student/img/studentbk19.jpg").scaled(this->size())));
    this->setPalette(p);
    //设置学生成绩管理界面为固定大小
    this->setMaximumSize(822,583);
    this->setMinimumSize(822,583);
    //设置学生成绩管理界面的标题
    this->setWindowTitle("学生成绩管理");
    //设置学生成绩管理界面的图标
    this->setWindowIcon(QIcon(":/student/img/book.jpg"));
    //设置按钮的图标
    ui->scorebtn->setIcon(QIcon(":/student/img/bianfuxia.png"));
    ui->scorebtn->setFlat(true);
    ui->passwordbtn->setIcon(QIcon(":/student/img/m8.png"));
    ui->passwordbtn->setFlat(true);
    ui->infobtn->setIcon(QIcon(":/student/img/m14.png"));
    ui->infobtn->setFlat(true);
    ui->searchbtn->setIcon(QIcon(":/student/img/m10.png"));
    ui->searchbtn->setFlat(true);
    ui->exitbtn->setIcon(QIcon(":/student/img/m7.png"));
    ui->exitbtn->setFlat(true);
    ui->returnbtn->setIcon(QIcon(":/student/img/m9.png"));
    ui->returnbtn->setFlat(true);
    //设置工具栏名称
    ui->studenttool->setItemText(0,"成绩管理");
    ui->studenttool->setItemText(1,"个人中心");
    QDateTime time=QDateTime::currentDateTime();
    QString str=time.toString("yyyy-MM-dd hh:mm:ss ddd");
    ui->timeline->setText(str);
    //设置定时器
    timelinetimer=new QTimer(this);
    timelinetimer->setInterval(100);
    timelinetimer->start();
    connect(timelinetimer,SIGNAL(timeout()),this,SLOT(settimeline()));
    //创建密码修改窗口
    stupassword=new StuPassWord;
    ui->studentstack->addWidget(stupassword);
    stupassword->hide();
    connect(ui->passwordbtn,SIGNAL(clicked()),this,SLOT(passwordbtnSlot()));
    connect(this,SIGNAL(tostudentname(QString)),stupassword,SLOT(comeStudentManage(QString)));
    //创建学生信息修改窗口
    stuinfo=new StuInfo;
    ui->studentstack->addWidget(stuinfo);
    connect(ui->infobtn,SIGNAL(clicked()),this,SLOT(infobtnSlot()));
    connect(this,SIGNAL(tostudentname(QString)),stuinfo,SLOT(comeStudentManage(QString)));
    //创建学生信息查询窗口
    stuinfosearch=new StuInfoSearch;
    ui->studentstack->addWidget(stuinfosearch);
    connect(ui->searchbtn,SIGNAL(clicked()),this,SLOT(searchbtnSlot()));
    connect(this,SIGNAL(toStuInfoSearch(QString)),stuinfosearch,SLOT(comeStudentManage(QString)));
    //创建学生成绩查询窗口
    studentscore=new StudentSocre;
    ui->studentstack->addWidget(studentscore);
    connect(ui->scorebtn,SIGNAL(clicked()),this,SLOT(scorebtnSlot()));
    connect(this,SIGNAL(toStudentScore(QString)),studentscore,SLOT(comeStudentManage(QString)));
    //退出系统按钮信号与槽连接
    connect(ui->exitbtn,SIGNAL(clicked()),this,SLOT(exitbtnSlot()));

    //各个功能窗口与studentmanage窗口的信号与槽连接
    connect(stuinfo,SIGNAL(EmitToStuManage()),this,SLOT(setbtnEnable()));
    connect(stuinfosearch,SIGNAL(EmitToStuManage()),this,SLOT(setbtnEnable()));
    connect(stupassword,SIGNAL(EmitToStuManage()),this,SLOT(setbtnEnable()));
    connect(studentscore,SIGNAL(EmitToStuManage()),this,SLOT(setbtnEnable()));
    connect(stuinfosearch,SIGNAL(EimtToStudengStack()),this,SLOT(stuinfosearchSlot()));
    //注销用户按钮信号与槽连接
    connect(ui->returnbtn,SIGNAL(clicked()),this,SLOT(returnbtnSlot()));
}

StudentManage::~StudentManage()
{
    delete stupassword;
    delete stuinfo;
    delete stuinfosearch;
    delete ui;
}

void StudentManage::comeLoginDialog(QString name,QString num)
{
    studentname=name;
    studentnum=num;
    ui->studentnameline->setText(studentname);
}
void StudentManage::settimeline()
{
    QDateTime time=QDateTime::currentDateTime();
    QString str=time.toString("yyyy-MM-dd hh:mm:ss ddd");
    ui->timeline->setText(str);
}
void StudentManage::passwordbtnSlot()
{
    stupassword->show();
    ui->studentstack->setCurrentIndex(0);
    emit tostudentname(studentnum);
    this->btnsetfalse();
}
void StudentManage::infobtnSlot()
{
    stuinfo->show();
    ui->studentstack->setCurrentIndex(1);
    emit tostudentname(studentnum);
    this->btnsetfalse();
}
void StudentManage::searchbtnSlot()
{
    stuinfosearch->show();
    ui->studentstack->setCurrentIndex(2);
    this->btnsetfalse();
    emit toStuInfoSearch(studentnum);
}
void StudentManage::exitbtnSlot()
{
    if(QMessageBox::question(this,"提示","是否退出系统?",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
    {
    this->close();
    delete this;
    }
}
void StudentManage::btnsetfalse()
{
    ui->passwordbtn->setEnabled(false);
    ui->searchbtn->setEnabled(false);
    ui->exitbtn->setEnabled(false);
    ui->scorebtn->setEnabled(false);
    ui->infobtn->setEnabled(false);
    ui->returnbtn->setEnabled(false);
}
void StudentManage::btnsettrue()
{
    ui->exitbtn->setEnabled(true);
    ui->infobtn->setEnabled(true);
    ui->searchbtn->setEnabled(true);
    ui->passwordbtn->setEnabled(true);
    ui->scorebtn->setEnabled(true);
    ui->returnbtn->setEnabled(true);
}
void StudentManage::setbtnEnable()
{
 this->btnsettrue();
}

void StudentManage::returnbtnSlot()
{
    if(QMessageBox::question(this,"提示","是否注销用户?",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
    {
    emit toLoginDialog();
    delete this;
    }
}
void StudentManage::scorebtnSlot()
{
    studentscore->show();
    ui->studentstack->setCurrentIndex(3);
    this->btnsetfalse();
    emit toStudentScore(studentnum);

}
void StudentManage::stuinfosearchSlot()
{
    ui->studentstack->setCurrentIndex(1);
    emit tostudentname(studentnum);
}
