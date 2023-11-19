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
    float SumError;  //����ۼ�
    sint32 LastError;  //��һ�����
    sint32 PrevError;  //���ϴ����
    sint32 LastData;  //�ϴ�����
//    sint32 PrevData;  //�ϴ�����
//    sint32 LastDeta;  //�ϴ�΢��
//    sint32 Error_Threshold_L;  //������ֵ
//    sint32 Error_Threshold_H;  //������ֵ
    float P;
    float I;
    float D;
    float T;  //���ﲻ��ʱ�䣬���ǶԻ���������޷�
} PID_t;

typedef struct
 {
    struct //���ٶȻ�
    {
        PID_t pid;
        float out;
    } Gyro;

     struct //�ǶȻ�
     {
        PID_t pid;
         float out;
     } Angle;


     struct //�ٶȻ�
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
    PID_NONE = 0X00,                    //��
    D_ON_MEASURE = 0x01,            //΢������
    D_FILTER = 0x02,                //΢�ֵ�ͨ�˲�
    I_LIMIT = 0x04,                 //�����޷�
    TRAPEZOID_I = 0x10,             //���λ���
    CHANGE_I_RATE = 0x20,           //�����
}PID_set_e;

// PID����
void PID_init(PID_t *tem_P,float p, float i, float d, float t);

//PID������ʼ��
void PID_all_init(void);

// ����ӦPID����
sint32 PID_Adapt(PID_t *p, sint32 NowData, sint32 SetData);
sint32 PlacePID_Control(PID_t *p, float NowData, float SetData);

// λ��ʽPID����
//sint32 PID_Realize(pPID_t p, sint32 NowData, sint32 SetData, uint8 PID_set);
float PID_Realize(PID_t *p, float NowData, float SetData);

// ����ʽPID����
float PID_Increase(PID_t *p, float NowData, float SetData);

#endif
