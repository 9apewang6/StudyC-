#include "FindOrgImage.h"
#include "qfiledialog.h"
#include <direct.h>
#include <fstream>
#include <QMessageBox>
#ifdef WIN32
#define ACCESS(fileName,accessMode) _access(fileName,accessMode)
#define MKDIR(path) _mkdir(path)
#else
#define ACCESS(fileName,accessMode) access(fileName,accessMode)
#define MKDIR(path) mkdir(path,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)
#endif
vector<string> res;
vector<string> FindOrgImage::listdir(const string &path) {
	string dir = path;

	vector<string> s;

	_finddatai64_t fileDir;

	_int64 lfDir = 0;



	if ((lfDir = _findfirsti64(dir.c_str(), &fileDir)) == -1l)

		printf("No file is found\n");

	else {

		do {
			string str(fileDir.name);

			if (str.size() >= 3)

				s.push_back(str);

		} while (_findnexti64(lfDir, &fileDir) == 0);

	}

	_findclose(lfDir);

	return s;

}
void FindOrgImage::findfile(const string & str)
{
	string s = str;

	vector<string> tmp = FindOrgImage::listdir(s + "\\*");
	
	for (int i = 0; i < tmp.size(); i++)

	{
		string temp = s + "\\" + tmp[i];
		 if (tmp[i] == WATER)
		{
			QString path = StringToQString(temp);
			CreateCameraPath(path);
			waterPath.push_back(path);
		//	ui.textBrowser->setText(path);
		}
		else if (tmp[i] == INSECT)
		{
			QString path = StringToQString(temp);
			CreateCameraPath(path);
			insectPath.push_back(path);
			ui.textBrowser->setText(path);
		}
		else if (tmp[i] == FLAW)
		{
			QString path = StringToQString(temp);
			CreateCameraPath(path);
			FlawPath.push_back(path);
		//	ui.textBrowser->setText(path);
		}
		else if (tmp[i] == FOREIGN)
		{
			QString path = StringToQString(temp);
			CreateCameraPath(path);
			ForeignPath.push_back(path);
			//ui.textBrowser->setText(path);
		}
		else if (tmp[i] == BLACKSPOT)
		{
			QString path = StringToQString(temp);
			CreateCameraPath(path);
			blackPath.push_back(path);
		//	ui.textBrowser->setText(path);
		}
		findfile(temp);

	}
	printf("load path over \n");
}
FindOrgImage::FindOrgImage(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initTask();
}

FindOrgImage::~FindOrgImage()
{
	exit_ = true;
	if (FindTask.joinable())
	{
		FindTask.join();
	}
	if (CopyImageTask.joinable())
	{
		CopyImageTask.join();
	}
}

void FindOrgImage::on_SelectDataCatalog_clicked()
{
	QFileDialog *dialog = new QFileDialog(this);
	dialog->setFileMode(QFileDialog::DirectoryOnly);

	//QString file = dialog->getExistingDirectory(this,tr("Open Directory"),"/home",QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
	QString file = dialog->getExistingDirectory();
	file.replace("/", "\\");
	ui.le_alarm->setText(file);
	dataPath = file;
	//ui.textBrowser->append(dataPath);
}

void FindOrgImage::on_SelectNoCatalog_clicked()
{
	QFileDialog *dialog = new QFileDialog(this);
	//dialog->setNameFilter(tr("Images(*.png *.jpg *.jpeg *.bmp)"));

	dialog->setFileMode(QFileDialog::DirectoryOnly);
	//QString file = dialog->getExistingDirectory(this,tr("Open Directory"),"/home",QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
	QString file = dialog->getExistingDirectory();
	file.replace("/", "\\");
	ui.le_No->setText(file);
	cableNoPath = file;
}

void FindOrgImage::on_GetWaterOrg_clicked()
{
	QString src, dst;
	MoveFileToAnotherPath(src,dst);
}

void FindOrgImage::on_GetRealOrg_clicked()
{

}

void FindOrgImage::on_GetForeignOrg_clicked()
{

}

void FindOrgImage::on_GetInsectOrg_clicked()
{

}

void FindOrgImage::on_GetBlackPotOrg_clicked()
{

}

