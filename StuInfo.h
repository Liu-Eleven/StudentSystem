#ifndef STUINFO_H
#define STUINFO_H

#include <QWidget>
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QMessageBox>
#include <QStringList>
#include <QCompleter>
#include <QStringListModel>
namespace Ui {
class StuInfo;
}

class StuInfo : public QWidget
{
    Q_OBJECT

public:
    explicit StuInfo(QWidget *parent = 0);
    ~StuInfo();
    bool judgeEmpty();
    void clearAll();
private:
    Ui::StuInfo *ui;
    QString studentnum;
    QSqlTableModel *model;
    QStringListModel *listmodel;
    QCompleter *completer;
private slots:
    void comeStudentManage(QString);
    void canclebtnSlot();
    void confimbtnSlot();
    void emainlineSlot(QString);
signals:
    void EmitToStuManage();
};

#endif // STUINFO_H
