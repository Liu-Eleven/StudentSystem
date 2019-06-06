#include "LoginDialog.h"
#include "ui_LoginDialog.h"
#include <QVBoxLayout>
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    //创建QSqlTableModel
    model=new QSqlTableModel(this);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //设置登录对话框的标题
    this->setWindowTitle("登录");
    //设置登录对话框的图标
    this->setWindowIcon(QIcon(":/student/img/book.jpg"));
    //设置登录对话框大小固定为399*252
    this->setMaximumSize(399,252);
    this->setMinimumSize(399,252);
    //设置调色板,用于设置titlelabel的颜色
    QPalette p;
    p.setColor(QPalette::WindowText,Qt::black);
    ui->titlelabel->setPalette(p);
    //设置调色板,用于设置logindialog的背景
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/student/img/loginbk1.jpg").scaled(this->size())));
    this->setPalette(palette);
    //设置三个按钮的图标
    ui->exitbtn->setIcon(QIcon(":/student/img/exit.png"));
    ui->registerbtn->setIcon(QIcon(":/student/img/log.png"));
    ui->loginbtn->setIcon(QIcon(":/student/img/Enter.png"));
    //设置groupbox，放置两个radiobutton
    radiogroup=new QButtonGroup(this);
    radiogroup->addButton(ui->studentradio,0);
    radiogroup->addButton(ui->teacherradio,1);
    //设置图片
    ui->piclabel->setPixmap(QPixmap(":/student/img/log.png").scaled(ui->piclabel->size()));
    //设置登录按钮不可用
    ui->loginbtn->setEnabled(false);
    //设置lineedit提示语句
    ui->userline->setPlaceholderText("请输入用户名");
    ui->passwordline->setPlaceholderText("请输入密码");
    //设置passlineedit显示为密码模式
    ui->passwordline->setEchoMode(QLineEdit::Password);
    //连接信号与槽
    connect(ui->loginbtn,SIGNAL(clicked()),this,SLOT(loginbtnSlot()));
    connect(ui->registerbtn,SIGNAL(clicked()),this,SLOT(registerbtnSlot()));
    connect(ui->exitbtn,SIGNAL(clicked()),this,SLOT(exitbtnSlot()));
    //设置登录按钮可用
    connect(ui->userline,SIGNAL(textChanged(QString)),this,SLOT(loginbtnSetSlot(QString)));
    connect(ui->passwordline,SIGNAL(textChanged(QString)),this,SLOT(loginbtnSetSlot(QString)));
}
LoginDialog::~LoginDialog()
{
    delete ui;
}
void LoginDialog::loginbtnSlot()
{
    if(!this->judgeEmpty())
    {
        ui->passwordline->clear();
        return;
    }
    //判断是否学生登录
    if(radiogroup->checkedId()==0)
    {
        model->setTable("student");
        model->select();
        int i;
        for(i=0;i<model->rowCount();i++)
        {
            QSqlRecord record=model->record(i);

            if(1)
            {
                QString str1="登录成功";
                QString str2=record.value(1).toString();
                QString str3="学生";
                QMessageBox::information(this,"提示",str3+str2+str1,QMessageBox::Yes);
                this->clearAll();
                //创建学生成绩管理窗口
                student=new StudentManage;
                //连接学生成绩管理窗口和登录对话框信号与槽
                connect(student,SIGNAL(toLoginDialog()),this,SLOT(showNormal()));
                student->show();
                connect(this,SIGNAL(toStudentManage(QString,QString)),student,SLOT(comeLoginDialog(QString,QString)));
                emit toStudentManage(str2,record.value(0).toString());
                this->hide();
                return;
            }
            else if(record.value(0)==ui->userline->text()&&
                    record.value(5)!=ui->passwordline->text())
           {
                QMessageBox::information(this,"提示","密码输入有误",QMessageBox::Yes);
                this->clearAll();
                return;
            }
        }
        QMessageBox::warning(this,"提示","用户不存在,请注册",QMessageBox::Yes);
        this->clearAll();
        return;
    }
    else if(radiogroup->checkedId()==1)
    {

            if(1)
            {
                QString str1="登录成功";

                QString str3="教师";
                //QMessageBox::information(this,"提示",str3+str2+str1,QMessageBox::Yes);
                //创建教师成绩管理窗口
                teacher=new TeacherManage;
                teacher->show();
                connect(this,SIGNAL(toTeacherManage(QString,QString)),teacher,SLOT(comeLoginDialog(QString,QString)));
                connect(teacher,SIGNAL(toLoginDialog()),this,SLOT(showNormal()));
                //emit toTeacherManage(str2,record.value(0).toString());
                this->clearAll();
                this->hide();
                return;
            }

    }

}
void LoginDialog::registerbtnSlot()
{
    RegisterDialog d(this);
    this->hide();
    if(d.exec()==QDialog::Accepted)
    {
        this->showNormal();
    }
    this->clearAll();
}
void LoginDialog::exitbtnSlot()
{
    this->close();
}
void LoginDialog::loginbtnSetSlot(QString)
{
    ui->loginbtn->setEnabled(true);
}
void LoginDialog::clearAll()
{
    ui->userline->clear();
    ui->passwordline->clear();
}
bool LoginDialog::judgeEmpty()
{
    if(ui->userline->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","用户名不能为空");
        return false;
    }
    if(ui->passwordline->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","密码不能为空");
        return false;
    }
    else
        return true;
}
