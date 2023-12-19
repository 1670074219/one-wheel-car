#include "Loop.h" //�߳�

/***************ƽ�����*******************/
float Start_Flag; //����λ
float Med_Angle = 0.1; //������ƽ�����
float M_Med_Angle = 1.6, X_Med_Angle = -0.1; //��ʼ��ƽ�����
short Encoder_A,Encoder_B,Encoder_C; //������ֵ
float M_Left_PWM = 0; //����������p��
float M_Right_PWM = 0; //����������p��
float k_offset = -0.08; //��̱���k
float speed = 140; //��ʼ�ٶ�

/***************�ٶ�ƽ������*******************/
float offset1; //�м���� ƫ�����ֵ
int start1=0; //�м���� ����
uint8 old_speed = 0,new_speed = 0,cur_speed = 0; //�м���� �ٶ�ƽ��

/***************���Ե�������*******************/
float x_axis = 0,y_axis = 0; //x y��ʼ����
float angle_integral = 0; //�ǶȻ��ֱ���
float angle_integral_rad = 0; //���Ȼ��ֱ���
float Yaw_Start = 0; //��ʼyaw��

/***************PID����*******************/
float X_Velocity_Kp = 0,X_Velocity_Ki = 0,X_Velocity_out = 0;
float M_Velocity_Kp = 0,M_Velocity_Ki = 0,M_Velocity_out = 0;
float T_Velocity_Kp = 0,T_Velocity_Ki = 0,T_Velocity_out = 0;

float X_Velocity(int encoder,float set);
float M_Velocity(int encoder,float set);
float T_Velocity(int encoder,float set);

void Loop_20ms()//20ms �ٶȻ�
{
    /***************�����ٶȻ���ʱ�� ��ֹ������ת*******************/
    if(Start_Flag==1 && start1 < 500)
        start1++;

    /***************ƫ�����ֵ*******************/
    offset1=offset;
    if(offset1<0)
        offset1=-offset1;
    /***************��ֱ���ٶ�ƽ��*******************/
    if(road_type.bend || road_type.straight)
    {
        new_speed = speed;

        if(new_speed-old_speed>1)
            new_speed=old_speed+1;
        if(new_speed-old_speed<-1)
            new_speed=old_speed-1;
        old_speed = new_speed;

        cur_speed=old_speed;
    }
    else
    {
        cur_speed = speed;
    }

    /***************Բ������ �ٶȻ�*******************/
    M_Velocity_out = M_Velocity((Encoder_A+Encoder_B),0);
    if((road_type.RightCirque && (2<=huandao_stage<=5 || huandao_stage==7)) || (road_type.LeftCirque&& (2<=huandao_stage<=5 || huandao_stage==7)))
        X_Velocity_out = X_Velocity(Encoder_C,cur_speed-offset1*0.12-8);
    else
        X_Velocity_out = X_Velocity(Encoder_C,cur_speed-offset1*0.12);

}

float Med_Angle_last;
float offset_last;
void Loop_10ms()//10ms
{
    /***************����ƽ�⶯̬���*******************/
    if(Encoder_C>120)
        Med_Angle = offset*k_offset +(offset-offset_last)*(-0.003)+ M_Med_Angle;
    else if(Encoder_C>100)
        Med_Angle = offset*(k_offset+0.01)+(offset-offset_last)*(-0.003) + M_Med_Angle;
    else if(Encoder_C>80)
        Med_Angle = offset*(k_offset+0.015)+(offset-offset_last)*(-0.003) + M_Med_Angle;
    else if(Encoder_C>60)
        Med_Angle = offset*(k_offset+0.02)+(offset-offset_last)*(-0.003) + M_Med_Angle;
    else
        Med_Angle = offset*(k_offset+0.05)+(offset-offset_last)*(-0.003) + M_Med_Angle;

    /***************��̬����޷�*******************/
    if((Med_Angle-Med_Angle_last>25))
    {
        Med_Angle=Med_Angle_last+25;
    }
    else if(Med_Angle-Med_Angle_last<-25)
    {
        Med_Angle=Med_Angle_last-25;
    }

    Med_Angle_last=Med_Angle;
    Med_Angle = fclip(Med_Angle, -25, 25);
    offset_last=offset;

    /***************�ǶȻ�*******************/
    M.Angle.out = PID_Realize(&M.Angle.pid, Pitch, (M_Velocity_out+Med_Angle));
    X.Angle.out = PID_Realize(&X.Angle.pid, Roll, (X_Velocity_out+X_Med_Angle));
    T.Angle.out = PID_Realize(&T.Angle.pid, offset, 0);
}

/***************����flag ���ֲ���*******************/
extern uint8 Duanlu_flag;
extern float Duanlu_angle;
extern uint8 huandao_flag;
extern float huandao_angle;
extern uint8 podao_flag;
extern uint16 podao_encoder;
extern uint8 zhangai_flag;
extern float zhangai_angle;
extern uint8 cheku_stage;
extern float cheku_out_encoder;
extern float cheku_out_angle;

