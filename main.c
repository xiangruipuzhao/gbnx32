/******************************************************************************

                  版权所有 (C), 2001-2011, 国网电科院通信与用电技术分公司

 ******************************************************************************
  文 件 名   : main.c
  版 本 号   : 初稿
  作    者   : liming
  生成日期   : 2013年12月9日 星期一
  最近修改   :
  功能描述   : 国标能效3-2协议及适配层测试代码
  函数列表   :
  修改历史   :
  1.日    期   : 2013年12月9日 星期一
    作    者   : liming
    修改内容   : 创建文件

******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <stdarg.h>
#include <math.h>
#include "gbnx_32_api.h"
#include "fmprint.h"

#define TC_TEST_COLOR      // 将在Linux下以多色显示.
// #undef TC_TEST_COLOR    // windows 或无法支持颜色

#define PACK_MEM_SIZE  16384
#define OUT_BUF_LEN    16384

#define BUF_LEN_MAX   (1024*1024*50)
UINT8 g_ucPackMem[PACK_MEM_SIZE] = {0}; // 测试封装命令的参数的内存空间
UINT8 g_ucOutBuf[OUT_BUF_LEN]    = {0}; // 存放输出报文
UINT8 g_ucInBuf[OUT_BUF_LEN]     = {0};
UINT8 g_ucOutBufColor[OUT_BUF_LEN]    = {0}; // 存放输出报文

char * sGetErr(eTcErr eErr)
{
    char *pStr = NULL;
    switch(eErr)
    {
        case TC_OK:
            pStr = "TC_OK";
            break;

        case TC_ERR_NULL:
            pStr = "TC_ERR_NULL";
            break;

        case TC_ERR_OUTRNG:
            pStr = "TC_ERR_OUTRNG";
            break;

        case TC_ERR_NONE:
            pStr = "TC_ERR_NONE";
            break;

        case TC_ERR_IO:
            pStr = "TC_ERR_IO";
            break;

        case TC_ERR_RES:
            pStr = "TC_ERR_RES";
            break;

        case TC_ERR_INIT:
            pStr = "TC_ERR_INIT";
            break;

        case TC_ERR_PARA:
            pStr = "TC_ERR_PARA";
            break;

        case TC_ERR_FN:
            pStr = "TC_ERR_FN";
            break;

        case TC_ERR_PN:
            pStr = "TC_ERR_PN";
            break;

        case TC_ERR_ADDR:
            pStr = "TC_ERR_ADDR";
            break;

        case TC_ERR_CTRL:
            pStr = "TC_ERR_CTRL";
            break;

        case TC_ERR_0x10:
            pStr = "TC_ERR_0x10";
            break;

        case TC_ERR_A2CS:
            pStr = "TC_ERR_A2CS";
            break;

         case TC_ERR_AFN:
            pStr = "TC_ERR_AFN";
            break;

        case TC_ERR_UNCOMP:
            pStr = "TC_ERR_UNCOMP";
            break;

        case TC_ERR_0x68:
            pStr = "TC_ERR_0x68";
            break;

        case TC_ERR_PROTO:
            pStr = "TC_ERR_PROTO";
            break;

        case TC_ERR_CS:
            pStr = "TC_ERR_CS";
            break;

        case TC_ERR_0x16:
            pStr = "TC_ERR_0x16";
            break;

        case TC_ERR_LOGIC:
            pStr = "TC_ERR_LOGIC";
            break;

        case TC_ERR_PACK:
            pStr = "TC_ERR_PACK";
            break;

        case TC_ERR_PFC:
            pStr = "TC_ERR_PFC";
            break;

        case TC_ERR_TIMEOUT:
            pStr = "TC_ERR_TIMEOUT";
            break;

        case TC_ERR_PRM:
            pStr = "TC_ERR_PRM";
            break;

        case TC_ERR_TEAM:
            pStr = "TC_ERR_TEAM";
            break;

         default:
            pStr = "Unkown Err";
            break;
    }

    return pStr;

}
void printf_chars(UINT8 *pChar, int n)
{
    if(!pChar)
    {
        return;
    }
    int i = 0;
    for(i = 0; i < n; i++)
    {
        printf("%c", (char)pChar[i]);
    }
}
void show_main_name(char *str)
{
      #ifdef TC_TEST_COLOR
      fm_print(str, FR_GREEN|FM_UNDERLINE);
      #else
      printf(str);
      #endif
}

void show_sub_name(char * str)
{
    #ifdef TC_TEST_COLOR
    fm_print(str,FR_YELLOW|BK_NORMAL);
    #else
    printf(str);
    #endif
}

void show_item_value(char *str)
{
    #ifdef TC_TEST_COLOR
    fm_print(str,FR_WHITE|BK_MAGENTA);
    #else
    printf(str);
    #endif
}

void show_error(char *str)
{
    #ifdef TC_TEST_COLOR
    fm_print(str,FR_RED|FM_BOLD|FM_FLASH);
    #else
    printf(str);
    #endif
}

void printf_buffer_color(char * pBuf, UINT16 usBufLen)
{
    memset(g_ucOutBufColor, 0,PACK_MEM_SIZE);

    if(!pBuf)
    {
       show_error("error print_buffer pointer null!\n");
        return;
    }

    int Len = 0;
    int i = 0;
    Len = (int)usBufLen;
    char *pColorBuf = NULL;
    pColorBuf = (char*)g_ucOutBufColor;

    #ifdef TC_TEST_COLOR
    fm_print("pack length is: ", FR_YELLOW|FM_BOLD);
    #else
    printf("pack length is: ");
    #endif

    char buf[10] = {0};
    sprintf(buf,"%d", Len);

    #ifdef TC_TEST_COLOR
    fm_print(buf,FR_RED|BK_NORMAL|FM_BOLD);
    #else
    printf(buf);
    #endif
    printf("\n\n");
    
    if(Len != 0)
    {
        for(i = 0; i < Len; i++)
        {
            memset(buf, 0,10);
   
            sprintf(pColorBuf,"%02X", (UINT8)pBuf[i]);
            pColorBuf += 2;

            if(i != Len - 1)
            {
                sprintf(pColorBuf," ");
                pColorBuf += 1;
            }
        }     
    }

    #ifdef TC_TEST_COLOR
    fm_print((char*)g_ucOutBufColor,  FR_WHITE|BK_MAGENTA|FM_BOLD);
    #else
    printf(buf);
    #endif
    
    printf("\n\n\n");
}

// 测试例函数类型
typedef eTcErr (*pTestFunc)(BOOL bActive);

typedef struct
{
    int       nTestCmd;  // 命令的对应的十六进制数
    pTestFunc pTestM2S;  // 下行的测试例
    pTestFunc pTestS2M;  // 上行的测试例

}sTestPack;




/*****************************************************************************
 函 数 名  : test_afn00f1_m2s
 功能描述  : 封装测试例 全部确认或否认
 测试命令  : TCMD_AFN_0_F1_ALL_OK_DENY

 输入参数  : BOOL bActive 是否为主动性

 输出参数  :
 返 回 值  : eTcErr
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月7日 星期二
    作    者   : liming
    修改内容   : 新生成函数
*****************************************************************************/
eTcErr test_afn00f1_c2t(BOOL bActive)
{   
    /*1 声明参数 */
    eTcErr     eRet        = TC_OK;
    UINT16     usBuflen    = 0;
    UINT8      *pMemPack   = NULL;
    sTcPackCon    *psPack     = NULL;
    sTcInit    sInit;
 
    pMemPack = (UINT8*)malloc(TC_USER_MAX);
    if(!pMemPack)
    {      
        return TC_ERR_IO;
    }
   
    psPack = (sTcPackCon*)pMemPack;

    /* 2 环境初始化 */
    sInit.eRole = TC_ROLE_CONTOR;
    sInit.ucPermitDelayMinutes = 255;
    eRet = eTcInit(&sInit);
    if(eRet != TC_OK)
    {
        printf("初始化失败\n");
        free(pMemPack);
        return eRet;
    }
    
    /* 3 封装参数 */
    psPack->sAddress.ucConAddress = 123;
    psPack->sAddress.bTeam        = FALSE;
    psPack->sAddress.ulTmlAddress = 123456789;
    memcpy(psPack->sAddress.acRegionCode, "110000", TC_REGN_LEN);
    psPack->ucPSEQ = 1;
 
    memcpy(psPack->aPw, "1234567890ABCDEF", TC_PW_LEN);

    psPack->usNum = 1;
    psPack->sData[0].eCmd         = TCMD_AFN_0_F1_ALL_OK_DENY;
    psPack->sData[0].usPN         = 0;
    psPack->sData[0].bApp         = TRUE;

    psPack->sData[0].uApp.eResCode  = TC_RES_NONE;
    
    
    /* 4 调用函数 */
    eRet = etcPackCon(psPack, (UINT8*)g_ucOutBuf, &usBuflen);
    if(eRet != TC_OK)
    {
        printf("emcPack() error %d\n", eRet);
        free(pMemPack);
        return eRet;
    }
    
    /* 5 输出结果 */ 
    printf_buffer_color((char*)g_ucOutBuf, usBuflen);

    return TC_OK;

}

/*****************************************************************************
 函 数 名  : test_afn00f1_t2c
 功能描述  : 封装测试例 
 测试命令  : TCMD_AFN_0_F1_ALL_OK_DENY

 输入参数  : BOOL bActive 是否为主动性

 输出参数  :
 返 回 值  : eTcErr
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月7日 星期二
    作    者   : liming
    修改内容   : 新生成函数
*****************************************************************************/
eTcErr test_afn00f1_t2c(BOOL bActive)
{   
    /*1 声明参数 */
    eTcErr     eRet        = TC_OK;
    UINT16     usBuflen    = 0;
    UINT8      *pMemPack   = NULL;
    sTcPackTml  *psPack     = NULL;
    sTcInit    sInit;
 
    pMemPack = (UINT8*)malloc(TC_USER_MAX);
    if(!pMemPack)
    {      
        return TC_ERR_IO;
    }
   
    psPack = (sTcPackTml*)pMemPack;

    /* 2 环境初始化 */
    sInit.eRole = TC_ROLE_TERMIN;
    sInit.ucPermitDelayMinutes = 255;
    eRet = eTcInit(&sInit);
    if(eRet != TC_OK)
    {
        printf("初始化失败\n");
        free(pMemPack);
        return eRet;
    }
    
    /* 3 封装参数 */
    psPack->sAddress.ucConAddress = 1;
    psPack->sAddress.bTeam        = FALSE;
    psPack->sAddress.ulTmlAddress = 1;
    memcpy(psPack->sAddress.acRegionCode, "110000", TC_REGN_LEN);

    psPack->bActive = TRUE;
    psPack->bReSend = FALSE;

    psPack->usNum = 1;
    psPack->sData[0].eCmd         = TCMD_AFN_0_F1_ALL_OK_DENY;
    psPack->sData[0].usPN         = 0;
    psPack->sData[0].bApp         = TRUE;

    psPack->sData[0].uApp.eResCode  = TC_RES_NONE;


    /* 4 调用函数 */
    eRet = etcPackTml(psPack, (UINT8*)g_ucOutBuf, &usBuflen);
    if(eRet != TC_OK)
    {
        printf("emcPack() error %d\n", eRet);
        free(pMemPack);
        return eRet;
    }
    
    /* 5 输出结果 */ 
    printf_buffer_color((char*)g_ucOutBuf, usBuflen);
    return TC_OK;
}

/*****************************************************************************
 函 数 名  : test_afn01f1_c2t
 功能描述  : 封装测试例 
 测试命令  : TCMD_AFN_1_F1_HARD_INIT

 输入参数  : BOOL bActive 是否为主动性

 输出参数  :
 返 回 值  : eTcErr
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月7日 星期二
    作    者   : liming
    修改内容   : 新生成函数
*****************************************************************************/
eTcErr test_afn01f1_c2t(BOOL bActive)
{   
    /*1 声明参数 */
    eTcErr     eRet        = TC_OK;
    UINT16     usBuflen    = 0;
    UINT8      *pMemPack   = NULL;
    sTcPackCon  *psPack    = NULL;
    sTcInit    sInit;
 
    pMemPack = (UINT8*)malloc(TC_USER_MAX);
    if(!pMemPack)
    {      
        return TC_ERR_IO;
    }
   
    psPack = (sTcPackCon*)pMemPack;

    /* 2 环境初始化 */
    sInit.eRole = TC_ROLE_CONTOR;
    sInit.ucPermitDelayMinutes = 255;
    eRet = eTcInit(&sInit);
    if(eRet != TC_OK)
    {
        printf("初始化失败\n");
        free(pMemPack);
        return eRet;
    }
    
    /* 3 封装参数 */
    psPack->sAddress.ucConAddress = 1;
    psPack->sAddress.bTeam        = FALSE;
    psPack->sAddress.ulTmlAddress = 1;
    memcpy(psPack->sAddress.acRegionCode, "110000", TC_REGN_LEN);
    psPack->ucPSEQ = 1;
 
    memcpy(psPack->aPw, "1234567890ABCDEF", TC_PW_LEN);

    psPack->usNum = 1;
    psPack->sData[0].eCmd         = TCMD_AFN_1_F1_HARD_INIT;
    psPack->sData[0].usPN         = 0;
    psPack->sData[0].bApp         = FALSE;

    /* 4 调用函数 */
    eRet = etcPackCon(psPack, (UINT8*)g_ucOutBuf, &usBuflen);
    if(eRet != TC_OK)
    {
        printf("emcPack() error %d\n", eRet);
        free(pMemPack);
        return eRet;
    }
    
    /* 5 输出结果 */ 
    printf_buffer_color((char*)g_ucOutBuf, usBuflen);
    return TC_OK;
}

/*****************************************************************************
 函 数 名  : test_afn01f2_c2t
 功能描述  : 封装测试例 
 测试命令  : TCMD_AFN_1_F2_DATA_INIT

 输入参数  : BOOL bActive 是否为主动性

 输出参数  :
 返 回 值  : eTcErr
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月7日 星期二
    作    者   : liming
    修改内容   : 新生成函数
*****************************************************************************/
eTcErr test_afn01f2_c2t(BOOL bActive)
{   
    /*1 声明参数 */
    eTcErr     eRet        = TC_OK;
    UINT16     usBuflen    = 0;
    UINT8      *pMemPack   = NULL;
    sTcPackCon   *psPack   = NULL;
    sTcInit    sInit;

    pMemPack = (UINT8*)malloc(TC_USER_MAX);
    if(!pMemPack)
    {      
        return TC_ERR_IO;
    }
   
    psPack = (sTcPackCon*)pMemPack;

    /* 2 环境初始化 */
    sInit.eRole = TC_ROLE_CONTOR;
    sInit.ucPermitDelayMinutes = 255;
    eRet = eTcInit(&sInit);
    if(eRet != TC_OK)
    {
        printf("初始化失败\n");
        free(pMemPack);
        return eRet;
    }
    
    /* 3 封装参数 */
    psPack->sAddress.ucConAddress = 1;
    psPack->sAddress.bTeam        = FALSE;
    psPack->sAddress.ulTmlAddress = 1;
    memcpy(psPack->sAddress.acRegionCode, "110000", TC_REGN_LEN);
    psPack->ucPSEQ = 1;
 
    memcpy(psPack->aPw, "1234567890ABCDEF", TC_PW_LEN);

    psPack->usNum = 1;
    psPack->sData[0].eCmd         = TCMD_AFN_1_F2_DATA_INIT;
    psPack->sData[0].usPN         = 0;
    psPack->sData[0].bApp         = FALSE;

    /* 4 调用函数 */
    eRet = etcPackCon(psPack, (UINT8*)g_ucOutBuf, &usBuflen);
    if(eRet != TC_OK)
    {
        printf("emcPack() error %d\n", eRet);
        free(pMemPack);
        return eRet;
    }
    
    /* 5 输出结果 */ 
    printf_buffer_color((char*)g_ucOutBuf, usBuflen);
    return TC_OK;
}

/*****************************************************************************
 函 数 名  : test_afn01f3_c2t
 功能描述  : 封装测试例 
 测试命令  : TCMD_AFN_1_F3_FACTORY_RESET

 输入参数  : BOOL bActive 是否为主动性

 输出参数  :
 返 回 值  : eTcErr
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月7日 星期二
    作    者   : liming
    修改内容   : 新生成函数
*****************************************************************************/
eTcErr test_afn01f3_c2t(BOOL bActive)
{   
    /*1 声明参数 */
    eTcErr     eRet        = TC_OK;
    UINT16     usBuflen    = 0;
    UINT8      *pMemPack   = NULL;
    sTcPackCon   *psPack   = NULL;
    sTcInit    sInit;
 
    pMemPack = (UINT8*)malloc(TC_USER_MAX);
    if(!pMemPack)
    {      
         return TC_ERR_IO;
    }
   
    psPack = (sTcPackCon*)pMemPack;

    /* 2 环境初始化 */
    sInit.eRole = TC_ROLE_CONTOR;
    sInit.ucPermitDelayMinutes = 255;
    eRet = eTcInit(&sInit);
    if(eRet != TC_OK)
    {
        printf("初始化失败\n");
        free(pMemPack);
        return eRet;
    }
    
    /* 3 封装参数 */
    psPack->sAddress.ucConAddress = 1;
    psPack->sAddress.bTeam        = FALSE;
    psPack->sAddress.ulTmlAddress = 1;
    memcpy(psPack->sAddress.acRegionCode, "110000", TC_REGN_LEN);
    psPack->ucPSEQ = 1;
 
    memcpy(psPack->aPw, "1234567890ABCDEF", TC_PW_LEN);

    psPack->usNum = 1;
    psPack->sData[0].eCmd         = TCMD_AFN_1_F3_FACTORY_RESET;
    psPack->sData[0].usPN         = 0;
    psPack->sData[0].bApp         = FALSE;
    
    /* 4 调用函数 */
    eRet = etcPackCon(psPack, (UINT8*)g_ucOutBuf, &usBuflen);
    if(eRet != TC_OK)
    {
        printf("emcPack() error %d\n", eRet);
        free(pMemPack);
        return eRet;
    }
    
    /* 5 输出结果 */ 
    printf_buffer_color((char*)g_ucOutBuf, usBuflen);
    return TC_OK;
}

/*****************************************************************************
 函 数 名  : test_afn01f4_c2t
 功能描述  : 封装测试例 
 测试命令  : TCMD_AFN_1_F4_PARA_INIT

 输入参数  : BOOL bActive 是否为主动性

 输出参数  :
 返 回 值  : eTcErr
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月7日 星期二
    作    者   : liming
    修改内容   : 新生成函数
*****************************************************************************/
eTcErr test_afn01f4_c2t(BOOL bActive)
{   
    /*1 声明参数 */
    eTcErr     eRet        = TC_OK;
    UINT16     usBuflen    = 0;
    UINT8      *pMemPack   = NULL;
    sTcPackCon   *psPack   = NULL;
    sTcInit    sInit;
 
    pMemPack = (UINT8*)malloc(TC_USER_MAX);
    if(!pMemPack)
    {      
         return TC_ERR_IO;
    }
    
    psPack = (sTcPackCon*)pMemPack;

    /* 2 环境初始化 */
    sInit.eRole = TC_ROLE_CONTOR;
    sInit.ucPermitDelayMinutes = 255;
    eRet = eTcInit(&sInit);
    if(eRet != TC_OK)
    {
        printf("初始化失败\n");
        free(pMemPack);
        return eRet;
    }
    
    /* 3 封装参数 */
    psPack->sAddress.ucConAddress = 1;
    psPack->sAddress.bTeam        = FALSE;
    psPack->sAddress.ulTmlAddress = 1;
    memcpy(psPack->sAddress.acRegionCode, "110000", TC_REGN_LEN);
    psPack->ucPSEQ = 1;
 
    memcpy(psPack->aPw, "1234567890ABCDEF", TC_PW_LEN);

    psPack->usNum = 1;
    psPack->sData[0].eCmd         = TCMD_AFN_1_F4_PARA_INIT;
    psPack->sData[0].usPN         = 0;
    psPack->sData[0].bApp         = FALSE;
 
    /* 4 调用函数 */
    eRet = etcPackCon(psPack, (UINT8*)g_ucOutBuf, &usBuflen);
    if(eRet != TC_OK)
    {
        printf("emcPack() error %d\n", eRet);
        free(pMemPack);
        return eRet;
    }
    
    /* 5 输出结果 */ 
    printf_buffer_color((char*)g_ucOutBuf, usBuflen);
    return TC_OK;
}

/*****************************************************************************
 函 数 名  : test_afn02f1_t2c
 功能描述  : 封装测试例 
 测试命令  : TCMD_AFN_2_F1_LOG_IN

 输入参数  : BOOL bActive 是否为主动性

 输出参数  :
 返 回 值  : eTcErr
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月7日 星期二
    作    者   : liming
    修改内容   : 新生成函数
*****************************************************************************/
eTcErr test_afn02f1_t2c(BOOL bActive)
{   
    /*1 声明参数 */
    eTcErr     eRet        = TC_OK;
    UINT16     usBuflen    = 0;
    UINT8      *pMemPack   = NULL;
    sTcPackTml  *psPack     = NULL;
    sTcInit    sInit;
 
    pMemPack = (UINT8*)malloc(TC_USER_MAX);
    if(!pMemPack)
    {      
        return TC_ERR_IO;
    }
   
    psPack = (sTcPackTml*)pMemPack;

    /* 2 环境初始化 */
    sInit.eRole = TC_ROLE_TERMIN;
    sInit.ucPermitDelayMinutes = 255;
    eRet = eTcInit(&sInit);
    if(eRet != TC_OK)
    {
        printf("初始化失败\n");
        free(pMemPack);
        return eRet;
    }
    
    /* 3 封装参数 */
    psPack->sAddress.ucConAddress = 1;
    psPack->sAddress.bTeam        = FALSE;
    psPack->sAddress.ulTmlAddress = 1;
    memcpy(psPack->sAddress.acRegionCode, "110000", TC_REGN_LEN);

    psPack->bActive = TRUE;
    psPack->bReSend = FALSE;

    psPack->usNum = 1;
    psPack->sData[0].eCmd         = TCMD_AFN_2_F1_LOG_IN;
    psPack->sData[0].usPN         = 0;
    psPack->sData[0].bApp         = FALSE;


    /* 4 调用函数 */
    eRet = etcPackTml(psPack, (UINT8*)g_ucOutBuf, &usBuflen);
    if(eRet != TC_OK)
    {
        printf("emcPack() error %d\n", eRet);
        free(pMemPack);
        return eRet;
    }
    
    /* 5 输出结果 */ 
    printf_buffer_color((char*)g_ucOutBuf, usBuflen);
    return TC_OK;
}

/*****************************************************************************
 函 数 名  : test_afn02f2_t2c
 功能描述  : 封装测试例 
 测试命令  : TCMD_AFN_2_F2_LOG_OUT

 输入参数  : BOOL bActive 是否为主动性

 输出参数  :
 返 回 值  : eTcErr
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月7日 星期二
    作    者   : liming
    修改内容   : 新生成函数
*****************************************************************************/
eTcErr test_afn02f2_t2c(BOOL bActive)
{   
    /*1 声明参数 */
    eTcErr     eRet        = TC_OK;
    UINT16     usBuflen    = 0;
    UINT8      *pMemPack   = NULL;
    sTcPackTml  *psPack     = NULL;
    sTcInit    sInit;
 
    pMemPack = (UINT8*)malloc(TC_USER_MAX);
    if(!pMemPack)
    {      
        return TC_ERR_IO;
    }
   
    psPack = (sTcPackTml*)pMemPack;

    /* 2 环境初始化 */
    sInit.eRole = TC_ROLE_TERMIN;
    sInit.ucPermitDelayMinutes = 255;
    eRet = eTcInit(&sInit);
    if(eRet != TC_OK)
    {
        printf("初始化失败\n");
        free(pMemPack);
        return eRet;
    }
    
    /* 3 封装参数 */
    psPack->sAddress.ucConAddress = 1;
    psPack->sAddress.bTeam        = FALSE;
    psPack->sAddress.ulTmlAddress = 1;
    memcpy(psPack->sAddress.acRegionCode, "110000", TC_REGN_LEN);

    psPack->bActive = TRUE;
    psPack->bReSend = FALSE;

    psPack->usNum = 1;
    psPack->sData[0].eCmd         = TCMD_AFN_2_F2_LOG_OUT;
    psPack->sData[0].usPN         = 0;
    psPack->sData[0].bApp         = FALSE;


    /* 4 调用函数 */
    eRet = etcPackTml(psPack, (UINT8*)g_ucOutBuf, &usBuflen);
    if(eRet != TC_OK)
    {
        printf("emcPack() error %d\n", eRet);
        free(pMemPack);
        return eRet;
    }
    
    /* 5 输出结果 */ 
    printf_buffer_color((char*)g_ucOutBuf, usBuflen);
    return TC_OK;
}

/*****************************************************************************
 函 数 名  : test_afn03f2_t2c
 功能描述  : 封装测试例 
 测试命令  : TCMD_AFN_2_F3_HEART_BEAT

 输入参数  : BOOL bActive 是否为主动性

 输出参数  :
 返 回 值  : eTcErr
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月7日 星期二
    作    者   : liming
    修改内容   : 新生成函数
*****************************************************************************/
eTcErr test_afn02f3_t2c(BOOL bActive)
{   
    /*1 声明参数 */
    eTcErr     eRet        = TC_OK;
    UINT16     usBuflen    = 0;
    UINT8      *pMemPack   = NULL;
    sTcPackTml  *psPack     = NULL;
    sTcInit    sInit;
 
    pMemPack = (UINT8*)malloc(TC_USER_MAX);
    if(!pMemPack)
    {      
        return TC_ERR_IO;
    }
   
    psPack = (sTcPackTml*)pMemPack;

    /* 2 环境初始化 */
    sInit.eRole = TC_ROLE_TERMIN;
    sInit.ucPermitDelayMinutes = 255;
    eRet = eTcInit(&sInit);
    if(eRet != TC_OK)
    {
        printf("初始化失败\n");
        free(pMemPack);
        return eRet;
    }
    
    /* 3 封装参数 */
    psPack->sAddress.ucConAddress = 1;
    psPack->sAddress.bTeam        = FALSE;
    psPack->sAddress.ulTmlAddress = 1;
    memcpy(psPack->sAddress.acRegionCode, "110000", TC_REGN_LEN);

    psPack->bActive = TRUE;
    psPack->bReSend = FALSE;

    psPack->usNum = 1;
    psPack->sData[0].eCmd         = TCMD_AFN_2_F3_HEART_BEAT;
    psPack->sData[0].usPN         = 0;
    psPack->sData[0].bApp         = FALSE;

    /* 4 调用函数 */
    eRet = etcPackTml(psPack, (UINT8*)g_ucOutBuf, &usBuflen);
    if(eRet != TC_OK)
    {
        printf("emcPack() error %d\n", eRet);
        free(pMemPack);
        return eRet;
    }
    
    /* 5 输出结果 */ 
    printf_buffer_color((char*)g_ucOutBuf, usBuflen);
    return TC_OK;
}

