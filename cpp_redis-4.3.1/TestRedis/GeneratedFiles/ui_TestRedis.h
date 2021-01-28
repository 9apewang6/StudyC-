/********************************************************************************
** Form generated from reading UI file 'TestRedis.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTREDIS_H
#define UI_TESTREDIS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TestRedisClass
{
public:

    void setupUi(QWidget *TestRedisClass)
    {
        if (TestRedisClass->objectName().isEmpty())
            TestRedisClass->setObjectName(QStringLiteral("TestRedisClass"));
        TestRedisClass->resize(600, 400);

        retranslateUi(TestRedisClass);

        QMetaObject::connectSlotsByName(TestRedisClass);
    } // setupUi

    void retranslateUi(QWidget *TestRedisClass)
    {
        TestRedisClass->setWindowTitle(QApplication::translate("TestRedisClass", "TestRedis", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TestRedisClass: public Ui_TestRedisClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTREDIS_H
