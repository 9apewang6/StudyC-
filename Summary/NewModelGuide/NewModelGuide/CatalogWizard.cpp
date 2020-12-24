#include <QFile>
#include <QFileDialog>
#include <QDesktopServices>
#include <QMessageBox>
#include "CatalogWizard.h"
#include "vpmodelwidget.h"
#define PRJName Qt::UserRole+1
CatalogWizard::CatalogWizard(QWidget* parent/* =nullptr */) :QDialog(parent),mSelectedModelPath_("")
{
    ui.setupUi(this);


    initMenu();

    ui.listProjects->setContentsMargins(0, 0, 0, 10);
    ui.listProjects->setSpacing(2);
    loadProjects();
    connect(&mMenu, SIGNAL(triggered(QAction*)), this, SLOT(onMenuTriggered(QAction*)));
}
CatalogWizard::~CatalogWizard()
{
    mProjs_.clear();
}

QString CatalogWizard::projectPath()
{
    return mSelectedModelPath_;
}

void CatalogWizard::on_pbImport_clicked()
{
    QString projectName;
    QString projectPath;
    projectPath = QFileDialog::getOpenFileName(this, tr("save path"), "./", "*.vpprj");
    QStringList nameandsuffix = projectPath.split(".");
    if (nameandsuffix.size() == 2)
    {
        projectName = nameandsuffix[0];
    }
    else
    {
        QMessageBox::information(this,"warning",QStringLiteral("路径选择错误!!"));
        return;
    }

    QFile f(mConfigSettings);
    if (f.exists() && f.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        std::string prjName, fileName;
        prjName = projectName.toLocal8Bit();
        fileName = projectPath.toLocal8Bit();
        QFile prjFile(QString::fromStdString(fileName));
        if (prjFile.exists())
        {
            QString prjCfg = QString("%1 = %2\n").arg(QString::fromStdString(prjName)).arg(QString::fromStdString(fileName));
            mNameToPath[QString::fromStdString(prjName)] = QString::fromStdString(fileName);
            mProjs_[prjName] = prjCfg.toStdString();//存map
            f.write(prjCfg.toLocal8Bit());

            QListWidgetItem* item = new QListWidgetItem(ui.listProjects, 0);
            item->setSizeHint(QSize(100, 100));
            item->setData(PRJName, prjName.c_str());
            vpmodelwidget* w = new vpmodelwidget(ui.listProjects);
            w->setText(QString::fromStdString(prjName), QString::fromStdString(fileName));
            ui.listProjects->setItemWidget(item, w);

        }
        f.close();
    }
}

void CatalogWizard::on_listProjects_itemDoubleClicked(QListWidgetItem* item)
{
    vpmodelwidget* w = dynamic_cast<vpmodelwidget*>(ui.listProjects->itemWidget(item));
    if (w)
    {
        mSelectedModelPath_ = w->path();
        accept();
    }
}

void CatalogWizard::contextMenuEvent(QContextMenuEvent* event)
{
    QListWidgetItem* curItem = ui.listProjects->currentItem();
    if (curItem)
    {
        // 		if (curItem->)
        // 		{
        // 		}
        //把鼠标位置转化成相对于QWidget的位置，然后判断是否在QListWidget内.
        QPoint i = ui.listProjects->mapFromGlobal(event->globalPos());
        QRect rect(QPoint(0, 0), ui.listProjects->size());
        if (rect.contains(i))
        {
            mMenu.exec(QCursor::pos());
        }
    }
}

void CatalogWizard::onMenuTriggered(QAction* action)
{
    if (action == mRemoveAction)
    {
        onRemoveProject();
    }
    else if (action == mOpenProjectDir)
    {
        onOpenProjectDir();
    }
}