/*****************************************************************************
 函 数 名  : test_afn02f4_c2t
 功能描述  : 封装测试例 
 测试命令  : TCMD_AFN_2_F4_LINK_OK

 输入参数  : BOOL bActive 是否为主动性

 输出参数  :
 返 回 值  : eTcErr
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月7日 星期二
    作    者   : liming
    修改内容   : 新生成函数
*****************************************************************************/
eTcErr test_afn02f4_c2t(BOOL bActive)
{   
    /*1 声明参数 */
    eTcErr     eRet        = TC_OK;
    UINT16     usBuflen    = 0;
    UINT8      *pMemPack   = NULL;
    sTcPackCon   *psPack   = NULL;
    sTcInit    sInit;
 
    pMemPack = (UINT8*)malloc(TC_USER_MAX);
    if(!pMemPack)
    {      
         return TC_ERR_IO;
    }
    
    psPack = (sTcPackCon*)pMemPack;

    /* 2 环境初始化 */
    sInit.eRole = TC_ROLE_CONTOR;
    sInit.ucPermitDelayMinutes = 255;
    eRet = eTcInit(&sInit);
    if(eRet != TC_OK)
    {
        printf("初始化失败\n");
        free(pMemPack);
        return eRet;
    }
    
    /* 3 封装参数 */
    psPack->sAddress.ucConAddress = 1;
    psPack->sAddress.bTeam        = FALSE;
    psPack->sAddress.ulTmlAddress = 1;
    memcpy(psPack->sAddress.acRegionCode, "110000", TC_REGN_LEN);
    psPack->ucPSEQ = 1;
 
    memcpy(psPack->aPw, "1234567890ABCDEF", TC_PW_LEN);

    psPack->usNum = 1;
    psPack->sData[0].eCmd         = TCMD_AFN_2_F4_LINK_OK;
    psPack->sData[0].usPN         = 0;
    psPack->sData[0].bApp         = FALSE;
 
    /* 4 调用函数 */
    eRet = etcPackCon(psPack, (UINT8*)g_ucOutBuf, &usBuflen);
    if(eRet != TC_OK)
    {
        printf("emcPack() error %d\n", eRet);
        free(pMemPack);
        return eRet;
    }
    
    /* 5 输出结果 */ 
    printf_buffer_color((char*)g_ucOutBuf, usBuflen);
    return TC_OK;
}

/*****************************************************************************
 函 数 名  : test_afn04f1_c2t
 功能描述  : 封装测试例 
 测试命令  : TCMD_AFN_4_F1_CON_IP_PORT

 输入参数  : BOOL bActive 是否为主动性

 输出参数  :
 返 回 值  : eTcErr
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月7日 星期二
    作    者   : liming
    修改内容   : 新生成函数
*****************************************************************************/
eTcErr test_afn04f1_c2t(BOOL bActive)
{   
    /*1 声明参数 */
    eTcErr     eRet        = TC_OK;
    UINT16     usBuflen    = 0;
    UINT8      *pMemPack   = NULL;
    sTcPackCon   *psPack   = NULL;
    sTcInit    sInit;
 
    pMemPack = (UINT8*)malloc(TC_USER_MAX);
    if(!pMemPack)
    {      
         return TC_ERR_IO;
    }
    
    psPack = (sTcPackCon*)pMemPack;

    /* 2 环境初始化 */
    sInit.eRole = TC_ROLE_CONTOR;
    sInit.ucPermitDelayMinutes = 255;
    eRet = eTcInit(&sInit);
    if(eRet != TC_OK)
    {
        printf("初始化失败\n");
        free(pMemPack);
        return eRet;
    }
    
    /* 3 封装参数 */
    psPack->sAddress.ucConAddress = 1;
    psPack->sAddress.bTeam        = FALSE;
    psPack->sAddress.ulTmlAddress = 1;
    memcpy(psPack->sAddress.acRegionCode, "110000", TC_REGN_LEN);
    psPack->ucPSEQ = 1;
 
    memcpy(psPack->aPw, "0123456789ABCDEF", TC_PW_LEN);

    psPack->usNum = 1;
    psPack->sData[0].eCmd         = TCMD_AFN_4_F1_CON_IP_PORT;
    psPack->sData[0].usPN         = 0;
    psPack->sData[0].bApp         = TRUE;

    // 数据参数
    psPack->sData[0].uApp.sDownCfg.sMainIp.eVersion = TC_IP_V4;
    psPack->sData[0].uApp.sDownCfg.sMainIp.ip[0] = 192;
    psPack->sData[0].uApp.sDownCfg.sMainIp.ip[1] = 168;
    psPack->sData[0].uApp.sDownCfg.sMainIp.ip[2] = 10;
    psPack->sData[0].uApp.sDownCfg.sMainIp.ip[3] = 1;
    
    psPack->sData[0].uApp.sDownCfg.usMainPort = 6666;

    psPack->sData[0].uApp.sDownCfg.sBackIp.eVersion = TC_IP_V4;
    psPack->sData[0].uApp.sDownCfg.sBackIp.ip[0] = 192;
    psPack->sData[0].uApp.sDownCfg.sBackIp.ip[1] = 168;
    psPack->sData[0].uApp.sDownCfg.sBackIp.ip[2] = 10;
    psPack->sData[0].uApp.sDownCfg.sBackIp.ip[3] = 2;
    
    psPack->sData[0].uApp.sDownCfg.usBackPort = 7777;

    memcpy(&(psPack->sData[0].uApp.sDownCfg.ucAPN[0]), "0123456789ABCDEF", TC_APN_LEN);
    memcpy(&(psPack->sData[0].uApp.sDownCfg.ucUsr[0]), "0123456789ABCDEF0123456789ABCDEF", 32);
    memcpy(&(psPack->sData[0].uApp.sDownCfg.ucPwd[0]), "0123456789ABCDEF0123456789ABCDEF", 32);

    /* 4 调用函数 */
    eRet = etcPackCon(psPack, (UINT8*)g_ucOutBuf, &usBuflen);
    if(eRet != TC_OK)
    {
        printf("emcPack() error %d\n", eRet);
        free(pMemPack);
        return eRet;
    }
    
    /* 5 输出结果 */ 
    printf_buffer_color((char*)g_ucOutBuf, usBuflen);
    return TC_OK;
}

/*****************************************************************************
 函 数 名  : test_afn04f2_c2t
 功能描述  : 封装测试例 
 测试命令  : TCMD_AFN_4_F2_TML_UP_CFG

 输入参数  : BOOL bActive 是否为主动性

 输出参数  :
 返 回 值  : eTcErr
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月7日 星期二
    作    者   : liming
    修改内容   : 新生成函数
*****************************************************************************/
eTcErr test_afn04f2_c2t(BOOL bActive)
{   
    /*1 声明参数 */
    eTcErr     eRet        = TC_OK;
    UINT16     usBuflen    = 0;
    UINT8      *pMemPack   = NULL;
    sTcPackCon   *psPack   = NULL;
    sTcInit    sInit;
 
    pMemPack = (UINT8*)malloc(TC_USER_MAX);
    if(!pMemPack)
    {      
         return TC_ERR_IO;
    }
    
    psPack = (sTcPackCon*)pMemPack;

    /* 2 环境初始化 */
    sInit.eRole = TC_ROLE_CONTOR;
    sInit.ucPermitDelayMinutes = 255;
    eRet = eTcInit(&sInit);
    if(eRet != TC_OK)
    {
        printf("初始化失败\n");
        free(pMemPack);
        return eRet;
    }
    
    /* 3 封装参数 */
    psPack->sAddress.ucConAddress = 1;
    psPack->sAddress.bTeam        = FALSE;
    psPack->sAddress.ulTmlAddress = 1;
    memcpy(psPack->sAddress.acRegionCode, "110000", TC_REGN_LEN);
    psPack->ucPSEQ = 1;
 
    memcpy(psPack->aPw, "0123456789ABCDEF", TC_PW_LEN);

    psPack->usNum = 1;
    psPack->sData[0].eCmd         = TCMD_AFN_4_F2_TML_UP_CFG;
    psPack->sData[0].usPN         = 0;
    psPack->sData[0].bApp         = TRUE;

    // 数据参数
    psPack->sData[0].uApp.sTmlUpCfg.usListenPort = 1234;
    
    psPack->sData[0].uApp.sTmlUpCfg.sUpIp.eVersion = TC_IP_V4;
    psPack->sData[0].uApp.sTmlUpCfg.sUpIp.ip[0] = 192;
    psPack->sData[0].uApp.sTmlUpCfg.sUpIp.ip[1] = 168;
    psPack->sData[0].uApp.sTmlUpCfg.sUpIp.ip[2] = 10;
    psPack->sData[0].uApp.sTmlUpCfg.sUpIp.ip[3] = 123;
    
    psPack->sData[0].uApp.sTmlUpCfg.sUpMask.eVersion = TC_IP_V4;
    psPack->sData[0].uApp.sTmlUpCfg.sUpMask.ip[0] = 255;
    psPack->sData[0].uApp.sTmlUpCfg.sUpMask.ip[1] = 255;
    psPack->sData[0].uApp.sTmlUpCfg.sUpMask.ip[2] = 255;
    psPack->sData[0].uApp.sTmlUpCfg.sUpMask.ip[3] = 0;   
    
    psPack->sData[0].uApp.sTmlUpCfg.sGateIp.eVersion = TC_IP_V4;
    psPack->sData[0].uApp.sTmlUpCfg.sGateIp.ip[0] = 192;
    psPack->sData[0].uApp.sTmlUpCfg.sGateIp.ip[1] = 168;
    psPack->sData[0].uApp.sTmlUpCfg.sGateIp.ip[2] = 10;
    psPack->sData[0].uApp.sTmlUpCfg.sGateIp.ip[3] = 1;
    
    psPack->sData[0].uApp.sTmlUpCfg.eDelegate = TC_DELG_HTTP;

    psPack->sData[0].uApp.sTmlUpCfg.sDelgIp.eVersion = TC_IP_V4;
    psPack->sData[0].uApp.sTmlUpCfg.sDelgIp.ip[0] = 192;
    psPack->sData[0].uApp.sTmlUpCfg.sDelgIp.ip[1] = 168;
    psPack->sData[0].uApp.sTmlUpCfg.sDelgIp.ip[2] = 10;
    psPack->sData[0].uApp.sTmlUpCfg.sDelgIp.ip[3] = 234;

    psPack->sData[0].uApp.sTmlUpCfg.usDelgPort = 6666;


    #if 0
    psPack->sData[0].uApp.sTmlUpCfg.eDelgLink  = TC_DELK_USRPWD;
   
    psPack->sData[0].uApp.sTmlUpCfg.bDlegUsr   = TRUE;
    psPack->sData[0].uApp.sTmlUpCfg.ucDlegUsrLen = 20;
    memcpy(psPack->sData[0].uApp.sTmlUpCfg.ucDlegUsr, "012456789ABCDEF012345678", 20);
    
    psPack->sData[0].uApp.sTmlUpCfg.bDlegPwd = TRUE;
    psPack->sData[0].uApp.sTmlUpCfg.ucDlegPwdLen = 20;
    memcpy(psPack->sData[0].uApp.sTmlUpCfg.ucDlegPwd, "012456789ABCDEF012345678", 20);
    #else
    psPack->sData[0].uApp.sTmlUpCfg.eDelgLink  = TC_DELK_ANYONE;
   
    psPack->sData[0].uApp.sTmlUpCfg.bDlegUsr   = FALSE;
    
    psPack->sData[0].uApp.sTmlUpCfg.bDlegPwd   = FALSE;
    #endif


    psPack->sData[0].uApp.sTmlUpCfg.ucPermitDelayM = 255;
    psPack->sData[0].uApp.sTmlUpCfg.ucReSendTimes = 3;
    psPack->sData[0].uApp.sTmlUpCfg.ucHeartBeat = 1;
    psPack->sData[0].uApp.sTmlUpCfg.usWaitTimeoutS = 1234;
    psPack->sData[0].uApp.sTmlUpCfg.bPermitTk = TRUE;
    psPack->sData[0].uApp.sTmlUpCfg.bPermitEv = TRUE;
  

    /* 4 调用函数 */
    eRet = etcPackCon(psPack, (UINT8*)g_ucOutBuf, &usBuflen);
    if(eRet != TC_OK)
    {
        printf("emcPack() error %d\n", eRet);
        free(pMemPack);
        return eRet;
    }
    
    /* 5 输出结果 */ 
    printf_buffer_color((char*)g_ucOutBuf, usBuflen);
    return TC_OK;
}

/*****************************************************************************
 函 数 名  : test_afn04f3_c2t
 功能描述  : 封装测试例 
 测试命令  : TCMD_AFN_4_F3_TML_AUTH_PARA

 输入参数  : BOOL bActive 是否为主动性

 输出参数  :
 返 回 值  : eTcErr
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月7日 星期二
    作    者   : liming
    修改内容   : 新生成函数
*****************************************************************************/
eTcErr test_afn04f3_c2t(BOOL bActive)
{   
    /*1 声明参数 */
    eTcErr     eRet        = TC_OK;
    UINT16     usBuflen    = 0;
    UINT8      *pMemPack   = NULL;
    sTcPackCon   *psPack   = NULL;
    sTcInit    sInit;
 
    pMemPack = (UINT8*)malloc(TC_USER_MAX);
    if(!pMemPack)
    {      
         return TC_ERR_IO;
    }
    
    psPack = (sTcPackCon*)pMemPack;

    /* 2 环境初始化 */
    sInit.eRole = TC_ROLE_CONTOR;
    sInit.ucPermitDelayMinutes = 255;
    eRet = eTcInit(&sInit);
    if(eRet != TC_OK)
    {
        printf("初始化失败\n");
        free(pMemPack);
        return eRet;
    }
    
    /* 3 封装参数 */
    psPack->sAddress.ucConAddress = 1;
    psPack->sAddress.bTeam        = FALSE;
    psPack->sAddress.ulTmlAddress = 1;
    memcpy(psPack->sAddress.acRegionCode, "110000", TC_REGN_LEN);
    psPack->ucPSEQ = 1;
 
    memcpy(psPack->aPw, "0123456789ABCDEF", TC_PW_LEN);

    psPack->usNum = 1;
    psPack->sData[0].eCmd         = TCMD_AFN_4_F3_TML_AUTH_PARA;
    psPack->sData[0].usPN         = 0;
    psPack->sData[0].bApp         = TRUE;

    // 数据参数
    psPack->sData[0].uApp.sAuthPara.usAuthPara = 1;
    psPack->sData[0].uApp.sAuthPara.ucTypeID   = 123;
    
    /* 4 调用函数 */
    eRet = etcPackCon(psPack, (UINT8*)g_ucOutBuf, &usBuflen);
    if(eRet != TC_OK)
    {
        printf("emcPack() error %d\n", eRet);
        free(pMemPack);
        return eRet;
    }
    
    /* 5 输出结果 */ 
    printf_buffer_color((char*)g_ucOutBuf, usBuflen);
    return TC_OK;
}

/*****************************************************************************
 函 数 名  : test_afn04f4_c2t
 功能描述  : 封装测试例 
 测试命令  : TCMD_AFN_4_F4_TML_STATE_INPUT

 输入参数  : BOOL bActive 是否为主动性

 输出参数  :
 返 回 值  : eTcErr
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月7日 星期二
    作    者   : liming
    修改内容   : 新生成函数
*****************************************************************************/
eTcErr test_afn04f4_c2t(BOOL bActive)
{   
    /*1 声明参数 */
    eTcErr     eRet        = TC_OK;
    UINT16     usBuflen    = 0;
    UINT8      *pMemPack   = NULL;
    sTcPackCon   *psPack   = NULL;
    sTcInit    sInit;
 
    pMemPack = (UINT8*)malloc(TC_USER_MAX);
    if(!pMemPack)
    {      
         return TC_ERR_IO;
    }
    
    psPack = (sTcPackCon*)pMemPack;

    /* 2 环境初始化 */
    sInit.eRole = TC_ROLE_CONTOR;
    sInit.ucPermitDelayMinutes = 255;
    eRet = eTcInit(&sInit);
    if(eRet != TC_OK)
    {
        printf("初始化失败\n");
        free(pMemPack);
        return eRet;
    }
    
    /* 3 封装参数 */
    psPack->sAddress.ucConAddress = 1;
    psPack->sAddress.bTeam        = FALSE;
    psPack->sAddress.ulTmlAddress = 1;
    memcpy(psPack->sAddress.acRegionCode, "110000", TC_REGN_LEN);
    psPack->ucPSEQ = 1;
 
    memcpy(psPack->aPw, "0123456789ABCDEF", TC_PW_LEN);

    psPack->usNum = 1;
    psPack->sData[0].eCmd         = TCMD_AFN_4_F4_TML_STATE_INPUT;
    psPack->sData[0].usPN         = 0;
    psPack->sData[0].bApp         = TRUE;

    // 数据参数
    int i = 0;
    for(i = 0; i < 8; i++)
    {
       psPack->sData[0].uApp.sStateInput.bIn[i] = TRUE;
       psPack->sData[0].uApp.sStateInput.bOn[i] = TRUE;
    }
   
    /* 4 调用函数 */
    eRet = etcPackCon(psPack, (UINT8*)g_ucOutBuf, &usBuflen);
    if(eRet != TC_OK)
    {
        printf("emcPack() error %d\n", eRet);
        free(pMemPack);
        return eRet;
    }
    
    /* 5 输出结果 */ 
    printf_buffer_color((char*)g_ucOutBuf, usBuflen);
    return TC_OK;
}

/*****************************************************************************
 函 数 名  : test_afn04f5_c2t
 功能描述  : 封装测试例 
 测试命令  : TCMD_AFN_4_F5_TML_EVENT_CFG

 输入参数  : BOOL bActive 是否为主动性

 输出参数  :
 返 回 值  : eTcErr
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月7日 星期二
    作    者   : liming
    修改内容   : 新生成函数
*****************************************************************************/
eTcErr test_afn04f5_c2t(BOOL bActive)
{   
    /*1 声明参数 */
    eTcErr     eRet        = TC_OK;
    UINT16     usBuflen    = 0;
    UINT8      *pMemPack   = NULL;
    sTcPackCon   *psPack   = NULL;
    sTcInit    sInit;
 
    pMemPack = (UINT8*)malloc(TC_USER_MAX);
    if(!pMemPack)
    {      
         return TC_ERR_IO;
    }
    
    psPack = (sTcPackCon*)pMemPack;

    /* 2 环境初始化 */
    sInit.eRole = TC_ROLE_CONTOR;
    sInit.ucPermitDelayMinutes = 255;
    eRet = eTcInit(&sInit);
    if(eRet != TC_OK)
    {
        printf("初始化失败\n");
        free(pMemPack);
        return eRet;
    }
    
    /* 3 封装参数 */
    psPack->sAddress.ucConAddress = 1;
    psPack->sAddress.bTeam        = FALSE;
    psPack->sAddress.ulTmlAddress = 1;
    memcpy(psPack->sAddress.acRegionCode, "110000", TC_REGN_LEN);
    psPack->ucPSEQ = 1;
 
    memcpy(psPack->aPw, "0123456789ABCDEF", TC_PW_LEN);

    psPack->usNum = 1;
    psPack->sData[0].eCmd         = TCMD_AFN_4_F5_TML_EVENT_CFG;
    psPack->sData[0].usPN         = 0;
    psPack->sData[0].bApp         = TRUE;

    // 数据参数
    psPack->sData[0].uApp.sEventCfg.ucNeed    = 3;
    psPack->sData[0].uApp.sEventCfg.aNeed[0]  = TC_ERC_1_RESET;
    psPack->sData[0].uApp.sEventCfg.aNeed[1]  = TC_ERC_2_SOFT_CHANGE;
    psPack->sData[0].uApp.sEventCfg.aNeed[2]  = TC_ERC_3_PARA_CHANGE;

    psPack->sData[0].uApp.sEventCfg.ucImpt    = 2;
    psPack->sData[0].uApp.sEventCfg.aImpt[0]  = TC_ERC_1_RESET;
    psPack->sData[0].uApp.sEventCfg.aImpt[1]  = TC_ERC_2_SOFT_CHANGE;

   
    /* 4 调用函数 */
    eRet = etcPackCon(psPack, (UINT8*)g_ucOutBuf, &usBuflen);
    if(eRet != TC_OK)
    {
        printf("emcPack() error %d\n", eRet);
        free(pMemPack);
        return eRet;
    }
    
    /* 5 输出结果 */ 
    printf_buffer_color((char*)g_ucOutBuf, usBuflen);
    return TC_OK;
}

/*****************************************************************************
 函 数 名  : test_afn04f17_c2t
 功能描述  : 封装测试例 
 测试命令  : TCMD_AFN_4_F17_FREZ_TASK_PARA

 输入参数  : BOOL bActive 是否为主动性

 输出参数  :
 返 回 值  : eTcErr
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月7日 星期二
    作    者   : liming
    修改内容   : 新生成函数
*****************************************************************************/
eTcErr test_afn04f17_c2t(BOOL bActive)
{   
    /*1 声明参数 */
    eTcErr     eRet        = TC_OK;
    UINT16     usBuflen    = 0;
    UINT8      *pMemPack   = NULL;
    sTcPackCon   *psPack   = NULL;
    sTcInit    sInit;
 
    pMemPack = (UINT8*)malloc(TC_USER_MAX);
    if(!pMemPack)
    {      
         return TC_ERR_IO;
    }
    
    psPack = (sTcPackCon*)pMemPack;

    /* 2 环境初始化 */
    sInit.eRole = TC_ROLE_CONTOR;
    sInit.ucPermitDelayMinutes = 255;
    eRet = eTcInit(&sInit);
    if(eRet != TC_OK)
    {
        printf("初始化失败\n");
        free(pMemPack);
        return eRet;
    }
    
    /* 3 封装参数 */
    psPack->sAddress.ucConAddress = 1;
    psPack->sAddress.bTeam        = FALSE;
    psPack->sAddress.ulTmlAddress = 1;
    memcpy(psPack->sAddress.acRegionCode, "110000", TC_REGN_LEN);
    psPack->ucPSEQ = 1;
 
    memcpy(psPack->aPw, "0123456789ABCDEF", TC_PW_LEN);

    psPack->usNum = 1;
    psPack->sData[0].eCmd         = TCMD_AFN_4_F17_FREZ_TASK_PARA;
    psPack->sData[0].usPN         = 0;
    psPack->sData[0].bApp         = TRUE;

    // 数据参数

  
    psPack->sData[0].uApp.sFrezTaskPara.sTimeFrez.ucYY = 0;
    psPack->sData[0].uApp.sFrezTaskPara.sTimeFrez.ucMM = 1;
    psPack->sData[0].uApp.sFrezTaskPara.sTimeFrez.ucWW = 1;
    psPack->sData[0].uApp.sFrezTaskPara.sTimeFrez.ucDD = 1;
    psPack->sData[0].uApp.sFrezTaskPara.sTimeFrez.ucHH = 1;
    psPack->sData[0].uApp.sFrezTaskPara.sTimeFrez.ucmm = 1;
    psPack->sData[0].uApp.sFrezTaskPara.sTimeFrez.ucss = 1;   

    psPack->sData[0].uApp.sFrezTaskPara.sFreez.usPeriod = 1;   
    psPack->sData[0].uApp.sFrezTaskPara.sFreez.eUnit = TC_PUNT_MIN;   
    psPack->sData[0].uApp.sFrezTaskPara.sFreez.ucTimes = 0;   


    psPack->sData[0].uApp.sFrezTaskPara.ucPeriodRpt = 1;   
    psPack->sData[0].uApp.sFrezTaskPara.eUnitRpt = TC_PUNT_MIN;   

    psPack->sData[0].uApp.sFrezTaskPara.sTimeRprt.ucYY = 0;
    psPack->sData[0].uApp.sFrezTaskPara.sTimeRprt.ucMM = 1;
    psPack->sData[0].uApp.sFrezTaskPara.sTimeRprt.ucWW = 1;
    psPack->sData[0].uApp.sFrezTaskPara.sTimeRprt.ucDD = 1;
    psPack->sData[0].uApp.sFrezTaskPara.sTimeRprt.ucHH = 1;
    psPack->sData[0].uApp.sFrezTaskPara.sTimeRprt.ucmm = 1;
    psPack->sData[0].uApp.sFrezTaskPara.sTimeRprt.ucss = 1;   

    psPack->sData[0].uApp.sFrezTaskPara.eUnitRpt = TC_PUNT_MIN;
    
    psPack->sData[0].uApp.sFrezTaskPara.ucPeriodRpt = 1;
    
    psPack->sData[0].uApp.sFrezTaskPara.uCmdPnNum = 2;

    psPack->sData[0].uApp.sFrezTaskPara.sCmdPn[0].eCmd = TCMD_AFN_D_F49_ELEC_A;
    psPack->sData[0].uApp.sFrezTaskPara.sCmdPn[0].usPn = 1;

    psPack->sData[0].uApp.sFrezTaskPara.sCmdPn[1].eCmd = TCMD_AFN_D_F41_VOLT_A;
    psPack->sData[0].uApp.sFrezTaskPara.sCmdPn[1].usPn = 2;

   
    /* 4 调用函数 */
    eRet = etcPackCon(psPack, (UINT8*)g_ucOutBuf, &usBuflen);
    if(eRet != TC_OK)
    {
        printf("emcPack() error %d\n", eRet);
        free(pMemPack);
        return eRet;
    }
    
    /* 5 输出结果 */ 
    printf_buffer_color((char*)g_ucOutBuf, usBuflen);
    return TC_OK;
}

