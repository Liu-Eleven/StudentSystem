#-------------------------------------------------
#
# Project created by QtCreator 2015-12-08T18:02:44
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StudentSystem
TEMPLATE = app


SOURCES += main.cpp\
        LoginDialog.cpp \
    RegisterDialog.cpp \
    StudentManage.cpp \
    StuPassWord.cpp \
    StuInfo.cpp \
    StuInfoSearch.cpp \
    StudentSocre.cpp \
    TeacherManage.cpp \
    TeaPassWord.cpp \
    TeacherSearch.cpp \
    TeacherChangeScore.cpp \
    TeacherInsert.cpp \
    TeacherDelete.cpp

HEADERS  += LoginDialog.h \
    RegisterDialog.h \
    StudentManage.h \
    StuPassWord.h \
    StuInfo.h \
    StuInfoSearch.h \
    StudentSocre.h \
    TeacherManage.h \
    TeaPassWord.h \
    TeacherSearch.h \
    TeacherChangeScore.h \
    TeacherInsert.h \
    TeacherDelete.h

FORMS    += LoginDialog.ui \
    RegisterDialog.ui \
    StudentManage.ui \
    StuPassWord.ui \
    StuInfo.ui \
    StuInfoSearch.ui \
    StudentSocre.ui \
    TeacherManage.ui \
    TeaPassWord.ui \
    TeacherSearch.ui \
    TeacherChangeScore.ui \
    TeacherInsert.ui \
    TeacherDelete.ui

RESOURCES += \
    studentimg.qrc
RC_FILE = logo.rc
