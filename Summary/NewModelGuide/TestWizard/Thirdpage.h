#pragma once
#include <QWizardPage>
#include "ui_Thridpage.h"

class Thirdpage : public QWizardPage
{
    Q_OBJECT
public:
    Thirdpage(QWizardPage *parent = nullptr);
    ~Thirdpage();
private:
    Ui::thirdpage ui;
};
