/*!
  * @file     LQ_GPSR.h
  *
  * @brief    ÿ��CPU��4������ж�
  *
  * @company  �����������ܿƼ�
  *
  * @author   LQ-005
  *
  * @note     Tab�� 4���ո�
  *
  * @version  V1.0
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2020��5��6��
  */ 
#ifndef SRC_APPSW_TRICORE_DRIVER_LQ_GPSR_H_
#define SRC_APPSW_TRICORE_DRIVER_LQ_GPSR_H_

#include "../../Libraries/iLLD/TC29B/Tricore/_Impl/IfxSrc_cfg.h"

/***********************************************************************************************/
/***********************************************************************************************/
/*****************    CPU�ж����ȼ� �� ָ���ں����� �û����������޸�*******************************/
/***********************************************************************************************/
/***********************************************************************************************/

/**
 * ����е����ö��
 */
typedef enum
{
	SoftIRQ0,
	SoftIRQ1,
	SoftIRQ2,
	SoftIRQ3
}SOFT_IRQ;

void GPSR_InitConfig(IfxSrc_Tos cpu, SOFT_IRQ index);
void CPSR_Trig(IfxSrc_Tos cpu, SOFT_IRQ index);

#endif /* SRC_APPSW_TRICORE_DRIVER_LQ_GPSR_H_ */
