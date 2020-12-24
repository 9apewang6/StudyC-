/********************************************************************************
** Form generated from reading UI file 'MITACTServer.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MITACTSERVER_H
#define UI_MITACTSERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MITACTServerClass
{
public:
    QGridLayout *gridLayout;
    QPushButton *pb_OpenCommunication;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QPushButton *pb_GetDevice;
    QSpinBox *spinBox;
    QHBoxLayout *horizontalLayout_3;
    QSpinBox *spinBox_3;
    QLineEdit *lineEdit_3;
    QPushButton *pb_GetCpuType;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QSpinBox *spinBox_2;
    QPushButton *pb_SetDevice;
    QPushButton *pb_CloseCommunication;

    void setupUi(QWidget *MITACTServerClass)
    {
        if (MITACTServerClass->objectName().isEmpty())
            MITACTServerClass->setObjectName(QStringLiteral("MITACTServerClass"));
        MITACTServerClass->resize(965, 544);
        gridLayout = new QGridLayout(MITACTServerClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pb_OpenCommunication = new QPushButton(MITACTServerClass);
        pb_OpenCommunication->setObjectName(QStringLiteral("pb_OpenCommunication"));

        gridLayout->addWidget(pb_OpenCommunication, 0, 0, 1, 1);

        label = new QLabel(MITACTServerClass);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(MITACTServerClass);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        lineEdit = new QLineEdit(MITACTServerClass);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        pb_GetDevice = new QPushButton(MITACTServerClass);
        pb_GetDevice->setObjectName(QStringLiteral("pb_GetDevice"));

        horizontalLayout->addWidget(pb_GetDevice);

        spinBox = new QSpinBox(MITACTServerClass);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setMinimumSize(QSize(150, 0));
        spinBox->setMaximum(65535);

        horizontalLayout->addWidget(spinBox);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        spinBox_3 = new QSpinBox(MITACTServerClass);
        spinBox_3->setObjectName(QStringLiteral("spinBox_3"));
        spinBox_3->setMinimumSize(QSize(150, 0));
        spinBox_3->setMaximum(1000000);

        horizontalLayout_3->addWidget(spinBox_3);

        lineEdit_3 = new QLineEdit(MITACTServerClass);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        horizontalLayout_3->addWidget(lineEdit_3);

        pb_GetCpuType = new QPushButton(MITACTServerClass);
        pb_GetCpuType->setObjectName(QStringLiteral("pb_GetCpuType"));

        horizontalLayout_3->addWidget(pb_GetCpuType);


        gridLayout->addLayout(horizontalLayout_3, 1, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_3 = new QLabel(MITACTServerClass);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3);

        lineEdit_2 = new QLineEdit(MITACTServerClass);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        horizontalLayout_2->addWidget(lineEdit_2);

        spinBox_2 = new QSpinBox(MITACTServerClass);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setMinimumSize(QSize(150, 0));
        spinBox_2->setMaximum(65535);

        horizontalLayout_2->addWidget(spinBox_2);

        pb_SetDevice = new QPushButton(MITACTServerClass);
        pb_SetDevice->setObjectName(QStringLiteral("pb_SetDevice"));

        horizontalLayout_2->addWidget(pb_SetDevice);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        pb_CloseCommunication = new QPushButton(MITACTServerClass);
        pb_CloseCommunication->setObjectName(QStringLiteral("pb_CloseCommunication"));

        gridLayout->addWidget(pb_CloseCommunication, 3, 0, 1, 1);


        retranslateUi(MITACTServerClass);

        QMetaObject::connectSlotsByName(MITACTServerClass);
    } // setupUi

    void retranslateUi(QWidget *MITACTServerClass)
    {
        MITACTServerClass->setWindowTitle(QApplication::translate("MITACTServerClass", "MITACTServer", Q_NULLPTR));
        pb_OpenCommunication->setText(QApplication::translate("MITACTServerClass", "OpenConmmunication", Q_NULLPTR));
        label->setText(QString());
        label_2->setText(QApplication::translate("MITACTServerClass", "Device", Q_NULLPTR));
        pb_GetDevice->setText(QApplication::translate("MITACTServerClass", "GetDevice", Q_NULLPTR));
        pb_GetCpuType->setText(QApplication::translate("MITACTServerClass", "GetCpuType", Q_NULLPTR));
        label_3->setText(QApplication::translate("MITACTServerClass", "Device", Q_NULLPTR));
        pb_SetDevice->setText(QApplication::translate("MITACTServerClass", "SetDevice", Q_NULLPTR));
        pb_CloseCommunication->setText(QApplication::translate("MITACTServerClass", "CloseCommunication", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MITACTServerClass: public Ui_MITACTServerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MITACTSERVER_H
