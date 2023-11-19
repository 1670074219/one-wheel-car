/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
 ��ƽ    ̨�������������ܿƼ�TC264DA���İ�
 ����    д��ZYF/chiusir
 ��E-mail  ��chiusir@163.com
 ������汾��V1.1 ��Ȩ���У���λʹ��������ϵ��Ȩ
 �������¡�2020��10��28��
 �������Ϣ�ο����е�ַ��
 ����    վ��http://www.lqist.cn
 ���Ա����̡�http://longqiu.taobao.com
 ------------------------------------------------
 ��dev.env.��AURIX Development Studio1.2.2�����ϰ汾
 ��Target �� TC264DA/TC264D
 ��Crystal�� 20.000Mhz
 ��SYS PLL�� 200MHz
 ________________________________________________________________
 ����iLLD_1_0_1_11_0�ײ����,

 ʹ�����̵�ʱ�򣬽������û�пո��Ӣ��·����
 ����CIFΪTC264DA�����⣬�����Ĵ������TC264D
 ����Ĭ�ϳ�ʼ����EMEM��512K������û�ʹ��TC264D��ע�͵�EMEM_InitConfig()��ʼ��������
 ������\Libraries\iLLD\TC26B\Tricore\Cpu\CStart\IfxCpu_CStart0.c��164�����ҡ�
 QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ
 *  ��    ע��TC264ֻ��15���̶���GPIO֧���ⲿ�ж� ��15���̶�GPIO��Ϊ4�飬ÿ��ֻ��ѡ������һ����Ϊ�ⲿ�жϹܽ�ʹ��
 *           0��P15_4  P33_7  P15_5                             1��P14_3  P15_8
 *           2��P10_2  P02_1  P00_4  P20_0  P11_10              3��P10_3  P14_1  P02_0  P20_9  P15_1
 *			�ⲿ�жϷ�������LQ_GPIO.c��  �ж����ȼ�������LQ_GPIO.h�� ���������޸�
 QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#ifndef _LQ_GPIO_H_
#define _LQ_GPIO_H_

#include "../../Libraries/iLLD/TC29B/Tricore/Cpu/Std/Platform_Types.h"
#include "../../Libraries/iLLD/TC29B/Tricore/Port/Std/IfxPort.h"

