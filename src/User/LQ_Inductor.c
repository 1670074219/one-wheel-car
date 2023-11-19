/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL                             //龙邱自带 未使用
【平    台】北京龙邱智能科技TC264DA核心板
【编    写】chiusir
【E-mail】chiusir@163.com
【软件版本】V1.1 版权所有，单位使用请先联系授权
【最后更新】2020年10月28日
【相关信息参考下列地址】
【网    站】http://www.lqist.cn
【淘宝店铺】http://longqiu.taobao.com
------------------------------------------------
【dev.env.】AURIX Development Studio1.2.2及以上版本
【Target 】 TC264DA/TC264D
【Crystal】 20.000Mhz
【SYS PLL】 200MHz
________________________________________________________________
基于iLLD_1_0_1_11_0底层程序,

使用例程的时候，建议采用没有空格的英文路径，
除了CIF为TC264DA独有外，其它的代码兼容TC264D
本库默认初始化了EMEM：512K，如果用户使用TC264D，注释掉EMEM_InitConfig()初始化函数。
工程下\Libraries\iLLD\TC26B\Tricore\Cpu\CStart\IfxCpu_CStart0.c第164行左右。
=================================================================
程序配套视频地址：https://space.bilibili.com/95313236
=================================================================
使用说明：
本教学演示程序适用于电磁四轮或者三轮车：
整车资源为：
模块：龙邱TC264DA核心板、配套母板、双路全桥电机驱动、双编码器、TFT1.8屏幕、单舵机、四路电感模块；
车模：三轮或者四轮均可；
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



#define  Kbat       2        //电池电压对电机占空比的影响系数
#define  Kencoder   20       //编码器速度对电机占空比的影响系数
#define  Koffset    (6/5)    //赛道曲率对电机占空比的影响系数

#define  MtTargetDuty  2000  //电机占空比值得最大值，实际需要减去电池电压，编码器，赛道曲率，达不到该值

sint16 TempAngle = 0;        //根据电感偏移量计算出的临时打角值
sint16 LastAngle = 0;        //记忆冲出赛道前的有效偏移方向

sint16 Loffset0 = 0, Loffset1 = 0, Loffset4 = 0, Loffset5 = 0;  //电感偏移量
sint16 LnowADC[6];           //电感当前ADC数值

sint16 ad_max[6] = {0, 0, 0, 0, 0, 0}; //新板子放到赛道标定最大值,会被程序刷新
sint16 ad_min[6] = {5000, 5000, 5000, 5000, 5000, 5000}; //新板子据需要标定最小值,会被程序刷新

sint16 MotorDuty1 = 500;      //电机驱动占空比数值
sint16 MotorDuty2 = 500;      //电机驱动占空比数值

sint16 ECPULSE1 = 0;          //速度全局变量
sint16 ECPULSE2 = 0;          //速度全局变量
sint16 ECPULSE3 = 0;          //速度全局变量
//初始化函数
void InductorInit (void)
{
    ADC_InitConfig(ADC0, 1000000); //初始化
    ADC_InitConfig(ADC1, 1000000); //初始化
    ADC_InitConfig(ADC2, 1000000); //初始化
    ADC_InitConfig(ADC3, 1000000); //初始化
}

/*************************************************************************
 *  函数名称：void CCU61_CH0_IRQHandler (void)
 *  功能说明：定时读取编码器数值
 *  参数说明：无
 *  函数返回：无
 *  修改时间：2020年10月10日
 *  备    注：
 *************************************************************************/
void CCU61_CH0_IRQHandlerXXX (void)//不能跟   LQ_CCU6.c里面重复，需要改掉一个
{
    /* 开启CPU中断  否则中断不可嵌套 */
    IfxCpu_enableInterrupts();

    //清除中断标志
    IfxCcu6_clearInterruptStatusFlag(&MODULE_CCU61, IfxCcu6_InterruptSource_t12PeriodMatch);

    /* 用户代码 */
    /* 获取编码器值 */
    ECPULSE1 = ENC_GetCounter(ENC2_InPut_P33_7); //左电机 母板上编码器1，小车前进为负值
    ECPULSE2 = ENC_GetCounter(ENC4_InPut_P02_8); //右电机 母板上编码器2，小车前进为正值
}

/*************************************************************************
 *  函数名称：void ElectroMagneticCar(void)
 *  功能说明：电磁车双电机差速控制，简单的分段比例控制算法
 *  参数说明：无
 *  函数返回：无
 *  修改时间：2020年10月28日
 *  备    注：驱动2个电机
 *************************************************************************/
