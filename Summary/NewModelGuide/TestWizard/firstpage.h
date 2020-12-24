#pragma once
#include <QWizardPage>
#include "ui_firstpage.h"

class firstpage : public QWizardPage
{
    Q_OBJECT
public:
    firstpage(QWizardPage *parent = nullptr);
    ~firstpage();
private:
    Ui::firstpage ui;
};