/********************************************************************************
** Form generated from reading UI file 'NewModelGuide.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWMODELGUIDE_H
#define UI_NEWMODELGUIDE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewModelGuide
{
public:
    QListWidget *listWidget;
    QPushButton *pushButton;

    void setupUi(QWidget *NewModelGuide)
    {
        if (NewModelGuide->objectName().isEmpty())
            NewModelGuide->setObjectName(QStringLiteral("NewModelGuide"));
        NewModelGuide->resize(718, 637);
        NewModelGuide->setStyleSheet(QLatin1String("QWidget\n"
"{\n"
"backgroudn-color:white;\n"
"color:black;\n"
"}\n"
"\n"
"QPushButton\n"
"{\n"
"	font:15px \"Microsoft yahei\";\n"
"	background-color:black;\n"
"	color:green;\n"
"}\n"
""));
        listWidget = new QListWidget(NewModelGuide);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(50, 80, 331, 391));
        pushButton = new QPushButton(NewModelGuide);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(510, 540, 121, 51));

        retranslateUi(NewModelGuide);

        QMetaObject::connectSlotsByName(NewModelGuide);
    } // setupUi

    void retranslateUi(QWidget *NewModelGuide)
    {
        NewModelGuide->setWindowTitle(QApplication::translate("NewModelGuide", "\346\226\260\345\273\272\346\265\201\346\260\264\345\220\221\345\257\274", Q_NULLPTR));
        pushButton->setText(QApplication::translate("NewModelGuide", "\344\270\213\344\270\200\346\255\245", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class NewModelGuide: public Ui_NewModelGuide {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWMODELGUIDE_H
