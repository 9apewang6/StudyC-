#pragma once

#include "SysBase.h"

namespace SysBase
{
	//////////////////////////////////////////////////////////////////////////
	//����

	class CBufferQueueImp;

	//////////////////////////////////////////////////////////////////////////
	//CBufferBase

	class CBufferBase : public SysBase::CObject
	{
	public:

		CBufferBase(){};

		virtual ~CBufferBase(){};

		friend class CBufferQueueImp;

	protected:

		char* m_pBuffer;

		UINT32 m_nSize;

		UINT32 m_nDataSize;

		CBufferQueueImp* m_pCBufferQueueImp;
	};

	//////////////////////////////////////////////////////////////////////////
	//CBufferRead

	class CBufferRead : public CBufferBase
	{
	public:

		CBufferRead();

		virtual ~CBufferRead();

		const char* GetData(UINT32 nOffset = 0);

		UINT32 GetDataSize();

		UINT32 GetSize();

		void Release();
	};

	//////////////////////////////////////////////////////////////////////////
	//CBufferWrite

	class CBufferWrite : public CBufferBase
	{
	public:

		//////////////////////////////////////////////////////////////////////////

		enum ERROR_CODE
		{
			ERROR_CODE_SUCCESS = 0,			//�ɹ�
			ERROR_CODE_PARAM,				//��������
			ERROR_CODE_OUT_RANGE,			//д�����ݻ�������󳬳���Χ
			ERROR_CODE_INVALID,				//������Ч
		};

		//////////////////////////////////////////////////////////////////////////

		CBufferWrite();

		virtual ~CBufferWrite();

		//����ѹ��Դ���У����ú�ö����ٿ��ã�
		void Push();

		//�ͷţ�Դ���л��տռ䣬������������У����ú�ö����ٿ��ã�
		void Release();

		ERROR_CODE AddData(const void* pData, UINT32 nDataSize);

		ERROR_CODE SetData(const void* pData, UINT32 nDataSize);

		char* GetData(UINT32 nOffset = 0);

		UINT32 GetDataSize();

		ERROR_CODE SetDataSize(UINT32 nDataSize);

		UINT32 GetSize();

		void Clear();
	};

	//////////////////////////////////////////////////////////////////////////

	class CBufferQueue : public SysBase::CObject
	{
	public:
		
		//////////////////////////////////////////////////////////////////////////

		enum ERROR_CODE
		{
			ERROR_CODE_SUCCESS = 0,			//�ɹ�
			ERROR_CODE_PARAM,				//��������
			ERROR_CODE_FULL,				//������
			ERROR_CODE_SYSTEM,				//ϵͳ�������⣨һ��Ϊ�ڴ�����ϵͳ�����ʼ��ʧ�ܣ�
			ERROR_CODE_NO_INIT,				//δ��ʼ��
			ERROR_CODE_EMPTY,				//���пգ�û��������
			ERROR_CODE_MORE_DATA_SIZE,		//�����ѹ������ݱ�Ŀ�껺������
		};

		//////////////////////////////////////////////////////////////////////////

		CBufferQueue();

		virtual ~CBufferQueue();

		ERROR_CODE Init(UINT32 nSize, UINT32 nCount, bool bSemaphore = false);

        void Release();

		ERROR_CODE GetBufferWrite(CBufferWrite& aCBufferWrite);

		ERROR_CODE Push(CBufferWrite& aCBufferWrite);

		ERROR_CODE Push(const void* pData, UINT32 nDataSize);

		ERROR_CODE Pop(void* pBuffer, UINT32 nBufferSize, UINT32& nDataSize, UINT32 nWaitTime = 1000);

		ERROR_CODE Pop(CBufferRead& aCBufferRead, UINT32 nWaitTime = 1000);

		UINT32 GetCount();

		UINT32 GetIdleCount();

		UINT32 GetItemCount();

        void Clear();

        bool Empty();

	private:

		void* m_pImp;
	};
}
