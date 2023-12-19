#include "Loop.h" //线程

/***************平衡参数*******************/
float Start_Flag; //启动位
float Med_Angle = 0.1; //动量轮平衡零点
float M_Med_Angle = 1.6, X_Med_Angle = -0.1; //初始化平衡零点
short Encoder_A,Encoder_B,Encoder_C; //编码器值
float M_Left_PWM = 0; //动量轮左轮p波
float M_Right_PWM = 0; //动量轮右轮p波
float k_offset = -0.08; //编程倍数k
float speed = 140; //初始速度

/***************速度平滑参数*******************/
float offset1; //中间变量 偏差绝对值
int start1=0; //中间变量 计数
uint8 old_speed = 0,new_speed = 0,cur_speed = 0; //中间变量 速度平滑

/***************惯性导航参数*******************/
float x_axis = 0,y_axis = 0; //x y起始坐标
float angle_integral = 0; //角度积分变量
float angle_integral_rad = 0; //弧度积分变量
float Yaw_Start = 0; //初始yaw角

/***************PID参数*******************/
float X_Velocity_Kp = 0,X_Velocity_Ki = 0,X_Velocity_out = 0;
float M_Velocity_Kp = 0,M_Velocity_Ki = 0,M_Velocity_out = 0;
float T_Velocity_Kp = 0,T_Velocity_Ki = 0,T_Velocity_out = 0;

float X_Velocity(int encoder,float set);
float M_Velocity(int encoder,float set);
float T_Velocity(int encoder,float set);

void Loop_20ms()//20ms 速度环
{
    /***************设置速度缓冲时间 防止开启疯转*******************/
    if(Start_Flag==1 && start1 < 500)
        start1++;

    /***************偏差绝对值*******************/
    offset1=offset;
    if(offset1<0)
        offset1=-offset1;
    /***************弯直道速度平滑*******************/
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

    /***************圆环减速 速度环*******************/
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
    /***************左右平衡动态零点*******************/
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

    /***************动态零点限幅*******************/
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

    /***************角度环*******************/
    M.Angle.out = PID_Realize(&M.Angle.pid, Pitch, (M_Velocity_out+Med_Angle));
    X.Angle.out = PID_Realize(&X.Angle.pid, Roll, (X_Velocity_out+X_Med_Angle));
    T.Angle.out = PID_Realize(&T.Angle.pid, offset, 0);
}

/***************积分flag 积分参数*******************/
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

uint8 start = 0; //停止标志

/***************惯性导航参数*******************/
float yaw_predirect = 0; //yaw转动角度
float x_axis_pre = 2500; //前一次x坐标
float y_axis_pre = 738; //前一次y坐标


