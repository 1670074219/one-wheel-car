/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【平    台】北京龙邱智能科技TC3xxxA核心板
【编    写】chiusir
【E-mail】chiusir@163.com
【软件版本】V1.1 版权所有，单位使用请先联系授权
【最后更新】2020年10月28日
【相关信息参考下列地址】
【网    站】http://www.lqist.cn
【淘宝店铺】http://longqiu.taobao.com
------------------------------------------------
【dev.env.】AURIX Development Studio1.4及以上版本
【Target 】 TC3xxxA
【Crystal】 20.000Mhz
【SYS PLL】 300MHz
________________________________________________________________
基于iLLD_1_0_1_11_0底层程序,

使用例程的时候，建议采用没有空格的英文路径，
除了RIF为TC3xxxA独有外，其它的代码兼容TC3xx
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#ifndef _LQ_INCLUDE_H_
#define _LQ_INCLUDE_H_

/////////////c标准库文件//////////////////////////////////////////////////
/****************************************************************************
 * 标准C库
 ****************************************************************************/
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

/*****************************************************************************
 * 官方底层库
 ****************************************************************************/
#include "Platform_Types.h"
#include <CompilerTasking.h>
#include <IfxCpu.h>
#include <IfxScuCcu.h>
#include <IfxScuWdt.h>
#include <IfxStm.h>
#include <IfxStm_reg.h>

/*****************************************************************************
 * 龙邱应用库
 ****************************************************************************/
#include "LQ_ADC_7Mic.h"
#include "LQ_Atom_Motor.h"
#include "LQ_CAMERA.h"
#include "LQ_CCU6_Timer.h"
#include "LQ_EEPROM_TEST.h"
#include "LQ_FFT_TEST.h"
#include "LQ_GPIO_ExInt.h"
#include "LQ_GPIO_KEY.h"
#include "LQ_GPIO_LED.h"
#include "LQ_GPT_mini512.h"
#include "LQ_I2C_9AX.h"
#include "LQ_I2C_VL53.h"
#include "LQ_ICM20602.h"
#include "LQ_IIC_Gyro.h"
#include "LQ_MPU6050_DMP.h"
#include "LQ_MT9V034.h"
#include "LQ_OLED096.h"
#include "LQ_RDA5807.h"
#include "LQ_STM_Timer.h"
#include "LQ_TFT18.h"
#include "LQ_TFT2.h"
#include "LQ_TFTPicFont.h"
#include "LQ_Tim_InputCature.h"
#include "LQ_Tom_Servo.h"
#include "LQ_UART_Bluetooth.h"

/*****************************************************************************
 * 龙邱驱动库
 ****************************************************************************/
#include "LQ_ADC.h"
#include "LQ_CCU6.h"
#include "LQ_DMA.h"
#include "LQ_EEPROM.h"
#include "LQ_GPIO.h"
#include "LQ_GPSR.h"
#include "LQ_GPT12_ENC.h"
#include "LQ_GTM.h"
#include "LQ_QSPI.h"
#include "LQ_SOFTI2C.h"
#include "LQ_SPI.h"
#include "LQ_STM.h"
#include "LQ_UART.h"

/*****************************************************************************
 * 龙邱用户库
 ****************************************************************************/
#include "LQ_AnoScope.h"
#include "LQ_Inductor.h"
#include "LQ_MotorServo.h"
#include "LQ_PID.h"
#include "ConfigurationIsr.h"
#include "Ifx_Cfg.h"
#include "Main.h"

#include "Ano_DT.h"
#include "PID.h"
#include "my_math.h"
#include "Loop.h"

#include "Image_process.h"
#include "Cirque.h"
#include "Cross.h"
#include "podao.h"
#include "Zhangai.h"
#include "image.h"
#include "Cheku.h"
#include "Duanlu.h"
#include <stddef.h>

#include "../User/menu.h"
#include "swj.h"
#include "vofa+.h"
////////////////////////////////////////////////////////////////////////////
typedef struct
{
    float32 sysFreq;  //Actual SPB frequency
    float32 cpuFreq;  //Actual CPU frequency
    float32 pllFreq;  //Actual PLL frequency
    float32 stmFreq;  //Actual STM frequency
} AppInfo;

// Application information
typedef struct
{
    AppInfo info;     //Info object
} App_Cpu0;

#define Bin_Image Pixle
#endif




