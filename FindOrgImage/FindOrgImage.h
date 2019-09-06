

#pragma once
#include <QtWidgets/QWidget>
#include "ui_FindOrgImage.h"
#include <sys/types.h>
#include <stdio.h>
#include <string>
#include <tchar.h>
#include <io.h>
#include <vector>
#include <iostream>
#include <QTextCodec>
#include <thread>
#include "boming_public_list.h"
#include "PathListDef.h"
#include <QDirIterator>
#include <QDateTime>
#include <windows.h>
#include "bmThreadPool.h"
#define WATER "water"
#define BLACKSPOT "blackspot"
#define FLAW "flaw"
#define INSECT "insect"
#define FOREIGN "foreign_matter"
#define ORG_PATH "org_image"
#define DEFECTPATH "defect"
#define SURFACEPATH "surface"
#define DIAPATH "dia"
#define CONPATH "convex"
#define ORG1 "left_up"
#define ORG2 "left_down"
#define ORG3  "right_up"
#define ORG4  "right_down"
using namespace std;

class FindOrgImage :public QWidget {
	Q_OBJECT
public:
	vector<string> listdir(const string &path);
	void findfile(const string &str);
//	AAData* ReadFile(const char* file);
public:
	FindOrgImage(QWidget *parent = Q_NULLPTR);
	~FindOrgImage();
private slots:
	void on_SelectDataCatalog_clicked();
	void on_SelectNoCatalog_clicked();
	void on_GetWaterOrg_clicked();
	void on_GetRealOrg_clicked();
	void on_GetForeignOrg_clicked();
	void on_GetInsectOrg_clicked();
	void on_GetBlackPotOrg_clicked();
	void on_GetAllOrg_clicked();
	void on_ListPath_clicked();
	void on_SelectFile_clicked();
private:
	QString StringToQString(std::string src);
	std::string QStringToString(QString path);
	int load_Alarm_list(QString dir_path);
	void RemoveOrgDataTask();
	void CopyImageDataTask();
	void initTask();
	void checkable();
	void MoveFileToAnotherPath(QString src,QString dst);
	void CreateCameraPath(QString Srcpath);
	int32_t createDirectory(const std::string &directoryPath);
	void DealWithAlarmImageName(QString image_name ,std::string &dst_name);
	LPCWSTR StringToLPCWStr(QString original_string);
	void ExcuteCopy(QString path);
	bool PretreatmentPath(QString filePath);
private:
	Ui::FindOrgImage ui;
	QString dataPath;
	QString cableNoPath;
	std::thread FindTask;
	std::thread CopyImageTask;
	CbmThreadPool bmCopyFile;
	bool exit_ = false;
	TSListTemp<QString > waterPath;
	TSListTemp<QString> blackPath;
	TSListTemp<QString> insectPath;
	TSListTemp<QString> FlawPath;
	TSListTemp<QString> ForeignPath;
	TSListTemp<QString> OrgpathList;
	TSListTemp<QString> DefectList;
	TSListTemp<QString> SurfaceList;
	TSListTemp<QString> DiaList;
	TSListTemp<QString> ConList;
	TSListTemp<QString > ImageList;
	TSListTemp<image_informations_ptr> trdList;
	QString image_name_;
	bool start_=false;
};