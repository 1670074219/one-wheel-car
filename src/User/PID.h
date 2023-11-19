/*
 * @Descripttion:
 * @version:
 * @Author: Dog_Eggs
 * @Date: 2020-06-04 11:34:40
 * @LastEditors: Dog_Eggs
 * @LastEditTime: 2020-07-05 22:31:31
 */
#ifndef __PID_H__
#define __PID_H__

#include "include.h"

#define RANGE_PROTECT(x,max,min) ((x)<(min) ? (min) : ( (x)>(max) ? (max):(x) ))

typedef struct
{
    float SumError;  //误差累计
    sint32 LastError;  //上一次误差
    sint32 PrevError;  //上上次误差
    sint32 LastData;  //上次数据
//    sint32 PrevData;  //上次数据
//    sint32 LastDeta;  //上次微分
//    sint32 Error_Threshold_L;  //误差低阈值
//    sint32 Error_Threshold_H;  //误差高阈值
    float P;
    float I;
    float D;
    float T;  //这里不是时间，而是对积分相进行限幅
} PID_t;

typedef struct
 {
    struct //角速度环
    {
        PID_t pid;
        float out;
    } Gyro;

     struct //角度环
     {
        PID_t pid;
         float out;
     } Angle;


     struct //速度环
     {
         PID_t pid;
         float out;
     } Speed;

 } Momentum_Wheel;

extern Momentum_Wheel M;
extern Momentum_Wheel X;
extern Momentum_Wheel T;

typedef enum
{
    PID_NONE = 0X00,                    //无
    D_ON_MEASURE = 0x01,            //微分先行
    D_FILTER = 0x02,                //微分低通滤波
    I_LIMIT = 0x04,                 //积分限幅
    TRAPEZOID_I = 0x10,             //梯形积分
    CHANGE_I_RATE = 0x20,           //变积分
}PID_set_e;

// PID创建
void PID_init(PID_t *tem_P,float p, float i, float d, float t);

//PID参数初始化
void PID_all_init(void);

// 自适应PID控制
sint32 PID_Adapt(PID_t *p, sint32 NowData, sint32 SetData);
sint32 PlacePID_Control(PID_t *p, float NowData, float SetData);

// 位置式PID控制
//sint32 PID_Realize(pPID_t p, sint32 NowData, sint32 SetData, uint8 PID_set);
float PID_Realize(PID_t *p, float NowData, float SetData);

// 增量式PID控制
float PID_Increase(PID_t *p, float NowData, float SetData);

#endif
