#ifndef __LOOP_H
#define __LOOP_H

#include "include.h"

extern float M_Med_Angle, X_Med_Angle;
extern float Start_Flag;
extern short Encoder_A,Encoder_B,Encoder_C;
extern float X_Velocity_Kp,X_Velocity_Ki,X_Velocity_out;
extern float M_Velocity_Kp,M_Velocity_Ki,M_Velocity_out;
extern float T_Velocity_Kp,T_Velocity_Ki,T_Velocity_out;
extern float speed;
extern float k_offset;
extern float Med_Angle;
extern float M_Left_PWM;
extern float M_Right_PWM;
extern int start1;

extern float x_axis,y_axis;
extern float angle_integral;
extern float yaw_predirect;

extern float Yaw_Start;
extern float x_axis_pre;
extern float y_axis_pre;

void Loop_2ms(void);//2ms 角速度环
void Loop_10ms(void);//10ms 角度环
void Loop_20ms(void);//20ms 速度环

#endif /*__LOOP_H*/
