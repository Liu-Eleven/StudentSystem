#include "TeacherSearch.h"
#include "ui_TeacherSearch.h"

TeacherSearch::TeacherSearch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TeacherSearch)
{
    ui->setupUi(this);
    //返回按钮连接信号和槽
    connect(ui->returnbtn,SIGNAL(clicked()),this,SLOT(returnbtnSlot()));
    connect(ui->searchbtn,SIGNAL(clicked()),this,SLOT(searchbtnSlot()));
    //设置view不可编辑
    ui->teachersearchview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->teachersearchview->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    //设置按钮图标
    ui->searchbtn->setIcon(QIcon(":/student/img/m1.png"));
    ui->searchbtn->setFlat(true);
    ui->returnbtn->setIcon(QIcon(":/student/img/m8.png"));
    ui->returnbtn->setFlat(true);
    //设置inputedit提示显示
    ui->inputline->setPlaceholderText("请输入学生学号或者学生姓名");
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

    //创建_model实现查询功能
    _model=new QSqlTableModel(this);
    _model->setTable("student");
    _model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    _model->setHeaderData(0,Qt::Horizontal,"学号");
    _model->setHeaderData(1,Qt::Horizontal,"学生姓名");
    _model->setHeaderData(2,Qt::Horizontal,"语文成绩");
    _model->setHeaderData(3,Qt::Horizontal,"数学成绩");
    _model->setHeaderData(4,Qt::Horizontal,"英语成绩");
    _model->removeColumns(5,5);
    //创建buttongroup
    buttongroup=new QButtonGroup(this);
    buttongroup->addButton(ui->numradio,0);
    buttongroup->addButton(ui->nameradio,1);
    //连接inputedit信号和槽
    connect(ui->inputline,SIGNAL(textChanged(QString)),this,SLOT(inputeditSlot(QString)));
    connect(buttongroup,SIGNAL(buttonClicked(int)),this,SLOT(buttongroupSlot(int)));
}

TeacherSearch::~TeacherSearch()
{
    delete ui;
}
void TeacherSearch::searchbtnSlot()
{
    if(ui->inputline->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","查询输入框不能为空!");
        return;
    }

    if(buttongroup->checkedId()==0)
    {
        _model->setFilter("studentnum="+ui->inputline->text());
        _model->select();
        if(_model->data(model->index(0,0)).toString().isEmpty())
        {
            QMessageBox::warning(this,"警告","用户不存在");
            ui->teachersearchview->setModel(model);
            ui->inputline->clear();
            return;
        }
        ui->teachersearchview->setModel(_model);
    }
    else if(buttongroup->checkedId()==1)
    {
        _model->setFilter( "name='"+ui->inputline->text()+"'");
        _model->select();
        if(_model->data(model->index(0,0)).toString().isEmpty())
        {
            QMessageBox::warning(this,"警告","用户不存在");
            ui->teachersearchview->setModel(model);
            ui->inputline->clear();
            return;
        }
        ui->teachersearchview->setModel(_model);
    }
    else
    {
        QMessageBox::warning(this,"警告","请选择查询方式");
    }
}
void TeacherSearch::comeTeacherManage()
{
    model->select();
    if(model->data(model->index(0,0)).toString().isEmpty())
    {
        QMessageBox::information(this,"提示","学生信息为空，请增加学生信息",QMessageBox::Yes);
        emit EmitToTeacherManageToChangeStack();
        this->hide();
        return;
    }
    ui->teachersearchview->setModel(model);
}
void TeacherSearch::returnbtnSlot()
{
    ui->inputline->clear();
    emit EmitToTeacherManage();
    this->hide();
}
void TeacherSearch::inputeditSlot(QString)
{
    if(ui->inputline->text().isEmpty())
    {
        ui->teachersearchview->setModel(model);
    }
}
void TeacherSearch::buttongroupSlot(int)
{
    ui->teachersearchview->setModel(model);
    ui->inputline->clear();
}