void FindOrgImage::on_GetAllOrg_clicked()
{
	ui.ListPath->setEnabled(true);
}
void FindOrgImage::checkable() {
	if (!ui.CableNo->isChecked() && !ui.AllAlarm->isChecked()) {
		ui.GetAllOrg->setEnabled(false);
	}
	if (ui.CableNo->isChecked()) {
		ui.GetAllOrg->setEnabled(true);
	}
	if (ui.AllAlarm->isChecked()) {
		ui.GetAllOrg->setEnabled(true);
	}
	if (ui.CableNo->isChecked() && ui.AllAlarm->isChecked()) {
		ui.GetAllOrg->setEnabled(false);
	}
}
LPCWSTR FindOrgImage::StringToLPCWStr(QString original_string)
{
	size_t origsize = original_string.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t* wcstring = (wchar_t*)malloc(sizeof(wchar_t)*(origsize));
	mbstowcs_s(&convertedChars, wcstring, origsize, original_string.toStdString().c_str(), _TRUNCATE);
	return wcstring;
}

void FindOrgImage::ExcuteCopy(QString path)
{

	WinExec(path.toStdString().c_str(), SW_HIDE);
}

bool FindOrgImage::PretreatmentPath(QString filePath)
{
	int index = filePath.lastIndexOf('\\');
	QString Flag;
	Flag = filePath.right(filePath.length() - index - 1);
	if (Flag == WATER)
	{
		waterPath.push_back(filePath);
		return false;
	}
	else if (Flag == INSECT)
	{
		insectPath.push_back(filePath);
		return false;
	}
	else if (Flag == FLAW)
	{
		FlawPath.push_back(filePath);
		return false;
	}
	else if (Flag == BLACKSPOT)
	{
		blackPath.push_back(filePath);
		return false;
	}
	else if (Flag == FOREIGN)
	{
		ForeignPath.push_back(filePath);
		return false;
	}
	return true;
}

void FindOrgImage::MoveFileToAnotherPath(QString src, QString dst)
{
	
	if (!start_)
	{
		return;
	}
	QString Head = "cmd /c copy";
	//CopyFile(StringToLPCWStr(src), StringToLPCWStr(dst), true);//false代表覆盖，true不覆
	src.replace('/', '\\');
	dst.replace('/', '\\');
	Head = Head + "  " + src + "  " + dst;
	ImageList.push_back(Head);
	//LPCSTR c_str = StringToLPCWStr(Head);
	//ui.textBrowser->setText(Head);
	
	//WinExec(_T("cmd /c copy D:\\BOMMING\\Cableaoi\\CableAOI\\QCableAOISoftware\\x64\\Release\\Data\\test\\2019082\\org_image\\left_down\\1028.1_1.jpg   D:\\BOMMING\\Cableaoi\\CableAOI\\QCableAOISoftware\\x64\\Release\\Data\\test\\2019082\\defect\\left_up\\1028.1_1.jpg"), SW_HIDE);
}

int32_t FindOrgImage::createDirectory(const std::string &directoryPath)
{
	QDir dir(directoryPath.c_str());
	if (dir.exists())
	{
		return true;
	}
	if (0 != ACCESS(directoryPath.c_str(), 0))
	{
		MKDIR(directoryPath.c_str());
	}
	return 0;
}

void FindOrgImage::DealWithAlarmImageName(QString image_name, std::string &dst_name)
{
	if (!start_)
	{
		return;
	}
	QStringList list_name = image_name.split('_');
	int size = list_name.size();
	QString tempName;
	QStringList tempList;
	int index;
	switch (size)
	{
	case 2:
		dst_name = image_name.toStdString();
		break;
	case 3:
		dst_name = image_name.toStdString();
		break;
	case 9:
	{
		tempList = image_name.split('_');
		tempName = tempList.at(1);
		dst_name = tempName.toStdString();
		index = dst_name.find_first_of('m');
		dst_name.insert(index - 1, "_");
		dst_name.insert(index - 2, "_");
		dst_name = dst_name.substr(0, dst_name.length() - 1);
		dst_name.append(".jpg");
	}
		break;
	case 10:
	{
		tempList = image_name.split('_');
		tempName = tempList.at(1);
		tempName.append("_");
		tempName.append(tempList.at(2));
		tempName.append(".jpg");
		dst_name = tempName.toStdString();
	}
		break;

	default:
		break;
	}
}

