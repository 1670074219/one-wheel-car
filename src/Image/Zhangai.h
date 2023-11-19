/*
 * Zhangai.h
 *
 *  Created on: 2023��4��27��
 *      Author: lan
 */

#ifndef SRC_IMAGE_ZHANGAI_H_
#define SRC_IMAGE_ZHANGAI_H_

#include "include.h"

extern uint8 zhangai_once_flag;
extern uint8 zhangai_flag;
extern uint8 zhangai_stage;
extern float zhangai_angle;

extern float zhangai_offset0;
extern float zhangai_angle0;
extern float zhangai_offset1;
extern float zhangai_angle1;
extern float zhangai_offset2;
extern float zhangai_angle2;

extern float zhangai_dir;

void Handle_ZhangAi(void);

#endif /* SRC_IMAGE_ZHANGAI_H_ */
