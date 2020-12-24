#include <QMessageBox>
#include "NewModelGuide.h"
NewModelGuide::NewModelGuide(QWidget*parent):QWizard(parent),manageModel_(new SelectModel),partition_(new PartitionSetting)
{
    std::cout << " NewModelGuide::NewModelGuide" << std::endl;
   /* loadCatalogDialog();*/
    setPage(0, manageModel_);
    setPage(1, partition_);

    setWizardStyle(QWizard::ModernStyle);
    setWindowTitle("Qt wizard");

    QPixmap pix(QSize(500, 78));
    pix.fill(QColor(173, 173, 173));
    setPixmap(QWizard::BannerPixmap, pix);


    setTitleFormat(Qt::RichText);
    //设置子标题显示格式
    setSubTitleFormat(Qt::RichText);
    setButtonText(QWizard::NextButton, QStringLiteral("<下一步>"));
    setButtonText(QWizard::BackButton, QStringLiteral("<上一步"));
}
NewModelGuide::~NewModelGuide()
{
    if (catalog_)
    {
        delete catalog_;
        catalog_ = nullptr;
        std::cout << "delete Catalog" << std::endl;
    }
    if (manageModel_)
    {
        delete manageModel_;
        manageModel_ = nullptr;
        std::cout << "delete SelectModel" << std::endl;

    }
    if (partition_)
    {
        delete partition_;
        partition_ = nullptr;
        std::cout << "delete Partition" << std::endl;

    }
    std::cout << "NewModelGuide::~NewModelGuide" << std::endl;
}

void NewModelGuide::loadCatalogDialog()
{
    catalog_ = new CatalogWizard();
    if (QDialog::Accepted == catalog_->exec())
    {
        manageModel_ = new SelectModel();
        std::cout << "Create Select Model" << std::endl;
        manageModel_->setprojectpath(catalog_->projectPath());
        manageModel_->show();   
    }
    else
    {
        QMessageBox::warning(nullptr, QStringLiteral("VisionPlatform"), QString("%1:%2").arg(QStringLiteral("无法打开文件")).arg(catalog_->projectPath()));
        std::cout << " select file failed" << std::endl;
        return;
    }
 
}

extern "C" NEWMODELGUIDE_API QWidget* createNewModelGuideWidget()
{
    NewModelGuide* guide = new NewModelGuide();
    return (QWidget*)(guide);
}