void FindOrgImage::CreateCameraPath(QString Srcpath)
{
	QString LeftUpPath;
	QString LeftDownPath;
	QString RightUpPath;
	QString RightDownPath;
	Srcpath.append("\\");
	LeftUpPath = Srcpath;
	LeftDownPath = Srcpath;
	RightDownPath = Srcpath;
	RightUpPath = Srcpath;
	LeftUpPath.append(ORG1);
	LeftUpPath.replace('\\', '/');
	createDirectory(LeftUpPath.toStdString());
	LeftDownPath.replace('\\', '/');
	LeftDownPath.append(ORG2);
	createDirectory(LeftDownPath.toStdString());
	RightUpPath.replace('\\', '/');
	RightUpPath.append(ORG3);
	createDirectory(RightUpPath.toStdString());
	RightDownPath.replace('\\', '/');
	RightDownPath.append(ORG4);
	createDirectory(RightDownPath.toStdString());
}

void FindOrgImage::on_ListPath_clicked()
{
	ui.ListPath->setEnabled(false);
	if (dataPath.size()>0)
	{
		start_ = true;
		string path = QStringToString(dataPath);
		if (!PretreatmentPath(dataPath))
		{
			return;
		}
		findfile(path);
	
	}
	else
	{
		QMessageBox *box = new QMessageBox;
		box->setWindowTitle(QStringLiteral("提示"));
		box->setText(QStringLiteral("请先选择Data路径"));
		
		box->exec();//box->show();都可以
		return;
	}
}

void FindOrgImage::on_SelectFile_clicked()
{
	ui.ListPath->setEnabled(true);
	start_ = false;
	return;
	QFileDialog *dialog = new QFileDialog(this);
	dialog->setNameFilter(tr("Images(*.png *.jpg *.jpeg *.bmp)"));

	dialog->setFileMode(QFileDialog::ExistingFiles);
	//QString file = dialog->getExistingDirectory(this,tr("Open Directory"),"/home",QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
	
	dialog->setViewMode(QFileDialog::Detail);
	QStringList Slist;
	if (dialog->exec())
	{
		Slist = dialog->selectedFiles();
	}
	QString names;
	std::string imageName;
	names = Slist.at(0);
	int index = names.lastIndexOf("/");
	image_name_ = names.right(names.length() - index - 1);
	DealWithAlarmImageName(image_name_,imageName);
}

QString FindOrgImage::StringToQString(std::string src)
{
	return QString::fromLocal8Bit(src.c_str());
}

std::string FindOrgImage::QStringToString(QString path)
{
	QTextCodec *codec = QTextCodec::codecForName("GB2312");
	QTextCodec::setCodecForLocale(codec);
	//string s = ui.lineEdit->text().toStdString();
	string s = codec->fromUnicode(path).data();
	return s;
}

