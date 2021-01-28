/********************************************************************************
** Form generated from reading UI file 'PlcDeviceManageUI.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLCDEVICEMANAGEUI_H
#define UI_PLCDEVICEMANAGEUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlcDeviceManageUIClass
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *pb_Getsegment;
    QSpinBox *spinBox_3;
    QHBoxLayout *horizontalLayout_5;
    QSpinBox *spinBox_2;
    QPushButton *pb_clearsegment;
    QHBoxLayout *horizontalLayout_4;
    QSpinBox *spinBox;
    QPushButton *pb_setwidth;
    QPushButton *pb_Init;
    QPushButton *pb_Uninit;
    QPushButton *pb_open;
    QPushButton *pb_close;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox;
    QSpinBox *spinBox_4;
    QPushButton *pb_GetDevice;
    QSpinBox *spinBox_5;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *comboBox_2;
    QSpinBox *spinBox_6;
    QPushButton *pb_SetDevice;
    QSpinBox *spinBox_7;
    QLabel *label;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *lineEdit;
    QPushButton *pb_add;
    QHBoxLayout *horizontalLayout_8;
    QLineEdit *lineEdit_3;
    QPushButton *pb_delete;

    void setupUi(QWidget *PlcDeviceManageUIClass)
    {
        if (PlcDeviceManageUIClass->objectName().isEmpty())
            PlcDeviceManageUIClass->setObjectName(QStringLiteral("PlcDeviceManageUIClass"));
        PlcDeviceManageUIClass->resize(1010, 590);
        gridLayout = new QGridLayout(PlcDeviceManageUIClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        pb_Getsegment = new QPushButton(PlcDeviceManageUIClass);
        pb_Getsegment->setObjectName(QStringLiteral("pb_Getsegment"));

        horizontalLayout_6->addWidget(pb_Getsegment);

        spinBox_3 = new QSpinBox(PlcDeviceManageUIClass);
        spinBox_3->setObjectName(QStringLiteral("spinBox_3"));
        spinBox_3->setMaximum(300000);

        horizontalLayout_6->addWidget(spinBox_3);


        gridLayout->addLayout(horizontalLayout_6, 4, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        spinBox_2 = new QSpinBox(PlcDeviceManageUIClass);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setMaximum(30000);

        horizontalLayout_5->addWidget(spinBox_2);

        pb_clearsegment = new QPushButton(PlcDeviceManageUIClass);
        pb_clearsegment->setObjectName(QStringLiteral("pb_clearsegment"));

        horizontalLayout_5->addWidget(pb_clearsegment);


        gridLayout->addLayout(horizontalLayout_5, 1, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        spinBox = new QSpinBox(PlcDeviceManageUIClass);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setMaximum(300000);

        horizontalLayout_4->addWidget(spinBox);

        pb_setwidth = new QPushButton(PlcDeviceManageUIClass);
        pb_setwidth->setObjectName(QStringLiteral("pb_setwidth"));

        horizontalLayout_4->addWidget(pb_setwidth);


        gridLayout->addLayout(horizontalLayout_4, 3, 0, 1, 1);

        pb_Init = new QPushButton(PlcDeviceManageUIClass);
        pb_Init->setObjectName(QStringLiteral("pb_Init"));

        gridLayout->addWidget(pb_Init, 0, 0, 1, 1);

        pb_Uninit = new QPushButton(PlcDeviceManageUIClass);
        pb_Uninit->setObjectName(QStringLiteral("pb_Uninit"));

        gridLayout->addWidget(pb_Uninit, 5, 0, 1, 1);

        pb_open = new QPushButton(PlcDeviceManageUIClass);
        pb_open->setObjectName(QStringLiteral("pb_open"));

        gridLayout->addWidget(pb_open, 0, 1, 1, 1);

        pb_close = new QPushButton(PlcDeviceManageUIClass);
        pb_close->setObjectName(QStringLiteral("pb_close"));

        gridLayout->addWidget(pb_close, 5, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        comboBox = new QComboBox(PlcDeviceManageUIClass);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout->addWidget(comboBox);

        spinBox_4 = new QSpinBox(PlcDeviceManageUIClass);
        spinBox_4->setObjectName(QStringLiteral("spinBox_4"));
        spinBox_4->setMaximum(3000);

        horizontalLayout->addWidget(spinBox_4);

        pb_GetDevice = new QPushButton(PlcDeviceManageUIClass);
        pb_GetDevice->setObjectName(QStringLiteral("pb_GetDevice"));

        horizontalLayout->addWidget(pb_GetDevice);

        spinBox_5 = new QSpinBox(PlcDeviceManageUIClass);
        spinBox_5->setObjectName(QStringLiteral("spinBox_5"));
        spinBox_5->setMaximum(3000);

        horizontalLayout->addWidget(spinBox_5);


        gridLayout->addLayout(horizontalLayout, 1, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        comboBox_2 = new QComboBox(PlcDeviceManageUIClass);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));

        horizontalLayout_2->addWidget(comboBox_2);

        spinBox_6 = new QSpinBox(PlcDeviceManageUIClass);
        spinBox_6->setObjectName(QStringLiteral("spinBox_6"));
        spinBox_6->setMaximum(30000);

        horizontalLayout_2->addWidget(spinBox_6);

        pb_SetDevice = new QPushButton(PlcDeviceManageUIClass);
        pb_SetDevice->setObjectName(QStringLiteral("pb_SetDevice"));

        horizontalLayout_2->addWidget(pb_SetDevice);

        spinBox_7 = new QSpinBox(PlcDeviceManageUIClass);
        spinBox_7->setObjectName(QStringLiteral("spinBox_7"));
        spinBox_7->setMaximum(30000);

        horizontalLayout_2->addWidget(spinBox_7);

        label = new QLabel(PlcDeviceManageUIClass);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);


        gridLayout->addLayout(horizontalLayout_2, 3, 1, 1, 1);

        groupBox = new QGroupBox(PlcDeviceManageUIClass);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tableWidget = new QTableWidget(groupBox);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        verticalLayout->addWidget(tableWidget);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout_3->addWidget(lineEdit);

        pb_add = new QPushButton(groupBox);
        pb_add->setObjectName(QStringLiteral("pb_add"));

        horizontalLayout_3->addWidget(pb_add);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        lineEdit_3 = new QLineEdit(groupBox);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        horizontalLayout_8->addWidget(lineEdit_3);

        pb_delete = new QPushButton(groupBox);
        pb_delete->setObjectName(QStringLiteral("pb_delete"));

        horizontalLayout_8->addWidget(pb_delete);


        verticalLayout->addLayout(horizontalLayout_8);


        gridLayout->addWidget(groupBox, 4, 1, 1, 1);


        retranslateUi(PlcDeviceManageUIClass);

        QMetaObject::connectSlotsByName(PlcDeviceManageUIClass);
    } // setupUi

    void retranslateUi(QWidget *PlcDeviceManageUIClass)
    {
        PlcDeviceManageUIClass->setWindowTitle(QApplication::translate("PlcDeviceManageUIClass", "PlcDeviceManageUI", Q_NULLPTR));
        pb_Getsegment->setText(QApplication::translate("PlcDeviceManageUIClass", "GetSegment", Q_NULLPTR));
        pb_clearsegment->setText(QApplication::translate("PlcDeviceManageUIClass", "clearSegment", Q_NULLPTR));
        pb_setwidth->setText(QApplication::translate("PlcDeviceManageUIClass", "setWidth", Q_NULLPTR));
        pb_Init->setText(QApplication::translate("PlcDeviceManageUIClass", "Init", Q_NULLPTR));
        pb_Uninit->setText(QApplication::translate("PlcDeviceManageUIClass", "Uninit", Q_NULLPTR));
        pb_open->setText(QApplication::translate("PlcDeviceManageUIClass", "Open", Q_NULLPTR));
        pb_close->setText(QApplication::translate("PlcDeviceManageUIClass", "Close", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("PlcDeviceManageUIClass", "M", Q_NULLPTR)
         << QApplication::translate("PlcDeviceManageUIClass", "D", Q_NULLPTR)
        );
        pb_GetDevice->setText(QApplication::translate("PlcDeviceManageUIClass", "GetDevice", Q_NULLPTR));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("PlcDeviceManageUIClass", "M", Q_NULLPTR)
         << QApplication::translate("PlcDeviceManageUIClass", "D", Q_NULLPTR)
        );
        pb_SetDevice->setText(QApplication::translate("PlcDeviceManageUIClass", "SetDevice", Q_NULLPTR));
        label->setText(QString());
        groupBox->setTitle(QApplication::translate("PlcDeviceManageUIClass", "\345\242\236\345\210\240", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("PlcDeviceManageUIClass", "Label", Q_NULLPTR));
        pb_add->setText(QApplication::translate("PlcDeviceManageUIClass", "add", Q_NULLPTR));
        pb_delete->setText(QApplication::translate("PlcDeviceManageUIClass", "delete", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PlcDeviceManageUIClass: public Ui_PlcDeviceManageUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLCDEVICEMANAGEUI_H
