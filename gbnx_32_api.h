/******************************************************************************

                  版权所有 (C), 2005-2015, 国家电网通信与用电技术分公司

 ******************************************************************************
  文 件 名   : gbnx_32_api.h
  版 本 号   : 初稿
  作    者   : liming
  生成日期   : 2013年10月17日
  最近修改   :
  功能描述   : GB/T XXXX.32 2013 主站与采集终端通信协议解析api(C语言)
               该文件给出国家电力能力监测系统技术规范(国标) 
               第3-2部分  电力能效监测终端通信协议
               相关的定义及协议解析的基本接口
               
  缩写说明   : 主站              master       -> m 
               交互终端(集中器)  concentrator -> c
               采集终端(终端)    terminal     -> t

               用户侧数据(默认字节对齐)
               封帧侧数据(用1 字节对齐)

  函数列表   :
  修改历史   :
  1.日    期   : 2013年10月17日
    作    者   : liming(vliming@126.com)
    修改内容   : 创建文件

******************************************************************************/
#ifndef _GBNX_32_API_H_
#define _GBNX_32_API_H_


/*******************************************************
 *  配置文件 编译宏
 *  用此API之前请配置好
 *
{*///
#ifndef _TYPE_DEF_LM_
#define _TYPE_DEF_LM_
#ifndef __RTL_H__
#define __RTL_H__
typedef char                BOOL;
#endif
#define TRUE                (1)
#define FALSE               (0)
typedef unsigned char       UCHAR;
typedef char                CHAR;
typedef unsigned short      USHORT;
typedef short               SHORT;
typedef unsigned long       ULONG;
typedef long                LONG;

#ifndef _TYPE_DEF_
#define _TYPE_DEF_
typedef char                INT8;       //c
typedef short               INT16;      //s
typedef int                 INT32;      //l
typedef unsigned char       UINT8;      //uc
typedef unsigned short      UINT16;     //us
typedef unsigned int        UINT32;     //ul

#ifdef MACHINE_64_BITS
typedef long                INT64;
typedef unsigned long       UINT64;
#else
typedef long long           INT64;
typedef unsigned long long  UINT64;
#endif

typedef char*               STRING;     // str
typedef char                ISBOOL;     // b
typedef unsigned int        IPADDR;     // ip
typedef double              DOUBLE;
typedef void*               FRWK_HANDLE;
#endif
#endif
///*}

/*******************************************************
 *  配置文件 编译宏
 *  用此API之前请配置好
 *
{*///

#define TC_CFG_SPT_TML         (1)         // 是否支持终端   配置文件 不支持将其改为 0
#define TC_CFG_SPT_CON         (1)         // 是否支持集中器 配置文件 不支持将其改为 0
#define TC_CFG_MEDIUM_NET      (1)         // 通信介质,将决定报文的最大长度 如果是以太置1 不是置0
#define TC_CFG_ENCRYPT         (0)         // 是否需要加密
#define TC_CFG_EC              (1)         // 附加域中默认允许加上Ec 
#define TC_CFG_TP              (1)         // 附加域中默认允许加上Tp
#define TC_CFG_PW              (1)         // 附加域中默认允许加上Pw
#define TC_CFG_IP_VER          (1)         // IP地址的版本 1-IPV4 0-IPV6    
#define TC_CFG_NAME            (1)         // 是否记录命令码的名字, 在终端代码空间较小的情况下将该宏置0
///*}

/*******************************************************
 *  协议相关宏定义
 *
{*///

#define TC_PROTO_VERSION       (0x41)       // 本协议版本

#define TC_METER_ADDR_LEN      (12)         // 电表地址长度
/****************************************
 *  地址域
 *  终端地址A2选址范围为1～65535。
 *  A2=0000H为无效地址，A2=FFFFH且A3的D0位为"1"时表示系统广播地址。
 *
 *
 *
{*///

#define TC_TML_ADDR_MIN        (1)         // 终端或集中器地址最大值
#define TC_TML_ADDR_MAX        (65535)     // 主站地址最大值
#define TC_TML_ADDR_BRD        (0xFFFF)    // 主站地址最大值

#define TC_MST_ADDR_MIN        (0)         // 主站地址最大值
#define TC_MST_ADDR_MAX        (127)       // 主站地址最大值

///*}

/****************************************
 *  应用数据域 数据单元标识
 *  对于一个确定的DaDt结构,最大支持 8个Pn 同时各对应用于下边 8个Fn
 *  所以需要 8*8个数据单元
 *
 *
 *
{*///

#define TC_PN_INDEX_MAX        (8)          // 用于数据单元的组织
#define TC_FN_INDEX_MAX        (8)          // 用于数据单元的组织
///*}


/****************************************
 *  解封、封装相关部分字节长
 *
 *
 *
{*///
#define TC_PW_LEN              (16)         // 消息认证长度
#define TC_PN_MAX              (2040)       // 数据单元标识 DA Pn 最大值
#define TC_PN_MIN              (0)          // 数据单元标识 Da Pn 最小值
#define TC_PN_NONE             (0xFFFF)     // 数据单元标识 Da Pn 无效值 即不用关心的值
 
#define TC_FN_MAX              (248)        // 数据单元标识 Dt Fn 最大值
#define TC_FN_MIN              (1)          // 数据单元标识 Dt Fn 最小值
#define TC_FN_NONE             (0xFF)       // 数据单元标识 Dt Fn 无效值 即不用关心的值

#define TC_UNIT_DATA_MAX       (128)        // 最大的数据单元字长

#define TC_FRM_MAX_WRLESS      (255)        // 采用专用无线数传信道,长度L1不大于255
#define TC_FRM_MAX_NET         (16384)      // 采用网络传输,长度L1不大于16383
#define TC_SEQ2CS_MAX          (2048)       // 每单帧允许SEQ与CS之间数据字节数最大值
#define TC_CA_LEN              (10)         // 控制域与地址域总字长
#define TC_VAC_LEN             (2)          // 变长帧中协议标识与应用控制域AC字节长度
#define TC_CANS_LEN            (8)          // 控制域C 地址域A AFN SEQ字节总长
#define TC_UN_USER_LEN         (8)          // 报文中非数据域总长度  0x68 0x68 L L CS 0x16
#define TC_DADT_LEN            (4)          // 数据标识字长 DaDt
#define TC_AFN_LEN             (1)          // AFN 字长
#define TC_DADT_ERR_LEN        (TC_DADT_LEN + 1)  // DaDt 与 ERR总字长


// 帧的最大字长
#if TC_CFG_MEDIUM_NET
#define TC_FRM_LEN_MAX         TC_FRM_MAX_NET
#else
#define TC_FRM_LEN_MAX         TC_FRM_MAX_WRLESS
#endif

#define TC_CS_LEN              (1)                          // 校验和CS字长
#define TC_FIXED_USR_LEN       (TC_A_LEN + TC_C_LEN + 1)    // 固定帧用户数据域字长 (控制域C + 地址域A + 链路用户数据D)
#define TC_FIXED_LEN           (TC_FIXED_USR_LEN + 3)       // 固定帧字长           (用户数据域 + 起始字符+ CS)
#define TC_STCHAR_FIXED        (0x10)                       // 固定帧起始字符
#define TC_STCHAR_ALTER        (0x68)                       // 可变帧起始字符
#define TC_FRM_END_CHAR        (0x16)                       // 结束符
#define TC_ALTER_USR_OTHER_LEN (TC_A_LEN + TC_C_LEN)        // 可变帧用户数据域字长(除链路用户数据)
#define TC_ALTER_BUT_USER_LEN  (8)                          // 可变帧除了(用户数据域之外的长度)
#define TC_ALTER_OTHER_LEN     (TC_ALTER_USR_OTHER_LEN + 8) // 可变帧除了链路用户数据外部分字长

#define TC_A2CS_BYTE_MAX       (TC_FRM_LEN_MAX - TC_ALTER_OTHER_LEN)  // 每单帧允许A与CS之间数据字节数最大值
#define TC_USER_MAX            (2*TC_A2CS_BYTE_MAX)                   // 用户侧等变长结构 stcPack stcBasePack 最大长度


// 帧的最小字长
#define TC_FRM_LEN_MIN         (TC_FIXED_LEN)               // 心跳、登录的帧长最小

// IP地址长度
#if TC_CFG_IP_VER
#define TC_IP_LEN              (4)                          // 对应IPv4 地址长度
#else 
#define TC_IP_LEN              (16)                         // 对应Ipv6 地址长度
#endif
///*}

/*******************************************************
 *  错误码定义 eTcErr
 *
{*///
typedef enum
{  
    TC_OK,             // 无错误                    0
    TC_ERR_NULL,       // 指针为空                  1
    TC_ERR_OUTRNG,     // 参数越界                  2
    TC_ERR_NONE,       // 不存在,没有找到           3
    TC_ERR_IO,         // IO错误                    4
    TC_ERR_RES,        // 资源不足                  5
    TC_ERR_INIT,       // 没有初始化                6
    TC_ERR_PARA,       // 参数错误                  7
    TC_ERR_FN,         // 指定Afn 中不支持的 Fn     8
    TC_ERR_PN,         // 指定Afn 中不支持的 Pn     9
    TC_ERR_ADDR,       // 无效地址                  10
    TC_ERR_CTRL,       // 控制域错误                11
    TC_ERR_0x10,       // SEQ域错误                 12
    TC_ERR_A2CS,       // A2CS 错误错误             13
    TC_ERR_AFN,        // AFN 错误                  14
    TC_ERR_UNCOMP,     // 不完整的协议包            15
    TC_ERR_0x68,       // 错误的报文起始            16
    TC_ERR_PROTO,      // 错误的协议标识            17
    TC_ERR_CS,         // 错误的检测和              18
    TC_ERR_0x16,       // 错误的结尾符              19
    TC_ERR_LOGIC,      // 错误的处理逻辑            20
    TC_ERR_PACK,       // 不是一个有效的包          21
    TC_ERR_PFC,        // 序列号不对应              22
    TC_ERR_TIMEOUT,    // 报文超时                  23
    TC_ERR_PRM,        // 启动站标识错              24
    TC_ERR_TEAM,       // Fn或Pn不在同一个组        25
    TC_ERR_ENCRYPT,    // 加密错误                  26
    TC_ERR_DECRYPT,    // 解密错误                  27
    TC_ERR_L1L2,       // 帧中的L1和L2不相等        28
    TC_ERR_FCODE,      // 功能码错误                29
    TC_ERR_DIR,        // 报文的方向错误            30
    
}eTcErr;    
///*} 

/*******************************************************
 *  应用层功能码 AFN
 *
{*///
typedef enum
{
    TC_AFN_00_CONF  = 0x00,     // 确认否认
    TC_AFN_01_RSET  = 0x01,     // 复位
    TC_AFN_02_LINK  = 0x02,     // 链路控制  抽象出来的 协议本来没有 
    TC_AFN_04_SETP  = 0x04,     // 设置参数
    TC_AFN_05_CTRL  = 0x05,     // 控制命令
    TC_AFN_06_AUTH  = 0x06,     // 身份认证及密钥协商
    TC_AFN_10_GETP  = 0x0A,     // 查询参数
    TC_AFN_12_ASKT  = 0x0C,     // 请求（定时上报）任务数据
    TC_AFN_13_ASKR  = 0x0D,     // 请求实时数据 
    TC_AFN_14_ASKE  = 0x0E,     // 请求（主动上报）事件记录 
    TC_AFN_15_FILE  = 0x0F,     // 文件传输
    TC_AFN_16_DATA  = 0x10,     // 数据转发
    TC_AFN_NULL     = 0xFF      // 不存在的AFN

}eTcAFN;    
 ///*} 

/*******************************************************
 *  命令码定义
 *  命名规则 TCMD_AFN_(xx)_F(xx)_NAME  
 *  xx 表示数字 
 *  F  表示信息类标识
 *  根据协议规则, 每组内的最多8个Fn可以组成一个数据标识
 *  上行: 终端或集中器到主站
 *  下行: 主站到终端或集中器
 *
{*///
typedef enum
{

    TCMD_AFN_F_UNKOWN,                                // 未知命令

    /**********************************
    * 类型: 确认/否认
    * AFN : 00H
    *  PN : p0
    * 上行: 有
    * 下行: 有
    {*///
    TCMD_AFN_0_F1_ALL_OK_DENY         = 0x0001,       // 全部确认/否认：对收到报文中的全部数据单元标识进行确认/否认 
    TCMD_AFN_0_F2_ONE_BY_ONE          = 0x0003,       // 按数据单元标识确认和否认：对收到报文中的全部数据单元标识进行逐个确认/否认
    ///*}    

    /**********************************
     * 类型: 复位命令
     * AFN : 01
     *  PN : p0 /监测终端号
     * 上行: AFN 00H 确认/否认
     * 下行: 有
    {*///
    TCMD_AFN_1_F1_HARD_INIT           = 0x0101,       // 硬件初始化
    TCMD_AFN_1_F2_DATA_INIT           = 0x0102,       // 数据区初始化
    TCMD_AFN_1_F3_FACTORY_RESET       = 0x0103,       // 参数及全体数据区初始化（即恢复至出厂配置）
    TCMD_AFN_1_F4_PARA_INIT           = 0x0104,       // 参数（除与系统主站通信有关的）及全体数据区初始化
    TCMD_AFN_1_F5_DATA_CLEAR          = 0x0105,       // 清零指定数据
    ///*}                                            

    /**********************************
     * 链路接口检测
     * AFN : 无
     *  PN : 无
     * 上行: 有(F1 ~ F3)
     * 下行: 有(F4)
     * 说明: 仅该命令帧为固定帧,其余的帧格式为可变帧
    {*///
    TCMD_AFN_2_F1_LOG_IN              = 0x0201,       // 建立链路、登录系统
    TCMD_AFN_2_F2_LOG_OUT             = 0x0202,       // 拆除链路、退出系统
    TCMD_AFN_2_F3_HEART_BEAT          = 0x0203,       // 保持链路、在线心跳
    TCMD_AFN_2_F4_LINK_OK             = 0x0204,       // 确认(登录/退出/心跳)
    ///*}

    /**********************************
     * 类型: 设置参数
     * AFN : 04
     *  PN : 分组定义
     * 上行: 有
     * 下行: 有
    {*///
    // 组1   pn:p0
    TCMD_AFN_4_F1_CON_IP_PORT         = 0x0401,       // 集中与交互终端IP地址和端口
    TCMD_AFN_4_F2_TML_UP_CFG          = 0x0402,       // 监测终端上行通信参数配置
    TCMD_AFN_4_F3_TML_AUTH_PARA       = 0x0403,       // 监测终端上行通信消息认证参数设置  
    TCMD_AFN_4_F4_TML_STATE_INPUT     = 0x0404,       // 状态量输入参数
    TCMD_AFN_4_F5_TML_EVENT_CFG       = 0x0405,       // 事件记录配置
    
    // 组3   pn:任务号 
    TCMD_AFN_4_F17_FREZ_TASK_PARA     = 0x0411,       // 冻结数据任务配置  

    // 组4   pn:电气测量点号
    TCMD_AFN_4_F25_ELEC_MP_CFG        = 0x0419,       // 电气测量点配置参数
    TCMD_AFN_4_F26_ELEC_MP_BASE       = 0x041A,       // 电气测量点基本参数 
    TCMD_AFN_4_F27_ELEC_LMIT_PARA     = 0x041B,       // 电气测量点限值参数
    TCMD_AFN_4_F28_ELEC_LMIT_FACTR    = 0x041C,       // 电气测量点总功率因数参数 
    TCMD_AFN_4_F29_ELEC_FIX_HARM      = 0x041D,       // 电气测量点谐波畸变率越限定值
    TCMD_AFN_4_F30_ELEC_FLASH         = 0x041E,       // 电气测量点闪变越限参数
    
    // 组5   pn:非电气测量点号
    TCMD_AFN_4_F33_NELC_MP_CFG        = 0x0421,       // 非电气测量点配置参数 
    TCMD_AFN_4_F34_NELC_MP_PARA       = 0x0422,       // 非电气测量点基本参数
    TCMD_AFN_4_F35_NELC_MP_LMIT       = 0x0423,       // 非电气测量点越限参数
    ///*}   

    /**********************************
     * 类型: 控制命令
     * AFN : 05
     *  PN : 分组定义
     * 上行: AFN 00H 确认/否认
     * 下行: 有
    {*///
    // 组1  pn:p0
    TCMD_AFN_5_F1_CHECK_TIME          = 0x0501,       // 校时命令
    TCMD_AFN_5_F2_FREZ_TEMP           = 0x0502,       // 临时冻结命令
    TCMD_AFN_5_F3_AUTO_SAY_ON         = 0x0503,       // 允许主动上报 
    TCMD_AFN_5_F4_AUTO_SAY_OFF        = 0x0504,       // 禁止主动上报 
    TCMD_AFN_5_F5_NX_MODEL_ACT        = 0x0505,       // 能效模型有效
    TCMD_AFN_5_F6_NX_MODEL_CLR        = 0x0506,       // 能效模型清除
    TCMD_AFN_5_F7_RQ_RESPN_ACT        = 0x0507,       // 需求响应信息有效
    TCMD_AFN_5_F8_RQ_RESPN_CLT        = 0x0508,       // 需求响应信息清除
    
    // 组2  pn:任务号    
    TCMD_AFN_5_F9_REPT_FREZ_ON        = 0x0509,       // 启动定时上报冻结数据任务
    TCMD_AFN_5_F10_REPT_FREZ_OFF      = 0x050A,       // 禁止定时上报冻结数据任务

    // 组3  pn:p0
    TCMD_AFN_5_F17_REMOTE_OFF          = 0x0511,      // 遥控跳闸
    TCMD_AFN_5_F18_REMOTE_ON           = 0x0512,      // 允许合闸
    ///*}
    
    /**********************************
     * 类型: 身份认证及密钥协商
     * AFN : 06
     *  PN : p0
     * 上行: 有
     * 下行: 有
    {*///
    TCMD_AFN_6_F1_ID_AUTH_Q           = 0x0601,       // 身份认证请求
    TCMD_AFN_6_F2_ID_AUTH_A           = 0x0602,       // 身份认证响应
    TCMD_AFN_6_F3_RAND_Q              = 0x0603,       // 取随机数请求
    TCMD_AFN_6_F4_RAND_A              = 0x0604,       // 取随机数响应
    ///*}   

     /**********************************
     * 类型: 查询参数
     * AFN : 0A
     *  PN : 分组定义
     * 上行: 有
     * 下行: 有
    {*///
    // 组1   pn:p0
    TCMD_AFN_A_F1_CON_IP_PORT         = 0x0A01,       // 集中与交互终端IP地址和端口
    TCMD_AFN_A_F2_TML_UP_CFG          = 0x0A02,       // 监测终端上行通信参数配置
    TCMD_AFN_A_F3_TML_AUTH_PARA       = 0x0A03,       // 监测终端上行通信消息认证参数设置  
    TCMD_AFN_A_F4_TML_STATE_INPUT     = 0x0A04,       // 状态量输入参数
    TCMD_AFN_A_F5_TML_EVENT_CFG       = 0x0A05,       // 事件记录配置

    // 组2  pn:P0    
    TCMD_AFN_A_F11_TML_SPRT_EVENT     = 0x050B,       // 终端支持的事件记录信息
    TCMD_AFN_A_F12_ELEC_MP_INFO       = 0x0A0C,       // 已配置电气测量点信息
    TCMD_AFN_A_F13_NELC_MP_INFO       = 0x0A0D,       // 已配置非电气测量点信息
    TCMD_AFN_A_F14_TML_PROTO_SPRT     = 0x0A0E,       // 接入端口支持的通信协议信息
    TCMD_AFN_A_F15_TML_MODEL_VERSION  = 0x0A0F,       // 终端内各智能模块的软硬件版本信息
    TCMD_AFN_A_F16_TML_VERSION        = 0x0A10,       // 终端软硬件版本信息
    
    // 组3   pn:任务号 
    TCMD_AFN_A_F17_FREZ_TASK_PARA     = 0x0A11,       // 冻结数据任务配置  

    // 组4   pn:电气测量点号
    TCMD_AFN_A_F25_ELEC_MP_CFG        = 0x0A19,       // 电气测量点配置参数
    TCMD_AFN_A_F26_ELEC_MP_BASE       = 0x0A1A,       // 电气测量点基本参数 
    TCMD_AFN_A_F27_ELEC_LMIT_PARA     = 0x0A1B,       // 电气测量点限值参数
    TCMD_AFN_A_F28_ELEC_LMIT_FACTR    = 0x0A1C,       // 电气测量点总功率因数参数 
    TCMD_AFN_A_F29_ELEC_FIX_HARM      = 0x0A1D,       // 电气测量点谐波畸变率越限定值
    TCMD_AFN_A_F30_ELEC_FLASH         = 0x0A1E,       // 电气测量点闪变越限参数
    
    // 组5   pn:非电气测量点号
    TCMD_AFN_A_F33_NELC_MP_CFG        = 0x0A21,       // 非电气测量点配置参数 
    TCMD_AFN_A_F34_NELC_MP_PARA       = 0x0A22,       // 非电气测量点基本参数
    TCMD_AFN_A_F35_NELC_MP_LMIT       = 0x0A23,       // 非电气测量点越限参数
    ///*}

    /**********************************
     * 类型: 请求(定时上报)任务数据
     * AFN : 0CH
     *  PN : 分组定义
     * 上行: 有
     * 下行: 有
    {*///
     // 组1   pn:p0
    TCMD_AFN_C_F1_FREZ_TEMP          = 0x0A01,       // 请求临时冻结命令的冻结数据  

     // 组2   pn:任务号
    TCMD_AFN_C_F9_FREZ_AUTO          = 0x0A09,       // 请求（定时上报）冻结数据任务 
    ///*} 

    /**********************************
     * 类型: 请求实时数据
     * AFN : 13
     *  PN : 分组定义
     * 上行: 有
     * 下行: 有
    {*///
    // 组1   pn: p0
    TCMD_AFN_D_F1_CLOCK              = 0x0D01,       // 日历时钟  
    TCMD_AFN_D_F2_PARA_STATE         = 0x0D02,       // 参数状态    
    TCMD_AFN_D_F3_EVENT_1            = 0x0D03,       // 重要事件计数器当前值  
    TCMD_AFN_D_F4_EVENT_2            = 0x0D04,       // 一般事件计数器当前值  
    TCMD_AFN_D_F5_EVENT_STATE        = 0x0D05,       // 事件状态标志   
    TCMD_AFN_D_F6_POWR_TIMES         = 0x0D06,       // 上电次数  

    // 组2   pn: p0
    TCMD_AFN_D_F9_STATE              = 0x0D09,       // 状态量及变位标志 

    // 组3   pn:电气测量点号 
    TCMD_AFN_D_F17_POWR_HAVE_T       = 0x0D11,       // 总有功功率 
    TCMD_AFN_D_F18_POWR_NONE_T       = 0x0D12,       // 总无功功率  
    TCMD_AFN_D_F19_DEMD_TIME_D       = 0x0D13,       // 日最大需量及发生时间
    TCMD_AFN_D_F20_DEMD_TIME_M       = 0x0D14,       // 月最大需量及发生时间
    TCMD_AFN_D_F21_FACTR_T           = 0x0D15,       // 总功率因数 
    TCMD_AFN_D_F22_FACTR_A           = 0x0D16,       // A相功率因素 
    TCMD_AFN_D_F23_FACTR_B           = 0x0D17,       // B相功率因数  
    TCMD_AFN_D_F24_FACTR_C           = 0x0D18,       // C相功率因数 

    // 组4   pn:电气测量点号
    TCMD_AFN_D_F25_POWR_HAVE_A       = 0x0D19,       // A相有功功率 
    TCMD_AFN_D_F26_POWR_HAVE_B       = 0x0D1A,       // B相有功功率 
    TCMD_AFN_D_F27_POWR_HAVE_C       = 0x0D1B,       // C相有功功率 
    TCMD_AFN_D_F28_POWR_NONE_A       = 0x0D1C,       // A相无功功率  
    TCMD_AFN_D_F29_POWR_NONE_B       = 0x0D1D,       // B相无功功率  
    TCMD_AFN_D_F30_POWR_NONE_C       = 0x0D1E,       // C相无功功率  

    // 组5   pn:电气测量点号
    TCMD_AFN_D_F33_POWR_HAVE_FRTH    = 0x0D21,       // （正向）有功总电能示数
    TCMD_AFN_D_F34_POWR_HAVE_BACK    = 0x0D22,       // （反向）有功总电能示数 
    TCMD_AFN_D_F35_POWR_NONE_FRTH    = 0x0D23,       // （正向）无功总电能示数
    TCMD_AFN_D_F36_POWR_NONE_BACK    = 0x0D24,       // （反向）无功总电能示数 

    // 组6 pn:电气测量点号
    TCMD_AFN_D_F41_VOLT_A            = 0x0D29,       // A相电压     
    TCMD_AFN_D_F42_VOLT_B            = 0x0D2A,       // B相电压     
    TCMD_AFN_D_F43_VOLT_C            = 0x0D2B,       // C相电压     
    TCMD_AFN_D_F44_VANGL_A           = 0x0D2C,       // A相电压相位角    
    TCMD_AFN_D_F45_VANGL_B           = 0x0D2D,       // B相电压相位角     
    TCMD_AFN_D_F46_VANGL_C           = 0x0D2E,       // C相电压相位角     
    TCMD_AFN_D_F47_VOLT_UBL          = 0x0D2F,       // 电压不平衡度      
    TCMD_AFN_D_F48_CIRCLE_V          = 0x0D30,       // 周波

    // 组7 pn:电气测量点号
    TCMD_AFN_D_F49_ELEC_A            = 0x0D31,       // A相电流      
    TCMD_AFN_D_F50_ELEC_B            = 0x0D32,       // B相电流      
    TCMD_AFN_D_F51_ELEC_C            = 0x0D33,       // C相电流      
    TCMD_AFN_D_F52_ELEC_M            = 0x0D34,       // 中性线电流      
    TCMD_AFN_D_F53_EANGL_A           = 0x0D35,       // A相电流相位角     
    TCMD_AFN_D_F54_EANGL_B           = 0x0D36,       // B相电流相位角     
    TCMD_AFN_D_F55_EANGL_C           = 0x0D37,       // C相电流相位角     
    TCMD_AFN_D_F56_ELEC_UBL          = 0x0D38,       // 电流不平衡度      

    // 组8 pn:电气测量点号
    TCMD_AFN_D_F57_VDMAX_A_TIME      = 0x0D39,       // 日A相电压极大值和发生时间      
    TCMD_AFN_D_F58_VDMAX_B_TIME      = 0x0D3A,       // 日B相电压极大值和发生时间      
    TCMD_AFN_D_F59_VDMAX_C_TIME      = 0x0D3B,       // 日C相电压极大值和发生时间     
    TCMD_AFN_D_F60_IDMAX_A_TIME      = 0x0D3C,       // 日A相电流极大值和发生时间      
    TCMD_AFN_D_F61_IDMAX_B_TIME      = 0x0D3D,       // 日B相电流极大值和发生时间      
    TCMD_AFN_D_F62_IDMAX_C_TIME      = 0x0D3E,       // 日C相电流极大值和发生时间     

    // 组9 pn:电气测量点号
    TCMD_AFN_D_F65_VDPP_TIME_A       = 0x0D41,       // A相电压越上上限日累计时间  
    TCMD_AFN_D_F66_VDPP_TIME_B       = 0x0D42,       // B相电压越上上限日累计时间  
    TCMD_AFN_D_F67_VDPP_TIME_C       = 0x0D43,       // C相电压越上上限日累计时间  
    TCMD_AFN_D_F68_VDNN_TIME_A       = 0x0D44,       // A相电压越下下限日累计时间  
    TCMD_AFN_D_F69_VDNN_TIME_B       = 0x0D45,       // B相电压越下下限日累计时间  
    TCMD_AFN_D_F70_VDNN_TIME_C       = 0x0D46,       // C相电压越下下限日累计时间  

    // 组10 pn:电气测量点号
    TCMD_AFN_D_F73_VMPP_TIME_A        = 0x0D49,       // A相电压越上上限月累计时间  
    TCMD_AFN_D_F74_VMPP_TIME_B        = 0x0D4A,       // B相电压越上上限月累计时间  
    TCMD_AFN_D_F75_VMPP_TIME_C        = 0x0D4B,       // C相电压越上上限月累计时间  
    TCMD_AFN_D_F76_VMNN_TIME_A        = 0x0D4C,       // A相电压越下下限月累计时间  
    TCMD_AFN_D_F77_VMNN_TIME_B        = 0x0D4D,       // B相电压越下下限月累计时间  
    TCMD_AFN_D_F78_VMNN_TIME_C        = 0x0D4E,       // C相电压越下下限月累计时间  

    // 组11 pn:电气测量点号
    TCMD_AFN_D_F81_VABR_TOTL_A       = 0x0D51,       // A相电压总畸变率  
    TCMD_AFN_D_F82_VABR_TOTL_B       = 0x0D52,       // B相电压总畸变率  
    TCMD_AFN_D_F83_VABR_TOTL_C       = 0x0D53,       // C相电压总畸变率  
    TCMD_AFN_D_F84_EABR_TOTL_A       = 0x0D54,       // A相电流总畸变率  
    TCMD_AFN_D_F85_EABR_TOTL_B       = 0x0D55,       // B相电流总畸变率  
    TCMD_AFN_D_F86_EABR_TOTL_C       = 0x0D56,       // C相电流总畸变率  

    // 组12 pn:电气测量点号
    TCMD_AFN_D_F89_VABR_OOD_A        = 0x0D59,       // A相电压奇次畸变率  
    TCMD_AFN_D_F90_VABR_EVN_A        = 0x0D5A,       // A相电压偶次畸变率  
    TCMD_AFN_D_F91_VABR_OOD_B        = 0x0D5B,       // B相电压奇次畸变率  
    TCMD_AFN_D_F92_VABR_EVN_B        = 0x0D5C,       // B相电压偶次畸变率  
    TCMD_AFN_D_F93_VABR_OOD_C        = 0x0D5D,       // C相电压奇次畸变率  
    TCMD_AFN_D_F94_VABR_EVN_C        = 0x0D5E,       // C相电压偶次畸变率  

    // 组13 pn:电气测量点号
    TCMD_AFN_D_F97_EABR_OOD_A        = 0x0D61,       // A相电流奇次畸变率  
    TCMD_AFN_D_F98_EABR_EVN_A        = 0x0D62,       // A相电流偶次畸变率  
    TCMD_AFN_D_F99_EABR_OOD_B        = 0x0D63,       // B相电流奇次畸变率  
    TCMD_AFN_D_F100_EABR_EVN_B       = 0x0D64,       // B相电流偶次畸变率  
    TCMD_AFN_D_F101_EABR_OOD_C       = 0x0D65,       // C相电流奇次畸变率 
    TCMD_AFN_D_F102_EABR_EVN_C       = 0x0D66,       // C相电流偶次畸变率  

    // 组14 pn:电气测量点号
    TCMD_AFN_D_F105_TFW_HAVE         = 0x0D69,       // 总基波有功功率  
    TCMD_AFN_D_F106_TFW_NONE         = 0x0D6A,       // 总基波无功功率   
    TCMD_AFN_D_F107_THW_HAVE         = 0x0D6B,       // 总谐波有功功率  
    TCMD_AFN_D_F108_THW_NONE         = 0x0D6C,       // 总基波无功功率    
   
    // 组15 pn:电气测量点号
    TCMD_AFN_D_F113_HARM_VOLT_A      = 0x0D71,       // A相N次谐波电压
    TCMD_AFN_D_F114_HARM_VOLT_B      = 0x0D72,       // B相N次谐波电压
    TCMD_AFN_D_F115_HARM_VOLT_C      = 0x0D73,       // C相N次谐波电压
    TCMD_AFN_D_F116_HARM_ELEC_A      = 0x0D74,       // A相N次谐波电流
    TCMD_AFN_D_F117_HARM_ELEC_B      = 0x0D75,       // B相N次谐波电流
    TCMD_AFN_D_F118_HARM_ELEC_C      = 0x0D76,       // C相N次谐波电流

    // 组16 pn:电气测量点号
    TCMD_AFN_D_F121_HARM_VINC_A      = 0x0D79,       // A相N次谐波电压含有率
    TCMD_AFN_D_F122_HARM_VINC_B      = 0x0D7A,       // B相N次谐波电压含有率
    TCMD_AFN_D_F123_HARM_VINC_C      = 0x0D7B,       // C相N次谐波电压含有率
    TCMD_AFN_D_F124_HARM_EINC_A      = 0x0D7C,       // A相N次谐波电流含有率
    TCMD_AFN_D_F125_HARM_EINC_B      = 0x0D7D,       // B相N次谐波电流含有率
    TCMD_AFN_D_F126_HARM_EINC_C      = 0x0D7E,       // C相N次谐波电流含有率
    
    // 组17 pn:电气测量点号
    TCMD_AFN_D_F129_FLS_SHRT_A       = 0x0D81,       // A相短时闪变
    TCMD_AFN_D_F130_FLS_SHRT_B       = 0x0D82,       // B相短时闪变
    TCMD_AFN_D_F131_FLS_SHRT_C       = 0x0D83,       // C相短时闪变
    TCMD_AFN_D_F132_FLS_LONG_A       = 0x0D84,       // A相长时闪变
    TCMD_AFN_D_F133_FLS_LONG_B       = 0x0D85,       // B相长时闪变
    TCMD_AFN_D_F134_FLS_LONG_C       = 0x0D86,       // C相长时闪变

    // 组18 pn:非电气测量点号
    TCMD_AFN_D_F137_NELC_VALUE       = 0x0D89,       // 非电气量
    ///*} 

   /**********************************
     * 类型: 请求（主动上报）事件记录
     * AFN : 0E
     *  PN : p0
     * 上行: 有
     * 下行: 有
    {*///
    TCMD_AFN_E_F1_EVENT_1             = 0x0E01,       // 请求（主动上报）重要事件
    TCMD_AFN_E_F2_EVENT_2             = 0x0E02,       // 请求（主动上报）一般事件
    TCMD_AFN_E_F3_EVENT_S             = 0x0E03,       // 请求指定事件记录
    ///*}   

    
    /**********************************
     * 类型: 文件传输
     * AFN : 0F
     *  PN : p0
     * 上行: 有
     * 下行: 有
    {*///
    // 组1   pn:p0/监测终端号 
    TCMD_AFN_F_F1_SOFT_DOWN           = 0x0F01,        // 软件下载 
    TCMD_AFN_F_F2_SOFT_LEFT           = 0x0F02,        // 软件下载未收到数据段  

    // 组2   pn:p0/监测终端号 
    TCMD_AFN_F_F9_NXMD_DOWN           = 0x0F09,        // 软件下载 
    TCMD_AFN_F_F10_NXMD_LEFT          = 0x0F0A,        // 软件下载未收到数据段  

    // 组3   pn:p0/监测终端号 
    TCMD_AFN_F_F17_REQS_DOWN          = 0x0F11,        // 软件下载 
    TCMD_AFN_F_F18_REQS_LEFT          = 0x0F12,        // 软件下载未收到数据段  
    ///*}  

     /**********************************
     * 类型: 数据转发
     * AFN : 10H
     *  PN : p0
     * 上行: 有
     * 下行: 有
    {*///
    // 组1 Pn:P0
    TCMD_AFN_10_F1_TRANSMIT           = 0x1001,       // 透明转发
    ///*}  
     
    /* 在这之上添加扩展命令字 */    
    TCMD_AFN_FN_MAX  

}eTcmd;
///*} 