int FindOrgImage::load_Alarm_list(QString dir_path)
{
	//ui.textBrowser->clear();
	QDirIterator it(dir_path, QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
	int index_pic = 0;
	if (it.hasNext())
	{
		while (it.hasNext()&& start_)//存在
		{
			if (exit_) return -1;

			QString filepath = it.next();
			QFileInfo info(filepath);
			QString srcFilePath,srcFilePath2,srcFilePath3,srcFilePath4;
			QString dstFilePath,dstFilePath2,dstFilePath3,dstFilePath4;
			if (info.suffix() == "jpg" || info.suffix() == "bmp")
			{
				QDateTime date_time = info.lastModified();//图片的最后修改日期

														  //解析name
				QString picName;
				std::string image_name;
				QString path, flag,path2,flag2;
				int index = filepath.lastIndexOf(QRegExp("/"));
				picName = filepath.right(filepath.length() - index - 1);
				path = filepath.left(index);

				index = path.lastIndexOf(QRegExp("/"));
				flag = path.right(path.length() - index - 1);
				index = path.lastIndexOf("/");

				DealWithAlarmImageName(picName, image_name);
				if (flag == SURFACEPATH|| flag == DIAPATH||
					flag == CONPATH|| flag == WATER|| flag == BLACKSPOT||
					flag == FLAW|| flag == INSECT|| flag == FOREIGN||flag==DEFECTPATH
					)
				{
					path2 = path.left(index);
					while (flag2 != DEFECTPATH&&flag!=DEFECTPATH)
					{
					
						index = path2.lastIndexOf("/");
						flag2 = path2.right(path2.length() - index - 1);
					
						path2 = path2.left(index);
						if (flag2 == DEFECTPATH||flag==DEFECTPATH)
						{
							break;
						}	
					}
					path2.append("/");
					path2.append(ORG_PATH);
					path2.append("/");
					srcFilePath = path2;
					srcFilePath2 = path2;
					srcFilePath3 = path2;
					srcFilePath4 = path2;
					srcFilePath.append(ORG1);
					srcFilePath.append("/");
					srcFilePath.append(StringToQString(image_name));
					srcFilePath2.append(ORG2);
					srcFilePath2.append("/");
					srcFilePath2.append(StringToQString(image_name));
					srcFilePath3.append(ORG3);
					srcFilePath3.append("/");
					srcFilePath3.append(StringToQString(image_name));
					srcFilePath4.append(ORG4);
					srcFilePath4.append("/");
					srcFilePath4.append(StringToQString(image_name));

				//	srcFilePath = path.replace()
					path.append("/");
					dstFilePath = path;
					dstFilePath2 = path;
					dstFilePath3 = path;
					dstFilePath4 = path;
					dstFilePath.append(ORG1);
					dstFilePath.append("/");
					dstFilePath.append(StringToQString(image_name));
					dstFilePath2.append(ORG2);
					dstFilePath2.append("/");
					dstFilePath2.append(StringToQString(image_name));
					dstFilePath3.append(ORG3);
					dstFilePath3.append("/");
					dstFilePath3.append(StringToQString(image_name));
					dstFilePath4.append(ORG4);
					dstFilePath4.append("/");
					dstFilePath4.append(StringToQString(image_name));
					MoveFileToAnotherPath(srcFilePath, dstFilePath);
					MoveFileToAnotherPath(srcFilePath2, dstFilePath2);
					MoveFileToAnotherPath(srcFilePath3, dstFilePath3);
					MoveFileToAnotherPath(srcFilePath4, dstFilePath4);
				}
			
				
			}
		}
		ui.textBrowser->append(dir_path);
		return 0;
	}
	else
	{
		return -1;
	}
}

void FindOrgImage::RemoveOrgDataTask()
{
	while (!exit_)
	{
		/*if (DefectList.size() > 0)
		{
			QString defectpath;
			DefectList.pop_back(defectpath);

			load_Alarm_list(defectpath);
		}
		if (SurfaceList.size() > 0)
		{
			QString defectpath;
			SurfaceList.pop_back(defectpath);
			load_Alarm_list(defectpath);
		}
		if (DiaList.size() > 0)
		{
			QString defectpath;
			DiaList.pop_back(defectpath);
			load_Alarm_list(defectpath);
		}
		if (ConList.size() > 0)
		{
			QString defectpath;
			ConList.pop_back(defectpath);
			load_Alarm_list(defectpath);
		}*/
		if (waterPath.size() > 0)
		{
			QString defectpath;
			waterPath.pop_back(defectpath);
			load_Alarm_list(defectpath);
		}
		if (blackPath.size() > 0)
		{
			QString defectpath;
			blackPath.pop_back(defectpath);
			load_Alarm_list(defectpath);
		}
		if (insectPath.size() > 0)
		{
			QString defectpath;
			insectPath.pop_back(defectpath);
			load_Alarm_list(defectpath);
		}
		if (FlawPath.size() > 0)
		{
			QString defectpath;
			FlawPath.pop_back(defectpath);
			load_Alarm_list(defectpath);
		}
		if (ForeignPath.size() > 0)
		{
			QString defectpath;
			ForeignPath.pop_back(defectpath);
			load_Alarm_list(defectpath);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void FindOrgImage::CopyImageDataTask()
{
	while (!exit_)
	{
		if (ImageList.size() > 0)
		{
			QString temp;
			printf("ImageList.size [%d] \n",ImageList.size());
			ImageList.pop_back(temp);
			bmCopyFile.PushTask(std::bind(&FindOrgImage::ExcuteCopy,this,temp));
		//	ExcuteCopy(temp);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
}

void FindOrgImage::initTask()
{
	ui.CableNo->hide();
	ui.AllAlarm->hide();
	ui.label_2->hide();
	ui.le_No->hide();
	ui.SelectNoCatalog->hide();
	ui.groupBox->hide();
	//ui.textBrowser->hide();
	FindTask = std::thread([=]() {RemoveOrgDataTask(); });
	CopyImageTask = std::thread([=]() {CopyImageDataTask(); });

}
