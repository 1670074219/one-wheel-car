/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
 【平    台】北京龙邱智能科技TC264DA核心板
 【编    写】chiusir
 【E-mail  】chiusir@163.com
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
 使用例程的时候，建议采用没有中文及空格的英文路径，
 除了CIF为TC264DA独有外，其它的代码兼容TC264D
 QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#ifndef SRC_APPSW_TRICORE_USER_LQ_MOTORCONTROL_H_
#define SRC_APPSW_TRICORE_USER_LQ_MOTORCONTROL_H_

#include "../../Libraries/iLLD/TC29B/Tricore/Cpu/Std/Platform_Types.h"

#define DIN P22_3
#define DIN_ON  PIN_Write(DIN, 1);         // 启动（刹车线）
#define DIN_OFF PIN_Write(DIN, 0);         // 停止（刹车线）

#define Servo_Delta 150            //舵机左右转动的差值，与舵机型号，拉杆和舵机臂长有关
#define Servo_Center_Mid 760      //舵机直行中值，
#define Servo_Left_Max   (Servo_Center_Mid+Servo_Delta)      //舵机左转极限值
#define Servo_Right_Min  (Servo_Center_Mid-Servo_Delta)      //舵机右转极限值，此值跟舵机放置方式有关，立式

#include <stdint.h>
extern sint16 ECPULSE1;          //速度全局变量
extern sint16 ECPULSE2;          //速度全局变量
extern sint16 ECPULSE3;          //速度全局变量
void EncInit(void);
void TestEncoder(void);

void MotorInit(void);
void MotorCtrl3W (sint32 motor1, sint32 motor2, sint32 motor3);
void TestMotor(void);
void MotorCtrl(sint32 motor1, sint32 motor2);
void ServoInit(void);
void ServoCtrl(uint32 duty);
void TestServo(void);
#endif /* SRC_APPSW_TRICORE_USER_LQ_MOTORCONTROL_H_ */
