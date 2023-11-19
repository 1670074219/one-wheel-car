#include "podao.h"

uint8 podao_flag = 0;
uint16 podao_encoder = 0;

float podao_speed = 115;
float podao_encoder_set = 15000;

void Handle_Podao()
{
    podao_flag = 1;
    speed = podao_speed;

    if(podao_encoder > podao_encoder_set)
    {
        LED_Ctrl(LED0,OFF);
        LED_Ctrl(LED1,OFF);
        Beep_OFF;
        podao_encoder = 0;
        speed = f32wBuff[21];
        road_type.Podao = 0;
        podao_flag = 0;
    }
}


