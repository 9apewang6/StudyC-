/********************************************************************************
** Form generated from reading UI file 'PartitionSettings.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARTITIONSETTINGS_H
#define UI_PARTITIONSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PartitionSetting
{
public:
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton;
    QTableWidget *tableWidget;

    void setupUi(QWidget *PartitionSetting)
    {
        if (PartitionSetting->objectName().isEmpty())
            PartitionSetting->setObjectName(QStringLiteral("PartitionSetting"));
        PartitionSetting->resize(596, 477);
        label = new QLabel(PartitionSetting);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 60, 54, 12));
        label_2 = new QLabel(PartitionSetting);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(60, 150, 54, 12));
        lineEdit = new QLineEdit(PartitionSetting);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(180, 50, 113, 20));
        lineEdit_2 = new QLineEdit(PartitionSetting);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(180, 150, 113, 20));
        pushButton = new QPushButton(PartitionSetting);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(400, 150, 75, 23));
        tableWidget = new QTableWidget(PartitionSetting);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(120, 190, 256, 192));

        retranslateUi(PartitionSetting);

        QMetaObject::connectSlotsByName(PartitionSetting);
    } // setupUi

    void retranslateUi(QWidget *PartitionSetting)
    {
        PartitionSetting->setWindowTitle(QApplication::translate("PartitionSetting", "\344\270\200\351\224\256\346\215\242\345\236\213-\345\210\206\345\214\272\350\256\276\347\275\256", Q_NULLPTR));
        label->setText(QApplication::translate("PartitionSetting", "TextLabel", Q_NULLPTR));
        label_2->setText(QApplication::translate("PartitionSetting", "TextLabel", Q_NULLPTR));
        pushButton->setText(QApplication::translate("PartitionSetting", "PushButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PartitionSetting: public Ui_PartitionSetting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARTITIONSETTINGS_H