// GPIO ö�ٶ˿ڱ�ţ��ο�TC297datasheet���£�2021��10��28��
// UART ��סUART��ҲҪ�޸�
typedef enum //
{
    P00_0 = 0xA000,
    P00_1 = 0xA001,
    P00_2 = 0xA002,
    P00_3 = 0xA003,
    P00_4 = 0xA004,
    P00_5 = 0xA005,
    P00_6 = 0xA006,
    P00_7 = 0xA007,
    P00_8 = 0xA008,
    P00_9 = 0xA009,
    P00_10 = 0xA00A,
    P00_11 = 0xA00B,
    P00_12 = 0xA00C,

    P01_3 = 0xA103,
    P01_4 = 0xA104,
    P01_5 = 0xA105,
    P01_6 = 0xA106,
    P01_7 = 0xA107,

    P02_0 = 0xA200,
    P02_1 = 0xA201,
    P02_2 = 0xA202,
    P02_3 = 0xA203,
    P02_4 = 0xA204,
    P02_5 = 0xA205,
    P02_6 = 0xA206,
    P02_7 = 0xA207,
    P02_8 = 0xA208,
    P02_9 = 0xA209,
    P02_10 = 0xA20A,
    P02_11 = 0xA20B,

    P10_0 = 0xB000,
    P10_1 = 0xB001,
    P10_2 = 0xB002,
    P10_3 = 0xB003,
    P10_4 = 0xB004,
    P10_5 = 0xB005,
    P10_6 = 0xB006,
    P10_7 = 0xB007,
    P10_8 = 0xB008,

    P11_0 = 0xB100,
    P11_1 = 0xB101,
    P11_2 = 0xB102,
    P11_3 = 0xB103,
    P11_4 = 0xB104,
    P11_5 = 0xB105,
    P11_6 = 0xB106,
    P11_7 = 0xB107,
    P11_8 = 0xB108,
    P11_9 = 0xB109,
    P11_10 = 0xB10A,
    P11_11 = 0xB10B,
    P11_12 = 0xB10C,
    P11_13 = 0xB10D,
    P11_14 = 0xB10E,
    P11_15 = 0xB10F,

    P12_0 = 0xB200,
    P12_1 = 0xB201,
    P13_0 = 0xB300,
    P13_1 = 0xB301,
    P13_2 = 0xB302,
    P13_3 = 0xB303,

    P14_0 = 0xB400,
    P14_1 = 0xB401,
    P14_2 = 0xB402,
    P14_3 = 0xB403,
    P14_4 = 0xB404,
    P14_5 = 0xB405,
    P14_6 = 0xB406,
    P14_7 = 0xB407,
    P14_8 = 0xB408,
    P14_9 = 0xB409,
    P14_10 = 0xB40A,

    P15_0 = 0xB500,
    P15_1 = 0xB501,
    P15_2 = 0xB502,
    P15_3 = 0xB503,
    P15_4 = 0xB504,
    P15_5 = 0xB505,
    P15_6 = 0xB506,
    P15_7 = 0xB507,
    P15_8 = 0xB508,

    P20_0 = 0xC000,
    P20_1 = 0xC001,
    P20_2 = 0xC002,
    P20_3 = 0xC003,
    P20_4 = 0xC004,
    P20_5 = 0xC005,
    P20_6 = 0xC006,
    P20_7 = 0xC007,
    P20_8 = 0xC008,
    P20_9 = 0xC009,
    P20_10 = 0xC00A,
    P20_11 = 0xC00B,
    P20_12 = 0xC00C,
    P20_13 = 0xC00D,
    P20_14 = 0xC00E,

    P21_0 = 0xC100,
    P21_1 = 0xC101,
    P21_2 = 0xC102,
    P21_3 = 0xC103,
    P21_4 = 0xC104,
    P21_5 = 0xC105,
    P21_6 = 0xC106,
    P21_7 = 0xC107,

    P22_0 = 0xC200,
    P22_1 = 0xC201,
    P22_2 = 0xC202,
    P22_3 = 0xC203,
    P22_4 = 0xC204,
    P22_5 = 0xC205,
    P22_6 = 0xC206,
    P22_7 = 0xC207,
    P22_8 = 0xC208,
    P22_9 = 0xC209,
    P22_10 = 0xC20A,
    P22_11 = 0xC20B,
    P22_12 = 0xC20C,

    P23_1 = 0xC301,
    P23_2 = 0xC302,
    P23_3 = 0xC303,
    P23_4 = 0xC304,
    P23_5 = 0xC305,
    P23_6 = 0xC306,
    P23_7 = 0xC307,

    P32_0 = 0xD200,
    P32_1 = 0xD201,
    P32_2 = 0xD202,
    P32_3 = 0xD203,
    P32_4 = 0xD204,
    P32_5 = 0xD205,
    P32_6 = 0xD206,
    P32_7 = 0xD207,

    P33_0 = 0xD300,
    P33_1 = 0xD301,
    P33_2 = 0xD302,
    P33_3 = 0xD303,
    P33_4 = 0xD304,
    P33_5 = 0xD305,
    P33_6 = 0xD306,
    P33_7 = 0xD307,
    P33_8 = 0xD308,
    P33_9 = 0xD309,
    P33_10 = 0xD30A,
    P33_11 = 0xD30B,
    P33_12 = 0xD30C,
    P33_13 = 0xD30D,
    P33_14 = 0xD30E,
    P33_15 = 0xD30F,

    P34_0 = 0xD400,
    P34_1 = 0xD401,
    P34_2 = 0xD402,
    P34_3 = 0xD403,
    P34_4 = 0xD404,
    P34_5 = 0xD405,

    P40_0 = 0xE000,
    P40_1 = 0xE001,
    P40_2 = 0xE002,
    P40_3 = 0xE003,
    P40_4 = 0xE004,
    P40_5 = 0xE005,
    P40_6 = 0xE006,
    P40_7 = 0xE007,
    P40_8 = 0xE008,
    P40_9 = 0xE009,
    P40_10 = 0xE00A,
    P40_11 = 0xE00B,
    P40_12 = 0xE00C,
    P40_13 = 0xE00D,
    P40_14 = 0xE00E,

} GPIO_Name_t;

/* ��ȡGPIO��Ӧ MODULE �궨��L */
#define PIN_GetModule(GPIO_NAME) (Ifx_P*)(0xF0030000u | (GPIO_NAME & 0xFF00))//TC297,��ͬ��Ƭ���ĵ�ַ���ܲ�ͬ

/* ��ȡGPIO��Ӧ �ܽ����к� �궨��Q */
#define PIN_GetIndex(GPIO_NAME)   (uint8)(GPIO_NAME & 0x000F)

/* GPIOģʽ */
#define PIN_MODE_OUTPUT          IfxPort_Mode_outputPushPullGeneral    /*!< �������  */
#define PIN_MODE_OUTPUT_OD       IfxPort_Mode_outputOpenDrainGeneral   /*!< ��©���  */
#define PIN_MODE_INPUT           IfxPort_Mode_inputNoPullDevice        /*!< ��������  */
#define PIN_MODE_INPUT_PULLUP    IfxPort_Mode_inputPullUp              /*!< ��������  */
#define PIN_MODE_INPUT_PULLDOWN  IfxPort_Mode_inputPullDown            /*!< ��������  */

/* GPIO �жϴ���ģʽ */
#define PIN_IRQ_MODE_RISING             IfxPort_InputMode_pullDown     /*!< �����أ������������ж� */
#define PIN_IRQ_MODE_FALLING            IfxPort_InputMode_pullUp       /*!< �½��أ������������ж� */
#define PIN_IRQ_MODE_RISING_FALLING     IfxPort_InputMode_noPullDevice /*!< ˫���أ���©�������ж� */


void PIN_InitConfig (GPIO_Name_t pin, IfxPort_Mode mode, uint8 output);
uint8 PIN_Read (GPIO_Name_t pin);
void PIN_Write (GPIO_Name_t pin, uint8 output);
void PIN_Dir (GPIO_Name_t pin, uint8 mode);
void PIN_Reverse (GPIO_Name_t pin);
void PIN_Exti (GPIO_Name_t pin, IfxPort_InputMode mode);
void PIN_ExtiEnable(GPIO_Name_t pin, boolean bool);

#endif /* 0_APPSW_TRICORE_APP_LQ_GPIO_H_ */