void Loop_2ms()//2ms
{
    Encoder_A = ENC_GetCounter(ENC5_InPut_P10_3);   //左电机 母板上编码器1，小车前进为负值
    Encoder_B = -ENC_GetCounter(ENC4_InPut_P02_8);  //右电机 母板上编码器2，小车前进为正值
    Encoder_C = -ENC_GetCounter(ENC6_InPut_P20_3);  //行进电机 母板上编码器3，小车前进为正值
    LQ_DMP_Read();                                  //获取姿态信息

    /************************积分****************************/
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
        /****************************************************************************惯导处理***********************************************************************/

        /***************转动角度*******************/
        angle_integral = Yaw-Yaw_Start;

        /***************转动角度限幅*******************/
        if(angle_integral > 180)
            angle_integral -= 360;
        else if(angle_integral < -180)
            angle_integral += 360;

        /***************转动角度弧度制*******************/
        angle_integral_rad = angle_integral/57.3;

        /***************x y坐标计算*******************/
        x_axis += cos(angle_integral_rad)*(Encoder_C / 50);
        y_axis += sin(angle_integral_rad)*(Encoder_C / 50);

        if(Duanlu_Flag1 == 1)
        {
            /***************坐标角度*******************/
            yaw_predirect = atan((y_axis - y_axis_pre)/(x_axis - x_axis_pre));

            /***************坐标角度限幅*******************/
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

            /***************坐标角度 转动角度 计算偏差*******************/
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
    /************************角速度环****************************/
    M.Gyro.out = PID_Realize(&M.Gyro.pid, gyro[0], M.Angle.out);
    X.Gyro.out = PID_Realize(&X.Gyro.pid, gyro[1], X.Angle.out);
    T.Gyro.out = PID_Realize(&T.Gyro.pid, gyro[2], T.Angle.out);

    M_Left_PWM = M.Gyro.out;//+T.Gyro.out;
    M_Right_PWM = -M.Gyro.out;//+T.Gyro.out;

    M_Left_PWM = fclip(M_Left_PWM, -10000, 10000);                     //PWM限幅
    M_Right_PWM = fclip(M_Right_PWM, -10000, 10000);                   //PWM限幅
    X.Gyro.out = fclip(X.Gyro.out, -3500, 3500);                       //PWM限幅
    if(fabs(Pitch)>35 || fabs(Roll)>30){Start_Flag=0;}                 //超过特定角度停止运行

    if((Start_Flag==1)&&(start == 0)) //启动
    {
        DIN_ON;
        MotorCtrl3W((sint32)(M_Left_PWM),(sint32)(M_Right_PWM), (sint32)(X.Gyro.out));
    }
    else //停止
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
    EnC_Err_Lowout_last=EnC_Err_Lowout;//防止速度过大的影响直立环的正常工作。
    //3.对速度偏差积分，积分出位移
    Encoder_S+=EnC_Err_Lowout;//【4】
    //4.积分限幅
   if(Encoder_S>500)
       Encoder_S=500;
   if(Encoder_S<-500)
       Encoder_S=-500;

    if(Start_Flag == 0)
        Encoder_S = 0;
    //5.速度环控制输出计算
    PWM_out=X_Velocity_Kp*EnC_Err_Lowout+X_Velocity_Ki*Encoder_S;//【5】
    return PWM_out;
}

/*********************
速度环PI：Kp*Ek+Ki*Ek_S
*********************/
float M_Velocity(int encoder,float set)
{
    static float PWM_out,Encoder_Err,Encoder_S,EnC_Err_Lowout,EnC_Err_Lowout_last;//【2】
    float a=0.7;//【3】

    //1.计算速度偏差
    Encoder_Err=set-encoder;//舍去误差
    //2.对速度偏差进行低通滤波
    //low_out=(1-a)*Ek+a*low_out_last;
    EnC_Err_Lowout=(1-a)*Encoder_Err+a*EnC_Err_Lowout_last;//使得波形更加平滑，滤除高频干扰，防止速度突变。
    EnC_Err_Lowout_last=EnC_Err_Lowout;//防止速度过大的影响直立环的正常工作。
    //3.对速度偏差积分，积分出位移
    Encoder_S+=EnC_Err_Lowout;//【4】
    //4.积分限幅
    Encoder_S=Encoder_S>10000?10000:(Encoder_S<(-10000)?(-10000):Encoder_S);

    if(Start_Flag == 0)
        Encoder_S = 0;
    //5.速度环控制输出计算
    PWM_out=M_Velocity_Kp*EnC_Err_Lowout+M_Velocity_Ki*Encoder_S;//【5】
    return PWM_out;
}

/*********************
速度环PI：Kp*Ek+Ki*Ek_S
*********************/
float T_Velocity(int encoder,float set)
{
    static float PWM_out,Encoder_Err,Encoder_S,EnC_Err_Lowout,EnC_Err_Lowout_last;//【2】
    float a=0.7;//【3】

    //1.计算速度偏差
    Encoder_Err=set-encoder;//舍去误差
    //2.对速度偏差进行低通滤波
    //low_out=(1-a)*Ek+a*low_out_last;
    EnC_Err_Lowout=(1-a)*Encoder_Err+a*EnC_Err_Lowout_last;//使得波形更加平滑，滤除高频干扰，防止速度突变。
    EnC_Err_Lowout_last=EnC_Err_Lowout;//防止速度过大的影响直立环的正常工作。
    //3.对速度偏差积分，积分出位移
    Encoder_S+=EnC_Err_Lowout;//【4】
    //4.积分限幅
    Encoder_S=Encoder_S>10000?10000:(Encoder_S<(-10000)?(-10000):Encoder_S);

    if(Start_Flag == 0)
        Encoder_S = 0;
    //5.速度环控制输出计算
    PWM_out=T_Velocity_Kp*EnC_Err_Lowout+T_Velocity_Ki*Encoder_S;//【5】
    return PWM_out;
}
