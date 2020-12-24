
// �ļ�����:barcode-lib.h
// �汾��Ϣ:2011-4-13 10:11:59 By 88911562@qq.com
// ��ϵ����:88911562@qq.com
******************************************/

/******************************************	
// ʹ��˵��
// pdf417α����_____________________________________________:
//***********************************************************
// int w=0,h=0,left,top;
// PDF417PARAM pdf417param = {0};
// HDC tmpHdc = NULL;
// pdf417param.options = PDF417_INVERT_BITMAP|PDF417_USE_ERROR_LEVEL;
// pdf417param.errorLevel = 2;
// pdf417param.outBits = NULL;
// pdf417param.lenBits = 0;
// pdf417param.error = 0;
// pdf417param.lenText = -1;
// pdf417param.text = "hello";
// pdf417param.yHeight = 3;
// pdf417param.aspectRatio = 0.5;
// // hdc����null,ָ��ÿ�����ֿ�͸ߵ����طֱ�Ϊ1��3.
// // w,h����pdf417ͼ�����Ҫ�Ŀ�ȸ߶�.
// if ( 0!=z_pdf417::PDF417DrawImg(NULL,&pdf417param,w,h,1,3) )
// {
// 	return ;
// }
// if (  0==w || 0==h )
// {
// 	return;
// }
// 	// ....
// 	// ����λͼ,���Ϊw,�߶�Ϊh
// 	// ....

// if ( 0==z_pdf417::PDF417DrawImg(tmpHdc,&pdf417param,left,top,1,3) )
// {
// // �ɹ�������ͼ��
// }
// pdf417α����_____________________________________________//

// ----------------------------------------------------------

// qrcodeα����_____________________________________________:
//***********************************************************
// int w=0,h=0,left,top;
// HDC tmpHdc = NULL;
// QRCODEPARAM qrcodeparam = {0};
// qrcodeparam.nLevel = QR_LEVEL_M;
// qrcodeparam.nVersion = 3;
// qrcodeparam.bAutoExtent = true;
// qrcodeparam.nMaskingNo = -1;
// qrcodeparam.lpsSource = "hello";
// // hdc����null,ָ��ÿ�����ֵĸ߶ȿ�ȶ�Ϊ3
// // left��top����qr_codeͼ����Ҫ�ĸ߶ȺͿ��(w=h)
// if ( 0!=z_qrcode::QRCODEDrawImg(NULL,&qrcodeparam,w,h,3) )
// {
// return;
// }
// 	if ( 0==w || 0==h )
// 	{
// 		return;
// 	}
// // ....
// // ����λͼ,���Ϊw,�߶�Ϊh
// // ....
// if ( 0!=z_qrcode::QRCODEDrawImg(tmpHdc,&qrcodeparam,w,h,3) )
// {
// //�ɹ�������qr_codeͼ��
// }
// qrcodeα����_____________________________________________//

******************************************/


#ifndef  barcode_lib_h
#define  barcode_lib_h


#if defined(_WIN32_WINNT ) && (_WIN32_WINNT <0x0400)
	#undef _WIN32_WINNT
	#define _WIN32_WINNT  0x0500
#elif !defined(_WIN32_WINNT)
	#define _WIN32_WINNT  0x0500
#endif


#include <windows.h>
#pragma comment(lib,"gdi32.lib")

namespace z_pdf417
{
	#define PDF417_USE_ASPECT_RATIO			0	//- use aspectRatio to set the y/x dimension. Also uses yHeight
	#define PDF417_FIXED_RECTANGLE			1	//- make the barcode dimensions at least codeColumns by codeRows
	#define PDF417_FIXED_COLUMNS			2	//- make the barcode dimensions at least codeColumns
	#define PDF417_FIXED_ROWS				4	//- make the barcode dimensions at least codeRows
	#define PDF417_AUTO_ERROR_LEVEL			0	//- automatic error level depending on text size
	#define PDF417_USE_ERROR_LEVEL			16	// - the error level is errorLevel. The used errorLevel may be different
	#define PDF417_USE_RAW_CODEWORDS		64	//- use codewords instead of text
	#define PDF417_INVERT_BITMAP			128	//- invert the resulting bitmap	
	// pdf417������Ϣ
	enum PDF417_ERROR{
		PDF417_ERROR_SUCCESS		= 0,
		PDF417_ERROR_TEXT_TOO_BIG	= 1,
		PDF417_ERROR_INVALID_PARAMS = 2,
	};

