/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL                               //�����Դ� δʹ��
 ��ƽ    ̨�������������ܿƼ�TC264DA���İ�
 ����    д��chiusir
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
 ʹ�����̵�ʱ�򣬽������û�����ļ��ո��Ӣ��·����
 ����CIFΪTC264DA�����⣬�����Ĵ������TC264D
 QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#include "LQ_MotorServo.h"

#include <IfxGtm_PinMap.h>
#include <IfxPort.h>
#include <IfxPort_reg.h>
#include <Platform_Types.h>
#include <stdio.h>

#include "../APP/LQ_GPIO_KEY.h"
#include "../APP/LQ_GPIO_LED.h"
#include "../APP/LQ_TFT18.h"
#include "../Driver/LQ_GPIO.h"
#include "../Driver/LQ_GPT12_ENC.h"
#include "../Driver/LQ_GTM.h"
#include "../Driver/LQ_STM.h"
#include "../Driver/LQ_UART.h"



//#define USE7843or7971
#define USEDRV8701  //USEDRV8701 ʹ������ͬ������ģ�飬ѡ���Ӧ�ĺ궨��
//���Ƶ��
#define MOTOR_FREQUENCY    12500

//���PWM �궨��
#define MOTOR1_P          IfxGtm_ATOM0_6_TOUT42_P23_1_OUT
#define MOTOR1_N          IfxGtm_ATOM0_5_TOUT40_P32_4_OUT

#define MOTOR2_P          IfxGtm_ATOM0_0_TOUT53_P21_2_OUT
#define MOTOR2_N          IfxGtm_ATOM0_4_TOUT50_P22_3_OUT


#define MOTOR3_P          IfxGtm_ATOM0_7_TOUT64_P20_8_OUT
#define MOTOR3_N          IfxGtm_ATOM0_3_TOUT56_P21_5_OUT


#define MOTOR4_P          IfxGtm_ATOM0_2_TOUT55_P21_4_OUT
#define MOTOR4_N          IfxGtm_ATOM0_1_TOUT54_P21_3_OUT

#define ATOMSERVO1       IfxGtm_ATOM2_0_TOUT32_P33_10_OUT
#define ATOMSERVO2       IfxGtm_ATOM2_5_TOUT35_P33_13_OUT

/*************************************************************************
 *  �������ƣ�void MotorInit(void)
 *  ����˵�������PWM��ʼ��
 *  ����˵������
 *  �������أ���
 *  �޸�ʱ�䣺2020��4��1��
 *  ��    ע������2�����
 *************************************************************************/
void MotorInit (void)
{
    ATOM_PWM_InitConfig(MOTOR1_P, 0, MOTOR_FREQUENCY);
//    ATOM_PWM_InitConfig(MOTOR2_P, 0, MOTOR_FREQUENCY);
    ATOM_PWM_InitConfig(MOTOR3_P, 0, MOTOR_FREQUENCY);
    ATOM_PWM_InitConfig(MOTOR4_P, 0, MOTOR_FREQUENCY);

    PIN_InitConfig(P32_4, PIN_MODE_OUTPUT, 0);
//    PIN_InitConfig(P22_3, PIN_MODE_OUTPUT, 0);
    PIN_InitConfig(P21_5, PIN_MODE_OUTPUT, 0);
    PIN_InitConfig(P21_3, PIN_MODE_OUTPUT, 0);
}

/*************************************************************************
 *  �������ƣ�void EncInit (void)
 *  ����˵������������ʼ������
 *  ����˵������
 *  �������أ���
 *  �޸�ʱ�䣺2020��4��1��
 *  ��    ע������2��������
 *************************************************************************/
void EncInit (void)
{
    ENC_InitConfig(ENC6_InPut_P20_3, ENC6_Dir_P20_0);
    ENC_InitConfig(ENC4_InPut_P02_8, ENC4_Dir_P33_5);
    ENC_InitConfig(ENC5_InPut_P10_3, ENC5_Dir_P10_1);
}

/*************************************************************************
 *  �������ƣ�void MotorCtrl(float motor1, float motor2)
 *  ����˵�������ת�Ǻ���������С�����˷�Χ���ƣ���С
 *  ����˵����   @param    motor1   �� ���1ռ�ձ�
 @param    motor2   �� ���2ռ�ձ�
 *  �������أ���
 *  �޸�ʱ�䣺2020��4��1��
 *  ��    ע������2���������ͨ����ֻ��Ҫһ���������
 *************************************************************************/