/*******************************************************
 *  事件类型定义 eTcErc
 *
{*///
typedef enum
{
    TC_ERC_UNKOWN,            // ERC0: 未知事件记录类型
    TC_ERC_1_RESET,           // ERC1: 复位事件
    TC_ERC_2_SOFT_CHANGE,     // ERC2: 软件版本变更事件
    TC_ERC_3_PARA_CHANGE,     // ERC3: 参数变更事件
    TC_ERC_4_STATE_CHANGE,    // ERC4: 状态量变位事件
    TC_ERC_5_REMOTE_SWITCH,   // ERC5: 遥控跳闸事件
    TC_ERC_6_POWER_ON_OFF,    // ERC6: 停/上电事件 
    TC_ERC_7_FACTOR_OVER,     // ERC7: 总功率因素越限事件
    TC_ERC_8_VOLT_EXCP,       // ERC8: 电压偏差越限事件
    TC_ERC_9_VOLT_CRICLE,     // ERC9: 电压回路异常事件
    TC_ERC_10_ELEC_CRICLE,    // ERC10:电流回路异常事件
    TC_ERC_11_VOLT_OVER,      // ERC11:电压越限事件
    TC_ERC_12_ELEC_OVER,      // ERC12:电流越限事件
    TC_ERC_13_UNBL_OVER_V,    // ERC13:电压不平衡度越限事件
    TC_ERC_14_UNBL_OVER_I,    // ERC14:电流不平度越限事件
    TC_ERC_15_HUNBL_OVER_V,   // ERC15:谐波电压畸变率越限事件
    TC_ERC_16_HUNBL_OVER_I,   // ERC16:谐波电流畸变率越限事件
    TC_ERC_17_NELC_OVER,      // ERC17:非电气量越限事件
    TC_ERC_NUM_MAX            // 事件类型最大值
}eTcEventRecord, eTcErc; // 事件类型定义
///*} 

/*******************************************************
 *  帧侧与用户侧 数据结构转换函数类型定义
 *
{*///
typedef enum
{
    TC_TRANS_UNKOWN,    // 未知方向
    TC_TRANS_U2F,       // 用户侧数据结构到帧数据结构
    TC_TRANS_F2U,       // 帧侧数据结构到用户侧数据结构

}eTcTrans;              // 用户侧与帧侧数据结构转换方向

// 转换帧侧与用户侧数据结构的函数指针类型
// pusLen 为封装成帧侧的数据字节长
typedef eTcErr (*pTcFunc)(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/************************************************************
 *  内部接口
 *
{*///
/*******************************************************************
 *  附录A 数据格式的定义与转换函数
 *
{*///

/*********************************************
 *  数据格式01 对于表A.1
 *  格式:
 *  字长: 6
 *  +-------+------+------+------+------+------+------+------+------+
 *  |              |                       字节格式                 |
 *  + 名 称 +------+------+------+------+------+------+------+------+
 *  |       |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +-------+------+------+------+------+------+------+------+------+
 *  |   秒  |         BCD码十位         |         BCD码个位         |
 *  +-------+------+------+------+------+------+------+------+------+
 *  |   分  |         BCD码十位         |         BCD码个位         |
 *  +-------+------+------+------+------+------+------+------+------+
 *  |   时  |         BCD码十位         |         BCD码个位         |
 *  +-------+------+------+------+------+------+------+------+------+
 *  |   日  |         BCD码十位         |         BCD码个位         |
 *  +-------+------+------+------+------+------+------+------+------+
 *  |星期-月| 星期BCD个位        |月BCD |        月BCD码个位        |
 *  |       |                    |码十位|                           |
 *  +-------+------+------+------+------+------+------+------+------+
 *  |   年  |         BCD码十位         |         BCD码个位         |
 *  +-------+------+------+------+------+------+------+------+------+
 *  星期定义如下：D5 ~ D7编码表示 0 ~ 7，0：无效，1-7依次表示星期一至星期日
{*///

// 用户侧
typedef struct
{
    UINT8 ucYY;    // 年
    UINT8 ucMM;    // 月
    UINT8 ucWW;    // 星期
    UINT8 ucDD;    // 日
    UINT8 ucHH;    // 小时
    UINT8 ucmm;    // 分钟
    UINT8 ucss;    // 秒

}sTcUerClock, sTcFmt01, sTcYWMDhms;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8  bcd_ss_0:4;  //秒
    UINT8  bcd_ss_1:4;
    UINT8  bcd_mm_0:4;  // 分
    UINT8  bcd_mm_1:4;
    UINT8  bcd_HH_0:4;  // 时
    UINT8  bcd_HH_1:4;
    UINT8  bcd_DD_0:4;  // 日
    UINT8  bcd_DD_1:4;
    UINT8  bcd_MM_0:4;  // 月
    UINT8  bcd_MM_1:1;
    UINT8  bcd_WW_0:3;  // 星期
    UINT8  bcd_YY_0:4;  // 年
    UINT8  bcd_YY_1:4;

}sTcUerClock_f, sTcFmt01_f, sTcYWMDhms_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_YWMDhms(eTcTrans eTrans, sTcYWMDhms* psUser, sTcYWMDhms_f* psFrame);
///*}

/*********************************************
 *  数据格式2 对于表A.2
 *  单位: 年月日时分
 *  字长: 5
 *  格式:
 *  +------+------+------+------+------+------+------+------+------+
 *  |      |                       字节格式                        |
 *  + 名称 +------+------+------+------+------+------+------+------+
 *  |      |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +------+------+------+------+------+------+------+------+------+
 *  |  分  |         BCD码十位         |         BCD码个位         |
 *  +------+------+------+------+------+------+------+------+------+
 *  |  时  |         BCD码十位         |         BCD码个位         |
 *  +------+------+------+------+------+------+------+------+------+
 *  |  日  |         BCD码十位         |         BCD码个位         |
 *  +------+------+------+------+------+------+------+------+------+
 *  |  月  |         BCD码十位         |         BCD码个位         |
 *  +------+------+------+------+------+------+------+------+------+
 *  |  年  |         BCD码十位         |         BCD码个位         |
 *  +------+------+------+------+------+------+------+------+------+
 *
{*///

// 用户侧
typedef struct
{
    UINT8  ucYY;        // 年
    UINT8  ucMM;        // 月
    UINT8  ucDD;        // 日
    UINT8  ucHH;        // 时
    UINT8  ucmm;        // 分

}sTcFmt02, sTcYYMMDDhhmm, sTcYMDhm;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8  bcd_mm_0:4;  // 分
    UINT8  bcd_mm_1:4;
    UINT8  bcd_hh_0:4;  // 时
    UINT8  bcd_hh_1:4;
    UINT8  bcd_DD_0:4;  // 日
    UINT8  bcd_DD_1:4;
    UINT8  bcd_MM_0:4;  // 月
    UINT8  bcd_MM_1:4;
    UINT8  bcd_YY_0:4;  // 年
    UINT8  bcd_YY_1:4;

}sTcFmt02_f, sTcYYMMDDhhmm_f, sTcYMDhm_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_YYMMDDhhmm(eTcTrans eTrans, sTcYMDhm* psUser, sTcYMDhm_f* psFrame);
///*}

/*********************************************
 *  数据格式3 对于表A.3
 *  单位: 月日时分
 *  字长: 4
 *  格式:
 *  +------+------+------+------+------+------+------+------+------+
 *  |      |                       字节格式                        |
 *  + 名称 +------+------+------+------+------+------+------+------+
 *  |      |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +------+------+------+------+------+------+------+------+------+
 *  |  秒  |         BCD码十位         |         BCD码个位         |
 *  +------+------+------+------+------+------+------+------+------+
 *  |  分  |         BCD码十位         |         BCD码个位         |
 *  +------+------+------+------+------+------+------+------+------+
 *  |  时  |         BCD码十位         |         BCD码个位         |
 *  +------+------+------+------+------+------+------+------+------+
 *  |  日  |         BCD码十位         |         BCD码个位         |
 *  +------+------+------+------+------+------+------+------+------+
 *
{*///

// 用户侧
typedef struct
{
    UINT8  ucDD;        // 日
    UINT8  ucHH;        // 时
    UINT8  ucmm;        // 分
    UINT8  ucss;        // 秒
}sTcFmt03, sTcDDHHmmss;

// 帧侧
typedef struct
{
    UINT8  bcd_ss_0:4;  // 秒
    UINT8  bcd_ss_1:4;
    UINT8  bcd_mm_0:4;  // 分
    UINT8  bcd_mm_1:4;
    UINT8  bcd_HH_0:4;  // 时
    UINT8  bcd_HH_1:4;
    UINT8  bcd_DD_0:4;  // 日
    UINT8  bcd_DD_1:4;

}sTcFmt03_f, sTcDDHHmmss_f;

// 转换函数
eTcErr etc_trans_DDHHmmss(eTcTrans eTrans, sTcDDHHmmss* psDDHHmmss_u, sTcDDHHmmss_f* psDDHHmmss_f);
///*}

/*********************************************
 *  数据格式4 对于表A.4
 *  格式: (+)XXXXXX.XXXX
 *  字长: 5
 *  格式:
 *  +-------+------+------+------+------+------+------+------+------+
 *  |       |                       字节格式                        |
 *  + 名称  +------+------+------+------+------+------+------+------+
 *  |       |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE1 |        BCD码千分位        |        BCD码万分位        |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE2 |        BCD码十分位        |        BCD码百分位        |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE3 |         BCD码十位         |         BCD码个位         |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE4 |         BCD码千位         |         BCD码百位         |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE5 |        BCD码十万位        |          BCD码万位        |
 *  +-------+------+------+------+------+------+------+------+------+
{*///

// 用户侧
// double dXXXXXX.XXXX

// 帧侧
typedef struct
{
    UINT8 BCD_0_4:4;  // BCD 百分位
    UINT8 BCD_0_3:4;  // BCD 十分位
    UINT8 BCD_0_2:4;  // BCD 百分位
    UINT8 BCD_0_1:4;  // BCD 十分位
    UINT8 BCD_0  :4;  // BCD 个位
    UINT8 BCD_1  :4;  // BCD 十位
    UINT8 BCD_2  :4;  // BCD 百位
    UINT8 BCD_3  :4;  // BCD 千位
    UINT8 BCD_4  :4;  // BCD 万位
    UINT8 BCD_5  :4;  // BCD 十万位

}sTcFmt04, sTcFmt04_f, sTcFmt_XXXXXX_XXXX;

// 转换函数
eTcErr etc_trans_XXXXXX_XXXX(eTcTrans eTrans, double* psUser, sTcFmt_XXXXXX_XXXX* psFrame);
///*}

/*********************************************
 *  数据格式5 对于表A.5
 *  格式: (+)XXXXXX.XX
 *  字长: 4
 *  +-------+------+------+------+------+------+------+------+------+
 *  |       |                       字节格式                        |
 *  + 名称  +------+------+------+------+------+------+------+------+
 *  |       |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE1 |        BCD码十分位        |        BCD码百分位        |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE2 |         BCD码十位         |         BCD码个位         |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE3 |         BCD码千位         |         BCD码百位         |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE4 |        BCD码十万位        |         BCD码万位         |
 *  +-------+------+------+------+------+------+------+------+------+
{*///

// 用户侧
// double dXXXXXX.XX

// 帧侧
typedef struct
{
    UINT8 BCD_0_2:4;  // BCD 百分位
    UINT8 BCD_0_1:4;  // BCD 十分位
    UINT8 BCD_0  :4;  // BCD 个位
    UINT8 BCD_1  :4;  // BCD 十位
    UINT8 BCD_2  :4;  // BCD 百位
    UINT8 BCD_3  :4;  // BCD 千位
    UINT8 BCD_4  :4;  // BCD 万位
    UINT8 BCD_5  :4;  // BCD 十万位

}sTcFmt05, sTcFmt05_f, sTcFmt_XXXXXX_XX;

// 转换函数
eTcErr etc_trans_XXXXXX_XX(eTcTrans eTrans, double* psUser, sTcFmt_XXXXXX_XX* psFrame);
///*}

/*********************************************
 *  数据格式6 对于表A.6
 *  格式: (+/-)XX.XXXX
 *  字长: 3
 *  +-------+------+------+------+------+------+------+------+------+
 *  |       |                       字节格式                        |
 *  + 名称  +------+------+------+------+------+------+------+------+
 *  |       |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE1 |        BCD码千分位        |        BCD码万分位        |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE2 |        BCD码十分位        |        BCD码百分位        |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE3 |  S   |     BCD码十位      |         BCD码个位         |
 *  +-------+------+------+------+------+------+------+------+------+
{*///

// 用户侧
// float fXX.XXXX

// 帧侧
typedef struct
{
    UINT8 BCD_0_4:4;  // BCD 万分位
    UINT8 BCD_0_3:4;  // BCD 千分位
    UINT8 BCD_0_2:4;  // BCD 百分位
    UINT8 BCD_0_1:4;  // BCD 十分位
    UINT8 BCD_0  :4;  // BCD 个位
    UINT8 BCD_1  :3;  // BCD 十位
    UINT8 S      :1;  // 符号位
}sTcFmt06_f, sTcFmt_sXX_XXXX;

// 10 exp次方 exp < 10
int  ntc_pow(UINT8 exp);

// 转换函数
eTcErr etc_trans_sXX_XXXX(eTcTrans eTrans, float* psUser, sTcFmt06_f* psFrame);
///*}

/*********************************************
 *  数据格式07 对于表A.7
 *  格式: (+/-)XXX.X
 *  字长: 2
 *  +-------+------+------+------+------+------+------+------+------+
 *  |       |                       字节格式                        |
 *  + 名 称 +------+------+------+------+------+------+------+------+
 *  |       |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE1 |        BCD码个分位        |        BCD码十分位        |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE2 |  S   |     BCD码百位      |         BCD码十位         |
 *  +-------+------+------+------+------+------+------+------+------+
{*///
// 用户侧
// float fsXXX.X

// 帧侧
typedef struct
{
    UINT8 BCD_0_1:4; // BCD 十分位
    UINT8 BCD_0  :4; // BCD 个位
    UINT8 BCD_1  :4; // BCD 十位
    UINT8 BCD_2  :3; // BCD 百位
    UINT8 S      :1; // BCD 符号位
}sTcFmt07, sTcFmt07_f, sTcFmt_sXXX_X;

// 转换函数
eTcErr etc_trans_sXXX_X(eTcTrans eTrans, float* psUser, sTcFmt07_f* psFrame);
///*}

/*********************************************
 *  数据格式08 对于表A.8
 *  格式: (+)XXX.X
 *  字长: 2
 *  +-------+------+------+------+------+------+------+------+------+
 *  |       |                       字节格式                        |
 *  + 名 称 +------+------+------+------+------+------+------+------+
 *  |       |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE1 |        BCD码个分位        |        BCD码十分位        |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE2 |         BCD码百位         |         BCD码十位         |
 *  +-------+------+------+------+------+------+------+------+------+
{*///

// 用户侧
// float fXXX.X

// 帧侧
typedef struct
{
    UINT8 BCD_0_1:4;  // BCD 十分位
    UINT8 BCD_0  :4;  // BCD 个位
    UINT8 BCD_1  :4;  // BCD 十位
    UINT8 BCD_2  :4;  // BCD 百位
}sTcFmt08, sTcFmt08_f, sTcFmt_XXX_X;

// 转换函数
eTcErr etc_trans_XXX_X(eTcTrans eTrans, float* psUser, sTcFmt_XXX_X* psFrame);
///*}

