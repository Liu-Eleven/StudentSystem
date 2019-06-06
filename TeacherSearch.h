#ifndef TEACHERSEARCH_H
#define TEACHERSEARCH_H

#include <QWidget>
#include <QSqlTableModel>
#include <QDebug>
#include <QStringList>
#include <QMessageBox>
#include <QButtonGroup>
namespace Ui {
class TeacherSearch;
}

class TeacherSearch : public QWidget
{
    Q_OBJECT

public:
    explicit TeacherSearch(QWidget *parent = 0);
    ~TeacherSearch();

private:
    Ui::TeacherSearch *ui;
    QSqlTableModel *model,*_model;
    QButtonGroup *buttongroup;
private slots:
    void searchbtnSlot();
    void comeTeacherManage();
    void returnbtnSlot();
    void inputeditSlot(QString);
    void buttongroupSlot(int);
signals:
    void EmitToTeacherManage();
    void EmitToTeacherManageToChangeStack();
};

#endif // TEACHERSEARCH_H
