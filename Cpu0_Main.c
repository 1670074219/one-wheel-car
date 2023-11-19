#include "include.h"

App_Cpu0 g_AppCpu0;                     // brief CPU 0 global data
IfxCpu_mutexLock mutexCpu0InitIsOk = 1; // CPU0 ��ʼ����ɱ�־λ
volatile char mutexCpu0TFTIsOk = 0;     // CPU1 0ռ��/1�ͷ� TFT
IFX_ALIGN(4)
IfxCpu_syncEvent g_cpuSyncEvent = 0;

/**************��ʼ������***************/
unsigned char res;
char  txt[30];
float BAT=0.0;
int DMP_num=0;

/**************�������***************/
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
    // �ر�CPU���ж�
    IfxCpu_disableInterrupts();

    // �رտ��Ź�����������ÿ��Ź�ι����Ҫ�ر�
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());

    // ��ȡ����Ƶ��
    g_AppCpu0.info.pllFreq = IfxScuCcu_getPllFrequency();
    g_AppCpu0.info.cpuFreq = IfxScuCcu_getCpuFrequency(IfxCpu_getCoreIndex());
    g_AppCpu0.info.sysFreq = IfxScuCcu_getSpbFrequency();
    g_AppCpu0.info.stmFreq = IfxStm_getFrequency(&MODULE_STM0);

    /**************��ʼ����ʼ***************/
    //��Ļ��ʼ��
    TFTSPI_Init(0);               // TFT1.8��ʼ��0:����  1������
    TFTSPI_CLS(u16CYAN);          // ����
    TFTSPI_Show_Logo(0,37);       // ��ʾ����LOGO
    TFTSPI_P16x16Str(0,0,(unsigned char*)"�����������ܿƼ�",u16RED,u16BLUE);// �ַ�����ʾ
    //��ȡ����
    //data_read();
    //PID��ʼ��
    PID_all_init();
    //Flash��ȡ����
    Read_Parameter();
    //��ʱ
    delayms(1000);
    //������ʼ��
    GPIO_KEY_Init();
    //LED��ʼ��
    GPIO_LED_Init();
    //ɲ���߳�ʼ��
    PIN_InitConfig(DIN, PIN_MODE_OUTPUT, 1);
    DIN_OFF;
    //��������ʼ��
    PIN_InitConfig(Beep, PIN_MODE_OUTPUT, 1);
    Beep_OFF;
    //�����ʼ��
    PIN_InitConfig(P00_5, PIN_MODE_INPUT, 1);
    //���ڳ�ʼ��
    UART_InitConfig(UART0_RX_P14_1, UART0_TX_P14_0, 115200);
    delayms(100);
    UART_PutStr(UART0, "LQ UART0 START...\r\n");
    printf("printf ok\n");
    //����ͷ��ʼ��
    CAMERA_Init(50);
    //mpu6050��ʼ��
    IIC_Init();                     //IIC��ʼ��//IIC��ʼ��
    delayms(100);
    res = Gyro_Chose();             //�ж��������ͺ�
    MPU6050_Init();                 //�����ǳ�ʼ��*/
    //�����ʼ��
    MotorInit();                    //�����ʼ��
    DIN_OFF;                        //ɲ��
    MotorCtrl3W(0,0,0);             //���� ���ֶ�ֹͣ4
    //��������ʼ��
    EncInit();                      //��������ʼ��
    //DMP��ʼ��
    LQ_DMP_Init();                  //DMP��ʼ��
    TFTSPI_Init(2);                 //��Ļ��ʼ��Ϊ���� ����ʾ
    TFTSPI_CLS(u16CYAN);            //��������ɫ
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
     TFTSPI_CLS(u16CYAN);            //��������ɫ
     //ADC��ʼ��
     ADC_InitConfig(ADC7, 80000);    //ADC�ɼ���ѹ��ʼ��
     // ��ʱ��1ͨ��0��ʼ��,�жϺ�����CCU6.C�� */
     CCU6_InitConfig(CCU61, CCU6_Channel0, 2000);// 2ms
     /**************��ʼ������***************/

    // ����CPU���ж�
    IfxCpu_enableInterrupts();
    // ֪ͨCPU2��CPU1��CPU0��ʼ�����
    IfxCpu_releaseMutex(&mutexCpu0InitIsOk);
    // �м�CPU0,CPU1...������ͬʱ������Ļ��ʾ�������ͻ����ʾ
    mutexCpu0TFTIsOk = 0; // CPU1�� 0ռ��/1�ͷ� TFT
    // �ȴ�ͬ��
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 10);

    /**************����Ĭ���ٶ�***************/
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
    /**************�˵�***************/
    Menu_Switch();

    while (1)
    {

    }
}
