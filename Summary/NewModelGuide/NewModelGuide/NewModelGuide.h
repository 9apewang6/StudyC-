#ifndef _NEWMODELGUIDE_H_
#define _NEWMODELGUIDE_H_
#include <iostream>
#include <QWizard>
#include "newmodelguide_global.h"
#include "CatalogWizard.h"
#include "SelectModel.h"
#include "PartitionSetting.h"

class NEWMODELGUIDE_API NewModelGuide:public QWizard
{
public:
    NewModelGuide(QWidget* parent=nullptr);
    ~NewModelGuide();

    void loadModelCfg() {};

    int addModelCfg() { return 0; };

    int cpyModelCfg() { return 0; };

    int deleteModelCfg() { return 0; };

    int guide() { return 0; };

   
private:
    void initConnect() {}; // 
    
private:
    //1. Â·¾¶Ñ¡Ôñ
    void loadCatalogDialog();
    // currentModelcfg  


private:
    CatalogWizard* catalog_ = nullptr;
    SelectModel* manageModel_ = nullptr;
    PartitionSetting* partition_ = nullptr;

};


#endif //_NEWMODELGUIDE_H_