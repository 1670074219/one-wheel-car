/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨�������������ܿƼ�TC297TX���İ�
����    д��chiusir
��E-mail��chiusir@163.com
������汾��V1.1 ��Ȩ���У���λʹ��������ϵ��Ȩ
�������¡�2021��10��28��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://longqiu.taobao.com
------------------------------------------------
��dev.env.��AURIX Development Studio1.4�����ϰ汾
��Target �� TC297TX
��Crystal�� 20.000Mhz
��SYS PLL�� 300MHz*3
________________________________________________________________
����iLLD_1_0_1_11_0�ײ����,

ʹ�����̵�ʱ�򣬽������û�пո��Ӣ��·�����л�workspace����ǰ���������ļ��У�
����RIFΪTC3xxxA�����⣬�����Ĵ������TC3xx
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#include "include.h"


unsigned char buffer_0[ASC_RX_BUFFER_SIZE];     //����0���ջ���

//����ͨ�Žṹ��
IfxAsclin_Asc g_UartConfig[4];

static uint8 s_AscTxBuffer[4][ASC_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
static uint8 s_AscRxBuffer[4][ASC_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];

/* UART�ж� */
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


/** UART�ж�CPU��� */
const uint8 UartIrqVectabNum[4] = {UART0_VECTABNUM, UART1_VECTABNUM, UART2_VECTABNUM, UART3_VECTABNUM};

/** UART�ж����ȼ� */
const uint8 UartIrqPriority[12] = {UART0_RX_PRIORITY, UART0_TX_PRIORITY, UART0_ER_PRIORITY, UART1_RX_PRIORITY, UART1_TX_PRIORITY, UART1_ER_PRIORITY,
		                           UART2_RX_PRIORITY, UART2_TX_PRIORITY, UART2_ER_PRIORITY, UART3_RX_PRIORITY, UART3_TX_PRIORITY, UART3_ER_PRIORITY};

/** UART�жϷ�������ַ */
const void *UartIrqFuncPointer[12] = {&UART0_RX_IRQHandler, &UART0_TX_IRQHandler, &UART0_ER_IRQHandler,
									   &UART1_RX_IRQHandler, &UART1_TX_IRQHandler, &UART1_ER_IRQHandler,
									   &UART2_RX_IRQHandler, &UART2_TX_IRQHandler, &UART2_ER_IRQHandler,
									   &UART3_RX_IRQHandler, &UART3_TX_IRQHandler, &UART3_ER_IRQHandler,};

/*************************************************************************
*  �������ƣ�void UART0_RX_IRQHandler(void)
*  ����˵����UART0_RX_IRQHandler�жϷ�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��3��30��
*  ��    ע��
*************************************************************************/
void UART0_RX_IRQHandler(void)
{
    char buf;
    static int num0;
	IfxAsclin_Asc_isrReceive(&g_UartConfig[0]);

	/* �û����� */
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

	/* �û����� */
}

void UART0_ER_IRQHandler(void)
{
	IfxAsclin_Asc_isrError(&g_UartConfig[0]);

	/* �û����� */

}

void UART1_RX_IRQHandler(void)
{
	IfxAsclin_Asc_isrReceive(&g_UartConfig[1]);

	/* �û����� */
	UART_PutChar(UART1, UART_GetChar(UART1));
}

void UART1_TX_IRQHandler(void)
{
	IfxAsclin_Asc_isrTransmit(&g_UartConfig[1]);

	/* �û����� */
}

void UART1_ER_IRQHandler(void)
{
	IfxAsclin_Asc_isrError(&g_UartConfig[1]);

	/* �û����� */
}

void UART2_RX_IRQHandler(void)
{
	IfxAsclin_Asc_isrReceive(&g_UartConfig[2]);

	/* �û����� */
	UART_PutChar(UART2, UART_GetChar(UART2));
}

void UART2_TX_IRQHandler(void)
{
	IfxAsclin_Asc_isrTransmit(&g_UartConfig[2]);

	/* �û����� */
}

void UART2_ER_IRQHandler(void)
{
	IfxAsclin_Asc_isrError(&g_UartConfig[2]);

	/* �û����� */
}

void UART3_RX_IRQHandler(void)
{
	IfxAsclin_Asc_isrReceive(&g_UartConfig[3]);

	/* �û����� */
	UART_PutChar(UART3, UART_GetChar(UART3));
}

void UART3_TX_IRQHandler(void)
{
	IfxAsclin_Asc_isrTransmit(&g_UartConfig[3]);

	/* �û����� */
}

void UART3_ER_IRQHandler(void)
{
	IfxAsclin_Asc_isrError(&g_UartConfig[3]);

	/* �û����� */
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
@�������ƣ�void UART_InitConfig(UART_TypeDef* UARTx,unsigned long baudrate,UART_TX_e tx_pin, UART_RX_erx_pin)
@����˵��������ģ���ʼ��
@����˵����RxPin�����ڽ��չܽ�  TxPin�����ڷ��͹ܽ�  baudrate�� ������
@�������أ��ֽ�
@�޸�ʱ�䣺2022/12/29
@���÷�����UART_InitConfig(USAR1,9600,UART1_TX_A9,UART1_RX_A10); //��ʼ������1 ������ 115200
@��    ע������żУ�� 1ֹͣλ ʹ�ùܽ�
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void UART_InitConfig(UART_RX_t RxPin, UART_TX_t TxPin, unsigned long baudrate)
{
    int i,j;
    //�ر�CPU�ж�
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
#pragma warning 557         // ���ξ���
        while (1);          // ��� RX��TX �Ƿ�ΪͬһUART
#pragma warning default     // �򿪾���
    }

    //�½��������ýṹ��
    IfxAsclin_Asc_Config ascConfig;

    //��ʼ��ģ��
    IfxAsclin_Asc_initModuleConfig(&ascConfig, IfxAsclin_Tx->module);
    if(RxPin == UART3_RX_P00_1)
    {
        /* Default values for baudrate */
        ascConfig.clockSource           = IfxAsclin_ClockSource_kernelClock;         /* kernel clock, fclc*/
        ascConfig.baudrate.prescaler    = 4;                                         /* default prescaler*/
        ascConfig.baudrate.baudrate     = 100000;                                    /* default baudrate (the fractional dividier setup will be calculated in initModule*/
        ascConfig.baudrate.oversampling = IfxAsclin_OversamplingFactor_8;            /* default oversampling factor*/

        /* Default Values for Bit Timings */
        ascConfig.bitTiming.medianFilter        = IfxAsclin_SamplesPerBit_three;       /* ÿλһ�β���*/
        ascConfig.bitTiming.samplePointPosition = IfxAsclin_SamplePointPosition_3;   /* ������λ��Ϊ3*/
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
        ascConfig.baudrate.baudrate  = (float32)baudrate;        //������
        ascConfig.baudrate.prescaler    = 4;//����֡ģʽ
        ascConfig.baudrate.oversampling   = IfxAsclin_OversamplingFactor_8; //���ݳ���

        unsigned char uartNum = IfxAsclin_getIndex(IfxAsclin_Tx->module);

        //�ж����ȼ�����
        ascConfig.interrupt.rxPriority = UartIrqPriority[uartNum * 3];
        ascConfig.interrupt.txPriority = UartIrqPriority[uartNum * 3 + 1];
        ascConfig.interrupt.erPriority = UartIrqPriority[uartNum * 3 + 2];
        ascConfig.interrupt.typeOfService = UartIrqVectabNum[uartNum];

        //���պͷ���FIFO������
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

        //��������ṹ����Ԥ��Ĳ��������ģ��ĳ�ʼ��
        IfxAsclin_Asc_initModule(&g_UartConfig[uartNum], &ascConfig);

        //���գ����ͺʹ����ж�����
        IfxCpu_Irq_installInterruptHandler((void*)UartIrqFuncPointer[uartNum * 3],     UartIrqPriority[uartNum * 3]);
        IfxCpu_Irq_installInterruptHandler((void*)UartIrqFuncPointer[uartNum * 3 + 1], UartIrqPriority[uartNum * 3 + 1]);
        IfxCpu_Irq_installInterruptHandler((void*)UartIrqFuncPointer[uartNum * 3 + 2], UartIrqPriority[uartNum * 3 + 2]);
    }
    //����CPU�ж�
    IfxCpu_enableInterrupts();
}
/*************************************************************************
*  �������ƣ�void UART_PutChar(UART_t  uratn, char ch)
*  ����˵����UART�����ֽں���,ʹ��ǰ���ȳ�ʼ����Ӧ����
*  ����˵����uratn �� UART0 - UART3/ ch    �� Ҫ��ӡ���ַ�
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��UART_PutChar(UART0, 'a');  //��ӡ�ַ�a
*************************************************************************/
void UART_PutChar(UART_t  uratn, char ch)
{
	IfxAsclin_Asc_blockingWrite(&g_UartConfig[uratn], ch);
}

/*************************************************************************
*  �������ƣ�void UART_PutStr(UART_t  uratn, char *str)
*  ����˵����UART�����ַ�������(�� NULL ֹͣ����),ʹ��ǰ���ȳ�ʼ����Ӧ����
*  ����˵����uratn �� UART0 - UART3/ str   �� Ҫ��ӡ���ַ�����ַ
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��UART_PutStr(UART3, "123456789"); //����9���ֽ�
*************************************************************************/
void UART_PutStr(UART_t  uratn, char *str)
{
   while(*str)
    {
        UART_PutChar(uratn, *str++);
    }
}

/*************************************************************************
*  �������ƣ�void UART_PutBuff(UART_t  uratn, unsigned char *buff, unsigned long len)
*  ����˵����UART�����ֽں���,ʹ��ǰ���ȳ�ʼ����Ӧ����
*  ����˵����
* @param    uratn �� UART0 - UART3
* @param    buff  �� Ҫ��ӡ���ַ�����ַ
* @param    len   �� Ҫ��ӡ�ĳ���
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��UART_PutBuff(UART4, "123456789",5);//ʵ�ʷ���5���ֽڡ�1����2����3����4����5��
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
*  �������ƣ�Ifx_SizeT UART_GetCount(UART_t  uratn)
*  ����˵������ȡ ���ջ����� ��ŵ�ǰ�������ݸ���
*  ����˵���� uratn �� UART0 - UART3
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��
*************************************************************************/
uint8 UART_GetCount(UART_t  uratn)
{
	return (uint8)IfxAsclin_Asc_getReadCount(&g_UartConfig[uratn]);
}

/*************************************************************************
*  �������ƣ�char UART_GetChar(UART_t  uratn)
*  ����˵����UART��ȡ�ֽ� ʹ��ǰ���ȳ�ʼ����Ӧ���� ����ǰ��ȷ���н��յ����� �����ȴ����ݵ���
*  ����˵����uratn �� UART0 - UART3
*  �������أ���ȡ�ֽ�
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��UART_GetChar(UART3); //����һ���ַ�
*************************************************************************/
char UART_GetChar(UART_t  uratn)
{
	uint8 data=0;
	Ifx_SizeT count = 1;

	/* ��ȡ���յ���һ���ֽ����� ע�����û�н��յ�����һֱ�ȴ� */
	IfxAsclin_Asc_read(&g_UartConfig[uratn], &data, &count, TIME_INFINITE);

	return 	data;
}

/*************************************************************************
*  �������ƣ�char UART_GetBuff(UART_t  uratn, unsigned char *data, unsigned char len)
*  ����˵��������һ�������ַ� ʹ��ǰ���ȳ�ʼ����Ӧ���� ����ǰ��ȷ���н��յ����� ��������ʧ��
*  ����˵����uratn �� UART0 - UART3
*  �������أ�0:��ȡ����  ���� ��ȡʧ��
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��ART_GetChar(UART0, data, 10); //����10���ַ�
*************************************************************************/
char UART_GetBuff(UART_t  uratn, unsigned char *data, unsigned char len)
{
	Ifx_SizeT count = len;

	if(UART_GetCount(uratn) < len)
	{
		return 1;  //�жϵ�ǰ���յ����������� ������ȡ����
	}

	/* ��ȡ���յ�����  */
	IfxAsclin_Asc_read(&g_UartConfig[uratn], data, &count, TIME_INFINITE);
	return 	0;
}

/*******************************************************************************
* Function Name  : _write
* Description    : Support Printf Function ���stdio.h
* Input          : *buf: UART send Data.
*                  size: Data length
* Return         : size: Data length
*******************************************************************************/
int _write(int fd, char *buf, int size)
{
  int i;

  for(i=0; i<size; i++)
  {
    UART_PutChar(UART0, *buf++);//���ĸ�UART�ڣ��͸�Ϊ��Ӧ�Ķ˿ڼ���
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