/*****************************************************************************
 函 数 名  : test_afn04f25_c2t
 功能描述  : 封装测试例 
 测试命令  : TCMD_AFN_4_F25_ELEC_MP_CFG

 输入参数  : BOOL bActive 是否为主动性

 输出参数  :
 返 回 值  : eTcErr
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月7日 星期二
    作    者   : liming
    修改内容   : 新生成函数
*****************************************************************************/
eTcErr test_afn04f25_c2t(BOOL bActive)
{   
    /*1 声明参数 */
    eTcErr     eRet        = TC_OK;
    UINT16     usBuflen    = 0;
    UINT8      *pMemPack   = NULL;
    sTcPackCon   *psPack   = NULL;
    sTcInit    sInit;
    eTcAcsPort eAcsPort = TC_ACS_PORT_SER; // 通过更改这个初始化，改变运行参数

    pMemPack = (UINT8*)malloc(TC_USER_MAX);
    if(!pMemPack)
    {      
         return TC_ERR_IO;
    }
    
    psPack = (sTcPackCon*)pMemPack;

    /* 2 环境初始化 */
    sInit.eRole = TC_ROLE_CONTOR;
    sInit.ucPermitDelayMinutes = 255;
    eRet = eTcInit(&sInit);
    if(eRet != TC_OK)
    {
        printf("初始化失败\n");
        free(pMemPack);
        return eRet;
    }
    
    /* 3 封装参数 */
    psPack->sAddress.ucConAddress = 1;
    psPack->sAddress.bTeam        = FALSE;
    psPack->sAddress.ulTmlAddress = 1;
    memcpy(psPack->sAddress.acRegionCode, "110000", TC_REGN_LEN);
    psPack->ucPSEQ = 1;
 
    memcpy(psPack->aPw, "0123456789ABCDEF", TC_PW_LEN);

    psPack->usNum = 1;
    psPack->sData[0].eCmd         = TCMD_AFN_4_F25_ELEC_MP_CFG;
    psPack->sData[0].usPN         = 0;
    psPack->sData[0].bApp         = TRUE;

    // 数据参数

  
       #if 1
    //psPack->sData[0].uApp.sElecMpCfg.usID   = 0;
    psPack->sData[0].uApp.sElecMpCfg.ucPort = 1;
    memcpy(psPack->sData[0].uApp.sElecMpCfg.ucAddr, "0000000000000001", 16);


    psPack->sData[0].uApp.sElecMpCfg.eAcsProto = TC_ACS_PROT_MODBUS;
    memcpy(psPack->sData[0].uApp.sElecMpCfg.ucPwd, "123456", 6);

    psPack->sData[0].uApp.sElecMpCfg.eAcsPort = eAcsPort;
    switch(eAcsPort)
    {
        case TC_ACS_PORT_DC:
        case TC_ACS_PORT_AC:
            break;        

        case TC_ACS_PORT_SER:
            psPack->sData[0].uApp.sElecMpCfg.uPortPara.sSer.eBaud  = TC_BAUD_1200;
            psPack->sData[0].uApp.sElecMpCfg.uPortPara.sSer.bStop1 = TRUE;
            psPack->sData[0].uApp.sElecMpCfg.uPortPara.sSer.bCheck = TRUE;
            psPack->sData[0].uApp.sElecMpCfg.uPortPara.sSer.bOdd   = TRUE;
            psPack->sData[0].uApp.sElecMpCfg.uPortPara.sSer.eBit   = TC_SBIT_5;
            break;    
            
        case TC_ACS_PORT_ETH:
            psPack->sData[0].uApp.sElecMpCfg.uPortPara.sEth.usPort  = 1234;
            psPack->sData[0].uApp.sElecMpCfg.uPortPara.sEth.sMask.eVersion = TC_IP_V4;
            psPack->sData[0].uApp.sElecMpCfg.uPortPara.sEth.sMask.ip[0]  = 255;
            psPack->sData[0].uApp.sElecMpCfg.uPortPara.sEth.sMask.ip[1]  = 255;
            psPack->sData[0].uApp.sElecMpCfg.uPortPara.sEth.sMask.ip[2]  = 255;
            psPack->sData[0].uApp.sElecMpCfg.uPortPara.sEth.sMask.ip[3]  = 0;

   
            psPack->sData[0].uApp.sElecMpCfg.uPortPara.sEth.sGate.eVersion = TC_IP_V4;
            psPack->sData[0].uApp.sElecMpCfg.uPortPara.sEth.sGate.ip[0]  = 192;
            psPack->sData[0].uApp.sElecMpCfg.uPortPara.sEth.sGate.ip[1]  = 168;
            psPack->sData[0].uApp.sElecMpCfg.uPortPara.sEth.sGate.ip[2]  = 0;
            psPack->sData[0].uApp.sElecMpCfg.uPortPara.sEth.sGate.ip[3]  = 1;         
           
            break;     

        case TC_ACS_PORT_ZIGB:
            psPack->sData[0].uApp.sElecMpCfg.uPortPara.ulAddrZigb = 12345678;
            break;      
            
        default:
            break;

    }

  /*
    
    psPack->sData[0].uApp.sElecMpCfg.usAcsPort   = 1234;
    

    psPack->sData[0].uApp.sElecMpCfg.sAccess.eVersion = TC_IP_V4;
    psPack->sData[0].uApp.sElecMpCfg.sAccess.ip[0]  = 192;
    psPack->sData[0].uApp.sElecMpCfg.sAccess.ip[1]  = 168;
    psPack->sData[0].uApp.sElecMpCfg.sAccess.ip[2]  = 1;
    psPack->sData[0].uApp.sElecMpCfg.sAccess.ip[3]  = 111;

  
    psPack->sData[0].uApp.sElecMpCfg.sGateIp.eVersion = MC_IP_V4;
    psPack->sData[0].uApp.sElecMpCfg.sGateIp.ip[0]  = 192;
    psPack->sData[0].uApp.sElecMpCfg.sGateIp.ip[1]  = 168;
    psPack->sData[0].uApp.sElecMpCfg.sGateIp.ip[2]  = 0;
    psPack->sData[0].uApp.sElecMpCfg.sGateIp.ip[3]  = 1;    

*/
    
    #endif


   
    /* 4 调用函数 */
    eRet = etcPackCon(psPack, (UINT8*)g_ucOutBuf, &usBuflen);
    if(eRet != TC_OK)
    {
        printf("emcPack() error %d\n", eRet);
        free(pMemPack);
        return eRet;
    }
    
    /* 5 输出结果 */ 
    printf_buffer_color((char*)g_ucOutBuf, usBuflen);
    return TC_OK;
}

/*****************************************************************************
 函 数 名  : test_afn05f1_c2t
 功能描述  : 封装测试例 
 测试命令  : TCMD_AFN_5_F1_CHECK_TIME

 输入参数  : BOOL bActive 是否为主动性

 输出参数  :
 返 回 值  : eTcErr
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月7日 星期二
    作    者   : liming
    修改内容   : 新生成函数
*****************************************************************************/
eTcErr test_afn05f1_c2t(BOOL bActive)
{   
    /*1 声明参数 */
    eTcErr     eRet        = TC_OK;
    UINT16     usBuflen    = 0;
    UINT8      *pMemPack   = NULL;
    sTcPackCon   *psPack   = NULL;
    sTcInit    sInit;
 
    pMemPack = (UINT8*)malloc(TC_USER_MAX);
    if(!pMemPack)
    {      
         return TC_ERR_IO;
    }
    
    psPack = (sTcPackCon*)pMemPack;

    /* 2 环境初始化 */
    sInit.eRole = TC_ROLE_CONTOR;
    sInit.ucPermitDelayMinutes = 255;
    eRet = eTcInit(&sInit);
    if(eRet != TC_OK)
    {
        printf("初始化失败\n");
        free(pMemPack);
        return eRet;
    }
    
    /* 3 封装参数 */
    psPack->sAddress.ucConAddress = 1;
    psPack->sAddress.bTeam        = FALSE;
    psPack->sAddress.ulTmlAddress = 1;
    memcpy(psPack->sAddress.acRegionCode, "110000", TC_REGN_LEN);
    psPack->ucPSEQ = 1;
 
    memcpy(psPack->aPw, "0123456789ABCDEF", TC_PW_LEN);

    psPack->usNum = 1;
    psPack->sData[0].eCmd         = TCMD_AFN_5_F1_CHECK_TIME;
    psPack->sData[0].usPN         = 0;
    psPack->sData[0].bApp         = TRUE;

    // 数据参数
    psPack->sData[0].uApp.sCheckClock.ucYY    = 14;
    psPack->sData[0].uApp.sCheckClock.ucMM    = 1;
    psPack->sData[0].uApp.sCheckClock.ucWW    = 5;
    psPack->sData[0].uApp.sCheckClock.ucDD    = 10;
    psPack->sData[0].uApp.sCheckClock.ucHH    = 10;
    psPack->sData[0].uApp.sCheckClock.ucmm    = 13;
    psPack->sData[0].uApp.sCheckClock.ucss    = 13;
    
    /* 4 调用函数 */
    eRet = etcPackCon(psPack, (UINT8*)g_ucOutBuf, &usBuflen);
    if(eRet != TC_OK)
    {
        printf("emcPack() error %d\n", eRet);
        free(pMemPack);
        return eRet;
    }
    
    /* 5 输出结果 */ 
    printf_buffer_color((char*)g_ucOutBuf, usBuflen);
    return TC_OK;
}


/*****************************************************************************
 函 数 名  : test_afn05f3_c2t
 功能描述  : 封装测试例 
 测试命令  : TCMD_AFN_5_F3_AUTO_SAY_ON

 输入参数  : BOOL bActive 是否为主动性

 输出参数  :
 返 回 值  : eTcErr
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月7日 星期二
    作    者   : liming
    修改内容   : 新生成函数
*****************************************************************************/
eTcErr test_afn05f3_c2t(BOOL bActive)
{   
    /*1 声明参数 */
    eTcErr     eRet        = TC_OK;
    UINT16     usBuflen    = 0;
    UINT8      *pMemPack   = NULL;
    sTcPackCon   *psPack   = NULL;
    sTcInit    sInit;
 
    pMemPack = (UINT8*)malloc(TC_USER_MAX);
    if(!pMemPack)
    {      
         return TC_ERR_IO;
    }
    
    psPack = (sTcPackCon*)pMemPack;

    /* 2 环境初始化 */
    sInit.eRole = TC_ROLE_CONTOR;
    sInit.ucPermitDelayMinutes = 255;
    eRet = eTcInit(&sInit);
    if(eRet != TC_OK)
    {
        printf("初始化失败\n");
        free(pMemPack);
        return eRet;
    }
    
    /* 3 封装参数 */
    psPack->sAddress.ucConAddress = 1;
    psPack->sAddress.bTeam        = FALSE;
    psPack->sAddress.ulTmlAddress = 1;
    memcpy(psPack->sAddress.acRegionCode, "110000", TC_REGN_LEN);
    psPack->ucPSEQ = 1;
 
    memcpy(psPack->aPw, "0123456789ABCDEF", TC_PW_LEN);

    psPack->usNum = 1;
    psPack->sData[0].eCmd         = TCMD_AFN_5_F3_AUTO_SAY_ON;
    psPack->sData[0].usPN         = 0;
    psPack->sData[0].bApp         = FALSE;


    /* 4 调用函数 */
    eRet = etcPackCon(psPack, (UINT8*)g_ucOutBuf, &usBuflen);
    if(eRet != TC_OK)
    {
        printf("emcPack() error %d\n", eRet);
        free(pMemPack);
        return eRet;
    }
    
    /* 5 输出结果 */ 
    printf_buffer_color((char*)g_ucOutBuf, usBuflen);
    return TC_OK;
}

/*****************************************************************************
 函 数 名  : test_afn05f4_c2t
 功能描述  : 封装测试例 
 测试命令  : TCMD_AFN_5_F4_AUTO_SAY_OFF

 输入参数  : BOOL bActive 是否为主动性

 输出参数  :
 返 回 值  : eTcErr
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月7日 星期二
    作    者   : liming
    修改内容   : 新生成函数
*****************************************************************************/
eTcErr test_afn05f4_c2t(BOOL bActive)
{   
    /*1 声明参数 */
    eTcErr     eRet        = TC_OK;
    UINT16     usBuflen    = 0;
    UINT8      *pMemPack   = NULL;
    sTcPackCon   *psPack   = NULL;
    sTcInit    sInit;
 
    pMemPack = (UINT8*)malloc(TC_USER_MAX);
    if(!pMemPack)
    {      
         return TC_ERR_IO;
    }
    
    psPack = (sTcPackCon*)pMemPack;

    /* 2 环境初始化 */
    sInit.eRole = TC_ROLE_CONTOR;
    sInit.ucPermitDelayMinutes = 255;
    eRet = eTcInit(&sInit);
    if(eRet != TC_OK)
    {
        printf("初始化失败\n");
        free(pMemPack);
        return eRet;
    }
    
    /* 3 封装参数 */
    psPack->sAddress.ucConAddress = 1;
    psPack->sAddress.bTeam        = FALSE;
    psPack->sAddress.ulTmlAddress = 1;
    memcpy(psPack->sAddress.acRegionCode, "110000", TC_REGN_LEN);
    psPack->ucPSEQ = 1;
 
    memcpy(psPack->aPw, "0123456789ABCDEF", TC_PW_LEN);

    psPack->usNum = 1;
    psPack->sData[0].eCmd         = TCMD_AFN_5_F4_AUTO_SAY_OFF;
    psPack->sData[0].usPN         = 0;
    psPack->sData[0].bApp         = FALSE;


    /* 4 调用函数 */
    eRet = etcPackCon(psPack, (UINT8*)g_ucOutBuf, &usBuflen);
    if(eRet != TC_OK)
    {
        printf("emcPack() error %d\n", eRet);
        free(pMemPack);
        return eRet;
    }
    
    /* 5 输出结果 */ 
    printf_buffer_color((char*)g_ucOutBuf, usBuflen);
    return TC_OK;
}

/*****************************************************************************
 函 数 名  : test_afn05f5_c2t
 功能描述  : 封装测试例 
 测试命令  : TCMD_AFN_5_F5_NX_MODEL_ACT

 输入参数  : BOOL bActive 是否为主动性

 输出参数  :
 返 回 值  : eTcErr
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月7日 星期二
    作    者   : liming
    修改内容   : 新生成函数
*****************************************************************************/
eTcErr test_afn05f5_c2t(BOOL bActive)
{   
    /*1 声明参数 */
    eTcErr     eRet        = TC_OK;
    UINT16     usBuflen    = 0;
    UINT8      *pMemPack   = NULL;
    sTcPackCon   *psPack   = NULL;
    sTcInit    sInit;
 
    pMemPack = (UINT8*)malloc(TC_USER_MAX);
    if(!pMemPack)
    {      
         return TC_ERR_IO;
    }
    
    psPack = (sTcPackCon*)pMemPack;

    /* 2 环境初始化 */
    sInit.eRole = TC_ROLE_CONTOR;
    sInit.ucPermitDelayMinutes = 255;
    eRet = eTcInit(&sInit);
    if(eRet != TC_OK)
    {
        printf("初始化失败\n");
        free(pMemPack);
        return eRet;
    }
    
    /* 3 封装参数 */
    psPack->sAddress.ucConAddress = 1;
    psPack->sAddress.bTeam        = FALSE;
    psPack->sAddress.ulTmlAddress = 1;
    memcpy(psPack->sAddress.acRegionCode, "110000", TC_REGN_LEN);
    psPack->ucPSEQ = 1;
 
    memcpy(psPack->aPw, "0123456789ABCDEF", TC_PW_LEN);

    psPack->usNum = 1;
    psPack->sData[0].eCmd         = TCMD_AFN_5_F5_NX_MODEL_ACT;
    psPack->sData[0].usPN         = 0;
    psPack->sData[0].bApp         = TRUE;

    psPack->sData[0].uApp.sNxModelAct.ucN = 1;
    psPack->sData[0].uApp.sNxModelAct.sOne[0].ucID = 1;
    psPack->sData[0].uApp.sNxModelAct.sOne[0].sTime.ucYY = 14;
    psPack->sData[0].uApp.sNxModelAct.sOne[0].sTime.ucMM = 1;
    psPack->sData[0].uApp.sNxModelAct.sOne[0].sTime.ucWW = 1;
    psPack->sData[0].uApp.sNxModelAct.sOne[0].sTime.ucDD = 13;
    psPack->sData[0].uApp.sNxModelAct.sOne[0].sTime.ucHH = 14;
    psPack->sData[0].uApp.sNxModelAct.sOne[0].sTime.ucmm = 14;
    psPack->sData[0].uApp.sNxModelAct.sOne[0].sTime.ucss = 14;


    /* 4 调用函数 */
    eRet = etcPackCon(psPack, (UINT8*)g_ucOutBuf, &usBuflen);
    if(eRet != TC_OK)
    {
        printf("emcPack() error %d\n", eRet);
        free(pMemPack);
        return eRet;
    }
    
    /* 5 输出结果 */ 
    printf_buffer_color((char*)g_ucOutBuf, usBuflen);
    return TC_OK;
}

/*****************************************************************************
 函 数 名  : test_afn05f6_c2t
 功能描述  : 封装测试例 
 测试命令  : TCMD_AFN_5_F6_NX_MODEL_CLR

 输入参数  : BOOL bActive 是否为主动性

 输出参数  :
 返 回 值  : eTcErr
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月7日 星期二
    作    者   : liming
    修改内容   : 新生成函数
*****************************************************************************/
eTcErr test_afn05f6_c2t(BOOL bActive)
{   
    /*1 声明参数 */
    eTcErr     eRet        = TC_OK;
    UINT16     usBuflen    = 0;
    UINT8      *pMemPack   = NULL;
    sTcPackCon   *psPack   = NULL;
    sTcInit    sInit;
 
    pMemPack = (UINT8*)malloc(TC_USER_MAX);
    if(!pMemPack)
    {      
         return TC_ERR_IO;
    }
    
    psPack = (sTcPackCon*)pMemPack;

    /* 2 环境初始化 */
    sInit.eRole = TC_ROLE_CONTOR;
    sInit.ucPermitDelayMinutes = 255;
    eRet = eTcInit(&sInit);
    if(eRet != TC_OK)
    {
        printf("初始化失败\n");
        free(pMemPack);
        return eRet;
    }
    
    /* 3 封装参数 */
    psPack->sAddress.ucConAddress = 1;
    psPack->sAddress.bTeam        = FALSE;
    psPack->sAddress.ulTmlAddress = 1;
    memcpy(psPack->sAddress.acRegionCode, "110000", TC_REGN_LEN);
    psPack->ucPSEQ = 1;
 
    memcpy(psPack->aPw, "0123456789ABCDEF", TC_PW_LEN);

    psPack->usNum = 1;
    psPack->sData[0].eCmd         = TCMD_AFN_5_F6_NX_MODEL_CLR;
    psPack->sData[0].usPN         = 0;
    psPack->sData[0].bApp         = TRUE;

    psPack->sData[0].uApp.sNxModelClr.ucN = 1;
    psPack->sData[0].uApp.sNxModelClr.ucID[0] = 1;

    
    /* 4 调用函数 */
    eRet = etcPackCon(psPack, (UINT8*)g_ucOutBuf, &usBuflen);
    if(eRet != TC_OK)
    {
        printf("emcPack() error %d\n", eRet);
        free(pMemPack);
        return eRet;
    }
    
    /* 5 输出结果 */ 
    printf_buffer_color((char*)g_ucOutBuf, usBuflen);
    return TC_OK;
}

/*****************************************************************************
 函 数 名  : test_afn05f7_c2t
 功能描述  : 封装测试例 
 测试命令  : TCMD_AFN_5_F7_RQ_RESPN_ACT

 输入参数  : BOOL bActive 是否为主动性

 输出参数  :
 返 回 值  : eTcErr
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月7日 星期二
    作    者   : liming
    修改内容   : 新生成函数
*****************************************************************************/
eTcErr test_afn05f7_c2t(BOOL bActive)
{   
    /*1 声明参数 */
    eTcErr     eRet        = TC_OK;
    UINT16     usBuflen    = 0;
    UINT8      *pMemPack   = NULL;
    sTcPackCon   *psPack   = NULL;
    sTcInit    sInit;
 
    pMemPack = (UINT8*)malloc(TC_USER_MAX);
    if(!pMemPack)
    {      
         return TC_ERR_IO;
    }
    
    psPack = (sTcPackCon*)pMemPack;

    /* 2 环境初始化 */
    sInit.eRole = TC_ROLE_CONTOR;
    sInit.ucPermitDelayMinutes = 255;
    eRet = eTcInit(&sInit);
    if(eRet != TC_OK)
    {
        printf("初始化失败\n");
        free(pMemPack);
        return eRet;
    }
    
    /* 3 封装参数 */
    psPack->sAddress.ucConAddress = 1;
    psPack->sAddress.bTeam        = FALSE;
    psPack->sAddress.ulTmlAddress = 1;
    memcpy(psPack->sAddress.acRegionCode, "110000", TC_REGN_LEN);
    psPack->ucPSEQ = 1;
 
    memcpy(psPack->aPw, "0123456789ABCDEF", TC_PW_LEN);

    psPack->usNum = 1;
    psPack->sData[0].eCmd         = TCMD_AFN_5_F7_RQ_RESPN_ACT;
    psPack->sData[0].usPN         = 0;
    psPack->sData[0].bApp         = TRUE;

    psPack->sData[0].uApp.sRqRespnAct.ucN = 1;
    psPack->sData[0].uApp.sRqRespnAct.ucID[0] = 1;

    /* 4 调用函数 */
    eRet = etcPackCon(psPack, (UINT8*)g_ucOutBuf, &usBuflen);
    if(eRet != TC_OK)
    {
        printf("emcPack() error %d\n", eRet);
        free(pMemPack);
        return eRet;
    }
    
    /* 5 输出结果 */ 
    printf_buffer_color((char*)g_ucOutBuf, usBuflen);
    return TC_OK;
}

/*****************************************************************************
 函 数 名  : test_afn05f8_c2t
 功能描述  : 封装测试例 
 测试命令  : TCMD_AFN_5_F8_RQ_RESPN_CLT

 输入参数  : BOOL bActive 是否为主动性

 输出参数  :
 返 回 值  : eTcErr
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月7日 星期二
    作    者   : liming
    修改内容   : 新生成函数
*****************************************************************************/
eTcErr test_afn05f8_c2t(BOOL bActive)
{   
    /*1 声明参数 */
    eTcErr     eRet        = TC_OK;
    UINT16     usBuflen    = 0;
    UINT8      *pMemPack   = NULL;
    sTcPackCon   *psPack   = NULL;
    sTcInit    sInit;
 
    pMemPack = (UINT8*)malloc(TC_USER_MAX);
    if(!pMemPack)
    {      
         return TC_ERR_IO;
    }
    
    psPack = (sTcPackCon*)pMemPack;

    /* 2 环境初始化 */
    sInit.eRole = TC_ROLE_CONTOR;
    sInit.ucPermitDelayMinutes = 255;
    eRet = eTcInit(&sInit);
    if(eRet != TC_OK)
    {
        printf("初始化失败\n");
        free(pMemPack);
        return eRet;
    }
    
    /* 3 封装参数 */
    psPack->sAddress.ucConAddress = 1;
    psPack->sAddress.bTeam        = FALSE;
    psPack->sAddress.ulTmlAddress = 1;
    memcpy(psPack->sAddress.acRegionCode, "110000", TC_REGN_LEN);
    psPack->ucPSEQ = 1;
 
    memcpy(psPack->aPw, "0123456789ABCDEF", TC_PW_LEN);

    psPack->usNum = 1;
    psPack->sData[0].eCmd         = TCMD_AFN_5_F8_RQ_RESPN_CLT;
    psPack->sData[0].usPN         = 0;
    psPack->sData[0].bApp         = TRUE;

    psPack->sData[0].uApp.sRqRespnClr.ucN = 1;
    psPack->sData[0].uApp.sRqRespnClr.ucID[0] = 1;

    /* 4 调用函数 */
    eRet = etcPackCon(psPack, (UINT8*)g_ucOutBuf, &usBuflen);
    if(eRet != TC_OK)
    {
        printf("emcPack() error %d\n", eRet);
        free(pMemPack);
        return eRet;
    }
    
    /* 5 输出结果 */ 
    printf_buffer_color((char*)g_ucOutBuf, usBuflen);
    return TC_OK;
}

