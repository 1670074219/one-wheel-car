#include "Cross.h"

uint8 cross_count = 0;
sint16 cross_s = 0;
uint8 cross_flag = 0;
float corss_encoder = 5000;
//����ʮ��
void Handle_Cross(void)
{
    speed = element_speed.Cross_speed;
    cross_flag = 1;

    if(cross_s > corss_encoder)
    {
        cross_count++;
        Beep_OFF;
        LED_Ctrl(LED0,OFF);
        LED_Ctrl(LED1,OFF);
        cross_flag = 0;
        cross_s = 0;
        road_type.Cross = 0;
        speed = f32wBuff[21];
    }

    Check_Cross_Guaidian(1);
    if(cross_left[0] !=0 && cross_left[1] !=0)     //������¹յ㶼����
    {//ʮ��һ�׶�
        LED_Ctrl(LED0,ON);
        La_zhixian(l_line_x[cross_left[0]], cross_left[0], l_line_x[cross_left[1]], cross_left[1], l_line_x);    //����������ĺ�������
    }
    else if(cross_left[0] ==0 && cross_left[1] !=0)     //ֻ���ѵ����ϵ㣨ʮ���У�
    {//ʮ�ֶ��׶�
        LED_Ctrl(LED1,ON);
        Regression(1, cross_left[1]-10, cross_left[1]);
        Hua_Xian(1, cross_left[1], MT9V03X_H-3, parameterB, parameterA);
    }

    Check_Cross_Guaidian(2);
    if(cross_right[0] !=0 && cross_right[1] !=0)     //�Ҳ����¹յ㶼����
    {//ʮ��һ�׶�
        La_zhixian(r_line_x[cross_right[0]], cross_right[0], r_line_x[cross_right[1]], cross_right[1], r_line_x);    //����������ĺ�������
    }
    else if(cross_right[0] ==0 && cross_right[1] !=0)     //ֻ���ѵ����ϵ㣨ʮ���У�
    {//ʮ�ֶ��׶�
        Regression(2, cross_right[1]-10, cross_right[1]);
        Hua_Xian(2, cross_right[1], MT9V03X_H-3, parameterB, parameterA);
    }
}
/****************************ʮ�ִ������*****************************************/



uint8 xieshizi_stage=1;
//������бʮ�� δ��
void Handle_L_Cross()
{
    switch(xieshizi_stage)
    {
        case 1:
        {
            if(l_lose_value<20)
            {
                xieshizi_stage =2;
            }
        }
        break;
        case 2:
        {
            if(l_lose_value>40 && r_lose_value>22)  //ǰհ����Ҫ��
            {
                xieshizi_stage =3;
            }
        }
        break;
        case 3:
        {
            annulus_s1 += Distance_Measure();
            if(annulus_s1 >2000)
            {
                road_type.L_Cross =0;
                annulus_s1 =0;
                xieshizi_stage =1;
                r_guaidain_x =0;
                r_guaidain_y =0;
                l_guaidain_x =0;
                l_guaidain_y =0;
                Beep_OFF;
            }
        }
        break;
    }
    //����
    if(xieshizi_stage ==1 || xieshizi_stage ==3)
    {
        for(uint8 y =MT9V03X_H-1; y>20; y--)
        {
            l_line_x[y] = r_line_x[y] - kuandu_saidao[MT9V03X_H-1 -y];
        }
    }
    else if(xieshizi_stage ==2)
    {
        ;//��������
    }
        else if(xieshizi_stage ==3)
        {
            if(r_line_x[MT9V03X_H -1] != 0)//���¹յ���ڣ�ȡ�յ������
            {
                for(uint8 y=MT9V03X_H -1; y>30; y--)
                {
                    if(fabs(r_line_x[y] -r_line_x[y+1])<4 && (r_line_x[y]- r_line_x[y-6] <-8))
                    {
                        r_guaidain_x = r_line_x[y];
                        r_guaidain_y = y;
                        break;
                    }
                }
            }
            else
            {
                r_guaidain_x = MT9V03X_W-5;
                r_guaidain_y = 60;
            }

            for(uint8 y = (r_guaidain_y-10); y>10; y--)
            {
                if(image_01[y][r_guaidain_x] ==0 && image_01[y-1][r_guaidain_x]==0 && image_01[y-2][r_guaidain_x]==0)
                {
                    r_guaidain_y = y;
                    break;
                }
            }
            La_zhixian(1, MT9V03X_H -1, r_guaidain_x, r_guaidain_y, l_line_x);
        }
}
/****************************��бʮ�ִ������*****************************************/

