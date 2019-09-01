#include "sqlback.h"
#include <QMessageBox>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <QFileDialog>
#include <string>
using namespace std;
sqlback::sqlback(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}
void sqlback::on_pushButton_clicked()
{
	QString file = QFileDialog::getOpenFileName(this, QStringLiteral("��־�ļ�����"), ".", QStringLiteral("��־�ļ�(*.txt)"));
	if (!file.isEmpty())
	{

		string targetPath = file.toStdString();
		string destPath = "./sql.txt";

		ifstream srcFile(targetPath.c_str()); //���ı�ģʽ��in.txt����
		if (!srcFile) { //��ʧ��
			cout << "error opening source file." << endl;
			return;
		}
		ofstream destFile(destPath); //���ı�ģʽ��out.txt��д
		if (!destFile) { //��ʧ��
			cout << "error opening source file." << endl;
			srcFile.close();
			return;
		}

		const int LINE_LENGTH = 20480;
		char str[LINE_LENGTH] = { 0x00 };
		char out[LINE_LENGTH] = { 0x00 };
		while (srcFile.getline(str, LINE_LENGTH))
		{
			std::string s(str);
			string value;
			int index_start = s.find("insert into");
			
			int index_end = s.find(";");
			if (index_start != -1)
			{

				value = s.substr(index_start, index_end - index_start);
			}
			else {
				index_start = s.find("INSERT INTO");
				if (index_start != -1)
				{
					value = s.substr(index_start, index_end - index_start);
				}
			}
			destFile << value.c_str()<<';'<< endl;
			memset(str, 0x00, LINE_LENGTH);
			memset(out, 0x00, LINE_LENGTH);
		}

		srcFile.close();
		destFile.close();
	}

	QMessageBox *box = new QMessageBox;
	box->setWindowTitle(QStringLiteral("��ʾ"));
	box->setText(QStringLiteral("�������"));
	box->exec();//box->show();������
}