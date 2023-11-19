/*
 * @Descripttion: PID文件
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


//λ��ʽPID
float PID_Realize(PID_t *p, float NowData, float SetData)
{
    //��ǰ������Ϊ�Ĵ���������ֻ���������ͺ��ַ��ͱ�������������ٶ�
    float iError,   // ��ǰ���
          Realize;  // ���ó���ʵ������

    iError = SetData - NowData; // ���㵱ǰ���
    p->SumError += p->I * iError;   // ������
    p->SumError = RANGE_PROTECT(p->SumError, p->T, -(p->T));

    Realize = ( (p->P) * iError
                     + p->SumError
                     + p->D * (iError - p->LastError) );

    p->PrevError = p->LastError;    // ����ǰ�����
    p->LastError = iError;          // �����ϴ����
    p->LastData  = NowData;         // �����ϴ�����

    return Realize; // ����ʵ��ֵ
}

/**
 * @brief:      ����ʽPID
 * @param       p: PID�����ṹ��ָ��
 * @param       NowData: ��ǰ����ֵ
 * @param       SetData: Ŀ��ֵ
 * @return:     PID���
 * @since:
 * @sample:     Duty = PID_Increase(Direct_PID, Speed, Speed_Set);
 */
float PID_Increase(PID_t *p, float NowData, float SetData)
{
    //��ǰ������Ϊ�Ĵ���������ֻ���������ͺ��ַ��ͱ�������������ٶ�
    float iError, //��ǰ���
        Increase; //���ó���ʵ������

    iError = SetData - NowData; // ���㵱ǰ���

    Increase = (float)(p->P * (iError - p->LastError) + p->I * iError + p->D * (iError - (2 * p->LastError) + p->PrevError));

    p->PrevError = p->LastError; // ����ǰ�����
    p->LastError = iError;       // �����ϴ����
    //p->LastData = NowData;       // �����ϴ�����     //û�õ�

    return Increase; // ��������
}



// λ��ʽ��̬PID����
sint32 PlacePID_Control(PID_t *p, float NowData, float SetData)
{
    //����Ϊ�Ĵ���������ֻ���������ͺ��ַ��ͱ�������������ٶ�
    float iError;   //��ǰ���
    float  Actual;  //���ó���ʵ�����ֵ
    float Kp;       //��̬P

    iError = SetData - NowData; //���㵱ǰ���
    p->SumError += iError * 0.01;
    if (p->SumError >= p->T)
    {
        p->SumError = p->T;
    }
    else if (p->SumError <= p->T)
    {
        p->SumError = -p->T;
    }
    //���κ�����Ϊ�˴ﵽ ���Խ��  ��ӦԽ�� �ظ���Խ�� ���� KIֵ�����Ϊ0ʱ��P Ҳ����ֱ���ϵ�Pֵ
    Kp = 1.0 * (iError * iError) / p->P + p->I; //Pֵ���ֵ�ɶ��κ�����ϵ���˴�P��I����PID���������Ƕ�̬PID������Ҫע�⣡����

    Actual = Kp * iError
           + p->D * ((0.8 * iError + 0.2 * p->LastError) - p->LastError);//����ȫ΢��

    p->LastError = iError;      //�����ϴ����

    return Actual;
}
/**
 * @brief:      λ��ʽ��̬PID
 * @param       p: PID�����ṹ��ָ��
 * @param       NowData: ��ǰ����ֵ
 * @param       SetData: Ŀ��ֵ
 * @return:     PID���
 * @since:
 * @sample:     Duty = PID_Adapt(Direct_PID, Speed, Speed_Set);
 */
sint32 PID_Adapt(PID_t *p, sint32 NowData, sint32 SetData)
{
    sint32 iError, //��ǰ���
        Actual;   //���ó���ʵ�����ֵ

    iError = SetData - NowData; //���㵱ǰ���

    Actual = (sint32)(p->P * (iError * iError) //Pֵ���ֵ�ɶ��κ�����ϵ
                     + (p->I * 1)             //�˴���I���ǻ��֣����Ƕ�̬������һ����Сֵ
                     + (p->D) * (iError - p->LastError));

    p->LastError = iError; //�����ϴ����

    return Actual;
}

/**
 * @brief:      λ��ʽPID
 * @param       p: PID�����ṹ��ָ��
 * @param       NowData: ��ǰ����ֵ
 * @param       SetData: Ŀ��ֵ
 * @param       PID_set:    PID�ڲ����ܿ���
 *                          NONE = 0X00,                    //��
                            D_ON_MEASURE = 0x01,            //΢������
                            D_FILTER = 0x02,                //΢�ֵ�ͨ�˲�
                            TRAPEZOID_I = 0x04,             //���λ���
                            CHANGE_I_RATE = 0x10,           //�����
 * @return:     PID���
 * @since:
 * @sample:     Duty = PID_Realize(Direct_PID, Speed, Speed_Set, D_ON_MEASURE | D_FILTER);
 */
// sint32 PID_Realize(pPID_t p, sint32 NowData, sint32 SetData, uint8 PID_set)
// {
//  //��ǰ������Ϊ�Ĵ���������ֻ���������ͺ��ַ��ͱ�������������ٶ�
//  sint32 iError, // ��ǰ���
//      Deta,     // ��ǰ΢��
//      Realize;  // ���ó���ʵ������
//
//  iError = SetData - NowData; // ���㵱ǰ���
//
//  if ((PID_set & (D_ON_MEASURE | D_FILTER)) == 0) //��ͨ΢��
//  {
//      Deta = iError - p->LastError;
//  }
//  else
//  {
//      if (PID_set & D_ON_MEASURE != 0) //΢������
//      {
//          Deta = NowData - p->LastData - p->LastData + p->PrevData; //ֻ�Բ���ֵ����΢��
//      }
//
//      if (PID_set & D_FILTER != 0) //΢�ֵ�ͨ�˲�
//      {
//          Deta = (Deta + p->LastDeta) / 2;
//          p->LastDeta = Deta;
//      }
//  }
//
//  if ((PID_set & (TRAPEZOID_I + CHANGE_I_RATE)) == 0) //��ͨ����
//  {
//      p->SumError += p->I * iError; // ������
//  }
//  else
//  {
//      if (PID_set & TRAPEZOID_I != 0) //���λ���
//      {
//          p->SumError += p->I * (iError + p->LastError) / 2; // ������
//      }
//      else if (PID_set & CHANGE_I_RATE != 0) //�����
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
//  p->SumError = RANGE_PROTECT(p->SumError, -(p->T), p->T); //�����޷�
//
//  Realize = (sint32)((p->P) * iError + p->SumError + p->D * Deta);
//
//  p->PrevError = p->LastError; // ����ǰ�����
//  p->LastError = iError;       // �����ϴ����
//  p->LastData = NowData;       // �����ϴ�����
//  p->PrevData = p->LastData;   // �������ϴ�����
//
//  return Realize; // ����ʵ��ֵ
// }
