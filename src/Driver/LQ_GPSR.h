/*!
  * @file     LQ_GPSR.h
  *
  * @brief    每个CPU有4个软件中断
  *
  * @company  北京龙邱智能科技
  *
  * @author   LQ-005
  *
  * @note     Tab键 4个空格
  *
  * @version  V1.0
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2020年5月6日
  */ 
#ifndef SRC_APPSW_TRICORE_DRIVER_LQ_GPSR_H_
#define SRC_APPSW_TRICORE_DRIVER_LQ_GPSR_H_

#include "../../Libraries/iLLD/TC29B/Tricore/_Impl/IfxSrc_cfg.h"

/***********************************************************************************************/
/***********************************************************************************************/
/*****************    CPU中断优先级 和 指向内核配置 用户可以自行修改*******************************/
/***********************************************************************************************/
/***********************************************************************************************/

/**
 * 软件中的序号枚举
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
