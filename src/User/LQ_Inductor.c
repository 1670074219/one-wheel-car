/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL                             //�����Դ� δʹ��
��ƽ    ̨�������������ܿƼ�TC264DA���İ�
����    д��chiusir
��E-mail��chiusir@163.com
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
=================================================================
����������Ƶ��ַ��https://space.bilibili.com/95313236
=================================================================
ʹ��˵����
����ѧ��ʾ���������ڵ�����ֻ������ֳ���
������ԴΪ��
ģ�飺����TC264DA���İ塢����ĸ�塢˫·ȫ�ŵ��������˫��������TFT1.8��Ļ�����������·���ģ�飻
��ģ�����ֻ������־��ɣ�
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#include <IfxCcu6.h>
#include <IfxCpu.h>
#include <Platform_Types.h>
#include <stdio.h>

#include "../APP/LQ_GPIO_KEY.h"
#include "../APP/LQ_TFT18.h"
#include "../Driver/LQ_ADC.h"
#include "../Driver/LQ_GPT12_ENC.h"
#include "LQ_MotorServo.h"



#define  Kbat       2        //��ص�ѹ�Ե��ռ�ձȵ�Ӱ��ϵ��
#define  Kencoder   20       //�������ٶȶԵ��ռ�ձȵ�Ӱ��ϵ��
#define  Koffset    (6/5)    //�������ʶԵ��ռ�ձȵ�Ӱ��ϵ��

#define  MtTargetDuty  2000  //���ռ�ձ�ֵ�����ֵ��ʵ����Ҫ��ȥ��ص�ѹ�����������������ʣ��ﲻ����ֵ

sint16 TempAngle = 0;        //���ݵ��ƫ�������������ʱ���ֵ
sint16 LastAngle = 0;        //����������ǰ����Чƫ�Ʒ���

sint16 Loffset0 = 0, Loffset1 = 0, Loffset4 = 0, Loffset5 = 0;  //���ƫ����
sint16 LnowADC[6];           //��е�ǰADC��ֵ

sint16 ad_max[6] = {0, 0, 0, 0, 0, 0}; //�°��ӷŵ������궨���ֵ,�ᱻ����ˢ��
sint16 ad_min[6] = {5000, 5000, 5000, 5000, 5000, 5000}; //�°��Ӿ���Ҫ�궨��Сֵ,�ᱻ����ˢ��

sint16 MotorDuty1 = 500;      //�������ռ�ձ���ֵ
sint16 MotorDuty2 = 500;      //�������ռ�ձ���ֵ

sint16 ECPULSE1 = 0;          //�ٶ�ȫ�ֱ���
sint16 ECPULSE2 = 0;          //�ٶ�ȫ�ֱ���
sint16 ECPULSE3 = 0;          //�ٶ�ȫ�ֱ���
//��ʼ������
void InductorInit (void)
{
    ADC_InitConfig(ADC0, 1000000); //��ʼ��
    ADC_InitConfig(ADC1, 1000000); //��ʼ��
    ADC_InitConfig(ADC2, 1000000); //��ʼ��
    ADC_InitConfig(ADC3, 1000000); //��ʼ��
}

/*************************************************************************
 *  �������ƣ�void CCU61_CH0_IRQHandler (void)
 *  ����˵������ʱ��ȡ��������ֵ
 *  ����˵������
 *  �������أ���
 *  �޸�ʱ�䣺2020��10��10��
 *  ��    ע��
 *************************************************************************/
void CCU61_CH0_IRQHandlerXXX (void)//���ܸ�   LQ_CCU6.c�����ظ�����Ҫ�ĵ�һ��
{
    /* ����CPU�ж�  �����жϲ���Ƕ�� */
    IfxCpu_enableInterrupts();

    //����жϱ�־
    IfxCcu6_clearInterruptStatusFlag(&MODULE_CCU61, IfxCcu6_InterruptSource_t12PeriodMatch);

    /* �û����� */
    /* ��ȡ������ֵ */
    ECPULSE1 = ENC_GetCounter(ENC2_InPut_P33_7); //���� ĸ���ϱ�����1��С��ǰ��Ϊ��ֵ
    ECPULSE2 = ENC_GetCounter(ENC4_InPut_P02_8); //�ҵ�� ĸ���ϱ�����2��С��ǰ��Ϊ��ֵ
}

