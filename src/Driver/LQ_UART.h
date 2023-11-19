/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【平    台】北京龙邱智能科技TC297TX核心板
【编    写】chiusir
【E-mail】chiusir@163.com
【软件版本】V1.1 版权所有，单位使用请先联系授权
【最后更新】2021年10月28日
【相关信息参考下列地址】
【网    站】http://www.lqist.cn
【淘宝店铺】http://longqiu.taobao.com
------------------------------------------------
【dev.env.】AURIX Development Studio1.4及以上版本
【Target 】 TC297TX
【Crystal】 20.000Mhz
【SYS PLL】 300MHz*3
________________________________________________________________
基于iLLD_1_0_1_11_0底层程序,

使用例程的时候，建议采用没有空格的英文路径，切换workspace到当前工程所放文件夹！
除了RIF为TC3xxxA独有外，其它的代码兼容TC3xx
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#ifndef _LQ_ASC_H_
#define _LQ_ASC_H_

#include <Platform_Types.h>
#include <stdint.h>
#include <Ifx_Fifo.h>
#include <Ifx_Types.h>
#include <IfxAsclin.h>
#include <IfxAsclin_Asc.h>
#include <IfxAsclin_PinMap.h>
#include <IfxCpu.h>
#include <IfxCpu_Irq.h>
#include <IfxPort.h>
#include <IfxPort_regdef.h>
#include "interrupt.h"

/**
  * @brief UART 枚举
  */
typedef enum
{
	UART0 = 0,
	UART1,
	UART2,
	UART3
}UART_t;

//L.Q UART RX 管脚枚举
typedef enum
{
	UART0_RX_P14_1 = 0xB401, UART0_RX_P15_3 = 0xB503,

	UART1_RX_P02_3 = 0xA203, UART1_RX_P11_10= 0xB10A, UART1_RX_P15_1 = 0xB501, UART1_RX_P15_5 = 0xB505, UART1_RX_P20_9 = 0xC009, UART1_RX_P33_13= 0xD30D,

	UART2_RX_P02_0 = 0xA200, UART2_RX_P02_1 = 0xA201, UART2_RX_P10_6 = 0xB006, UART2_RX_P14_3 = 0xB403, UART2_RX_P33_8 = 0xD308,

	UART3_RX_P00_1 = 0xA001, UART3_RX_P15_7 = 0xB507, UART3_RX_P20_3 = 0xC003, UART3_RX_P21_6 = 0xC106

}UART_RX_t;


//L.Q UART TX 管脚枚举
typedef enum
{
	UART0_TX_P14_0 = 0xB400, UART0_TX_P14_1 = 0xB401, UART0_TX_P15_2 = 0xB502, UART0_TX_P15_3 = 0xB503,

	UART1_TX_P02_2 = 0xA202, UART1_TX_P11_12= 0xB10C, UART1_TX_P15_0 = 0xB500, UART1_TX_P15_1 = 0xB501, UART1_TX_P15_4 = 0xB504, UART1_TX_P15_5 = 0xB505, UART1_TX_P20_10= 0xC00A, UART1_TX_P33_12= 0xD30C, UART1_TX_P33_13 = 0xD30D,

	UART2_TX_P02_0 = 0xA200, UART2_TX_P10_5 = 0xB005, UART2_TX_P14_2 = 0xB402, UART2_TX_P14_3 = 0xB403, UART2_TX_P33_8 = 0xD308, UART2_TX_P33_9 = 0xD309,

	UART3_TX_P00_0 = 0xA000, UART3_TX_P00_1 = 0xA001, UART3_TX_P15_6 = 0xB506, UART3_TX_P15_7 = 0xB507, UART3_TX_P20_0 = 0xC000, UART3_TX_P20_3 = 0xC003, UART3_TX_P21_7 = 0xC107

}UART_TX_t;



#define ASC_TX_BUFFER_SIZE 64        //发送缓冲区长度
#define ASC_RX_BUFFER_SIZE 64        //接收缓冲区长度

extern unsigned char buffer_0[ASC_RX_BUFFER_SIZE];

void UART_InitConfig(UART_RX_t RxPin, UART_TX_t TxPin, unsigned long baudrate);
void UART_PutChar(UART_t  uratn, char ch);
void UART_PutStr(UART_t  uratn, char *str);
void UART_PutBuff(UART_t  uratn, unsigned char *buff, unsigned long len);
uint8 UART_GetCount(UART_t  uratn);
char UART_GetChar(UART_t  uratn);
char UART_GetBuff(UART_t  uratn, unsigned char *data, unsigned char len);

#endif /* 0_APPSW_TRICORE_APP_LQ_ASC_H_ */
