#ifndef _CATALOGWIZARD_H_
#define _CATALOGWIZARD_H_
#include <QDialog>
#include <QMenu>
#include <QMoveEvent>
#include <QMap>

#include "ui_CatalogWizard.h"
#include "newmodelguide_global.h"
class NEWMODELGUIDE_API CatalogWizard :public QDialog
{
    Q_OBJECT
public:
    CatalogWizard(QWidget* parent=nullptr);
    ~CatalogWizard();
    QString projectPath();
private slots:
    void on_pbImport_clicked();
    void on_listProjects_itemDoubleClicked(QListWidgetItem* item);
    void contextMenuEvent(QContextMenuEvent* event);
    void onMenuTriggered(QAction* action);
    
private:
    void loadProjects();
    void initMenu();

    void appendProjectInfo(QString name, QString filepath);

    void onRemoveProject();
    void onOpenProjectDir();


    void saveMapToConfig();


    
private:
    Ui::CatalogWizard ui;
    QString mSelectedModelPath_ ;
    std::map<std::string, std::string> mProjs_;
    std::map<QString, QString> mNameToPath;

    QString mConfigSettings = "./catalogwizard.settings";


    QAction  *mRemoveAction, *mOpenProjectDir;
    QMenu mMenu;

};



#endif //_CATALOGWIZARD_H_