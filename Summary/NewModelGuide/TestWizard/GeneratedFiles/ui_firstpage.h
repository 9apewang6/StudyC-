/********************************************************************************
** Form generated from reading UI file 'firstpage.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIRSTPAGE_H
#define UI_FIRSTPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_firstpage
{
public:
    QLabel *label;

    void setupUi(QWidget *firstpage)
    {
        if (firstpage->objectName().isEmpty())
            firstpage->setObjectName(QStringLiteral("firstpage"));
        firstpage->resize(400, 300);
        firstpage->setStyleSheet(QStringLiteral("QWidget{background-color:black;color:white;}"));
        label = new QLabel(firstpage);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(100, 120, 151, 51));

        retranslateUi(firstpage);

        QMetaObject::connectSlotsByName(firstpage);
    } // setupUi

    void retranslateUi(QWidget *firstpage)
    {
        firstpage->setWindowTitle(QApplication::translate("firstpage", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("firstpage", "\347\254\254\344\270\200\351\241\265", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class firstpage: public Ui_firstpage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIRSTPAGE_H
