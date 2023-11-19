/*
 * Zhangai.h
 *
 *  Created on: 2023Äê4ÔÂ27ÈÕ
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