#ifdef USE7843or7971
void MotorCtrl (sint32 motor1, sint32 motor2)
{
    if (motor1 > 0)
    {
        ATOM_PWM_SetDuty(MOTOR1_P, motor1, MOTOR_FREQUENCY);
        IfxPort_setPinLow(&MODULE_P32, 4);
    }
    else
    {
        ATOM_PWM_SetDuty(MOTOR1_P, 10000+motor1, MOTOR_FREQUENCY);
        IfxPort_setPinHigh(&MODULE_P32, 4);
    }

    if (motor2 > 0)
    {
        ATOM_PWM_SetDuty(MOTOR2_P, motor2, MOTOR_FREQUENCY);
        IfxPort_setPinLow(&MODULE_P22, 3);
    }
    else
    {
        ATOM_PWM_SetDuty(MOTOR2_P, 10000+motor2, MOTOR_FREQUENCY);
        IfxPort_setPinHigh(&MODULE_P22, 3);
    }
}

void MotorCtrl3W (sint32 motor1, sint32 motor2, sint32 motor3)
{
    if (motor1 > 0)
       {
           ATOM_PWM_SetDuty(MOTOR3_P, 10000-motor1, MOTOR_FREQUENCY);
           IfxPort_setPinLow(&MODULE_P21, 5);
       }
       else
       {
           ATOM_PWM_SetDuty(MOTOR3_P, (10000+motor1),  MOTOR_FREQUENCY);
           IfxPort_setPinHigh(&MODULE_P21, 5);
       }

       if (motor2 > 0)
       {
           ATOM_PWM_SetDuty(MOTOR4_P, 10000-motor2, MOTOR_FREQUENCY);
           IfxPort_setPinLow(&MODULE_P21, 3);
       }
       else
       {
           ATOM_PWM_SetDuty(MOTOR4_P, (10000+motor2), MOTOR_FREQUENCY);
           IfxPort_setPinHigh(&MODULE_P21, 3);
       }

       if(motor3>3000)motor3=3000;
       if(motor3<-3000)motor3=-3000;
       if (motor3 > 0)
       {
           ATOM_PWM_SetDuty(MOTOR1_P, motor3, MOTOR_FREQUENCY);
           IfxPort_setPinLow(&MODULE_P32, 4);
       }
       else
       {
           ATOM_PWM_SetDuty(MOTOR1_P, (10000+motor3), MOTOR_FREQUENCY);
           IfxPort_setPinHigh(&MODULE_P32, 4);
       }
}
void MotorCtrl4w(sint32 motor1, sint32 motor2,sint32 motor3, sint32 motor4)
{
    if (motor1 > 0)
       {
           ATOM_PWM_SetDuty(MOTOR1_P, motor1, MOTOR_FREQUENCY);
           IfxPort_setPinLow(&MODULE_P32, 4);
       }
       else
       {
           ATOM_PWM_SetDuty(MOTOR1_P, 10000+motor1, MOTOR_FREQUENCY);
           IfxPort_setPinHigh(&MODULE_P32, 4);
       }

    if (motor2 > 0)
       {
           ATOM_PWM_SetDuty(MOTOR2_P, motor2, MOTOR_FREQUENCY);
           IfxPort_setPinLow(&MODULE_P22, 3);
       }
       else
       {
           ATOM_PWM_SetDuty(MOTOR2_P, 10000+motor2, MOTOR_FREQUENCY);
           IfxPort_setPinHigh(&MODULE_P22, 3);
       }
    if (motor3 > 0)
       {
           ATOM_PWM_SetDuty(MOTOR3_P, motor3, MOTOR_FREQUENCY);
           IfxPort_setPinLow(&MODULE_P21, 5);
       }
       else
       {
           ATOM_PWM_SetDuty(MOTOR3_P, 10000+motor3, MOTOR_FREQUENCY);
           IfxPort_setPinHigh(&MODULE_P21, 5);
       }

       if (motor4 > 0)
       {
           ATOM_PWM_SetDuty(MOTOR4_P, motor4, MOTOR_FREQUENCY);
           IfxPort_setPinLow(&MODULE_P21, 3);
       }
       else
       {
           ATOM_PWM_SetDuty(MOTOR4_P, 10000+motor4, MOTOR_FREQUENCY);
           IfxPort_setPinHigh(&MODULE_P21, 3);
       }
}
#else   //USEDRV8701
void MotorCtrl(sint32 motor1, sint32 motor2)
{
    if (motor1 > 0)
           {
               ATOM_PWM_SetDuty(MOTOR1_P, 10000-motor1, MOTOR_FREQUENCY);
               IfxPort_setPinLow(&MODULE_P32, 4);
           }
           else
           {
               ATOM_PWM_SetDuty(MOTOR1_P, (10000+motor1),  MOTOR_FREQUENCY);
               IfxPort_setPinHigh(&MODULE_P32, 4);
           }

           if (motor2 > 0)
           {
               ATOM_PWM_SetDuty(MOTOR2_P, 10000-motor2, MOTOR_FREQUENCY);
               IfxPort_setPinLow(&MODULE_P22, 3);
           }
           else
           {
               ATOM_PWM_SetDuty(MOTOR2_P, (10000+motor2), MOTOR_FREQUENCY);
               IfxPort_setPinHigh(&MODULE_P22, 3);
           }
}
void MotorCtrl3W (sint32 motor1, sint32 motor2, sint32 motor3)
{
    if (motor1 > 0)
       {
           ATOM_PWM_SetDuty(MOTOR3_P, 10000-motor1, MOTOR_FREQUENCY);
           IfxPort_setPinLow(&MODULE_P21, 5);
       }
       else
       {
           ATOM_PWM_SetDuty(MOTOR3_P, (10000+motor1),  MOTOR_FREQUENCY);
           IfxPort_setPinHigh(&MODULE_P21, 5);
       }

       if (motor2 > 0)
       {
           ATOM_PWM_SetDuty(MOTOR4_P, 10000-motor2, MOTOR_FREQUENCY);
           IfxPort_setPinLow(&MODULE_P21, 3);
       }
       else
       {
           ATOM_PWM_SetDuty(MOTOR4_P, (10000+motor2), MOTOR_FREQUENCY);
           IfxPort_setPinHigh(&MODULE_P21, 3);
       }

       if(motor3>3000)motor3=3000;
       if(motor3<-3000)motor3=-3000;
       if (motor3 > 0)
       {
           ATOM_PWM_SetDuty(MOTOR1_P, motor3, MOTOR_FREQUENCY);
           IfxPort_setPinLow(&MODULE_P32, 4);
       }
       else
       {
           ATOM_PWM_SetDuty(MOTOR1_P, (0-motor3), MOTOR_FREQUENCY);
           IfxPort_setPinHigh(&MODULE_P32, 4);
       }
}