/*****************************************************************************
 函 数 名  : test_afn05f9_c2t
 功能描述  : 封装测试例 
 测试命令  : TCMD_AFN_5_F9_REPT_FREZ_ON

 输入参数  : BOOL bActive 是否为主动性

 输出参数  :
 返 回 值  : eTcErr
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月7日 星期二
    作    者   : liming
    修改内容   : 新生成函数
*****************************************************************************/
eTcErr test_afn05f9_c2t(BOOL bActive)
{   
    /*1 声明参数 */
    eTcErr     eRet        = TC_OK;
    UINT16     usBuflen    = 0;
    UINT8      *pMemPack   = NULL;
    sTcPackCon   *psPack   = NULL;
    sTcInit    sInit;
 
    pMemPack = (UINT8*)malloc(TC_USER_MAX);
    if(!pMemPack)
    {      
         return TC_ERR_IO;
    }
    
    psPack = (sTcPackCon*)pMemPack;

    /* 2 环境初始化 */
    sInit.eRole = TC_ROLE_CONTOR;
    sInit.ucPermitDelayMinutes = 255;
    eRet = eTcInit(&sInit);
    if(eRet != TC_OK)
    {
        printf("初始化失败\n");
        free(pMemPack);
        return eRet;
    }
    
    /* 3 封装参数 */
    psPack->sAddress.ucConAddress = 1;
    psPack->sAddress.bTeam        = FALSE;
    psPack->sAddress.ulTmlAddress = 1;
    memcpy(psPack->sAddress.acRegionCode, "110000", TC_REGN_LEN);
    psPack->ucPSEQ = 1;
 
    memcpy(psPack->aPw, "0123456789ABCDEF", TC_PW_LEN);

    psPack->usNum = 1;
    psPack->sData[0].eCmd         = TCMD_AFN_5_F9_REPT_FREZ_ON;
    psPack->sData[0].usPN         = 0;
    psPack->sData[0].bApp         = FALSE;


    /* 4 调用函数 */
    eRet = etcPackCon(psPack, (UINT8*)g_ucOutBuf, &usBuflen);
    if(eRet != TC_OK)
    {
        printf("emcPack() error %d\n", eRet);
        free(pMemPack);
        return eRet;
    }
    
    /* 5 输出结果 */ 
    printf_buffer_color((char*)g_ucOutBuf, usBuflen);
    return TC_OK;
}


/*****************************************************************************
 函 数 名  : test_afn05f10_c2t
 功能描述  : 封装测试例 
 测试命令  : TCMD_AFN_5_F10_REPT_FREZ_OFF

 输入参数  : BOOL bActive 是否为主动性

 输出参数  :
 返 回 值  : eTcErr
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月7日 星期二
    作    者   : liming
    修改内容   : 新生成函数
*****************************************************************************/
eTcErr test_afn05f10_c2t(BOOL bActive)
{   
    /*1 声明参数 */
    eTcErr     eRet        = TC_OK;
    UINT16     usBuflen    = 0;
    UINT8      *pMemPack   = NULL;
    sTcPackCon   *psPack   = NULL;
    sTcInit    sInit;
 
    pMemPack = (UINT8*)malloc(TC_USER_MAX);
    if(!pMemPack)
    {      
         return TC_ERR_IO;
    }
    
    psPack = (sTcPackCon*)pMemPack;

    /* 2 环境初始化 */
    sInit.eRole = TC_ROLE_CONTOR;
    sInit.ucPermitDelayMinutes = 255;
    eRet = eTcInit(&sInit);
    if(eRet != TC_OK)
    {
        printf("初始化失败\n");
        free(pMemPack);
        return eRet;
    }
    
    /* 3 封装参数 */
    psPack->sAddress.ucConAddress = 1;
    psPack->sAddress.bTeam        = FALSE;
    psPack->sAddress.ulTmlAddress = 1;
    memcpy(psPack->sAddress.acRegionCode, "110000", TC_REGN_LEN);
    psPack->ucPSEQ = 1;
 
    memcpy(psPack->aPw, "0123456789ABCDEF", TC_PW_LEN);

    psPack->usNum = 1;
    psPack->sData[0].eCmd         = TCMD_AFN_5_F10_REPT_FREZ_OFF;
    psPack->sData[0].usPN         = 0;
    psPack->sData[0].bApp         = FALSE;


    /* 4 调用函数 */
    eRet = etcPackCon(psPack, (UINT8*)g_ucOutBuf, &usBuflen);
    if(eRet != TC_OK)
    {
        printf("emcPack() error %d\n", eRet);
        free(pMemPack);
        return eRet;
    }
    
    /* 5 输出结果 */ 
    printf_buffer_color((char*)g_ucOutBuf, usBuflen);
    return TC_OK;
}

/*****************************************************************************
 函 数 名  : test_afn05f17_c2t
 功能描述  : 封装测试例 
 测试命令  : TCMD_AFN_5_F17_REMOTE_OFF

 输入参数  : BOOL bActive 是否为主动性

 输出参数  :
 返 回 值  : eTcErr
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月7日 星期二
    作    者   : liming
    修改内容   : 新生成函数
*****************************************************************************/
eTcErr test_afn05f17_c2t(BOOL bActive)
{   
    /*1 声明参数 */
    eTcErr     eRet        = TC_OK;
    UINT16     usBuflen    = 0;
    UINT8      *pMemPack   = NULL;
    sTcPackCon   *psPack   = NULL;
    sTcInit    sInit;
 
    pMemPack = (UINT8*)malloc(TC_USER_MAX);
    if(!pMemPack)
    {      
         return TC_ERR_IO;
    }
    
    psPack = (sTcPackCon*)pMemPack;

    /* 2 环境初始化 */
    sInit.eRole = TC_ROLE_CONTOR;
    sInit.ucPermitDelayMinutes = 255;
    eRet = eTcInit(&sInit);
    if(eRet != TC_OK)
    {
        printf("初始化失败\n");
        free(pMemPack);
        return eRet;
    }
    
    /* 3 封装参数 */
    psPack->sAddress.ucConAddress = 1;
    psPack->sAddress.bTeam        = FALSE;
    psPack->sAddress.ulTmlAddress = 1;
    memcpy(psPack->sAddress.acRegionCode, "110000", TC_REGN_LEN);
    psPack->ucPSEQ = 1;
 
    memcpy(psPack->aPw, "0123456789ABCDEF", TC_PW_LEN);

    psPack->usNum = 1;
    psPack->sData[0].eCmd         = TCMD_AFN_5_F17_REMOTE_OFF;
    psPack->sData[0].usPN         = 110;
    psPack->sData[0].bApp         = FALSE;

    int i = 0;
    for(i = 0; i < 8; i++)
    {
        psPack->sData[0].uApp.sRemoteOff.bOff[i]  = TRUE;
    }

    psPack->sData[0].uApp.sRemoteOff.sTimeStart.ucYY = 14;
    psPack->sData[0].uApp.sRemoteOff.sTimeStart.ucMM = 1;
    psPack->sData[0].uApp.sRemoteOff.sTimeStart.ucDD = 14;
    psPack->sData[0].uApp.sRemoteOff.sTimeStart.ucHH = 9;
    psPack->sData[0].uApp.sRemoteOff.sTimeStart.ucmm = 18;


    psPack->sData[0].uApp.sRemoteOff.sTimeEnd.ucYY = 14;
    psPack->sData[0].uApp.sRemoteOff.sTimeEnd.ucMM = 1;
    psPack->sData[0].uApp.sRemoteOff.sTimeEnd.ucDD = 14;
    psPack->sData[0].uApp.sRemoteOff.sTimeEnd.ucHH = 19;
    psPack->sData[0].uApp.sRemoteOff.sTimeEnd.ucmm = 28;  


    /* 4 调用函数 */
    eRet = etcPackCon(psPack, (UINT8*)g_ucOutBuf, &usBuflen);
    if(eRet != TC_OK)
    {
        printf("emcPack() error %d\n", eRet);
        free(pMemPack);
        return eRet;
    }
    
    /* 5 输出结果 */ 
    printf_buffer_color((char*)g_ucOutBuf, usBuflen);
    return TC_OK;
}

/*****************************************************************************
 函 数 名  : test_afn05f18_c2t
 功能描述  : 封装测试例 
 测试命令  : TCMD_AFN_5_F18_REMOTE_ON

 输入参数  : BOOL bActive 是否为主动性

 输出参数  :
 返 回 值  : eTcErr
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月7日 星期二
    作    者   : liming
    修改内容   : 新生成函数
*****************************************************************************/
eTcErr test_afn05f18_c2t(BOOL bActive)
{   
    /*1 声明参数 */
    eTcErr     eRet        = TC_OK;
    UINT16     usBuflen    = 0;
    UINT8      *pMemPack   = NULL;
    sTcPackCon   *psPack   = NULL;
    sTcInit    sInit;
 
    pMemPack = (UINT8*)malloc(TC_USER_MAX);
    if(!pMemPack)
    {      
         return TC_ERR_IO;
    }
    
    psPack = (sTcPackCon*)pMemPack;

    /* 2 环境初始化 */
    sInit.eRole = TC_ROLE_CONTOR;
    sInit.ucPermitDelayMinutes = 255;
    eRet = eTcInit(&sInit);
    if(eRet != TC_OK)
    {
        printf("初始化失败\n");
        free(pMemPack);
        return eRet;
    }
    
    /* 3 封装参数 */
    psPack->sAddress.ucConAddress = 1;
    psPack->sAddress.bTeam        = FALSE;
    psPack->sAddress.ulTmlAddress = 1;
    memcpy(psPack->sAddress.acRegionCode, "110000", TC_REGN_LEN);
    psPack->ucPSEQ = 1;
 
    memcpy(psPack->aPw, "0123456789ABCDEF", TC_PW_LEN);

    psPack->usNum = 1;
    psPack->sData[0].eCmd         = TCMD_AFN_5_F18_REMOTE_ON;
    psPack->sData[0].usPN         = 0;
    psPack->sData[0].bApp         = TRUE;
    
    int i = 0;
    for(i = 0; i < 8; i++)
    {
        psPack->sData[0].uApp.sRemoteOn.bOn[i]  = TRUE;
    }


    /* 4 调用函数 */
    eRet = etcPackCon(psPack, (UINT8*)g_ucOutBuf, &usBuflen);
    if(eRet != TC_OK)
    {
        printf("emcPack() error %d\n", eRet);
        free(pMemPack);
        return eRet;
    }
    
    /* 5 输出结果 */ 
    printf_buffer_color((char*)g_ucOutBuf, usBuflen);
    return TC_OK;
}


/*****************************************************************************
 函 数 名  : test_afn10f1_c2t
 功能描述  : 封装测试例 
 测试命令  : TCMD_AFN_A_F1_CON_IP_PORT

 输入参数  : BOOL bActive 是否为主动性

 输出参数  :
 返 回 值  : eTcErr
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月7日 星期二
    作    者   : liming
    修改内容   : 新生成函数
*****************************************************************************/
eTcErr test_afn10f1_c2t(BOOL bActive)
{   
    /*1 声明参数 */
    eTcErr     eRet        = TC_OK;
    UINT16     usBuflen    = 0;
    UINT8      *pMemPack   = NULL;
    sTcPackCon   *psPack   = NULL;
    sTcInit    sInit;
 
    pMemPack = (UINT8*)malloc(TC_USER_MAX);
    if(!pMemPack)
    {      
         return TC_ERR_IO;
    }
    
    psPack = (sTcPackCon*)pMemPack;

    /* 2 环境初始化 */
    sInit.eRole = TC_ROLE_CONTOR;
    sInit.ucPermitDelayMinutes = 255;
    eRet = eTcInit(&sInit);
    if(eRet != TC_OK)
    {
        printf("初始化失败\n");
        free(pMemPack);
        return eRet;
    }
    
    /* 3 封装参数 */
    psPack->sAddress.ucConAddress = 1;
    psPack->sAddress.bTeam        = FALSE;
    psPack->sAddress.ulTmlAddress = 1;
    memcpy(psPack->sAddress.acRegionCode, "110000", TC_REGN_LEN);
    psPack->ucPSEQ = 1;
 
    memcpy(psPack->aPw, "0123456789ABCDEF", TC_PW_LEN);

    psPack->usNum = 1;
    psPack->sData[0].eCmd         = TCMD_AFN_A_F1_CON_IP_PORT;
    psPack->sData[0].usPN         = 0;
    psPack->sData[0].bApp         = FALSE;
    


    /* 4 调用函数 */
    eRet = etcPackCon(psPack, (UINT8*)g_ucOutBuf, &usBuflen);
    if(eRet != TC_OK)
    {
        printf("emcPack() error %d\n", eRet);
        free(pMemPack);
        return eRet;
    }
    
    /* 5 输出结果 */ 
    printf_buffer_color((char*)g_ucOutBuf, usBuflen);
    return TC_OK;
}

/*****************************************************************************
 函 数 名  : test_afn10f2_c2t
 功能描述  : 封装测试例 
 测试命令  : TCMD_AFN_A_F2_TML_UP_CFG

 输入参数  : BOOL bActive 是否为主动性

 输出参数  :
 返 回 值  : eTcErr
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月7日 星期二
    作    者   : liming
    修改内容   : 新生成函数
*****************************************************************************/
eTcErr test_afn10f2_c2t(BOOL bActive)
{   
    /*1 声明参数 */
    eTcErr     eRet        = TC_OK;
    UINT16     usBuflen    = 0;
    UINT8      *pMemPack   = NULL;
    sTcPackCon   *psPack   = NULL;
    sTcInit    sInit;
 
    pMemPack = (UINT8*)malloc(TC_USER_MAX);
    if(!pMemPack)
    {      
         return TC_ERR_IO;
    }
    
    psPack = (sTcPackCon*)pMemPack;

    /* 2 环境初始化 */
    sInit.eRole = TC_ROLE_CONTOR;
    sInit.ucPermitDelayMinutes = 255;
    eRet = eTcInit(&sInit);
    if(eRet != TC_OK)
    {
        printf("初始化失败\n");
        free(pMemPack);
        return eRet;
    }
    
    /* 3 封装参数 */
    psPack->sAddress.ucConAddress = 1;
    psPack->sAddress.bTeam        = FALSE;
    psPack->sAddress.ulTmlAddress = 1;
    memcpy(psPack->sAddress.acRegionCode, "110000", TC_REGN_LEN);
    psPack->ucPSEQ = 1;
 
    memcpy(psPack->aPw, "0123456789ABCDEF", TC_PW_LEN);

    psPack->usNum = 1;
    psPack->sData[0].eCmd         = TCMD_AFN_A_F2_TML_UP_CFG;
    psPack->sData[0].usPN         = 0;
    psPack->sData[0].bApp         = TRUE;

    // 配置参数
    psPack->sData[0].uApp.sTmlUpCfg.usListenPort = 1;

    // sUpIp
    psPack->sData[0].uApp.sTmlUpCfg.sUpIp.eVersion = TC_IP_V4;
    psPack->sData[0].uApp.sTmlUpCfg.sUpIp.ip[0]  = 192;
    psPack->sData[0].uApp.sTmlUpCfg.sUpIp.ip[1]  = 168;
    psPack->sData[0].uApp.sTmlUpCfg.sUpIp.ip[2]  = 1;
    psPack->sData[0].uApp.sTmlUpCfg.sUpIp.ip[3]  = 2;

    // sUpMask
    psPack->sData[0].uApp.sTmlUpCfg.sUpMask.eVersion = TC_IP_V4;
    psPack->sData[0].uApp.sTmlUpCfg.sUpMask.ip[0]  = 255;
    psPack->sData[0].uApp.sTmlUpCfg.sUpMask.ip[1]  = 255;
    psPack->sData[0].uApp.sTmlUpCfg.sUpMask.ip[2]  = 255;
    psPack->sData[0].uApp.sTmlUpCfg.sUpMask.ip[3]  = 0;

    // sGateIp
    psPack->sData[0].uApp.sTmlUpCfg.sGateIp.eVersion = TC_IP_V4;
    psPack->sData[0].uApp.sTmlUpCfg.sGateIp.ip[0]  = 192;
    psPack->sData[0].uApp.sTmlUpCfg.sGateIp.ip[1]  = 168;
    psPack->sData[0].uApp.sTmlUpCfg.sGateIp.ip[2]  = 1;
    psPack->sData[0].uApp.sTmlUpCfg.sGateIp.ip[3]  = 1;

    // eDelegate
    psPack->sData[0].uApp.sTmlUpCfg.eDelegate  = TC_DELG_HTTP;

    // sDelgIp
    psPack->sData[0].uApp.sTmlUpCfg.sDelgIp.eVersion = TC_IP_V4;
    psPack->sData[0].uApp.sTmlUpCfg.sDelgIp.ip[0]  = 192;
    psPack->sData[0].uApp.sTmlUpCfg.sDelgIp.ip[1]  = 168;
    psPack->sData[0].uApp.sTmlUpCfg.sDelgIp.ip[2]  = 1;
    psPack->sData[0].uApp.sTmlUpCfg.sDelgIp.ip[3]  = 2;

    // usDelgPort
    psPack->sData[0].uApp.sTmlUpCfg.usDelgPort  = 123;
    psPack->sData[0].uApp.sTmlUpCfg.eDelgLink   = TC_DELK_USRPWD;
    
    psPack->sData[0].uApp.sTmlUpCfg.bDlegUsr  = TRUE;
    psPack->sData[0].uApp.sTmlUpCfg.ucDlegUsrLen  = 16;
    memcpy(psPack->sData[0].uApp.sTmlUpCfg.ucDlegUsr, "1234567890abcdef", 16);

    
    psPack->sData[0].uApp.sTmlUpCfg.bDlegPwd  = TRUE;
    psPack->sData[0].uApp.sTmlUpCfg.ucDlegPwdLen  = 16;
    memcpy(psPack->sData[0].uApp.sTmlUpCfg.ucDlegPwd, "1234567890abcdef", 16);

    psPack->sData[0].uApp.sTmlUpCfg.ucPermitDelayM  = 123;
    psPack->sData[0].uApp.sTmlUpCfg.ucReSendTimes   = 3;
    psPack->sData[0].uApp.sTmlUpCfg.ucHeartBeat     = 1;
    psPack->sData[0].uApp.sTmlUpCfg.usWaitTimeoutS  = 1234;
    psPack->sData[0].uApp.sTmlUpCfg.bPermitTk       = TRUE;
    psPack->sData[0].uApp.sTmlUpCfg.bPermitEv       = TRUE;

    /* 4 调用函数 */
    eRet = etcPackCon(psPack, (UINT8*)g_ucOutBuf, &usBuflen);
    if(eRet != TC_OK)
    {
        printf("emcPack() error %d\n", eRet);
        free(pMemPack);
        return eRet;
    }
    
    /* 5 输出结果 */ 
    printf_buffer_color((char*)g_ucOutBuf, usBuflen);
    return TC_OK;
}

/*****************************************************************************
 函 数 名  : test_afn10f1_t2c
 功能描述  : 封装测试例 
 测试命令  : TCMD_AFN_A_F1_CON_IP_PORT

 输入参数  : BOOL bActive 是否为主动性

 输出参数  :
 返 回 值  : eTcErr
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月7日 星期二
    作    者   : liming
    修改内容   : 新生成函数
*****************************************************************************/
eTcErr test_afn10f1_t2c(BOOL bActive)
{   
    /*1 声明参数 */
    eTcErr     eRet        = TC_OK;
    UINT16     usBuflen    = 0;
    UINT8      *pMemPack   = NULL;
    sTcPackTml  *psPack     = NULL;
    sTcInit    sInit;
 
    pMemPack = (UINT8*)malloc(TC_USER_MAX);
    if(!pMemPack)
    {      
        return TC_ERR_IO;
    }
   
    psPack = (sTcPackTml*)pMemPack;

    /* 2 环境初始化 */
    sInit.eRole = TC_ROLE_TERMIN;
    sInit.ucPermitDelayMinutes = 255;
    eRet = eTcInit(&sInit);
    if(eRet != TC_OK)
    {
        printf("初始化失败\n");
        free(pMemPack);
        return eRet;
    }
    
    /* 3 封装参数 */
    psPack->sAddress.ucConAddress = 1;
    psPack->sAddress.bTeam        = FALSE;
    psPack->sAddress.ulTmlAddress = 1;
    memcpy(psPack->sAddress.acRegionCode, "110000", TC_REGN_LEN);

    psPack->bActive = TRUE;
    psPack->bReSend = FALSE;

    psPack->usNum = 1;
    psPack->sData[0].eCmd         = TCMD_AFN_A_F1_CON_IP_PORT;
    psPack->sData[0].usPN         = 0;
    psPack->sData[0].bApp         = TRUE;

     // 数据参数
    psPack->sData[0].uApp.sDownCfg.sMainIp.eVersion = TC_IP_V4;
    psPack->sData[0].uApp.sDownCfg.sMainIp.ip[0] = 192;
    psPack->sData[0].uApp.sDownCfg.sMainIp.ip[1] = 168;
    psPack->sData[0].uApp.sDownCfg.sMainIp.ip[2] = 10;
    psPack->sData[0].uApp.sDownCfg.sMainIp.ip[3] = 1;
    
    psPack->sData[0].uApp.sDownCfg.usMainPort = 6666;

    psPack->sData[0].uApp.sDownCfg.sBackIp.eVersion = TC_IP_V4;
    psPack->sData[0].uApp.sDownCfg.sBackIp.ip[0] = 192;
    psPack->sData[0].uApp.sDownCfg.sBackIp.ip[1] = 168;
    psPack->sData[0].uApp.sDownCfg.sBackIp.ip[2] = 10;
    psPack->sData[0].uApp.sDownCfg.sBackIp.ip[3] = 2;
    
    psPack->sData[0].uApp.sDownCfg.usBackPort = 7777;

    memcpy(&(psPack->sData[0].uApp.sDownCfg.ucAPN[0]), "0123456789ABCDEF", TC_APN_LEN);
    memcpy(&(psPack->sData[0].uApp.sDownCfg.ucUsr[0]), "0123456789ABCDEF0123456789ABCDEF", 32);
    memcpy(&(psPack->sData[0].uApp.sDownCfg.ucPwd[0]), "0123456789ABCDEF0123456789ABCDEF", 32); 

    /* 4 调用函数 */
    eRet = etcPackTml(psPack, (UINT8*)g_ucOutBuf, &usBuflen);
    if(eRet != TC_OK)
    {
        printf("emcPack() error %d\n", eRet);
        free(pMemPack);
        return eRet;
    }
    
    /* 5 输出结果 */ 
    printf_buffer_color((char*)g_ucOutBuf, usBuflen);
    return TC_OK;
}


/*****************************************************************************
 函 数 名  : test_afn10f2_t2c
 功能描述  : 封装测试例 
 测试命令  : TCMD_AFN_A_F2_TML_UP_CFG

 输入参数  : BOOL bActive 是否为主动性

 输出参数  :
 返 回 值  : eTcErr
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月20日 星期一
    作    者   : liming
    修改内容   : 新生成函数
*****************************************************************************/
eTcErr test_afn10f2_t2c(BOOL bActive)
{   
    /*1 声明参数 */
    eTcErr     eRet        = TC_OK;
    UINT16     usBuflen    = 0;
    UINT8      *pMemPack   = NULL;
    sTcPackTml  *psPack     = NULL;
    sTcInit    sInit;
 
    pMemPack = (UINT8*)malloc(TC_USER_MAX);
    if(!pMemPack)
    {      
        return TC_ERR_IO;
    }
   
    psPack = (sTcPackTml*)pMemPack;

    /* 2 环境初始化 */
    sInit.eRole = TC_ROLE_TERMIN;
    sInit.ucPermitDelayMinutes = 255;
    eRet = eTcInit(&sInit);
    if(eRet != TC_OK)
    {
        printf("初始化失败\n");
        free(pMemPack);
        return eRet;
    }
    
    /* 3 封装参数 */
    psPack->sAddress.ucConAddress = 1;
    psPack->sAddress.bTeam        = FALSE;
    psPack->sAddress.ulTmlAddress = 1;
    memcpy(psPack->sAddress.acRegionCode, "110000", TC_REGN_LEN);

    psPack->bActive = TRUE;
    psPack->bReSend = FALSE;

    psPack->usNum = 1;
    psPack->sData[0].eCmd         = TCMD_AFN_A_F2_TML_UP_CFG;
    psPack->sData[0].usPN         = 0;
    psPack->sData[0].bApp         = TRUE;

     // 数据参数
    psPack->sData[0].uApp.sTmlUpCfg.usListenPort = 1;

    // sUpIp
    psPack->sData[0].uApp.sTmlUpCfg.sUpIp.eVersion = TC_IP_V4;
    psPack->sData[0].uApp.sTmlUpCfg.sUpIp.ip[0]  = 192;
    psPack->sData[0].uApp.sTmlUpCfg.sUpIp.ip[1]  = 168;
    psPack->sData[0].uApp.sTmlUpCfg.sUpIp.ip[2]  = 1;
    psPack->sData[0].uApp.sTmlUpCfg.sUpIp.ip[3]  = 2;

    // sUpMask
    psPack->sData[0].uApp.sTmlUpCfg.sUpMask.eVersion = TC_IP_V4;
    psPack->sData[0].uApp.sTmlUpCfg.sUpMask.ip[0]  = 255;
    psPack->sData[0].uApp.sTmlUpCfg.sUpMask.ip[1]  = 255;
    psPack->sData[0].uApp.sTmlUpCfg.sUpMask.ip[2]  = 255;
    psPack->sData[0].uApp.sTmlUpCfg.sUpMask.ip[3]  = 0;

    // sGateIp
    psPack->sData[0].uApp.sTmlUpCfg.sGateIp.eVersion = TC_IP_V4;
    psPack->sData[0].uApp.sTmlUpCfg.sGateIp.ip[0]  = 192;
    psPack->sData[0].uApp.sTmlUpCfg.sGateIp.ip[1]  = 168;
    psPack->sData[0].uApp.sTmlUpCfg.sGateIp.ip[2]  = 1;
    psPack->sData[0].uApp.sTmlUpCfg.sGateIp.ip[3]  = 1;

    // eDelegate
    psPack->sData[0].uApp.sTmlUpCfg.eDelegate  = TC_DELG_HTTP;

    // sDelgIp
    psPack->sData[0].uApp.sTmlUpCfg.sDelgIp.eVersion = TC_IP_V4;
    psPack->sData[0].uApp.sTmlUpCfg.sDelgIp.ip[0]  = 192;
    psPack->sData[0].uApp.sTmlUpCfg.sDelgIp.ip[1]  = 168;
    psPack->sData[0].uApp.sTmlUpCfg.sDelgIp.ip[2]  = 1;
    psPack->sData[0].uApp.sTmlUpCfg.sDelgIp.ip[3]  = 2;

    // usDelgPort
    psPack->sData[0].uApp.sTmlUpCfg.usDelgPort  = 123;
    psPack->sData[0].uApp.sTmlUpCfg.eDelgLink   = TC_DELK_USRPWD;
    
    psPack->sData[0].uApp.sTmlUpCfg.bDlegUsr  = TRUE;
    psPack->sData[0].uApp.sTmlUpCfg.ucDlegUsrLen  = 16;
    memcpy(psPack->sData[0].uApp.sTmlUpCfg.ucDlegUsr, "1234567890abcdef", 16);

    
    psPack->sData[0].uApp.sTmlUpCfg.bDlegPwd  = TRUE;
    psPack->sData[0].uApp.sTmlUpCfg.ucDlegPwdLen  = 16;
    memcpy(psPack->sData[0].uApp.sTmlUpCfg.ucDlegPwd, "1234567890abcdef", 16);

    psPack->sData[0].uApp.sTmlUpCfg.ucPermitDelayM  = 123;
    psPack->sData[0].uApp.sTmlUpCfg.ucReSendTimes   = 3;
    psPack->sData[0].uApp.sTmlUpCfg.ucHeartBeat     = 1;
    psPack->sData[0].uApp.sTmlUpCfg.usWaitTimeoutS  = 1234;
    psPack->sData[0].uApp.sTmlUpCfg.bPermitTk       = TRUE;
    psPack->sData[0].uApp.sTmlUpCfg.bPermitEv       = TRUE;
 

    /* 4 调用函数 */
    eRet = etcPackTml(psPack, (UINT8*)g_ucOutBuf, &usBuflen);
    if(eRet != TC_OK)
    {
        printf("emcPack() error %d\n", eRet);
        free(pMemPack);
        return eRet;
    }
    
    /* 5 输出结果 */ 
    printf_buffer_color((char*)g_ucOutBuf, usBuflen);
    return TC_OK;
}



