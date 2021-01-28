/********************************************************************************
** Form generated from reading UI file 'Secondpage.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SECONDPAGE_H
#define UI_SECONDPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SecondPage
{
public:
    QLabel *label;

    void setupUi(QWidget *SecondPage)
    {
        if (SecondPage->objectName().isEmpty())
            SecondPage->setObjectName(QStringLiteral("SecondPage"));
        SecondPage->resize(400, 300);
        SecondPage->setStyleSheet(QStringLiteral("QWidget{background-color:black;color:white;}"));
        label = new QLabel(SecondPage);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(140, 100, 101, 61));

        retranslateUi(SecondPage);

        QMetaObject::connectSlotsByName(SecondPage);
    } // setupUi

    void retranslateUi(QWidget *SecondPage)
    {
        SecondPage->setWindowTitle(QApplication::translate("SecondPage", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("SecondPage", "\347\254\254\344\272\214\351\241\265", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SecondPage: public Ui_SecondPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SECONDPAGE_H
