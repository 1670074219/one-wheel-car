#ifndef __CIRQUE_H
#define __CIRQUE_H

#include "include.h"

extern float l_angle_in;
extern float l_angle_out;
extern float r_angle_in;
extern float r_angle_out;

void Handle_Left_Cirque(void);
void Handle_Right_Cirque(void);

extern int circle_flag;
extern uint8 huandao_stage;
extern uint8 huandao_flag;
extern float huandao_angle;

extern uint32 dont_handle_encoder;
extern uint16 dont_handle_flag;
void Dont_handle_l_cirque(void);
void Dont_handle_r_cirque(void);
#endif /*__CIRQUE_H*/