// 测试例列表
const sTestPack g_test_pack[] =
{
    {TCMD_AFN_0_F1_ALL_OK_DENY,    test_afn00f1_c2t,   test_afn00f1_t2c},
    {TCMD_AFN_0_F2_ONE_BY_ONE,     test_afn00f1_c2t,   test_afn00f1_c2t},

    {TCMD_AFN_1_F1_HARD_INIT,      test_afn01f1_c2t,   NULL},
    {TCMD_AFN_1_F2_DATA_INIT,      test_afn01f2_c2t,   NULL},
    {TCMD_AFN_1_F3_FACTORY_RESET,  test_afn01f3_c2t,   NULL},
    {TCMD_AFN_1_F4_PARA_INIT,      test_afn01f4_c2t,   NULL},
    {TCMD_AFN_1_F5_DATA_CLEAR,      NULL,   NULL},      // 暂时没有实现该功能,省级主站也没有实现该功能
    
    {TCMD_AFN_2_F1_LOG_IN,          NULL,              test_afn02f1_t2c},
    {TCMD_AFN_2_F2_LOG_OUT,         NULL,              test_afn02f2_t2c},
    {TCMD_AFN_2_F3_HEART_BEAT,      NULL,              test_afn02f3_t2c},
    {TCMD_AFN_2_F4_LINK_OK,         test_afn02f4_c2t,              NULL},

    // 设置参数
    {TCMD_AFN_4_F1_CON_IP_PORT,     test_afn04f1_c2t,              NULL},
    {TCMD_AFN_4_F2_TML_UP_CFG,      test_afn04f2_c2t,              NULL},
    {TCMD_AFN_4_F3_TML_AUTH_PARA,   test_afn04f3_c2t,              NULL},
    {TCMD_AFN_4_F4_TML_STATE_INPUT, test_afn04f4_c2t,              NULL},
    {TCMD_AFN_4_F5_TML_EVENT_CFG,   test_afn04f5_c2t,              NULL},
    {TCMD_AFN_4_F17_FREZ_TASK_PARA, test_afn04f17_c2t,             NULL},
    {TCMD_AFN_4_F25_ELEC_MP_CFG,    test_afn04f25_c2t,             NULL},

    // 控制命令
    {TCMD_AFN_5_F1_CHECK_TIME,      test_afn05f1_c2t,              NULL},
    {TCMD_AFN_5_F3_AUTO_SAY_ON,     test_afn05f3_c2t,              NULL},
    {TCMD_AFN_5_F4_AUTO_SAY_OFF,    test_afn05f4_c2t,              NULL},
    {TCMD_AFN_5_F5_NX_MODEL_ACT,    test_afn05f5_c2t,              NULL},
    {TCMD_AFN_5_F6_NX_MODEL_CLR,    test_afn05f6_c2t,              NULL},
    {TCMD_AFN_5_F7_RQ_RESPN_ACT,    test_afn05f7_c2t,              NULL},
    {TCMD_AFN_5_F8_RQ_RESPN_CLT,    test_afn05f8_c2t,              NULL},
    {TCMD_AFN_5_F9_REPT_FREZ_ON,    test_afn05f9_c2t,              NULL},
    {TCMD_AFN_5_F10_REPT_FREZ_OFF,  test_afn05f10_c2t,             NULL},
    {TCMD_AFN_5_F17_REMOTE_OFF,     test_afn05f17_c2t,             NULL},
    {TCMD_AFN_5_F18_REMOTE_ON,      test_afn05f18_c2t,             NULL},

    // 查询参数
    {TCMD_AFN_A_F1_CON_IP_PORT,     test_afn10f1_c2t,    test_afn10f1_t2c},
    {TCMD_AFN_A_F2_TML_UP_CFG,      test_afn10f2_c2t,    test_afn10f2_t2c},
    {TCMD_AFN_A_F2_TML_UP_CFG,      test_afn10f1_c2t,    test_afn10f2_t2c},


    







    // 在这之上添加测试用例
    {0xFFFF, NULL, NULL}

};



// 测试例运行函数
void run_pack_test(int iTest, BOOL bActive, BOOL bM2S)
{
    pTestFunc   pTest = NULL;
    int i = 0;
    int count = 0;
    eTcErr eRet = TC_OK;
    //char *pErrText = NULL;
    count = sizeof(g_test_pack) / sizeof(sTestPack);

    for(i = 0; i < count; i++)
    {
        if(g_test_pack[i].nTestCmd == iTest)
        {
            if(TRUE == bM2S)
            {
                pTest = g_test_pack[i].pTestM2S;
            }
            else
            {
                pTest = g_test_pack[i].pTestS2M;
            }

            break;
        }
    }

    // 调用测试例函数
    if(pTest!= NULL)
    {
        eRet = pTest(bActive);
        if(eRet != TC_OK)
        {
            //pErrText = stcGetErr(eRet);
            //show_error(pErrText);
            printf("eRet = %d\n", eRet);
        }
    }
    else
    {
       show_error("尚不支持的命令或没有添加该测试\n");

    }

}
/*****************************************************************************
 函 数 名  : unpack_analyse
 功能描述  : 帧方式解析报文,并显示解析结果

 输入参数  :  报文的十六进制 字节格式序列(68 10 10 68... 16)

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月7日 星期二
    作    者   : liming
    修改内容   : 新生成函数
*****************************************************************************/
void unpack_analyse(int nstart, int argc, char *argv[])
{
    INT32    i, j     = 0;
    UINT16   usLen    = 0;
    BOOL     bFixed   = FALSE;
    eTcErr   eRet     = TC_OK;
    UINT8   *pInBuf   = NULL;
    UINT8    ucTemp   = 0;
    UINT8    *pucTmp  = NULL;
    char     *pstr    = NULL;
    char     ac[8]    = {0};
    sTcfHeadFixed *psHeadFixed    = NULL;
    sTcfHeadAlter *psHeadAlter    = NULL;
    sTcPackCommon sUnpackCom;
    sTcmdInfor    sCmdInfor   = {0};

    for(i = nstart; i < argc; i++)
    {
        g_ucInBuf[j++] = strtol(argv[i], NULL,16);
    }

    usLen    = argc - nstart;
    pInBuf   = (UINT8*)g_ucInBuf;

    eRet = etc_unpack_common(&sUnpackCom, pInBuf, usLen);
    if(TC_OK != eRet)
    {
        printf("etc_unpack_common() error %d", eRet);
        return;
    }

    bFixed = sUnpackCom.bFixed;
    psHeadFixed = (sTcfHeadFixed *)pInBuf;
    psHeadAlter = (sTcfHeadAlter *)pInBuf;
    
    fm_print("--------------------------analyse success-------------------------\n",FR_GREEN);
    show_main_name("起始字符:\t");
    show_sub_name("  S:");

    if(bFixed == TRUE)
    {
        printf("[%02X]\t\t", psHeadFixed->f10);
        show_item_value("固定帧");
        printf("\n");
    }
    else
    {
        printf("[%02X]\t\t", psHeadAlter->f68);
        show_item_value("可变帧");

        // L1 
        printf("\n");
        show_main_name("长 度 域:");
        printf("\t ");
        show_sub_name("L1:"); 
        pucTmp = &(psHeadAlter->f68);
        printf("[%02X %02X]", *(pucTmp + 1), *(pucTmp + 2));
        printf("\t%d\t", psHeadAlter->usL1);


        // L2   
        printf("\n\t\t ");
        show_sub_name("L2:");
        printf("[%02X %02X]", *(pucTmp + 3), *(pucTmp + 4));
        printf("\t%d\n", psHeadAlter->usL2);

        // s68
        show_main_name("起始字符:");
        printf("\t    [%02X]\n", psHeadAlter->s68);
        
    }

    // 控制域        
    
    show_main_name("控 制 域:\t");
    show_sub_name("  C:");
    pucTmp = (UINT8*)&(psHeadFixed->usC);
    printf("[%02X %02X]\t\t", *pucTmp, *(pucTmp + 1));

    show_item_value("报文方向");
    printf("\t%s\n", sUnpackCom.sCtrl.eDir == TC_DIR_C2T ? "集中器->终端":"终端->集中器");
    printf("\t\t\t\t\t");
    show_item_value("启动方向");
    printf("\t%s\n", sUnpackCom.sCtrl.ePRM == TC_PRM_A2P ? "启动->从动":"从动->启动");

    printf("\t\t\t\t\t");
    show_item_value("启动帧序号");
    printf("\t%d\n", sUnpackCom.sCtrl.ucPSEQ);

    printf("\t\t\t\t\t");
    show_item_value("响应帧序列");
    printf("\t%d\n", sUnpackCom.sCtrl.ucRSEQ);

    printf("\t\t\t\t\t");
    show_item_value("帧功能码");
    printf("\t%d ", sUnpackCom.sCtrl.eFcode);

    if(bFixed == TRUE)
    {
        switch(sUnpackCom.sCtrl.eFcode)
        {
            case TC_FCD_LINK_OK:
            pstr = "链路确认";
            break;

            case TC_FCD_LOG_IN:
            pstr = "建立链路、登录系统";
            break;

            case TC_FCD_LOG_OUT:
            pstr = "拆除链路、退出系统";
            break;

            case TC_FCD_HEART_BEAT:
            pstr = "保持链路、在线心跳";
            break;

            default:
            pstr = "错误的功能码";
            break;

        }
    }
    else
    {
        switch(sUnpackCom.sCtrl.eFcode)
        {
            case TC_FCD_OK:  
            //case TC_FCD_NOTI:
                if(sUnpackCom.sCtrl.ePRM == TC_PRM_A2P)
                {
                     pstr = "发送/无回答";
                }
                else
                {
                     pstr = "链路用户确认";
                }
           
            break;

            case TC_FCD_ANSWER:
            //case TC_FCD_CONF:
                if(sUnpackCom.sCtrl.ePRM == TC_PRM_A2P)
                {
                    pstr = "以用户数据响应请求";
                }
                else
                {
                    pstr = "发送/确认";
                }
          
            break;
            
            case TC_FCD_ASK:
            pstr = "请求/响应";
            break;

            default:
            pstr = "错误的功能码";
            break;
        }

    }
    printf("(%s)\n", pstr);
    
    // 地址域
    show_main_name("地 址 域:");
    show_sub_name("\t A1:");
    printf("[%02X %02X %02X]\t\t", 
            psHeadFixed->stA.acRegionCode[0], 
            psHeadFixed->stA.acRegionCode[1],
            psHeadFixed->stA.acRegionCode[2]);
            
    show_item_value("行政区划码");
    memcpy(ac, sUnpackCom.sAddress.acRegionCode, TC_REGN_LEN);
    printf("\t%s\n", ac);
    show_sub_name("\t\t A2:");
    printf("[%02X %02X %02X %02X]\t", 
            psHeadFixed->stA.acRegionCode[3], 
            psHeadFixed->stA.acRegionCode[4],
            psHeadFixed->stA.acRegionCode[5],
            psHeadFixed->stA.acRegionCode[6]);

    if(sUnpackCom.sAddress.ulTmlAddress == 0)
    {
        show_item_value("终端 无效地址");
    }
    else if(sUnpackCom.sAddress.ulTmlAddress == 0xFFFFFFFF)
    {
        show_item_value("终端 广播地址");
    }
    else
    {
        show_item_value("终端地址");
    }
    
    printf("\t%d\t", sUnpackCom.sAddress.ulTmlAddress);

    show_sub_name("\n\t\t A3:");
    ucTemp = psHeadFixed->stA.acRegionCode[7];
    printf("[%02X]\t\t", ucTemp);

    show_item_value("主站地址");
    printf("\t%d\n", sUnpackCom.sAddress.ucConAddress);

    /*
    show_sub_name("\t\t bT:\t\t");
    ucTemp = ucTemp & 0x01;
    printf("%d\t", ucTemp);
    if(ucTemp == 1)
    {
        show_item_value("A2为组地址\n");
    }
    else
    {
        show_item_value("A2为单地址\n");
    }
    */
    
    // 链路层数据
    show_main_name("链路数据:\t");
    if(TRUE == bFixed)
    {
       // version
        show_sub_name("  V:");
        printf("[%02X]\t\t", psHeadFixed->ucV);
        show_item_value("协议版本\n");

        show_sub_name("\t\t CS:");
        printf("[%02X]\t\t", psHeadFixed->ucS);
        show_item_value("校验和\n");
    }
    else
    {
        show_sub_name("  V:");
        printf("[%02X]\t\t", psHeadAlter->ucV);
        show_item_value("协议版本");
        printf("\n\t\t");

        // 应用控制域AC
        show_sub_name(" AC:");
        printf("[%02X]\t\t", psHeadAlter->ucAc);
        show_item_value("应用控制域"); 

        sTcAc sAc;
        eRet = etc_trans_ac(TC_TRANS_F2U, &sAc, &psHeadAlter->ucAc);
        if(TC_OK != eRet)
        {
            printf("\t应用控制域错误 %d\n", eRet);
        }
        else
        {
            printf("\ttp(%s) ec(%s) fcode(%d)",
                    sAc.bTp == TRUE ? "T":"F",
                    sAc.bEc == TRUE ? "T":"F",
                    sAc.eAfn);
                     
            switch(sAc.eAfn)
            {
                case TC_AFN_00_CONF:
                    show_item_value("确认否认");
                    break;      
                    
                case TC_AFN_01_RSET:
                    show_item_value("复位");
                    break;   
                    
                case TC_AFN_04_SETP:
                    show_item_value("设置参数");
                    break;  
                    
                case TC_AFN_05_CTRL:
                    show_item_value("控制命令");
                    break;          
                    
                case TC_AFN_06_AUTH:
                    show_item_value("身份认证及密钥协商");
                    break;      
                    

                 case TC_AFN_10_GETP:
                    show_item_value("查询参数");
                    break;   
                    
                case TC_AFN_12_ASKT:
                    show_item_value("请求（定时上报）任务数据");
                    break;  
                    
                case TC_AFN_13_ASKR:
                    show_item_value("请求实时数据");
                    break;          
                    
                case TC_AFN_14_ASKE:
                    show_item_value("请求（主动上报）事件记录");
                    break;      
                    
                case TC_AFN_15_FILE:
                    show_item_value("文件传输");
                    break;
                           
                case TC_AFN_16_DATA:
                    show_item_value("数据转发");
                    break;

                default:
                    show_item_value("未知AFN");
                    break;

            }
        }

        printf("\n");
            
        sTcDaDt sDaDt = {0};
        memcpy(&sDaDt, (void*)(&psHeadAlter->ucAc + 1), sizeof(sTcDaDt));
        
        show_sub_name("\t\tDa1:");
        printf("[%02X]\t",  sDaDt.ucDA1);       
        printf("%d\n",  sDaDt.ucDA1);

        show_sub_name("\t\tDa2:");
        printf("[%02X]\t",  sDaDt.ucDA2);       
        printf("%d\n",  sDaDt.ucDA2);
        
        show_sub_name("\t\tDt1:");
        printf("[%02X]\t",  sDaDt.ucDT1);       
        printf("%d\n",  sDaDt.ucDT1);
        
        show_sub_name("\t\tDt2:");
        printf("[%02X]\t",  sDaDt.ucDT2);       
        printf("%d\n",  sDaDt.ucDT2);

        sTcPnFn sPnFn;
        eRet =  etc_dadt_to_pnfn(&sDaDt, &sPnFn);
        sTcmdPn sCmdPn[64];
        UINT8    ucNumCmdPn = 0;
        if(eRet != TC_OK)
        {
            show_item_value("标识错误\n");
        }
        else
        {             
            eRet = etc_pnfn_to_cmdpn(sAc.eAfn, &sPnFn, 1,   (sTcmdPn*)&sCmdPn, &ucNumCmdPn);

            for(i = 0; i < ucNumCmdPn; i++)
            {
                 show_main_name("命令类型:");
                printf("\t%d:\n", i+1);
                show_sub_name("\t\tPn:\t\t");
                printf("%d\n",  sCmdPn[i].usPn);
                show_sub_name("\t\tcmd:\t\t");
                printf("%04X\t",  sCmdPn[i].eCmd);
                eRet = eTcGetCmdInfor(sCmdPn[i].eCmd, sUnpackCom.sCtrl.eDir, &sCmdInfor);
                if(TC_OK != eRet)
                {
                   show_item_value("未知命令\n");
                }
                else
                {
                   #if TC_CFG_NAME
                   show_item_value(sCmdInfor.pName);
                   #endif
                   printf("\n");
                }
            }
           
        }
    
        
    }
    
    // 输出结果
    fm_print("--------------------------analyse success-------------------------\n",FR_GREEN);
    
   
}




