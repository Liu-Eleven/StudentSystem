﻿#include "StuPassWord.h"
#include "ui_StuPassWord.h"

StuPassWord::StuPassWord(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StuPassWord)
{
    ui->setupUi(this);
    //创建model实现与数据库交互
    model=new QSqlTableModel(this);
    model->setTable("student");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //设置输入lineedit为密码样式
    ui->oldpassline->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    ui->oldpassline->setPlaceholderText("请输入旧密码");
    ui->newpassline->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    ui->newpassline->setPlaceholderText("请输入新密码");
    ui->newpassline1->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    ui->newpassline1->setPlaceholderText("请再次输入新密码");
    ui->yanzhengline->setPlaceholderText("请输入验证码");
    //设置按钮的图标
    ui->confirmbtn->setIcon(QIcon(":/student/img/m10.png"));
    ui->confirmbtn->setFlat(true);
    ui->canclebtn->setIcon(QIcon(":/student/img/m17.png"));
    ui->canclebtn->setFlat(true);
    //设置验证码
    QTime t;
    t= QTime::currentTime();
    qsrand(t.msec()+t.second()*1000);
    this->setyanzheng();
    //两个按钮连接槽函数
    connect(ui->confirmbtn,SIGNAL(clicked()),this,SLOT(confirmbtnSlot()));
    connect(ui->canclebtn,SIGNAL(clicked()),this,SLOT(canclebtnSlot()));
}

StuPassWord::~StuPassWord()
{
    delete ui;
}
void StuPassWord::setyanzheng()
{
    yanzheng=rand()%10000;
    while(yanzheng<1000)
    yanzheng=rand()%10000;
    ui->yanzhenglabel->setText(QString::number(yanzheng));
}
void StuPassWord::comeStudentManage(QString num)
{
    studentnum=num;
}
void StuPassWord::confirmbtnSlot()
{
    int i;
    model->select();
    if(!this->judgeEmpty())
    {
        this->clearAll();
        this->setyanzheng();
        return;
    }
    for(i=0;i<model->rowCount();i++)
    {
        QSqlRecord record=model->record(i);
        if(studentnum==record.value(0))
        {
            break;
        }
    }
    QSqlRecord record=model->record(i);
    if(record.value(5)!=ui->oldpassline->text())
    {
        QMessageBox::warning(this,"警告","旧密码输入有误,请重新设置",QMessageBox::Yes);
        this->clearAll();
        this->setyanzheng();
        return;
    }
    if(ui->newpassline->text()!=ui->newpassline1->text())
    {
        QMessageBox::warning(this,"警告","两次密码输入不一致,请重新设置",QMessageBox::Yes);
        this->clearAll();
        this->setyanzheng();
        return;
    }
    if(ui->oldpassline->text()==ui->newpassline->text())
    {
        QMessageBox::warning(this,"警告","新旧密码一致,请重新设置",QMessageBox::Yes);
        this->clearAll();
        this->setyanzheng();
        return;
    }
    if(ui->yanzhengline->text()!=ui->yanzhenglabel->text())
    {
        QMessageBox::warning(this,"警告","验证码输入有误",QMessageBox::Yes);
        this->clearAll();
        this->setyanzheng();
        return;
    }
    model->setData(model->index(i,5),ui->newpassline->text());
   if(model->submitAll())
   QMessageBox::information(this,"提示","密码修改成功",QMessageBox::Yes);
   else
   QMessageBox::information(this,"提示","密码修改失败",QMessageBox::Yes);
   this->clearAll();
   this->setyanzheng();
}
void StuPassWord::canclebtnSlot()
{
    if(ui->oldpassline->text().isEmpty()&&ui->newpassline->text().isEmpty()&&
       ui->newpassline1->text().isEmpty())
    {
    emit EmitToStuManage();
    this->hide();
    this->clearAll();
    this->setyanzheng();
        return;
    }
    if(QMessageBox::question(this,"提示","密码尚未修改,是否退出",QMessageBox::Yes|QMessageBox::No)
            ==QMessageBox::Yes)
    {
        emit EmitToStuManage();
        this->hide();
        this->clearAll();
        this->setyanzheng();
    }
}
bool StuPassWord::judgeEmpty()
{
    if(ui->oldpassline->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","旧密码不能为空");
        return false;
    }
    else if(ui->newpassline->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","新密码不能为空");
        return false;
    }
    else if(ui->newpassline1->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","确认密码不能为空");
        return false;
    }
    else if(ui->yanzhengline->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","验证码不能为空");
        return false;
    }
    else
        return true;
}
void StuPassWord::clearAll()
{
    ui->oldpassline->clear();
    ui->newpassline->clear();
    ui->newpassline1->clear();
    ui->yanzhengline->clear();
}