//������бʮ�� δ��
void Handle_R_Cross()
{
    switch(xieshizi_stage)
    {
        case 1:
        {
            if(r_lose_value<20)
            {
                xieshizi_stage =2;
            }
        }
        break;
        case 2:
        {
            if(l_lose_value>22 && r_lose_value>40)  //ǰհ����Ҫ��
            {
                xieshizi_stage =3;
            }
        }
        break;
        case 3:
        {
            annulus_s1 += Distance_Measure();
            if(annulus_s1 >2000)
            {
                road_type.R_Cross =0;
                annulus_s1 =0;
                xieshizi_stage =1;
                r_guaidain_x =0;
                r_guaidain_y =0;
                l_guaidain_x =0;
                l_guaidain_y =0;
                Beep_OFF;
            }
        }
        break;
    }
    //����
    if(xieshizi_stage ==1 || xieshizi_stage ==3)
    {
        for(uint8 y =MT9V03X_H-1; y>20; y--)
        {
            r_line_x[y] = l_line_x[y] + kuandu_saidao[MT9V03X_H-1 -y];
        }
    }
    else if(xieshizi_stage ==2)
    {
        ;//��������
    }
    //        else if(xieshizi_stage ==3)
    //        {
    //            if(l_line_x[MT9V03X_H -1] != 0)//���¹յ���ڣ�ȡ�յ������
    //            {
    //                for(uint8 y=MT9V03X_H -1; y>30; y--)
    //                {
    //                    if(fabs(l_line_x[y] -l_line_x[y+1])<4 && (l_line_x[y]- l_line_x[y-6] > 8))
    //                    {
    //                        l_guaidain_x = l_line_x[y];
    //                        l_guaidain_y = y;
    //                        break;
    //                    }
    //                }
    //            }
    //            else
    //            {
    //                l_guaidain_x = 5;
    //                l_guaidain_y = 60;
    //            }
    //
    //            for(uint8 y = (r_guaidain_y-10); y>10; y--)
    //            {
    //                if(image_01[y][l_guaidain_x] ==0 && image_01[y-1][l_guaidain_x]==0 && image_01[y-2][l_guaidain_x]==0)
    //                {
    //                    l_guaidain_y = y;
    //                    break;
    //                }
    //            }
    //            La_zhixian(MT9V03X_W-1, MT9V03X_H -1, l_guaidain_x, l_guaidain_y, r_line_x);
    //        }

}
/****************************��бʮ�ִ������*****************************************/
float cross_turn_angle = 0;
uint8 cross_turn_flag = 0;


float cross_l_turn_offset = -110;
float cross_l_turn_angle = 70;
void Handle_cross_l_turn()
{
    speed = element_speed.Cross_speed;
    Check_Cross_Guaidian(1);
    Check_Cross_Guaidian(2);
    if(cross_left[0] !=0 && cross_left[1] !=0 && cross_right[0] !=0 && cross_right[1] !=0)     //������¹յ㶼����
    {//ʮ��һ�׶�
        La_zhixian(l_line_x[cross_left[0]], cross_left[0], l_line_x[cross_left[1]], cross_left[1], l_line_x);    //����������ĺ�������
        La_zhixian(r_line_x[cross_right[0]], cross_right[0], r_line_x[cross_right[1]], cross_right[1], r_line_x);    //����������ĺ�������
    }
    else// if(cross_left[0] ==0 && cross_left[1] !=0 && cross_right[0] ==0 && cross_right[1] !=0)     //ֻ���ѵ����ϵ㣨ʮ���У�
    {//ʮ�ֶ��׶�
        LED_Ctrl(LED0,ON);
        LED_Ctrl(LED1,ON);
        cross_turn_flag = 1;
        offset = cross_l_turn_offset;
    }

    if((cross_turn_angle > cross_l_turn_angle) || (cross_turn_angle < -cross_l_turn_angle))
    {
        Beep_OFF;
        LED_Ctrl(LED0,OFF);
        LED_Ctrl(LED1,OFF);
        speed = f32wBuff[21];
        cross_turn_angle = 0;
        road_type.Cross = 0;
        cross_turn_flag = 0;
        cross_count++;
    }


}


float cross_r_turn_offset = 110;
float cross_r_turn_angle = 70;
void Handle_cross_r_turn()
{
    speed = element_speed.Cross_speed;
    Check_Cross_Guaidian(1);
    Check_Cross_Guaidian(2);
    if(cross_left[0] !=0 && cross_left[1] !=0 && cross_right[0] !=0 && cross_right[1] !=0)     //������¹յ㶼����
    {//ʮ��һ�׶�
        La_zhixian(l_line_x[cross_left[0]], cross_left[0], l_line_x[cross_left[1]], cross_left[1], l_line_x);    //����������ĺ�������
        La_zhixian(r_line_x[cross_right[0]], cross_right[0], r_line_x[cross_right[1]], cross_right[1], r_line_x);    //����������ĺ�������
    }
    else// if(cross_left[0] ==0 && cross_left[1] !=0 && cross_right[0] ==0 && cross_right[1] !=0)     //ֻ���ѵ����ϵ㣨ʮ���У�
    {//ʮ�ֶ��׶�
        LED_Ctrl(LED0,ON);
        LED_Ctrl(LED1,ON);
        cross_turn_flag = 1;
        offset = cross_r_turn_offset;
    }

    if((cross_turn_angle > cross_r_turn_angle) || (cross_turn_angle < -cross_r_turn_angle))
    {
        Beep_OFF;
        LED_Ctrl(LED0,OFF);
        LED_Ctrl(LED1,OFF);
        speed = f32wBuff[21];
        cross_turn_angle = 0;
        road_type.Cross = 0;
        cross_turn_flag = 0;
        cross_count++;
    }
}
