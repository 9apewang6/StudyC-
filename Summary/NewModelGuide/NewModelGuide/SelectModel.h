#ifndef _SELECTMODEL_H_
#define _SELECTMODEL_H_
#include <QWizardPage>
#include "ui_SelectModel.h"

class SelectModel :public QWizardPage
{
    Q_OBJECT
public:
    SelectModel(QWizardPage *parent = nullptr);
    ~SelectModel();
    void setprojectpath(QString filepath);// modelconfig . 

private:
    Ui::SelectModel ui;
    QString projectpath_;
};

#endif //_SELECTMODEL_H_