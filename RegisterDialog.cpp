#include "RegisterDialog.h"
#include "ui_RegisterDialog.h"

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    //设置对话框的大小
    this->setMaximumSize(232,320);
    this->setMinimumSize(232,320);
    //创建model,进行数据库操作
    model=new QSqlTableModel(this);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //设置注册对话框的背景
    QPalette p;
    p.setBrush(QPalette::Background,QBrush(QPixmap(":/student/img/loginbk1.jpg").scaled(this->size())));
    this->setPalette(p);
    //设置注册对话框的标题颜色
    QPalette p1;
    p1.setColor(QPalette::WindowText,Qt::black);
    ui->titlelabel->setPalette(p1);
    //设置注册对话框标题
    this->setWindowTitle("注册用户");
    //设置两个按钮的图案
    ui->registerbtn->setIcon(QIcon(":/student/img/Enter.png"));
    ui->returnbtn->setIcon(QIcon(":/student/img/exit.png"));
    //设置两行密码lineedit的显示
    ui->passwordline->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    ui->passwordline1->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    //设置lineedit提示语句
    ui->userline->setPlaceholderText("请输入用户名");
    ui->studentnumline->setPlaceholderText("请输入工作号");
    ui->passwordline->setPlaceholderText("请输入密码");
    ui->passwordline1->setPlaceholderText("请重新输入密码");
    ui->yanzhengline->setPlaceholderText("请输入验证码");
    //设置注册按钮不可用
    ui->registerbtn->setEnabled(false);
    //两个按钮的信号与槽的连接
    connect(ui->registerbtn,SIGNAL(clicked()),this,SLOT(registerbtnSlot()));
    connect(ui->returnbtn,SIGNAL(clicked()),this,SLOT(returnbtnSlot()));
    //设置验证码
    QTime t;
    t= QTime::currentTime();
    qsrand(t.msec()+t.second()*1000);
    this->setyanzheng();
    //设置QButtonGroup
    radiogroup=new QButtonGroup(this);
    radiogroup->addButton(ui->stduentradio,0);
    radiogroup->addButton(ui->teacherradio,1);
    //lineedit与槽连接
    connect(ui->userline,SIGNAL(textChanged(QString)),this,SLOT(registerbtnSetSlot(QString)));
    connect(ui->passwordline,SIGNAL(textChanged(QString)),this,SLOT(registerbtnSetSlot(QString)));
    connect(ui->studentnumline,SIGNAL(textChanged(QString)),this,SLOT(registerbtnSetSlot(QString)));
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}
void RegisterDialog::registerbtnSlot()
{
    int i;
    //判断lineedit是否为空
    if(!this->judgeEmpty())
    {
        ui->passwordline->clear();
        ui->passwordline1->clear();
        ui->yanzhengline->clear();
        return;
    }
    //判断两次密码输入是否一致
    if(ui->passwordline->text()!=ui->passwordline1->text())
    {
        QMessageBox::warning(this,"警告","两次密码输入不一致",QMessageBox::Yes);
        ui->passwordline->clear();
        ui->passwordline1->clear();
        ui->yanzhengline->clear();
        this->setyanzheng();
        return;
    }
    //判断验证码输入是否正确
    if(ui->yanzhenglabel->text()!=ui->yanzhengline->text())
    {
        QMessageBox::warning(this,"警告","验证码输入错误",QMessageBox::Yes);
        ui->passwordline->clear();
        ui->passwordline1->clear();
        ui->yanzhengline->clear();
        this->setyanzheng();
        return;
    }
     //判断是否学生注册
    if(radiogroup->checkedId()==0)
    {
        //设置table为student表
        model->setTable("student");
        model->select();
        for(i=0;i<model->rowCount();i++)
        {
            QSqlRecord record=model->record(i);
            //判断学生信息已经存在
             if((record.value(0)==ui->studentnumline->text()&&record.value(5)!=""))
            {
                QMessageBox::warning(this,"警告","用户已存在",QMessageBox::Yes);
                this->clearAll();
                this->setyanzheng();
                return;
            }
        }
        //如果学生信息不存在,添加学生信息进数据库
        if(i==model->rowCount())
        {
            QSqlRecord record1=model->record();
            record1.setValue("studentnum",ui->studentnumline->text());
            record1.setValue("name",ui->userline->text());
            record1.setValue("password",ui->passwordline->text());
            model->insertRecord(-1,record1);
        }
        //判断学生信息是否上传数据库成功
        if(model->submitAll())
        {
            QMessageBox::information(this,"提示","恭喜你注册成功^*^",QMessageBox::Yes);
            this->accept();
        }
        //上传不成功
        else
        QMessageBox::information(this,"提示","注册失败请重新注册",QMessageBox::Yes);
        this->clearAll();
        this->setyanzheng();
    }
    //判断是否老师注册
    else if(radiogroup->checkedId()==1)
    {
        int i;
        model->setTable("teacher");
        model->select();
        for(i=0;i<model->rowCount();i++)
        {
            QSqlRecord record=model->record(i);
            if(record.value(0)==ui->studentnumline->text())
            {
                QMessageBox::warning(this,"警告","用户已存在",QMessageBox::Yes);
                this->clearAll();
                this->setyanzheng();
                return;
            }
        }
        if(i==model->rowCount())
        {
            QSqlRecord record=model->record();
            record.setValue("teachernum",ui->studentnumline->text());
            record.setValue("name",ui->userline->text());
            record.setValue("password",ui->passwordline->text());
            model->insertRecord(-1,record);
        }
        //判断教师信息是否上传数据库成功
        if(model->submitAll())
        {
            QMessageBox::information(this,"提示","恭喜你注册成功^*^",QMessageBox::Yes);
             this->accept();
        }
        //上传不成功
        else
        QMessageBox::information(this,"提示","注册失败请重新注册",QMessageBox::Yes);
        this->clearAll();
        this->setyanzheng();
    }
    else
        QMessageBox::warning(this,"警告","请选择注册方式",QMessageBox::Yes);

}

void RegisterDialog::returnbtnSlot()
{
    this->accept();
}
void RegisterDialog::registerbtnSetSlot(QString)
{
    ui->registerbtn->setEnabled(true);
}
//清空lineedit的上的文本
void RegisterDialog::clearAll()
{
    ui->userline->clear();
    ui->passwordline->clear();
    ui->passwordline1->clear();
    ui->studentnumline->clear();
    ui->yanzhengline->clear();
}
//设置验证码
void RegisterDialog::setyanzheng()
{
    QPalette p1;
    p1.setColor(QPalette::WindowText,Qt::red);
    yanzheng=qrand()%10000;
    while(yanzheng<1000)
        yanzheng=qrand()%10000;
    ui->yanzhenglabel->setText(QString::number(yanzheng));
    ui->yanzhenglabel->setPalette(p1);
}
//判断lineedit是否为空
bool RegisterDialog::judgeEmpty()
{
    if(ui->userline->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","用户名不能为空");
        return false;
    }
    else if(ui->studentnumline->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","用户工作号不能为空");
        return false;
    }
    else if(ui->passwordline->text().isEmpty()||
            ui->passwordline1->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","用户密码不能为空");
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


