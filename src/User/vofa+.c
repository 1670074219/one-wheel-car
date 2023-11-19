#include "vofa+.h" //vofa免费上位机协议 justfloat


#define VOFA_UART                       UART0
#define vofa_uart_write_buffer          UART_PutBuff

//vofa+ justfloat类型发送数据
void vofa_send_2_data(float data0, float data1)
{
    uint8 BUFF[30] = {0};
    uint8 _cnt=0;
    BUFF[_cnt++]=BYTE0(data0);
    BUFF[_cnt++]=BYTE1(data0);
    BUFF[_cnt++]=BYTE2(data0);
    BUFF[_cnt++]=BYTE3(data0);

    BUFF[_cnt++]=BYTE0(data1);
    BUFF[_cnt++]=BYTE1(data1);
    BUFF[_cnt++]=BYTE2(data1);
    BUFF[_cnt++]=BYTE3(data1);

    BUFF[_cnt++]=0x00;
    BUFF[_cnt++]=0x00;
    BUFF[_cnt++]=0x80;
    BUFF[_cnt++]=0x7f;

    vofa_uart_write_buffer(VOFA_UART, BUFF, _cnt);
}

void vofa_send_4_data(float data0, float data1, float data2, float data3)
{
    uint8 BUFF[30] = {0};
    uint8 _cnt=0;
    BUFF[_cnt++]=BYTE0(data0);
    BUFF[_cnt++]=BYTE1(data0);
    BUFF[_cnt++]=BYTE2(data0);
    BUFF[_cnt++]=BYTE3(data0);

    BUFF[_cnt++]=BYTE0(data1);
    BUFF[_cnt++]=BYTE1(data1);
    BUFF[_cnt++]=BYTE2(data1);
    BUFF[_cnt++]=BYTE3(data1);

    BUFF[_cnt++]=BYTE0(data2);
    BUFF[_cnt++]=BYTE1(data2);
    BUFF[_cnt++]=BYTE2(data2);
    BUFF[_cnt++]=BYTE3(data2);

    BUFF[_cnt++]=BYTE0(data3);
    BUFF[_cnt++]=BYTE1(data3);
    BUFF[_cnt++]=BYTE2(data3);
    BUFF[_cnt++]=BYTE3(data3);

    BUFF[_cnt++]=0x00;
    BUFF[_cnt++]=0x00;
    BUFF[_cnt++]=0x80;
    BUFF[_cnt++]=0x7f;

    vofa_uart_write_buffer(VOFA_UART, BUFF, _cnt);
}

void vofa_send_6_data(float data0, float data1, float data2, float data3, float data4, float data5)
{
    uint8 BUFF[30] = {0};
    uint8 _cnt=0;
    BUFF[_cnt++]=BYTE0(data0);
    BUFF[_cnt++]=BYTE1(data0);
    BUFF[_cnt++]=BYTE2(data0);
    BUFF[_cnt++]=BYTE3(data0);

    BUFF[_cnt++]=BYTE0(data1);
    BUFF[_cnt++]=BYTE1(data1);
    BUFF[_cnt++]=BYTE2(data1);
    BUFF[_cnt++]=BYTE3(data1);

    BUFF[_cnt++]=BYTE0(data2);
    BUFF[_cnt++]=BYTE1(data2);
    BUFF[_cnt++]=BYTE2(data2);
    BUFF[_cnt++]=BYTE3(data2);

    BUFF[_cnt++]=BYTE0(data3);
    BUFF[_cnt++]=BYTE1(data3);
    BUFF[_cnt++]=BYTE2(data3);
    BUFF[_cnt++]=BYTE3(data3);

    BUFF[_cnt++]=BYTE0(data4);
    BUFF[_cnt++]=BYTE1(data4);
    BUFF[_cnt++]=BYTE2(data4);
    BUFF[_cnt++]=BYTE3(data4);

    BUFF[_cnt++]=BYTE0(data5);
    BUFF[_cnt++]=BYTE1(data5);
    BUFF[_cnt++]=BYTE2(data5);
    BUFF[_cnt++]=BYTE3(data5);

    BUFF[_cnt++]=0x00;
    BUFF[_cnt++]=0x00;
    BUFF[_cnt++]=0x80;
    BUFF[_cnt++]=0x7f;

    vofa_uart_write_buffer(VOFA_UART, BUFF, _cnt);
}



