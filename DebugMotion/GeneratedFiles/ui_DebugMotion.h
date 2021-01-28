/********************************************************************************
** Form generated from reading UI file 'DebugMotion.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEBUGMOTION_H
#define UI_DEBUGMOTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DebugMotion
{
public:

    void setupUi(QWidget *DebugMotion)
    {
        if (DebugMotion->objectName().isEmpty())
            DebugMotion->setObjectName(QStringLiteral("DebugMotion"));
        DebugMotion->resize(1032, 679);

        retranslateUi(DebugMotion);

        QMetaObject::connectSlotsByName(DebugMotion);
    } // setupUi

    void retranslateUi(QWidget *DebugMotion)
    {
        DebugMotion->setWindowTitle(QApplication::translate("DebugMotion", "\345\244\232\350\275\264\350\277\220\345\212\250", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DebugMotion: public Ui_DebugMotion {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEBUGMOTION_H
