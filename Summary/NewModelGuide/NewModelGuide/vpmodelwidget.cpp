#include "vpmodelwidget.h"


vpmodelwidget::vpmodelwidget(QWidget *parent)
    : QWidget(parent)
{
    mLayout = new QVBoxLayout(this);
    mNameLabel = new QLabel(this);
    mPathLabel = new QLabel(this);
    mNameLabel->setStyleSheet("font: 75 12px 更纱黑体 UI SC;\n color:rgba(255,255,255,1);");
    mPathLabel->setStyleSheet("font: 75 12px 更纱黑体 UI SC;\n color:rgba(255,255,255,1);");
    mLayout->addWidget(mNameLabel);
    mLayout->addWidget(mPathLabel);
    mPathLabel->setWordWrap(true);
    mLayout->setStretch(0, 1);
    mLayout->setStretch(1, 2);
    setLayout(mLayout);
}

vpmodelwidget::~vpmodelwidget()
{
}

void vpmodelwidget::setText(QString name, QString path)
{
    mNameLabel->setText(name);
    mPathLabel->setText(path);
}

QString vpmodelwidget::path()
{
    return mPathLabel->text();
}


