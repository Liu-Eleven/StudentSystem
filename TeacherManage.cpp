#include "TeacherManage.h"
#include "ui_TeacherManage.h"

TeacherManage::TeacherManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TeacherManage)
{
    ui->setupUi(this);
    //设置教师成绩管理界面背景
    QPalette p;
    p.setBrush(QPalette::Background,QBrush(QPixmap(":/student/img/studentbk19.jpg").scaled(this->size())));
    this->setPalette(p);
    //设置教师成绩管理界面为固定大小
    this->setMaximumSize(822,583);
    this->setMinimumSize(822,583);
    //设置教师成绩管理界面的标题
    this->setWindowTitle("教师成绩管理");
    //设置教师成绩管理界面的图标
    this->setWindowIcon(QIcon(":/student/img/book.jpg"));
    //设置定时器
    timelinetimer=new QTimer(this);
    timelinetimer->setInterval(100);
    timelinetimer->start();
    connect(timelinetimer,SIGNAL(timeout()),this,SLOT(settimeline()));
    //设置按钮图标
    ui->searchbtn->setIcon(QIcon(":/student/img/m5.png"));
    ui->searchbtn->setFlat(true);
    ui->changebtn->setIcon(QIcon(":/student/img/m1.png"));
    ui->changebtn->setFlat(true);
    ui->insertbtn->setIcon(QIcon(":/student/img/m13.png"));
    ui->insertbtn->setFlat(true);
    ui->deletebtn->setIcon(QIcon(":/student/img/m3.png"));
    ui->deletebtn->setFlat(true);
    ui->passwordbtn->setIcon(QIcon(":/student/img/m4.png"));
    ui->passwordbtn->setFlat(true);
    ui->returnbtn->setIcon(QIcon(":/student/img/m6.png"));
    ui->returnbtn->setFlat(true);
    ui->exitbtn->setIcon(QIcon(":/student/img/m7.png"));
    ui->exitbtn->setFlat(true);
    //设置toolbox标题
    ui->teachertool->setItemText(0,"成绩管理");
    ui->teachertool->setItemText(1,"个人中心");
    //连接退出系统按钮信号和槽
    connect(ui->exitbtn,SIGNAL(clicked()),this,SLOT(exitbtnSlot()));
    //连接返回按钮信号和槽
    connect(ui->returnbtn,SIGNAL(clicked()),this,SLOT(returnbtnSlot()));
    //创建教师修改密码窗口
    teapassword=new TeaPassWord;
    ui->teacherstack->addWidget(teapassword);
    teapassword->hide();
    connect(ui->passwordbtn,SIGNAL(clicked()),this,SLOT(passwordbtnSlot()));
    connect(this,SIGNAL(toTeaPassWord(QString)),teapassword,SLOT(comeTeacherManage(QString)));
    //创建教师查询成绩窗口
    teachersearch=new TeacherSearch;
    ui->teacherstack->addWidget(teachersearch);
    connect(this,SIGNAL(toTeacherSearch()),teachersearch,SLOT(comeTeacherManage()));
    connect(ui->searchbtn,SIGNAL(clicked()),this,SLOT(searchbtnSlot()));
    //创建教师修改成绩窗口
    teacherchangescore=new TeacherChangeScore;
    ui->teacherstack->addWidget(teacherchangescore);
    connect(this,SIGNAL(toTeacherChangeScore()),teacherchangescore,SLOT(comeTeacherManage()));
    connect(ui->changebtn,SIGNAL(clicked()),this,SLOT(changebtnSlot()));
    //创建教师增加学生成绩窗口
    teacherinsert=new TeacherInsert;
    ui->teacherstack->addWidget(teacherinsert);
    connect(ui->insertbtn,SIGNAL(clicked()),this,SLOT(insertbtnSlot()));
    //创建教师删除学生窗口
    teacherdelete=new TeacherDelete;
    ui->teacherstack->addWidget(teacherdelete);
    connect(ui->deletebtn,SIGNAL(clicked()),this,SLOT(deletebtnSlot()));
    connect(this,SIGNAL(toTeacherDelete()),teacherdelete,SLOT(comeStudentManage()));
    //实现个功能窗口与教师成绩管理窗口信号槽连接，用于设置button的属性
    connect(teachersearch,SIGNAL(EmitToTeacherManage()),this,SLOT(setbtnEnableSlot()));
    connect(teacherchangescore,SIGNAL(EmitToTeacherManage()),this,SLOT(setbtnEnableSlot()));
    connect(teacherinsert,SIGNAL(EmitToTeacherManage()),this,SLOT(setbtnEnableSlot()));
    connect(teacherdelete,SIGNAL(EmitToTeacherManage()),this,SLOT(setbtnEnableSlot()));
    connect(teapassword,SIGNAL(EmitToTeacherManage()),this,SLOT(setbtnEnableSlot()));
    connect(teachersearch,SIGNAL(EmitToTeacherManageToChangeStack()),this,SLOT(tosetStack()));
    connect(teacherchangescore,SIGNAL(EmitToTeacherManageToChangeStack()),this,SLOT(tosetStack()));
}
TeacherManage::~TeacherManage()
{
    delete ui;
}
void TeacherManage::comeLoginDialog(QString name, QString num)
{
    teachername=name;
    teachernum=num;
    ui->teachernameline->setText(teachername);
}
void TeacherManage::settimeline()
{
    QDateTime time=QDateTime::currentDateTime();
    QString str=time.toString("yyyy-MM-dd hh:mm:ss ddd");
    ui->timeline->setText(str);
}
void TeacherManage::exitbtnSlot()
{
    if(QMessageBox::question(this,"提示","是否退出系统?",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
    {
    this->close();
    delete this;
    }
}
void TeacherManage::returnbtnSlot()
{
    if(QMessageBox::question(this,"提示","是否注销用户?",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
    {
    emit toLoginDialog();
    delete this;
    }
}
void TeacherManage::passwordbtnSlot()
{
    this->setbtnfalse();
    teapassword->show();
    emit toTeaPassWord(teachernum);
    ui->teacherstack->setCurrentIndex(0);

}
void TeacherManage::searchbtnSlot()
{
    this->setbtnfalse();
    teachersearch->show();
    ui->teacherstack->setCurrentIndex(1);
    emit toTeacherSearch();
}
void TeacherManage::changebtnSlot()
{
    this->setbtnfalse();
    teacherchangescore->show();
    ui->teacherstack->setCurrentIndex(2);
    emit toTeacherChangeScore();
}
void TeacherManage::insertbtnSlot()
{
    this->setbtnfalse();
    teacherinsert->show();
    ui->teacherstack->setCurrentIndex(3);
}
void TeacherManage::deletebtnSlot()
{
    this->setbtnfalse();
    teacherdelete->show();
    ui->teacherstack->setCurrentIndex(4);
    emit toTeacherDelete();
}
void TeacherManage::setbtnfalse()
{
    ui->searchbtn->setEnabled(false);
    ui->changebtn->setEnabled(false);
    ui->insertbtn->setEnabled(false);
    ui->deletebtn->setEnabled(false);
    ui->passwordbtn->setEnabled(false);
    ui->returnbtn->setEnabled(false);
    ui->exitbtn->setEnabled(false);
}
void TeacherManage::setbtntrue()
{
    ui->searchbtn->setEnabled(true);
    ui->changebtn->setEnabled(true);
    ui->insertbtn->setEnabled(true);
    ui->deletebtn->setEnabled(true);
    ui->passwordbtn->setEnabled(true);
    ui->returnbtn->setEnabled(true);
    ui->exitbtn->setEnabled(true);
}
void TeacherManage::setbtnEnableSlot()
{
    this->setbtntrue();
}
void TeacherManage::tosetStack()
{
    teacherinsert->show();
    ui->teacherstack->setCurrentIndex(3);
}
