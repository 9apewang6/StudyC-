// LoadIni.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
LPCWSTR  stringToLPCWSTR(string original)
{
	size_t origsize = original.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t* wcstring = (wchar_t*)malloc(sizeof(wchar_t)*(original.length() - 1));
	mbstowcs_s(&convertedChars, wcstring, origsize, original.c_str(), _TRUNCATE);
	return wcstring;
}

int main()
{

	
	CString SName;
	LPCTSTR  appName = _T("cable_information");
	LPCTSTR  keyName = __T("cable_type1");
//	LPSTR Temp =(LPSTR)new char(40);
	LPSTR Temp = (LPSTR)malloc(sizeof(LPSTR)*(40));
	DWORD size;
	size = 256;
	DWORD ret;
	ret = GetPrivateProfileStringW(appName,keyName,__T(""),SName.GetBuffer(256),size,__T("./cable_information.ini"));
	ret = GetPrivateProfileStringA("cable_information","cable_type","",Temp,size,"./cable_information.ini");
	string cableno = Temp;
	string cable_type(CW2A(SName.GetString()));
	ret = WritePrivateProfileString(appName,keyName,__T("test02"),__T("./cable_information.ini"));
	LPCTSTR  temp;
	temp = stringToLPCWSTR(cable_type);
	return 0;
}