void CatalogWizard::loadProjects()
{
    QFile file(mConfigSettings);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while (!file.atEnd())
        {
            QByteArray baLine = file.readLine();
            QString qstrLine(QString::fromLocal8Bit(baLine));
            QStringList strlstLine = qstrLine.split('=');
            if (2 == strlstLine.size())
            {
                QString name = strlstLine[0].trimmed();
                QString path = strlstLine[1].trimmed();
                mNameToPath[name] = path;
                // 				mProjects[name] = path;
                mProjs_[name.toStdString()] = qstrLine.toLocal8Bit();//存map

                QListWidgetItem* item = new QListWidgetItem(ui.listProjects, 0);
                item->setSizeHint(QSize(100, 100));
                item->setData(PRJName, name.toLocal8Bit());
                vpmodelwidget* w = new vpmodelwidget(ui.listProjects);
                w->setText(name, path);
                ui.listProjects->setItemWidget(item, w);
            }
        }
        file.close();
    }
}

void CatalogWizard::initMenu()
{
    mRemoveAction = new QAction(QStringLiteral("从列表移除"), this);
    mOpenProjectDir = new QAction(QStringLiteral("打开工程文件所在文件夹"), this);
    mMenu.addAction(mRemoveAction);
    mMenu.addAction(mOpenProjectDir);
}

void CatalogWizard::appendProjectInfo(QString name, QString filepath)
{
    QFile f(mConfigSettings);
    if (f.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        f.write(QString("%1 = %2\n").arg(name).arg(filepath).toLocal8Bit());
        if (!QFile::exists(filepath))
        {
            QFile prjFile(filepath);
            if (prjFile.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QString content = "device = dev.json\nworkflow = workflow.xml\nui = ui.xml\nrtdb = rt.db";
                prjFile.write(content.toLocal8Bit());
                prjFile.close();
            }
        }
        f.close();
    }
}

void CatalogWizard::onRemoveProject()
{
    QListWidgetItem* curItem = ui.listProjects->currentItem();
    std::map<std::string, std::string>::iterator iter;
    if (!curItem) { return; }
    QString qstrNamestr = curItem->data(PRJName).toString();
    std::string nameStr = qstrNamestr.toStdString();

    for (iter = mProjs_.begin(); iter != mProjs_.end(); )
    {
        if (iter->first == nameStr)
        {
            // 
            // 			QString pth = mNameToPath[iter->first.c_str()];
            // 			QFile prjFile(pth);
            // 			if (prjFile.exists())
            // 			{
            // 				prjFile.remove();
            // 			}

            mProjs_.erase(iter);
            break;
        }
        else
        {
            iter++;
        }
    }
    std::map<QString, QString>::iterator  qIter;
    for (qIter = mNameToPath.begin(); qIter != mNameToPath.end();)
    {

        // 			std::string strK = qIter.key().toStdString();
        if (qIter->first == QString::fromLocal8Bit(nameStr.c_str()))
        {
            mNameToPath.erase(qIter);
            break;
        }
        else
        {
            qIter++;
        }
    }
    ui.listProjects->removeItemWidget(curItem);
    delete curItem;
    saveMapToConfig();
}

void CatalogWizard::onOpenProjectDir()
{
    QListWidgetItem* curItem = ui.listProjects->currentItem();
    if (!curItem) { return; }
    std::string nameStr = curItem->data(PRJName).toString().toStdString();
    for (auto iter = mProjs_.begin(); iter != mProjs_.end(); ++iter)
    {
        if (iter->first == nameStr)
        {
            QString pth = mNameToPath[iter->first.c_str()];
            QFile prjFile(pth);
            if (prjFile.exists())
            {
                QString curPrjPath;
                int pos1 = pth.lastIndexOf("\\");
                int pos2 = pth.lastIndexOf("/");
                if (pos1 < pos2)
                {
                    curPrjPath = pth.left(pos2);
                }
                else
                {
                    curPrjPath = pth.left(pos1);
                }
                QDesktopServices::openUrl(QUrl::fromLocalFile(curPrjPath));
            }
            else
            {
                QMessageBox box;
                box.setText(QStringLiteral("工程文件不存在"));
                box.exec();
            }
            break;
        }

    }
}

void CatalogWizard::saveMapToConfig()
{
    std::string writeStr = "";
    std::map<std::string, std::string>::iterator iter;
    for (iter = mProjs_.begin(); iter != mProjs_.end(); iter++)
    {
        writeStr = writeStr + iter->second;
    }
    QFile f(mConfigSettings);
    f.resize(0);
    if (f.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        f.write(writeStr.c_str());
        f.close();
    }
}


