#include "StuInfo.h"
#include "ui_StuInfo.h"

StuInfo::StuInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StuInfo)
{
    ui->setupUi(this);
    //创建model用于与数据库交互
    model=new QSqlTableModel(this);
    model->setTable("student");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //设置窗口大小固定
    this->setMaximumSize(641,501);
    this->setMinimumSize(641,501);
    //设置按钮图标
    ui->confirmbtn->setIcon(QIcon(":/student/img/m13.png"));
    ui->canclebtn->setIcon(QIcon(":/student/img/m14.png"));
    ui->confirmbtn->setFlat(true);
    ui->canclebtn->setFlat(true);
    //设置lineedit显示提示信息
    ui->telephoneline->setPlaceholderText("请输入电话号码");
    ui->qqline->setPlaceholderText("请输入qq号码");
    ui->emainline->setPlaceholderText("请输入e-mail");
    ui->adressline->setPlaceholderText("请输入家庭地址");
    //两个按钮连接槽函数
    connect(ui->canclebtn,SIGNAL(clicked()),this,SLOT(canclebtnSlot()));
    connect(ui->confirmbtn,SIGNAL(clicked()),this,SLOT(confimbtnSlot()));
    //emailline连接槽函数设置completer
   connect(ui->emainline,SIGNAL(textChanged(QString)),this,SLOT(emainlineSlot(QString)));
}

StuInfo::~StuInfo()
{
    delete ui;
}
void StuInfo::canclebtnSlot()
{ 
    if(ui->telephoneline->text().isEmpty()&&ui->qqline->text().isEmpty()&&
       ui->emainline->text().isEmpty()&&ui->adressline->text().isEmpty())
    {
        this->hide();
        emit EmitToStuManage();
        return;
    }
    if(QMessageBox::question(this,"提示","尚未提交学生信息，是否退出?",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
    {
        this->hide();
        emit EmitToStuManage();
        this->clearAll();
    }
}
void StuInfo::comeStudentManage(QString num)
{
    this->studentnum=num;
}
void StuInfo::confimbtnSlot()
{
    int i;
    if(!this->judgeEmpty())
    {
        return;
    }
    model->select();

    for(i=0;i<model->rowCount();i++)
    {
        QSqlRecord record=model->record(i);
        if(record.value(0)==studentnum)
        {
            break;
        }
    }
    model->setData(model->index(i,6),ui->telephoneline->text());
    model->setData(model->index(i,7),ui->qqline->text());
    model->setData(model->index(i,8),ui->emainline->text());
    model->setData(model->index(i,9),ui->adressline->text());
    if(model->submitAll())
    {
        QMessageBox::information(this,"提示","学生信息修改成功",QMessageBox::Yes);
    }
    else
    {
        QMessageBox::information(this,"提示","学生信息修改失败",QMessageBox::Yes);
    }
    this->clearAll();
}
bool StuInfo::judgeEmpty()
{
    if(ui->telephoneline->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","用户电话信息不能为空");
        return false;
    }
    else if(ui->qqline->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","用户qq信息不能为空");
        return false;
    }
    else if(ui->emainline->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","用户email信息不能为空");
        return false;
    }
    else if(ui->adressline->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","用户家庭地址信息不能为空");
        return false;
    }
    else
        return true;
}
void StuInfo::clearAll()
{
    ui->telephoneline->clear();
    ui->qqline->clear();
    ui->emainline->clear();
    ui->adressline->clear();
}
void StuInfo::emainlineSlot(QString)
{
    //设置completer
    QStringList list;
    list<<ui->emainline->text()+"@163.com"<<ui->emainline->text()+"@qq.com"
       <<ui->emainline->text()+"@sina.com"<<ui->emainline->text()+"@gmail.com";
    listmodel=new QStringListModel(list,this);
    completer=new QCompleter(this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setModel(listmodel);
    ui->emainline->setCompleter(completer);
}