uint8 start = 0; //ֹͣ��־

/***************���Ե�������*******************/
float yaw_predirect = 0; //yawת���Ƕ�
float x_axis_pre = 2500; //ǰһ��x����
float y_axis_pre = 738; //ǰһ��y����


void Loop_2ms()//2ms
{
    Encoder_A = ENC_GetCounter(ENC5_InPut_P10_3);   //���� ĸ���ϱ�����1��С��ǰ��Ϊ��ֵ
    Encoder_B = -ENC_GetCounter(ENC4_InPut_P02_8);  //�ҵ�� ĸ���ϱ�����2��С��ǰ��Ϊ��ֵ
    Encoder_C = -ENC_GetCounter(ENC6_InPut_P20_3);  //�н���� ĸ���ϱ�����3��С��ǰ��Ϊ��ֵ
    LQ_DMP_Read();                                  //��ȡ��̬��Ϣ

    /************************����****************************/
    if(huandao_flag)
        huandao_angle += (float)gyro[2]/16.4*0.002;

    if(cheku_sum_flag)
        cheku_angle += (float)gyro[2]/16.4*0.002;

    if(cross_turn_flag)
        cross_turn_angle += (float)gyro[2]/16.4*0.002;

    if(cross_flag)
        cross_s += Encoder_C;

    if(cheku_stage == 2)
        cheku_out_angle += (float)gyro[2]/16.4*0.002;

    if(zhangai_flag)
        zhangai_angle += (float)gyro[2]/16.4*0.002;

    if(Duanlu_flag)
        Duanlu_angle += (float)gyro[2]/16.4*0.002;

    if(podao_flag && Start_Flag == 1)
        podao_encoder += Encoder_C;

    if(cheku_stage == 1)
        cheku_out_encoder += Encoder_C;

    if(dont_handle_flag == 1)
        dont_handle_encoder += Encoder_C;

    if(Start_Flag)
    {
        /****************************************************************************�ߵ�����***********************************************************************/

        /***************ת���Ƕ�*******************/
        angle_integral = Yaw-Yaw_Start;

        /***************ת���Ƕ��޷�*******************/
        if(angle_integral > 180)
            angle_integral -= 360;
        else if(angle_integral < -180)
            angle_integral += 360;

        /***************ת���ǶȻ�����*******************/
        angle_integral_rad = angle_integral/57.3;

        /***************x y�������*******************/
        x_axis += cos(angle_integral_rad)*(Encoder_C / 50);
        y_axis += sin(angle_integral_rad)*(Encoder_C / 50);

        if(Duanlu_Flag1 == 1)
        {
            /***************����Ƕ�*******************/
            yaw_predirect = atan((y_axis - y_axis_pre)/(x_axis - x_axis_pre));

            /***************����Ƕ��޷�*******************/
            if(x_axis - x_axis_pre >= 0 && y_axis - y_axis_pre >= 0)
            {
                yaw_predirect *= 57.3;
                yaw_predirect -= 180;
            }
            else if(x_axis - x_axis_pre <= 0 && y_axis - y_axis_pre >= 0)
            {
                yaw_predirect *= 57.3;
            }
            else if(x_axis - x_axis_pre <= 0 && y_axis - y_axis_pre <= 0)
            {
                yaw_predirect *= 57.3;
            }
            else if(x_axis - x_axis_pre >= 0 && y_axis - y_axis_pre <= 0)
            {
                yaw_predirect *= 57.3;
                yaw_predirect += 180;
            }

            /***************����Ƕ� ת���Ƕ� ����ƫ��*******************/
            if((yaw_predirect >= 90 && yaw_predirect <= 180 && angle_integral <= -90 && angle_integral >= -180)||(yaw_predirect >= 0 && yaw_predirect <= 90 && angle_integral <= -90 && angle_integral >= -180))
            {
                offset = 360 - yaw_predirect - fabs(angle_integral);
                offset = fclip(offset, -130, 130);
            }
            else if(yaw_predirect <= -90 && yaw_predirect >= -180 && angle_integral >= 90 && angle_integral <= 180)
            {
                offset = -360 + angle_integral - yaw_predirect;
                offset = fclip(offset, -130, 130);
            }
            else
            {
                offset = angle_integral - yaw_predirect;
                offset = fclip(offset, -130, 130);
            }
        }
    }
    /************************���ٶȻ�****************************/
    M.Gyro.out = PID_Realize(&M.Gyro.pid, gyro[0], M.Angle.out);
    X.Gyro.out = PID_Realize(&X.Gyro.pid, gyro[1], X.Angle.out);
    T.Gyro.out = PID_Realize(&T.Gyro.pid, gyro[2], T.Angle.out);

    M_Left_PWM = M.Gyro.out;//+T.Gyro.out;
    M_Right_PWM = -M.Gyro.out;//+T.Gyro.out;

    M_Left_PWM = fclip(M_Left_PWM, -10000, 10000);                     //PWM�޷�
    M_Right_PWM = fclip(M_Right_PWM, -10000, 10000);                   //PWM�޷�
    X.Gyro.out = fclip(X.Gyro.out, -3500, 3500);                       //PWM�޷�
    if(fabs(Pitch)>35 || fabs(Roll)>30){Start_Flag=0;}                 //�����ض��Ƕ�ֹͣ����

    if((Start_Flag==1)&&(start == 0)) //����
    {
        DIN_ON;
        MotorCtrl3W((sint32)(M_Left_PWM),(sint32)(M_Right_PWM), (sint32)(X.Gyro.out));
    }
    else //ֹͣ
    {
        DIN_OFF;
        MotorCtrl3W(0,0,0);

        M.Gyro.pid.SumError = 0;
        X.Gyro.pid.SumError = 0;
        T.Gyro.pid.SumError = 0;

        x_axis = 0,y_axis = 0;
        angle_integral = 0;
        yaw_predirect = 0;
    }
}


