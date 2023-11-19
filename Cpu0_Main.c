#include "include.h"

App_Cpu0 g_AppCpu0;                     // brief CPU 0 global data
IfxCpu_mutexLock mutexCpu0InitIsOk = 1; // CPU0 初始化完成标志位
volatile char mutexCpu0TFTIsOk = 0;     // CPU1 0占用/1释放 TFT
IFX_ALIGN(4)
IfxCpu_syncEvent g_cpuSyncEvent = 0;

/**************初始化变量***************/
unsigned char res;
char  txt[30];
float BAT=0.0;
int DMP_num=0;

/**************出库变量***************/
float cheku_out_finish_flag = 0;
float cheku_offset = 70;
float cheku_out_angle = 0;
float cheku_angle_set = 35;
float cheku_out_encoder = 0;
float cheku_out_encoder_set = 2000;
uint8 cheku_stage = 0;
float cheku_fangxiang = 0;
uint8 fache_flag = 0;

int core0_main(void)
{
    // 关闭CPU总中断
    IfxCpu_disableInterrupts();

    // 关闭看门狗，如果不设置看门狗喂狗需要关闭
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());

    // 读取总线频率
    g_AppCpu0.info.pllFreq = IfxScuCcu_getPllFrequency();
    g_AppCpu0.info.cpuFreq = IfxScuCcu_getCpuFrequency(IfxCpu_getCoreIndex());
    g_AppCpu0.info.sysFreq = IfxScuCcu_getSpbFrequency();
    g_AppCpu0.info.stmFreq = IfxStm_getFrequency(&MODULE_STM0);

    /**************初始化开始***************/
    //屏幕初始化
    TFTSPI_Init(0);               // TFT1.8初始化0:横屏  1：竖屏
    TFTSPI_CLS(u16CYAN);          // 清屏
    TFTSPI_Show_Logo(0,37);       // 显示龙邱LOGO
    TFTSPI_P16x16Str(0,0,(unsigned char*)"北京龙邱智能科技",u16RED,u16BLUE);// 字符串显示
    //读取参数
    //data_read();
    //PID初始化
    PID_all_init();
    //Flash读取参数
    Read_Parameter();
    //延时
    delayms(1000);
    //按键初始化
    GPIO_KEY_Init();
    //LED初始化
    GPIO_LED_Init();
    //刹车线初始化
    PIN_InitConfig(DIN, PIN_MODE_OUTPUT, 1);
    DIN_OFF;
    //蜂鸣器初始化
    PIN_InitConfig(Beep, PIN_MODE_OUTPUT, 1);
    Beep_OFF;
    //红外初始化
    PIN_InitConfig(P00_5, PIN_MODE_INPUT, 1);
    //串口初始化
    UART_InitConfig(UART0_RX_P14_1, UART0_TX_P14_0, 115200);
    delayms(100);
    UART_PutStr(UART0, "LQ UART0 START...\r\n");
    printf("printf ok\n");
    //摄像头初始化
    CAMERA_Init(50);
    //mpu6050初始化
    IIC_Init();                     //IIC初始化//IIC初始化
    delayms(100);
    res = Gyro_Chose();             //判断陀螺仪型号
    MPU6050_Init();                 //陀螺仪初始化*/
    //电机初始化
    MotorInit();                    //电机初始化
    DIN_OFF;                        //刹车
    MotorCtrl3W(0,0,0);             //飞轮 独轮都停止4
    //编码器初始化
    EncInit();                      //编码器初始化
    //DMP初始化
    LQ_DMP_Init();                  //DMP初始化
    TFTSPI_Init(2);                 //屏幕初始化为竖屏 倒显示
    TFTSPI_CLS(u16CYAN);            //清屏蓝绿色
    do{
        LQ_DMP_Read();
        sprintf((char*)txt,"%06d",gyro[0]);
        TFTSPI_P8X8Str(9,15,txt,u16RED,u16BLACK);
        sprintf((char*)txt,"%06d",gyro[1]);
        TFTSPI_P8X8Str(9,16,txt,u16RED,u16BLACK);
        sprintf((char*)txt,"%06d",DMP_num++);
        TFTSPI_P8X16Str(0,0,txt,u16RED,u16BLACK);

        sprintf((char*)txt,"Don`t move me!!!");
        TFTSPI_P8X16Str(0,2,txt,u16RED,u16BLACK);
        sprintf((char*)txt,"Don`t move me!!!");
        TFTSPI_P8X16Str(0,4,txt,u16YELLOW,u16BLACK);
        }while(!(abs(gyro[0])<2 && abs(gyro[1])<2 && abs(gyro[2])<2));
     TFTSPI_CLS(u16CYAN);            //清屏蓝绿色
     //ADC初始化
     ADC_InitConfig(ADC7, 80000);    //ADC采集电压初始化
     // 定时器1通道0初始化,中断函数在CCU6.C中 */
     CCU6_InitConfig(CCU61, CCU6_Channel0, 2000);// 2ms
     /**************初始化结束***************/

    // 开启CPU总中断
    IfxCpu_enableInterrupts();
    // 通知CPU2、CPU1，CPU0初始化完成
    IfxCpu_releaseMutex(&mutexCpu0InitIsOk);
    // 切记CPU0,CPU1...不可以同时开启屏幕显示，否则冲突不显示
    mutexCpu0TFTIsOk = 0; // CPU1： 0占用/1释放 TFT
    // 等待同步
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 10);

    /**************设置默认速度***************/
    if(cheku_out_finish_flag == 0)
    {
        speed = 0;
        offset = 0;
    }
    else
    {
        speed = f32wBuff[21];
        offset = 0;
    }
    /**************菜单***************/
    Menu_Switch();

    while (1)
    {

    }
}