/*********************************************
 *  数据格式09 对于表A.9
 *  格式: (+/-)XXX.XXX
 *  字长: 3
 *  +-------+------+------+------+------+------+------+------+------+
 *  |       |                       字节格式                        |
 *  + 名称  +------+------+------+------+------+------+------+------+
 *  |       |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE1 |        BCD码百分位        |        BCD码千分位        |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE2 |         BCD码个位         |        BCD码十分位        |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE3 |  S   |     BCD码百位      |         BCD码十位         |
 *  +-------+------+------+------+------+------+------+------+------+
 *
{*///

// 用户侧
// float sXXX.XXX    (+/-)XXX.XXX

// 帧侧
typedef struct
{
    UINT8 BCD_0_3:4;  // BCD 千分位
    UINT8 BCD_0_2:4;  // BCD 百分位
    UINT8 BCD_0_1:4;  // BCD 十分位
    UINT8 BCD_0  :4;  // BCD 个位
    UINT8 BCD_1  :4;  // BCD 十位
    UINT8 BCD_2  :3;  // BCD 百位
    UINT8 S      :1;  // 符号位

}sTcFmt09,sTcFmt09_f,sTcFmt_sXXX_XXX;

// 转换函数
eTcErr etc_trans_sXXX_XXX(eTcTrans eTrans, float* psUser, sTcFmt_sXXX_XXX* psFrame);
///*}

/*********************************************
 *  数据格式10 对于表A.10 格式有变
 *  格式: (+)XX.XX
 *  字长: 2
 *  +-------+------+------+------+------+------+------+------+------+
 *  |       |                       字节格式                        |
 *  + 名 称 +------+------+------+------+------+------+------+------+
 *  |       |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE1 |        BCD码十分位        |        BCD码百分位        |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE2 |         BCD码十位         |         BCD码个位         |
 *  +-------+------+------+------+------+------+------+------+------+
{*///

// 用户侧
// float fXX.XX

// 帧侧
typedef struct
{
    UINT8 BCD_0_2:4;  // BCD 百分位
    UINT8 BCD_0_1:4;  // BCD 十分位
    UINT8 BCD_0  :4;  // BCD 个位
    UINT8 BCD_1  :4;  // BCD 十位
}sTcFmt10_f, sTcFmt_XX_XX;

// 转换函数
eTcErr etc_trans_XX_XX(eTcTrans eTrans, float* psUser, sTcFmt10_f* psFrame);
///*}

/*********************************************
 *  数据格式11 对于表A.11
 *  格式: (+/-)XXXXXXX
 *  字长: 4
 *  +-------+------+------+------+------+------+------+------+------+
 *  |       |                       字节格式                        |
 *  + 名 称 +------+------+------+------+------+------+------+------+
 *  |       |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE1 |         BCD码十位         |         BCD码个位         |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE2 |         BCD码千位         |         BCD码百位         |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE3 |        BCD码十万位        |         BCD码万位         |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE4 |  G3  |  G2  |  G1  |  S   |         BCD码百万位       |
 *  +-------+------+------+------+------+------+------+------+------+
 *  
 *  +-------+-------+-------+----------+
 *  |   G3  |  G2   |  G1   |   含义   |
 *  +-------+-------+-------+----------+
 *  |   0   |   0   |   0   |   10(4)  |
 *  +-------+-------+-------+----------+
 *  |   0   |   0   |   1   |   10(3)  |
 *  +-------+-------+-------+----------+
 *  |   0   |   1   |   0   |   10(2)  |
 *  +-------+-------+-------+----------+
 *  |   0   |   1   |   1   |   10(1)  |
 *  +-------+-------+-------+----------+
 *  |   1   |   0   |   0   |   10(0)  |
 *  +-------+-------+-------+----------+
 *  |   1   |   0   |   1   |   10(-1) |
 *  +-------+-------+-------+----------+
 *  |   1   |   1   |   0   |   10(-2) |
 *  +-------+-------+-------+----------+
 *  |   1   |   1   |   1   |   10(-3) |
 *  +-------+-------+-------+----------+
 *
 *  S 符号位:S = 0 正数 S = 1 表示负数
 *
{*///
// 用户侧
//double dValue
#define TC_SX7_MIN     (-99999990000.0)
#define TC_SX7_MAX     (99999990000.0)

typedef enum
{
    TC_PREC_UNKOWN,
    TC_PREC_P4,  // 范围 0, (+/-)10000~99999990000
    TC_PREC_P3,  // 范围 0, (+/-)1000~9999999000
    TC_PREC_P2,  // 范围 0, (+/-)100~999999900
    TC_PREC_P1,  // 范围 0, (+/-)10~99999990
    TC_PREC_P0,  // 范围 0, (+/-)1~9999999
    TC_PREC_N1,  // 范围 0, (+/-)0.1~999999.9
    TC_PREC_N2,  // 范围 0, (+/-)0.01~99999.99
    TC_PREC_N3,  // 范围 0, (+/-)0.001~9999.999

}eTcPrecise;            // 精度

typedef struct
{
    eTcPrecise  ePrec;
    double      dValue;   
}sTcFmt11, sTcDouble; 

// 帧侧
#pragma pack(1)
typedef struct
{
    UINT8 BCD_0  :4; // BCD 个位
    UINT8 BCD_1  :4; // BCD 十位
    UINT8 BCD_2  :4; // BCD 百位
    UINT8 BCD_3  :4; // BCD 千位
    UINT8 BCD_4  :4; // BCD 万位
    UINT8 BCD_5  :4; // BCD 十万位
    UINT8 BCD_6  :4; // BCD 百万位
    UINT8 SG123  :4;
    /*
    UINT8 S      :1; // 符号位 0 为正 1为负
    UINT8 G1     :1; // 
    UINT8 G2     :1; // 
    UINT8 G3     :1; // 
    */
}sTcFmt11_f, sTcFmt_sX7_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_sX7(eTcTrans eTrans, void* psUser, void* psFrame);
///*}
///*}

/******************************************************************************
 *  数据名称:float类型的
 *  数据说明:
 *  浮点数在机内用指数型式表示，分解为：数符，尾数，指数符，指数四部分。
 *  无论是单精度还是双精度在存储中都分为三个部分：
 1.符号位(Sign) : 0代表正，1代表为负
 2.指数位（Exponent）:用于存储科学计数法中的指数数据，并且采用移位存储
 3.尾数部分（Mantissa）：尾数部分
{*///
typedef union
{
    float v;
    struct
    {
        unsigned mantissa1 : 23;
        unsigned exponent  : 8;
        unsigned sign      : 1;
    }s;

}uMcFloatFmt;

int    ntc_get_float_sign(float fVal);              // 取得一个flaot的符号位  sign = -1 / +1
void   vtc_set_float_sign(float *pfVal, int sign);  // 设置一个浮点数的符号位 sign = -1 / +1
///*}

/******************************************************************************
 * 数据名称: double 类型的合成与解合成
 * 数据说明:
 * 浮点数在机内用指数型式表示，分解为：数符，尾数，指数符，指数四部分。
 * 无论是单精度还是双精度在存储中都分为三个部分：
 *   1.符号位(Sign) : 0代表正，1代表为负
 *   2.指数位（Exponent）:用于存储科学计数法中的指数数据，并且采用移位存储
 *   3.尾数部分（Mantissa）：尾数部分
 *
{*///
typedef union
{
    double v;
    struct
    {
        unsigned mantissa2 : 32;
        unsigned mantissa1 : 20;
        unsigned exponent  : 11;
        unsigned sign      :  1;
    } s;

}uMcDoubleFmt;

int    ntc_get_double_sign(double dVal);              // 取得一个double的符号位 sign = -1 / +1
void   vtc_set_double_sign(double *pdVal, int sign);  // 设置一个浮点数的符号位 sign = -1 / +1
///*}
///*}


/*********************************************
 *  BCD 转换函数
 *
 *
{*///
UINT8 uctc_get_bcd_0(UINT8 ucData);        // 获得该数的BCD低位
UINT8 uctc_get_bcd_1(UINT8 ucData);        // 获得该数的BCD高位
///*}

/***************************************************************************
 * BCD 与 字符串的转换函数
 * len 必须为偶数
 *
{*///
eTcErr etc_str_to_bcd(const UINT8* pstr, UINT8* pbcd, INT32 len);
eTcErr etc_bcd_to_str(const UINT8* pbcd, UINT8* pstr, INT32 len);
///*}

/*******************************************************
 *  子命令信息数据表及映射函数
 *
{*///
typedef enum
{
    TC_ROLE_UNKOWN,    // 未知身份
    TC_ROLE_CONTOR,    // 集中器
    TC_ROLE_TERMIN,    // 终端
}eTcRole;              // 协议应用模块的身份
 
typedef enum
{
    TC_DIR_UNKOWN,     // 未知报文方向
    TC_DIR_C2T,        // 集中器到终端  下行
    TC_DIR_T2C,        // 终端到集中器  上行
}eTcDir;               // 报文的发送方向

typedef enum
{
    TC_PN_UNKOWN,      // 未知PN类型
    TC_PN_P0,          // P0 不关心PN 集中器本身
    TC_PN_MP,          // 测量点号(measured point)
    TC_PN_TK,          // 任务号  (task number)
    TC_PN_TM,          // 终端号

}eTcPn;                // Pn类型

typedef struct
{
    eTcmd    eCmd;     // 子命令标识
    eTcDir   eDir;     // 该报文存在的方向类型
    eTcPn    ePn;      // Pn类型
    pTcFunc  pFunc;    // 该命令对应的用户侧数据与封装侧数据结构转换函数

    #if TC_CFG_NAME
    char*    pName;    // 该协议信息的中文含义
    #endif
    
}sTcmdInfor;
///*}

// 通过命令类型和报文方向获得该命令对应的相关信息
eTcErr eTcGetCmdInfor(eTcmd eCmd, eTcDir eDir, sTcmdInfor* psInfor);
///*}

/************************************************************
 *  地址域A结构
 *
{*///
// 用户侧结构
#define TC_REGN_LEN   (6)      // 行政区划码A1 长度 (用户侧)
#define TC_A1_LEN     (3)      // 行政区划码A1 长度 (封帧侧)
#define TC_A_LEN      (8)      // 地址域 帧侧长度

typedef struct
{
    UINT8  acRegionCode[TC_REGN_LEN];   // 行政区划码A1 如北京 110000, 行政区划码按GB2260-91的规定执行
    UINT32 ulTmlAddress;                // 监测终端地址A2选址    范围为 1~4294967295
    BOOL   bTeam;                       // 为true 表示ulTmlAddress 为组地址, 为false 表示ulTmlAddress单一地址
    UINT8  ucConAddress;                // 主站地址和组地址标志A3, 范围(0~127)

}sTcA, sTcAddress;

// 封帧侧结构
#pragma pack(1)
typedef struct
{
    UINT8  acRegionCode[TC_A1_LEN];     // 行政区划码A1           (BCD)  低字节在前  高字节在后
    UINT32 ulTmlAddress;                // 监测终端地址A2选址   范围为1~4294967295
    //UINT8  ucTeam:1;                  // 为1表示 ulTmlAddress 为组地址,A2 == 0xFFFF即广播地址, 为 0 表示单地址
    UINT8  ucConAddress;                // 主站地址和组地址标志A3 (BIN)  最好不要用位域

}sTcA_f, sTcAddress_f; // 帧地址格式定义
#pragma pack()

// 转换函数
eTcErr etc_trans_address(eTcTrans eTrans, sTcAddress *psAddr_u, sTcAddress_f *psAddr_f);
///*}

/************************************************************
 *  控制域C 结构及转换函数
 *
 *  封帧侧为2字节
 *  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+
 *  | D15  | D14  | D13  | D12  | D11  | D10  |  D9  |  D8  |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+
 *  | DIR  | PRM  | 备用 |            启动帧序号PSEQ        |      启动帧序号PSEQ       |          帧功能码         |
 *  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+
 *
 *
 * DIR 传输方向位   DIR = 0 表示此帧报文是由主(子)站向信息集中与交互终端发出的下行报文
 *                  DIR = 1 表示此帧报文是由信息集中与交互终端向主(子)站发出的上行报文
 *
 * PRM 启动标志位   PRM = 0 表示此帧报文来自从动（响应）站，从动站（响应站）向启动站传输报文
 *                  PRM = 1 表示此帧报文来自启动站，启动站向从动站传输报文
 *
 *  启动帧序号PSEQ
 *      (1)启动帧序号PSEQ用编码表示0~31，用于区别和对应传输帧，以及防止信息传输的丢失或重复。
 *      (2)每一对启动站和从动站之间均有1个独立的计数器，用于记录当前PSEQ，启动站向同一
 *         从动站发起新的传输服务时，PSEQ+1。若超时未收到从动站的报文，
 *         或接收出现差错，则启动站不改变PSEQ，重复原来的传输服务
 *
 *  响应帧序号RSEQ
 *      (1)响应帧序号RSEQ在PRM=0时，即从动帧中有效，用编码表示0~15，用于多个从动帧对应一个启动帧的传输
 *      (2)每一对启动站和从动站之间均有1个独立的计数器，用于记录当前RSEQ，当只需一帧从动帧回应启动帧的，RSEQ=0；
 *         当需用n（n≤16）帧回应的，RSEQ从n-1起递减计数，每回送一帧减1，直至最后一帧RSEQ=0
 *         从动站发起新的传输服务时，PSEQ+1。若超时未收到从动站的报
 *
 *  帧功能码，固定帧和可变帧的帧功能码定义不同
 *
{*///

typedef enum
{
    TC_PRM_UNKWON,                 // 未知方向
    TC_PRM_A2P,                    // 该帧来自于主动站
    TC_PRM_P2A,                    // 该帧来自于从动站

}eTcPRM;                           // 控制域中PRM字段描述

// 获得某方向某命令该的PRM属性
eTcPRM etc_get_prm(eTcDir eDir, eTcAFN eAfn, BOOL bAuto);

typedef enum
{
    // 固定帧
    // PRM 0
    TC_FCD_LINK_OK      = 0,       // 确认

    // PRM 1
    TC_FCD_LOG_IN       = 1,       // 建立链路、登录系统
    TC_FCD_LOG_OUT      = 2,       // 拆除链路、退出系统
    TC_FCD_HEART_BEAT   = 3,       // 保持链路、在线心跳


    // 可变帧
    // PRM 0
    TC_FCD_OK           = 0,       // 链路用户确认
    TC_FCD_ANSWER       = 1,       // 以用户数据响应请求

    // PRM 1
    TC_FCD_NOTI         = 0,       // 发送 ∕无回答
    TC_FCD_CONF         = 1,       // 发送 ∕确认
    TC_FCD_ASK          = 2,       // 请求 ∕响应

    TC_FCD_MAX,

}eTcFcode;       // 控制域功能码

#define TC_C_LEN       (2)         // 控制域C　帧侧字长

#define TC_PSEQ_MIN    (0)         // PSEQ 最小值
#define TC_PSEQ_MAX    (31)        // PSEQ 最大值

#define TC_RSEQ_MIN    (0)         // PSEQ 最小值
#define TC_RSEQ_MAX    (15)        // PSEQ 最大值

// 用户侧
typedef struct
{
    eTcDir     eDir;               // 上下行
    eTcPRM     ePRM;               // 标志该报文是来自启动站 还是从动站
    UINT8      ucPSEQ;             // 启动帧序号 PSEQ
    UINT8      ucRSEQ;             // 响应帧序号 RSEQ
    eTcFcode   eFcode;             // 帧功能码

}sTctrl;

// 帧侧
// UINT16 usTcCtrl;
// 转换函数
eTcErr etc_trans_ctrl(eTcTrans eTrans, sTctrl* puCtrl, UINT16* pfCtrl);

// 获得 eTcFcode 帧侧对应的功能码
eTcErr etc_get_fcode(eTcmd eCmd, eTcDir eDir, eTcPRM ePRM, eTcFcode * peFcode);


// 封装函数
eTcErr etc_get_ctrl(eTcAFN eAFN, eTcDir eDir, eTcPRM ePRM, sTctrl *psCtrl);
///*}
/************************************************************
 *  应用控制域AC 结构及转换函数
 *
 *  封帧侧为1字节
 *  +------+------+------+------+------+------+------+------+
 *  |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +------+------+------+------+------+------+------+------+
 *  |  Tpv |  ACD |  --  |          应用功能码 AFN          |
 *  +------+------+------+------+------+------+------+------+
 *
 *
 * Tpv 时间标签有效位 Tpv
 *     TpV=0：表示在附加信息域中[无]时间标签 Tp
 *     TpV=1：表示在附加信息域中[有]时间标签 Tp
 *
 * ACD 请示访问位
 *     ACD=1：表示有重要事件数据等待访问，且附加信息域中有 EC
 *     ACD=0：表示无重要事件数据等待访问
 *
 * AFN 应用功能码
 *     0   确认∕否认
 *     1   复位
 *     4   设置参数
 *     5   控制命令
 *     6   身份认证及密钥协商
 *     10  查询参数
 *     12  请求（定时上报）任务数据
 *     13  请求实时数据
 *     14  请求（主动上报）事件记录
 *     15  文件传输
 *     16  数据转发
 *
{*///
// 用户侧结构
typedef struct
{
    BOOL    bTp;    // 是否有Tp
    BOOL    bEc;    // 是否有Ec
    eTcAFN  eAfn;   // 应用功能码

}sTcAc;             // 应用控制域AC

// 封装侧结构
// ucAc;

// 转换函数
eTcErr etc_trans_ac(eTcTrans eTrans, sTcAc* puAc, UINT8* pfAc);
///*}

/************************************************************
 *  数据标识单元
 *  每个数据标识单元的信息是组的形式组织的
 *  每个数据标识单元包含最多(8)个Fn 及最多包含(8)个Pn
 *
 * -----
 * DADT 帧侧结构
 * 信息点 | DA | DA1 | D7 D6 D5 D4 D3 D2 D1 D0
 *        |    | DA2 | D7 D6 D5 D4 D3 D2 D1 D0
 * 信息类 | DT | DT1 | D7 D6 D5 D4 D3 D2 D1 D0
 *        |    | DT2 | D7 D6 D5 D4 D3 D2 D1 D0
 *
 * ---
 * 信息点DA由信息点元DA1和信息点组DA2两个字节构成
 * DA1 对位表示某一信息点组的1～8个信息点
 * DA2 采用二进制编码方式表示信息点组
 * DA1、DA2共同构成信息点标识pn（n = 1～2040）
 * 信息点标识pn对应于不同信息类标识Fn可以是以下各种含义
 * 测量点号、总加组号、控制轮次、直流模拟量端口号、任务号
 *
 * 信息点组DA2 | 信息点元DA1
 *       D7~D0 | D7    D6    D5    D4    D3    D2    D1    D0
 *           1 | p8    p7    p6    P5    p4    p3    p2    p1
 *           2 | p16   p15   p14   p13   p12   p11   p10   p9
 *           3 | p24   p23   p22   p21   p20   p19   p18   p17
 *          .. | ...   ...   ...   ...   ...   ...   ...   ...
 *          255| P2040 P2039 P2038 P2037 P2036 P2035 P2034 P2033
 *
 * ---
 * 信息类DT由信息类元DT1和信息类组DT2两个字节构成
 * DT1 对位表示某一信息类组的1～8种信息类型
 * DT2 采用二进制编码方式表示信息类组
 * DT1 DT2 共同构成信息类标识Fn（n = 1～248）
 *
 * 信息类组DT2 | 信息类元D T1
 *       D7~D0 | D7   D6   D5   D4   D3   D2   D1   D0
 *           0 | F8   F7   F6   F5   F4   F3   F2   F1
 *           1 | F16  F15  F14  F13  F12  F11  F10  F9
 *           2 | F24  F23  F22  F21  F20  F19  F18  F17
 *          .. | ...  ...  ...  ...  ...  ...  ...  ...
 *          30 | F248 F247 F246 F245 F244 F243 F242 F241
 *
{*///

// 用户侧结构
typedef struct
{

    UINT16  usPn[TC_PN_INDEX_MAX];      // Pn (0 ~ 2040)
                                        // TC_PN_MAX  最大值
                                        // TC_PN_MIN  最小值
                                        // TC_PN_NONE 无效值

    UINT8   ucFn[TC_FN_INDEX_MAX];      // Fn (1 ~ 248)
                                        // TC_FN_MAX  最大值
                                        // TC_FN_MIN  最小值
                                        // TC_FN_NONE 无效值
}sTcPnFn;

// 帧侧结构
typedef struct
{
    UINT8       ucDA1;         // 信息点元
    UINT8       ucDA2;         // 信息点组
    UINT8       ucDT1;         // 信息类元
    UINT8       ucDT2;         // 信息类组
}sTcDaDt;

// 转换函数
eTcErr etc_pnfn_to_dadt(sTcPnFn* psPnFn, sTcDaDt* psDaDt);
eTcErr etc_dadt_to_pnfn(sTcDaDt* psDaDt, sTcPnFn* psPnFn);

typedef struct
{
    eTcmd  eCmd;
    UINT16 usPn;
}sTcmdPn;

// 内部函数
// 获得命令对应的AFN
eTcAFN eTcGetCmdAfn(eTcmd eCmd);

// 获得命令对应的Fn
UINT8  ucTcGetCmdFn(eTcmd eCmd);

// 判断最8个Pn是否在同一个信息点组,同时取得所属的信息点组
BOOL btc_same_team_pn(UINT16 *pUsPn8, UINT8* pucDa2);

// 判断一组Pn是否都为0
BOOL btc_is_p0(UINT16 *pUsPn8);

// 获得pn对应的信息点组
UINT8 uctc_get_pn_team(UINT16 usPn);

// 获得一组pn对应的信息点组
UINT8 uctc_get_pn8_team(UINT16 *pusPn);

// 判断某一个pn是否在一组8个pn中
BOOL btc_in_pn8(UINT16 usPn, UINT16 *pusPn8);

// 判断最8个Fn是否在同一个信息类组,同时取得所属的信息类组
BOOL btc_same_team_fn(UINT8  *pUcFn8, UINT8* pucDt2);

// 获得Fn对应的信息点组
UINT8 uctc_get_fn_team(UINT8 ucFn);

// 获得Fn对应的信息点在某组的bit
UINT8 uctc_get_fn_bit(UINT8 ucFn);

// 获得一组Fn对应的信息点组
UINT8 uctc_get_fn8_team(UINT8 *pucFn);

// 判断某一个fn是否在一组8个fn中
BOOL btc_in_fn8(UINT8 ucFn, UINT8 *pucFn8);

// 转换函数
eTcErr etc_add_cmdpn(sTcmdPn* psCmdPn,sTcmdPn sNewCmdPn, UINT8 *pucNumCmdPn);
eTcErr etc_pnfn_to_cmdpn(eTcAFN eAfn, sTcPnFn* psPnFn, UINT8 ucNumPnFn,   sTcmdPn* psCmdPn, UINT8 *pucNumCmdPn);
eTcErr etc_cmdpn_to_pnfn(eTcAFN eAfn, sTcPnFn* psPnFn, UINT8 *pucNumPnFn, sTcmdPn* psCmdPn, UINT8  ucNumCmdPn);
eTcErr etc_dadt_to_cmdpn(eTcAFN eAfn, sTcDaDt* psDaDt, UINT8 ucNumDaDt,   sTcmdPn* psCmdPn, UINT8 *pucNumCmdPn);
eTcErr etc_cmdpn_to_dadt(eTcAFN eAfn, sTcDaDt* psDaDt, UINT8 *pucNumDaDt, sTcmdPn* psCmdPn, UINT8  ucNumCmdPn);
///*}

/************************************************************
 *  Tp 时间标签格式
 *
{*///
// 用户侧
typedef struct
{
    sTcFmt03 sTime;                 // 启动帧发送时标
    UINT8    ucPermitDelayMinutes;  // 允许发送传输延时时间(分钟);
}sTcTp;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sTcFmt03_f sTime;                 // 启动帧发送时标
    UINT8      ucPermitDelayMinutes;  // 允许发送传输延时时间(分钟);
}sTcTp_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_tp(eTcTrans eTrans, sTcTp* pUser, sTcTp_f* pFrame);

// 获得当前用户侧Tp
eTcErr etc_get_tp(sTcTp *psuTp);   

// 以当前时间为基准判断一个tp是否超时
BOOL  btc_tp_timeout(sTcTp *psTP);
///*}

/*******************************************
 *  数据项相关
 *  协议允许应答中每个实际的数据项为空,在帧侧需要将该数据内容域填充0xEE
{*///
BOOL   btc_is_0xEE(UINT8* pData, UINT16 usLen);    // 判断帧侧某数据项是否是无效的
void   vtc_set_0xEE(UINT8* pData, UINT16 usLen);   // 将帧侧某数据项设置为无效

BOOL   btc_is_none(UINT8* pData, UINT16 usLen);    // 数据项缺少
void   vtc_set_none(UINT8* pData, UINT16 usLen);   // 将数据项设置为缺少
///*}

/************************************************************
 *  附加信息域 AUX 定义
 *
{*///

BOOL   btc_have_pw(eTcAFN eAFN, eTcDir eDir);      // 此类报文中是否应该有pw字段
BOOL   btc_have_ec(eTcAFN eAFN, eTcDir eDir);      // 此类报文中是否应该有EC字段
BOOL   btc_have_tp(eTcAFN eAFN, eTcDir eDir);      // 此类报文中是否应该有tp字段

// 用户侧
typedef struct
{
    UINT16 usEC1;              // 重要事件计数器 EC1
    UINT16 usEC2;              // 一般事件计数器 EC2

}sTcEc, sTcEc_f;

// 事件计数设置函数
void vtc_set_ec(sTcEc *psEc);

// 获得报文中附加域的帧侧的总字节数据
UINT16 ustc_get_aux_len(eTcAFN eAFN, eTcDir eDir, BOOL bEc, BOOL bTp); 

