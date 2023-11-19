/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【平    台】北京龙邱智能科技TC297TX核心板
【编    写】chiusir
【E-mail】chiusir@163.com
【软件版本】V1.1 版权所有，单位使用请先联系授权
【最后更新】2021年10月28日
【相关信息参考下列地址】
【网    站】http://www.lqist.cn
【淘宝店铺】http://longqiu.taobao.com
------------------------------------------------
【dev.env.】AURIX Development Studio1.4及以上版本
【Target 】 TC297TX
【Crystal】 20.000Mhz
【SYS PLL】 300MHz*3
________________________________________________________________
基于iLLD_1_0_1_11_0底层程序,

使用例程的时候，建议采用没有空格的英文路径，切换workspace到当前工程所放文件夹！
除了RIF为TC3xxxA独有外，其它的代码兼容TC3xx
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
#include "src/Driver/include.h"//各个模块的头文件
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
        // 放东西就干扰了CORE0和CORE1，为啥呢？
    }
    return (1);
}
