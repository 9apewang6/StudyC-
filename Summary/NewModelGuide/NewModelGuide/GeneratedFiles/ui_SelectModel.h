/********************************************************************************
** Form generated from reading UI file 'SelectModel.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTMODEL_H
#define UI_SELECTMODEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectModel
{
public:
    QListWidget *ModelList;
    QPushButton *pbNext;

    void setupUi(QWidget *SelectModel)
    {
        if (SelectModel->objectName().isEmpty())
            SelectModel->setObjectName(QStringLiteral("SelectModel"));
        SelectModel->resize(659, 521);
        SelectModel->setStyleSheet(QLatin1String("QWidget\n"
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
        ModelList = new QListWidget(SelectModel);
        ModelList->setObjectName(QStringLiteral("ModelList"));
        ModelList->setGeometry(QRect(70, 80, 256, 341));
        pbNext = new QPushButton(SelectModel);
        pbNext->setObjectName(QStringLiteral("pbNext"));
        pbNext->setGeometry(QRect(470, 380, 101, 41));

        retranslateUi(SelectModel);

        QMetaObject::connectSlotsByName(SelectModel);
    } // setupUi

    void retranslateUi(QWidget *SelectModel)
    {
        SelectModel->setWindowTitle(QString());
        pbNext->setText(QApplication::translate("SelectModel", "\344\270\213\344\270\200\346\255\245", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SelectModel: public Ui_SelectModel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTMODEL_H
