#pragma once

#include "SysBase.h"

namespace SysBase
{
    struct TSqlServerInstanceInfo 
    {
        TSqlServerInstanceInfo()
        {
            nTcpPort = 0;
            nTcpDynamicPort = 0;
            nLanguageCode = 0;
        }

        string strName;             //ʵ������
        string strVersion;          //�汾��Ϣ������������Ϣ��
        string strEdition;          //�汾���ͣ���ҵ�棬�����棬��׼�棩
        string strCollation;        //�������
        string strSQLBinRoot;       //��ʵ�������г���Ŀ¼
        string strSQLDataRoot;      //��ʵ��������Ŀ¼
        string strSQLPath;          //��ʵ����Ŀ¼
        string strSqlProgramDir;    //��װ���ݿ��Ŀ¼������

        UINT32 nLanguageCode;       //���Ա���

        UINT16 nTcpPort;            //TCP�����˿�
        UINT16 nTcpDynamicPort;     //TCP��̬�����˿�

    };

    class CSqlServerHelper
    {
    public:

        static bool GetDBInstanceInfoList(list<TSqlServerInstanceInfo>& aSqlServerInstanceInfoList);

    private:

        CSqlServerHelper();

        virtual ~CSqlServerHelper();
    };
}
