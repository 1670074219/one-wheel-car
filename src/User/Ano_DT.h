#ifndef __ANO_DT_H
#define __ANO_DT_H

#include "include.h"

//数据拆分宏定义，在发送大于1字节的数据类型时，比如int16、float等，需要把数据拆分成单独字节进行发送
#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)) )
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )

void sent_2_data(sint16 A,sint16 B);
void sent_3_data(sint16 A,sint16 B,sint16 C);
void sent_4_data(sint16 A,sint16 B,sint16 C,sint16 D);
void sent_5_data(sint16 A,sint16 B,sint16 C,sint16 D,sint16 E);

#endif /*__ANO_DT_H*/
