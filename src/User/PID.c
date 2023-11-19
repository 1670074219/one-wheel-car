/*
 * @Descripttion: PID鏂囦欢
 * @version:
 * @Author: Dog_Eggs
 * @Date: 2020-04-21 19:22:36
 * @LastEditors: Dog_Eggs
 * @LastEditTime: 2020-07-05 22:31:48
 */

#include "PID.h"

Momentum_Wheel M;
Momentum_Wheel X;
Momentum_Wheel T;

void PID_all_init(void)
{
    PID_init(&M.Gyro.pid, -29, -0.11, 0, 3000);
    PID_init(&M.Angle.pid, 128, 2.2, 6, 100);
    M_Velocity_Kp = 0.095;
    M_Velocity_Ki = 0.001;
    M_Velocity_out = 0;

    PID_init(&X.Gyro.pid, 1.44, 0.0192, 0, 3500);
    PID_init(&X.Angle.pid, 90, 2, 2, 100);
    X_Velocity_Kp = -0.1;
    X_Velocity_Ki = -0.00001;
    X_Velocity_out = 0;

    PID_init(&T.Gyro.pid, 12, 0, 0, 100);
    PID_init(&T.Angle.pid, 17, 0, 0, 100);
    T_Velocity_Kp = 0;
    T_Velocity_Ki = 0;
    T_Velocity_out = 0;
}

void PID_init(PID_t *tem_P,float p, float i, float d, float t)
{
    tem_P->LastData = 0;
    tem_P->LastError = 0;
    tem_P->PrevError = 0;
    tem_P->SumError = 0;

    tem_P->P = p;
    tem_P->I = i;
    tem_P->D = d;
    tem_P->T = t;
}


//位置式PID
float PID_Realize(PID_t *p, float NowData, float SetData)
{
    //当前误差，定义为寄存器变量，只能用于整型和字符型变量，提高运算速度
    float iError,   // 当前误差
          Realize;  // 最后得出的实际增量

    iError = SetData - NowData; // 计算当前误差
    p->SumError += p->I * iError;   // 误差积分
    p->SumError = RANGE_PROTECT(p->SumError, p->T, -(p->T));

    Realize = ( (p->P) * iError
                     + p->SumError
                     + p->D * (iError - p->LastError) );

    p->PrevError = p->LastError;    // 更新前次误差
    p->LastError = iError;          // 更新上次误差
    p->LastData  = NowData;         // 更新上次数据

    return Realize; // 返回实际值
}

/**
 * @brief:      增量式PID
 * @param       p: PID参数结构体指针
 * @param       NowData: 当前测量值
 * @param       SetData: 目标值
 * @return:     PID输出
 * @since:
 * @sample:     Duty = PID_Increase(Direct_PID, Speed, Speed_Set);
 */
float PID_Increase(PID_t *p, float NowData, float SetData)
{
    //当前误差，定义为寄存器变量，只能用于整型和字符型变量，提高运算速度
    float iError, //当前误差
        Increase; //最后得出的实际增量

    iError = SetData - NowData; // 计算当前误差

    Increase = (float)(p->P * (iError - p->LastError) + p->I * iError + p->D * (iError - (2 * p->LastError) + p->PrevError));

    p->PrevError = p->LastError; // 更新前次误差
    p->LastError = iError;       // 更新上次误差
    //p->LastData = NowData;       // 更新上次数据     //没用到

    return Increase; // 返回增量
}



// 位置式动态PID控制
sint32 PlacePID_Control(PID_t *p, float NowData, float SetData)
{
    //定义为寄存器变量，只能用于整型和字符型变量，提高运算速度
    float iError;   //当前误差
    float  Actual;  //最后得出的实际输出值
    float Kp;       //动态P

    iError = SetData - NowData; //计算当前误差
    p->SumError += iError * 0.01;
    if (p->SumError >= p->T)
    {
        p->SumError = p->T;
    }
    else if (p->SumError <= p->T)
    {
        p->SumError = -p->T;
    }
    //二次函数是为了达到 误差越大  反应越快 回复力越大 其中 KI值是误差为0时的P 也就是直道上的P值
    Kp = 1.0 * (iError * iError) / p->P + p->I; //P值与差值成二次函数关系，此处P和I不是PID参数，而是动态PID参数，要注意！！！

    Actual = Kp * iError
           + p->D * ((0.8 * iError + 0.2 * p->LastError) - p->LastError);//不完全微分

    p->LastError = iError;      //更新上次误差

    return Actual;
}
/**
 * @brief:      位置式动态PID
 * @param       p: PID参数结构体指针
 * @param       NowData: 当前测量值
 * @param       SetData: 目标值
 * @return:     PID输出
 * @since:
 * @sample:     Duty = PID_Adapt(Direct_PID, Speed, Speed_Set);
 */
