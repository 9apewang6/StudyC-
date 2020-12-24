#pragma once

#include "SysBase.h"
#include "Buffer.h"

namespace SysBase
{
	//////////////////////////////////////////////////////////////////////////
	//����

	class CBufferPoolImp;

	//////////////////////////////////////////////////////////////////////////
	//�������

	class CPBuffer : public SysBase::CObject
	{
	public:

		//////////////////////////////////////////////////////////////////////////

		enum ERROR_CODE
		{
			ERROR_CODE_SUCCESS = 0,
			ERROR_CODE_PARAM,
            ERROR_CODE_OUT_RANGE,			//д�����ݻ�������󳬳���Χ
            ERROR_CODE_INVALID,				//������Ч
		};

		//////////////////////////////////////////////////////////////////////////

		virtual ~CPBuffer();

		friend class CBufferPoolImp;

		//////////////////////////////////////////////////////////////////////////

		ERROR_CODE AddData(const void* pData, UINT32 nDataSize);

		ERROR_CODE SetData(const void* pData, UINT32 nDataSize);

		char* GetData(UINT32 nOffset = 0);

		UINT32 GetDataSize();

		ERROR_CODE SetDataSize(UINT32 nDataSize);

		UINT32 GetSize();

		void Clear();

		void Release();

	private:

        CPBuffer();

		char* m_pBuffer;

		UINT32 m_nSize;

		UINT32 m_nDataSize;

		CBufferPoolImp* m_pCBufferPoolImp;
	};

	////////////////////////////////////////////////////////////////////////////
	////CBufferPool �������������� [�̰߳�ȫ]

	class CBufferPool : public SysBase::CObject
	{
	public:

		//////////////////////////////////////////////////////////////////////////

		enum ERROR_CODE
		{
			ERROR_CODE_SUCCESS = 0,
			ERROR_CODE_PARAM,
			ERROR_CODE_SYSTEM,
		};

		//////////////////////////////////////////////////////////////////////////

		CBufferPool();

		virtual ~CBufferPool();

		ERROR_CODE Init(UINT32 nSize, UINT32 nCount);

		CPBuffer* Allocate();

		void Free(CPBuffer* pCPBuffer);

		UINT32 GetSize();

		UINT32 GetIdleCount();

		UINT32 GetCount();

	private:

		void* m_pImp;
	};

}