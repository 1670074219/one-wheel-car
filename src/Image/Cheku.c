#include "Cheku.h" //���Ԫ��

extern uint8 cheku_flag;
extern uint8 shibie_flag;

uint8 cheku_sum_flag = 0;
float cheku_angle = 0;

float cheku_l_offset = -100; //��תƫ��
float cheku_l_angle = 75; //��ת�Ƕ�
float cheku_r_offset = 90; //��תƫ��
float cheku_r_angle = 75; //��ת�Ƕ�
void Handle_Barn_in(uint8 type) //handle���� type=1 ��ת type=2 ��ת
{
    if(type == 1)
    {
        speed = 90;
        offset = cheku_l_offset;
        cheku_sum_flag = 1;

        if((cheku_angle > cheku_l_angle) || (cheku_angle < -cheku_l_angle))
        {
            shibie_flag =1;
            LED_Ctrl(LED0,OFF);
            Beep_OFF;
            cheku_angle = 0;
            cheku_flag = 0;
            cheku_sum_flag = 0;
            road_type.Barn_l_in = 0;
            //start = 1;                  //���ٻ��岿��
/*            speed = 60;
            offset = 0;
            delayms(30);
            speed = 30;
            delayms(20);*/
            speed = 0;
        }
    }

    if(type == 2)
    {
        speed = 90;
        offset = cheku_r_offset;
        cheku_sum_flag = 1;

        if((cheku_angle > cheku_r_angle) || (cheku_angle < -cheku_r_angle))
        {
            shibie_flag = 1;
            LED_Ctrl(LED0,OFF);
            Beep_OFF;
            cheku_angle = 0;
            cheku_flag = 0;
            cheku_sum_flag = 0;
            road_type.Barn_r_in = 0;
            //start = 1;                   //���ٻ��岿��
/*            speed = 60;
            offset = 0;
            delayms(30);
            speed = 30;
            delayms(20);*/
            speed = 0;
        }
    }
}