///*}

/*******************************************************
 *  加密与解密函数
 *  关键数据的加密
 *  加密算法:对于应用层需要加密的关键数据,采用对称算法进行数据加解密
 *  加密部分:应用层功能码、数据单元标识及数据单元部分
 *  加密长度:通过密码机采用对称密钥算法将明文数据加密成密文,用户数据长度会相应改变
 *           终端在收到采用对称密钥算法加密的密文信息后,对数据进行解密
 *           解密成功返回原始的明文信息及明文信息的数据长度
 *  报文类型:需要加密的报文类型
 *           (1)复位命令的下行报文
 *           (2)设置参数命令的下行报文
 *           (3)控制命令的下行报文
 *
 *  我的疑问: AFN是否应该加密   如果某加密将无法区分哪个类型加密
 *
{*///
#if TC_CFG_ENCRYPT

// 加密函数类型
typedef eTcErr (*peTcEncryptFunc)(UINT8* pInData, int nInLen, UINT8* pOutData, int *pOutLen);  

// 解密函数类型
typedef eTcErr (*peTcDecryptFunc)(UINT8* pInData, int nInLen, UINT8* pOutData, int *pOutLen);  

#endif
///*} 

/*******************************************************
 *  各数据项定义
 *  
 *  用户侧:默认字节对齐, 供上层调用时使用
 *  封帧侧:1字节对齐,用于封装帧和解析帧
 *  解析函数:实现对各Fn用户侧和封帧侧数据结构的转换功能  
 *  
 *
{*///

/*******************************************
 * 数据名称: 全部确认/否认：对收到报文中的全部数据单元标识进行确认/否认
 * 对应AFN : TC_AFN_00_CONF
 * 对应CMD : TCMD_AFN_0_F1_ALL_OK_DENY
 * PN 类型 : P0
{*///

// 用户结构
typedef enum
{
    TC_RES_OK          = 0,    // 确认
    TC_RES_NONE        = 1,    // 无请求的数据、无设置的参数、无要执行的功能
    TC_RES_NOT_READY   = 2,    // 请求的数据未产生、功能执行未满足
    TC_RES_REMOVE      = 3,    // 请求的数据已经被移出保存窗口
    TC_RES_DATA_OTRNG  = 4,    // 请求的数据超出支持的信息点范围
    TC_RES_PARA_OTRNG  = 5,    // 设置的参数超出支持的信息点范围
    TC_RES_NOT_SAME    = 6,    // 设置的接入端口号及属性与实际不符
    TC_RES_NOT_SUPT    = 7,    // 指定接口不支持转发
    TC_RES_DENY        = 255   // 否认
    
}eTcResCode, sTcAfn00F1;                   // 确认/否认信息码定义 

// eTcResCode    eResCode;

// 封帧结构
//UINT8  ucResCode;

