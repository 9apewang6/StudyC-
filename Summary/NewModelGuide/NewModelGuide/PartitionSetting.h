#ifndef _PARTITIONSETTING_H_
#define _PARTITIONSETTING_H_
#include <QWizardPage>
#include "ui_PartionSettings.h"
class PartitionSetting : public QWizardPage
{
    Q_OBJECT
public:
    PartitionSetting(QWizardPage* parent = nullptr);

    ~PartitionSetting();

    void setprojectpath(QString filepath);

private:
    Ui::PartionSetting ui;
    QString projectpath_;
};

#endif //_PARTITIONSETTING_H