/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
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
#ifndef SRC_APPSW_TRICORE_USER_LQ_MOTORCONTROL_H_
#define SRC_APPSW_TRICORE_USER_LQ_MOTORCONTROL_H_

#include "../../Libraries/iLLD/TC29B/Tricore/Cpu/Std/Platform_Types.h"

#define DIN P22_3
#define DIN_ON  PIN_Write(DIN, 1);         // ������ɲ���ߣ�
#define DIN_OFF PIN_Write(DIN, 0);         // ֹͣ��ɲ���ߣ�

#define Servo_Delta 150            //�������ת���Ĳ�ֵ�������ͺţ����˺Ͷ���۳��й�
#define Servo_Center_Mid 760      //���ֱ����ֵ��
#define Servo_Left_Max   (Servo_Center_Mid+Servo_Delta)      //�����ת����ֵ
#define Servo_Right_Min  (Servo_Center_Mid-Servo_Delta)      //�����ת����ֵ����ֵ��������÷�ʽ�йأ���ʽ

#include <stdint.h>
extern sint16 ECPULSE1;          //�ٶ�ȫ�ֱ���
extern sint16 ECPULSE2;          //�ٶ�ȫ�ֱ���
extern sint16 ECPULSE3;          //�ٶ�ȫ�ֱ���
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