// 详细显示各FN的应用层数据
void show_app_sub_data(eTcDir eDir,eTcmd emtCmd, uTcApp *puAppData)
{
    int     i   = 0;
    int     j   = 0;
    eTcErr eRet = TC_OK;
    //eTcErr eRet2 = TC_OK;

    sTcmdInfor sCmdInfo;
    eTcmd   eCmd = TCMD_AFN_F_UNKOWN;
    char *pStr = NULL;
    
    switch(emtCmd)
    {
    
        case TCMD_AFN_0_F1_ALL_OK_DENY:
        {   
            printf("eTcResCode = %d", puAppData->eResCode);
            switch(puAppData->eResCode)
            {
                case TC_RES_OK:
                    pStr = "确认";
                    break;
                
                case TC_RES_NONE:
                    pStr = "无请求的数据、无设置的参数、无要执行的功能";
                    break;
                    
                case TC_RES_NOT_READY:
                    pStr = "请求的数据未产生、功能执行未满足";
                    break;
                    
                case TC_RES_REMOVE:
                    pStr = "请求的数据已经被移出保存窗口";
                    break;
                    
                case TC_RES_DATA_OTRNG:
                    pStr = "请求的数据超出支持的信息点范围";
                    break;
                    
                case TC_RES_PARA_OTRNG:
                    pStr = "设置的参数超出支持的信息点范围";
                    break;
                    
                case TC_RES_NOT_SAME:
                    pStr = "设置的接入端口号及属性与实际不符";
                    break;
                    
                case TC_RES_NOT_SUPT:
                    pStr = "指定接口不支持转发";
                    break;
                    
                case TC_RES_DENY:
                    pStr = "否认";
                    break;
                    
                default:
                    pStr = "未知确认";
                    break;
                
            }
            
            printf("\t\t");
            show_item_value(pStr);
            printf("\n");
        }
        break;
    #if 0
        case TCMD_AFN_0_F2_ONE_BY_ONE:
        {
            printf("eAFN = %d\n", puAppData->sOneByOne.eAFN);
            printf("ucNum = %d\n", puAppData->sOneByOne.ucNum);
            
            for(i = 0; i < puAppData->sOneByOne.ucNum; i++)
            {
                eCmd = puAppData->sOneByOne.sOne[i].eCmd;             
                printf("eCmd[%d] = 0x%04X\t", i, eCmd);
                eRet = eTcGetCmdInfor(eCmd, TC_DIR_M2S, &sCmdInfo);
                if(TC_OK != eRet)
                {
                    show_error("错误命令");
                }
                else
                {
                    show_item_value(sCmdInfo.pName);
                }       
                
                printf("\nusPn[%d] = 0x%04X\n", i, puAppData->sOneByOne.sOne[i].usPn);
               
                printf("eTcResCode = %d",  puAppData->sOneByOne.sOne[i].eResCode);
                switch( puAppData->sOneByOne.sOne[i].eResCode)
                {

                    case TC_RES_OK:
                        pStr = "确认";
                        break;
                    
                    case TC_RES_NONE:
                        pStr = "无请求的数据、无设置的参数、无要执行的功能";
                        break;
                        
                    case TC_RES_NOT_READY:
                        pStr = "请求的数据未产生、功能执行未满足";
                        break;
                        
                    case TC_RES_REMOVE:
                        pStr = "请求的数据已经被移出保存窗口";
                        break;
                        
                    case TC_RES_DATA_OTRNG:
                        pStr = "请求的数据超出支持的信息点范围";
                        break;
                        
                    case TC_RES_PARA_OTRNG:
                        pStr = "设置的参数超出支持的信息点范围";
                        break;
                        
                    case TC_RES_NOT_SAME:
                        pStr = "设置的接入端口号及属性与实际不符";
                        break;
                        
                    case TC_RES_NOT_SUPT:
                        pStr = "指定接口不支持转发";
                        break;
                        
                    case TC_RES_DENY:
                        pStr = "否认";
                        break;
                        
                    default:
                        pStr = "未知确认";
                        break;
                
                }
            
                printf("\t\t");
                show_item_value(pStr);
                printf("\n");
            }
        }
        break;

        case TCMD_AFN_1_F5_DATA_CLEAR:
        {
            printf("Num = %d\n", puAppData->sRtDataClear.ucNum);
            for(i =0 ; i < puAppData->sRtDataClear.ucNum; i++)
            {
                eCmd = puAppData->sRtDataClear.sCmdPn[i].eCmd;
                printf("eCmd[%d] = 0x%04X\t", i, eCmd);
                eRet = eTcGetCmdInfor(eCmd, eDir, &sCmdInfo);
                if(TC_OK != eRet)
                {
                    show_error("错误命令");
                }
                else
                {
                    show_item_value(sCmdInfo.pName);
                }
                
                printf("\n");
            }
        }
        break;

        case TCMD_AFN_4_F1_CON_UP_CFG:
        {
            printf("ucPermitDelayM = %d\n", puAppData->sConUpCfg.ucPermitDelayM);
            printf("ucReSendTimes  = %d\n", puAppData->sConUpCfg.ucReSendTimes);
            printf("ucHeartBeat    = %d\n", puAppData->sConUpCfg.ucHeartBeat);
            printf("usWaitTimeoutS = %d\n", puAppData->sConUpCfg.usWaitTimeoutS);
            printf("bPermitRt = %s\n", puAppData->sConUpCfg.bPermitRt == TRUE ? "true":"false");
            printf("bPermitTk = %s\n", puAppData->sConUpCfg.bPermitTk == TRUE ? "true":"false");
            printf("bPermitEv = %s\n", puAppData->sConUpCfg.bPermitEv == TRUE ? "true":"false");
        }
        break;
#endif
        case TCMD_AFN_4_F1_CON_IP_PORT:
        case TCMD_AFN_A_F1_CON_IP_PORT:
        {
             printf("sMainIP\t\t= %s %d.%d.%d.%d\n", 
                    puAppData->sDownCfg.sMainIp.eVersion == TC_IP_V4 ? "ipv4":"ipv6",
                    puAppData->sDownCfg.sMainIp.ip[0],
                    puAppData->sDownCfg.sMainIp.ip[1],
                    puAppData->sDownCfg.sMainIp.ip[2],
                    puAppData->sDownCfg.sMainIp.ip[3]);
 
             printf("usMainPort\t= %d\n", puAppData->sDownCfg.usMainPort);
 
 
             printf("sBackIP\t\t= %s %d.%d.%d.%d\n", 
                     puAppData->sDownCfg.sBackIp.eVersion == TC_IP_V4 ? "ipv4":"ipv6",
                     puAppData->sDownCfg.sBackIp.ip[0],
                     puAppData->sDownCfg.sBackIp.ip[1],
                     puAppData->sDownCfg.sBackIp.ip[2],
                     puAppData->sDownCfg.sBackIp.ip[3]);
 
             printf("usMainPort\t= %d\n", puAppData->sDownCfg.usBackPort);
 
             printf("APN[16]\t\t= ");
             printf_chars(puAppData->sDownCfg.ucAPN, 16);
 
             printf("\nUsr[32]\t\t= ");
             printf_chars(puAppData->sDownCfg.ucUsr, 32);
 
             printf("\nPwd[16]\t\t= ");
             printf_chars(puAppData->sDownCfg.ucPwd, 32);
             printf("\n");
                
        }
        break;

        case TCMD_AFN_4_F3_TML_AUTH_PARA:
        case TCMD_AFN_A_F3_TML_AUTH_PARA:
        {
            printf("ucTypeID = %d\n", puAppData->sAuthPara.ucTypeID);
            printf("usAuthPara = %d\n", puAppData->sAuthPara.usAuthPara);
        }

        break;
#if 0

        case TCMD_AFN_4_F4_TEAM_ADDR:
        case TCMD_AFN_A_F4_TEAM_ADDR:
        {
            for(i = 0; i < 8; i++)
            {
                printf("TeamAddr[%d] = %d\n", i, puAppData->sTeamAddr.ulAddr[i]);
            }
            
        }
        break;
            
        
        case TCMD_AFN_4_F5_CON_IP_PORT:
        case TCMD_AFN_A_F5_CON_IP_PORT:
        {          
            printf("usPort\t\t= %d\n", puAppData->sIpPort.usPort);

            printf("sConIp\t\t= %s %d.%d.%d.%d\n", 
                   puAppData->sIpPort.sConIp.eVersion == TC_IP_V4 ? "ipv4":"ipv6",
                   puAppData->sIpPort.sConIp.ip[0],
                   puAppData->sIpPort.sConIp.ip[1],
                   puAppData->sIpPort.sConIp.ip[2],
                   puAppData->sIpPort.sConIp.ip[3]);
                                             
            printf("sMask\t\t= %s %d.%d.%d.%d\n", 
                   puAppData->sIpPort.sMask.eVersion == TC_IP_V4 ? "ipv4":"ipv6",
                   puAppData->sIpPort.sMask.ip[0],
                   puAppData->sIpPort.sMask.ip[1],
                   puAppData->sIpPort.sMask.ip[2],
                   puAppData->sIpPort.sMask.ip[3]);

            printf("sGateIp\t\t= %s %d.%d.%d.%d\n", 
                   puAppData->sIpPort.sGateIp.eVersion == TC_IP_V4 ? "ipv4":"ipv6",
                   puAppData->sIpPort.sGateIp.ip[0],
                   puAppData->sIpPort.sGateIp.ip[1],
                   puAppData->sIpPort.sGateIp.ip[2],
                   puAppData->sIpPort.sGateIp.ip[3]);

            printf("eDelegate\t= %d\t", puAppData->sIpPort.eDelegate);

            switch(puAppData->sIpPort.eDelegate)
            {
                case TC_DELG_NULL:
                    printf("不使用代理\n");
                    break;

                case TC_DELG_HTTP:
                    printf("使用http connect代理\n");
                    break;
                    
                case TC_DELG_SOCK4:
                    printf("使用sock4代理\n");
                    break;
                    
                case TC_DELG_SOCK5:
                    printf("使用sock5代理\n");
                    break;
                    
                default:
                    printf("未知代理\n");
                    break;
            }

            
            printf("sDelgIp\t\t= %s %d.%d.%d.%d\n", 
                   puAppData->sIpPort.sDelgIp.eVersion == TC_IP_V4 ? "ipv4":"ipv6",
                   puAppData->sIpPort.sDelgIp.ip[0],
                   puAppData->sIpPort.sDelgIp.ip[1],
                   puAppData->sIpPort.sDelgIp.ip[2],
                   puAppData->sIpPort.sDelgIp.ip[3]);

            printf("usDelgPort\t= %d\n", puAppData->sIpPort.usDelgPort);
            printf("eDelgLink\t= %d\t", puAppData->sIpPort.eDelgLink);

            switch(puAppData->sIpPort.eDelgLink)
            {
                case TC_DELK_ANYONE:
                    printf("无需要验证\n");
                    break;

                case TC_DELK_USRPWD:
                    printf("需要用户名和密码\n");
                    break;

                default:
                    printf("未知方式\n");
                    break;
            }
            
            printf("bDlegUsr\t= %s\n", puAppData->sIpPort.bDlegUsr == TRUE ? "true":"false");

            printf("ucDlegUsrLen\t= %d\t", puAppData->sIpPort.ucDlegUsrLen);
            for(i = 0; i < puAppData->sIpPort.ucDlegUsrLen; i++)
            {
                printf("%c", puAppData->sIpPort.ucDlegUsr[i]);
            }
            printf("\n");

            
          
            printf("bDlegPwd\t= %s\n", puAppData->sIpPort.bDlegPwd == TRUE ? "true":"false");

            printf("ucDlegPwdLen\t= %d\t", puAppData->sIpPort.ucDlegPwdLen);
            for(i = 0; i < puAppData->sIpPort.ucDlegPwdLen; i++)
            {
                printf("%c", puAppData->sIpPort.ucDlegPwd[i]);
            }
            printf("\n");  
        }
        break;

        case TCMD_AFN_4_F6_CON_CASC:
        case TCMD_AFN_A_F6_CON_CASC:
        {
            printf("eType = %d ", puAppData->sCasc.eType);
            switch(puAppData->sCasc.eType)
            {
                case TC_CASC_NULL:
                    printf("TC_CASC_NULL 不启用级联功能\n");
                    break;
                    
                case TC_CASC_RS485:
                    printf("TC_CASC_RS485 RS485级联\n");
                    break;
                    
                case TC_CASC_ETH:
                    printf("TC_CASC_ETH 以太网级联\n");
                    break;
                    
                default:
                    printf("TC_CASC_UNKOWN 未知级联方式\n");
                    break;
            }

            // sSer
            // eBaud
            switch(puAppData->sCasc.sSer.eBaud)
            {        
               case TC_BAUD_DEFAULT:
                     pStr = "TC_BAUD_DEFAULT , 无须使用或使用默认";
                     break;
               case TC_BAUD_1200:
                     pStr = "TC_BAUD_1200";
                     break;
                     
               case TC_BAUD_2400:
                     pStr = "TC_BAUD_2400";
                     break;
                     
               case TC_BAUD_4800:
                     pStr = "TC_BAUD_4800";
                     break;        
                     
                 case TC_BAUD_9600:
                     pStr = "TC_BAUD_9600";
                     break;       
                     
                 case TC_BAUD_19200:
                     pStr = "TC_BAUD_19200";
                     break;  
                     
                 case TC_BAUD_38400:
                     pStr = "TC_BAUD_38400";
                     break;  
                     
                 default:
                     pStr = "TC_BAUD_UNKOWN";
                     break;
                     
                 }
              printf("sSer.eBaud\t\t= %s\n", pStr);
  
             // bStop1
            if(TRUE == puAppData->sCasc.sSer.bStop1)
            {
               printf("sSer.bStop1\t\t= 1停止位\n");
            }
            else
            {
               printf("sSer.bStop1\t\t= 2停止位\n");
            }
  
            // bCheck
            if(TRUE == puAppData->sCasc.sSer.bCheck)
            {
               printf("sSer.bCheck\t\t= 有校验\n");
            }
            else
            {
               printf("sSer.bCheck\t\t= 无校验\n");
            }
  
            // bOdd
            if(TRUE == puAppData->sCasc.sSer.bOdd)
            {
               printf("sSer.bOdd\t\t= 奇校验\n");
            }
            else
            {
               printf("sSer.bOdd\t\t= 偶校验\n");
            }
  
            // eBit
            switch(puAppData->sCasc.sSer.eBit)
            {
                case TC_SBIT_5:
                    pStr = "TC_SBIT_5";
                    break;
                case TC_SBIT_6:
                    pStr = "TC_SBIT_6";
                    break;
                case TC_SBIT_7:
                    pStr = "TC_SBIT_7";
                    break;
                case TC_SBIT_8:
                    pStr = "TC_SBIT_8";
                    break;
                 default:
                    pStr = "unkown";
                    break;
            }
            printf("sSer.eBit\t\t= %s\n", pStr);

            printf("ucWaitP = %d\n", puAppData->sCasc.ucWaitP);
            printf("ucWaitC = %d\n", puAppData->sCasc.ucWaitC);
            printf("ucReTry = %d\n", puAppData->sCasc.ucReTry);
            printf("ucPeriod = %d\n", puAppData->sCasc.ucPeriod);
            printf("ucN = %d\n", puAppData->sCasc.ucN);

            for(i = 0; i < puAppData->sCasc.ucN; i++)
            {   
                printf("sOne[%d]:\n", i);
                // acRegionCode
                printf("acRegionCode = ");
                printf_chars(puAppData->sCasc.sOne[i].acRegionCode, TC_REGN_LEN);

                printf("\nulConAddr = %d\n", puAppData->sCasc.sOne[i].ulConAddr);
                
                // sIp                
                printf("sIp\t = %s %d.%d.%d.%d\n", puAppData->sCasc.sOne[i].sIp.eVersion == TC_IP_V4 ? "ipv4":"ipv6",
                                                    puAppData->sCasc.sOne[i].sIp.ip[0],
                                                    puAppData->sCasc.sOne[i].sIp.ip[1],
                                                    puAppData->sCasc.sOne[i].sIp.ip[2],
                                                    puAppData->sCasc.sOne[i].sIp.ip[3]);

                printf("usPort = %d\n", puAppData->sCasc.sOne[i].usPort);
            }
        }
        break;
        
        case TCMD_AFN_4_F7_CON_DOWN_CFG:
        {          
            printf("ucPort\t\t= %d\n", puAppData->sDownCfg.ucPort);

            printf("sMainIp\t\t= %s %d.%d.%d.%d\n", puAppData->sDownCfg.sMainIp.eVersion == TC_IP_V4 ? "ipv4":"ipv6",
                                                    puAppData->sDownCfg.sMainIp.ip[0],
                                                    puAppData->sDownCfg.sMainIp.ip[1],
                                                    puAppData->sDownCfg.sMainIp.ip[2],
                                                    puAppData->sDownCfg.sMainIp.ip[3]);
            printf("usMainPort\t\t= %d\n", puAppData->sDownCfg.usMainPort);
                              
            printf("sBackIp\t\t= %s %d.%d.%d.%d\n", puAppData->sDownCfg.sBackIp.eVersion == TC_IP_V4 ? "ipv4":"ipv6",
                                                    puAppData->sDownCfg.sBackIp.ip[0],
                                                    puAppData->sDownCfg.sBackIp.ip[1],
                                                    puAppData->sDownCfg.sBackIp.ip[2],
                                                    puAppData->sDownCfg.sBackIp.ip[3]);
            printf("usBackPort\t\t= %d\n", puAppData->sDownCfg.usBackPort);


            printf("ucAPN\t\t = ");
            for(i = 0; i < 16; i++)
            {
                printf("%c", puAppData->sDownCfg.ucAPN[i]);
            }
            printf("\n");

              printf("ucUsr\t\t = ");
            for(i = 0; i < 32; i++)
            {
                printf("%c", puAppData->sDownCfg.ucUsr[i]);
            }
            printf("\n");

            printf("ucPwd\t\t = ");
            for(i = 0; i < 32; i++)
            {
                printf("%c", puAppData->sDownCfg.ucPwd[i]);
            }
            printf("\n");
        }
        break;
        #endif        
    
        case TCMD_AFN_4_F5_TML_EVENT_CFG:
        case TCMD_AFN_A_F5_TML_EVENT_CFG:
        {
            printf("ucNeed\t\t= %d\n", puAppData->sEventCfg.ucNeed);
            for(i = 0; i < puAppData->sEventCfg.ucNeed; i++)
            {
                printf("aNeed[%d] %d\n", i, puAppData->sEventCfg.aNeed[i]);
            }
            
            printf("ucImpt\t\t= %d\n", puAppData->sEventCfg.ucImpt);
            for(i = 0; i < puAppData->sEventCfg.ucImpt; i++)
            {
                printf("aImpt[%d] %d\n", i, puAppData->sEventCfg.aImpt[i]);
            } 

        }

        break;
        case TCMD_AFN_4_F4_TML_STATE_INPUT:
        case TCMD_AFN_A_F4_TML_STATE_INPUT:
        {
            printf("sStateInput\n");
            for(i = 0; i < 8; i++)
            {
                printf("bIn[%d] %s\n", i, puAppData->sStateInput.bIn[i] == TRUE ? "接入":"未接入");
            }

            printf("-------------------");
            for(i = 0; i < 8; i++)
            {
                printf("bOn[%d] %s\n", i, puAppData->sStateInput.bOn[i] == TRUE ? "触点常开":"触点关闭");
            }
        }

        break;
    
        case TCMD_AFN_4_F2_TML_UP_CFG:
        case TCMD_AFN_A_F2_TML_UP_CFG:
        {    
            printf("usListenPort\t= %d\n", puAppData->sTmlUpCfg.usListenPort);
       


            printf("sUpIp\t\t= %s %d.%d.%d.%d\n", puAppData->sTmlUpCfg.sUpIp.eVersion == TC_IP_V4 ? "ipv4":"ipv6",
                                                 puAppData->sTmlUpCfg.sUpIp.ip[0],
                                                 puAppData->sTmlUpCfg.sUpIp.ip[1],
                                                 puAppData->sTmlUpCfg.sUpIp.ip[2],
                                                 puAppData->sTmlUpCfg.sUpIp.ip[3]);
                                             
            printf("sUpMask\t\t= %s %d.%d.%d.%d\n", puAppData->sTmlUpCfg.sUpMask.eVersion == TC_IP_V4 ? "ipv4":"ipv6",
                                               puAppData->sTmlUpCfg.sUpMask.ip[0],
                                               puAppData->sTmlUpCfg.sUpMask.ip[1],
                                               puAppData->sTmlUpCfg.sUpMask.ip[2],
                                               puAppData->sTmlUpCfg.sUpMask.ip[3]);

            printf("sGateIp\t\t= %s %d.%d.%d.%d\n", puAppData->sTmlUpCfg.sGateIp.eVersion == TC_IP_V4 ? "ipv4":"ipv6",
                                                puAppData->sTmlUpCfg.sGateIp.ip[0],
                                                puAppData->sTmlUpCfg.sGateIp.ip[1],
                                                puAppData->sTmlUpCfg.sGateIp.ip[2],
                                                puAppData->sTmlUpCfg.sGateIp.ip[3]);

            printf("eDelegate\t= %d\t", puAppData->sTmlUpCfg.eDelegate);

            switch(puAppData->sTmlUpCfg.eDelegate)
            {
                case TC_DELG_NULL:
                    printf("不使用代理\n");
                    break;

                case TC_DELG_HTTP:
                    printf("使用http connect代理\n");
                    break;
                    
                case TC_DELG_SOCK4:
                    printf("使用sock4代理\n");
                    break;
                    
                case TC_DELG_SOCK5:
                    printf("使用sock5代理\n");
                    break;
                    
                default:
                    printf("未知代理\n");
                    break;
            }

            
            printf("sDelgIp\t\t= %s %d.%d.%d.%d\n", puAppData->sTmlUpCfg.sDelgIp.eVersion == TC_IP_V4 ? "ipv4":"ipv6",
                                             puAppData->sTmlUpCfg.sDelgIp.ip[0],
                                             puAppData->sTmlUpCfg.sDelgIp.ip[1],
                                             puAppData->sTmlUpCfg.sDelgIp.ip[2],
                                             puAppData->sTmlUpCfg.sDelgIp.ip[3]);

                                             
            printf("usDelgPort\t= %d\n", puAppData->sTmlUpCfg.usDelgPort);


            printf("eDelgLink\t= %d\t", puAppData->sTmlUpCfg.eDelgLink);

            switch(puAppData->sTmlUpCfg.eDelgLink)
            {
                case TC_DELK_ANYONE:
                    printf("无需要验证\n");
                    break;

                case TC_DELK_USRPWD:
                    printf("需要用户名和密码\n");
                    break;

                default:
                    printf("未知方式\n");
                    break;
            }
            
            printf("bDlegUsr\t= %s\n", puAppData->sTmlUpCfg.bDlegUsr == TRUE ? "true":"false");

            printf("ucDlegUsrLen\t= %d\t", puAppData->sTmlUpCfg.ucDlegUsrLen);
            for(i = 0; i < puAppData->sTmlUpCfg.ucDlegUsrLen; i++)
            {
                printf("%c", puAppData->sTmlUpCfg.ucDlegUsr[i]);
            }
            printf("\n");


            printf("bDlegPwd\t= %s\n", puAppData->sTmlUpCfg.bDlegPwd == TRUE ? "true":"false");

            printf("ucDlegPwdLen\t= %d\t", puAppData->sTmlUpCfg.ucDlegPwdLen);
            for(i = 0; i < puAppData->sTmlUpCfg.ucDlegPwdLen; i++)
            {
                printf("%c", puAppData->sTmlUpCfg.ucDlegPwd[i]);
            }
            printf("\n");  

            printf("ucPermitDelayM  = %d\n", puAppData->sTmlUpCfg.ucPermitDelayM);
            printf("ucReSendTimes   = %d\n", puAppData->sTmlUpCfg.ucReSendTimes);
            printf("ucHeartBeat     = %d\n", puAppData->sTmlUpCfg.ucHeartBeat);
            printf("usWaitTimeoutS  = %d\n", puAppData->sTmlUpCfg.usWaitTimeoutS);
            printf("bPermitTk       = %s\n", puAppData->sTmlUpCfg.bPermitTk == TRUE ? "true":"false");
            printf("bPermitEv       = %s\n", puAppData->sTmlUpCfg.bPermitEv == TRUE ? "true":"false");
        }
        
        break;
#if 0
        case TCMD_AFN_4_F25_ELEC_MP_CFG:
        case TCMD_AFN_4_F33_NELC_MP_CFG:
        case TCMD_AFN_A_F25_ELEC_MP_CFG:
        case TCMD_AFN_A_F33_NELC_MP_CFG:
        {        
            printf("usID\t\t= %d\n", puAppData->sElecMpCfg.usID);
            printf("ucPort\t\t= %d\n", puAppData->sElecMpCfg.ucPort);
            char ucAddr[17] = {0};
            memcpy(ucAddr, puAppData->sElecMpCfg.ucAddr, 16);
            printf("ucAddr\t\t= %s\n", ucAddr);

            // eAcsProto
            switch(puAppData->sElecMpCfg.eAcsProto)
            {
                case TC_ACS_PROT_GBNX_32:
                    pStr = "TC_ACS_PROT_GBNX_32";
                    break;
                case TC_ACS_PROT_DLT645_97:
                    pStr = "TC_ACS_PROT_DLT645_97";
                    break;                    
                case TC_ACS_PROT_DLT645_07:
                    pStr = "TC_ACS_PROT_DLT645_07";
                    break;    

                case TC_ACS_PROT_MODBUS:
                    pStr = "TC_ACS_PROT_MODBUS";
                    break;
                case TC_ACS_PROT_UNKOWN:
                    pStr = "TC_ACS_PROT_UNKOWN";
                    break;
                    
                default:
                    pStr = "TC_ACS_PROT_USER";
                    break;
            }

            printf("eAcsProto\t= %s\n", pStr);

            // pwd 
            char pwd[7] = {0};
            memcpy(pwd, puAppData->sElecMpCfg.ucPwd, 6);
            printf("pwd\t\t= %s\n", pwd);

            // eAcsPort
            switch(puAppData->sElecMpCfg.eAcsPort)
            {
                case TC_ACS_PORT_UNKOWN:
                    pStr = "TC_ACS_PORT_UNKOWN";
                    break;
                case TC_ACS_PORT_DC:
                    pStr = "TC_ACS_PORT_DC";
                    break;                    
                case TC_ACS_PORT_AC:
                    pStr = "TC_ACS_PORT_AC";
                    break;    

                case TC_ACS_PORT_ETH:
                    pStr = "TC_ACS_PORT_ETH";
                    break;
                case TC_ACS_PORT_SER:
                    pStr = "TC_ACS_PORT_SER";
                    break;
                    
                 case TC_ACS_PORT_ZIGB:
                    pStr = "TC_ACS_PORT_ZIGB";
                    break;           
                    
                default:
                    pStr = "TC_ACS_PORT_UNKOWN";
                    break;
            
            }
            
            printf("eAcsPort\t= %s\n", pStr);

            // 
            if(puAppData->sElecMpCfg.eAcsPort == TC_ACS_PORT_SER)
            {
                // eBaud
                switch(puAppData->sElecMpCfg.uPortPara.sSer.eBaud)
                {        
                   case TC_BAUD_DEFAULT:
                         pStr = "TC_BAUD_DEFAULT , 无须使用或使用默认";
                         break;
                   case TC_BAUD_1200:
                         pStr = "TC_BAUD_1200";
                         break;
                         
                   case TC_BAUD_2400:
                         pStr = "TC_BAUD_2400";
                         break;
                         
                   case TC_BAUD_4800:
                         pStr = "TC_BAUD_4800";
                         break;        
                         
                     case TC_BAUD_9600:
                         pStr = "TC_BAUD_9600";
                         break;       
                         
                     case TC_BAUD_19200:
                         pStr = "TC_BAUD_19200";
                         break;  
                         
                     case TC_BAUD_38400:
                         pStr = "TC_BAUD_38400";
                         break;  
                         
                     default:
                         pStr = "TC_BAUD_UNKOWN";
                         break;
                         
                     }
                  printf("sSer.eBaud\t\t= %s\n", pStr);

                 // bStop1
                if(TRUE == puAppData->sElecMpCfg.uPortPara.sSer.bStop1)
                {
                   printf("sSer.bStop1\t\t= 1停止位\n");
                }
                else
                {
                   printf("sSer.bStop1\t\t= 2停止位\n");
                }

                // bCheck
                if(TRUE == puAppData->sElecMpCfg.uPortPara.sSer.bCheck)
                {
                   printf("sSer.bCheck\t\t= 有校验\n");
                }
                else
                {
                   printf("sSer.bCheck\t\t= 无校验\n");
                }

                // bOdd
                if(TRUE == puAppData->sElecMpCfg.uPortPara.sSer.bOdd)
                {
                   printf("sSer.bOdd\t\t= 奇校验\n");
                }
                else
                {
                   printf("sSer.bOdd\t\t= 偶校验\n");
                }

                // eBit
                switch(puAppData->sElecMpCfg.uPortPara.sSer.eBit)
                {
                    case TC_SBIT_5:
                        pStr = "TC_SBIT_5";
                        break;
                    case TC_SBIT_6:
                        pStr = "TC_SBIT_6";
                        break;
                    case TC_SBIT_7:
                        pStr = "TC_SBIT_7";
                        break;
                    case TC_SBIT_8:
                        pStr = "TC_SBIT_8";
                        break;
                     default:
                        pStr = "unkown";
                        break;
                }
                printf("sSer.eBit\t\t= %s\n", pStr);
  
            }

            // TC_ACS_PORT_ETH
            if(puAppData->sElecMpCfg.eAcsPort == TC_ACS_PORT_ETH)
            {
                printf("usPort\t\t= %d\n", puAppData->sElecMpCfg.uPortPara.sEth.usPort);
                printf("sMask\t\t= %s %d.%d.%d.%d\n", 
                puAppData->sElecMpCfg.uPortPara.sEth.sAccess.eVersion == TC_IP_V4 ? "ipv4":"ipv6",
                puAppData->sElecMpCfg.uPortPara.sEth.sAccess.ip[0],
                puAppData->sElecMpCfg.uPortPara.sEth.sAccess.ip[1],
                puAppData->sElecMpCfg.uPortPara.sEth.sAccess.ip[2],
                puAppData->sElecMpCfg.uPortPara.sEth.sAccess.ip[3]);

                /*
                printf("sGate\t\t= %s %d.%d.%d.%d\n", 
                puAppData->sElecMpCfg.uPortPara.sEth.sGate.eVersion == TC_IP_V4 ? "ipv4":"ipv6",
                puAppData->sElecMpCfg.uPortPara.sEth.sGate.ip[0],
                puAppData->sElecMpCfg.uPortPara.sEth.sGate.ip[1],
                puAppData->sElecMpCfg.uPortPara.sEth.sGate.ip[2],
                puAppData->sElecMpCfg.uPortPara.sEth.sGate.ip[3]);
                */
            }
            
            // TC_ACS_PORT_ZIGB
            if(puAppData->sElecMpCfg.eAcsPort == TC_ACS_PORT_ZIGB)
            {
                printf("ulAddrZigb\t= %d\n", puAppData->sElecMpCfg.uPortPara.ulAddrZigb);
            }

            // usAcsPort
            printf("usAcsPort\t= %d\n", puAppData->sElecMpCfg.usAcsPort);
            printf("sAccess\t\t= %s %d.%d.%d.%d\n", 
            puAppData->sElecMpCfg.sAccess.eVersion == TC_IP_V4 ? "ipv4":"ipv6",
            puAppData->sElecMpCfg.sAccess.ip[0],
            puAppData->sElecMpCfg.sAccess.ip[1],
            puAppData->sElecMpCfg.sAccess.ip[2],
            puAppData->sElecMpCfg.sAccess.ip[3]);

            /*
            printf("sGateIp\t\t= %s %d.%d.%d.%d\n", 
            puAppData->sElecMpCfg.sGateIp.eVersion == TC_IP_V4 ? "ipv4":"ipv6",
            puAppData->sElecMpCfg.sGateIp.ip[0],
            puAppData->sElecMpCfg.sGateIp.ip[1],
            puAppData->sElecMpCfg.sGateIp.ip[2],
            puAppData->sElecMpCfg.sGateIp.ip[3]);
            */
        }
        break;

        case TCMD_AFN_4_F26_ELEC_MP_BASE:
        {
            printf("ucInteger\t\t= %d\n", puAppData->sElecMpBase.sDigit.ucInteger);
            printf("ucDecimal\t\t= %d\n", puAppData->sElecMpBase.sDigit.ucDecimal);
            printf("usTimesU\t\t= %d\n", puAppData->sElecMpBase.usTimesU);
            printf("usTimesI\t\t= %d\n", puAppData->sElecMpBase.usTimesI);
            printf("fU\t\t= %4.1f\n", puAppData->sElecMpBase.fU);
            printf("fI\t\t= %6.3f\n", puAppData->sElecMpBase.fI);
            printf("eLink\t\t= %d\t", puAppData->sElecMpBase.sLinkWay.eLink);
            switch(puAppData->sElecMpBase.sLinkWay.eLink)
            {
                case TC_LINK_P3_L3:
                    printf("三相三线\n");
                    break;
                    
                case TC_LINK_P3_L4:
                    printf("三相四线\n");
                    break;
                    
                case TC_LINK_P1:
                    printf("单相表\n");
                    break;
                    
                default:
                    printf("未知\n");
                    break;
            }

            printf("ePhase\t\t= %d\t", puAppData->sElecMpBase.sLinkWay.ePhase);
            switch(puAppData->sElecMpBase.sLinkWay.ePhase)
            {
                case TC_PHASE_A:
                    printf("TC_PHASE_A\n");
                    break;
                    
                case TC_PHASE_B:
                    printf("TC_PHASE_B\n");
                    break;
                    
                case TC_PHASE_C:
                    printf("TC_PHASE_B\n");
                    break;
                    
                default:
                    printf("未知\n");
                    break;
            }  
        }
        break;

        case TCMD_AFN_4_F27_ELEC_LMIT_POWER:
        {
            printf("fDropV = %f\n", puAppData->sElecLimitPower.fDropV);
            printf("ucTimeLossV = %d\n", puAppData->sElecLimitPower.ucTimeLossV);

            // sOverV
            printf("sOverV.fUpUp = %f\n", puAppData->sElecLimitPower.sOverV.fUpUp);
            printf("sOverV.ucTime = %d\n", puAppData->sElecLimitPower.sOverV.ucTime);
            printf("sOverV.fFactor = %f\n", puAppData->sElecLimitPower.sOverV.fFactor);

            // sLossV
            printf("sLossV.fDownDown = %f\n", puAppData->sElecLimitPower.sLossV.fDownDown);
            printf("sLossV.ucTime = %d\n", puAppData->sElecLimitPower.sLossV.ucTime);
            printf("sLossV.fFactor = %f\n", puAppData->sElecLimitPower.sLossV.fFactor);

            // sOverI
            printf("sOverI.fUpUp = %f\n", puAppData->sElecLimitPower.sOverI.fUpUp);
            printf("sOverI.ucTime = %d\n", puAppData->sElecLimitPower.sOverI.ucTime);
            printf("sOverI.fFactor = %f\n", puAppData->sElecLimitPower.sOverI.fFactor);

            // sSuperI
            printf("sSuperI.fUp = %f\n", puAppData->sElecLimitPower.sSuperI.fUp);
            printf("sSuperI.ucTime = %d\n", puAppData->sElecLimitPower.sSuperI.ucTime);
            printf("sSuperI.fFactor = %f\n", puAppData->sElecLimitPower.sSuperI.fFactor);

            // sZeroI
            printf("sZeroI.fUp = %f\n", puAppData->sElecLimitPower.sZeroI.fUp);
            printf("sZeroI.ucTime = %d\n", puAppData->sElecLimitPower.sZeroI.ucTime);
            printf("sZeroI.fFactor = %f\n", puAppData->sElecLimitPower.sZeroI.fFactor);

            // sUblV
            printf("sUblV.fLimit = %f\n", puAppData->sElecLimitPower.sUblV.fLimit);
            printf("sUblV.ucTime = %d\n", puAppData->sElecLimitPower.sUblV.ucTime);
            printf("sUblV.fFactor = %f\n", puAppData->sElecLimitPower.sUblV.fFactor);

            // sUblI
            printf("sUblI.fLimit = %f\n", puAppData->sElecLimitPower.sUblI.fLimit);
            printf("sUblI.ucTime = %d\n", puAppData->sElecLimitPower.sUblI.ucTime);
            printf("sUblI.fFactor = %f\n", puAppData->sElecLimitPower.sUblI.fFactor);

        }
        break;
             
        case TCMD_AFN_4_F28_ELEC_LMIT_FACTR:
        {
            printf("fPara1 = %4.2f\n", puAppData->sFactorLimit.fPara1);
            printf("fPara2 = %4.2f\n", puAppData->sFactorLimit.fPara2);
            printf("fWarning = %4.2f\n", puAppData->sFactorLimit.fWarning);
        }
        break;  
        
        case TCMD_AFN_4_F29_ELEC_FIX_HARM:
        {
            printf("sVa.fTotal = %4.2f\n", puAppData->sElecFixHarm.sVa.fTotal);
            printf("sVa.fOdd = %4.2f\n", puAppData->sElecFixHarm.sVa.fOdd);
            printf("sVa.fEven = %4.2f\n", puAppData->sElecFixHarm.sVa.fEven);

            printf("sVb.fTotal = %4.2f\n", puAppData->sElecFixHarm.sVb.fTotal);
            printf("sVb.fOdd = %4.2f\n", puAppData->sElecFixHarm.sVb.fOdd);
            printf("sVb.fEven = %4.2f\n", puAppData->sElecFixHarm.sVb.fEven);

            printf("sVc.fTotal = %4.2f\n", puAppData->sElecFixHarm.sVc.fTotal);
            printf("sVc.fOdd = %4.2f\n", puAppData->sElecFixHarm.sVc.fOdd);
            printf("sVc.fEven = %4.2f\n", puAppData->sElecFixHarm.sVc.fEven);

            printf("sIa.fTotal = %4.2f\n", puAppData->sElecFixHarm.sIa.fTotal);
            printf("sIa.fOdd = %4.2f\n", puAppData->sElecFixHarm.sIa.fOdd);
            printf("sIa.fEven = %4.2f\n", puAppData->sElecFixHarm.sIa.fEven);         

            printf("sIb.fTotal = %4.2f\n", puAppData->sElecFixHarm.sIb.fTotal);
            printf("sIb.fOdd = %4.2f\n", puAppData->sElecFixHarm.sIb.fOdd);
            printf("sIb.fEven = %4.2f\n", puAppData->sElecFixHarm.sIb.fEven);

            printf("sIc.fTotal = %4.2f\n", puAppData->sElecFixHarm.sIc.fTotal);
            printf("sIc.fOdd = %4.2f\n", puAppData->sElecFixHarm.sIc.fOdd);
            printf("sIc.fEven = %4.2f\n", puAppData->sElecFixHarm.sIc.fEven);      

        }
        break;
        
        
        case TCMD_AFN_4_F30_ELEC_FLASH:
        {
            printf("fLong = %4.2f\n",puAppData->sElecFlash.fLong);
            printf("fShort = %4.2f\n",puAppData->sElecFlash.fShort);
        }
        break;
  #endif      
        case TCMD_AFN_5_F1_CHECK_TIME:
        case TCMD_AFN_D_F1_CLOCK:
        {
            printf("ucYY\t\t= %d\n", puAppData->sCheckClock.ucYY);
            printf("ucMM\t\t= %d\n", puAppData->sCheckClock.ucMM);
            printf("ucWW\t\t= %d\n", puAppData->sCheckClock.ucWW);
            printf("ucDD\t\t= %d\n", puAppData->sCheckClock.ucDD);
            printf("ucHH\t\t= %d\n", puAppData->sCheckClock.ucHH);
            printf("ucmm\t\t= %d\n", puAppData->sCheckClock.ucmm);
            printf("ucss\t\t= %d\n", puAppData->sCheckClock.ucss);
        }
        break;
        
        case TCMD_AFN_5_F5_NX_MODEL_ACT:
        {
            printf("ucN\t\t= %d\n", puAppData->sNxModelAct.ucN);
            for(i = 0; i < puAppData->sNxModelAct.ucN; i++)
            {
              printf("sOne[%d]:\n",i);
              
                printf("ucID\t\t= %d\n", puAppData->sNxModelAct.sOne[i].ucID);
                printf("ucYY\t\t= %d\n", puAppData->sNxModelAct.sOne[i].sTime.ucYY);
                printf("ucMM\t\t= %d\n", puAppData->sNxModelAct.sOne[i].sTime.ucMM);
                printf("ucWW\t\t= %d\n", puAppData->sNxModelAct.sOne[i].sTime.ucWW);
                printf("ucDD\t\t= %d\n", puAppData->sNxModelAct.sOne[i].sTime.ucDD);
                printf("ucHH\t\t= %d\n", puAppData->sNxModelAct.sOne[i].sTime.ucHH);
                printf("ucmm\t\t= %d\n", puAppData->sNxModelAct.sOne[i].sTime.ucmm);
                printf("ucss\t\t= %d\n", puAppData->sNxModelAct.sOne[i].sTime.ucss);
            }
        }
        break;

        case TCMD_AFN_5_F6_NX_MODEL_CLR:
        case TCMD_AFN_5_F7_RQ_RESPN_ACT:
        case TCMD_AFN_5_F8_RQ_RESPN_CLT:
        {
            printf("ucN\t\t= %d\n", puAppData->sNxModelClr.ucN);
            for(i = 0; i < puAppData->sNxModelClr.ucN; i++)
            {              
                printf("ucID[%d]\t\t= %d\n", i, puAppData->sNxModelClr.ucID[i]);              
            }
        }
        break;

        case TCMD_AFN_5_F17_REMOTE_OFF:
        {
            for(i = 0; i < 8; i++)
            {
                 printf("swich[%d] = %s\n", i, puAppData->sRemoteOff.bOff[i] == TRUE ? "off" : "on");
            }


            printf("sTimeStart:\n");
            printf("ucYY\t= %d\n", puAppData->sRemoteOff.sTimeStart.ucYY);
            printf("ucMM\t= %d\n", puAppData->sRemoteOff.sTimeStart.ucMM);
            printf("ucDD\t= %d\n", puAppData->sRemoteOff.sTimeStart.ucDD);
            printf("ucHH\t= %d\n", puAppData->sRemoteOff.sTimeStart.ucHH);
            printf("ucmm\t= %d\n", puAppData->sRemoteOff.sTimeStart.ucmm);

            printf("sTimeEnd:\n");
            printf("ucYY\t= %d\n", puAppData->sRemoteOff.sTimeEnd.ucYY);
            printf("ucMM\t= %d\n", puAppData->sRemoteOff.sTimeEnd.ucMM);
            printf("ucDD\t= %d\n", puAppData->sRemoteOff.sTimeEnd.ucDD);
            printf("ucHH\t= %d\n", puAppData->sRemoteOff.sTimeEnd.ucHH);
            printf("ucmm\t= %d\n", puAppData->sRemoteOff.sTimeEnd.ucmm);
  
        }
        break;
        
        case TCMD_AFN_5_F18_REMOTE_ON:
        {
            for(i = 0; i < 8; i++)
            {
                 printf("bOn[%d] = %s\n", i, puAppData->sRemoteOn.bOn[i] == TRUE ? "on" : "off");
            }
  
        }
        break;




        
    #if 0    
        case TCMD_AFN_A_F34_NELC_MP_PARA:
        case TCMD_AFN_4_F34_NELC_MP_PARA:
        case TCMD_AFN_4_F35_NELC_MP_LMIT:
            {
                printf("%d - ", puAppData->sNelcMpPara.eType);
                switch(puAppData->sNelcMpPara.eType)
                {
                    case TC_NELC_TEMP:
                        printf("TC_NELC_TEMP 温度\n");
                        break;
                        
                    case TC_NELC_FLOW:
                        printf("TC_NELC_FLOW 流量\n");
                        break;

                    case TC_NELC_FV:
                        printf("TC_NELC_FV 流速\n");
                        break;

                    case TC_NELC_PRESS:
                        printf("TC_NELC_PRESS 压力\n");
                        break;
                        
                    case TC_NELC_HUMI:
                        printf("TC_NELC_HUMI 温度\n");
                        break;
                        
                    case TC_NELC_LIGHT:
                        printf("TC_NELC_LIGHT 照度\n");
                        break;

                    case TC_NELC_RV:
                        printf("TC_NELC_RV 转速\n");
                        break;
                        
                    case TC_NELC_420MA:
                        printf("TC_NELC_420MA 4~20MA\n");
                        break;

                    default:
                        printf("TC_NELC_UNKOWN\n");
                        break;                       
                        
                }

                printf("sUp :");
                switch(puAppData->sNelcMpPara.sUp.ePrec)
                {
                    case TC_PREC_P4:
                        printf("TC_PREC_P4");
                        break;
                        
                    case TC_PREC_P3:
                        printf("TC_PREC_P3");
                        break;
                        
                    case TC_PREC_P2:
                        printf("TC_PREC_P2");
                        break;
                        
                    case TC_PREC_P1:
                        printf("TC_PREC_P1");
                        break;
                        
                    case TC_PREC_P0:
                        printf("TC_PREC_P0");
                        break;

                    case TC_PREC_N1:
                        printf("TC_PREC_N1");
                        break;
                        
                    case TC_PREC_N2:
                        printf("TC_PREC_N2");
                        break;
                        
                    case TC_PREC_N3:
                        printf("TC_PREC_N3");
                        break;

                    default:
                        printf("TC_PREC_UNKOWN");                        
                        break;
                     
                }

                printf(" %f\n", puAppData->sNelcMpPara.sUp.dValue);

                 printf("sDown :");
                switch(puAppData->sNelcMpPara.sDown.ePrec)
                {
                    case TC_PREC_P4:
                        printf("TC_PREC_P4");
                        break;
                        
                    case TC_PREC_P3:
                        printf("TC_PREC_P3");
                        break;
                        
                    case TC_PREC_P2:
                        printf("TC_PREC_P2");
                        break;
                        
                    case TC_PREC_P1:
                        printf("TC_PREC_P1");
                        break;
                        
                    case TC_PREC_P0:
                        printf("TC_PREC_P0");
                        break;

                    case TC_PREC_N1:
                        printf("TC_PREC_N1");
                        break;
                        
                    case TC_PREC_N2:
                        printf("TC_PREC_N2");
                        break;
                        
                    case TC_PREC_N3:
                        printf("TC_PREC_N3");
                        break;

                    default:
                        printf("TC_PREC_UNKOWN");                        
                        break;
                     
                }

                printf(" %f\n", puAppData->sNelcMpPara.sDown.dValue);
            }
            break;
#endif
        case TCMD_AFN_4_F17_FREZ_TASK_PARA:
        case TCMD_AFN_A_F17_FREZ_TASK_PARA:
        {

            printf("sTimeFrez:\n");
            printf("ucYY\t= %d\n", puAppData->sFrezTaskPara.sTimeFrez.ucYY);
            printf("ucMM\t= %d\n", puAppData->sFrezTaskPara.sTimeFrez.ucMM);
            printf("ucWW\t= %d\n", puAppData->sFrezTaskPara.sTimeFrez.ucWW);
            printf("ucDD\t= %d\n", puAppData->sFrezTaskPara.sTimeFrez.ucDD);
            printf("ucHH\t= %d\n", puAppData->sFrezTaskPara.sTimeFrez.ucHH);
            printf("ucmm\t= %d\n", puAppData->sFrezTaskPara.sTimeFrez.ucmm);
            printf("ucmm\t= %d\n", puAppData->sFrezTaskPara.sTimeFrez.ucss);

            printf("sTimeRprt:\n");
            printf("ucYY\t= %d\n", puAppData->sFrezTaskPara.sTimeRprt.ucYY);
            printf("ucMM\t= %d\n", puAppData->sFrezTaskPara.sTimeRprt.ucMM);
            printf("ucWW\t= %d\n", puAppData->sFrezTaskPara.sTimeRprt.ucWW);
            printf("ucDD\t= %d\n", puAppData->sFrezTaskPara.sTimeRprt.ucDD);
            printf("ucHH\t= %d\n", puAppData->sFrezTaskPara.sTimeRprt.ucHH);
            printf("ucmm\t= %d\n", puAppData->sFrezTaskPara.sTimeRprt.ucmm);
            printf("ucmm\t= %d\n", puAppData->sFrezTaskPara.sTimeRprt.ucss);    
            
            printf("sFreez:\n");
            printf("usPeriod\t= %d\n", puAppData->sFrezTaskPara.sFreez.usPeriod);
            printf("eUnit\t= %d\n", puAppData->sFrezTaskPara.sFreez.eUnit);
            printf("ucTimes\t= %d\n", puAppData->sFrezTaskPara.sFreez.ucTimes);    

            printf("ucPeriodRpt\t= %d\n", puAppData->sFrezTaskPara.ucPeriodRpt);   
            printf("eUnitRpt\t= %d\n", puAppData->sFrezTaskPara.eUnitRpt);   
            printf("uCmdPnNum\t= %d\n", puAppData->sFrezTaskPara.uCmdPnNum);   

            for(i = 0; i < puAppData->sFrezTaskPara.uCmdPnNum; i++)
            {
                printf("sCmdPn[%d].eCmd = %04X ", i,puAppData->sFrezTaskPara.sCmdPn[i].eCmd);
                eRet = eTcGetCmdInfor(puAppData->sFrezTaskPara.sCmdPn[i].eCmd, eDir, &sCmdInfo);
                if(TC_OK != eRet)
                {
                    show_error("错误命令");
                }
                else
                {
                    show_item_value(sCmdInfo.pName);
                }
                
                printf("\n");
                printf("sCmdPn[%d].usPn = %d\n", i, puAppData->sFrezTaskPara.sCmdPn[i].usPn);
            }
        }
        break;

#if 0
        case TCMD_AFN_C_F9_FREZ_AUTO:
        {
            if(eDir == TC_DIR_M2S)
            {
                printf("sTs.ucYY\t= %d\n", puAppData->sFrezAutoQ.sTs.ucYY);
                printf("sTs.ucMM\t= %d\n", puAppData->sFrezAutoQ.sTs.ucMM);
                printf("sTs.ucDD\t= %d\n", puAppData->sFrezAutoQ.sTs.ucDD);
                printf("sTs.ucHH\t= %d\n", puAppData->sFrezAutoQ.sTs.ucHH);
                printf("sTs.ucmm\t= %d\n", puAppData->sFrezAutoQ.sTs.ucmm);
                printf("-------------------\n");
                printf("sTe.ucYY\t= %d\n", puAppData->sFrezAutoQ.sTe.ucYY);
                printf("sTe.ucMM\t= %d\n", puAppData->sFrezAutoQ.sTe.ucMM);
                printf("sTe.ucDD\t= %d\n", puAppData->sFrezAutoQ.sTe.ucDD);
                printf("sTe.ucHH\t= %d\n", puAppData->sFrezAutoQ.sTe.ucHH);
                printf("sTe.ucmm\t= %d\n", puAppData->sFrezAutoQ.sTe.ucmm);
           }
           else
           {
                printf("sTs.ucYY\t= %d\n", puAppData->sFrezAutoA.sTs.ucYY);
                printf("sTs.ucMM\t= %d\n", puAppData->sFrezAutoA.sTs.ucMM);
                printf("sTs.ucDD\t= %d\n", puAppData->sFrezAutoA.sTs.ucDD);
                printf("sTs.ucHH\t= %d\n", puAppData->sFrezAutoA.sTs.ucHH);
                printf("sTs.ucmm\t= %d\n", puAppData->sFrezAutoA.sTs.ucmm);
                printf("usPeriod \t= %d\n", puAppData->sFrezAutoA.usPeriod);
                printf("eUnit \t= %d\t", puAppData->sFrezAutoA.eUnit);

                switch(puAppData->sFrezAutoA.eUnit)
                {
                    case TC_PUNT_MONTH:
                        printf("月");
                        break;

                    case TC_PUNT_DAY:
                        printf("日");
                        break;
                        
                    case TC_PUNT_HOUR:
                        printf("时");
                        break;

                    case TC_PUNT_MIN:
                        printf("分");
                        break;
                        
                    case TC_PUNT_SEC:
                        printf("秒");
                        break;

                    case TC_PUNT_MS:
                        printf("毫秒");
                        break;
                        
                    default:
                        printf("未知");
                        break;      
                }

                printf("\nucN \t= %d\t", puAppData->sFrezAutoA.ucN);
                printf("\nucM \t= %d\n", puAppData->sFrezAutoA.ucM);
                for(i = 0; i < puAppData->sFrezAutoA.ucM; i++)
                {

                    printf("------------------------------------\n");
                    printf("第%d个数据类型:\n", i+1);
                    printf("eCmd \t= %04X\t", puAppData->sFrezAutoA.sOne[i].sCmdPn.eCmd);
                    eRet = eTcGetCmdInfor(puAppData->sFrezAutoA.sOne[i].sCmdPn.eCmd, eDir, &sCmdInfo);
                    if(TC_OK != eRet)
                    {
                        show_error("错误命令");
                    }
                    else
                    {
                        show_item_value(sCmdInfo.pName);
                    }
                    
                    printf("\nusPn \t= %04X\n", puAppData->sFrezAutoA.sOne[i].sCmdPn.usPn);

                    for(j = 0; j < puAppData->sFrezAutoA.ucN; j++)
                    {
                       
                        printf("数据点%d:\n", j+1);
                        switch(puAppData->sFrezAutoA.sOne[i].sCmdPn.eCmd)
                        {
                            case TCMD_AFN_D_F233_NELC_VALUE: 
                            {
                                printf("eType = %d", puAppData->sFrezAutoA.sOne[i].uApp[j].sNelcValue.eType);
                                switch(puAppData->sFrezAutoA.sOne[i].uApp[j].sNelcValue.eType)
                                {
                                    case TC_NELC_TEMP:
                                        printf("TC_NELC_TEMP 温度\n");
                                        break;
                                        
                                    case TC_NELC_FLOW:
                                        printf("TC_NELC_FLOW 流量\n");
                                        break;

                                    case TC_NELC_FV:
                                        printf("TC_NELC_FV 流速\n");
                                        break;

                                    case TC_NELC_PRESS:
                                        printf("TC_NELC_PRESS 压力\n");
                                        break;
                                        
                                    case TC_NELC_HUMI:
                                        printf("TC_NELC_HUMI 温度\n");
                                        break;
                                        
                                    case TC_NELC_LIGHT:
                                        printf("TC_NELC_LIGHT 照度\n");
                                        break;

                                    case TC_NELC_RV:
                                        printf("TC_NELC_RV 转速\n");
                                        break;
                                        
                                    case TC_NELC_420MA:
                                        printf("TC_NELC_420MA 4~20MA\n");
                                        break;

                                    default:
                                        printf("TC_NELC_UNKOWN\n");
                                        break; 

                                }
                                
                                switch(puAppData->sFrezAutoA.sOne[i].uApp[j].sNelcValue.sDouble.ePrec)
                                {
                                    case TC_PREC_P4:
                                        printf("TC_PREC_P4");
                                        printf(" %f\n", puAppData->sFrezAutoA.sOne[i].uApp[j].sNelcValue.sDouble.dValue);
                                        break;
                                        
                                    case TC_PREC_P3:
                                        printf("TC_PREC_P3");
                                        printf(" %f\n", puAppData->sFrezAutoA.sOne[i].uApp[j].sNelcValue.sDouble.dValue);

                                        break;
                                        
                                    case TC_PREC_P2:
                                        printf("TC_PREC_P2");
                                        printf(" %f\n", puAppData->sFrezAutoA.sOne[i].uApp[j].sNelcValue.sDouble.dValue);
                                        
                                        break;
                                        
                                    case TC_PREC_P1:
                                        printf("TC_PREC_P1");
                                        printf(" %f\n", puAppData->sFrezAutoA.sOne[i].uApp[j].sNelcValue.sDouble.dValue);
                                        break;
                                        
                                    case TC_PREC_P0:
                                        printf("TC_PREC_P0");                    
                                        printf(" %f7.0\n", puAppData->sFrezAutoA.sOne[i].uApp[j].sNelcValue.sDouble.dValue);
                                        break;
                       
                                    case TC_PREC_N1:
                                        printf("TC_PREC_N1");                    
                                        printf(" %7.1f\n", puAppData->sFrezAutoA.sOne[i].uApp[j].sNelcValue.sDouble.dValue);
                                        break;
                                        
                                    case TC_PREC_N2:
                                        printf("TC_PREC_N2");
                                        printf(" %7.2f\n", puAppData->sFrezAutoA.sOne[i].uApp[j].sNelcValue.sDouble.dValue);
                                        break;
                                        
                                    case TC_PREC_N3:
                                        printf("TC_PREC_N3");
                                        printf(" %7.3f\n", puAppData->sFrezAutoA.sOne[i].uApp[j].sNelcValue.sDouble.dValue);
                                        break;
                       
                                    default:
                                        printf("TC_PREC_UNKOWN");                        
                                        break;
                                     
                                }
                            }
                            break;

                            case TCMD_AFN_D_F57_VOLT_A:
                            {
                                printf("sVoltA = %4.1f\n", puAppData->sFrezAutoA.sOne[i].uApp[j].sVoltA.fXXX_X);
                            }
                            break;

                            case TCMD_AFN_D_F58_VOLT_B:
                            {
                                printf("sVoltB = %4.1f\n", puAppData->sFrezAutoA.sOne[i].uApp[j].sVoltB.fXXX_X);
                            }
                            break;

                            case TCMD_AFN_D_F59_VOLT_C:
                            {
                                printf("sVoltC = %4.1f\n", puAppData->sFrezAutoA.sOne[i].uApp[j].sVoltC.fXXX_X);
                            }
                            break;
                            
                            
                            default:
                                break;
                        }

                    }

                }
            
                
           }
        }
        break;
        
        case TCMD_AFN_D_F2_PARA_STATE:
        {

            printf("ucNum\t= %d\n", puAppData->sParaState.ucNum);
            for (i = 0; i < puAppData->sParaState.ucNum; i++)
            {
                printf("eCmd[%2d]  = %04X ",i, puAppData->sParaState.eCmd[i]);
                eRet = eTcGetCmdInfor(puAppData->sParaState.eCmd[i], TC_DIR_M2S, &sCmdInfo);
                if(TC_OK != eRet)
                {
                    printf("未知设置参数命令\n");
                }
                else
                {
                     printf("%s\n", sCmdInfo.pName);
                }
            }
        }
        break;

        case TCMD_AFN_D_F3_EVENT_1:
        {

            printf("usEc1\t= %d\n", puAppData->usEc1);           
        }
        break;  
        
        case TCMD_AFN_D_F4_EVENT_2:
        {

            printf("usEc2\t= %d\n", puAppData->usEc2);          
        }
        break;
        
        case TCMD_AFN_D_F6_POWR_TIMES:
        case TCMD_AFN_D_F105_VMPP_TIME_A:
        case TCMD_AFN_D_F106_VMPP_TIME_B:
        case TCMD_AFN_D_F107_VMPP_TIME_C:
        case TCMD_AFN_D_F108_VMNN_TIME_A:
        case TCMD_AFN_D_F109_VMNN_TIME_B:
        {

            printf("(+)NNNNN\t= %d\n", puAppData->sPowerTimes.ulTimes);          
        }
        break;
        
        case TCMD_AFN_D_F5_EVENT_STATE:
        {
             for(i = 0; i < TC_ERC_20_NELC_OVER; i++)
             {
                 printf("ERC[%d] = %s\n",i, puAppData->sEventState.bHave[i] == TRUE ? "true":"false");
             }
        }
        break;

        case TCMD_AFN_D_F25_POWR_HAVE_T:
        case TCMD_AFN_D_F26_POWR_NONE_T:
        case TCMD_AFN_D_F33_DEMAND:
        case TCMD_AFN_D_F34_DEMAND_MAX:
        case TCMD_AFN_D_F64_CIRCLE_V:
        case TCMD_AFN_D_F89_TFW_HAVE:
        case TCMD_AFN_D_F90_TFW_NONE:
        case TCMD_AFN_D_F91_THW_HAVE:
        case TCMD_AFN_D_F92_THW_NONE:
        {
            printf("fXX.XXXX = %6.4f", puAppData->sPowerHaveT.fXX_XXXX);
        }

        break;
        
        case TCMD_AFN_D_F27_FACTR_T:
        case TCMD_AFN_D_F28_FACTR_A:
        case TCMD_AFN_D_F29_FACTR_B:
        case TCMD_AFN_D_F30_FACTR_C:
        case TCMD_AFN_D_F41_POWR_HAVE_A:
        case TCMD_AFN_D_F42_POWR_HAVE_B:
        case TCMD_AFN_D_F43_POWR_HAVE_C:
        case TCMD_AFN_D_F44_POWR_NONE_A:
        case TCMD_AFN_D_F45_POWR_NONE_B:
        case TCMD_AFN_D_F46_POWR_NONE_C:   
        case TCMD_AFN_D_F63_VOLT_UBL:
        {
            printf("fXX.XX = %4.2f", puAppData->sFactorT.fXX_XX);
        }
        break;

        case TCMD_AFN_D_F35_DEMAND_TIME:
        case TCMD_AFN_D_F74_VDMAX_A_TIME:
        case TCMD_AFN_D_F76_VDMAX_B_TIME:
        case TCMD_AFN_D_F78_VDMAX_C_TIME:
        case TCMD_AFN_D_F82_IDMAX_A_TIME:
        case TCMD_AFN_D_F84_IDMAX_B_TIME:
        case TCMD_AFN_D_F86_IDMAX_C_TIME:
        {
            printf("YY\t= %d\n", puAppData->sDemandTime.sTime.ucYY);
            printf("MM\t= %d\n", puAppData->sDemandTime.sTime.ucMM);
            printf("DD\t= %d\n", puAppData->sDemandTime.sTime.ucDD);
            printf("HH\t= %d\n", puAppData->sDemandTime.sTime.ucHH);
            printf("mm\t= %d\n", puAppData->sDemandTime.sTime.ucmm);
        }
        break;
        
        case TCMD_AFN_D_F49_POWR_HAVE_FRTH:
        case TCMD_AFN_D_F50_POWR_HAVE_BACK:
        {
            printf("fXX.XXXX = %10.4f", puAppData->sPowerHaveFrth.dXXXXXX_XXXX);
        }
        break;

        case TCMD_AFN_D_F51_POWR_NONE_FRTH:
        case TCMD_AFN_D_F52_POWR_NONE_BACK:
        {
            printf("fXXXXXX.XX = %8.2f", puAppData->sPowerNoneFrth.dXXXXXX_XX);
        }
        break;

        case TCMD_AFN_D_F57_VOLT_A:
        case TCMD_AFN_D_F58_VOLT_B:
        case TCMD_AFN_D_F59_VOLT_C:
        {
            printf("fXXX.X = %4.1f\n", puAppData->sVoltA.fXXX_X);
        }
        break;

        case TCMD_AFN_D_F65_ELEC_A:
        case TCMD_AFN_D_F66_ELEC_B:
        case TCMD_AFN_D_F67_ELEC_C:
        case TCMD_AFN_D_F68_ELEC_M:
        case TCMD_AFN_D_F81_IDMAX_A:
        case TCMD_AFN_D_F83_IDMAX_B:
        case TCMD_AFN_D_F85_IDMAX_C:
        {
            printf("(+/-)XXX.XXX = %6.3f\n", puAppData->sElecA.fsXXX_XXX);
        }
        break;  

        case TCMD_AFN_D_F60_VANGL_A:
        case TCMD_AFN_D_F61_VANGL_B:
        case TCMD_AFN_D_F62_VANGL_C:
        {
            printf("fsXXX.X = %4.1f\n", puAppData->sVAngleA.fsXXX_X);
        }
        break;

        case TCMD_AFN_D_F145_HARM_VOLT_A:
        case TCMD_AFN_D_F146_HARM_VOLT_B:
        case TCMD_AFN_D_F147_HARM_VOLT_C:
        {
            printf("ucN = %d\n", puAppData->sHarmVoltA.ucN);
            for(i = 0; i < puAppData->sHarmVoltA.ucN; i++)
            {
               printf("(+)XXX_X[%d] = %4.1f\n", i, puAppData->sHarmVoltA.fXXX_X[i]);
            }
          
        }
        break;  
        
        case TCMD_AFN_D_F148_HARM_ELEC_A:
        case TCMD_AFN_D_F149_HARM_ELEC_B:
        case TCMD_AFN_D_F150_HARM_ELEC_C:
        {
            printf("ucN = %d\n", puAppData->sHarmElecA.ucN);
            for(i = 0; i < puAppData->sHarmElecA.ucN; i++)
            {
               printf("(+/-)XXX_XXXX[%d] = %6.3f\n", i, puAppData->sHarmElecA.fsXXX_XXX[i]);
            }
          
        }
        break;  


        case TCMD_AFN_D_F153_HARM_VINC_A:
        case TCMD_AFN_D_F154_HARM_VINC_B:
        case TCMD_AFN_D_F155_HARM_VINC_C:
        case TCMD_AFN_D_F156_HARM_EINC_A:
        case TCMD_AFN_D_F157_HARM_EINC_B:
        case TCMD_AFN_D_F158_HARM_EINC_C:
        {
            printf("ucN = %d\n", puAppData->sHarmVincA.ucN);
            for(i = 0; i < puAppData->sHarmVincA.ucN; i++)
            {
               printf("(+)XX_XX[%d] = %4.2f\n", i, puAppData->sHarmVincA.fXX_XX[i]);
            }
          
        }
        break;  
        
        case TCMD_AFN_D_F233_NELC_VALUE:
        {
            printf("eType = %d", puAppData->sNelcValue.eType);
            switch(puAppData->sNelcValue.eType)
            {
                case TC_NELC_TEMP:
                    printf("TC_NELC_TEMP 温度\n");
                    break;
                    
                case TC_NELC_FLOW:
                    printf("TC_NELC_FLOW 流量\n");
                    break;

                case TC_NELC_FV:
                    printf("TC_NELC_FV 流速\n");
                    break;

                case TC_NELC_PRESS:
                    printf("TC_NELC_PRESS 压力\n");
                    break;
                    
                case TC_NELC_HUMI:
                    printf("TC_NELC_HUMI 温度\n");
                    break;
                    
                case TC_NELC_LIGHT:
                    printf("TC_NELC_LIGHT 照度\n");
                    break;

                case TC_NELC_RV:
                    printf("TC_NELC_RV 转速\n");
                    break;
                    
                case TC_NELC_420MA:
                    printf("TC_NELC_420MA 4~20MA\n");
                    break;

                default:
                    printf("TC_NELC_UNKOWN\n");
                    break; 

            }
            
            switch(puAppData->sNelcValue.sDouble.ePrec)
            {
                case TC_PREC_P4:
                    printf("TC_PREC_P4");
                    printf(" %f\n", puAppData->sNelcValue.sDouble.dValue);
                    break;
                    
                case TC_PREC_P3:
                    printf("TC_PREC_P3");
                    printf(" %f\n", puAppData->sNelcValue.sDouble.dValue);

                    break;
                    
                case TC_PREC_P2:
                    printf("TC_PREC_P2");
                    printf(" %f\n", puAppData->sNelcValue.sDouble.dValue);
                    
                    break;
                    
                case TC_PREC_P1:
                    printf("TC_PREC_P1");
                    printf(" %f\n", puAppData->sNelcValue.sDouble.dValue);
                    break;
                    
                case TC_PREC_P0:
                    printf("TC_PREC_P0");                    
                    printf(" %f7.0\n", puAppData->sNelcValue.sDouble.dValue);
                    break;
   
                case TC_PREC_N1:
                    printf("TC_PREC_N1");                    
                    printf(" %7.1f\n", puAppData->sNelcValue.sDouble.dValue);
                    break;
                    
                case TC_PREC_N2:
                    printf("TC_PREC_N2");
                    printf(" %7.2f\n", puAppData->sNelcValue.sDouble.dValue);
                    break;
                    
                case TC_PREC_N3:
                    printf("TC_PREC_N3");
                    printf(" %7.3f\n", puAppData->sNelcValue.sDouble.dValue);
                    break;
   
                default:
                    printf("TC_PREC_UNKOWN");                        
                    break;
                 
            }

            
        }
        break;


    #endif
        default:
        {
            show_error("没有数据域,或未实现显示\n");
        }
        break;

    }
}

