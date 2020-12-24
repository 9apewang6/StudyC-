/*
	100% free public domain implementation of the HMAC-SHA1 algorithm
	by Chien-Chung, Chung (Jim Chung) <jimchung1221@gmail.com>
*/


#pragma once

#include "../SysBase_Interface.h"

namespace SysBase
{
    class CHMAC_SHA1 : public CSHA1
    {
    private:
        BYTE m_ipad[64];
        BYTE m_opad[64];

        char * szReport ;
        char * SHA1_Key ;
        char * AppendBuf1 ;
        char * AppendBuf2 ;


    public:

        enum {
            SHA1_DIGEST_LENGTH	= 20,
            SHA1_BLOCK_SIZE		= 64,
            HMAC_BUF_LEN		= 4096
        } ;

        CHMAC_SHA1()
            :szReport(new char[HMAC_BUF_LEN]),
            AppendBuf1(new char[HMAC_BUF_LEN]),
            AppendBuf2(new char[HMAC_BUF_LEN]),
            SHA1_Key(new char[HMAC_BUF_LEN])
        {}

        ~CHMAC_SHA1()
        {
            delete[] szReport ;
            delete[] AppendBuf1 ;
            delete[] AppendBuf2 ;
            delete[] SHA1_Key ;
        }

        //参数 digest 的输出长度固定为20字节，所以 digest 的 size 必须大于等于 20
        void HMAC_SHA1(BYTE *text, int text_len, BYTE *key, int key_len, BYTE *digest);
    };
}
