#include "Ano_DT.h" //匿名上位机

uint8 BUFF[30];

void sent_2_data(sint16 A,sint16 B)
{
    int i;
    uint8 sumcheck = 0;
    uint8 addcheck = 0;
    uint8 _cnt=0;
    BUFF[_cnt++]=0xAA;//帧头
    BUFF[_cnt++]=0xFF;//目标地址
    BUFF[_cnt++]=0XF1;//功能码
    BUFF[_cnt++]=0x04;//数据长度
    BUFF[_cnt++]=BYTE0(A);//数据内容,小段模式，低位在前
    BUFF[_cnt++]=BYTE1(A);//需要将字节进行拆分，调用上面的宏定义即可。
    BUFF[_cnt++]=BYTE0(B);
    BUFF[_cnt++]=BYTE1(B);
    //SC和AC的校验直接抄最上面上面简介的即可
    for(i=0;i<BUFF[3]+4;i++)
    {
        sumcheck+=BUFF[i];
        addcheck+=sumcheck;
    }
    BUFF[_cnt++]=sumcheck;
    BUFF[_cnt++]=addcheck;

    UART_PutBuff(UART0, BUFF, _cnt);
}

void sent_3_data(sint16 A,sint16 B,sint16 C)
{
    int i;
    uint8 sumcheck = 0;
    uint8 addcheck = 0;
    uint8 _cnt=0;
    BUFF[_cnt++]=0xAA;//帧头
    BUFF[_cnt++]=0xFF;//目标地址
    BUFF[_cnt++]=0XF1;//功能码
    BUFF[_cnt++]=0x06;//数据长度
    BUFF[_cnt++]=BYTE0(A);//数据内容,小段模式，低位在前
    BUFF[_cnt++]=BYTE1(A);//需要将字节进行拆分，调用上面的宏定义即可。
    BUFF[_cnt++]=BYTE0(B);
    BUFF[_cnt++]=BYTE1(B);
    BUFF[_cnt++]=BYTE0(C);
    BUFF[_cnt++]=BYTE1(C);
    //SC和AC的校验直接抄最上面上面简介的即可
    for(i=0;i<BUFF[3]+4;i++)
    {
        sumcheck+=BUFF[i];
        addcheck+=sumcheck;
    }
    BUFF[_cnt++]=sumcheck;
    BUFF[_cnt++]=addcheck;

    UART_PutBuff(UART0, BUFF, _cnt);
}

void sent_4_data(sint16 A,sint16 B,sint16 C,sint16 D)
{
    int i;
    uint8 sumcheck = 0;
    uint8 addcheck = 0;
    uint8 _cnt=0;
    BUFF[_cnt++]=0xAA;//帧头
    BUFF[_cnt++]=0xFF;//目标地址
    BUFF[_cnt++]=0XF1;//功能码
    BUFF[_cnt++]=0x08;//数据长度
    BUFF[_cnt++]=BYTE0(A);//数据内容,小段模式，低位在前
    BUFF[_cnt++]=BYTE1(A);//需要将字节进行拆分，调用上面的宏定义即可。
    BUFF[_cnt++]=BYTE0(B);
    BUFF[_cnt++]=BYTE1(B);
    BUFF[_cnt++]=BYTE0(C);
    BUFF[_cnt++]=BYTE1(C);
    BUFF[_cnt++]=BYTE0(D);
    BUFF[_cnt++]=BYTE1(D);
    //SC和AC的校验直接抄最上面上面简介的即可
    for(i=0;i<BUFF[3]+4;i++)
    {
        sumcheck+=BUFF[i];
        addcheck+=sumcheck;
    }
    BUFF[_cnt++]=sumcheck;
    BUFF[_cnt++]=addcheck;

    UART_PutBuff(UART0, BUFF, _cnt);
}

void sent_5_data(sint16 A,sint16 B,sint16 C,sint16 D,sint16 E)
{
    int i;
    uint8 sumcheck = 0;
    uint8 addcheck = 0;
    uint8 _cnt=0;
    BUFF[_cnt++]=0xAA;//帧头
    BUFF[_cnt++]=0xFF;//目标地址
    BUFF[_cnt++]=0XF1;//功能码
    BUFF[_cnt++]=0x0A;//数据长度
    BUFF[_cnt++]=BYTE0(A);//数据内容,小段模式，低位在前
    BUFF[_cnt++]=BYTE1(A);//需要将字节进行拆分，调用上面的宏定义即可。
    BUFF[_cnt++]=BYTE0(B);
    BUFF[_cnt++]=BYTE1(B);
    BUFF[_cnt++]=BYTE0(C);
    BUFF[_cnt++]=BYTE1(C);
    BUFF[_cnt++]=BYTE0(D);
    BUFF[_cnt++]=BYTE1(D);
    BUFF[_cnt++]=BYTE0(E);
    BUFF[_cnt++]=BYTE1(E);
    //SC和AC的校验直接抄最上面上面简介的即可
    for(i=0;i<BUFF[3]+4;i++)
    {
        sumcheck+=BUFF[i];
        addcheck+=sumcheck;
    }
    BUFF[_cnt++]=sumcheck;
    BUFF[_cnt++]=addcheck;

    UART_PutBuff(UART0, BUFF, _cnt);
}