/*****************************************************************************
 函 数 名  : show_app_data
 功能描述  : 显示应用层数据
 输入参数  : smtSub *pSub  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2014年1月7日 星期二
    作    者   : liming
    修改内容   : 新生成函数

*****************************************************************************/
void show_app_data(eTcDir eDir, sTcData *pSub)
{
   if(!pSub)
   {
      return;
   }

    sTcmdInfor    sCmdInfor   = {0};
    eTcErr        eRet        = TC_OK;    
  
   // sub cmd
   printf("sCmd  = %04X\t\t", pSub->eCmd);
   show_sub_name("子命令ID\t");
   eRet = eTcGetCmdInfor(pSub->eCmd, eDir, &sCmdInfor);
   if(eRet != TC_OK)
   {
        show_error("错误的命令类型!");
        return;
   }
   else
   {
        show_item_value(sCmdInfor.pName);
   }
   printf("\n");

   //pn 
   printf("usPN  = %d\t\t", pSub->usPN);
   show_sub_name("信息点PN\t");
   switch(sCmdInfor.ePn)
   {
       case TC_PN_P0:
        show_item_value("PN无关");
        break;
        
       case TC_PN_TM:
        show_item_value("终端号");
        break;
        
       case TC_PN_MP:
        show_item_value("测量点号");
        break;

       case TC_PN_TK:
        show_item_value("任务号");
        break;
        
       default:
        show_error("未知PN 类型");
        break;
   }

    show_main_name("\n数据单元:\t");

      // 应用层数据
    if(sCmdInfor.pFunc == NULL)
    {
        printf("\t\t\t");
        show_item_value("无数据单元");
       return;

    }
    
    // 应用层数据
    if(sCmdInfor.pFunc == NULL)
    {
       show_item_value("无数据单元");
       return;
    }

    printf("\n");
    // 有应用层数据
    show_app_sub_data(eDir, pSub->eCmd, &(pSub->uApp));
    
}

