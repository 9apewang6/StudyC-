#pragma once

#include "SysBase.h"

namespace SysBase
{
    //////////////////////////////////////////////////////////////////////////
    //CBuffer ������������

    class CBuffer : public CObject
    {
    public:

		//////////////////////////////////////////////////////////////////////////

		enum ERROR_CODE
		{
			ERROR_CODE_SUCCESS = 0,
			ERROR_CODE_PARAM,
		};

		//////////////////////////////////////////////////////////////////////////

        //����:���캯��(Ĭ�Ͽ�ʹ�û�������С���ڻ�������С)
        //����:
        //      UINT32 nSize IN ��������С
        CBuffer(UINT32 nSize);

        virtual ~CBuffer();

        //����:��ȡ������������С
        //����ֵ: ��������С
        UINT32 GetSize();

		UINT32 GetDataSize();

		ERROR_CODE SetDataSize(UINT32 nDataSize);

        //����:��ȡ������ָ����ַ
        //����:
        //      UINT32 nOffset IN ��Ի������׵�ַ��ƫ����
        //����ֵ: ������ָ����ַ
        char* GetData(UINT32 nOffset = 0);

		//����:������л�������������Ϣ[������ԭ���ڴ�ռ��С]
		void ClearData();

    protected:

		UINT32 m_nDataSize;		//��Ч���ݴ�С

        UINT32 m_nSize;			//��������С

        char* m_pBuffer;		//�������׵�ַ
    };
}
