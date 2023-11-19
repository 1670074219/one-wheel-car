#include "Cirque.h"
int circle_flag=0;
//处理左环岛
uint8 huandao_stage=1;  //环岛阶段标志位
uint8 huandao_flag = 0;
float huandao_angle = 0;

float l_angle_in = 90;
float l_angle_out = 335;
void Handle_Left_Cirque()
{
    speed = element_speed.Cirque_speed;


    //判断在圆环的位置
    switch(huandao_stage)
    {
        case 1:
            Diuxian_weizhi_test(1, MT9V03X_H -1, MT9V03X_H -20);
            if(budiuxian_hang >=15)
            {
                Diuxian_weizhi_test(1, MT9V03X_H -20, MT9V03X_H -40);
                if(diuxian_hang >=15)
                {
                    huandao_stage = 2;  //黑段加白段（1阶段）（补线直行）
                }
            }
            break;
        case 2:
            Diuxian_weizhi_test(1,MT9V03X_H -1, MT9V03X_H -20);
            if(diuxian_hang >=5 && huandao_stage ==2)
            {
                Diuxian_weizhi_test(1, MT9V03X_H -20, MT9V03X_H -40);
                if(budiuxian_hang >=15)
                {
                    huandao_stage =3;  //白段加黑段（2阶段）（补线直行）
                }
            }
            break;
        case 3:
            Diuxian_weizhi_test(1, MT9V03X_H -20, MT9V03X_H -40);
            if(budiuxian_hang >=15 && huandao_stage ==3)
            {
                Diuxian_weizhi_test(1, MT9V03X_H -40, MT9V03X_H -60);
                if(diuxian_hang >=1)
                {
                    huandao_stage =4;  //黑段加白段（3阶段）（拉线进环）
                    huandao_flag = 1;
                }
            }
            break;
        case 4:
            //annulus_s1 += Distance_Measure();
            if( huandao_angle > l_angle_in)   //编码器积分大于一个值，进入环岛里面（这个值可以给小一些，车身路径不好）5500
            {
                LED_Ctrl(LED0,ON);
                huandao_stage =5;     //进入圆环内
                annulus_s1 =0;
            }
            break;
        case 5:
            Diuxian_weizhi_test(2,MT9V03X_H -40, MT9V03X_H -60);
            if(diuxian_hang >=10 && huandao_stage ==5)
            {
                huandao_stage =6;     //出环
            }
            break;
        case 6:
            annulus_s1 += Distance_Measure();
            if(huandao_angle > l_angle_out)//积分
            {
                LED_Ctrl(LED1,ON);
                huandao_stage =7;
                annulus_s1 =0;
            }
            break;
        case 7:
            annulus_s1 += Distance_Measure();
            if(annulus_s1 >5000)  //积分一段距离并补线环岛处理结束(所有标志位清零)
            {
                LED_Ctrl(LED0,OFF);
                LED_Ctrl(LED1,OFF);
                road_type.LeftCirque = 0;
                huandao_stage =1;
                annulus_s1 =0;
                l_guaidain_x=0, l_guaidain_y=0;
                r_guaidain_x=0, r_guaidain_y=0;
                huandao_angle = 0;
                huandao_flag = 0;
                Beep_OFF;
                speed = f32wBuff[21];
            }
            break;
    }

    //处理
    if(huandao_stage ==1)    //半宽补线补左线
    {
        for(uint8 y =MT9V03X_H -30; y >=MT9V03X_H -40; y--)  //只有80行的赛道宽度，够用了
        {
            l_line_x[y] = r_line_x[y] - kuandu_saidao[MT9V03X_H-1 -y]; //-5
            //r_line_x[y] = r_line_x[y];
        }
    }
    else if((huandao_stage ==2) || (huandao_stage ==3))
    {
        for(uint8 y =MT9V03X_H -30; y >=MT9V03X_H -40; y--)  //只有80行的赛道宽度，够用了
        {
            l_line_x[y] = r_line_x[y] - kuandu_saidao[MT9V03X_H-1 -y];//-10
            //r_line_x[y] = r_line_x[y];
        }
    }
    else if(huandao_stage ==4)   //赛道宽度补线
    {
        for(uint8 y =MT9V03X_H -30; y >=MT9V03X_H -40; y--)  //只有80行的赛道宽度，够用了
        {
            r_line_x[y] = l_line_x[y] + kuandu_saidao[MT9V03X_H-1 -y];   //随便给的一个偏移量，给小一点会内切
//            l_line_x[y] = l_line_x[y] ;
        }
    }
    else if(huandao_stage ==5)   //在环岛
    {
        ;//无需操作
    }
    else if(huandao_stage ==6)   //出环岛
    {
//        if(r_line_x[MT9V03X_H -1] != (MT9V03X_W-1))        //右下拐点存在&&(MT9V03X_H<50)
//        {
//            for(uint8 y=MT9V03X_H -1; y>10; y--)
//            {
//                if(fabs(r_line_x[y] -r_line_x[y+1])<4 && (r_line_x[y]- r_line_x[y-6] < -6))    //这个条件要更加严格一点
//                {
//                    r_guaidain_y = y;   //没进入这个循环
//                    r_guaidain_x = r_line_x[y];
//                    break;
//                }
//            }
//        }
//        else
//        {
            r_guaidain_y = MT9V03X_H -1;
            r_guaidain_x = MT9V03X_W-10;
//        }

        for(uint8 y =MT9V03X_H -40; y>10; y--)//50
        {
            if((image_01[y][50] == 0) && (image_01[y-1][50]==0) && (image_01[y-2][50]==0))
            {
                l_guaidain_y = y;
                l_guaidain_x = 50;//60
                break;
            }
        }

        La_zhixian(r_guaidain_x, r_guaidain_y, l_guaidain_x, l_guaidain_y, r_line_x);
    }
    else if(huandao_stage==7)
    {
        for(uint8 y =MT9V03X_H-1; y>20; y--)
        {
            l_line_x[y] = r_line_x[y] - kuandu_saidao[MT9V03X_H-1 -y];     //车辆路径偏右,为了准确识别环岛,采用偏移量使车身更加贴近左侧-5
            //r_line_x[y] = r_line_x[y];
        }
    }
}
/*****************************左环岛处理结束*****************************************/




