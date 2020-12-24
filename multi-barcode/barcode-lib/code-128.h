#ifndef _code_128__
#define _code_128__

#include "barcode-lib.h"
using namespace z_code_128;
// Code128����˵��
// A ��:
// 0-63  ��ʾASC�� 32-95���ַ� 
// 64-95 ��ʾASC��  0-31���ַ�

// B ��:
// 0-95	 ��ʾASC�� 32-127���ַ�

// C ��:
// 0-99  ��ʾ 00-99 ������
// ����c�������EAN128��ô�� StartC|FUC1 �����Code128 ֻ��StartC
#define IS_NOMARL_CHAR(c)		( (int)(c)>31 && (int)(c)<96 )	// 
#define IS_NUMBER(c)			( (int)(c)>47 && (int)(c)<58 )	// 
#define IS_CONTROL_SIGN(c)		( (int)(c)>=0 && (int)(c)<32 )	//
#define CANUSE_CODE128TYPE_A(c)	( (int)(c)>=0 && (int)(c)<96 )
#define CANUSE_CODE128TYPE_B(c)	( (int)(c)>31 && (int)(c)<128 )
#define CANUSE_CODE128TYPE_C(c) ( IS_NUMBER((c)[0]) && IS_NUMBER((c)[1]) && IS_NUMBER((c)[2]) && IS_NUMBER((c)[3]) )
// ���ֽڷ���codeBits���ӵĳ���, ���ֽڷ���enCodeStr�б�����ĳ���
DWORD PrintCODE128Code_A(char * codeBits,const char * enCodeStr,CODE128_ERROR * code128_Err,int &weight,int &checkCode,bool isFix);
DWORD PrintCODE128Code_B(char * codeBits,const char * enCodeStr,CODE128_ERROR * code128_Err,int &weight,int &checkCode,bool isFix);
DWORD PrintCODE128Code_C(char * codeBits,const char * enCodeStr,CODE128_ERROR * code128_Err,int &weight,int &checkCode,bool isFix,bool isUseEAN128);

DWORD StartCode128CodeType(char * codeBits,CODE128_TYPE code128Type,int &checkCode,CODE128_ERROR * retError=NULL);
DWORD EnterCode128CodeType(char * codeBits,CODE128_TYPE code128Type,CODE128_TYPE enterType,int &weight,int &checkCode,CODE128_ERROR * retError=NULL);

#endif // _code_128__
