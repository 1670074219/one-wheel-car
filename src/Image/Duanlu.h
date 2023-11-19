/*
 * Duanlu.h
 *
 *  Created on: 2023Äê7ÔÂ8ÈÕ
 *      Author: lan
 */

#ifndef SRC_IMAGE_DUANLU_H_
#define SRC_IMAGE_DUANLU_H_

#include "include.h"

extern uint8 Duanlu_stage;
extern uint8 Duanlu_flag;
extern float Duanlu_angle;
extern uint8 duanlu_white_count;
extern uint8 duanlu_once_flag;

extern float Duanlu_offset0;
extern float Duanlu_angle0;
extern float Duanlu_offset1;
extern float Duanlu_angle1;
extern float Duanlu_encoder_set;

extern float duanlu_seek_road;
extern float Duanlu_Flag1;
extern uint8 dont_handle_cirque;
extern uint8 duanlu_offset_limit_flag;

extern float Duanlu_set_angle;
extern float Duanlu_back_speed;
extern float duanlu_select;
extern uint8 duanlu_finish_stage;

void Handle_Duanlu(void);
void Handle_Duanlu1(void);

#endif /* SRC_IMAGE_DUANLU_H_ */