//处理右环岛
float r_angle_in = -90;
float r_angle_out = -350;
void Handle_Right_Cirque()
{
    speed = element_speed.Cirque_speed;


    //判断在圆环的位置
    switch(huandao_stage)
    {
        case 1:
            Diuxian_weizhi_test(2, MT9V03X_H -1, MT9V03X_H -20);
            if(budiuxian_hang >=15)
            {
                Diuxian_weizhi_test(2, MT9V03X_H -20, MT9V03X_H -40);
                if(diuxian_hang >=15)
                {
                    huandao_stage =2;  //黑段加白段（1阶段）（补线直行）
                }
            }
            break;

        case 2:
            Diuxian_weizhi_test(2,MT9V03X_H -1, MT9V03X_H -20);
            if(diuxian_hang >=15 && huandao_stage ==2)
            {
                Diuxian_weizhi_test(2, MT9V03X_H -20, MT9V03X_H -40);
                if(budiuxian_hang >=15)
                {
                    huandao_stage =3;  //白段加黑段（2阶段）（补线直行）
                }
            }
            break;

        case 3:
            Diuxian_weizhi_test(2, MT9V03X_H -20, MT9V03X_H -40);
            if(budiuxian_hang >=15 && huandao_stage ==3)
            {
                Diuxian_weizhi_test(2, MT9V03X_H -40, MT9V03X_H -60);
                if(diuxian_hang >=1)
                {
                    huandao_stage =4;  //黑段加白段（3阶段）（拉线进环）
                    huandao_flag = 1;
                }
            }
            break;
        case 4:
            //annulus_s1 += Angle_Measure();
            if(huandao_angle < r_angle_in)   //编码器积分大于一个值，进入环岛里面（这个值可以给小一些，车身路径不好）
            {
                LED_Ctrl(LED0,ON);
                huandao_stage =5;     //进入圆环内
                annulus_s1 =0;
                last_angle = 0;
                now_angle = 0;

            }
            break;
        case 5:
            Diuxian_weizhi_test(1,MT9V03X_H -40, MT9V03X_H -60);
            if(diuxian_hang >=10 && huandao_stage ==5)
            {
                annulus_s1 =0;
                last_angle = 0;
                now_angle = 0;
                huandao_stage =6;     //出环
            }
            break;
        case 6:
            //annulus_s1 += Angle_Measure();
            if( huandao_angle<r_angle_out)//积分
            {
                LED_Ctrl(LED1,ON);
                huandao_stage =7;
                annulus_s1 =0;
                last_angle = 0;
                now_angle = 0;
            }
            break;
        case 7:
            annulus_s1 += Distance_Measure();
            if(annulus_s1 >5000)  //积分一段距离并补线环岛处理结束(所有标志位清零)
            {
                LED_Ctrl(LED0,OFF);
                LED_Ctrl(LED1,OFF);
                road_type.RightCirque = 0;
                huandao_stage =1;
                annulus_s1 =0;
                l_guaidain_x=0, l_guaidain_y=0;
                r_guaidain_x=0, r_guaidain_y=0;
                huandao_angle = 0;
                huandao_flag = 0;
                Beep_OFF;
                speed = f32wBuff[21];
            }
            break;
    }

    //处理
    if(huandao_stage ==1)    //半宽补线补左线
    {
        for(uint8 y =MT9V03X_H -30; y >=MT9V03X_H -40; y--)  //只有80行的赛道宽度，够用了
        {
            r_line_x[y] = l_line_x[y] + kuandu_saidao[MT9V03X_H-1 -y]; //+5
            //l_line_x[y] = l_line_x[y];
        }
    }
    else if((huandao_stage ==2) || (huandao_stage ==3))
    {
        for(uint8 y =MT9V03X_H -30; y >=MT9V03X_H -40; y--)  //只有80行的赛道宽度，够用了
        {
            r_line_x[y] = l_line_x[y] + kuandu_saidao[MT9V03X_H-1 -y];//+10
            //l_line_x[y] = l_line_x[y];
        }
    }
    else if(huandao_stage ==4)   //赛道宽度补线
    {
        for(uint8 y =MT9V03X_H -30; y >=MT9V03X_H -40; y--)  //只有80行的赛道宽度，够用了
        {
            l_line_x[y] = r_line_x[y] - kuandu_saidao[MT9V03X_H-1 -y];  //随便给的一个偏移量，给小一点会内切 +5
            //r_line_x[y] = r_line_x[y]+4;
        }
    }
    else if(huandao_stage ==5)   //在环岛
    {
        ;//无需操作
    }
    else if(huandao_stage ==6)   //出环岛
    {
//        if(l_line_x[MT9V03X_H -1] != 0)         //左下拐点存在
//        {
//            for(uint8 y=MT9V03X_H -1; y>10; y--)
//            {
//                if(fabs(l_line_x[y] -l_line_x[y+1])<4 && (l_line_x[y]- l_line_x[y-6] >6))    //这个条件要更加严格一点
//                {
//                    l_guaidain_y = y;   //没进入这个循环
//                    l_guaidain_x = l_line_x[y];
//                    break;
//                }
//
//            }
//        }
//        else
//        {
            l_guaidain_y = MT9V03X_H -1;
            l_guaidain_x = 10;
//        }

        for(uint8 y =MT9V03X_H -40; y>10; y--)
        {
            if((image_01[y][MT9V03X_W - 60] == 0) && (image_01[y-1][MT9V03X_W - 60]==0) && (image_01[y-2][MT9V03X_W - 60]==0))
            {
                r_guaidain_y = y;
                r_guaidain_x = MT9V03X_W - 60;
                break;
            }
        }
        La_zhixian(l_guaidain_x, l_guaidain_y, r_guaidain_x, r_guaidain_y, l_line_x);
    }
    else if(huandao_stage==7)
    {
        for(uint8 y =MT9V03X_H-1; y>20; y--)
        {
            r_line_x[y] = l_line_x[y] + kuandu_saidao[MT9V03X_H-1 -y];     //车辆路径偏右,为了准确识别环岛,采用偏移量使车身更加贴近左侧
        }
    }
}
/*****************************右环岛处理结束*****************************************/

