#include "Zhangai.h"

uint8 zhangai_once_flag = 0;
uint8 zhangai_flag = 0;
uint8 zhangai_stage = 0;
float zhangai_angle = 0;

float zhangai_offset0 = 92;
float zhangai_angle0 = -44;
float zhangai_offset1 = -82;
float zhangai_angle1 = 30;
float zhangai_offset2 = 68;
float zhangai_angle2 = 0;

float zhangai_dir = 0;
void Handle_ZhangAi(void) //Ð´ËÀ
{
    speed = element_speed.ZhangAi_speed;

    if(zhangai_dir == 0)
    {
        zhangai_flag = 1;
        switch(zhangai_stage)
        {
            case 0:
                offset = -zhangai_offset0;
                if(zhangai_angle > -zhangai_angle0)
                {
                    zhangai_stage = 1;
                    LED_Ctrl(LED0,ON);
                }
                break;
            case 1:
                offset = -zhangai_offset1;
                if (zhangai_angle < -zhangai_angle1)
                {
                    zhangai_stage = 2;
                    LED_Ctrl(LED1,ON);
                }
                break;
            case 2:
                offset = -zhangai_offset2;
                if(zhangai_angle > -zhangai_angle2)
                {
                    zhangai_stage = 4;
                }
                break;
            default :
                Beep_OFF;
                LED_Ctrl(LED0,OFF);
                LED_Ctrl(LED1,OFF);
                road_type.ZhangAi = 0;
                zhangai_once_flag = 1;
                speed = f32wBuff[21];
                zhangai_flag = 0;
        }
    }
    else
    {
        zhangai_flag = 1;
        switch(zhangai_stage)
        {
            case 0:
                offset = zhangai_offset0;
                if(zhangai_angle < zhangai_angle0)
                {
                    zhangai_stage = 1;
                    LED_Ctrl(LED0,ON);
                }
                break;
            case 1:
                offset = zhangai_offset1;
                if (zhangai_angle > zhangai_angle1)
                {
                    zhangai_stage = 2;
                    LED_Ctrl(LED1,ON);
                }
                break;
            case 2:
                offset = zhangai_offset2;
                if(zhangai_angle < zhangai_angle2)
                {
                    zhangai_stage = 4;
                }
                break;
            default :
                Beep_OFF;
                LED_Ctrl(LED0,OFF);
                LED_Ctrl(LED1,OFF);
                road_type.ZhangAi = 0;
                zhangai_once_flag = 1;
                speed = f32wBuff[21];
                zhangai_flag = 0;
        }
    }
}
