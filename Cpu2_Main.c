/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨�������������ܿƼ�TC297TX���İ�
����    д��chiusir
��E-mail��chiusir@163.com
������汾��V1.1 ��Ȩ���У���λʹ��������ϵ��Ȩ
�������¡�2021��10��28��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://longqiu.taobao.com
------------------------------------------------
��dev.env.��AURIX Development Studio1.4�����ϰ汾
��Target �� TC297TX
��Crystal�� 20.000Mhz
��SYS PLL�� 300MHz*3
________________________________________________________________
����iLLD_1_0_1_11_0�ײ����,

ʹ�����̵�ʱ�򣬽������û�пո��Ӣ��·�����л�workspace����ǰ���������ļ��У�
����RIFΪTC3xxxA�����⣬�����Ĵ������TC3xx
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#include <IfxCpu.h>
#include <IfxScuWdt.h>
#include "src/APP/LQ_CAMERA.h"
#include "src/APP/LQ_GPIO_KEY.h"
#include "src/APP/LQ_GPIO_LED.h"

#include "src/APP/LQ_I2C_VL53.h"
#include "src/APP/LQ_ICM20602.h"
#include "src/APP/LQ_OLED096.h"
#include "src/APP/LQ_RDA5807.h"
#include "src/APP/LQ_TFT18.h"
#include "src/APP/LQ_TFT2.h"
#include "src/Driver/include.h"//����ģ���ͷ�ļ�
#include "src/Driver/LQ_STM.h"
#include "src/Driver/LQ_UART.h"
#include "src/User/LQ_MotorServo.h"
#include "src/Driver/LQ_CCU6.h"

extern IfxCpu_syncEvent g_cpuSyncEvent;

int core2_main(void)
{
    IfxCpu_enableInterrupts();
    
    /* !!WATCHDOG2 IS DISABLED HERE!!
     * Enable the watchdog and service it periodically if it is required
     */
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    
    /* Wait for CPU sync event */
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);

    while(1)
    {
        // �Ŷ����͸�����CORE0��CORE1��Ϊɶ�أ�
    }
    return (1);
}
