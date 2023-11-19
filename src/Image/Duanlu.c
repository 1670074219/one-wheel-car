#include "Duanlu.h"

#define MAX_COL 180
#define Bin_Image Pixle
int OFFSET0, OFFSET1, OFFSET2, OFFSET3;
sint16 temp0_L = 0, temp0_R = 0;        //临时数值
sint16 temp1_L = 0, temp1_R = 0;        //临时数值
sint16 temp2_L = 0, temp2_R = 0;        //临时数值

float duanlu_select = 0;
uint8 dont_handle_cirque = 0;
/***************************************************************************
 *                                                                          *
 *  函数名称：Seek_Road(void)                                           *
 *  功能说明：寻找白色区域偏差值                                            *
 *  参数说明：无                                                            *
 *  函数返回：值的大小                                                      *
 *  修改时间：2017-07-16                                                    *
 *  备    注：以中间为0，左侧减一，右侧加一，数值代表1的面积                *
 *            计算区域从第一行开始到倒数第二行结束。                        *
 *            如果面积为负数，数值越大说明越偏左边；                        *
 *            如果面积为正数，数值越大说明越偏右边。                        *
 ***************************************************************************/
void Seek_Road (void)
{
    sint16 nr; //行
    sint16 nc; //列
    sint16 temp = 0; //临时数值
    sint16 temp_L = 0, temp_R = 0; //临时数值
    sint16 temp2 = 0; //临时数值
    //for(nr=1; nr<MAX_ROW-1; nr++)
    temp = 0;
/*****************************8-24**********************************/
    for (nr = 80; nr < 90; nr++)
    {
        for (nc = 0; nc < MAX_COL / 2; nc = nc + 1)
        {
            if (image_01[nr][nc])
            {
                ++temp_L;
            }/*else{
                --temp_L;
            }*/
        }
        for (nc = MAX_COL / 2; nc < MAX_COL; nc++)
        {
            if (image_01[nr][nc])
            {
                ++temp_R;
            }/*else{
                --temp_R;
            }*/
        }
    }
    temp0_L = temp_L;
    temp0_R = temp_R;
    temp_L = 0;
    temp_R = 0;
    OFFSET0 = temp0_R - temp0_L;

    /*for (nr = 24; nr < 40; nr++)
    {
        for (nc = 0; nc < MAX_COL / 2; nc = nc + 1)
        {
            if (Bin_Image[nr][nc])
            {
                ++temp_L;
            }else{
                --temp_L;
            }
        }
        for (nc = MAX_COL / 2; nc < MAX_COL; nc = nc + 1)
        {
            if (Bin_Image[nr][nc])
            {
                ++temp_R;
            }else{
                --temp_R;
            }
        }
    }
    temp1_L = temp_L;
    temp1_R = temp_R;
    temp_L = 0;
    temp_R = 0;
    OFFSET1 = temp1_R - temp1_L;*/

/*    for (nr = 40; nr < 56; nr++)
    {
        for (nc = 0; nc < MAX_COL / 2; nc = nc + 1)
        {
            if (Bin_Image[nr][nc])
            {
                ++temp_L;
            }else{
                --temp_L;
            }
        }
        for (nc = MAX_COL / 2; nc < MAX_COL; nc = nc + 1)
        {
            if (Bin_Image[nr][nc])
            {
                ++temp_R;
            }else{
                --temp_R;
            }
        }
    }
    temp2_L = temp_L;
    temp2_R = temp_R;
    temp_L = 0;
    temp_R = 0;
    OFFSET2 = temp2_R - temp2_L;*/

}

uint8 Duanlu_stage = 0;
uint8 Duanlu_flag = 0;
float Duanlu_angle = 0;

float Duanlu_offset0 = 0;
float Duanlu_angle0 = 0;
float Duanlu_offset1 = 0;
float Duanlu_angle1 = 0;
float Duanlu_encoder_set = 2500;

uint8 duanlu_white_count = 0;
uint8 duanlu_once_flag = 0;

float duanlu_seek_road = 0;
void Handle_Duanlu(void) //普通两段积分到赛道
{
    speed = element_speed.Duanlu_speed;

    if(Duanlu_stage == 0)
    {
        Duanlu_flag = 1;
        offset = Duanlu_offset0;
        if(Duanlu_angle > Duanlu_angle0 || Duanlu_angle < -Duanlu_angle0)
        {
            LED_Ctrl(LED0,ON);
            Duanlu_angle = 0;
            Duanlu_flag = 0;
            Duanlu_stage = 1;
        }
    }
    else if(Duanlu_stage == 1)
    {
        Duanlu_flag = 1;
        offset = Duanlu_offset1;
        if(Duanlu_angle > Duanlu_angle1 || Duanlu_angle < -Duanlu_angle1)
        {
            LED_Ctrl(LED1,ON);
            Duanlu_angle = 0;
            Duanlu_flag = 0;
            offset = 0;
            Duanlu_stage = 2;
        }
    }
    else if(Duanlu_stage == 2)
    {
        duanlu_white_count = 0;

        for(int i = 90; i <= 110; i+=2)
        {
            if(image_01[i][90] != 0)
                duanlu_white_count++;
        }

        if(duanlu_white_count >= 5)
        {
            duanlu_once_flag = 1;
            offset = 0;
            LED_Ctrl(LED0,OFF);
            LED_Ctrl(LED1,OFF);
            Duanlu_stage = 0;
            road_type.Duanlu = 0;
            duanlu_white_count = 0;
            dont_handle_cirque = 1;
            speed = f32wBuff[21];
        }

        if(duanlu_seek_road == 0 && road_type.Duanlu == 1)
        {
            Seek_Road();
            offset = (float)OFFSET0/15;
        }
    }
}