float X_Velocity(int encoder,float set)
{
    static float PWM_out,Encoder_Err,Encoder_S,EnC_Err_Lowout,EnC_Err_Lowout_last;
    float a=0.7;

    Encoder_Err=set-encoder;

    EnC_Err_Lowout=(1-a)*Encoder_Err+a*EnC_Err_Lowout_last;
    EnC_Err_Lowout_last=EnC_Err_Lowout;//��ֹ�ٶȹ����Ӱ��ֱ����������������
    //3.���ٶ�ƫ����֣����ֳ�λ��
    Encoder_S+=EnC_Err_Lowout;//��4��
    //4.�����޷�
   if(Encoder_S>500)
       Encoder_S=500;
   if(Encoder_S<-500)
       Encoder_S=-500;

    if(Start_Flag == 0)
        Encoder_S = 0;
    //5.�ٶȻ������������
    PWM_out=X_Velocity_Kp*EnC_Err_Lowout+X_Velocity_Ki*Encoder_S;//��5��
    return PWM_out;
}

/*********************
�ٶȻ�PI��Kp*Ek+Ki*Ek_S
*********************/
float M_Velocity(int encoder,float set)
{
    static float PWM_out,Encoder_Err,Encoder_S,EnC_Err_Lowout,EnC_Err_Lowout_last;//��2��
    float a=0.7;//��3��

    //1.�����ٶ�ƫ��
    Encoder_Err=set-encoder;//��ȥ���
    //2.���ٶ�ƫ����е�ͨ�˲�
    //low_out=(1-a)*Ek+a*low_out_last;
    EnC_Err_Lowout=(1-a)*Encoder_Err+a*EnC_Err_Lowout_last;//ʹ�ò��θ���ƽ�����˳���Ƶ���ţ���ֹ�ٶ�ͻ�䡣
    EnC_Err_Lowout_last=EnC_Err_Lowout;//��ֹ�ٶȹ����Ӱ��ֱ����������������
    //3.���ٶ�ƫ����֣����ֳ�λ��
    Encoder_S+=EnC_Err_Lowout;//��4��
    //4.�����޷�
    Encoder_S=Encoder_S>10000?10000:(Encoder_S<(-10000)?(-10000):Encoder_S);

    if(Start_Flag == 0)
        Encoder_S = 0;
    //5.�ٶȻ������������
    PWM_out=M_Velocity_Kp*EnC_Err_Lowout+M_Velocity_Ki*Encoder_S;//��5��
    return PWM_out;
}

/*********************
�ٶȻ�PI��Kp*Ek+Ki*Ek_S
*********************/
float T_Velocity(int encoder,float set)
{
    static float PWM_out,Encoder_Err,Encoder_S,EnC_Err_Lowout,EnC_Err_Lowout_last;//��2��
    float a=0.7;//��3��

    //1.�����ٶ�ƫ��
    Encoder_Err=set-encoder;//��ȥ���
    //2.���ٶ�ƫ����е�ͨ�˲�
    //low_out=(1-a)*Ek+a*low_out_last;
    EnC_Err_Lowout=(1-a)*Encoder_Err+a*EnC_Err_Lowout_last;//ʹ�ò��θ���ƽ�����˳���Ƶ���ţ���ֹ�ٶ�ͻ�䡣
    EnC_Err_Lowout_last=EnC_Err_Lowout;//��ֹ�ٶȹ����Ӱ��ֱ����������������
    //3.���ٶ�ƫ����֣����ֳ�λ��
    Encoder_S+=EnC_Err_Lowout;//��4��
    //4.�����޷�
    Encoder_S=Encoder_S>10000?10000:(Encoder_S<(-10000)?(-10000):Encoder_S);

    if(Start_Flag == 0)
        Encoder_S = 0;
    //5.�ٶȻ������������
    PWM_out=T_Velocity_Kp*EnC_Err_Lowout+T_Velocity_Ki*Encoder_S;//��5��
    return PWM_out;
}