void MotorCtrl4w(sint32 motor1, sint32 motor2,sint32 motor3, sint32 motor4)
{
    if (motor1 > 0)
       {
           ATOM_PWM_SetDuty(MOTOR1_P, motor1, MOTOR_FREQUENCY);
           IfxPort_setPinLow(&MODULE_P32, 4);
       }
       else
       {
           ATOM_PWM_SetDuty(MOTOR1_P, (0-motor1),  MOTOR_FREQUENCY);
           IfxPort_setPinHigh(&MODULE_P32, 4);
       }

       if (motor2 > 0)
       {
           ATOM_PWM_SetDuty(MOTOR2_P, motor2, MOTOR_FREQUENCY);
           IfxPort_setPinLow(&MODULE_P22, 3);
       }
       else
       {
           ATOM_PWM_SetDuty(MOTOR2_P, (0-motor2), MOTOR_FREQUENCY);
           IfxPort_setPinHigh(&MODULE_P22, 3);
       }
    if (motor3 > 0)
       {
           ATOM_PWM_SetDuty(MOTOR3_P, motor3, MOTOR_FREQUENCY);
           IfxPort_setPinLow(&MODULE_P21, 5);
       }
       else
       {
           ATOM_PWM_SetDuty(MOTOR3_P, (0-motor3),  MOTOR_FREQUENCY);
           IfxPort_setPinHigh(&MODULE_P21, 5);
       }

       if (motor4 > 0)
       {
           ATOM_PWM_SetDuty(MOTOR4_P, motor4, MOTOR_FREQUENCY);
           IfxPort_setPinLow(&MODULE_P21, 3);
       }
       else
       {
           ATOM_PWM_SetDuty(MOTOR4_P, (0-motor4), MOTOR_FREQUENCY);
           IfxPort_setPinHigh(&MODULE_P21, 3);
       }
}


