/********************************************************************************
** Form generated from reading UI file 'sqlback.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SQLBACK_H
#define UI_SQLBACK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sqlbackClass
{
public:
    QPushButton *pushButton;

    void setupUi(QWidget *sqlbackClass)
    {
        if (sqlbackClass->objectName().isEmpty())
            sqlbackClass->setObjectName(QString::fromUtf8("sqlbackClass"));
        sqlbackClass->resize(600, 400);
        pushButton = new QPushButton(sqlbackClass);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(220, 170, 131, 51));

        retranslateUi(sqlbackClass);

        QMetaObject::connectSlotsByName(sqlbackClass);
    } // setupUi

    void retranslateUi(QWidget *sqlbackClass)
    {
        sqlbackClass->setWindowTitle(QApplication::translate("sqlbackClass", "sqlback", nullptr));
        pushButton->setText(QApplication::translate("sqlbackClass", "\346\201\242\345\244\215\346\225\260\346\215\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sqlbackClass: public Ui_sqlbackClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SQLBACK_H
