/********************************************************************************
** Form generated from reading UI file 'TestWizard.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTWIZARD_H
#define UI_TESTWIZARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TestWizardClass
{
public:

    void setupUi(QWidget *TestWizardClass)
    {
        if (TestWizardClass->objectName().isEmpty())
            TestWizardClass->setObjectName(QStringLiteral("TestWizardClass"));
        TestWizardClass->resize(600, 400);

        retranslateUi(TestWizardClass);

        QMetaObject::connectSlotsByName(TestWizardClass);
    } // setupUi

    void retranslateUi(QWidget *TestWizardClass)
    {
        TestWizardClass->setWindowTitle(QApplication::translate("TestWizardClass", "TestWizard", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TestWizardClass: public Ui_TestWizardClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTWIZARD_H