float Duanlu_Flag1 = 0;
float Duanlu_set_angle = 115;
float Duanlu_back_speed = 150;
uint8 duanlu_finish_stage = 0;
uint8 duanlu_offset_limit_flag = 0;
void Handle_Duanlu1(void) //惯性导航处理
{
    Duanlu_Flag1 = 1;

    if(fabs(x_axis - x_axis_pre) < 600 && fabs(y_axis - y_axis_pre) < 600)
        duanlu_finish_stage = 1;

    if(duanlu_finish_stage)
    {
        Duanlu_Flag1 = 0;
        offset = 0;
        speed = 120;

        switch(Duanlu_stage)
        {
            case 0:
                duanlu_white_count = 0;

                for(int i = 90; i <= 110; i+=2)
                {
                    if(image_01[i][90] != 0)
                        duanlu_white_count++;
                }

                if(duanlu_white_count >= 5)
                {
                    /*duanlu_once_flag = 1;
                    offset = 0;
                    LED_Ctrl(LED1,ON);
                    Duanlu_stage = 0;
                    road_type.Duanlu = 0;
                    duanlu_white_count = 0;
                    duanlu_finish_stage = 0;
                    dont_handle_cirque = 1;
                    duanlu_offset_limit_flag = 1;*/

                    duanlu_white_count = 0;
                    offset = 0;
                    Duanlu_stage++;

                    //printf("a:%.1f o:%.1f\n",angle_integral, offset);
                }

                if(duanlu_seek_road == 0 && /*road_type.Duanlu == 1*/Duanlu_stage == 0)
                {
                    /*Seek_Road();
                    offset = (float)OFFSET0/15;*/
                    LED_Ctrl(LED0,RVS);
                    offset = angle_integral - Duanlu_set_angle;
                    offset *= 1.2;

                }

                /*Duanlu_flag = 1;
                offset = Duanlu_offset2;
                if(Duanlu_angle > Duanlu_angle2 || Duanlu_angle < -Duanlu_angle2)
                {
                    Duanlu_flag = 0;
                    offset = 0;
                    Duanlu_angle = 0;
                    Duanlu_stage++;
                }*/


                /*if(angle_integral>90 && angle_integral<180)
                {
                    offset = angle_integral - 115;
                    if(offset < 5 && offset > -5)
                        Duanlu_stage++;
                }*/



                break;
            case 1:
                Calculate_Offset_d();
                LED_Ctrl(LED0,OFF);
                LED_Ctrl(LED1,RVS);
                if(fabs(angle_integral) > 150 && x_axis_pre >= 0)
                {
                    Duanlu_stage++;
                    road_type.Duanlu = 0;
                    duanlu_finish_stage = 0;
                    dont_handle_cirque = 1;
                    duanlu_offset_limit_flag = 1;
                    offset = 0;
                    duanlu_once_flag = 1;
                    //printf("f1:%.1f\n",angle_integral);
                }
                else if(fabs(angle_integral) < 30 && x_axis_pre <= 0)
                {
                    Duanlu_stage++;
                    road_type.Duanlu = 0;
                    duanlu_finish_stage = 0;
                    dont_handle_cirque = 1;
                    duanlu_offset_limit_flag = 1;
                    offset = 0;
                    duanlu_once_flag = 1;
                    //printf("f2:%.1f\n",angle_integral);
                }
                break;


                /*Duanlu_flag = 1;
                offset = Duanlu_offset2;
                if(Duanlu_angle > Duanlu_angle2 || Duanlu_angle < -Duanlu_angle2)
                {
                    LED_Ctrl(LED1,ON);

                    Duanlu_flag = 0;
                    offset = 0;
                    Duanlu_angle = 0;
                    Duanlu_stage++;

                    Duanlu_stage = 0;
                    road_type.Duanlu = 0;
                    duanlu_finish_stage = 0;
                    dont_handle_cirque = 1;
                    duanlu_offset_limit_flag = 1;
                }
                break;*/

                /*duanlu_white_count = 0;

                for(int i = 80; i <= 100; i+=2)
                {
                    if(image_01[i][90] != 0)
                        duanlu_white_count++;
                }

                if(duanlu_white_count >= 5)
                {
                    duanlu_once_flag = 1;
                    offset = 0;
                    LED_Ctrl(LED1,ON);
                    Duanlu_stage = 0;
                    road_type.Duanlu = 0;
                    duanlu_white_count = 0;
                    duanlu_finish_stage = 0;
                    dont_handle_cirque = 1;
                    duanlu_offset_limit_flag = 1;
                }

                if(duanlu_seek_road == 0 && road_type.Duanlu == 1)
                {
                    Seek_Road();
                    offset = (float)OFFSET0/20;
                }
                break;*/
        }
    }
    else
    {
        if(offset < 20 && offset > -20)
            speed = Duanlu_back_speed;
        else
            speed = element_speed.Duanlu_speed;
    }
}
