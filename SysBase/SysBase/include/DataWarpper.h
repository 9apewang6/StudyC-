//////////////////////////////////////////////////////////////////////////
//����:Ҷ��
//���ܣ�������ͨ��Э�鹹�������
//Э����֯�߼���
//�ܴ�С[4�ֽ�] + N * (ID[1�ֽ�] + ����[1�ֽ�] + ��С[2�ֽ�:��ʾ�����Value��Ϣ��С��
//    ������Ϊ����ʱΪCount���壬//��ʾ��������ĸ���])
//��������Э����֯��
//OBJ:ԭ���С���岻�䣬OBJ���͵�VALUE��ϢΪID���¶����һ����ϣ��븸����ID���κι�ϵ��[OBJ��VALUE�ڲ������ܴ�С]
//OBJ_ARRAY:OBJ���飬ԭ�����ݴ�С�ֶκ����Ϊ����ĸ����������С��OBJ_ARRAY���ܴ�С�ֶθ���,
//          �����Э����֯Ϊ���ܴ�С[4�ֽ�] + N * (INDEX[2�ֽڣ����������ֵ����0��ʼ] + ��С[2�ֽ�:����ֵ��С��
//          �����е�ÿ�������ֵ��С��һ����ͬ])
//
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "SysBase.h"

namespace SysBase
{
    //////////////////////////////////////////////////////////////////////////
    
    struct TDWBool
    {
        TDWBool()
        {
            btBool = 0;
        }

        bool ToBool()
        {
            return btBool == 0 ? false : true;
        }

        unsigned char btBool;   //0 Ϊ FALSE(false);��0 Ϊ TRUE(true)
    };

    struct TDWTime
    {
        TDWTime()
        {
            nTime = 0;
        }

        INT64 nTime;
    };

    //��������
    enum DW_DATA_TYPE
    {
        DW_DT_CHAR = 0,
        DW_DT_WCHAR,
        DW_DT_NULL,
        DW_DT_BOOL,
        DW_DT_INT8,
        DW_DT_UINT8,
        DW_DT_INT16,
        DW_DT_UINT16,
        DW_DT_INT32,
        DW_DT_UINT32,
        DW_DT_INT64,
        DW_DT_UINT64,
        DW_DT_TIME,
        DW_DT_FLOAT,
        DW_DT_DOUBLE,
        DW_DT_BYTE,
		DW_DT_UTF8,
        DW_DT_OBJ,
        DW_DT_OBJ_ARRAY,
    };

    //////////////////////////////////////////////////////////////////////////
    //CDWBuilder
 
    class CDWBuilder
    {
    public:

        //////////////////////////////////////////////////////////////////////////

        //������
        enum DW_ERROR
        {
            DW_ERROR_SUCCESS = 0,                      //�ɹ�
            DW_ERROR_ID_HAS_EXIST,                     //ID�Ѵ���
            DW_ERROR_DATA_OUT_OF_MAX_SIZE,             //���õ����ݲ��ܳ��������ֵ��65535��
            DW_ERROR_PARAM,                            //��������
            DW_ERROR_MEMORY_ALLOW_FAILED,              //����ϵͳ�ڴ����
            DW_ERROR_PROTOCOL,                         //Э�����
            CMD_ERROR_OUT_OF_MAX_ITEM,                 //���������Χ�����ֻ֧��256�������
        };

        //////////////////////////////////////////////////////////////////////////

        CDWBuilder(UINT32 nMaxSize = 10240);

        virtual ~CDWBuilder();

        const void* GetBuffer();

        UINT32 GetDataSize();

        UINT32 GetBufferSize();

        void Clear();

        DW_ERROR AddItem(const char* pCharStr, UINT8* pnIndex = NULL);

        DW_ERROR AddItem(const WCHAR* pWCharStr, UINT8* pnIndex = NULL);

        DW_ERROR AddItem(const char* pCharStr, UINT16 uLength, UINT8* pnIndex = NULL);

        DW_ERROR AddItem(const WCHAR* pWCharStr, UINT16 uLength, UINT8* pnIndex = NULL);

        //���NULLֵ
        DW_ERROR AddItem(UINT8* pnIndex = NULL);

        DW_ERROR AddItem(TDWBool bValue, UINT8* pnIndex = NULL);

        DW_ERROR AddItem(INT8 nValue, UINT8* pnIndex = NULL);

        DW_ERROR AddItem(UINT8 uValue, UINT8* pnIndex = NULL);

        DW_ERROR AddItem(INT16 nValue, UINT8* pnIndex = NULL);

        DW_ERROR AddItem(UINT16 uValue, UINT8* pnIndex = NULL);

        DW_ERROR AddItem(INT32 nValue, UINT8* pnIndex = NULL);

        DW_ERROR AddItem(UINT32 uValue, UINT8* pnIndex = NULL);
        
        DW_ERROR AddItem(INT64 nValue, UINT8* pnIndex = NULL);