// 转换函数
eTcErr etc_trans_afn00f1(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 逐个确认与否认
 * 对应AFN : TC_AFN_00_CONF
 * 对应CMD : TCMD_AFN_0_F2_ONE_BY_ONE
 * PN 类型 : P0
{*///
// 用户侧数据
typedef struct
{
    eTcmd       eCmd;         // 确认对应的功能码
    UINT16      usPn;         // Pn  0 ~ 2040
    eTcResCode  eResCode;     // 答复码
}sTcmdErr;                    // 确认与否认 用户侧数据结构

typedef struct
{
    eTcAFN        eAFN;       // 需要确认的AFN
    UINT8        ucNum;       // 需要确认 或 否认的 Fn个数
    sTcmdErr   sOne[1];       // ucNum 个sMtUFnPnErr  
}sTcOnebyOne;                 // 确认与否认 (用户侧数据结构)

// 帧侧数据
#pragma pack(1) 
typedef struct
{
    sTcPnFn     sPnFn;
    eTcResCode  eResCode;
}sTcFnPnErr;                   // 确认与否认 用户侧数据结构

typedef struct
{
    sTcDaDt     sDaDt;         // 数据单元标识
    UINT8       ucErr;         // 错误 标识   (0 正确 1 错误)
}sTcOne_f;                     // 确认与否认  帧侧数据结构   

typedef struct
{
    UINT8       ucAFN;
    sTcOne_f    sOne[1];
}sTcOneByOne_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn00f2(eTcTrans eTrans,void* psUser, void* psFrame, UINT16* pusfLen);
///*} 

/*******************************************
 * 数据名称: 指定数据清零(仅实时数据单元标识有效)
 * 对应AFN : TC_AFN_01_RSET
 * 对应CMD : TCMD_AFN_1_F5_DATA_CLEAR
 * PN 类型 : P0
{*///

// 用户侧
typedef struct
{
    UINT8   ucNum;      // 清零的数据项个数
    sTcmdPn sCmdPn[1];  // ucNum 个命令与pn的组合

}sTcDataClear, sTcAfn01f5, sTcRtDataClear;

// 封装侧
#pragma pack(1)
typedef struct
{
    UINT8    ucNum;    // 数据单元标识个数
    sTcDaDt  sDaDt[1]; // ncNum个数据单元标识

}sTcDataClear_f, sTcAfn01f5_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn01f5(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: IP地址数据结构
{*///
typedef enum
{
    TC_IP_UNKOWN,
    TC_IP_V4,
    TC_IP_V6,
}eTcIp;

// IP地址 子网掩码
typedef struct
{
    eTcIp eVersion;
    UINT8 ip[TC_IP_LEN];
}sTcIp, sTcMask;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8  ucVersion;
    UINT8 ip[TC_IP_LEN];

}sTcIp_f, sTcMask_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_ip(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 集中与交互终端IP地址和端口
 * 对应AFN : TC_AFN_04_SETP
 * 对应CMD : TCMD_AFN_4_F1_CON_IP_PORT
 *           TCMD_AFN_A_F1_CON_IP_PORT
 * PN 类型 : P0
{*///
// 用户侧
#define TC_APN_LEN  (16)
typedef struct
{
    sTcIp       sMainIp;             // 主用IP地址
    UINT16      usMainPort;          // 主用端口地址
    sTcIp       sBackIp;             // 备用IP地址
    UINT16      usBackPort;          // 备用端口地址
    UINT8       ucAPN[TC_APN_LEN];   // APN
    UINT8       ucUsr[32];           // 用户名
    UINT8       ucPwd[32];           // 密码
    
}sTcDownCfg, sTcAfn04f1;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sTcIp_f     sMainIp;             // 主用IP地址
    UINT16      usMainPort;          // 主用端口地址
    sTcIp_f     sBackIp;             // 备用IP地址
    UINT16      usBackPort;          // 备用端口地址
    UINT8       ucAPN[TC_APN_LEN];   // APN
    UINT8       ucUsr[32];           // 用户名
    UINT8       ucPwd[32];           // 密码
}sTcDownCfg_f, sTcAfn04f1_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn04f1(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 监测终端上行通信参数配置
 * 对应AFN : TC_AFN_04_SETP
 * 对应CMD : TCMD_AFN_4_F2_TML_UP_CFG
 *           TCMD_AFN_A_F2_TML_UP_CFG
 * PN 类型 : P0
{*///

#define TC_TML_UP_PROTO   (1) // 终端上行通信协议类型
// 用户侧
typedef enum
{
   TC_TUPP_UNKOWN,           // 未知属性
   TC_TUPP_DEL,              // 删除该监测终端号的配置参数
   TC_TUPP_SER,              // 串口
   TC_TUPP_ETH,              // 以太网
}eTcUpPara;                  // 监测终端上行通信端口属性

typedef enum
{
    TC_DELG_UNKOWN,  // 未知代理 
    TC_DELG_NULL,    // 不使用代理
    TC_DELG_HTTP,    // 使用http connect代理
    TC_DELG_SOCK4,   // 使用sock4代理
    TC_DELG_SOCK5,   // 使用sock5代理
   
}eTcDelegate;

// 代理服务器连接方式
typedef enum
{
    TC_DELK_UNKOWN, // 未知方式
    TC_DELK_ANYONE, // 无需要验证
    TC_DELK_USRPWD, // 需要用户名和密码
}eTcDelgLink;

typedef struct
{
    UINT16    usListenPort;     // 侦听端口号 
    sTcIp            sUpIp;     // IP地址
    sTcMask        sUpMask;     // 监测终端子网掩码地址
    sTcIp          sGateIp;     // 网关地址
    eTcDelegate  eDelegate;     // 代理类型
    sTcIp          sDelgIp;     // 代理服务地址IP地址
    UINT16      usDelgPort;     // 代理服务端口
    eTcDelgLink  eDelgLink;     // 代理服务器连接方式
    BOOL          bDlegUsr;     // 是否需要代理服务器用户名
    UINT8     ucDlegUsrLen;     // 代理服务器用户名长度 (1~20)
    UINT8    ucDlegUsr[20];     // 代理服务器用户名   
    BOOL          bDlegPwd;     // 是否需要
    UINT8     ucDlegPwdLen;     // 代理服务器密码长度   (1~20)
    UINT8    ucDlegPwd[20];     // 代理服务器密码
    UINT8   ucPermitDelayM;     // 监测终端作为启动站允许传输延时时间 (单位:分钟 0~255)
    UINT8    ucReSendTimes;     // 重发次数 (0~3)   0 表示不允许重发
    UINT8      ucHeartBeat;     // 心跳周期
    UINT16  usWaitTimeoutS;     // 监测终端作为启动站等待应答的超时时间 (秒数 0~4095)
    BOOL         bPermitTk;     // 任务数据 是否允许监测终端需要集中器确认
    BOOL         bPermitEv;     // 事件数据 是否允许监测终端需要集中器确认

}sTcTmlUpCfg, sTcAfn04f2;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT16    usListenPort;     // 监测终端侦听信端口号 
    sTcIp_f          sUpIp;     // 监测终端上行IP地址
    sTcMask_f      sUpMask;     // 监测终端子网掩码地址
    sTcIp_f        sGateIp;     // 网关地址
    UINT8       ucDelegate;     // 代理类型
    sTcIp_f        sDelgIp;     // 代理服务地址IP地址
    UINT16      usDelgPort;     // 代理服务端口
    UINT8       ucDelgLink;     // 代理服务器连接方式
    UINT8         ucUsrLen;     // 代理服务器用户名长度m (0~20) 0表示不需要用户名验证
    /* 以下为变长
    UINT8     ucDlegUsr[m];     // 代理服务器用户名
    UINT8     ucDlegPwdLen;     // 代理服务器密码长度 n  (0~20) 0表示不需要密码验证
    UINT8     ucDlegPwd[n];     // 代理服务器密码

    // 和结构 sTcUpCfg_f 相同
    UINT8  ucPermitDelayM;      // 信息集中与交互终端作为启动站允许传输延时时间 
    UINT8  ucSWTS1;             // 信息集中与交互终端作为启动站等待应答的超时时间和重发次数
    UINT8  ucSWTS2;             // 终端等待从动站响应的超时时间和重发次数 wait ts
    UINT8  bs8Con;              // 信息集中与交互终端作为启动站需确认应答的传输服务标志 
    UINT8  ucHeartBeat;         // 心跳周期                     
    */ 
}sTcTmlUpCfg_f, sTcAfn04f2_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn04f2(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 信息集中与交互终端上行通信消息认证参数
 * 对应AFN : TC_AFN_04_SETP
 * 对应CMD : TCMD_AFN_4_F3_TML_AUTH_PARA
 *           TCMD_AFN_A_F3_TML_AUTH_PARA
 * PN 类型 : P0
{*///
// 用户侧
typedef struct
{
    UINT8     ucTypeID;   // 用于表示由系统约定的各种消息认证方案，取值范围0～255
                          // 其中：0表示不认证，255表示专用硬件认证方案，
                          // 1～254用于表示各种软件认证方案
    UINT16    usAuthPara; // 消息认证方案参数
}sTcAuthPara, sTcAfn04f3;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8     ucTypeID; 
    UINT16    usAuthPara; 
}sTcAuthPara_f, sTcAfn04f3_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn04f3(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 设备状态量输入参数
 * 对应AFN : TC_AFN_04_SETP
 * 对应CMD : TCMD_AFN_4_F4_TML_STATE_INPUT
             TCMD_AFN_A_F4_TML_STATE_INPUT
 * PN 类型 : P0
{*///
// 用户侧
typedef struct
{
    BOOL bIn[8];       // 状态量接入标志位（对应 1～8 路状态量）置true接入.      置 false 未接入
    BOOL bOn[8];       // 状态量属性标志位（对应 1～8 路状态量） 置true常开触点。置 false 常闭触点

}sTcStateInput, sTcAfn04f4;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8 bIn;
    UINT8 bOn;

}sTcStateInput_f, sTcAfn04f4_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn04f4(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 事件记录配置
 * 对应AFN : TC_AFN_04_SETP
 * 对应CMD : TCMD_AFN_4_F5_TML_EVENT_CFG
             TCMD_AFN_A_F5_TML_EVENT_CFG
 * PN 类型 : P0
{*///

// 用户侧
typedef struct
{   
    UINT8      ucNeed;   // 需要记录的事件记录的类型个数   
    eTcErc  aNeed[64];   // ucErcNeed个需要记录的事件记录具体类型
    UINT8      ucImpt;   // 设置为重要事件的个数
    eTcErc  aImpt[64];   // ucErcImpt个事件设置为重要的事件(那么其余的就是一般事件)
                         // 事件重要性等级标志位：D0～D63 按顺序对位表示事件代码 ERC1～ERC64 所定义的事件。
                         //     置“1”：该位所对应的告警事件为重要事件，该事件发生后，如通道具备主动上报条件，
                         // 应主动上报事件记录，如不具备主动上报条件，通过 ACD 位上报；
                         //     置“0”：该位所对应的告警事件为一般事件，该事件发生后，只需要进行事件记录；

}sTcEventCfg, sTcAfn04f5;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8     aNeed[8];  // 事件记录有效标志位
    UINT8     aImpt[8];  // 事件重要性等级标志位
    
}sTcEventCfg_f, sTcAfn04f5_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn04f5(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 冻结数据任务参数
 * 对应AFN : TC_AFN_04_SETP
 * 对应CMD : TCMD_AFN_4_F17_FREZ_TASK_PARA
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef enum
{
    TC_PUNT_UNKOWN,  // 未知的周期单位
    TC_PUNT_MONTH,   // 月
    TC_PUNT_DAY,     // 日
    TC_PUNT_HOUR,    // 时
    TC_PUNT_MIN,     // 分钟
    TC_PUNT_SEC,     // 秒
    TC_PUNT_MS,      // 毫秒
}eTcPeriodUnit;      // 冻结周期单位

typedef struct
{
    UINT16         usPeriod;         // 冻结周期 为定时冻结的时间间隔，为0表示删除本项冻结任务。
    eTcPeriodUnit     eUnit;         // 冻结周期单位
    UINT8           ucTimes;         // 冻结周期数：表示以冻结周期为间隔，需冻结的次数，为0表示无限次数。 
}sTcFrezPeriod;

typedef struct
{
    sTcYWMDhms      sTimeFrez;         // 冻结基准时间：秒分时日月年 
    sTcYWMDhms      sTimeRprt;         // 上报基准时间：秒分时日月年
    sTcFrezPeriod      sFreez;         // 冻结周期
    UINT8         ucPeriodRpt;         // 定时上报周期    ：为定时上报数据的时间间隔，0为本项冻结任务内容无需定时上报。
    eTcPeriodUnit    eUnitRpt;         // 定时上报周期单位：数值范围1~4，依次分别表示分、时、日、月，其他备用
    UINT8           uCmdPnNum;         // 需要冻结的数据单元标识 个数
    sTcmdPn         sCmdPn[1];         // 需要冻结的数据单元标识 内容
    
}sTcFrezTaskPara, sTcAfn04f49;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT16         usPeriod;         // 冻结周期 为定时冻结的时间间隔，为0表示删除本项冻结任务。
    UINT8             eUnit;         // 冻结周期单位
    UINT8           ucTimes;         // 冻结周期数：表示以冻结周期为间隔，需冻结的次数，为0表示无限次数。 
}sTcFrezPeriod_f;

typedef struct
{
    sTcFmt01_f        sTimeFrez;     // 冻结基准时间：秒分时日月年 
    sTcFrezPeriod_f      sFreez;     // 冻结周期 
    UINT8             ucDaDtNum;     // 数据单元标识个数

    // 以下为变长
    /*
    sTcDaDt        sDaDt[1];         // ucDaDtNum 个数据单元标识
    sTcFmt01_f        sTimeRprt;     // 冻结基准时间：秒分时日月年 
    UINT8             eUnit;         // 定时上报周期
    UINT8           ucTimes;         // 定时上报周期单位 
    */
}sTcFrezTaskPara_f, sTcAfn04f49_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn04f17(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 电气测量点配置参数
 * 对应AFN : TC_AFN_04_SETP
 * 对应CMD : TCMD_AFN_4_F25_ELEC_MP_CFG
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef enum
{
    TC_BAUD_UNKOWN,
    TC_BAUD_DEFAULT,        // 无须设置或使用默认
    TC_BAUD_1200,            
    TC_BAUD_2400,
    TC_BAUD_4800,
    TC_BAUD_9600,
    TC_BAUD_19200,
    TC_BAUD_38400,         
    TC_BAUD_76800,   
}eTcSerBaud;                // 串口波特率

typedef enum
{
    TC_SBIT_5,
    TC_SBIT_6,
    TC_SBIT_7,
    TC_SBIT_8,

}eTcSerBit;

typedef struct
{
    eTcSerBaud      eBaud;  // 波特率
    BOOL           bStop1;  // 1停止位(true) 2停止位(false)
    BOOL           bCheck;  // 有校验(true) 无校验(false) 
    BOOL             bOdd;  // 奇校验(true) 偶校验(true)
    eTcSerBit        eBit;  // 5~8位数
}sTcAcsParaSer;             // 接入端口运行参数数据格式-串口

// 结构sTcAcsParaSer 转换函数
eTcErr etc_trans_serial(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);

typedef enum
{
   TC_ACS_PROT_UNKOWN,      // 未知通信协议类型
   TC_ACS_PROT_DLT645_97,   // 1 DL/T645-1997 
   TC_ACS_PROT_DLT645_07,   // 2 DL/T645-2007
   TC_ACS_PROT_MODBUS,      // 3 Modbus
   TC_ACS_PROT_USER = 128,  // (128~255)表示自定义
}eTcAcsProto;               // 接入设备通信类型

typedef enum
{
    TC_ACS_PORT_UNKOWN,     // 未知接口属性
    TC_ACS_PORT_DC,         // 直流模拟量
    TC_ACS_PORT_AC,         // 交流模拟量
    TC_ACS_PORT_SER,        // 串口(RS485/RS232)
    TC_ACS_PORT_ETH,        // 以太网
    TC_ACS_PORT_ZIGB,       // zigbee
    TC_ACS_PORT_USER = 128, // 128~255 用户自定义 
    
}eTcAcsPort;                // 接入端口属性

typedef struct
{
    UINT16          usPort; // 接入设备侦听端口号
    sTcMask          sMask; // 子网掩码地址
    sTcIp            sGate; // 网关地址
}sTcAcsParaEth;             // 接入端口运行参数数据格式-以太网

typedef struct
{

    UINT8            ucPort;     // 编码表示0~255，为0表示删除该电气测量点的配置参数
    UINT8        ucAddr[16];     // 接入设备通信地址
    eTcAcsProto   eAcsProto;     // 接入设备通信协议类型
    UINT8          ucPwd[6];     // 通信密码
    
    eTcAcsPort     eAcsPort;     // 接入终端属性 决定 uPortPara的内容
    union
    {
                                 // eAcsPort == TC_ACS_PORT_DC   直流模拟量无参数数据
                                 // eAcsPort == TC_ACS_PORT_AC   交流模拟量无参数数据
        sTcAcsParaSer  sSer;     // eAcsPort == TC_ACS_PORT_SER  串口运行参数
        sTcAcsParaEth  sEth;     // eAcsPort == TC_ACS_PORT_ETH  以太网运行参数
        UINT32   ulAddrZigb;     // eAcsPort == TC_ACS_PORT_ZIGB Zigbee地址 
        
    }uPortPara;                  // 接入端口运行参数内容

}sTcElecMpCfg, sTcAfn04f25;

// 封帧侧
#pragma pack(1)

typedef struct
{
    UINT16            usPort;    // 接入设备侦听端口号
    sTcMask_f          sMask;    // 子网掩码地址
    sTcIp_f            sGate;    // 网关地址
}sTcAcsParaEth_f;                // 接入端口运行参数数据格式-以太网

typedef struct
{

    UINT8            ucPort;     // 编码表示0~255，为0表示删除该电气测量点的配置参数
    UINT8      ucAddrBcd[8];     // 接入设备通信地址(BCD)
    UINT8         eAcsProto;     // 接入设备通信协议类型
    UINT8          ucPwd[6];     // 通信密码
    UINT8          eAcsPort;     // 接入终端属性
    UINT8      ucAcsParaLen;     // 对应的运行参数的结构长度

    /* 变长的运行参数结构
                                 // TC_ACS_PORT_DC 直流模拟量无参数数据
                                 // TC_ACS_PORT_AC 交流模拟量无参数数据
    UINT8            sSer;       // TC_ACS_PORT_SER  串口运行参数
    sTcAcsParaEth_f  sEth;       // TC_ACS_PORT_ETH  以太网运行参数
    UINT32   ulAddrZigb;         // TC_ACS_PORT_ZIGB Zigbee地址 

    */

}sTcElecMpCfg_f, sTcAfn04f25_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn04f25(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 电气测量点基本参数
 * 对应AFN : TC_AFN_04_SETP
 * 对应CMD : TCMD_AFN_4_F26_ELEC_MP_BASE
 * PN 类型 : 电气测量点号
{*///

#define TC_DNUM_INTGR_MIN   (4)  // 整数位数最小值
#define TC_DNUM_INTGR_MAX   (7)  // 整数位数最大值

#define TC_DNUM_DECIM_MIN   (1)  // 小数位数最小值
#define TC_DNUM_DECIM_MAX   (4)  // 小数位数最大值

typedef struct
{
    UINT8       ucInteger; // 有功电能示值的整数位个数(4~7)
    UINT8       ucDecimal; // 有功电能示值的小数位个数(1~4)
}sTcDigitNum;    

typedef enum
{   
    TC_LINK_UNKOWN, // 未知
    TC_LINK_P3_L3,  // 三相三线
    TC_LINK_P3_L4,  // 三相四线
    TC_LINK_P1,     // 单相表
    
}eTcLink;

typedef enum
{
    TC_PHASE_UNKOWN, // 未知
    TC_PHASE_A,      // A 相
    TC_PHASE_B,      // B 相
    TC_PHASE_C,      // C 相
    
}eTcPhase;

typedef struct
{
    eTcLink    eLink;
    eTcPhase   ePhase;
    
}sTcLinkWay; // 电源接线方式

// 用户侧
typedef struct
{
    sTcDigitNum      sDigit; // 有功电能示值整数位及小数位个数
    UINT16         usTimesU; // 电压互感器倍率
    UINT16         usTimesI; // 电流互感器倍率
    float                fU; // 额定电压   (+)XXX.X  (V)
    float                fI; // 额定电流(+/-)XXX.XXX (A)
    sTcLinkWay     sLinkWay; // 电源接线方式
}sTcElecMpBase, sTcAfn04f26;

// 封帧侧
#pragma pack(1)
typedef struct
{   
    UINT8            sDigit; // 有功电能示值整数位及小数位个数
    UINT16         usTimesU; // 电压互感器倍率
    UINT16         usTimesI; // 电流互感器倍率
    sTcFmt_XXX_X         fU; // 额定电压   (+)XXX.X   (V)
    sTcFmt_sXXX_XXX      fI; // 额定电流 (+/-)XXX.XXX (A)
    UINT8          sLinkWay; // 电源接线方式
    
}sTcElecMpBase_f, sTcAfn04f26_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn04f26(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 电气测量点电能量限值参数
 * 对应AFN : TC_AFN_04_SETP
 * 对应CMD : TCMD_AFN_4_F27_ELEC_LMIT_PARA
 * PN 类型 : 电气测量点号
{*///
typedef struct
{
    float          fUpUp;        // 电压上上限(过压门限) (+)XXX.X
    UINT8         ucTime;        // 持续时间
    float        fFactor;        // 越限恢复系统         (+)XX.XX 
}sTcOverV;                       // 过压判别参数

typedef struct
{
    float      fDownDown;        // 电压下下限(过压门限) (+)XXX.X
    UINT8         ucTime;        // 持续时间
    float        fFactor;        // 越限恢复系统         (+)XX.XX   
}sTcLossV;                       // 欠压判别参数 

typedef struct
{
    float          fUpUp;        // 电流上上限() (+/-)XXX.XXX
    UINT8         ucTime;        // 持续时间
    float        fFactor;        // 越限恢复系统         (+)XX.XX   
}sTcOverI;                       // 过流判别参数

typedef struct
{
    float            fUp;        // 电流上(额定电流上限) (+/-)XXX.XXX
    UINT8         ucTime;        // 持续时间
    float        fFactor;        // 越限恢复系统         (+)XX.XX   
}sTcSuperI;                      // 超额定电流判别参数

typedef struct
{
    float            fUp;        // 0序电流上限 (+/-)XXX.XXX
    UINT8         ucTime;        // 持续时间
    float        fFactor;        // 越限恢复系统         (+)XX.XX   
}sTcZeroI;                       // 零序电流超限判别参数

typedef struct
{
    float         fLimit;        // 三相电压不平衡度限值 (+/-)XX.XXXX
    UINT8         ucTime;        // 持续时间
    float        fFactor;        // 越限恢复系统         (+)XX.XX   
}sTcUnblnV;                      // 三相电压不平衡超限判别参数

typedef struct
{
    float         fLimit;        // 三相电流不平衡度限值 (+/-)XX.XXXX
    UINT8         ucTime;        // 持续时间
    float        fFactor;        // 越限恢复系统         (+)XX.XX   
}sTcUnblnI;                      // 三相电流不平衡超限判别参数

// 用户侧
typedef struct
{
    float             fDropV;    // 电压断相判别参数  (+)XXX.X
    UINT8        ucTimeLossV;    // 电压失压时间判别参数 minutes
    sTcOverV          sOverV;    // 过压判别参数
    sTcLossV          sLossV;    // 欠压判别参数
    sTcOverI          sOverI;    // 过流判别参数
    sTcSuperI        sSuperI;    // 超额定电流判别参数
    sTcZeroI          sZeroI;    // 零序电流超限判别参数
    sTcUnblnV          sUblV;    // 三相电压不平衡超限判别参数
    sTcUnblnI          sUblI;    // 三相电流不平衡超限判别参数
}sTcElecLimitPower, sTcAfn04f27;

// 封帧侧
#pragma pack(1)

typedef struct
{
    sTcFmt08_f     fUpUp;        // 电压上上限(过压门限) (+)XXX.X
    UINT8         ucTime;        // 持续时间
    sTcFmt10_f   fFactor;        // 越限恢复系统         (+)XX.XX 
}sTcOverV_f;                     // 过压判别参数

typedef struct
{
    sTcFmt08_f fDownDown;        // 电压下下限(过压门限) (+)XXX.X
    UINT8         ucTime;        // 持续时间
    sTcFmt10_f   fFactor;        // 越限恢复系统         (+)XX.XX   
}sTcLossV_f;                     // 欠压判别参数 

typedef struct
{
    sTcFmt09_f     fUpUp;        // 电流上上限() (+/-)XXX.XXX
    UINT8         ucTime;        // 持续时间
    sTcFmt10_f   fFactor;        // 越限恢复系统         (+)XX.XX   
}sTcOverI_f;                     // 过流判别参数

typedef struct
{
    sTcFmt09_f       fUp;        // 电流上(额定电流上限) (+/-)XXX.XXX
    UINT8         ucTime;        // 持续时间
    sTcFmt10_f   fFactor;        // 越限恢复系统         (+)XX.XX   
}sTcSuperI_f;                    // 超额定电流判别参数

typedef struct
{
    sTcFmt09_f       fUp;        // 0序电流上限 (+/-)XXX.XXX
    UINT8         ucTime;        // 持续时间
    sTcFmt10_f   fFactor;        // 越限恢复系统         (+)XX.XX   
}sTcZeroI_f;                     // 零序电流超限判别参数

typedef struct
{
    sTcFmt06_f    fLimit;        // 三相电压不平衡度限值 (+/-)XX.XXXX
    UINT8         ucTime;        // 持续时间
    sTcFmt10_f   fFactor;        // 越限恢复系统         (+)XX.XX   
}sTcUnblnV_f;                    // 三相电压不平衡超限判别参数

typedef struct
{
    sTcFmt06_f    fLimit;        // 三相电流不平衡度限值 (+/-)XX.XXXX
    UINT8         ucTime;        // 持续时间
    sTcFmt10_f   fFactor;        // 越限恢复系统         (+)XX.XX   
}sTcUnblnI_f;                    // 三相电流不平衡超限判别参数

typedef struct
{
    sTcFmt08_f        fDropV;    // 电压断相判别参数  
    UINT8        ucTimeLossV;    // 电压失压时间判别参数 minutes
    sTcOverV_f        sOverV;    // 过压判别参数
    sTcLossV_f        sLossV;    // 欠压判别参数
    sTcOverI_f        sOverI;    // 过流判别参数
    sTcSuperI_f      sSuperI;    // 超额定电流判别参数
    sTcZeroI_f        sZeroI;    // 零序电流超限判别参数
    sTcUnblnV_f        sUblV;    // 三相电压不平衡超限判别参数
    sTcUnblnI_f        sUblI;    // 三相电流不平衡超限判别参数
}sTcElecLimitPower_f, sTcAfn04f27_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn04f27(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 电气测量点功率因素越限值参数
 * 对应AFN : TC_AFN_04_SETP
 * 对应CMD : TCMD_AFN_4_F28_ELEC_LMIT_FACTR
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef struct
{
    float  fPara1;            // 总功率因数分段参数 1   (+)XX.XX
    float  fPara2;            // 总功率因数分段参数 2   (+)XX.XX
    float  fWarning;          // 总功率因数越限告警定值 (+)XX.XX
}sTcFactorLimit, sTcAfn04F28; // 电气测量点功率因数越限值参数数据单元格式  

// 封帧侧
#pragma pack(1)
typedef struct
{
    sTcFmt10_f  fPara1;      // 总功率因数分段参数 1
    sTcFmt10_f  fPara2;      // 总功率因数分段参数 2
    sTcFmt10_f  fWarning;    // 总功率因数越限告警定值
}sTcFactorLimit_f, sTcAfn04F28_f; // 电气测量点功率因数越限值参数数据单元格式  
#pragma pack()

// 转换函数
eTcErr etc_trans_afn04f28(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 电气测量点谐波畸变率越限定值
 * 对应AFN : TC_AFN_04_SETP
 * 对应CMD : TCMD_AFN_4_F29_ELEC_FIX_HARM
 * PN 类型 : 电气测量点号
{*///
// aberration 畸变
typedef struct
{
   float fTotal;              // 总畸变率越限定值
   float   fOdd;              // 奇次畸变率越限定值
   float  fEven;              // 偶次畸变率超限定值
}sTcAberLimit; 

// 用户侧
typedef struct
{
    sTcAberLimit      sVa;    // A相电压畸变率越限定值
    sTcAberLimit      sVb;    // B相电压畸变率越限定值
    sTcAberLimit      sVc;    // C相电压畸变率越限定值
    sTcAberLimit      sIa;    // A相电流畸变率越限定值
    sTcAberLimit      sIb;    // B相电流畸变率越限定值
    sTcAberLimit      sIc;    // C相电流畸变率越限定值
     
}sTcElecFixHarm, sTcAfn04F29; // 电气测量点功率因数越限值参数数据单元格式  

// 封帧侧
#pragma pack(1)
typedef struct
{
   sTcFmt10_f fTotal;             // 总畸变率越限定值
   sTcFmt10_f   fOdd;             // 奇次畸变率越限定值
   sTcFmt10_f  fEven;             // 偶次畸变率超限定值
}sTcAberLimit_f;

typedef struct
{
    sTcAberLimit_f      sVa;    // A相电压畸变率越限定值
    sTcAberLimit_f      sVb;    // B相电压畸变率越限定值
    sTcAberLimit_f      sVc;    // C相电压畸变率越限定值
    sTcAberLimit_f      sIa;    // A相电流畸变率越限定值
    sTcAberLimit_f      sIb;    // B相电流畸变率越限定值
    sTcAberLimit_f      sIc;    // C相电流畸变率越限定值
    
}sTcElecFixHarm_f, sTcAfn04F29_f; // 电气测量点功率因数越限值参数数据单元格式  
#pragma pack()

// 转换函数
eTcErr etc_trans_afn04f29(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 电气测量点闪变越限参数
 * 对应AFN : TC_AFN_04_SETP
 * 对应CMD : TCMD_AFN_4_F30_ELEC_FLASH
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef struct
{
    float    fLong;      // 短时闪变越限值  (+)XX.XX
    float   fShort;      // 长时闪变越限值  (+)XX.XX
}sTcElecFlash, sTcAfn04f30;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sTcFmt10_f    fLong;      // 短时闪变越限值
    sTcFmt10_f   fShort;      // 长时闪变越限值
}sTcElecFlash_f, sTcAfn04f30_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn04f30(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 非电气测量点配置参数
 * 对应AFN : TC_AFN_04_SETP
 * 对应CMD : TCMD_AFN_4_F33_NELC_MP_CFG
 * PN 类型 : 电气测量点号
{*///
///*} 

// 用户侧
typedef sTcElecMpCfg sTcNelcMpCfg;
typedef sTcAfn04f25  sTcAfn04f33;

// 封帧侧
//typedef sTcElecMpCfg_f sTcNelcMpCfg_f;

// 转换函数
eTcErr etc_trans_afn04f33(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 非电气测量点数据参数
 * 对应AFN : TC_AFN_04_SETP
 * 对应CMD : TCMD_AFN_4_F34_NELC_MP_PARA
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef enum
{
   TC_NELC_UNKOWN,
   TC_NELC_TEMP,       // 温度
   TC_NELC_FLOW,       // 流量
   TC_NELC_FV,         // 流速
   TC_NELC_PRESS,      // 压力
   TC_NELC_HUMI,       // 湿度
   TC_NELC_LIGHT,      // 照度
   TC_NELC_RV,         // 转速
   TC_NELC_420MA,      // 4~20MA

}eTcNelcType;

typedef struct
{
    eTcNelcType eType;           // 非电气量类型
    sTcDouble     sUp;           // 量程上限
    sTcDouble   sDown;           // 量程下限
}sTcNelcMpPara, sTcAfn04f34;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8       eType;            // 非电气量类型
    sTcFmt11_f    sUp;            // 量程上限
    sTcFmt11_f  sDown;            // 量程下限
}sTcNelcMpCfg_f, sTcAfn04f34_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn04f34(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 非电气测量点越限数据参数
 * 对应AFN : TC_AFN_04_SETP
 * 对应CMD : TCMD_AFN_4_F35_NELC_MP_LMIT
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef struct
{
    eTcNelcType eType;           // 非电气量类型
    sTcDouble    sUp;             // 越上限定值
    sTcDouble    sDown;           // 越下限定值

}sTcNelcMpLimit, sTcAfn04f35;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8       eType;            // 非电气量类型
    sTcFmt11_f    sUp;            // 越上限定值
    sTcFmt11_f  sDown;            // 越下限定值
}sTcNelcMpLimit_f, sTcAfn04f35_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn04f35(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 校时命令
 * 对应AFN : TC_AFN_04_SETP
 * 对应CMD : TCMD_AFN_5_F1_CHECK_TIME
 * PN 类型 : 电气测量点号
{*///

// 用户侧
// sTcYWMDhms
// 封帧侧
// sTcYWMDhms_f

// 转换函数
eTcErr etc_trans_afn05f1(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 临时冻结命令
 * 对应AFN : TC_AFN_05_CTRL
 * 对应CMD : TCMD_AFN_5_F2_FREZ_TEMP
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef struct
{
    UINT8         ucNum;    // 数据单元标识个数
    sTcmdPn   sCmdPn[1];    // ucNum 个数据单元标识
}sTcFrezTemp, sTcAfn05f2;

// 封帧侧
typedef struct
{
    UINT8         ucNum;     // 数据单元标识个数 DaDt
    sTcDaDt    sDaDt[1];  // ucNum 个DaDt
}sTcFrezTemp_f, sTcAfn05f2_f;

// 转换函数
eTcErr etc_trans_afn05f2(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 遥控跳闸
 * 对应AFN : TC_AFN_05_CTRL
 * 对应CMD : TCMD_AFN_5_F17_REMOTE_OFF
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef struct
{
    BOOL         bOff[8];    // 第1-8输出开关是否跳闸
    sTcYMDhm sTimeStart;    // 跳闸开始时间 
    sTcYMDhm   sTimeEnd;    // 跳闸结束时间 
}sTcRemoteOff, sTcAfn05f17;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8         bOff;      // 每一bit表示第1-8输出开关是否合上
    sTcYMDhm_f sTimeStart;  // 跳闸开始时间 
    sTcYMDhm_f   sTimeEnd;  // 跳闸结束时间   

}sTcRemoteOff_f, sTcAfn05f17_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn05f17(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 允许合闸
 * 对应AFN : TC_AFN_05_CTRL
 * 对应CMD : TCMD_AFN_5_F18_REMOTE_ON
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef struct
{
    BOOL         bOn[8];    // 第1-8输出开关是否跳闸
}sTcRemoteOn, sTcAfn05f18;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8         bOn;      // 每一bit表示第1-8输出开关是否合上
 
}sTcRemoteOn_f, sTcAfn05f18_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn05f18(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 能效模型有效
 * 对应AFN : TC_AFN_05_CTRL
 * 对应CMD : TCMD_AFN_5_F5_NX_MODEL_ACT
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    UINT8        ucID;       // 第N个能效模式编号
    sTcYWMDhms  sTime;       // 起始时间:年月日时分秒
}sTcNxModelOne;

typedef struct
{
    UINT8              ucN;  // 能效模型个数
    sTcNxModelOne  sOne[1];  // 第n个能效模型 一共N个能效模型

}sTcNxModelAct, sTcAfn05f5;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8         ucID;       // 第N个能效模式编号
    sTcYWMDhms_f  sTime;      // 起始时间:年月日时分秒
}sTcNxModelOne_f;

typedef struct
{
    UINT8              ucN;  // 能效模型个数
    sTcNxModelOne_f   sOne[1];  // 第n个能效模型 一共N个能效模型
}sTcNxModelAct_f, sTcAfn05f5_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn05f5(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 能效模型清除
 * 对应AFN : TC_AFN_05_CTRL
 * 对应CMD : TCMD_AFN_5_F6_NX_MODEL_CLR
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    UINT8            ucN;  // 能效模型个数
    UINT8        ucID[1];  // 第n个能效模型编号
}sTcNxModelClr, sTcAfn05f6;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8            ucN;  // 能效模型个数
    UINT8        ucID[1];  // 第n个能效模型编号
}sTcNxModelClr_f, sTcAfn05f6_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn05f6(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 需求响应信息有效
 * 对应AFN : TC_AFN_05_CTRL
 * 对应CMD : TCMD_AFN_5_F7_RQ_RESPN_ACT
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    UINT8            ucN;  // 需求响应信息个数n
    UINT8        ucID[1];  // 第n个需求响应信息编号
}sTcRqRespnAct, sTcAfn05f19;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8            ucN;  // 需求响应信息个数n
    UINT8        ucID[1];  // 第n个需求响应信息编号
}sTcRqRespnAct_f, sTcAfn05f19_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn05f7(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 需求响应信息清除
 * 对应AFN : TC_AFN_05_CTRL
 * 对应CMD : TCMD_AFN_5_F8_RQ_RESPN_CLT
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    UINT8            ucN;  // 需求响应信息个数n
    UINT8        ucID[1];  // 第n个需求响应信息编号
}sTcRqRespnClr, sTcAfn05f20;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8            ucN;  // 需求响应信息个数n
    UINT8        ucID[1];  // 第n个需求响应信息编号
}sTcRqRespnClr_f, sTcAfn05f20_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn05f8(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 设备支持的事件记录(询问没有参数 应答本结构)
 * 对应AFN : TC_AFN_10_GETP
 * 对应CMD : TCMD_AFN_A_F11_TML_SPRT_EVENT
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
   BOOL  bSuprt[TC_ERC_NUM_MAX];    // 对各事件是否支持
   
}sTcSuptEvent, sTcAfn10f11;

// 封帧侧
#pragma pack(1)
typedef struct
{
   UINT8   ucEvent[8];              // D0~D63按顺序对应表示事件代码ERC1~ERC64所定义的事件
   
}sTcSuptEvent_f, sTcAfn10f11_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn10f11(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 已配置电气测量点信息(询问没有参数 应答本结构)
 * 对应AFN : TC_AFN_10_GETP
 * 对应CMD : TCMD_AFN_A_F12_ELEC_MP_INFO
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    UINT8    ucSprt;          // 支持的测量点信息点组数据n (1 < n < 255)
    UINT16    usNum;          // 已经配置的Pn个数
    UINT16  usPn[1];          // 配置的具体pn
}sTcElecMpInfo, sTcAfn10f12;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8   ucSprt;           // 支持的测量点信息点组数据n (1 < n < 255)
    UINT8   ucSDa2;           // 本帧上报的起始信息点组DA2 (1 < m < 255)
    UINT8   ucK;              // 本帧上报的个数
    UINT8   ucDa1[1];         // 第i 个信息点组DA2所对应的DA1（i=m~m+k-1） 
}sTcElecMpInfo_f, sTcAfn10f12_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn10f12(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 已配置非电气测量点信息(询问没有参数 应答本结构)
 * 对应AFN : TC_AFN_10_GETP
 * 对应CMD : TCMD_AFN_A_F13_NELC_MP_INFO
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    UINT8    ucSprt;          // 支持的测量点信息点组数据n (1 < n < 255)
    UINT16    usNum;          // 已经配置的Pn个数
    UINT16  usPn[1];          // 配置的具体pn
}sTcNelcMpInfo, sTcAfn10f13;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8   ucSprt;           // 支持的测量点信息点组数据n (1 < n < 255)
    UINT8   ucSDa2;           // 本帧上报的起始信息点组DA2 (1 < m < 255)
    UINT8   ucK;              // 本帧上报的个数
    UINT8   ucDa1[1];         // 第i 个信息点组DA2所对应的DA1（i=m~m+k-1） 
}sTcNelcMpInfo_f, sTcAfn10f13_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn10f13(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 接入端口支持的通信协议信息(询问没有参数 应答本结构)
 * 对应AFN : TC_AFN_10_GETP
 * 对应CMD : TCMD_AFN_A_F14_TML_PROTO_SPRT
 * PN 类型 : p0
{*///

#define TC_PROTO_NAME_LEN  (16)
typedef struct
{
    eTcAcsProto eType;
    UINT8       strName[TC_PROTO_NAME_LEN];    
}sTcProto;

// 用户侧
typedef struct
{
    UINT8        ucN;               // 支持的通信协议数量n  当n=0时，表示接入端口不支持任何通信协议
    UINT8        ucM;               // 本帧上报的起始序号m（m≥1）
    UINT8        ucK;               // 本帧上报的个数k
    sTcProto sOne[1];               // 一共K个 (m~m+k-1)
}sTcTmlProtoSprt, sTcAfn10f14;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8      eType;
    UINT8      strName[TC_PROTO_NAME_LEN];    
}sTcProto_f;

typedef struct
{
    UINT8         ucN;               // 支持的通信协议数量n 当n=0时，表示接入端口不支持任何通信协议
    UINT8         ucM;               // 本帧上报的起始序号m（m≥1）
    UINT8         ucK;               // 本帧上报的个数k
    sTcProto_f sOne[1];               // 一共K个 (m~m+k-1)
}sTcTmlProtoSprt_f, sTcAfn10f14_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn10f14(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 


// 
/*******************************************
 * 数据名称: 软硬件版本信息定义
 * 命令说明: 对应于附录G
 *
{*///

// 用户侧
typedef struct
{
    UINT8    strFactory[4];       // 厂商代号
    UINT8      strDevId[4];       // 设备∕模块代码 
    UINT8       strAddr[16];      // 设备∕模块编号（地址）  16位数字
    UINT8       strHard[4];       // 硬件版本号
    sTcYMDhm     sTimeHard;       // 硬件版本发布时间 (分时日月年)
    UINT8       strSoft[4];       // 软件版本号
    sTcYMDhm     sTimeSoft;       // 软件版本发布时间 (分时日月年)
    UINT8    strVolume[12];       // 配置容量信息码
    UINT8     strProto[16];       // 上行通信协议版本号
}sTcVersion;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8    strFactory[4];       // 厂商代号
    UINT8      strDevId[4];       // 设备∕模块代码 
    UINT8       strAddr[8];       // 设备∕模块编号（地址） BCD 16位数字
    UINT8       strHard[4];       // 硬件版本号
    sTcYMDhm_f   sTimeHard;       // 硬件版本发布时间 (分时日月年)
    UINT8       strSoft[4];       // 软件版本号
    sTcYMDhm_f   sTimeSoft;       // 软件版本发布时间 (分时日月年)
    UINT8    strVolume[12];       // 配置容量信息码
    UINT8     strProto[16];       // 上行通信协议版本号
}sTcVersion_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_version(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 终端内各智能模块的软硬件版本信息
 * 对应AFN : TC_AFN_10_GETP
 * 对应CMD : TCMD_AFN_A_F15_TML_MODEL_VERSION
 * 命令说明: 询问没有参数 应答本结构
 * PN 类型 : p0
{*///

typedef struct
{
    UINT8            ucID;      // 智能模块编号
    sTcVersion   sVersion;      // 智能模块软硬件版本信息
}sTcModelVerion;

// 用户侧
typedef struct
{
    UINT8              ucN;      // 智能模块数量n 当n=0时，表示监测终端内无智能模块，表 47所示的数据单元也就仅有一字节。
    UINT8              ucM;      // 本帧上报的起始序号m（m≥1）
    UINT8              ucK;      // 本帧上报的个数k
    sTcModelVerion sOne[1];
}sTcTmlModelVersion, sTcAfn10f15;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8              ucID;      // 智能模块编号
    sTcVersion_f   sVersion;      // 智能模块软硬件版本信息
}sTcModelVerion_f;

typedef struct
{
    UINT8                ucN;     // 智能模块数量n 当n=0时，表示监测终端内无智能模块，表 47所示的数据单元也就仅有一字节。
    UINT8                ucM;     // 本帧上报的起始序号m（m≥1）
    UINT8                ucK;     // 本帧上报的个数k
    sTcModelVerion_f sOne[1];
}sTcTmlModelVersion_f, sTcAfn10f15_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn10f15(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 终端软硬件版本信息
 * 对应AFN : TC_AFN_10_GETP
 * 对应CMD : TCMD_AFN_A_F16_TML_VERSION
 * 命令说明: 询问没有参数 应答本结构
 * PN 类型 : p0
{*///
// 用户侧
typedef sTcVersion sTcTmlVersion;

// 封帧侧
// typedef sTcVersion_f sTcTmlVersion_f;

// 转换函数
eTcErr etc_trans_afn10f16(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 


/*******************************************
 * 数据名称: 日历时钟(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F1_CLOCK
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sTcUerClock sTcClock, sTcAfn13f1;

// 封帧侧
#pragma pack(1)
typedef sTcUerClock_f sTcClock_f, sTcAfn13f1_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn13f1(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 参数状态标志(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F2_PARA_STATE
 * PN 类型 : p0/监测终端号
{*///

// 目前可以设置的参数个数为20(TCMD_AFN_4_F1_CON_IP_PORT  到 TCMD_AFN_4_F49_FREZ_TASK_PARA)
#define TC_SET_NUM_MAX  (20)     

// 用户侧
typedef struct
{
    UINT8    ucNum;  // 已经设置的个数
    eTcmd  eCmd[1];  // 已经设置的参数类型
}sTcParaState, sTcAfn13f2;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8  ucSet[31];
}sTcParaState_f, sTcAfn13f2_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn13f2(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 重要事件计数器当前值(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F3_EVENT_1
 * PN 类型 : p0/监测终端号
{*///

// 用户侧
// UINT16 usEc1

// 封帧侧
// UINT16 usEc1_f

// 转换函数
eTcErr etc_trans_afn13f3(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 一般事件计数器当前值(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F4_EVENT_2
 * PN 类型 : p0/监测终端号
{*///

// 用户侧
// UINT16 usEc2

// 封帧侧
// UINT16 ucEc2_f

// 转换函数
eTcErr etc_trans_afn13f4(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 事件状态标志
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F5_EVENT_STATE
 * 结构类型: 命令无参数, 应答为本结构
 * PN 类型 : P0
{*///
// 用户侧
typedef struct
{
    BOOL bHave[TC_ERC_NUM_MAX];      // 真:有或支持该事件 假: 无或不支持该事件 
}sTcEventState, sTcAfn13f5;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8   ucHave[8];               // 每个bit代表是否有对应的事件发生
}sTcEventState_f, sTcAfn13f5_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn13f5(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 上电次数(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F6_POWR_TIMES
 * PN 类型 : p0/监测终端号
{*///

#define TC_POWR_TIMES_MAX (999999)
// 用户侧
typedef struct
{
    UINT32 ulTimes;    //  (0-999999)
}sTcPowerTimes, sTcAfn13f6;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8   ucBcd[3];       // BCD格式
}sTcPowerTimes_f, sTcAfn13f6_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn13f6(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 状态量及变位标志(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F9_STATE
 * PN 类型 : p0/监测终端号
{*///

// 用户侧
typedef struct
{
    BOOL bSt[8];   // 表示1-8路状态量的状态ST 真:合, 假:分          
    BOOL bCd[8];   // 表示1-8路状态量的变化CD 
                   // 真:自前次遥信传送后至少有一次状态变化
                   // 假:自前次遥信传送后没有状态变化
}sTcState, sTcAfn13f9;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8  ucSt8;
    UINT8  ucCd8;
}sTcState_f, sTcAfn13f9_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn13f9(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 总有功功率(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F17_POWR_HAVE_T
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    float fXX_XXXX;              //  总有功功率(Kw) (+)XX.XXXX
}sTcPowerHaveT, sTcAfn13f17;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sTcFmt06_f fXX_XXXX;       
}sTcPowerHaveT_f, sTcAfn13f17_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn13f17(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 总无功功率(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F18_POWR_NONE_T
 * PN 类型 : p0/监测终端号
{*///

// 用户侧
typedef struct
{
    float fXX_XXXX;             //  总无功功率(Kw) (+)XX.XXXX
}sTcPowerNoneT, sTcAfn13f18;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sTcFmt06_f fXX_XXXX;       
}sTcPowerNoneT_f, sTcAfn13f18_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn13f18(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 日最大需量发生时间(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F19_DEMD_TIME_D
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef struct
{
    float    fXX_XXXX;           // 最大需量 (+/-)XX.XXXX
    sTcYMDhm sTime;              //  日最大需量发生时间 年月日时分
}sTcDemandMaxD, sTcAfn13f19;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sTcFmt06_f fXX_XXXX;  
    sTcYMDhm_f sTime;             //  日最大需量发生时间 年月日时分
}sTcDemandMaxD_f, sTcAfn13f19_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn13f19(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 月最大需量及发生时间(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F20_DEMD_TIME_M
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcDemandMaxD sTcDemandMaxM;

// 转换函数
// 同 eTcErr etc_trans_afn13f19(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 总功率因数(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F21_FACTR_T
 * PN 类型 : p0/监测终端号
{*///

// 用户侧
typedef struct
{
    float fXX_XX;             //  总功率因数 (+)XX.XX
}sTcFactorT, sTcAfn13f21;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sTcFmt10_f fXX_XX;       
}sTcFactorT_f, sTcAfn13f21_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn13f21(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相功率因素(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F22_FACTR_A
 * PN 类型 : p0/监测终端号
{*///

// 用户侧
typedef struct
{
    float fXX_XX;             //  A相功率因素 (+)XX.XX
}sTcFactorA, sTcAfn13f28;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sTcFmt10_f fXX_XX;       
}sTcFactorA_f, sTcAfn13f28_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn13f22(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相功率因素(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F23_FACTR_B
 * PN 类型 : p0/监测终端号
{*///

// 用户侧
typedef struct
{
    float fXX_XX;             //  B相功率因素 (+)XX.XX
}sTcFactorB, sTcAfn13f29;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sTcFmt10_f fXX_XX;       
}sTcFactorB_f, sTcAfn13f29_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn13f23(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相功率因素(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F24_FACTR_C
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    float fXX_XX;             //  C相功率因素 (+)XX.XX
}sTcFactorC, sTcAfn13f30;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sTcFmt10_f fXX_XX;       
}sTcFactorC_f, sTcAfn13f30_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn13f24(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相有功功率(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F25_POWR_HAVE_A
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    float fXX_XX;             //  A相有功功率 (+)XX.XX
}sTcPowerHaveA, sTcAfn13f25;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sTcFmt10_f fXX_XX;       
}sTcPowerHaveA_f, sTcAfn13f25_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn13f25(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相有功功率(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F26_POWR_HAVE_B
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sTcPowerHaveA sTcPowerHaveB;

// 封帧侧
// typdef sTcPowerHaveA_f sTcPowerHaveB_f;

// 转换函数
eTcErr etc_trans_afn13f26(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相有功功率(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F27_POWR_HAVE_C
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sTcPowerHaveA sTcPowerHaveC;

// 封帧侧
// typdef sTcPowerHaveA_f sTcPowerHaveC_f;

// 转换函数
eTcErr etc_trans_afn13f27(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相无功功率(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F28_POWR_NONE_A
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sTcPowerHaveA sTcPowerNoneA;

// 封帧侧
// typdef sTcPowerHaveA_f sTcPowerNoneA_f;

// 转换函数
eTcErr etc_trans_afn13f28(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相无功功率(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F29_POWR_NONE_B
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sTcPowerHaveA sTcPowerNoneB;

// 封帧侧
// typdef sTcPowerHaveA_f sTcPowerNoneB_f;

// 转换函数
eTcErr etc_trans_afn13f29(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相无功功率(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F30_POWR_NONE_C
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sTcPowerHaveA sTcPowerNoneC;

// 封帧侧
// typdef sTcPowerHaveA_f sTcPowerNoneC_f;

// 转换函数
eTcErr etc_trans_afn13f30(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: （正向）有功总电能示数(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F33_POWR_HAVE_FRTH
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    double dXXXXXX_XXXX;           // 电能示数    (+)XXXXXX.XXXX    
}sTcPowerHaveFrth, sTcAfn13f33;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sTcFmt04_f dXXXXXX_XXXX;
}sTcPowerHaveFrth_f, sTcAfn13f33_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn13f33(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: （反向）有功总电能示数(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F34_POWR_HAVE_BACK
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sTcPowerHaveFrth sTcPowerHaveBack;

// 封帧侧
// typdef sTcPowerHaveFrth_f sTcPowerHaveBack_f;

// 转换函数
eTcErr etc_trans_afn13f34(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: （正向）无功总电能示数(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F35_POWR_NONE_FRTH
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    double dXXXXXX_XX;           // 电能示数    (+)XXXXXX.XX    
}sTcPowerNoneFrth, sTcAfn13f35;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sTcFmt05_f dXXXXXX_XX;
}sTcPowerNoneFrth_f, sTcAfn13f35_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn13f35(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: （反向）有功总电能示数(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F36_POWR_NONE_BACK
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sTcPowerNoneFrth sTcPowerNoneBack;

// 封帧侧
// typdef sTcPowerNoneFrth_f sTcPowerNoneBack_f;

// 转换函数
eTcErr etc_trans_afn13f36(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相电压(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F41_VOLT_A
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    float fXXX_X;           // 电压示数 (V)   (+)XXX.X    
}sTcVoltA, sTcAfn13f41;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sTcFmt08_f fXXX_X;
}sTcVoltA_f, sTcAfn13f41_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn13f41(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称:  B相电压(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F58_VOLT_B
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sTcVoltA sTcVoltB;

// 封帧侧
//typedef sTcVoltA_f sTcVoltB_f;

// 转换函数
eTcErr etc_trans_afn13f42(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相电压(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F43_VOLT_C
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sTcVoltA sTcVoltC;

// 封帧侧
//typedef sTcVoltA_f sTcVoltC_f;

// 转换函数
eTcErr etc_trans_afn13f43(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相电压相位角(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F44_VANGL_A
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    float fsXXX_X;           // 电压示数 (度)   (+/-)XXX.X    
}sTcVAngleA, sTcAfn13f44;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sTcFmt07_f fsXXX_X;
}sTcVAngleA_f, sTcAfn13f44_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn13f44(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称:  B相电压相位角(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F45_VANGL_B
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sTcVAngleA sTcVAngleB;

// 封帧侧
// typedef sTcVAngleA_f sTcVAngleB_f;

// 转换函数
eTcErr etc_trans_afn13f45(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相电压相位角(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F46_VANGL_C
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sTcVAngleA sTcVAngleC;

// 封帧侧
// typedef sTcVAngleA_f sTcVAngleC_f;

// 转换函数
eTcErr etc_trans_afn13f46(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 电压不平衡度(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F47_VOLT_UBL
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sTcFactorT sTcVoltUbl;

// 封帧侧
// typedef sTcFactorT_f sTcVoltUbl_f;

// 转换函数
eTcErr etc_trans_afn13f47(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 周波(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F48_CIRCLE_V
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sTcAfn13f25 sTcVCircle;

// 封帧侧

// 转换函数
eTcErr etc_trans_afn13f48(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相电流(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F49_ELEC_A
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    float fsXXX_XXX;        //  (A) (+/-)XXX.XXX  
}sTcElecA, sTcAfn13f49;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sTcFmt09_f fsXXX_XXX;
}sTcElecA_f, sTcAfn13f49_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn13f49(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相电流(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F50_ELEC_B
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sTcElecA sTcElecB;

// 封帧侧
// 转换函数
eTcErr etc_trans_afn13f50(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相电流(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F51_ELEC_C
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sTcElecA sTcElecC;

// 封帧侧
// 转换函数
eTcErr etc_trans_afn13f51(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 中性线电流(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F52_ELEC_M
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sTcElecA sTcElecM;

// 封帧侧
// 转换函数
eTcErr etc_trans_afn13f52(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相电流相位角(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F53_EANGL_A
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sTcAfn13f44 sTcEAngleA;

// 封帧侧
// 转换函数
eTcErr etc_trans_afn13f53(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相电流相位角(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F54_EANGL_B
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sTcAfn13f44 sTcEAngleB;

// 封帧侧
// 转换函数
eTcErr etc_trans_afn13f54(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相电流相位角(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F55_EANGL_C
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sTcAfn13f44 sTcEAngleC;

// 封帧侧
// 转换函数
eTcErr etc_trans_afn13f55(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 电流不平衡度(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F56_ELEC_UBL
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sTcAfn13f44 sTcElecUbl;

// 封帧侧
// 转换函数
eTcErr etc_trans_afn13f56(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 日A相电压极大值和发生时间(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F57_VDMAX_A_TIME
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    float fXXX_X;           // 电压示数 (V)   (+)XXX.X    
    sTcYMDhm sTime;         // 发生时间 年月日时分
    
}sTcVdMaxTimeA, sTcAfn13f57;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sTcFmt08_f fXXX_X;
    sTcFmt02_f sTime;       
}sTcVdMaxTimeA_f, sTcAfn13f57_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn13f57(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 日B相电压极大值和发生时间(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F58_VDMAX_B_TIME
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sTcVdMaxTimeA sTcVdMaxTimeB;

// 封帧侧

// 转换函数
// 同 eTcErr etc_trans_afn13f57(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 日C相电压极大值和发生时间(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F59_VDMAX_C_TIME
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sTcVdMaxTimeA sTcVdMaxTimeC;

// 封帧侧

// 转换函数
// 同 eTcErr etc_trans_afn13f57(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 日A相电流极大值和发生时间(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F60_IDMAX_A_TIME
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    float fsXXX_XXX;        // 电流极大值 (A) (+/-)XXX.XXX  
    sTcYMDhm sTime;         // 发生时间 年月日时分
    
}sTcIdMaxTimeA, sTcAfn13f60;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sTcFmt09_f fsXXX_XXX;
    sTcFmt02_f sTime;       
}sTcIdMaxTimeA_f, sTcAfn13f60_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn13f60(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 日B相电流极大值和发生时间(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F61_IDMAX_B_TIME
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sTcIdMaxTimeA sTcIdMaxTimeB;

// 封帧侧

// 转换函数
// 同 eTcErr etc_trans_afn13f60(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 日C相电流极大值和发生时间(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F62_IDMAX_C_TIME
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sTcIdMaxTimeA sTcIdMaxTimeC;

// 封帧侧

// 转换函数
// 同 eTcErr etc_trans_afn13f60(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相电压越上上限日累计时间(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F65_VDPP_TIME_A
 * PN 类型 : 电气测量点号
{*///
#define TC_BCD_XXXX_MAX  (9999)

// 用户侧
typedef struct
{
    UINT16    usMinutes;       // 时间 分钟 最大值 TC_BCD_XXXX_MAX
    
}sTcVDppTimeA, sTcAfn13f97;  

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8 ucBCD[2];
    
}sTcVDppTimeA_f, sTcAfn13f97_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn13f65(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相电压越上上限日累计时间(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F66_VDPP_TIME_B
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcVDppTimeA sTcVDppTimeB;
// 转换函数
// 同 eTcErr etc_trans_afn13f65(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相电压越上上限日累计时间(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F67_VDPP_TIME_C
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcVDppTimeA sTcVDppTimeC;
// 转换函数
// 同 eTcErr etc_trans_afn13f65(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相电压越下下限日累计时间(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F68_VDNN_TIME_A
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcVDppTimeA sTcVDnnTimeA;
// 转换函数
// 同 eTcErr etc_trans_afn13f65(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相电压越下下限日累计时间(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F69_VDNN_TIME_B
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcVDppTimeA sTcVDnnTimeB;
// 转换函数
// 同 eTcErr etc_trans_afn13f65(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相电压越下下限日累计时间(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F70_VDNN_TIME_C
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcVDppTimeA sTcVDnnTimeC;
// 转换函数
// eTcErr etc_trans_afn13f65(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相电压越上上限月累计时间(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F73_VMPP_TIME_A
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcPowerTimes sTcVMppTimeA;
// 转换函数
// 同 eTcErr etc_trans_afn13f6(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相电压越上上限月累计时间(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F74_VMPP_TIME_B
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcPowerTimes sTcVMppTimeB;
// 转换函数
// 同 eTcErr etc_trans_afn13f6(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相电压越上上限月累计时间(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F75_VMPP_TIME_C
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcPowerTimes sTcVMppTimeC;
// 转换函数
// 同 eTcErr etc_trans_afn13f6(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相电压越下下限月累计时间(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F76_VMNN_TIME_A
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcPowerTimes sTcVMnnTimeA;
// 转换函数
// 同 eTcErr etc_trans_afn13f6(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相电压越下下限月累计时间(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F77_VMNN_TIME_B
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcPowerTimes sTcVMnnTimeB;
// 转换函数
// 同 eTcErr etc_trans_afn13f6(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相电压越下下限月累计时间(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F78_VMNN_TIME_C
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcPowerTimes sTcVMnnTimeC;
// 转换函数
// 同 eTcErr etc_trans_afn13f6(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相电压总畸变率(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F81_VABR_TOTL_A
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcAfn13f21 sTcVabrTotalA;
// 转换函数
// 同 eTcErr etc_trans_afn13f21(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相电压总畸变率(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F82_VABR_TOTL_B
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcAfn13f21 sTcVabrTotalB;
// 转换函数
// 同 eTcErr etc_trans_afn13f21(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相电压总畸变率(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F83_VABR_TOTL_C
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcAfn13f21 sTcVabrTotalC;
// 转换函数
// 同 eTcErr etc_trans_afn13f21(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相电流总畸变率(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F84_EABR_TOTL_A
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcAfn13f21 sTcEabrTotalA;
// 转换函数
// 同 eTcErr etc_trans_afn13f21(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相电流总畸变率(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F85_EABR_TOTL_B
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcAfn13f21 sTcEabrTotalB;
// 转换函数
// 同 eTcErr etc_trans_afn13f21(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相电流总畸变率(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F86_EABR_TOTL_C
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcAfn13f21 sTcEabrTotalC;
// 转换函数
// 同 eTcErr etc_trans_afn13f21(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相电压奇次畸变率(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F89_VABR_OOD_A
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcAfn13f21 sTcVabrOddA;
// 转换函数
// 同 eTcErr etc_trans_afn13f21(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相电压偶次畸变率(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F90_VABR_EVN_A
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcAfn13f21 sTcVabrEvnA;
// 转换函数
// 同 eTcErr etc_trans_afn13f21(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相电压奇次畸变率(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F91_VABR_OOD_B
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcAfn13f21 sTcVabrOddB;
// 转换函数
// 同 eTcErr etc_trans_afn13f21(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相电压偶次畸变率(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F92_VABR_EVN_B
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcAfn13f21 sTcVabrEvnB;
// 转换函数
// 同 eTcErr etc_trans_afn13f21(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相电压奇次畸变率(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F93_VABR_OOD_C
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcAfn13f21 sTcVabrOddC;
// 转换函数
// 同 eTcErr etc_trans_afn13f21(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相电压偶次畸变率(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F94_VABR_EVN_C
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcAfn13f21 sTcVabrEvnC;
// 转换函数
// 同 eTcErr etc_trans_afn13f21(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相电压奇次畸变率(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F97_EABR_OOD_A
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcAfn13f21 sTcEabrOddA;
// 转换函数
// 同 eTcErr etc_trans_afn13f21(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相电流偶次畸变率(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F98_EABR_EVN_A
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcAfn13f21 sTcEabrEvnA;
// 转换函数
// 同 eTcErr etc_trans_afn13f21(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相电流奇次畸变率(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F99_EABR_OOD_B
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcAfn13f21 sTcEabrOddB;
// 转换函数
// 同 eTcErr etc_trans_afn13f21(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相电流偶次畸变率(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F100_EABR_EVN_B
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcAfn13f21 sTcEabrEvnB;
// 转换函数
// 同 eTcErr etc_trans_afn13f21(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相电流奇次畸变率(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F101_EABR_OOD_C
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcAfn13f21 sTcEabrOddC;
// 转换函数
// 同 eTcErr etc_trans_afn13f21(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相电流偶次畸变率(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F102_EABR_EVN_C
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcAfn13f21 sTcEabrEvnC;
// 转换函数
// 同 eTcErr etc_trans_afn13f21(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 总基波有功功率(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F105_TFW_HAVE
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sTcAfn13f17 sTcTfwHave;   // (Total Fundamental Wave)

// 封帧侧
// 转换函数
// 同 eTcErr etc_trans_afn13f17(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);

///*} 

/*******************************************
 * 数据名称: 总基波无功功率(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F106_TFW_NONE
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sTcAfn13f17 sTcTfwNone;   // (Total Fundamental Wave)

// 封帧侧
// 转换函数
// 同 eTcErr etc_trans_afn13f17(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 总谐波有功功率(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F107_THW_HAVE
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sTcAfn13f17 sTcThwHave;   // (Total Harmonic Wave)

// 封帧侧
// 转换函数
// 同 eTcErr etc_trans_afn13f17(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 总基波无功功率(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F108_THW_NONE
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef sTcAfn13f17 sTcThwNone;   // (Total Harmonic Wave)

// 封帧侧
// 转换函数
// 同 eTcErr etc_trans_afn13f17(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相N次谐波电压(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F113_HARM_VOLT_A
 * PN 类型 : 电气测量点号
{*///

#define TC_HARM_TIMES_MAX      (19) // 谐波次数最大值

// 用户侧
typedef struct
{
    UINT8        ucN;          // 谐波次数
    float    fXXX_X[1];        // 2 ~ n次谐波  (数组元素个数为 ucN - 1)
}sTcHarmVoltA, sTcAfn13f113;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8             ucN;      // 谐波次数
    sTcFmt08_f  fXXX_X[1];      // 2 ~ n次谐波  (数组元素个数为 ucN - 1)
}sTcHarmVoltA_f, sTcAfn13f113_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn13f113(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相N次谐波电压(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F114_HARM_VOLT_B
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcHarmVoltA sTcHarmVoltB;
// 转换函数
// 同 eTcErr etc_trans_afn13f113(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相N次谐波电压(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F115_HARM_VOLT_C
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcHarmVoltA sTcHarmVoltC;
// 转换函数
// 同 eTcErr etc_trans_afn13f113(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相N次谐波电流(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F116_HARM_ELEC_A
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef struct
{
    UINT8             ucN;          // 谐波次数
    float    fsXXX_XXX[1];          // 2 ~ n次谐波  (数组元素个数为 ucN - 1)
}sTcHarmElecA, sTcAfn13f116;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8                ucN;      // 谐波次数
    sTcFmt09_f  fsXXX_XXX[1];      // 2 ~ n次谐波  (数组元素个数为 ucN - 1)
}sTcHarmElecA_f, sTcAfn13f116_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn13f116(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相N次谐波电流(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F117_HARM_ELEC_B
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcHarmElecA sTcHarmElecB;

// 转换函数
// 同 eTcErr etc_trans_afn13f116(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相N次谐波电流(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F118_HARM_ELEC_C
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcHarmElecA sTcHarmElecC;

// 转换函数
// 同 eTcErr etc_trans_afn13f116(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相N次谐波电压含有率(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F121_HARM_VINC_A
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef struct
{
    UINT8             ucN;          // 谐波次数
    float       fXX_XX[1];          // 2 ~ n次谐波含有率  (数组元素个数为 ucN - 1)
}sTcHarmVincA, sTcAfn13f121;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8              ucN;      // 谐波次数
    sTcFmt10_f   fXX_XX[1];      // 2 ~ n次谐波含有率  (数组元素个数为 ucN - 1)
}sTcHarmVincA_f, sTcAfn13f121_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn13f121(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相N次谐波电压含有率(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F122_HARM_VINC_B
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcHarmVincA sTcHarmVincB;

// 转换函数
// 同 eTcErr etc_trans_afn13f121(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相N次谐波电压含有率(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F123_HARM_VINC_C
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcHarmVincA sTcHarmVincC;

// 转换函数
// 同 eTcErr etc_trans_afn13f121(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相N次谐波电流含有率(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F124_HARM_EINC_A
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcHarmVincA sTcHarmEincA;

// 转换函数
// 同 eTcErr etc_trans_afn13f121(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相N次谐波电流含有率(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F125_HARM_EINC_B
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcHarmVincA sTcHarmEincB;

// 转换函数
// 同 eTcErr etc_trans_afn13f121(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相N次谐波电流含有率(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F126_HARM_EINC_C
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcHarmVincA sTcHarmEincC;

// 转换函数
// 同 eTcErr etc_trans_afn13f121(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相短时闪变(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F129_FLS_SHRT_A
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcAfn13f21 sTcFlashShortA;
// 转换函数
// 同 eTcErr etc_trans_afn13f21(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相短时闪变(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F130_FLS_SHRT_B
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcAfn13f21 sTcFlashShortB;
// 转换函数
// 同 eTcErr etc_trans_afn13f21(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相短时闪变(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F131_FLS_SHRT_C
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcAfn13f21 sTcFlashShortC;
// 转换函数
// 同 eTcErr etc_trans_afn13f21(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: A相长时闪变(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F132_FLS_LONG_A
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcAfn13f21 sTcFlashLongA;
// 转换函数
// 同 eTcErr etc_trans_afn13f21(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: B相长时闪变(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F133_FLS_LONG_B
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcAfn13f21 sTcFlashLongB;
// 转换函数
// 同 eTcErr etc_trans_afn13f21(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: C相长时闪变(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F134_FLS_LONG_C
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef sTcAfn13f21 sTcFlashLongC;
// 转换函数
// 同 eTcErr etc_trans_afn13f21(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 非电气量(应答格式)
 * 对应AFN : TC_AFN_13_ASKR
 * 对应CMD : TCMD_AFN_D_F137_NELC_VALUE
 * PN 类型 : 电气测量点号
{*///
// 用户侧
typedef struct
{
    eTcNelcType   eType;           // 非电气量类型
    sTcDouble   sDouble;           // 非电气量类型 数值
}sTcNelcValue, sTcAfn13f137;

// 封帧侧
#pragma pack(1)
typedef struct
{
    UINT8         eType;       // 非电气量类型
    sTcFmt11_f   sDouble;      // 非电气量类型  数值
}sTcNelcValue_f, sTcAfn13f137_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn13f137(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 请求（定时上报）冻结数据任务(命令参数)
 * 对应AFN : TC_AFN_12_ASKT
 * 对应CMD : TCMD_AFN_C_F9_FREZ_AUTO
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef struct
{
    sTcYMDhm   sTs;    // 请求冻结数据任务中的数据的起始时间ts：分时日月年
    sTcYMDhm   sTe;    // 请求冻结数据任务中的数据的结束时间te：分时日月年
}sTcFrezAutoQ, sTcAfn12f9;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sTcFmt02_f           sTs;         // 请求冻结数据任务中的数据的起始时间ts：分时日月年
    sTcFmt02_f           sTe;         // 请求冻结数据任务中的数据的结束时间te：分时日月年
}sTcFrezAutoQ_f, sTcAfn12f9_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn12f9_m2s(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * 数据名称: 请求（定时上报）冻结数据任务(应答格式)
 * 对应AFN : TC_AFN_12_ASKT
 * 对应CMD : TCMD_AFN_C_F9_FREZ_AUTO
 * PN 类型 : p0/监测终端号
{*///
// 用户侧
typedef union
{
    // TCMD_AFN_D_F1_CLOCK
    sTcUerClock           sUerClock;
    
    // TCMD_AFN_D_F2_PARA_STATE
    // 参数状态标志
    sTcParaState          sParaState;       

    // TCMD_AFN_D_F3_EVENT_1
    // 重要事件计数器当前值
    UINT16                usEc1;            

    // TCMD_AFN_D_F4_EVENT_2
    // 一般事件计数器当前值
    UINT16                usEc2;           

    // TCMD_AFN_D_F5_EVENT_STATE
    // 事件状态标志
    sTcEventState         sEventState;      

    // TCMD_AFN_D_F6_POWR_TIMES
    sTcPowerTimes         sPowerTimes;

    // TCMD_AFN_D_F9_STATE 
    // 状态量及变位标志
    sTcState              sState;           
    
    // TCMD_AFN_D_F17_POWR_HAVE_T  
    // 总有功功率
    sTcPowerHaveT         sPowerHaveT;
    
    // TCMD_AFN_D_F18_POWR_NONE_T         
    // 总无功功率
    sTcPowerNoneT         sPowerNoneT;      

    // TCMD_AFN_D_F19_DEMD_TIME_D           
    // 日最大需量发生时间
    sTcDemandMaxD         sDemandMaxD;

    // TCMD_AFN_D_F20_DEMD_TIME_M            
    // 月最大需量及发生时间
    sTcDemandMaxM         sDemandMaxM;
  
    // TCMD_AFN_D_F21_FACTR_T 
    // 总功率因数	
    sTcFactorT            sFactorT;

    // TCMD_AFN_D_F22_FACTR_A               
    // A相功率因素
    sTcFactorA            sFactorA;
    
    // TCMD_AFN_D_F23_FACTR_B               
    // B相功率因数
    sTcFactorB            sFactorB;
    
    // TCMD_AFN_D_F24_FACTR_C               
    // C相功率因数
    sTcFactorC            sFactorC;
        
    // TCMD_AFN_D_F25_POWR_HAVE_A            
    // A相有功功率
    sTcPowerHaveA sPowerHaveA;

    // TCMD_AFN_D_F26_POWR_HAVE_B            
    // B相有功功率
    sTcPowerHaveB sPowerHaveB;

    // TCMD_AFN_D_F27_POWR_HAVE_C           
    // C相有功功率
    sTcPowerHaveC sPowerHaveC;

    // TCMD_AFN_D_F28_POWR_NONE_A           
    // A相无功功率
    sTcPowerNoneA sPowerNoneA;

    // TCMD_AFN_D_F29_POWR_NONE_B           
    // B相无功功率
    sTcPowerNoneB sPowerNoneB;

    // TCMD_AFN_D_F30_POWR_NONE_C            
    // C相无功功率
    sTcPowerNoneC sPowerNoneC;

    // TCMD_AFN_D_F33_POWR_HAVE_FRTH         
    // （正向）有功总电能示数
    sTcPowerHaveFrth sPowerHaveFrth;

    // TCMD_AFN_D_F34_POWR_HAVE_BACK         
    // （反向）有功总电能示数
    sTcPowerHaveBack sPowerHaveBack;

    // TCMD_AFN_D_F35_POWR_NONE_FRTH         
    // （正向）无功总电能示数
    sTcPowerNoneFrth sPowerNoneFrth;

    // TCMD_AFN_D_F36_POWR_NONE_BACK         
    // （反向）无功总电能示数
    sTcPowerNoneBack sPowerNoneBack;

    // TCMD_AFN_D_F41_VOLT_A                 
    // A相电压
    sTcVoltA sVoltA;

    // TCMD_AFN_D_F42_VOLT_B                
    // B相电压
    sTcVoltB sVoltB;

    // TCMD_AFN_D_F43_VOLT_C                
    // C相电压
    sTcVoltC sVoltC;

    // TCMD_AFN_D_F44_VANGL_A                
    // A相电压相位角
    sTcVAngleA sVAngleA;

    // TCMD_AFN_D_F45_VANGL_B                
    // B相电压相位角
    sTcVAngleB sVAngleB;

    // TCMD_AFN_D_F46_VANGL_C                
    // C相电压相位角
    sTcVAngleC sVAngleC;

    // TCMD_AFN_D_F47_VOLT_UBL               
    // 电压不平衡度
    sTcVoltUbl sVoltUbl;

    // TCMD_AFN_D_F48_CIRCLE_V               
    // 周波
    sTcVCircle sVCircle;

    // TCMD_AFN_D_F49_ELEC_A                 
    // A相电流
    sTcElecA sElecA;

    // TCMD_AFN_D_F50_ELEC_B                 
    // B相电流
    sTcElecB sElecB;

    // TCMD_AFN_D_F51_ELEC_C                  
    // C相电流
    sTcElecC sElecC;

    // TCMD_AFN_D_F52_ELEC_M                  
    // 中性线电流
    sTcElecM sElecM;

    // TCMD_AFN_D_F53_EANGL_A                 
    // A相电流相位角
    sTcEAngleA sEAngleA;

    // TCMD_AFN_D_F54_EANGL_B                 
    // B相电流相位角
    sTcEAngleB sEAngleB;

    // TCMD_AFN_D_F55_EANGL_C                 
    // C相电流相位角
    sTcEAngleC sEAngleC;

    // TCMD_AFN_D_F56_ELEC_UBL               
    // 电流不平衡度
    sTcElecUbl sElecUbl;

    // TCMD_AFN_D_F57_VDMAX_A_TIME                
    // 日A相电压极大值和发生时间
    sTcVdMaxTimeA sVdMaxTimeA;

    // TCMD_AFN_D_F58_VDMAX_B_TIME            
    // 日B相电压极大值和发生时间
    sTcVdMaxTimeB sVdMaxTimeB;

    // TCMD_AFN_D_F59_VDMAX_C_TIME                 
    // 日C相电压极大值和发生时间
    sTcVdMaxTimeC sTcVdMaxTimeC;

    // TCMD_AFN_D_F60_IDMAX_A_TIME                
    // 日A相电流极大值和发生时间
    sTcIdMaxTimeA sIdMaxTimeA;

    // TCMD_AFN_D_F61_IDMAX_B_TIME            
    // 日B相电流极大值和发生时间
    sTcIdMaxTimeB sIdMaxTimeB;

    // TCMD_AFN_D_F62_IDMAX_C_TIME            
    // 日C相电流极大值和发生时间
    sTcIdMaxTimeC sIdMaxTimeC;
   
    // TCMD_AFN_D_F66_VDPP_TIME_B             
    // A相电压越上上限日累计时间
    sTcVDppTimeA  sVDppTimeA;

    // TCMD_AFN_D_F66_VDPP_TIME_B             
    // B相电压越上上限日累计时间
    sTcVDppTimeB  sVDppTimeB;

    // TCMD_AFN_D_F67_VDPP_TIME_C             
    // C相电压越上上限日累计时间
    sTcVDppTimeC  sVDppTimeC;

    // TCMD_AFN_D_F68_VDNN_TIME_A            
    // A相电压越下下限日累计时间
    sTcVDnnTimeA sVDnnTimeA;

    // TCMD_AFN_D_F69_VDNN_TIME_B            
    // B相电压越下下限日累计时间
    sTcVDnnTimeB sVDnnTimeB;

    // TCMD_AFN_D_F70_VDNN_TIME_C            
    // C相电压越下下限日累计时间
    sTcVDnnTimeC sVDnnTimeC;

    // TCMD_AFN_D_F73_VMPP_TIME_A            
    // A相电压越上上限月累计时间
    sTcVMppTimeA  sVMppTimeA;

    // TCMD_AFN_D_F74_VMPP_TIME_B            
    // B相电压越上上限月累计时间
    sTcVMppTimeB sVMppTimeB;

    // TCMD_AFN_D_F75_VMPP_TIME_C            
    // C相电压越上上限月累计时间
    sTcVMppTimeC sVMppTimeC;

    // TCMD_AFN_D_F76_VMNN_TIME_A            
    // A相电压越下下限月累计时间
    sTcVMnnTimeA sVMnnTimeA;

    // TCMD_AFN_D_F77_VMNN_TIME_B            
    // B相电压越下下限月累计时间
    sTcVMnnTimeB sVMnnTimeB;

    // TCMD_AFN_D_F78_VMNN_TIME_C            
    // C相电压越下下限月累计时间
    sTcVMnnTimeC sVMnnTimeC;

    // TCMD_AFN_D_F81_VABR_TOTL_A            
    // A相电压总畸变率
    sTcVabrTotalA sVabrTotalA;

    // TCMD_AFN_D_F82_VABR_TOTL_B            
    // B相电压总畸变率
    sTcVabrTotalB sVabrTotalB;

    // TCMD_AFN_D_F83_VABR_TOTL_C            
    // C相电压总畸变率
    sTcVabrTotalC sVabrTotalC;
    
    // TCMD_AFN_D_F84_EABR_TOTL_A            
    // A相电流总畸变率
    sTcEabrTotalA sEabrTotalA;
    
    // TCMD_AFN_D_F85_EABR_TOTL_B            
    // B相电流总畸变率
    sTcEabrTotalB sEabrTotalB;
    
    // TCMD_AFN_D_F86_EABR_TOTL_C            
    // C相电流总畸变率
    sTcEabrTotalC sEabrTotalC;

    // TCMD_AFN_D_F89_VABR_OOD_A             
    // A相电压奇次畸变率
    sTcVabrOddA sVabrOddA;
    
    // TCMD_AFN_D_F90_VABR_EVN_A             
    // A相电压偶次畸变率
    sTcVabrEvnA sVabrEvnA;
    
    // TCMD_AFN_D_F91_VABR_OOD_B             
    // B相电压奇次畸变率
    sTcVabrOddB sVabrOddB;
    
    // TCMD_AFN_D_F92_VABR_EVN_B             
    // B相电压偶次畸变率
    sTcVabrEvnB sVabrEvnB;
    
    // TCMD_AFN_D_F93_VABR_OOD_C             
    // C相电压奇次畸变率
    sTcVabrOddC sVabrOddC;
    
    // TCMD_AFN_D_F94_VABR_EVN_C             
    // C相电压偶次畸变率
    sTcVabrEvnC sVabrEvnC;

    // TCMD_AFN_D_F97_EABR_OOD_A             
    // A相电流奇次畸变率
    sTcEabrOddA sEabrOddA;
    
    // TCMD_AFN_D_F98_EABR_EVN_A             
    // A相电流偶次畸变率
    sTcEabrEvnA sEabrEvnA;
    
    // TCMD_AFN_D_F99_EABR_OOD_B             
    // B相电流奇次畸变率
    sTcEabrOddB sEabrOddB;
    
    // TCMD_AFN_D_F100_EABR_EVN_B             
    // B相电流偶次畸变率
    sTcEabrEvnB sEabrEvnB;
    
    // TCMD_AFN_D_F101_EABR_OOD_C           
    // C相电流奇次畸变率
    sTcEabrOddC sEabrOddC;
    
    // TCMD_AFN_D_F102_EABR_EVN_C           
    // C相电流偶次畸变率
    sTcEabrEvnC sEabrEvnC;
    
    // TCMD_AFN_D_F105_TFW_HAVE              
    // 总基波有功功率  
    sTcTfwHave sTfwHave;

    // TCMD_AFN_D_F106_TFW_NONE                
    // 总基波无功功率
    sTcTfwNone sTfwNone;
    
    // TCMD_AFN_D_F107_THW_HAVE                
    // 总谐波有功功率
    sTcThwHave sThwHave;
    
    // TCMD_AFN_D_F108_THW_NONE                
    // 总基波无功功率
    sTcThwNone sThwNone;

    // TCMD_AFN_D_F113_HARM_VOLT_A            
    // A相N次谐波电压
    sTcHarmVoltA sHarmVoltA;
    
    // TCMD_AFN_D_F114_HARM_VOLT_B          
    // B相N次谐波电压
    sTcHarmVoltB sHarmVoltB;
    
    // TCMD_AFN_D_F115_HARM_VOLT_C          
    // C相N次谐波电压
    sTcHarmVoltC sHarmVoltC;
    
    // TCMD_AFN_D_F116_HARM_ELEC_A             
    // A相N次谐波电流
    sTcHarmElecA sHarmElecA;
    
    // TCMD_AFN_D_F117_HARM_ELEC_B            
    // B相N次谐波电流
    sTcHarmElecB sHarmElecB;
    
    // TCMD_AFN_D_F118_HARM_ELEC_C            
    // C相N次谐波电流
    sTcHarmElecC sHarmElecC;

    // TCMD_AFN_D_F121_HARM_VINC_A           
    // A相N次谐波电压含有率
    sTcHarmVincA sHarmVincA;

    // TCMD_AFN_D_F122_HARM_VINC_B           
    // B相N次谐波电压含有率
    sTcHarmVincB sHarmVincB;

    // TCMD_AFN_D_F123_HARM_VINC_C            
    // C相N次谐波电压含有率
    sTcHarmVincC sHarmVincC;

    // TCMD_AFN_D_F124_HARM_EINC_A          
    // A相N次谐波电流含有率
    sTcHarmEincA sHarmEincA;

    // TCMD_AFN_D_F125_HARM_EINC_B           
    // B相N次谐波电流含有率
    sTcHarmEincB sHarmEincB;

    // TCMD_AFN_D_F126_HARM_EINC_C        
    // C相N次谐波电流含有率
    sTcHarmEincC sHarmEincC;

    // TCMD_AFN_D_F129_FLS_SHRT_A             
    // A相短时闪变
    sTcFlashShortA sFlashShortA;
    
    // TCMD_AFN_D_F130_FLS_SHRT_B            
    // B相短时闪变
    sTcFlashShortB sFlashShortB;
    
    // TCMD_AFN_D_F131_FLS_SHRT_C     
    // C相短时闪变
    sTcFlashShortC sFlashShortC;
    
    // TCMD_AFN_D_F132_FLS_LONG_A       
    // A相长时闪变
    sTcFlashLongA sFlashLongA;
    
    // TCMD_AFN_D_F133_FLS_LONG_B   
    // B相长时闪变
    sTcFlashLongB sFlashLongB;
    
    // TCMD_AFN_D_F134_FLS_LONG_C             
    // C相长时闪变
    sTcFlashLongC sFlashLongC;
    
    // TCMD_AFN_D_F137_NELC_VALUE      
    // 非电气量
    sTcNelcValue sNelcValue;
}uTcFrezApp;

typedef struct
{
    sTcmdPn    sCmdPn;
    uTcFrezApp uApp[1];       // ucN个
}sTcFrezOne;

typedef struct
{
    sTcYMDhm            sTs;    // 请求冻结数据任务中的数据的起始时间ts：分时日月年
    UINT16         usPeriod;    // 冻结周期 为定时冻结的时间间隔，为0表示删除本项冻结任务。
    eTcPeriodUnit     eUnit;    // 冻结周期单位
    UINT8               ucN;    // 冻结周期数：表示以冻结周期为间隔，需冻结的次数，为0表示无限次数。 
    UINT8               ucM;    // 本次应答（上报）的冻结数据任务中配置的数据单元标识数m
    sTcFrezOne      sOne[1];    // ucM 个    
}sTcFrezAutoA, sTcAfn12f9A;

// 封帧侧
#pragma pack(1)
typedef struct
{
    sTcFmt02_f          sTs;
    UINT16         usPeriod;     // 冻结周期 为定时冻结的时间间隔，为0表示删除本项冻结任务。
    UINT8             eUnit;     // 冻结周期单位
    UINT8               ucN;     // 冻结周期数：表示以冻结周期为间隔，需冻结的次数，为0表示无限次数。 
    UINT8               ucM;     // 本次应答（上报）的冻结数据任务中配置的数据单元标识数m
    UINT8         ucDaDt[1];     // 以下为变长
    
}sTcFrezAutoA_f, sTcAfn12f9A_f;
#pragma pack()

// 转换函数
eTcErr etc_trans_afn12f9_s2m(eTcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 
///*} 

/***************************************
 *  通用部分封装函数  (低级抽象)
 *  在该函数内实现加密与解密过程
 *  两种类型的帧
 *  (1) 固定帧
 *
 *  +------+------+------+------+------+------+------+------+
 *  |       起始字符(10H)       |          启动字符         |
 *  |------+------+------+------+------+------+------+------|
 *  |          控制域C          |                           |
 *  |------+------+------+------|                           |  
 *  |          地址域A          |          用户数据         |
 *  |------+------+------+------|                           |  
 *  |        链路用户数据       |                           |
 *  |------+------+------+------+------+------+------+------|  
 *  |          校验和CS         |           帧校验          |
 *  +------+------+------+------+------+------+------+------+  
 *  
 *  链路用户数据
 *  +------+------+------+------+
 *  |         协议标识          |
 *  +------+------+------+------+
 *
 *  (2) 可变帧
 *
 *  +------+------+------+------+------+------+------+------+
 *  |        起始字符(68H)      |                           |
 *  |------+------+------+------|                           |  
 *  |           长度L           |                           |
 *  |------+------+------+------|            帧头           |  
 *  |           长度L           |                           |
 *  |------+------+------+------|
                         |  
 *  |        起始字符(68H)      |                           |
 *  |------+------+------+------+------+------+------+------|  
 *  |          控制域C          |                           |
 *  |------+------+------+------|                           |  
 *  |          地址域A          |        用户数据           |
 *  |------+------+------+------|                           |  
 *  |        链路用户数据       |                           |
 *  |------+------+------+------+------+------+------+------|  
 *  |          校验和CS         |          帧校验           |
 *  |------+------+------+------+------+------+------+------|  
 *  |        结束字符(16H)      |         帧结束符          |
 *  +------+------+------+------+------+------+------+------+  
 *
 *  链路用户数据
 *  +------+------+------+------+
 *  |         协议标识          |
 *  |------+------+------+------|
 *  |        应用控制域AC       |
 *  |------+------+------+------|
 *  |       数据单元标识1       |
 *  |------+------+------+------|
 *  |         数据单元1         |
 *  |------+------+------+------|
 *  |         .........         |
 *  |------+------+------+------|
 *  |       数据单元标识n       |
 *  |------+------+------+------|
 *  |         数据单元n         |
 *  |------+------+------+------|
 *  |       附加信息域AUX       |
 *  +------+------+------+------+
 *
 *  说明:
 *  校验和CS:全部用户数据的算法和, 不考虑进位
 *
{*///
// 用户侧数据
typedef struct
{
    sTcAddress    sAddress;      // 地址域 A
    sTctrl        sCtrl;         // 控制域 C
    //sTcAc         sAc;           // 应用控制域Ac(Tp Ec Afn)    // 交到上层处理
    BOOL          bFixed;        // 固定帧 还是 可变帧 
    UINT16        usA2CsLen;     // 从addr 到 Cs 之间的数据长度
    UINT8         *pA2CsData;    // 从addr 到 Cs 之间的数据内容
    
}sTcPackCommon;

// 抽象帧头
// 固定帧
#pragma pack(1)
typedef struct
{
    UINT8   f10;      // 起始字符(10H) 
    UINT16  usC;      // 控制域C
    sTcA_f  stA;      // 地址域A
    UINT8   ucV;      // 本协议版本 定值 TC_PROTO_VERSION    
    UINT8   ucS;      // 校验和CS
    UINT8   ucE;      // 结束符    
}sTcfHeadFixed;

// 可变帧
typedef struct
{
    UINT8   f68;      // 第一个 起始字符(68H)
    UINT16  usL1;     // 第一个长度L
    UINT16  usL2;     // 第二个长度L
    UINT8   s68;      // 第二个 起始字符(68H)
    UINT16  usC;      // 控制域C
    sTcA_f  stA;      // 地址域A
    UINT8   ucV;      // 本协议版本 定值 TC_PROTO_VERSION  
    UINT8   ucAc;     // 应用控制域AC
    
}sTcfHeadAlter;
#pragma pack()

// 计算检测和函数(校验和是全部用户数据的算术和,不考虑进位(模256))
UINT8 uctc_get_check_sum(UINT8 *pStartPos, UINT16 usLen);

// 封装每个帧的公共部分 
eTcErr etc_pack_common(sTcPackCommon *psCommon,  UINT16 *pusLen, UINT8  *pOutBuf); 

// 解析公共部分
// 解析函数
eTcErr etc_unpack_common(sTcPackCommon *psUnpack, UINT8* pInBuf, UINT16 usLen);
///*}


/*******************************************************
 *  外部接口(用户只需关心以下接口)
 *
{*///

/***************************************
 *  协议模块初始化
 *  使该协议API需要先进行初始化
 *  
{*///
typedef struct
{
    eTcRole eRole;                  // 身份，主站或是从站
    UINT8   ucPermitDelayMinutes;   // 允许时延

#if  TC_CFG_SPT_CON   
    UINT8   aucPw[TC_PW_LEN];       // 消息认证码 仅在下行报文中
#endif

#if TC_CFG_ENCRYPT
    peTcEncryptFunc   EncryptFunc;  // 加密接口
    peTcDecryptFunc   DecryptFunc;  // 解密接口
#endif
    
}sTcInit;                           // 协议初始化数据结构

// 初始化函数
eTcErr eTcInit(sTcInit* psInit);
///*}

// 判断是否有是一个效帧
eTcErr etcIsValidPack(const UINT8* pInBuf, UINT16 usLen, BOOL *pbFiexed);

// 找到第一个有效的位置及其长度
eTcErr etcFindValidPack(UINT8* pinBuf, UINT16 usLen, UINT16* pusFirstOff, UINT16* pusFirstLen);

/***************************************************************************
 *  数据单元 应用层数据结构定义
 *  上行与下行同类型的数据结构有时会一不样
 *  
 *  终端在响应主站对终端的参数或数据请求时,
 *    如终端没有所需的某个数据项,则将应答报文中DT的对应标志位清除；
 *    如终端仅是没有某个数据项中的部分内容，则应将该数据项中的所缺部分
 *    内容的每个字节填写“EEH”。
 *    注意:在扩展应用层数据单元时,需要在每个定义中为每个数据项加上 
 *         有/无的标识 可以用一个BOOL 来表示 
 *  
{*///
typedef union
{
    /**********************************
     * 类型: 确认/否认
     * AFN : 00H
    {*///
    // TCMD_AFN_0_F1_ALL_OK_DENY
    // 全部确认/否认：对收到报文中的全部数据单元标识进行确认/否认
    // 下行:本结构
    // 上行:本结构
    eTcResCode            eResCode;         

    // TCMD_AFN_0_F2_ONE_BY_ONE
    // 按数据单元标识确认和否认：对收到报文中的全部数据单元标识进行逐个确认/否认
    // 下行:无此命令
    // 上行:本结构
    sTcOnebyOne           sOneByOne;    
    ///*}
 
    /**********************************
     * 类型: 复位命令
     * AFN : 01H
    {*///
    // TCMD_AFN_1_F1_HARD_INIT
    // TCMD_AFN_1_F2_DATA_INIT
    // TCMD_AFN_1_F3_FACTORY_RESET
    // TCMD_AFN_1_F4_PARA_INIT
    // 下行:无参数
    // 上行:AFN_00

    // TCMD_AFN_1_F5_DATA_CLEAR
    // 下行:
    sTcRtDataClear        sRtDataClear;    
    // 上行:AFN_00
    ///*}

    /**********************************
     * 类型: 链路接口检测
     * AFN : 02H
    {*///
    // TCMD_AFN_2_F1_LOG_IN
    // TCMD_AFN_2_F2_LOG_OUT
    // TCMD_AFN_2_F3_HEART_BEAT
    // 下行:无此命令
    // 上行:无参数

    // TCMD_AFN_2_F4_LINK_OK
    // 下行:无参数(对登录、退出和心跳的应答)
    // 上行:无此命令
    ///*}

    /**********************************
     * 类型: 设置参数
     * AFN : 04H
     * 上行: AFN_00
    {*///
    // TCMD_AFN_4_F1_CON_IP_PORT 
    // (设置)集中与交互终端IP地址和端口
    // 下行:
    sTcDownCfg              sDownCfg;  

    // TCMD_AFN_4_F2_TML_UP_CFG
    // (设置)监测终端上行通信参数配置
    // 下行:
    sTcTmlUpCfg            sTmlUpCfg; 

    // TCMD_AFN_4_F3_TML_AUTH_PARA
    // (设置)监测终端上行通信消息认证参数设置
    // 下行:
    sTcAuthPara            sAuthPara; 

    // TCMD_AFN_4_F4_TML_STATE_INPUT
    // (设置)状态量输入参数
    // 下行:
    sTcStateInput          sStateInput; 

    // TCMD_AFN_4_F5_TML_EVENT_CFG
    // (设置)事件记录配置
    // 下行:
    sTcEventCfg            sEventCfg; 

    // TCMD_AFN_4_F17_FREZ_TASK_PARA 
    // (设置)冻结数据任务配置
    // 下行:
    sTcFrezTaskPara        sFrezTaskPara;  

    // TCMD_AFN_4_F25_ELEC_MP_CFG
    // (设置)电气测量点配置参数
    // 下行:
    sTcElecMpCfg          sElecMpCfg; 

    // TCMD_AFN_4_F26_ELEC_MP_BASE
    // (设置)电气测量点基本参数
    // 下行:
    sTcElecMpBase         sElecMpBase;     

    // TCMD_AFN_4_F27_ELEC_LMIT_PARA
    // (设置)电气测量点限值参数
    // 下行:
    sTcElecLimitPower      sElecLimitPower; 

    // TCMD_AFN_4_F28_ELEC_LMIT_FACTR
    // (设置)电气测量点总功率因数参数
    // 下行:
    sTcFactorLimit         sFactorLimit; 

    // TCMD_AFN_4_F29_ELEC_FIX_HARM
    // (设置)电气测量点谐波畸变率越限定值
    // 下行:
    sTcElecFixHarm         sElecFixHarm; 

    // TCMD_AFN_4_F30_ELEC_FLASH
    // (设置)电气测量点闪变越限参数
    // 下行:
    sTcElecFlash           sElecFlash; 

    // TCMD_AFN_4_F33_NELC_MP_CFG
    // (设置)非电气测量点配置参数
    // 下行:
    sTcNelcMpCfg          sNElecMpCfg; 

    // TCMD_AFN_4_F34_NELC_MP_PARA
    // (设置)非电气测量点基本参数
    // 下行:
    sTcNelcMpPara          sNelcMpPara;      

    // TCMD_AFN_4_F35_NELC_MP_LMIT
    // (设置)非电气测量点越限参数
    // 下行:
    sTcNelcMpLimit         sNelcMpLimit;  
    ///*}

    /**********************************
     * 类型: TCMD_AFN_5_F1_CHECK_TIME
     * AFN : 05H
     * 上行: AFN_00
    {*///
    // TCMD_AFN_5_F1_CHECK_TIME
    // 校时命令 
    // 下行:
    sTcUerClock         sCheckClock; 

    // TCMD_AFN_5_F2_FREZ_TEMP
    // 临时冻结命令 
    // 下行:
    sTcFrezTemp         sFrezTemp; 

    // TCMD_AFN_5_F3_AUTO_SAY_ON
    // TCMD_AFN_5_F4_AUTO_SAY_OFF 
    // 下行:无参数

    // TCMD_AFN_5_F5_NX_MODEL_ACT
    // 能效模型有效 
    // 下行:
    sTcNxModelAct       sNxModelAct; 

    // TCMD_AFN_5_F6_NX_MODEL_CLR
    // 能效模型清除 
    // 下行:
    sTcNxModelClr       sNxModelClr; 

    // TCMD_AFN_5_F7_RQ_RESPN_ACT
    // 需求响应信息有效 
    // 下行:
    sTcRqRespnAct       sRqRespnAct; 

    // TCMD_AFN_5_F8_RQ_RESPN_CLT
    // 需求响应信息清除 
    // 下行:
    sTcRqRespnClr       sRqRespnClr; 

    // TCMD_AFN_5_F9_REPT_FREZ_ON
    // TCMD_AFN_5_F10_REPT_FREZ_OFF 
    // 下行:无参数

    // TCMD_AFN_5_F17_REMOTE_OFF
    // 遥控跳闸 
    // 下行:
    sTcRemoteOff        sRemoteOff; 

    // TCMD_AFN_5_F18_REMOTE_ON
    // 允许合闸 
    // 下行:
    sTcRemoteOn         sRemoteOn; 
    ///*}
    
    /**********************************
     * 类型: 查询参数
     * AFN : 0AH
    {*///
    // TCMD_AFN_A_F1_CON_IP_PORT
    // (查询)集中与交互终端IP地址和端口 
    // 下行:无参数
    // 上行:
    sTcDownCfg             sDownCfgA; 

    // TCMD_AFN_A_F2_TML_UP_CFG
    // (查询)监测终端上行通信参数配置
    // 下行:无参数
    // 上行:
    sTcTmlUpCfg            sTmlUpCfgA;    

    // TCMD_AFN_A_F3_TML_AUTH_PARA
    // (查询)监测终端上行通信消息认证参数设置
    // 下行:无参数
    // 上行:
    sTcAuthPara            sAuthParaA; 

    // TCMD_AFN_A_F4_TML_STATE_INPUT
    // (查询)状态量输入参数 
    // 下行:无参数
    // 上行:
    sTcStateInput          sStateInputA; 

    // TCMD_AFN_A_F5_TML_EVENT_CFG
    // (查询)事件记录配置
    // 下行:无参数
    // 上行:
    sTcEventCfg            sEventCfgA; 

    // TCMD_AFN_A_F11_TML_SPRT_EVENT
    // (查询)终端支持的事件记录信息
    // 下行:无参数
    // 上行:
    sTcSuptEvent           sSuptEventA; 

    // TCMD_AFN_A_F12_ELEC_MP_INFO
    // (查询)已配置电气测量点信息 
    // 下行:无参数
    // 上行:
    sTcElecMpInfo          sElecMpInfoA; 

    // TCMD_AFN_A_F13_NELC_MP_INFO
    // (查询)已配置非电气测量点信息
    // 下行:无参数
    // 上行:
    sTcNelcMpInfo          sNelcMpInfoA; 

    // TCMD_AFN_A_F14_TML_PROTO_SPRT
    // (查询)接入端口支持的通信协议信息
    // 下行:无参数
    // 上行:
    sTcTmlProtoSprt        sTmlProtoSprtA; 

    // TCMD_AFN_A_F15_TML_MODEL_VERSION
    // (查询)终端内各智能模块的软硬件版本信息 
    // 下行:无参数
    // 上行:
    sTcTmlModelVersion      sTmlModelVersionA; 

    // TCMD_AFN_A_F16_TML_VERSION
    // (查询)终端软硬件版本信息
    // 下行:无参数
    // 上行:
    sTcTmlVersion           sTmlVersionA; 

    // TCMD_AFN_A_F17_FREZ_TASK_PARA
    // (查询)冻结数据任务配置
    // 下行:无参数
    // 上行:
    sTcFrezTaskPara        sFrezTaskParaA;  

    // TCMD_AFN_A_F25_ELEC_MP_CFG
    // (查询)电气测量点配置参数
    // 下行:无参数
    // 上行:
    sTcElecMpCfg          sElecMpCfgA; 

    // TCMD_AFN_A_F26_ELEC_MP_BASE
    // (查询)电气测量点基本参数
    // 下行:无参数
    // 上行:
    sTcElecMpBase         sElecMpBaseA;     

    // TCMD_AFN_A_F27_ELEC_LMIT_PARA
    // (查询)电气测量点限值参数
    // 下行:无参数
    // 上行:
    sTcElecLimitPower      sElecLimitPowerA; 

    // TCMD_AFN_A_F28_ELEC_LMIT_FACTR
    // (查询)电气测量点总功率因数参数
    // 下行:无参数
    // 上行:
    sTcFactorLimit         sFactorLimitA; 

    // TCMD_AFN_A_F29_ELEC_FIX_HARM
    // (查询)电气测量点谐波畸变率越限定值
    // 下行:无参数
    // 上行:
    sTcElecFixHarm         sElecFixHarmA; 

    // TCMD_AFN_A_F30_ELEC_FLASH
    // (查询)电气测量点闪变越限参数
    // 下行:无参数
    // 上行:
    sTcElecFlash           sElecFlashA; 

    // TCMD_AFN_A_F33_NELC_MP_CFG
    // (查询)非电气测量点配置参数
    // 下行:无参数
    // 上行:
    sTcNelcMpCfg          sNElecMpCfgA; 

    // TCMD_AFN_A_F34_NELC_MP_PARA
    // (查询)非电气测量点基本参数
    // 下行:无参数
    // 上行:
    sTcNelcMpPara          sNelcMpParaA;      

    // TCMD_AFN_A_F35_NELC_MP_LMIT
    // (查询)非电气测量点越限参数
    // 下行:无参数
    // 上行:
    sTcNelcMpLimit         sNelcMpLimitA;  
    ///*}

    /**********************************
     * 类型: 请求(定时上报)任务数据
     * AFN : 0CH
    {*///
    // TCMD_AFN_C_F1_FREZ_TEMP
    // 请求临时冻结命令的冻结数据
    // 下行:无参数
    // 上行:采用请求实时数据命令的上行报文格式

    // TCMD_AFN_C_F9_FREZ_AUTO
    // 请求（定时上报）冻结数据任务
    // 下行:
    sTcFrezAutoQ   sFrezAutoQ;
    // 上行:
    sTcFrezAutoA   sFrezAutoA;
    ///*}

    /**********************************
     * 类型: 请求实时数据
     * AFN : 0CH
     * 下行: 无参数
    {*///
    // TCMD_AFN_D_F1_CLOCK
    sTcUerClock           sUerClock;
    
    // TCMD_AFN_D_F2_PARA_STATE
    // 参数状态标志
    sTcParaState          sParaState;       

    // TCMD_AFN_D_F3_EVENT_1
    // 重要事件计数器当前值
    UINT16                usEc1;            

    // TCMD_AFN_D_F4_EVENT_2
    // 一般事件计数器当前值
    UINT16                usEc2;           

    // TCMD_AFN_D_F5_EVENT_STATE
    // 事件状态标志
    sTcEventState         sEventState;      

    // TCMD_AFN_D_F6_POWR_TIMES
    sTcPowerTimes         sPowerTimes;

    // TCMD_AFN_D_F9_STATE 
    // 状态量及变位标志
    sTcState              sState;           
    
    // TCMD_AFN_D_F17_POWR_HAVE_T  
    // 总有功功率
    sTcPowerHaveT         sPowerHaveT;
    
    // TCMD_AFN_D_F18_POWR_NONE_T         
    // 总无功功率
    sTcPowerNoneT         sPowerNoneT;      

    // TCMD_AFN_D_F19_DEMD_TIME_D           
    // 日最大需量发生时间
    sTcDemandMaxD         sDemandMaxD;

    // TCMD_AFN_D_F20_DEMD_TIME_M            
    // 月最大需量及发生时间
    sTcDemandMaxM         sDemandMaxM;
  
    // TCMD_AFN_D_F21_FACTR_T 
    // 总功率因数	
    sTcFactorT            sFactorT;

    // TCMD_AFN_D_F22_FACTR_A               
    // A相功率因素
    sTcFactorA            sFactorA;
    
    // TCMD_AFN_D_F23_FACTR_B               
    // B相功率因数
    sTcFactorB            sFactorB;
    
    // TCMD_AFN_D_F24_FACTR_C               
    // C相功率因数
    sTcFactorC            sFactorC;
        
    // TCMD_AFN_D_F25_POWR_HAVE_A            
    // A相有功功率
    sTcPowerHaveA sPowerHaveA;
    
    // TCMD_AFN_D_F26_POWR_HAVE_B            
    // B相有功功率
    sTcPowerHaveB sPowerHaveB;

    // TCMD_AFN_D_F27_POWR_HAVE_C           
    // C相有功功率
    sTcPowerHaveC sPowerHaveC;

    // TCMD_AFN_D_F28_POWR_NONE_A           
    // A相无功功率
    sTcPowerNoneA sPowerNoneA;

    // TCMD_AFN_D_F29_POWR_NONE_B           
    // B相无功功率
    sTcPowerNoneB sPowerNoneB;

    // TCMD_AFN_D_F30_POWR_NONE_C            
    // C相无功功率
    sTcPowerNoneC sPowerNoneC;

    // TCMD_AFN_D_F33_POWR_HAVE_FRTH         
    // （正向）有功总电能示数
    sTcPowerHaveFrth sPowerHaveFrth;

    // TCMD_AFN_D_F34_POWR_HAVE_BACK         
    // （反向）有功总电能示数
    sTcPowerHaveBack sPowerHaveBack;

    // TCMD_AFN_D_F35_POWR_NONE_FRTH         
    // （正向）无功总电能示数
    sTcPowerNoneFrth sPowerNoneFrth;

    // TCMD_AFN_D_F36_POWR_NONE_BACK         
    // （反向）无功总电能示数
    sTcPowerNoneBack sPowerNoneBack;

    // TCMD_AFN_D_F41_VOLT_A                 
    // A相电压
    sTcVoltA sVoltA;

    // TCMD_AFN_D_F42_VOLT_B                
    // B相电压
    sTcVoltB sVoltB;

    // TCMD_AFN_D_F43_VOLT_C                
    // C相电压
    sTcVoltC sVoltC;

    // TCMD_AFN_D_F44_VANGL_A                
    // A相电压相位角
    sTcVAngleA sVAngleA;

    // TCMD_AFN_D_F45_VANGL_B                
    // B相电压相位角
    sTcVAngleB sVAngleB;

    // TCMD_AFN_D_F46_VANGL_C                
    // C相电压相位角
    sTcVAngleC sVAngleC;

    // TCMD_AFN_D_F47_VOLT_UBL               
    // 电压不平衡度
    sTcVoltUbl sVoltUbl;

    // TCMD_AFN_D_F48_CIRCLE_V               
    // 周波
    sTcVCircle sVCircle;

    // TCMD_AFN_D_F49_ELEC_A                 
    // A相电流
    sTcElecA sElecA;

    // TCMD_AFN_D_F50_ELEC_B                 
    // B相电流
    sTcElecB sElecB;

    // TCMD_AFN_D_F51_ELEC_C                  
    // C相电流
    sTcElecC sElecC;

    // TCMD_AFN_D_F52_ELEC_M                  
    // 中性线电流
    sTcElecM sElecM;

    // TCMD_AFN_D_F53_EANGL_A                 
    // A相电流相位角
    sTcEAngleA sEAngleA;

    // TCMD_AFN_D_F54_EANGL_B                 
    // B相电流相位角
    sTcEAngleB sEAngleB;

    // TCMD_AFN_D_F55_EANGL_C                 
    // C相电流相位角
    sTcEAngleC sEAngleC;

    // TCMD_AFN_D_F56_ELEC_UBL               
    // 电流不平衡度
    sTcElecUbl sElecUbl;

    // TCMD_AFN_D_F57_VDMAX_A_TIME                
    // 日A相电压极大值和发生时间
    sTcVdMaxTimeA sVdMaxTimeA;

    // TCMD_AFN_D_F58_VDMAX_B_TIME            
    // 日B相电压极大值和发生时间
    sTcVdMaxTimeB sVdMaxTimeB;

    // TCMD_AFN_D_F59_VDMAX_C_TIME                 
    // 日C相电压极大值和发生时间
    sTcVdMaxTimeC sTcVdMaxTimeC;

    // TCMD_AFN_D_F60_IDMAX_A_TIME                
    // 日A相电流极大值和发生时间
    sTcIdMaxTimeA sIdMaxTimeA;

    // TCMD_AFN_D_F61_IDMAX_B_TIME            
    // 日B相电流极大值和发生时间
    sTcIdMaxTimeB sIdMaxTimeB;

    // TCMD_AFN_D_F62_IDMAX_C_TIME            
    // 日C相电流极大值和发生时间
    sTcIdMaxTimeC sIdMaxTimeC;
   
    // TCMD_AFN_D_F66_VDPP_TIME_B             
    // A相电压越上上限日累计时间
    sTcVDppTimeA  sVDppTimeA;

    // TCMD_AFN_D_F66_VDPP_TIME_B             
    // B相电压越上上限日累计时间
    sTcVDppTimeB  sVDppTimeB;

    // TCMD_AFN_D_F67_VDPP_TIME_C             
    // C相电压越上上限日累计时间
    sTcVDppTimeC  sVDppTimeC;

    // TCMD_AFN_D_F68_VDNN_TIME_A            
    // A相电压越下下限日累计时间
    sTcVDnnTimeA sVDnnTimeA;

    // TCMD_AFN_D_F69_VDNN_TIME_B            
    // B相电压越下下限日累计时间
    sTcVDnnTimeB sVDnnTimeB;

    // TCMD_AFN_D_F70_VDNN_TIME_C            
    // C相电压越下下限日累计时间
    sTcVDnnTimeC sVDnnTimeC;

    // TCMD_AFN_D_F73_VMPP_TIME_A            
    // A相电压越上上限月累计时间
    sTcVMppTimeA  sVMppTimeA;

    // TCMD_AFN_D_F74_VMPP_TIME_B            
    // B相电压越上上限月累计时间
    sTcVMppTimeB sVMppTimeB;

    // TCMD_AFN_D_F75_VMPP_TIME_C            
    // C相电压越上上限月累计时间
    sTcVMppTimeC sVMppTimeC;

    // TCMD_AFN_D_F76_VMNN_TIME_A            
    // A相电压越下下限月累计时间
    sTcVMnnTimeA sVMnnTimeA;

    // TCMD_AFN_D_F77_VMNN_TIME_B            
    // B相电压越下下限月累计时间
    sTcVMnnTimeB sVMnnTimeB;

    // TCMD_AFN_D_F78_VMNN_TIME_C            
    // C相电压越下下限月累计时间
    sTcVMnnTimeC sVMnnTimeC;

    // TCMD_AFN_D_F81_VABR_TOTL_A            
    // A相电压总畸变率
    sTcVabrTotalA sVabrTotalA;

    // TCMD_AFN_D_F82_VABR_TOTL_B            
    // B相电压总畸变率
    sTcVabrTotalB sVabrTotalB;

    // TCMD_AFN_D_F83_VABR_TOTL_C            
    // C相电压总畸变率
    sTcVabrTotalC sVabrTotalC;
    
    // TCMD_AFN_D_F84_EABR_TOTL_A            
    // A相电流总畸变率
    sTcEabrTotalA sEabrTotalA;
    
    // TCMD_AFN_D_F85_EABR_TOTL_B            
    // B相电流总畸变率
    sTcEabrTotalB sEabrTotalB;
    
    // TCMD_AFN_D_F86_EABR_TOTL_C            
    // C相电流总畸变率
    sTcEabrTotalC sEabrTotalC;

    // TCMD_AFN_D_F89_VABR_OOD_A             
    // A相电压奇次畸变率
    sTcVabrOddA sVabrOddA;
    
    // TCMD_AFN_D_F90_VABR_EVN_A             
    // A相电压偶次畸变率
    sTcVabrEvnA sVabrEvnA;
    
    // TCMD_AFN_D_F91_VABR_OOD_B             
    // B相电压奇次畸变率
    sTcVabrOddB sVabrOddB;
    
    // TCMD_AFN_D_F92_VABR_EVN_B             
    // B相电压偶次畸变率
    sTcVabrEvnB sVabrEvnB;
    
    // TCMD_AFN_D_F93_VABR_OOD_C             
    // C相电压奇次畸变率
    sTcVabrOddC sVabrOddC;
    
    // TCMD_AFN_D_F94_VABR_EVN_C             
    // C相电压偶次畸变率
    sTcVabrEvnC sVabrEvnC;

    // TCMD_AFN_D_F97_EABR_OOD_A             
    // A相电流奇次畸变率
    sTcEabrOddA sEabrOddA;
    
    // TCMD_AFN_D_F98_EABR_EVN_A             
    // A相电流偶次畸变率
    sTcEabrEvnA sEabrEvnA;
    
    // TCMD_AFN_D_F99_EABR_OOD_B             
    // B相电流奇次畸变率
    sTcEabrOddB sEabrOddB;
    
    // TCMD_AFN_D_F100_EABR_EVN_B             
    // B相电流偶次畸变率
    sTcEabrEvnB sEabrEvnB;
    
    // TCMD_AFN_D_F101_EABR_OOD_C           
    // C相电流奇次畸变率
    sTcEabrOddC sEabrOddC;
    
    // TCMD_AFN_D_F102_EABR_EVN_C           
    // C相电流偶次畸变率
    sTcEabrEvnC sEabrEvnC;
    
    // TCMD_AFN_D_F105_TFW_HAVE              
    // 总基波有功功率  
    sTcTfwHave sTfwHave;

    // TCMD_AFN_D_F106_TFW_NONE                
    // 总基波无功功率
    sTcTfwNone sTfwNone;
    
    // TCMD_AFN_D_F107_THW_HAVE                
    // 总谐波有功功率
    sTcThwHave sThwHave;
    
    // TCMD_AFN_D_F108_THW_NONE                
    // 总基波无功功率
    sTcThwNone sThwNone;
    
    // TCMD_AFN_D_F113_HARM_VOLT_A            
    // A相N次谐波电压
    sTcHarmVoltA sHarmVoltA;
    
    // TCMD_AFN_D_F114_HARM_VOLT_B          
    // B相N次谐波电压
    sTcHarmVoltB sHarmVoltB;
    
    // TCMD_AFN_D_F115_HARM_VOLT_C          
    // C相N次谐波电压
    sTcHarmVoltC sHarmVoltC;
    
    // TCMD_AFN_D_F116_HARM_ELEC_A             
    // A相N次谐波电流
    sTcHarmElecA sHarmElecA;
    
    // TCMD_AFN_D_F117_HARM_ELEC_B            
    // B相N次谐波电流
    sTcHarmElecB sHarmElecB;
    
    // TCMD_AFN_D_F118_HARM_ELEC_C            
    // C相N次谐波电流
    sTcHarmElecC sHarmElecC;

    // TCMD_AFN_D_F121_HARM_VINC_A           
    // A相N次谐波电压含有率
    sTcHarmVincA sHarmVincA;

    // TCMD_AFN_D_F122_HARM_VINC_B           
    // B相N次谐波电压含有率
    sTcHarmVincB sHarmVincB;

    // TCMD_AFN_D_F123_HARM_VINC_C            
    // C相N次谐波电压含有率
    sTcHarmVincC sHarmVincC;

    // TCMD_AFN_D_F124_HARM_EINC_A          
    // A相N次谐波电流含有率
    sTcHarmEincA sHarmEincA;

    // TCMD_AFN_D_F125_HARM_EINC_B           
    // B相N次谐波电流含有率
    sTcHarmEincB sHarmEincB;

    // TCMD_AFN_D_F126_HARM_EINC_C        
    // C相N次谐波电流含有率
    sTcHarmEincC sHarmEincC;

    // TCMD_AFN_D_F129_FLS_SHRT_A             
    // A相短时闪变
    sTcFlashShortA sFlashShortA;
    
    // TCMD_AFN_D_F130_FLS_SHRT_B            
    // B相短时闪变
    sTcFlashShortB sFlashShortB;
    
    // TCMD_AFN_D_F131_FLS_SHRT_C     
    // C相短时闪变
    sTcFlashShortC sFlashShortC;
    
    // TCMD_AFN_D_F132_FLS_LONG_A       
    // A相长时闪变
    sTcFlashLongA sFlashLongA;
    
    // TCMD_AFN_D_F133_FLS_LONG_B   
    // B相长时闪变
    sTcFlashLongB sFlashLongB;
    
    // TCMD_AFN_D_F134_FLS_LONG_C             
    // C相长时闪变
    sTcFlashLongC sFlashLongC;

    // TCMD_AFN_D_F137_NELC_VALUE      
    // 非电气量
    sTcNelcValue sNelcValue;
    ///*}
  
    // 仅用于占位 无应用意义
    UINT8            ucRev[TC_UNIT_DATA_MAX];
    
}uTcApp;

/***************************************
 *  帧内容数据结构 用户侧  (低级抽象)
 *  用于封装与解析
 *  变长结构
{*///
typedef struct
{
    sTcPnFn    sPnFn;
    uTcApp     *puApp[TC_PN_INDEX_MAX][TC_FN_INDEX_MAX];   // 保存最多64个数据单元的指针
}sTcBaseData;

typedef struct
{
    sTcAddress    sAddress;        // 地址域 A
    sTctrl        sCtrl;           // 控制域 C
    BOOL          bFixed;          // 固定帧还是可变帧 

    // 可变帧存在以下字段
    sTcAc         sAc;             // 应用控制域Ac(Tp Ec Afn)
    sTcEc         sEc;             // 事件计数器  决定于 sTcAc 域中的bEc (只存在于上行报文中)
    sTcTp         sTp;             // 时间标签    决定于 sTcAc 域中的bTp 
    UINT8         aPw[TC_PW_LEN];  // 消息认证码  (只存在于重要的下行报文中)
    
    // 数据单元域  变长域
    UINT16        usNum;           // 数据单元组的个数
    sTcBaseData   sData[1];        // 数据单元组
}stcBaskPack;

void vtc_free_base_data(sTcBaseData* pBaseData, INT32 Num);

// 封帧函数
eTcErr etc_pack_base(stcBaskPack* psPack, UINT8* pOutBuf, UINT16* pusLen);   

// 解帧函数
eTcErr etc_unPack_base(stcBaskPack *psUnpack, UINT8* pInBuf, UINT16 usLen);
///*}

/***************************************
 *  数据单元标识与对应的数据单元 (高级抽象)
 *  
 * 数据单元为按数据单元标识所组织的数据,包括参数、命令等。
 * 数据组织的顺序规则：离散方式
 * 即：命令标识 数据单元 一一对应的方式
 * 
{*///
typedef struct
{
    eTcmd        eCmd;        // 功能码
    UINT16       usPN;        // Pn (0 <= pn <= 2040 )
    BOOL         bApp;        // 是否有数据单元
    uTcApp       uApp;        // 对应不同的命令类型, 及上下行类型, 应用层数据时有时无
    
}sTcData;
///*}

/***************************************
 *  封帧与解帧(通用) 用户侧数据结构 (高级抽象)
 *  用于封装及解封装 
 *  变长结构
{*///
typedef struct
{    
    sTcAddress    sAddress;        // 地址域 A
    sTctrl        sCtrl;           // 控制域 C
    BOOL          bFixed;          // 固定帧还是可变帧 

    // 可变帧有以下可选字段
    sTcAc         sAc;             // 应用控制域Ac(Tp Ec Afn)
    sTcEc         sEc;             // 事件计数器  决定于 sTcAc 域中的bEc (只存在于上行报文中)
    sTcTp         sTp;             // 时间标签    决定于 sTcAc 域中的bTp 
    BOOL          bPw;             // 是否有Pw字段(只存在重要的下行的报文中)
    UINT8         aPw[TC_PW_LEN];  // 消息认证码  (只存在于重要的下行报文中)

    // 数据单元域  变长域
    UINT16        usNum;           // 数据单元组的个数
    sTcData       sData[1];        // usNum个数据单元组
    
}stcPack;

// 高级接口(用户使用)
// 封装函数
eTcErr etcPack(stcPack* psPack, UINT8* pOutBuf, UINT16* pusLen);   

// 解帧函数
eTcErr etcUnPack(stcPack *psUnpack, UINT8* pInBuf, UINT16 usLen);
///*}

/***************************************
 *  终端侧结构与接口(集中器侧不关注) 
 *  功能:
 *   (1)高级抽象终端侧的变长结构
 *   (2)屏蔽终端侧不需要关心的字段
 *   (3)实现终端侧数据结构报文的封帧与解封装 
 *  注意:
 *   (1)
 *
{*///
typedef struct
{
    sTcAddress    sAddress;        // 地址域 A
    BOOL          bReSend;         // 是否为重发  TRUE 重发的帧计数不会自动增加1 FALSE 会自增1
    BOOL          bActive;         // 是否为主动上报 (仅登录、心跳、退出登录、1类2类数据主动上报时为真)
    UINT16        usNum;           // 该包中含有子命令的个数 最少有一个子命令
    sTcData       sData[1];        // usNum个数据单元组
}sTcPackTml;

// 封装函数
eTcErr etcPackTml(sTcPackTml* psPack, UINT8* pOutBuf, UINT16* pusLen);   

// 解帧函数
eTcErr etcUnPackTml(sTcPackTml *psUnpack, UINT8* pInBuf, UINT16 usLen);
///*}

/***************************************
 *  集中器侧结构与接口(终端侧不关注) 
 *  功能:
 *   (1)高级抽象集中器侧的变长结构
 *   (2)屏蔽集中器侧不需要关心的字段
 *   (3)实现集中器侧数据结构报文的封帧与解封装 
 *  注意:
 *   (1)集中器侧,需要维护每个通信终端的ucPSEQ
 *
 *
{*///
typedef struct
{
    sTcAddress    sAddress;        // 地址域 A
    UINT8         ucPSEQ;          // 启动帧序号 PSEQ
    UINT8         ucRSEQ;          // 响应帧序号 RSEQ
    UINT8         aPw[TC_PW_LEN];  // 消息认证码  (只存在于重要的下行报文中)

    // 数据单元域  变长域
    UINT16        usNum;           // 数据单元组的个数
    sTcData       sData[1];        // usNum个数据单元组

}sTcPackCon;

// 封装函数
eTcErr etcPackCon(sTcPackCon* psPack, UINT8* pOutBuf, UINT16* pusLen);   

// 解帧函数
eTcErr etcUnPackCon(sTcPackCon *psUnpack, UINT8* pInBuf, UINT16 usLen);
///*}
#endif // _GBNX_32_API_H_