#endif
/*************************************************************************
 *  �������ƣ�TestMotor(void)
 *  ����˵�������Ա궨���PWM���Ƶ��
 *  ����˵������
 *  �������أ���
 *  �޸�ʱ�䣺2020��4��1��
 *  ��    ע������2�����
 ��ע�����ע�⣬һ��Ҫ�Զ����ǽ�������
 ʹ������ĸ��������̣�
 1.��ʹ�����ñ������ص�ѹ����ر�֤��ص�ѹ��7V���ϣ�������������Ӧ��
 2.�Ӻ�ĸ�嵽��������ź��߼���Դ�ߣ�
 3.�Ӻ������嵽����ĵ��ߣ�
 4.��д�������У�ȷ�����������ת���󣬿����������Դ���أ�
 5.����K0/K1ȷ�����ת���ٶȼ�����
 6.������ַ�ת������K2�����ص���ģʽ������ֱ�ӹر��������Դ��
 *************************************************************************/
void TestMotor (void)
{
    short duty = 1500;
    char txt[16];

    TFTSPI_CLS(u16BLUE);          //����
    TFTSPI_P8X16Str(2, 0, "LQ Motor Test", u16RED, u16BLUE);
    MotorInit();
    PIN_InitConfig(DIN, PIN_MODE_OUTPUT, 1);     //ɲ����
    DIN_OFF;                        //ɲ��

    while (1)
    {
        if (KEY_Read(KEY0) == 0)      //����KEY0����ռ�ձȼ�С
        {
            if (duty > -ATOM_PWM_MAX)
                duty -= 100;
        }
        if (KEY_Read(KEY2) == 0)      //����KEY2����ռ�ձȼӴ�
        {
            if (duty < ATOM_PWM_MAX)      //��ռ�ձ�Ϊ12500
                duty += 100;
        }
        if (KEY_Read(KEY1) == 0)      //����KEY1����ռ�ձ���ֵ
        {
            if(duty>0)
                duty = -1500;
            else
                duty = 1500;
            while(KEY_Read(KEY1) == 0);
        }
        if (KEY_Read(START) == 0)      //����start�� ������ֹͣ������
        {
            if(PIN_Read(DIN))
            {
                DIN_OFF;
            }else{
                DIN_ON;
            }
            while(KEY_Read(START) == 0);
        }

        MotorCtrl3W(duty,duty,duty);
        sprintf(txt, "PWM: %05d;", duty);
        TFTSPI_P8X16Str(0, 5, txt, u16WHITE, u16BLACK);       //�ַ�����ʾ
        UART_PutStr(UART0, txt);

        LED_Ctrl(LED0, RVS);       //��ƽ��ת,LED��˸
        delayms(200);              //��ʱ�ȴ�
    }
}
/*************************************************************************
 *  �������ƣ�void ServoInit(void)
 *  ����˵�������PWM��ʼ��
 *  ����˵������
 *  �������أ���
 *  �޸�ʱ�䣺2020��4��1��
 *  ��    ע������2�����
 *************************************************************************/
void ServoInit (void)
{
    ATOM_PWM_InitConfig(ATOMSERVO1, 760, 50);  //���Ƶ��Ϊ100HZ����ʼֵΪ1.5ms��ֵ
    ATOM_PWM_InitConfig(ATOMSERVO2, 760, 50);  //������۷�ΧΪ��0.5ms--2.5ms�������ʵ�ʱ������ΧС
}

/*************************************************************************
 *  �������ƣ�void ServoCtrl(uint32 duty)
 *  ����˵�������ת�Ǻ���������С�����˷�Χ���ƣ���С
 *  ����˵����short duty��ռ�ձ�
 *  �������أ���
 *  �޸�ʱ�䣺2020��4��1��
 *  ��    ע������2���������ͨ����ֻ��Ҫһ���������
 *************************************************************************/