void ElectroMagneticCar (void)
{
    uint16 batv=0;
    sint16 OffsetDelta = 0;
    char txt[30] = "X:";

    while (1)
    {
        LnowADC[0] = ADC_Read(ADC0);  //左侧第1个电感，平行赛道，采集各个电感的AD值
        LnowADC[1] = ADC_Read(ADC1);  //左侧第2个电感，垂直赛道，
        LnowADC[4] = ADC_Read(ADC2);  //右侧第2个电感，垂直赛道，
        LnowADC[5] = ADC_Read(ADC3);  //右侧第1个电感，平行赛道，

        if (LnowADC[0] < ad_min[0])            ad_min[0] = LnowADC[0];     //刷新最小值
        else if (LnowADC[0] > ad_max[0])       ad_max[0] = LnowADC[0];     //刷新最大值
        if (LnowADC[1] < ad_min[1])            ad_min[1] = LnowADC[1];
        else if (LnowADC[1] > ad_max[1])       ad_max[1] = LnowADC[1];
        if (LnowADC[4] < ad_min[4])            ad_min[4] = LnowADC[4];
        else if (LnowADC[4] > ad_max[4])       ad_max[4] = LnowADC[4];
        if (LnowADC[5] < ad_min[5])            ad_min[5] = LnowADC[5];
        else if (LnowADC[5] > ad_max[5])       ad_max[5] = LnowADC[5];

        Loffset0 = (LnowADC[0] - ad_min[0]) * 100 / (ad_max[0] - ad_min[0]);     //各偏移量归一化到0--1000以内
        Loffset1 = (LnowADC[1] - ad_min[1]) * 100 / (ad_max[1] - ad_min[1]);
        Loffset4 = (LnowADC[4] - ad_min[4]) * 100 / (ad_max[4] - ad_min[4]);
        Loffset5 = (LnowADC[5] - ad_min[5]) * 100 / (ad_max[5] - ad_min[5]);

        if ((Loffset1 < 20) && (Loffset4 < 20))     //两个值都小于20，电磁杆远离赛道，进入直角弯和急弯
        {
            if ((Loffset4 < 10) && (Loffset1 < 10)) //冲出赛道，检测不到电感值时舵机需要打死
            {
                if (LastAngle < 0)                  //上次右偏，根据冲出赛道前记忆的偏离方向打死舵机回赛道
                {
                    TempAngle = Servo_Left_Max;     //根据记忆参数打角舵机，向左打死
                }
                else                                //上次左偏，根据冲出赛道前记忆的偏离方向打死舵机回赛道
                {
                    TempAngle = Servo_Right_Min;    //根据记忆参数打角舵机，向右打死
                }
            }
            else if (Loffset1 > Loffset4)           //左2电感值 大于 右2电感值
            {
                if (Loffset0 > Loffset5)            //并且 左1电感值 大于 右1电感值
                    TempAngle = Servo_Left_Max;     //小车右偏，左打死
            }
            else if (Loffset4 > Loffset1)           //左2电感值 小于 右2电感值
            {
                if (Loffset0 < Loffset5)            //并且 左1电感值 小于 右1电感值
                    TempAngle = Servo_Right_Min;    //小车左偏，右打死
            }
        }
        else if ((Loffset1 > 20) && (Loffset4 > 20)) //小车行走于赛道上中间
        {
            TempAngle = Servo_Center_Mid + (Loffset1 - Loffset4) * 3; //根据偏移量差值小幅度打角，防止直道摇摆
        }
        else                                         //小车行走于赛道上弯道区域，需要控制转向
        {
            TempAngle = Servo_Center_Mid + (Loffset1 - Loffset4) * 10; //一般弯道专项控制，数值越大，转向越早
            LastAngle = TempAngle; //记忆有效参数，记忆偏移方向
        }

        OffsetDelta = (Loffset1 - Loffset4);
        ServoCtrl(TempAngle);      //舵机打角控制
        MotorDuty1 = MtTargetDuty + ECPULSE1 - OffsetDelta * 3;   //有差速控制，右转偏差为负，左侧加速
        MotorDuty2 = MtTargetDuty - ECPULSE2 + OffsetDelta * 3;   //有差速控制，左转偏差为正，右侧加速
        MotorCtrl(MotorDuty1, MotorDuty2);//四轮电机驱动
        //MotorCtrl(MtTargetDuty-TempAngle*8/5, MtTargetDuty+TempAngle*8/5);//三轮车，无舵机

        if (KEY_Read(KEY2) == 0)   //按键K2才显示赛道信息，此处需要较多时间，开启后舵机反应慢
        {
            //调试信息
            sprintf(txt, "%04d %04d %04d ", TempAngle, ECPULSE1, ECPULSE2);   //显示舵机角度数值，电机占空比数值，编码器数值
            TFTSPI_P8X16Str(1, 0, txt, u16WHITE, u16BLUE);      //字符串显示
            sprintf(txt, "%04d %04d %04d %04d", Loffset0, Loffset1, Loffset4, Loffset5); //显示各电感归一化后的偏移量
            TFTSPI_P6X8Str(1, 2, txt, u16WHITE, u16BLUE);        //字符串显示
            //标定用
            sprintf(txt, "%04d %04d %04d %04d", LnowADC[0] -ad_min[0], LnowADC[1] -ad_min[1], LnowADC[4] -ad_min[4], LnowADC[5] -ad_min[5]);      //显示各电感差值
            TFTSPI_P6X8Str(1, 3, txt, u16WHITE, u16BLUE);        //字符串显示
            sprintf(txt, "%04d %04d %04d %04d", LnowADC[0], LnowADC[1], LnowADC[4], LnowADC[5]);    //当前各电感电压值
            TFTSPI_P6X8Str(1, 4, txt, u16WHITE, u16BLUE);        //字符串显示
            sprintf(txt, "%04d %04d %04d %04d", ad_min[0], ad_min[1], ad_min[4], ad_min[5]);        //各电感开机后历史最小值
            TFTSPI_P6X8Str(1, 6, txt, u16WHITE, u16BLUE);        //字符串显示
            sprintf(txt, "%04d %04d %04d %04d", ad_max[0], ad_max[1], ad_max[4], ad_max[5]);        //各电感开机后历史最大值
            TFTSPI_P6X8Str(1, 7, txt, u16WHITE, u16BLUE);        //字符串显示
           // batv = ADC_Read(ADC7);  //刷新电池电压
            batv = batv * 11 / 25;  // x/4095*3.3*100*5.7
            sprintf(txt, "BAT:%d.%02dV ", batv / 100, batv % 100);  // *3.3/4095*3
            TFTSPI_P8X16Str(8, 5, txt, u16WHITE, u16BLUE);       //字符串显示
        }
    }
}

