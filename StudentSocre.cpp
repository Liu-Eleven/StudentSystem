#include "StudentSocre.h"
#include "ui_StudentSocre.h"

StudentSocre::StudentSocre(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudentSocre)
{
    ui->setupUi(this);
    //返回按钮信号与槽连接
    connect(ui->returnbtn,SIGNAL(clicked()),this,SLOT(returnbtnSlot()));
    //设置按钮图标
    ui->returnbtn->setIcon(QIcon(":/student/img/m1.png"));
    //创建model实现与数据库的交互
    model=new QSqlTableModel(this);
    model->setTable("student");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setHeaderData(0,Qt::Horizontal,"学号");
    model->setHeaderData(1,Qt::Horizontal,"学生姓名");
    model->setHeaderData(2,Qt::Horizontal,"语文成绩");
    model->setHeaderData(3,Qt::Horizontal,"数学成绩");
    model->setHeaderData(4,Qt::Horizontal,"英语成绩");
    model->removeColumns(5,5);
    //设置view不可修改
    ui->scoreview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->scoreview->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

StudentSocre::~StudentSocre()
{
    delete ui;
}
void StudentSocre::comeStudentManage(QString num)
{
    studentnum=num;
    QString str;
    str="studentnum="+studentnum;
    model->setFilter(str);
    model->select();
    QSqlRecord record=model->record(0);
    if(     record.value(2).toFloat()==0&&
            record.value(3).toFloat()==0&&
            record.value(4).toFloat()==0 )
    {
        QMessageBox::information(this,"提示","老师尚未上传成绩,留意班级通知!!",QMessageBox::Yes);
        emit EmitToStuManage();
        this->hide();
        return;
    }
    ui->scoreview->setModel(model);
}
void StudentSocre::returnbtnSlot()
{
    this->hide();
    emit EmitToStuManage();
}
