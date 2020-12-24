#include "SelectModel.h"
SelectModel::SelectModel(QWizardPage* parent):QWizardPage(parent)
{
    ui.setupUi(this);
    
}

SelectModel::~SelectModel()
{

}

void SelectModel::setprojectpath(QString filepath)
{
    projectpath_ = filepath;
}