/*************************************************************************
 *  �������ƣ�void ElectroMagneticCar(void)
 *  ����˵������ų�˫������ٿ��ƣ��򵥵ķֶα��������㷨
 *  ����˵������
 *  �������أ���
 *  �޸�ʱ�䣺2020��10��28��
 *  ��    ע������2�����
 *************************************************************************/
void ElectroMagneticCar (void)
{
    uint16 batv=0;
    sint16 OffsetDelta = 0;
    char txt[30] = "X:";

    while (1)
    {
        LnowADC[0] = ADC_Read(ADC0);  //����1����У�ƽ���������ɼ�������е�ADֵ
        LnowADC[1] = ADC_Read(ADC1);  //����2����У���ֱ������
        LnowADC[4] = ADC_Read(ADC2);  //�Ҳ��2����У���ֱ������
        LnowADC[5] = ADC_Read(ADC3);  //�Ҳ��1����У�ƽ��������

        if (LnowADC[0] < ad_min[0])            ad_min[0] = LnowADC[0];     //ˢ����Сֵ
        else if (LnowADC[0] > ad_max[0])       ad_max[0] = LnowADC[0];     //ˢ�����ֵ
        if (LnowADC[1] < ad_min[1])            ad_min[1] = LnowADC[1];
        else if (LnowADC[1] > ad_max[1])       ad_max[1] = LnowADC[1];
        if (LnowADC[4] < ad_min[4])            ad_min[4] = LnowADC[4];
        else if (LnowADC[4] > ad_max[4])       ad_max[4] = LnowADC[4];
        if (LnowADC[5] < ad_min[5])            ad_min[5] = LnowADC[5];
        else if (LnowADC[5] > ad_max[5])       ad_max[5] = LnowADC[5];

        Loffset0 = (LnowADC[0] - ad_min[0]) * 100 / (ad_max[0] - ad_min[0]);     //��ƫ������һ����0--1000����
        Loffset1 = (LnowADC[1] - ad_min[1]) * 100 / (ad_max[1] - ad_min[1]);
        Loffset4 = (LnowADC[4] - ad_min[4]) * 100 / (ad_max[4] - ad_min[4]);
        Loffset5 = (LnowADC[5] - ad_min[5]) * 100 / (ad_max[5] - ad_min[5]);

        if ((Loffset1 < 20) && (Loffset4 < 20))     //����ֵ��С��20����Ÿ�Զ������������ֱ����ͼ���
        {
            if ((Loffset4 < 10) && (Loffset1 < 10)) //�����������ⲻ�����ֵʱ�����Ҫ����
            {
                if (LastAngle < 0)                  //�ϴ���ƫ�����ݳ������ǰ�����ƫ�뷽��������������
                {
                    TempAngle = Servo_Left_Max;     //���ݼ��������Ƕ�����������
                }
                else                                //�ϴ���ƫ�����ݳ������ǰ�����ƫ�뷽��������������
                {
                    TempAngle = Servo_Right_Min;    //���ݼ��������Ƕ�������Ҵ���
                }
            }
            else if (Loffset1 > Loffset4)           //��2���ֵ ���� ��2���ֵ
            {
                if (Loffset0 > Loffset5)            //���� ��1���ֵ ���� ��1���ֵ
                    TempAngle = Servo_Left_Max;     //С����ƫ�������
            }
            else if (Loffset4 > Loffset1)           //��2���ֵ С�� ��2���ֵ
            {
                if (Loffset0 < Loffset5)            //���� ��1���ֵ С�� ��1���ֵ
                    TempAngle = Servo_Right_Min;    //С����ƫ���Ҵ���
            }
        }
        else if ((Loffset1 > 20) && (Loffset4 > 20)) //С���������������м�
        {
            TempAngle = Servo_Center_Mid + (Loffset1 - Loffset4) * 3; //����ƫ������ֵС���ȴ�ǣ���ֱֹ��ҡ��
        }
        else                                         //С�����������������������Ҫ����ת��
        {
            TempAngle = Servo_Center_Mid + (Loffset1 - Loffset4) * 10; //һ�����ר����ƣ���ֵԽ��ת��Խ��
            LastAngle = TempAngle; //������Ч����������ƫ�Ʒ���
        }

        OffsetDelta = (Loffset1 - Loffset4);
        ServoCtrl(TempAngle);      //�����ǿ���
        MotorDuty1 = MtTargetDuty + ECPULSE1 - OffsetDelta * 3;   //�в��ٿ��ƣ���תƫ��Ϊ����������
        MotorDuty2 = MtTargetDuty - ECPULSE2 + OffsetDelta * 3;   //�в��ٿ��ƣ���תƫ��Ϊ�����Ҳ����
        MotorCtrl(MotorDuty1, MotorDuty2);//���ֵ������
        //MotorCtrl(MtTargetDuty-TempAngle*8/5, MtTargetDuty+TempAngle*8/5);//���ֳ����޶��

        if (KEY_Read(KEY2) == 0)   //����K2����ʾ������Ϣ���˴���Ҫ�϶�ʱ�䣬����������Ӧ��
        {
            //������Ϣ
            sprintf(txt, "%04d %04d %04d ", TempAngle, ECPULSE1, ECPULSE2);   //��ʾ����Ƕ���ֵ�����ռ�ձ���ֵ����������ֵ
            TFTSPI_P8X16Str(1, 0, txt, u16WHITE, u16BLUE);      //�ַ�����ʾ
            sprintf(txt, "%04d %04d %04d %04d", Loffset0, Loffset1, Loffset4, Loffset5); //��ʾ����й�һ�����ƫ����
            TFTSPI_P6X8Str(1, 2, txt, u16WHITE, u16BLUE);        //�ַ�����ʾ
            //�궨��
            sprintf(txt, "%04d %04d %04d %04d", LnowADC[0] -ad_min[0], LnowADC[1] -ad_min[1], LnowADC[4] -ad_min[4], LnowADC[5] -ad_min[5]);      //��ʾ����в�ֵ
            TFTSPI_P6X8Str(1, 3, txt, u16WHITE, u16BLUE);        //�ַ�����ʾ
            sprintf(txt, "%04d %04d %04d %04d", LnowADC[0], LnowADC[1], LnowADC[4], LnowADC[5]);    //��ǰ����е�ѹֵ
            TFTSPI_P6X8Str(1, 4, txt, u16WHITE, u16BLUE);        //�ַ�����ʾ
            sprintf(txt, "%04d %04d %04d %04d", ad_min[0], ad_min[1], ad_min[4], ad_min[5]);        //����п�������ʷ��Сֵ
            TFTSPI_P6X8Str(1, 6, txt, u16WHITE, u16BLUE);        //�ַ�����ʾ
            sprintf(txt, "%04d %04d %04d %04d", ad_max[0], ad_max[1], ad_max[4], ad_max[5]);        //����п�������ʷ���ֵ
            TFTSPI_P6X8Str(1, 7, txt, u16WHITE, u16BLUE);        //�ַ�����ʾ
           // batv = ADC_Read(ADC7);  //ˢ�µ�ص�ѹ
            batv = batv * 11 / 25;  // x/4095*3.3*100*5.7
            sprintf(txt, "BAT:%d.%02dV ", batv / 100, batv % 100);  // *3.3/4095*3
            TFTSPI_P8X16Str(8, 5, txt, u16WHITE, u16BLUE);       //�ַ�����ʾ
        }
    }
}