	typedef struct _PDF417PARAM 
	{
		char *outBits;      // ͼ������
		int lenBits;        // outBits�ĳ���
		int bitColumns;     // ͼ���ÿ1�е�bitλ��
		int codeRows;       // ͼ�������
		int codeColumns;    // ���������
		int codewords[928]; // the code words may be input. Is always output
		int lenCodewords;   // ���ֳ���
		int errorLevel;     // ����ȼ�0-8
		char *text;         // �����ı�
		int lenText;        // �����ı��ĳ��ȡ�����-1,�Զ���ȡ����
		int options;        // ��������
		float aspectRatio;  // y/x �ı�ֵ
		float yHeight;      // the y/x dot ratio
		int error;          // ���ش�����Ϣ
	} PDF417PARAM, *PPDF417PARAM;
	// ���ش�����Ϣ,PDF417_ERROR_SUCCESS��ʾ�ɹ�.
	// hdc��NULLʱ,left,top�ֱ𷵻���Ҫ��λͼ��Ⱥ͸߶�
	HRESULT PDF417DrawImg(HDC hdc,PPDF417PARAM pPDF417Param,int &left,
		int &top,int code_x=1,int code_y=3);
}

namespace z_qrcode
{
	// ����ȼ�
	#define QR_LEVEL_L	0
	#define QR_LEVEL_M	1
	#define QR_LEVEL_Q	2
	#define QR_LEVEL_H	3
	// qr_codeͼ����ؿհ�
	#define QR_MARGIN	0

	typedef struct _QRCODEPARAM
	{
		int		nLevel;			// ����ȼ�
		int		nVersion;		// qrcode�汾 0 - 40
		BOOL	bAutoExtent;	// ����Ϊ true
		int		nMaskingNo;		// ����Ϊ -1
		LPSTR	lpsSource;		// ������ַ���
		//int		ncSource;	// 0
	}QRCODEPARAM,*PQRCODEPARAM;

	// �������� 0 ��ʾ�ɹ�.
	// hdc��NULLʱ,left,top�ֱ𷵻���Ҫ��λͼ��Ⱥ͸߶�
	HRESULT QRCODEDrawImg(HDC hdc,PQRCODEPARAM pQrCodeeParam,
		int &left,int &top,int code_c=3);
}

namespace z_ean13
{
	#define LONG_HEIGHT			8*3	//ԭΪ8
	#define LEFT_MARGE			7*3	//ԭ5
	#define EAN13_FONT_SIZE		12*3	//ԭΪ12	

	enum EAN13CODE_ERROR
	{
		EANCode_Error_Success	= 0,
		EANCode_Error_InputData	= 1,
	};

	// ��������EANCode_Error_Success��ʾ�ɹ�
	// hdc��NULLʱ,left,top�ֱ𷵻���Ҫ��λͼ��Ⱥ͸߶� 
	HRESULT NTKOEan13DrawImg(HDC hdc,const char * enCodeStr,int &left,
		int &top,int code_x=1,int code_y=30);
}

namespace z_code_128
{
	#define MAX_Encode128Str_LEN	32		// �32λ�ַ���
	#define	MAX_Code128Bits_LEN	256		
	#define CODE128_FONT_SIZE	14*3			//ԭΪ14
	// ��������
	enum CODE128_TYPE
	{
		CODE128_TYPE_A	= 1,
		CODE128_TYPE_B	= 2,
		CODE128_TYPE_C	= 3,
		CODE128_TYPE_AUTO = 4,
	};

	enum CODE128_ERROR
	{
		CODE128_Error_Success	= 0,
		CODE128_Error_InputData	= 1,
		CODE128_Error_STRLEN	= 2,
		CODE128_Error_InvalidEncodeType = 4,
	};
	
	// ��������EANCode_Error_Success��ʾ�ɹ�
	// hdc��NULLʱ,left,top�ֱ𷵻���Ҫ��λͼ��Ⱥ͸߶� 
	HRESULT draw_image(HDC hdc,const char * enCodeStr, int &left,
		int &top,int code_x=1,int code_y=30,
		CODE128_TYPE code128Type=CODE128_TYPE_AUTO,
		bool isUseEAN128=true);
}

namespace z_code_39
{
	#define MAX_Encode39Str_LEN	24		// �32λ�ַ���
	#define	MAX_Code39Bits_LEN	335		// Ӧ��Ϊ (MAX_Encode39Str_LEN+2)*13
	#define CODE39_FONT_SIZE	14*3		//ԭΪ14
	// ��������
	enum CODE39_ERROR
	{
		CODE39_Error_Success	= 0,
		CODE39_Error_InputData	= 1,
		CODE39_Error_STRLEN		= 2,
	};
	// hdc��NULLʱ,left,top�ֱ𷵻���Ҫ��λͼ��Ⱥ͸߶� 
	HRESULT draw_image(HDC,const char * enCodeStr,int &left, int &top,
		int code_x=1,int code_y=30);

}

#endif // barcode_lib_h
