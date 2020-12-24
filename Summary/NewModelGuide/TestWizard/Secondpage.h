#pragma once
#include <QWizardPage>
#include "ui_Secondpage.h"

class Secondpage : public QWizardPage
{
    Q_OBJECT
public:
    Secondpage(QWizardPage *parent = nullptr);
    ~Secondpage();
private:
    Ui::SecondPage ui;
}; 
