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

#include "include.h"


unsigned char buffer_0[ASC_RX_BUFFER_SIZE];     //串口0接收缓存

//串口通信结构体
IfxAsclin_Asc g_UartConfig[4];

static uint8 s_AscTxBuffer[4][ASC_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
static uint8 s_AscRxBuffer[4][ASC_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];

/* UART中断 */
IFX_INTERRUPT(UART0_RX_IRQHandler, UART0_VECTABNUM, UART0_RX_PRIORITY);
IFX_INTERRUPT(UART1_RX_IRQHandler, UART1_VECTABNUM, UART1_RX_PRIORITY);
IFX_INTERRUPT(UART2_RX_IRQHandler, UART2_VECTABNUM, UART2_RX_PRIORITY);
IFX_INTERRUPT(UART3_RX_IRQHandler, UART3_VECTABNUM, UART3_RX_PRIORITY);
IFX_INTERRUPT(UART0_TX_IRQHandler, UART0_VECTABNUM, UART0_TX_PRIORITY);
IFX_INTERRUPT(UART1_TX_IRQHandler, UART1_VECTABNUM, UART1_TX_PRIORITY);
IFX_INTERRUPT(UART2_TX_IRQHandler, UART2_VECTABNUM, UART2_TX_PRIORITY);
IFX_INTERRUPT(UART3_TX_IRQHandler, UART3_VECTABNUM, UART3_TX_PRIORITY);
IFX_INTERRUPT(UART0_ER_IRQHandler, UART0_VECTABNUM, UART0_ER_PRIORITY);
IFX_INTERRUPT(UART1_ER_IRQHandler, UART1_VECTABNUM, UART1_ER_PRIORITY);
IFX_INTERRUPT(UART2_ER_IRQHandler, UART2_VECTABNUM, UART2_ER_PRIORITY);
IFX_INTERRUPT(UART3_ER_IRQHandler, UART3_VECTABNUM, UART3_ER_PRIORITY);


/** UART中断CPU标号 */
const uint8 UartIrqVectabNum[4] = {UART0_VECTABNUM, UART1_VECTABNUM, UART2_VECTABNUM, UART3_VECTABNUM};

/** UART中断优先级 */
const uint8 UartIrqPriority[12] = {UART0_RX_PRIORITY, UART0_TX_PRIORITY, UART0_ER_PRIORITY, UART1_RX_PRIORITY, UART1_TX_PRIORITY, UART1_ER_PRIORITY,
		                           UART2_RX_PRIORITY, UART2_TX_PRIORITY, UART2_ER_PRIORITY, UART3_RX_PRIORITY, UART3_TX_PRIORITY, UART3_ER_PRIORITY};

/** UART中断服务函数地址 */
const void *UartIrqFuncPointer[12] = {&UART0_RX_IRQHandler, &UART0_TX_IRQHandler, &UART0_ER_IRQHandler,
									   &UART1_RX_IRQHandler, &UART1_TX_IRQHandler, &UART1_ER_IRQHandler,
									   &UART2_RX_IRQHandler, &UART2_TX_IRQHandler, &UART2_ER_IRQHandler,
									   &UART3_RX_IRQHandler, &UART3_TX_IRQHandler, &UART3_ER_IRQHandler,};

/*************************************************************************
*  函数名称：void UART0_RX_IRQHandler(void)
*  功能说明：UART0_RX_IRQHandler中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2020年3月30日
*  备    注：
*************************************************************************/
void UART0_RX_IRQHandler(void)
{
    char buf;
    static int num0;
	IfxAsclin_Asc_isrReceive(&g_UartConfig[0]);

	/* 用户代码 */
//	UART_PutChar(UART0, UART_GetChar(UART0));
	buf = UART_GetChar(UART0);
	if(buf != '\n')
	{
	    buffer_0[num0++] = buf;
	}else{
	    buffer_0[num0] = '\0';
	    num0 = 0;
	    UART_PutStr(UART0,buffer_0);
	}



}

void UART0_TX_IRQHandler(void)
{
	IfxAsclin_Asc_isrTransmit(&g_UartConfig[0]);

	/* 用户代码 */
}

void UART0_ER_IRQHandler(void)
{
	IfxAsclin_Asc_isrError(&g_UartConfig[0]);

	/* 用户代码 */

}

void UART1_RX_IRQHandler(void)
{
	IfxAsclin_Asc_isrReceive(&g_UartConfig[1]);

	/* 用户代码 */
	UART_PutChar(UART1, UART_GetChar(UART1));
}

void UART1_TX_IRQHandler(void)
{
	IfxAsclin_Asc_isrTransmit(&g_UartConfig[1]);

	/* 用户代码 */
}

void UART1_ER_IRQHandler(void)
{
	IfxAsclin_Asc_isrError(&g_UartConfig[1]);

	/* 用户代码 */
}

void UART2_RX_IRQHandler(void)
{
	IfxAsclin_Asc_isrReceive(&g_UartConfig[2]);

	/* 用户代码 */
	UART_PutChar(UART2, UART_GetChar(UART2));
}

void UART2_TX_IRQHandler(void)
{
	IfxAsclin_Asc_isrTransmit(&g_UartConfig[2]);

	/* 用户代码 */
}

void UART2_ER_IRQHandler(void)
{
	IfxAsclin_Asc_isrError(&g_UartConfig[2]);

	/* 用户代码 */
}

void UART3_RX_IRQHandler(void)
{
	IfxAsclin_Asc_isrReceive(&g_UartConfig[3]);

	/* 用户代码 */
	UART_PutChar(UART3, UART_GetChar(UART3));
}

void UART3_TX_IRQHandler(void)
{
	IfxAsclin_Asc_isrTransmit(&g_UartConfig[3]);

	/* 用户代码 */
}

void UART3_ER_IRQHandler(void)
{
	IfxAsclin_Asc_isrError(&g_UartConfig[3]);

	/* 用户代码 */
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
@函数名称：void UART_InitConfig(UART_TypeDef* UARTx,unsigned long baudrate,UART_TX_e tx_pin, UART_RX_erx_pin)
@功能说明：串口模块初始化
@参数说明：RxPin：串口接收管脚  TxPin：串口发送管脚  baudrate： 波特率
@函数返回：字节
@修改时间：2022/12/29
@调用方法：UART_InitConfig(USAR1,9600,UART1_TX_A9,UART1_RX_A10); //初始化串口1 波特率 115200
@备    注：无奇偶校验 1停止位 使用管脚
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void UART_InitConfig(UART_RX_t RxPin, UART_TX_t TxPin, unsigned long baudrate)
{
    int i,j;
    //关闭CPU中断
    IfxCpu_disableInterrupts();

    Ifx_P *portRx = PIN_GetModule(RxPin);
    uint8 pinIndexRx = PIN_GetIndex(RxPin);

    Ifx_P *portTx = PIN_GetModule(TxPin);
    uint8 pinIndexTx = PIN_GetIndex(TxPin);

    IfxAsclin_Rx_In  * IfxAsclin_Rx = NULL_PTR;
    IfxAsclin_Tx_Out * IfxAsclin_Tx = NULL_PTR;

    for( i = 0; i < IFXASCLIN_PINMAP_NUM_MODULES; i++)
    {
        for( j = 0; j < IFXASCLIN_PINMAP_RX_IN_NUM_ITEMS; j++)
        {
            if(IfxAsclin_Rx_In_pinTable[i][j] == NULL_PTR)
            {

            }
            else if((unsigned long)portRx == (unsigned long)(IfxAsclin_Rx_In_pinTable[i][j]->pin.port) && pinIndexRx == IfxAsclin_Rx_In_pinTable[i][j]->pin.pinIndex)
            {
                IfxAsclin_Rx = IfxAsclin_Rx_In_pinTable[i][j];
            }
        }
        for(j = 0; j < IFXASCLIN_PINMAP_TX_OUT_NUM_ITEMS; j++)
        {
            if(IfxAsclin_Tx_Out_pinTable[i][j] == NULL_PTR)
            {

            }
            else if((unsigned long)portTx == (unsigned long)(IfxAsclin_Tx_Out_pinTable[i][j]->pin.port) && pinIndexTx == IfxAsclin_Tx_Out_pinTable[i][j]->pin.pinIndex)
            {
                IfxAsclin_Tx = IfxAsclin_Tx_Out_pinTable[i][j];
            }
        }
    }
    if(IfxAsclin_Rx->module != IfxAsclin_Tx->module)
    {
#pragma warning 557         // 屏蔽警告
        while (1);          // 检查 RX和TX 是否为同一UART
#pragma warning default     // 打开警告
    }

    //新建串口配置结构体
    IfxAsclin_Asc_Config ascConfig;

    //初始化模块
    IfxAsclin_Asc_initModuleConfig(&ascConfig, IfxAsclin_Tx->module);
    if(RxPin == UART3_RX_P00_1)
    {
        /* Default values for baudrate */
        ascConfig.clockSource           = IfxAsclin_ClockSource_kernelClock;         /* kernel clock, fclc*/
        ascConfig.baudrate.prescaler    = 4;                                         /* default prescaler*/
        ascConfig.baudrate.baudrate     = 100000;                                    /* default baudrate (the fractional dividier setup will be calculated in initModule*/
        ascConfig.baudrate.oversampling = IfxAsclin_OversamplingFactor_8;            /* default oversampling factor*/

        /* Default Values for Bit Timings */
        ascConfig.bitTiming.medianFilter        = IfxAsclin_SamplesPerBit_three;       /* 每位一次采样*/
        ascConfig.bitTiming.samplePointPosition = IfxAsclin_SamplePointPosition_3;   /* 采样点位置为3*/
        /* Default Values for Frame Control */
        ascConfig.frame.idleDelay               = IfxAsclin_IdleDelay_0;             /* no idle delay*/
        ascConfig.frame.stopBit                 = IfxAsclin_StopBit_2;               /* one stop bit*/
        ascConfig.frame.frameMode               = IfxAsclin_FrameMode_asc;           /* ASC mode*/
        ascConfig.frame.shiftDir                = IfxAsclin_ShiftDirection_lsbFirst; /* shift diection LSB first*/
        ascConfig.frame.parityBit               = TRUE;                             /* disable parity*/
        ascConfig.frame.parityType              = IfxAsclin_ParityType_even;         /* even parity (if parity enabled)*/
        ascConfig.frame.dataLength              = IfxAsclin_DataLength_8;            /* number of bits per transfer 8*/

        /* Default Values for Fifo Control */
        ascConfig.fifo.inWidth              = IfxAsclin_TxFifoInletWidth_1;          /* 8-bit wide write*/
        ascConfig.fifo.outWidth             = IfxAsclin_RxFifoOutletWidth_1;         /* 8-bit wide read*/
        ascConfig.fifo.txFifoInterruptLevel = IfxAsclin_TxFifoInterruptLevel_0;      /* txFifoInterruptLevel = 0. optimised to write upto 16 bytes at a time */
        ascConfig.fifo.rxFifoInterruptLevel = IfxAsclin_RxFifoInterruptLevel_1;
        ascConfig.fifo.buffMode             = IfxAsclin_ReceiveBufferMode_rxFifo;    /* RxFIFO*/

        /* Default Values for Interrupt ascConfig */
        ascConfig.interrupt.rxPriority = UartIrqPriority[IfxAsclin_getIndex(IfxAsclin_Tx->module) * 3];
        ascConfig.interrupt.txPriority = UartIrqPriority[IfxAsclin_getIndex(IfxAsclin_Tx->module) * 3 + 1];
        ascConfig.interrupt.erPriority = UartIrqPriority[IfxAsclin_getIndex(IfxAsclin_Tx->module) * 3 + 2];
        ascConfig.interrupt.typeOfService = UartIrqVectabNum[IfxAsclin_getIndex(IfxAsclin_Tx->module)];

        /* Enable error flags */
        ascConfig.errorFlags.ALL = ~0;                                               /* all error flags enabled*/
        IfxAsclin_Asc_Pins pins =
        {
            NULL,                     IfxPort_InputMode_pullUp,        /* CTS pin not used */
            IfxAsclin_Rx,             IfxPort_InputMode_pullUp,        /* Rx pin */
            NULL,                     IfxPort_OutputMode_pushPull,     /* RTS pin not used */
            IfxAsclin_Tx,             IfxPort_OutputMode_pushPull,     /* Tx pin */
            IfxPort_PadDriver_cmosAutomotiveSpeed1
        };
        /* init pointers */
        ascConfig.pins        = &pins;                                         /* pins to null pointer*/
        ascConfig.txBuffer     = &s_AscTxBuffer[IfxAsclin_getIndex(IfxAsclin_Tx->module)][0];
        ascConfig.txBufferSize = ASC_TX_BUFFER_SIZE;
        ascConfig.rxBuffer     = &s_AscRxBuffer[IfxAsclin_getIndex(IfxAsclin_Tx->module)][0];
        ascConfig.rxBufferSize = ASC_RX_BUFFER_SIZE;

        IfxAsclin_Asc_initModule(&g_UartConfig[IfxAsclin_getIndex(IfxAsclin_Tx->module)], &ascConfig);
        IfxAsclin_Asc_initModuleConfig(&ascConfig, IfxAsclin_Tx->module);

        IfxCpu_Irq_installInterruptHandler((void*)UartIrqFuncPointer[IfxAsclin_getIndex(IfxAsclin_Tx->module) * 3],     UartIrqPriority[IfxAsclin_getIndex(IfxAsclin_Tx->module) * 3]);
        IfxCpu_Irq_installInterruptHandler((void*)UartIrqFuncPointer[IfxAsclin_getIndex(IfxAsclin_Tx->module) * 3 + 1], UartIrqPriority[IfxAsclin_getIndex(IfxAsclin_Tx->module) * 3 + 1]);
        IfxCpu_Irq_installInterruptHandler((void*)UartIrqFuncPointer[IfxAsclin_getIndex(IfxAsclin_Tx->module) * 3 + 2], UartIrqPriority[IfxAsclin_getIndex(IfxAsclin_Tx->module) * 3 + 2]);
    }
    else
    {
        ascConfig.baudrate.baudrate  = (float32)baudrate;        //波特率
        ascConfig.baudrate.prescaler    = 4;//数据帧模式
        ascConfig.baudrate.oversampling   = IfxAsclin_OversamplingFactor_8; //数据长度

        unsigned char uartNum = IfxAsclin_getIndex(IfxAsclin_Tx->module);

        //中断优先级配置
        ascConfig.interrupt.rxPriority = UartIrqPriority[uartNum * 3];
        ascConfig.interrupt.txPriority = UartIrqPriority[uartNum * 3 + 1];
        ascConfig.interrupt.erPriority = UartIrqPriority[uartNum * 3 + 2];
        ascConfig.interrupt.typeOfService = UartIrqVectabNum[uartNum];

        //接收和发送FIFO的配置
        ascConfig.txBuffer     = &s_AscTxBuffer[uartNum][0];
        ascConfig.txBufferSize = ASC_TX_BUFFER_SIZE;
        ascConfig.rxBuffer     = &s_AscRxBuffer[uartNum][0];
        ascConfig.rxBufferSize = ASC_RX_BUFFER_SIZE;

        IfxAsclin_Asc_Pins pins =
        {
            NULL,                     IfxPort_InputMode_pullUp,        /* CTS pin not used */
            IfxAsclin_Rx,             IfxPort_InputMode_pullUp,        /* Rx pin */
            NULL,                     IfxPort_OutputMode_pushPull,     /* RTS pin not used */
            IfxAsclin_Tx,             IfxPort_OutputMode_pushPull,     /* Tx pin */
            IfxPort_PadDriver_cmosAutomotiveSpeed1
        };
        ascConfig.pins = &pins;

        //调用上面结构体所预设的参数，完成模块的初始化
        IfxAsclin_Asc_initModule(&g_UartConfig[uartNum], &ascConfig);

        //接收，发送和错误中断配置
        IfxCpu_Irq_installInterruptHandler((void*)UartIrqFuncPointer[uartNum * 3],     UartIrqPriority[uartNum * 3]);
        IfxCpu_Irq_installInterruptHandler((void*)UartIrqFuncPointer[uartNum * 3 + 1], UartIrqPriority[uartNum * 3 + 1]);
        IfxCpu_Irq_installInterruptHandler((void*)UartIrqFuncPointer[uartNum * 3 + 2], UartIrqPriority[uartNum * 3 + 2]);
    }
    //开启CPU中断
    IfxCpu_enableInterrupts();
}
/*************************************************************************
*  函数名称：void UART_PutChar(UART_t  uratn, char ch)
*  功能说明：UART发送字节函数,使用前请先初始化对应串口
*  参数说明：uratn ： UART0 - UART3/ ch    ： 要打印的字符
*  函数返回：无
*  修改时间：2020年3月10日
*  备    注：UART_PutChar(UART0, 'a');  //打印字符a
*************************************************************************/
void UART_PutChar(UART_t  uratn, char ch)
{
	IfxAsclin_Asc_blockingWrite(&g_UartConfig[uratn], ch);
}

/*************************************************************************
*  函数名称：void UART_PutStr(UART_t  uratn, char *str)
*  功能说明：UART发送字符串函数(遇 NULL 停止发送),使用前请先初始化对应串口
*  参数说明：uratn ： UART0 - UART3/ str   ： 要打印的字符串地址
*  函数返回：无
*  修改时间：2020年3月10日
*  备    注：UART_PutStr(UART3, "123456789"); //发送9个字节
*************************************************************************/
void UART_PutStr(UART_t  uratn, char *str)
{
   while(*str)
    {
        UART_PutChar(uratn, *str++);
    }
}

/*************************************************************************
*  函数名称：void UART_PutBuff(UART_t  uratn, unsigned char *buff, unsigned long len)
*  功能说明：UART发送字节函数,使用前请先初始化对应串口
*  参数说明：
* @param    uratn ： UART0 - UART3
* @param    buff  ： 要打印的字符串地址
* @param    len   ： 要打印的长度
*  函数返回：无
*  修改时间：2020年3月10日
*  备    注：UART_PutBuff(UART4, "123456789",5);//实际发送5个字节‘1’‘2’‘3’‘4’‘5’
*************************************************************************/
void UART_PutBuff(UART_t  uratn, unsigned char *buff, unsigned long len)
{
    while(len--)
    {
        UART_PutChar(uratn, *buff);
        buff++;
    }
}

/*************************************************************************
*  函数名称：Ifx_SizeT UART_GetCount(UART_t  uratn)
*  功能说明：获取 接收缓冲区 存放当前接收数据个数
*  参数说明： uratn ： UART0 - UART3
*  函数返回：无
*  修改时间：2020年3月10日
*  备    注：
*************************************************************************/
uint8 UART_GetCount(UART_t  uratn)
{
	return (uint8)IfxAsclin_Asc_getReadCount(&g_UartConfig[uratn]);
}

/*************************************************************************
*  函数名称：char UART_GetChar(UART_t  uratn)
*  功能说明：UART读取字节 使用前请先初始化对应串口 调用前请确认有接收到数据 否则会等待数据到来
*  参数说明：uratn ： UART0 - UART3
*  函数返回：读取字节
*  修改时间：2020年3月10日
*  备    注：UART_GetChar(UART3); //接收一个字符
*************************************************************************/
char UART_GetChar(UART_t  uratn)
{
	uint8 data=0;
	Ifx_SizeT count = 1;

	/* 获取接收到的一个字节数据 注意如果没有接收到，会一直等待 */
	IfxAsclin_Asc_read(&g_UartConfig[uratn], &data, &count, TIME_INFINITE);

	return 	data;
}

/*************************************************************************
*  函数名称：char UART_GetBuff(UART_t  uratn, unsigned char *data, unsigned char len)
*  功能说明：接收一定长度字符 使用前请先初始化对应串口 调用前请确认有接收到数据 否则会接受失败
*  参数说明：uratn ： UART0 - UART3
*  函数返回：0:读取正常  其他 读取失败
*  修改时间：2020年3月10日
*  备    注：ART_GetChar(UART0, data, 10); //接收10个字符
*************************************************************************/
char UART_GetBuff(UART_t  uratn, unsigned char *data, unsigned char len)
{
	Ifx_SizeT count = len;

	if(UART_GetCount(uratn) < len)
	{
		return 1;  //判断当前接收到的数据数量 不够读取长度
	}

	/* 获取接收到数据  */
	IfxAsclin_Asc_read(&g_UartConfig[uratn], data, &count, TIME_INFINITE);
	return 	0;
}

/*******************************************************************************
* Function Name  : _write
* Description    : Support Printf Function 配合stdio.h
* Input          : *buf: UART send Data.
*                  size: Data length
* Return         : size: Data length
*******************************************************************************/
int _write(int fd, char *buf, int size)
{
  int i;

  for(i=0; i<size; i++)
  {
    UART_PutChar(UART0, *buf++);//用哪个UART口，就改为对应的端口即可
  }
  return size;
}

/*
  int _write(int fd, char *buf, int size)
{
  int i;

  for(i=0; i<size; i++)
  {
#if (DEBUG == DEBUG_UART1)
    while (USART_GetFlagStatus(UART1, USART_FLAG_TC) == RESET);
    UART_PutChar(UART1, *buf++);
#elif (DEBUG == DEBUG_UART2)
    while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
    UART_PutChar(USART2, *buf++);
#elif (DEBUG == DEBUG_UART3)
    while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
    UART_PutChar(USART3, *buf++);
#endif
  }

  return size;
}
*/








/////////////////////////////////////////////////////////////////////////////////////
