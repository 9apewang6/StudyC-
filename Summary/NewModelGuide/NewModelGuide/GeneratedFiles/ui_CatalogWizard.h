/********************************************************************************
** Form generated from reading UI file 'CatalogWizard.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CATALOGWIZARD_H
#define UI_CATALOGWIZARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CatalogWizard
{
public:
    QHBoxLayout *horizontalLayout;
    QListWidget *listProjects;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbImport;

    void setupUi(QDialog *CatalogWizard)
    {
        if (CatalogWizard->objectName().isEmpty())
            CatalogWizard->setObjectName(QStringLiteral("CatalogWizard"));
        CatalogWizard->resize(857, 668);
        CatalogWizard->setStyleSheet(QLatin1String("QDialog\n"
"{\n"
"background-color:rgba(128,128,128,1);\n"
"}"));
        horizontalLayout = new QHBoxLayout(CatalogWizard);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        listProjects = new QListWidget(CatalogWizard);
        listProjects->setObjectName(QStringLiteral("listProjects"));

        horizontalLayout->addWidget(listProjects);

        widget = new QWidget(CatalogWizard);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 571, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(4, 37));
        label_4->setMaximumSize(QSize(4, 37));
        label_4->setStyleSheet(QLatin1String("#label_4\n"
"{\n"
"	background:rgba(255,255,255,1);\n"
"}"));

        horizontalLayout_2->addWidget(label_4);

        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(200, 30));
        label->setMaximumSize(QSize(200, 30));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\233\264\347\272\261\351\273\221\344\275\223 UI SC"));
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("\n"
"\n"
"\n"
"	font: 22px \"\346\233\264\347\272\261\351\273\221\344\275\223 UI SC\";\n"
"	font-weight:400;\n"
"	color:rgba(255,255,255,1);\n"
"\n"
""));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pbImport = new QPushButton(widget);
        pbImport->setObjectName(QStringLiteral("pbImport"));
        pbImport->setMinimumSize(QSize(50, 50));
        pbImport->setMaximumSize(QSize(50, 50));
        pbImport->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"border-image: url(:/NewModelGuide/Resources/\346\211\223\345\274\200normal.png);\n"
"}\n"
"QPushButton:hover\n"
"{\n"
"border-image: url(:/NewModelGuide/Resources/\346\211\223\345\274\200hover.png);\n"
"}\n"
"QPushButton:pressed\n"
"{\n"
"border-image: url(:/NewModelGuide/Resources/\346\211\223\345\274\200selected.png);\n"
"}"));

        horizontalLayout_2->addWidget(pbImport);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout->addWidget(widget);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 2);

        retranslateUi(CatalogWizard);

        QMetaObject::connectSlotsByName(CatalogWizard);
    } // setupUi

    void retranslateUi(QDialog *CatalogWizard)
    {
        CatalogWizard->setWindowTitle(QApplication::translate("CatalogWizard", "\345\267\245\347\250\213\350\267\257\345\276\204\351\200\211\346\213\251", Q_NULLPTR));
        label_4->setText(QString());
        label->setText(QApplication::translate("CatalogWizard", "\346\211\223\345\274\200\346\234\200\350\277\221\347\232\204\345\267\245\347\250\213\350\267\257\345\276\204", Q_NULLPTR));
        pbImport->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CatalogWizard: public Ui_CatalogWizard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CATALOGWIZARD_H
