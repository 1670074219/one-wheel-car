#ifndef __ANO_DT_H
#define __ANO_DT_H

#include "include.h"

//���ݲ�ֺ궨�壬�ڷ��ʹ���1�ֽڵ���������ʱ������int16��float�ȣ���Ҫ�����ݲ�ֳɵ����ֽڽ��з���
#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)) )
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )

void sent_2_data(sint16 A,sint16 B);
void sent_3_data(sint16 A,sint16 B,sint16 C);
void sent_4_data(sint16 A,sint16 B,sint16 C,sint16 D);
void sent_5_data(sint16 A,sint16 B,sint16 C,sint16 D,sint16 E);

#endif /*__ANO_DT_H*/
