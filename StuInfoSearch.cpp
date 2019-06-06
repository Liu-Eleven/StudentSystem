#include "StuInfoSearch.h"
#include "ui_StuInfoSearch.h"

StuInfoSearch::StuInfoSearch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StuInfoSearch)
{
    ui->setupUi(this);

    //设置按钮的图标
    ui->returnbtn->setIcon(QIcon(":/student/img/m2.png"));
    ui->returnbtn->setFlat(true);
    //返回按钮连接信号和槽
    connect(ui->returnbtn,SIGNAL(clicked()),this,SLOT(returnbtnSlot()));
    //创建model实现与数据库交互
    model=new QSqlTableModel(this);
    model->setTable("student");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

}

StuInfoSearch::~StuInfoSearch()
{
    delete ui;
}
void StuInfoSearch::comeStudentManage(QString num)
{

    studentnum=num;
    QString str;
    str="studentnum="+studentnum;
    model->setFilter(str);
    model->select();
    QSqlRecord record=model->record(0);
        if(record.value(6)==""&&record.value(7)==""
                &&record.value(8)==""&&record.value(9)=="")
        {
            ui->studentnumlabel->setText(record.value(0).toString());
            QMessageBox::information(this,"提示","学生个人信息为空,请填写学生信息",QMessageBox::Yes);
            emit EimtToStudengStack();
            this->hide();
            return;
        }
        ui->studentnumlabel->setText(record.value(0).toString());
        ui->telephonelabel->setText(record.value(6).toString());
        ui->qqlabel->setText(record.value(7).toString());
        ui->emaillabel->setText(record.value(8).toString());
        ui->adresslabel->setText(record.value(9).toString());
}

void StuInfoSearch::returnbtnSlot()
{
    this->hide();
    emit EmitToStuManage();
}
