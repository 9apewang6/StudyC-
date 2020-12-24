#pragma once

#include <QWizard>
#include <QtWidgets/QWidget>
#include "ui_TestWizard.h"

#include "firstpage.h"
#include  "Secondpage.h"
#include "Thirdpage.h"

class TestWizard : public QWizard
{
    Q_OBJECT

public:
    enum
    {
        Page_First,
        Page_second,
        Page_third
    };
    TestWizard(QWidget *parent = Q_NULLPTR);

private:
    firstpage *m_fir=nullptr;
    Secondpage *m_sec=nullptr;
    Thirdpage *m_thi=nullptr;

};
