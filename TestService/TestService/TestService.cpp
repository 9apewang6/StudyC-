// TestService.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

int getServiceState(TCHAR* service_name)
{

	SC_HANDLE schSCManager;
	SC_HANDLE schService;
	SERVICE_STATUS_PROCESS ssStatus;
	DWORD dwOldCheckPoint;
	DWORD DwStartTickCount;
	DWORD dwWaitTime;
	DWORD dwBytesNeeded;
	schSCManager = ::OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
	if (NULL == schSCManager)
	{
		return 0;
	}
	schService = OpenService(schSCManager,/*szSvcName*/service_name, SERVICE_ALL_ACCESS | DELETE/*|SERVICE_QUERY_STATUS|SERVICE_ENUMERATE_DEPENDENTS*/);
	if (schService == NULL)
	{
		CloseServiceHandle(schSCManager);
	}
	if (!QueryServiceStatusEx(schService, SC_STATUS_PROCESS_INFO, (LPBYTE)&ssStatus, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded))
	{
		CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);
	}
	else
	{
		if (ssStatus.dwCurrentState == SERVICE_STOPPED || ssStatus.dwCurrentState == SERVICE_STOP_PENDING || ssStatus.dwCurrentState == SERVICE_PAUSED || ssStatus.dwCurrentState == SERVICE_PAUSE_PENDING)
		{
			int res = StartService(schService, 0, NULL);
			if (!res)
			{
				return 0;
			}
			return 1;
		}
		else
		{
			return 1;
		}
	}

}
int main()
{
	int i =getServiceState(__T("Mysql57"));
    return 0;
}

