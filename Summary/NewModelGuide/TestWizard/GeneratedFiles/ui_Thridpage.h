/********************************************************************************
** Form generated from reading UI file 'Thridpage.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_THRIDPAGE_H
#define UI_THRIDPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_thirdpage
{
public:
    QLabel *label;

    void setupUi(QWidget *thirdpage)
    {
        if (thirdpage->objectName().isEmpty())
            thirdpage->setObjectName(QStringLiteral("thirdpage"));
        thirdpage->resize(400, 300);
        thirdpage->setStyleSheet(QStringLiteral("QWidget{background-color:black;color:white;}"));
        label = new QLabel(thirdpage);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(140, 120, 81, 51));

        retranslateUi(thirdpage);

        QMetaObject::connectSlotsByName(thirdpage);
    } // setupUi

    void retranslateUi(QWidget *thirdpage)
    {
        thirdpage->setWindowTitle(QApplication::translate("thirdpage", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("thirdpage", "\347\254\254\344\270\211\351\241\265", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class thirdpage: public Ui_thirdpage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_THRIDPAGE_H
