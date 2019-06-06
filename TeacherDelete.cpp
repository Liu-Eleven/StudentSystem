#include "TeacherDelete.h"
#include "ui_TeacherDelete.h"

TeacherDelete::TeacherDelete(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TeacherDelete)
{
    ui->setupUi(this);
    //创建model实现与数据库交互
    model=new QSqlTableModel(this);
    model->setTable("student");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setHeaderData(0,Qt::Horizontal,"学号");
    model->setHeaderData(1,Qt::Horizontal,"学生姓名");
    model->setHeaderData(2,Qt::Horizontal,"语文成绩");
    model->setHeaderData(3,Qt::Horizontal,"数学成绩");
    model->setHeaderData(4,Qt::Horizontal,"英语成绩");
    model->removeColumns(5,5);
    //设置view不可编辑
    ui->teacherdeleteview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->teacherdeleteview->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    //设置按钮图标
    ui->delbtn->setIcon(QIcon(":/student/img/m11.png"));
    ui->delbtn->setFlat(true);
    ui->returnbtn->setIcon(QIcon(":/student/img/m8.png"));
    ui->returnbtn->setFlat(true);
    //设置line提示
    ui->delline->setPlaceholderText("请输入学生学号");
    //连接按钮的信号和槽
    connect(ui->delbtn,SIGNAL(clicked()),this,SLOT(delbtnSlot()));
    connect(ui->returnbtn,SIGNAL(clicked()),this,SLOT(returnbtnSlot()));
}

TeacherDelete::~TeacherDelete()
{
    delete ui;
}
void TeacherDelete::delbtnSlot()
{

  if(ui->delline->text().isEmpty())
  {
      QMessageBox::warning(this,"警告","删除输入框不能为空");
      return;
  }
  model->select();
  int i;
  for(i=0;i<model->rowCount();i++)
  {
      if(model->data(model->index(i,0)).toString()==ui->delline->text())
      {
          if(QMessageBox::question(this,"提示","确定要删除吗？",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
          {
              model->removeRow(i);
              model->submitAll();
              ui->delline->clear();
              return;
          }
          else
              return;
      }
  }
  QMessageBox::information(this,"提示","学生用户不存在，删除失败!");
  ui->delline->clear();
}
void TeacherDelete::returnbtnSlot()
{
    ui->delline->clear();
    emit EmitToTeacherManage();
    this->hide();
}
void TeacherDelete::comeStudentManage()
{
    model->select();
    if(model->data(model->index(0,0)).toString().isEmpty())
    {
        QMessageBox::information(this,"提示","学生信息为空,无法删除学生信息",QMessageBox::Yes);
        emit EmitToTeacherManage();
        this->hide();
        return;
    }
    ui->teacherdeleteview->setModel(model);
}
