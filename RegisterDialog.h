#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QPalette>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QTime>
#include <QMessageBox>
#include <QButtonGroup>
namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = 0);
    ~RegisterDialog();
    void clearAll();
    void setyanzheng();
    bool judgeEmpty();
private:
    Ui::RegisterDialog *ui;
    QSqlTableModel *model;
    QButtonGroup *radiogroup;
    int yanzheng;
private slots:
    void registerbtnSlot();
    void returnbtnSlot();
    void registerbtnSetSlot(QString);
};

#endif // REGISTERDIALOG_H
