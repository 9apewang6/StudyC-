#include "PartitionSetting.h"
PartitionSetting::PartitionSetting(QWizardPage* parent ) :QWizardPage(parent)
{
    ui.setupUi(this);
}

PartitionSetting::~PartitionSetting()
{

}

void PartitionSetting::setprojectpath(QString filepath)
{
    projectpath_ = filepath;
}