void ServoCtrl (uint32 duty)
{
    if (duty >= Servo_Left_Max)                  //���Ʒ�ֵ
        duty = Servo_Left_Max;
    else if (duty <= Servo_Right_Min)            //���Ʒ�ֵ
        duty = Servo_Right_Min;

    ATOM_PWM_InitConfig(ATOMSERVO1, duty, 50);  //���Ƶ��Ϊ100HZ����ʼֵΪ1.5ms��ֵ
    ATOM_PWM_InitConfig(ATOMSERVO2, duty, 50);  //������۷�ΧΪ��0.5ms--2.5ms�������ʵ�ʱ������ΧС
}

/*************************************************************************
 *  �������ƣ�Test_Servo(void)
 *  ����˵�������PWM��ʼ�������Ա궨���PWM����SD5/S3010���
 *  ����˵������
 *  �������أ���
 *  �޸�ʱ�䣺2020��4��1��
 *  ��    ע������2�����
 ��ע�����ע�⣬һ��Ҫ�Զ����ǽ�������
 ʹ������ĸ��������̣�
 1.��ʹ�����ñ������ص�ѹ����ر�֤��ص�ѹ��7V���ϣ�������������Ӧ��
 2.Ȼ��ȷ����������ѹ��SD5�����5V���磬S3010��6-7V���磡����
 3.�Ѷ���Ķ���ȥ�����ö����������ת����
 4.��д�������У��ö��ת������ֵ���������û��Ӧ�ظ�1-2�������ߵ��������PWMƵ�ʼ�ռ�ձȣ����ܿ�Ϊ׼��
 5.����ܿغ�������ת�������֨֨�죬�Կ�ת������ʱ����װ�϶��̣�
 6.����K0/K1ȷ�����������ת�����ޣ�������������Ϊ�����޷���ֹ�����ת�ջ٣�
 *************************************************************************/
void TestServo (void)
{
    char txt[16] = "X:";
    signed short duty = Servo_Center_Mid;

    TFTSPI_CLS(u16BLUE);          //����
    TFTSPI_P8X16Str(2, 0, "LQ Servo Test", u16RED, u16BLUE);
    ServoInit();
    ServoCtrl(Servo_Center_Mid);      //��ֵ
    while (1)
    {
        if (!KEY_Read(KEY0))
        {
            if (duty > 10)  //��ֹduty��
            {
                duty -= 10;
            }
        }
        if (!KEY_Read(KEY1))
        {
            duty = Servo_Center_Mid;
        }
        if (!KEY_Read(KEY2))
        {
            duty += 10;
        }

        ATOM_PWM_SetDuty(ATOMSERVO2, duty, 50);
        ATOM_PWM_SetDuty(ATOMSERVO1, duty, 50);
        sprintf(txt, "Servo duty:%04d ", duty);
        TFTSPI_P8X16Str(1, 2, txt, u16BLACK, u16GREEN); //��ʾ����ʵ�����������Ա�������
        LED_Ctrl(LEDALL, RVS);        //�ĸ�LEDͬʱ��˸;
        delayms(100);
    }
}


/*************************************************************************
 *  �������ƣ�void TestEncoder(void)
 *  ����˵�������Գ���TFT1.8��ʾ
 *  ����˵������
 *  �������أ���
 *  �޸�ʱ�䣺2020��4��10��
 *  ��    ע��
 *************************************************************************/
void TestEncoder(void)
{
    char txt[32];

    TFTSPI_CLS(u16BLUE);   //��ɫ��Ļ
    TFTSPI_P8X16Str(0, 0, "Test Encoder", u16WHITE, u16BLACK);      //�ַ�����ʾ
    EncInit();
    while (1)
    {
        /* ��ȡ������ֵ */
        ECPULSE1 = ENC_GetCounter(ENC2_InPut_P33_7); //���� ĸ���ϱ�����1��С��ǰ��Ϊ��ֵ
        ECPULSE2 = ENC_GetCounter(ENC4_InPut_P02_8); //�ҵ�� ĸ���ϱ�����2��С��ǰ��Ϊ��ֵ

        sprintf(txt, "Enc1: %05d;", ECPULSE1);
        TFTSPI_P8X16Str(0, 3, txt, u16WHITE, u16BLACK);       //�ַ�����ʾ
        sprintf(txt, "Enc2: %05d;", ECPULSE2);
        TFTSPI_P8X16Str(0, 5, txt, u16WHITE, u16BLACK);       //�ַ�����ʾ

        LED_Ctrl(LED0, RVS);        //��ƽ��ת,LED��˸
        delayms(200);              //��ʱ�ȴ�
    }
}
