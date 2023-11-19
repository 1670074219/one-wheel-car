#ifndef __CROSS_H
#define __CROSS_H

#include "include.h"

extern uint8 cross_count;
extern sint16 cross_s;
extern float corss_encoder;
extern uint8 cross_flag;

extern float cross_l_turn_offset;
extern float cross_l_turn_angle;
extern float cross_r_turn_offset;
extern float cross_r_turn_angle;

extern float cross_turn_angle;
extern uint8 cross_turn_flag;
void Handle_cross_l_turn(void);
void Handle_cross_r_turn(void);

void Handle_Cross(void);
void Handle_L_Cross(void);
void Handle_R_Cross(void);

#endif /*__CROSS_H*/