// 详细显示一个报文的内容
void show_pack(stcPack *psUnpack)
{
    if(!psUnpack)
    {
        printf("psUnpack is null\n");
        return;
    }

    char *pstr = NULL;
    char str_reg[7]  = {0};
    char str_pw[17]  = {0};
    char strTmp[128] = {0};
    int i = 0;
    int nSubNum = 0;
    eTcDir eDir;
    BOOL bFixed = FALSE;

    // 输出地址信息
    show_main_name("address:");
    memcpy(str_reg,psUnpack->sAddress.acRegionCode, TC_REGN_LEN);

    printf("\nreg   = %s\t\t", str_reg);
    show_sub_name("区域码");

    printf("\nmst   = %d\t\t",    psUnpack->sAddress.ucConAddress);
    show_sub_name("集中器地址");
    
    printf("\ntml   = %d\t\t",    psUnpack->sAddress.ulTmlAddress);
    show_sub_name("终端地址");
    
    printf("\nteam  = %s\t\t",    psUnpack->sAddress.bTeam == TRUE ? "true" : "false");
    show_sub_name("是否为组地址\t");
    (psUnpack->sAddress.bTeam == TRUE ) ? show_item_value("是") : show_item_value("否");

    // 是否为固定帧
    show_main_name("\nframe:");
    bFixed = psUnpack->bFixed;
    printf("\nfix   = %s\t\t",bFixed == TRUE ? "true":"false");
    if(TRUE == bFixed)
    {
        show_sub_name("固定帧");
    }
    else
    {
        show_sub_name("可变帧");
    }

    // 控制域
    show_main_name("\nctrl:\n");
    printf("dir   = %s\t\t",psUnpack->sCtrl.eDir == TC_DIR_C2T ? "c2t":"t2c");
    (psUnpack->sCtrl.eDir == TC_DIR_C2T) ? show_sub_name("集中器到终端") : show_sub_name("终端到集中器");

    eDir = psUnpack->sCtrl.eDir;
    
    printf("\nprm   = %s\t\t",psUnpack->sCtrl.ePRM == TC_PRM_A2P ? "a2p":"p2a");
    (psUnpack->sCtrl.ePRM == TC_PRM_A2P) ? show_sub_name("启动站到从动站") : show_sub_name("从动站到主动站");

    printf("\npseq  = %d\t\t",psUnpack->sCtrl.ucPSEQ );
    show_sub_name("启动帧序列号");
    
    printf("\nrseq  = %d\t\t",psUnpack->sCtrl.ucRSEQ);
    show_sub_name("响应帧序列号");
    
    printf("\nfcode = %d\t\t",psUnpack->sCtrl.eFcode);
    show_sub_name("功能码");
    
    if(bFixed == TRUE)
    {
        switch(psUnpack->sCtrl.eFcode)
        {
            case TC_FCD_LINK_OK:
            pstr = "链路确认";
            break;

            case TC_FCD_LOG_IN:
            pstr = "建立链路、登录系统";
            break;

            case TC_FCD_LOG_OUT:
            pstr = "拆除链路、退出系统";
            break;

            case TC_FCD_HEART_BEAT:
            pstr = "保持链路、在线心跳";
            break;

            default:
            pstr = "错误的功能码";
            break;

        }
    }
    else
    {
        switch(psUnpack->sCtrl.eFcode)
        {
            case TC_FCD_OK:  
            //case TC_FCD_NOTI:
                if(psUnpack->sCtrl.ePRM == TC_PRM_A2P)
                {
                     pstr = "发送/无回答";
                }
                else
                {
                     pstr = "链路用户确认";
                }
           
            break;

            case TC_FCD_ANSWER:
            //case TC_FCD_CONF:
                if(psUnpack->sCtrl.ePRM == TC_PRM_A2P)
                {
                    pstr = "以用户数据响应请求";
                }
                else
                {
                    pstr = "发送/确认";
                }
          
            break;
            
            case TC_FCD_ASK:
            pstr = "请求/响应";
            break;

            default:
            pstr = "错误的功能码";
            break;
        }

    }
    
    printf("\t\t");
    show_item_value(pstr);
    
    // 链路用户数据
    printf("\n");
    //show_main_name("link:");
    //printf("\nproto = ");
    

    if(bFixed == TRUE)
    {
        
    }
    else
    {
        // 应用控制域
        show_main_name("ac:");
        printf("\nbtp   = %s\t\t",psUnpack->sAc.bTp == TRUE ? "true" : "false");
        show_sub_name("是否有时间标签");
        printf("\t");
        (psUnpack->sAc.bTp == TRUE) ? show_item_value("有") : show_item_value("无");


        printf("\nbec   = %s\t\t",psUnpack->sAc.bEc == TRUE ? "true" : "false");
        show_sub_name("是否有事件计数");
        printf("\t");

        (psUnpack->sAc.bEc == TRUE) ? show_item_value("有") : show_item_value("无");


        printf("\nafn   = %d\t\t", psUnpack->sAc.eAfn);
        show_sub_name("应用功能码");
        printf("\t");
        switch(psUnpack->sAc.eAfn)
        {
            case TC_AFN_00_CONF:
                show_item_value("确认否认");
                break;      
                
            case TC_AFN_01_RSET:
                show_item_value("复位");
                break;   
                
            case TC_AFN_04_SETP:
                show_item_value("设置参数");
                break;  
                
            case TC_AFN_05_CTRL:
                show_item_value("控制命令");
                break;          
                
            case TC_AFN_06_AUTH:
                show_item_value("身份认证及密钥协商");
                break;      
                

             case TC_AFN_10_GETP:
                show_item_value("查询参数");
                break;   
                
            case TC_AFN_12_ASKT:
                show_item_value("请求（定时上报）任务数据");
                break;  
                
            case TC_AFN_13_ASKR:
                show_item_value("请求实时数据");
                break;          
                
            case TC_AFN_14_ASKE:
                show_item_value("请求（主动上报）事件记录");
                break;      
                
            case TC_AFN_15_FILE:
                show_item_value("文件传输");
                break;
                       
            case TC_AFN_16_DATA:
                show_item_value("数据转发");
                break;

            default:
                show_item_value("未知AFN");
                break;

        }

        // 附加域AUX
        printf("\n");
        show_main_name("aux:");

        printf("\nbec   = %s\t\t",psUnpack->sAc.bEc == TRUE ? "true" : "false");
        printf("\nbpw   = %s\t\t",psUnpack->bPw == TRUE ? "true" : "false");
        printf("\nbtp   = %s\t\n",psUnpack->sAc.bTp == TRUE ? "true" : "false");


        // pw
        if(psUnpack->bPw == TRUE)
        {
              show_main_name("pw:");

            memcpy(str_pw, psUnpack->aPw, TC_PW_LEN);
            
            printf("\ntxt   = %s\t", str_pw);

            show_sub_name("消息认证码");
            printf("\nhex   = ");
            for(i = 0; i < TC_PW_LEN; i++)
            {
                printf("%02X ", psUnpack->aPw[i]);
            }
            printf("\n");
        }
        else
        {
            
        }

        // ec
        if(TRUE == psUnpack->sAc.bEc)
        {
            printf("\n");
            show_main_name("ec:");
            printf("\nEC1   = %d\n",  psUnpack->sEc.usEC1);
            printf("EC2   = %d\n",    psUnpack->sEc.usEC1);
            
        }

        // tp
        if(TRUE == psUnpack->sAc.bTp)
        {
            show_main_name("tp:");
            #if 0
            printf("\ntime  = %d日%d时%d分%d秒\t",  
                    psUnpack->sTp.sTime.ucDD,
                    psUnpack->sTp.sTime.ucHH,
                    psUnpack->sTp.sTime.ucmm,
                    psUnpack->sTp.sTime.ucss);
            show_sub_name("允许发送传输延时时间\n");
            #endif
            
            printf("\nucDD  = %d\n", psUnpack->sTp.sTime.ucDD);
            printf("ucHH  = %d\n", psUnpack->sTp.sTime.ucHH);
            printf("ucmm  = %d\n", psUnpack->sTp.sTime.ucmm);
            printf("ucss  = %d\t", psUnpack->sTp.sTime.ucss);

            printf("%d", psUnpack->sTp.sTime.ucDD);
            show_sub_name("日"); 
            printf("%d", psUnpack->sTp.sTime.ucHH);
            show_sub_name("时"); 
            printf("%d", psUnpack->sTp.sTime.ucmm);
            show_sub_name("分");
            printf("%d", psUnpack->sTp.sTime.ucss);
            show_sub_name("秒"); 

             printf("\ndelay = %d\t",    psUnpack->sTp.ucPermitDelayMinutes);
            show_sub_name("允许发送传输延时时间");
       
        }
        
    }


    // 应用层数据
    printf("\n");
    show_main_name("app_data:\n");
    nSubNum = psUnpack->usNum;
    printf("num  = %d\t\t", nSubNum);
    show_sub_name("子命令个数\n");

    for(i = 0; i < nSubNum; i++)
    {
        //printf("app data %d\n", i+1);
        sprintf(strTmp, "\n-------------------------- %d -----------------------------\n", i+1);
        fm_print(strTmp, FR_GREEN|FM_BOLD);
        show_app_data(eDir, &(psUnpack->sData[i]));
        printf("\n\n");
        //fm_print(strTmp, FR_GREEN|FM_BOLD);
    }
    
    #if 0
    

    // 主功能码
   


  

    // 应用层数据
    show_main_name("app_data:\n");
    nSubNum = psUnpack->usDataNum;
    printf("subNum = %d\t", nSubNum);
    show_sub_name("子命令个数\n");

    for(i = 0; i < nSubNum; i++)
    {
        //printf("app data %d\n", i+1);
        sprintf(strTmp, "\n-------------------------- %d -----------------------------\n", i+1);
        fm_print(strTmp, FR_GREEN|FM_BOLD);
        show_app_data(eDir, &(psUnpack->sData[i]));
        printf("\n\n");
        //fm_print(strTmp, FR_GREEN|FM_BOLD);
    }

    #endif
    printf("\n");
}


// 协议解析测试
void run_unpack_test(int nstart, int argc, char *argv[])
{
    INT32    i, j     = 0;
    UINT16   usLen    = 0;
    UINT16   usfLen   = 0; // 第一个有效帧的长度
    UINT16   usfPos   = 0; // 第一个有效帧相对地址偏移
    eTcErr   eRet     = TC_OK;
    UINT8   *pInBuf   = NULL;
    stcPack *pstcPack = NULL;
    char    *str      = NULL;
    sTcInit  sInit;

    // 解决命令行输入的参数
    for(i = nstart; i < argc; i++)
    {
        g_ucInBuf[j++] = strtol(argv[i], NULL,16);
        //printf(" %02X", (unsigned int)strtol(argv[i], NULL,16));
    }

    usLen    = argc - nstart;
    pInBuf   = (UINT8*)g_ucInBuf;
    pstcPack = (stcPack *)malloc(TC_USER_MAX);
    if(!pstcPack)
    {
        show_error("run_unpack_test malloc failed!\n");
        return;
    }
    
    // 初始化协议
    sInit.eRole = TC_ROLE_CONTOR;
    sInit.ucPermitDelayMinutes = 255;
    eTcInit(&sInit);

    // 找到第一个有效的帧
    eRet = etcFindValidPack(pInBuf, usLen, &usfPos, &usfLen);
    if(TC_OK != eRet)
    {
        show_error("run_unpack_test emcFindValidPack() failed!");
        str = sGetErr((eTcErr)eRet);
        printf("error code = %d %s\n", eRet, str);
        free(pstcPack);
        return; 
    }

     printf("usfLen = %d\n", usfLen);


    eRet = etcUnPack(pstcPack, pInBuf + usfPos, usfLen);
    if(TC_OK != eRet)
    {
        show_error("run_unpack_test etcUnPack() failed!");
        printf("error code = %d\n", eRet);
        free(pstcPack);
        return;
    }
    else
    {
        fm_print("--------------------------unpack success-------------------------\n",FR_GREEN);
        // 显示解析结构
        show_pack(pstcPack); 
        fm_print("--------------------------unpack success-------------------------\n",FR_GREEN);

    }
}



int main(int argc, char *argv[])
{
    int  opt       = 0;
    int  longIndex = 0;
    int  iTest     = 0;          // 测试例ID
    BOOL bActive   = FALSE;      // 是否为主动帧
    BOOL bC2T      = FALSE;      // 是否为下行报文
    char *strOpt   = "duohctasjp:";

    struct option longOpts[] =
    {
        /* 命令行说明
           -a [68 .. ] 分析报文-将各字段进行详细的分析
           -u [68 .. ] 解析报文
           -p [0xcmd] {-c | -m} {-o}
           -c 集中器到终端方向
           -t 终端到集中器方向
           -o 是否主动上报
           -h 帮助
        */

        {"pack",        required_argument,    NULL,    'p'},
        {"c2t",         no_argument,          NULL,    'c'},
        {"t2c",         no_argument,          NULL,    't'},
        {"auto",        no_argument,          NULL,    'o'},
        {"help",        no_argument,          NULL,    'h'},
        {"unpack",      no_argument,          NULL,    'u'},
        {"dunpack",     no_argument,          NULL,    'd'},  // 用适配层的接口来解析
        {"analyze",     no_argument,          NULL,    'a'},
        {"all",         no_argument,          NULL,    's'},
        {"cs",          no_argument,          NULL,    'j'},
        {NULL,          no_argument,          NULL,     0}
    };

    while((opt = getopt_long(argc, argv,strOpt, longOpts, &longIndex)) != -1)
    {
        switch(opt)
        {
            case 'h':
                {
                   char *pstr = "能效国标(3-2) 协议解析工具 v1.0 (vliming@126.com)\n\n"
                               "-a [68 .. ] 分析报文-将各字段进行详细的分析"
                               "-u [68 .. ] 解析报文\n"
                               "-p [0xcmd] {-c | -m} {-o}\n"
                               "\t-c 集中器到终端方向\n"
                               "\t-t 终端到集中器方向\n"
                               "\t-o 是否主动上报\n"
                               "-h 帮助\n\n";

                     fm_print(pstr, FR_GREEN|FM_BOLD);

                }
                  break;

            case 'a':
                unpack_analyse(optind, argc, argv);
                break;

            case 'c':
                bC2T = TRUE;
                break;

            case 't':
                 bC2T = FALSE;
              break;

            case 'o':
                 bActive = TRUE;
                break;

            case 'p':
                iTest = (int)strtol(optarg, NULL, 16);
                //printf("test id = %04X\n", iTest);
                run_pack_test(iTest, bActive, bC2T);
                break;

            case 'u':
                run_unpack_test(optind, argc, argv);
                break;
                
            case 'd':
                //run_unpack_test_adp(optind, argc, argv);
                break;
                
                case 's':
                //show_all_cmd();
                break;

                case 'j':
                //show_check_sum(optind, argc, argv);
                break;

              default:
                  printf("Your command line parameters are not right!\n");
                return -1;


        }

    }
    return 0;

    int very_longer_variable1, very_longer_variable3, very_longer_variable5;
    int very_longer_variable12, very_longer_variable14, very_longer_variable16;

    if ((very_longer_variable1 >= very_longer_variable12)  
        && (very_longer_variable3 <= very_longer_variable14)  
        && (very_longer_variable5 <= very_longer_variable16))
    {
        dosomething();
    }

}