        DW_ERROR AddItem(UINT64 uValue, UINT8* pnIndex = NULL);

        DW_ERROR AddItem(TDWTime tValue, UINT8* pnIndex = NULL);

        DW_ERROR AddItem(FLOAT fValue, UINT8* pnIndex = NULL);

        DW_ERROR AddItem(DOUBLE dbValue, UINT8* pnIndex = NULL);

        DW_ERROR AddItem(const void* pValue, UINT16 uSize, UINT8* pnIndex = NULL);

        DW_ERROR AddItem(CDWBuilder& pObjectBuilder, UINT8* pnIndex = NULL);

        DW_ERROR AddItem(CDWBuilder* pBuilderArray, UINT16 uBuilderCount, UINT8* pnIndex = NULL);

    protected:

        DW_ERROR AddItem(DW_DATA_TYPE eType, const void* pValue, unsigned short uValueSize, UINT8* pnIndex = NULL);

    private:

        UINT32 m_nDataSize;                         //��Ч���ݴ�С

        UINT32 m_nBufferSize;                       //��������С

        char m_buffer[10240];                       //Ĭ�ϻ�����

        char* m_pbigBuffer;                         //�Զ���Ĵ󻺳���

        char* m_pDestBuffer;                        //Ŀ�껺����

        UINT8 m_nItemCount;

        char* m_pWritePtr;

    };

    //////////////////////////////////////////////////////////////////////////
    //CDWParser

    class CDWParser
    {
    public:
        
        CDWParser();

        virtual ~CDWParser();

        bool Load(const void* pData, UINT32 nDataSize);

        //nIndex��ΧΪ��0 ��ʼ�� Count - 1
        const void* GetItemData(UINT8 nIndex, UINT32& nDataSize, DW_DATA_TYPE* outType = NULL);

		bool GetItemWCharData(UINT8 nIndex, UINT32& nDataSize,DW_DATA_TYPE* outType,WCHAR* szbuf,UINT32 ulCount);

        UINT32 GetDataSize();

        UINT32 GetCount();

    private:

        struct TDWItemInfo
        {
            UINT8 uType;
            UINT16 uCount;      //OBJ_ARRAY �ĸ���
            UINT32 uSize;       //��uTypeΪDW_DT_OBJ_ARRAYʱ�����ֶκ���ΪCount
            char* pData;
        };

        typedef map<UINT8, TDWItemInfo> DataMap;

        DataMap m_DataMap;

        char* m_pBufferPtr;

        UINT32 m_nDataSize;
    };

    //////////////////////////////////////////////////////////////////////////
    //CDWObjectItemParser

    class CDWObjectItemParser
    {
    public:

        CDWObjectItemParser();

        virtual ~CDWObjectItemParser();

        bool Load(const void* pData, UINT32 nDataSize);

        //nIndex��ΧΪ��0 ��ʼ�� Count - 1
        const void* GetItemData(UINT8 nIndex, UINT32& nDataSize, DW_DATA_TYPE* outType = NULL);


		bool GetItemWCharData(UINT8 nIndex, UINT32& nDataSize,DW_DATA_TYPE* outType,WCHAR* szbuf,UINT32 ulCount);

        UINT32 GetDataSize();

        UINT32 GetCount();

    private:

        struct TDWItemInfo
        {
            UINT8 uType;
            UINT16 uCount;      //OBJ_ARRAY �ĸ���
            UINT32 uSize;
            char* pData;
        };

        typedef map<UINT8, TDWItemInfo> DataMap;

        DataMap m_DataMap;

        char* m_pBufferPtr;

        UINT32 m_nDataSize;
    };

    //////////////////////////////////////////////////////////////////////////
    //CDWOjbectArrayItemParser

    class CDWOjbectArrayItemParser
    {
    public:

        CDWOjbectArrayItemParser();

        virtual ~CDWOjbectArrayItemParser();

        bool Load(const void* pData, UINT32 nDataSize);

        //nRowIndex ��ΧΪ��0 ��ʼ�� Count - 1
        //nFieldIndex(�ֶ�����) ��ΧΪ��0 ��ʼ�� Count - 1
        const void* GetItemData(UINT16 nRowIndex, UINT8 nFieldIndex, UINT32& nDataSize, DW_DATA_TYPE* outType = NULL);

        UINT32 GetDataSize();

        UINT16 GetRowCount();

        UINT32 GetFieldCount(UINT16 nRowIndex);

    private:

        struct TDWItemInfo
        {
            UINT8 uType;
            UINT16 uCount;      //OBJ_ARRAY �ĸ���
            UINT32 uSize;       //��uTypeΪDW_DT_OBJ_ARRAYʱ�����ֶκ���ΪCount
            char* pData;
        };

        typedef map<UINT8, TDWItemInfo> DataMap;

        typedef vector<DataMap> RowMap;

        RowMap m_RowArray;

        char* m_pBufferPtr;

        UINT32 m_nDataSize;
    };
}