uint32 dont_handle_encoder = 0;
uint16 dont_handle_flag = 0;
void Dont_handle_l_cirque(void)
{
    speed = element_speed.DotCirque_speed;
    dont_handle_flag = 1;

    for(uint8 y =MT9V03X_H -30; y >=MT9V03X_H -40; y--)  //只有80行的赛道宽度，够用了
    {
        l_line_x[y] = r_line_x[y] - kuandu_saidao[MT9V03X_H-1 -y];
    }

    if(dont_handle_encoder > 130000)
    {
        LED_Ctrl(LED0,OFF);
        LED_Ctrl(LED1,OFF);
        Beep_OFF;
        dont_handle_encoder = 0;
        dont_handle_flag = 0;
        road_type.LeftCirque = 0;
        speed = f32wBuff[21];
    }
}

void Dont_handle_r_cirque(void)
{
    speed = element_speed.DotCirque_speed;
    dont_handle_flag = 1;

    for(uint8 y =MT9V03X_H -30; y >=MT9V03X_H -40; y--)  //只有80行的赛道宽度，够用了
    {
        r_line_x[y] = l_line_x[y] + kuandu_saidao[MT9V03X_H-1 -y];
    }

    if(dont_handle_encoder > 130000)
    {
        LED_Ctrl(LED0,OFF);
        LED_Ctrl(LED1,OFF);
        Beep_OFF;
        dont_handle_encoder = 0;
        dont_handle_flag = 0;
        road_type.RightCirque = 0;
        speed = f32wBuff[21];
    }
}