sint32 PID_Adapt(PID_t *p, sint32 NowData, sint32 SetData)
{
    sint32 iError, //当前误差
        Actual;   //最后得出的实际输出值

    iError = SetData - NowData; //计算当前误差

    Actual = (sint32)(p->P * (iError * iError) //P值与差值成二次函数关系
                     + (p->I * 1)             //此处的I不是积分，而是动态参数的一个最小值
                     + (p->D) * (iError - p->LastError));

    p->LastError = iError; //更新上次误差

    return Actual;
}

/**
 * @brief:      位置式PID
 * @param       p: PID参数结构体指针
 * @param       NowData: 当前测量值
 * @param       SetData: 目标值
 * @param       PID_set:    PID内部功能控制
 *                          NONE = 0X00,                    //无
                            D_ON_MEASURE = 0x01,            //微分先行
                            D_FILTER = 0x02,                //微分低通滤波
                            TRAPEZOID_I = 0x04,             //梯形积分
                            CHANGE_I_RATE = 0x10,           //变积分
 * @return:     PID输出
 * @since:
 * @sample:     Duty = PID_Realize(Direct_PID, Speed, Speed_Set, D_ON_MEASURE | D_FILTER);
 */
// sint32 PID_Realize(pPID_t p, sint32 NowData, sint32 SetData, uint8 PID_set)
// {
//  //当前误差，定义为寄存器变量，只能用于整型和字符型变量，提高运算速度
//  sint32 iError, // 当前误差
//      Deta,     // 当前微分
//      Realize;  // 最后得出的实际增量
//
//  iError = SetData - NowData; // 计算当前误差
//
//  if ((PID_set & (D_ON_MEASURE | D_FILTER)) == 0) //普通微分
//  {
//      Deta = iError - p->LastError;
//  }
//  else
//  {
//      if (PID_set & D_ON_MEASURE != 0) //微分先行
//      {
//          Deta = NowData - p->LastData - p->LastData + p->PrevData; //只对测量值进行微分
//      }
//
//      if (PID_set & D_FILTER != 0) //微分低通滤波
//      {
//          Deta = (Deta + p->LastDeta) / 2;
//          p->LastDeta = Deta;
//      }
//  }
//
//  if ((PID_set & (TRAPEZOID_I + CHANGE_I_RATE)) == 0) //普通积分
//  {
//      p->SumError += p->I * iError; // 误差积分
//  }
//  else
//  {
//      if (PID_set & TRAPEZOID_I != 0) //梯形积分
//      {
//          p->SumError += p->I * (iError + p->LastError) / 2; // 误差积分
//      }
//      else if (PID_set & CHANGE_I_RATE != 0) //变积分
//      {
//          if (iError < p->Error_Threshold_L)
//          {
//              p->SumError += p->I * iError;
//          }
//          else if (iError < p->Error_Threshold_H)
//          {
//              p->SumError += p->I * iError / 2;
//          }
//      }
//  }
//
//  p->SumError = RANGE_PROTECT(p->SumError, -(p->T), p->T); //积分限幅
//
//  Realize = (sint32)((p->P) * iError + p->SumError + p->D * Deta);
//
//  p->PrevError = p->LastError; // 更新前次误差
//  p->LastError = iError;       // 更新上次误差
//  p->LastData = NowData;       // 更新上次数据
//  p->PrevData = p->LastData;   // 更新上上次数据
//
//  return Realize; // 返回实际值
// }
