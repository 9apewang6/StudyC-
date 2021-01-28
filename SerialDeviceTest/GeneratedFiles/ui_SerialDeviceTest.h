/********************************************************************************
** Form generated from reading UI file 'SerialDeviceTest.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERIALDEVICETEST_H
#define UI_SERIALDEVICETEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SerialDeviceTestClass
{
public:
    QPushButton *pbConnect;
    QPushButton *pbDisconnect;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pbGetValue;
    QDoubleSpinBox *doubleSpinBox;

    void setupUi(QWidget *SerialDeviceTestClass)
    {
        if (SerialDeviceTestClass->objectName().isEmpty())
            SerialDeviceTestClass->setObjectName(QStringLiteral("SerialDeviceTestClass"));
        SerialDeviceTestClass->resize(600, 400);
        pbConnect = new QPushButton(SerialDeviceTestClass);
        pbConnect->setObjectName(QStringLiteral("pbConnect"));
        pbConnect->setGeometry(QRect(360, 50, 75, 23));
        pbDisconnect = new QPushButton(SerialDeviceTestClass);
        pbDisconnect->setObjectName(QStringLiteral("pbDisconnect"));
        pbDisconnect->setGeometry(QRect(370, 340, 75, 23));
        layoutWidget = new QWidget(SerialDeviceTestClass);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(70, 190, 441, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pbGetValue = new QPushButton(layoutWidget);
        pbGetValue->setObjectName(QStringLiteral("pbGetValue"));

        horizontalLayout->addWidget(pbGetValue);

        doubleSpinBox = new QDoubleSpinBox(layoutWidget);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));
        doubleSpinBox->setDecimals(3);
        doubleSpinBox->setMaximum(1000);

        horizontalLayout->addWidget(doubleSpinBox);


        retranslateUi(SerialDeviceTestClass);

        QMetaObject::connectSlotsByName(SerialDeviceTestClass);
    } // setupUi

    void retranslateUi(QWidget *SerialDeviceTestClass)
    {
        SerialDeviceTestClass->setWindowTitle(QApplication::translate("SerialDeviceTestClass", "SerialDeviceTest", Q_NULLPTR));
        pbConnect->setText(QApplication::translate("SerialDeviceTestClass", "Connect", Q_NULLPTR));
        pbDisconnect->setText(QApplication::translate("SerialDeviceTestClass", "DisConnect", Q_NULLPTR));
        pbGetValue->setText(QApplication::translate("SerialDeviceTestClass", "GetValue", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SerialDeviceTestClass: public Ui_SerialDeviceTestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERIALDEVICETEST_H
