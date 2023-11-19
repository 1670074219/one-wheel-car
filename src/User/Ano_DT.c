#include "Ano_DT.h" //������λ��

uint8 BUFF[30];

void sent_2_data(sint16 A,sint16 B)
{
    int i;
    uint8 sumcheck = 0;
    uint8 addcheck = 0;
    uint8 _cnt=0;
    BUFF[_cnt++]=0xAA;//֡ͷ
    BUFF[_cnt++]=0xFF;//Ŀ���ַ
    BUFF[_cnt++]=0XF1;//������
    BUFF[_cnt++]=0x04;//���ݳ���
    BUFF[_cnt++]=BYTE0(A);//��������,С��ģʽ����λ��ǰ
    BUFF[_cnt++]=BYTE1(A);//��Ҫ���ֽڽ��в�֣���������ĺ궨�弴�ɡ�
    BUFF[_cnt++]=BYTE0(B);
    BUFF[_cnt++]=BYTE1(B);
    //SC��AC��У��ֱ�ӳ�������������ļ���
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
    BUFF[_cnt++]=0xAA;//֡ͷ
    BUFF[_cnt++]=0xFF;//Ŀ���ַ
    BUFF[_cnt++]=0XF1;//������
    BUFF[_cnt++]=0x06;//���ݳ���
    BUFF[_cnt++]=BYTE0(A);//��������,С��ģʽ����λ��ǰ
    BUFF[_cnt++]=BYTE1(A);//��Ҫ���ֽڽ��в�֣���������ĺ궨�弴�ɡ�
    BUFF[_cnt++]=BYTE0(B);
    BUFF[_cnt++]=BYTE1(B);
    BUFF[_cnt++]=BYTE0(C);
    BUFF[_cnt++]=BYTE1(C);
    //SC��AC��У��ֱ�ӳ�������������ļ���
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
    BUFF[_cnt++]=0xAA;//֡ͷ
    BUFF[_cnt++]=0xFF;//Ŀ���ַ
    BUFF[_cnt++]=0XF1;//������
    BUFF[_cnt++]=0x08;//���ݳ���
    BUFF[_cnt++]=BYTE0(A);//��������,С��ģʽ����λ��ǰ
    BUFF[_cnt++]=BYTE1(A);//��Ҫ���ֽڽ��в�֣���������ĺ궨�弴�ɡ�
    BUFF[_cnt++]=BYTE0(B);
    BUFF[_cnt++]=BYTE1(B);
    BUFF[_cnt++]=BYTE0(C);
    BUFF[_cnt++]=BYTE1(C);
    BUFF[_cnt++]=BYTE0(D);
    BUFF[_cnt++]=BYTE1(D);
    //SC��AC��У��ֱ�ӳ�������������ļ���
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
    BUFF[_cnt++]=0xAA;//֡ͷ
    BUFF[_cnt++]=0xFF;//Ŀ���ַ
    BUFF[_cnt++]=0XF1;//������
    BUFF[_cnt++]=0x0A;//���ݳ���
    BUFF[_cnt++]=BYTE0(A);//��������,С��ģʽ����λ��ǰ
    BUFF[_cnt++]=BYTE1(A);//��Ҫ���ֽڽ��в�֣���������ĺ궨�弴�ɡ�
    BUFF[_cnt++]=BYTE0(B);
    BUFF[_cnt++]=BYTE1(B);
    BUFF[_cnt++]=BYTE0(C);
    BUFF[_cnt++]=BYTE1(C);
    BUFF[_cnt++]=BYTE0(D);
    BUFF[_cnt++]=BYTE1(D);
    BUFF[_cnt++]=BYTE0(E);
    BUFF[_cnt++]=BYTE1(E);
    //SC��AC��У��ֱ�ӳ�������������ļ���
    for(i=0;i<BUFF[3]+4;i++)
    {
        sumcheck+=BUFF[i];
        addcheck+=sumcheck;
    }
    BUFF[_cnt++]=sumcheck;
    BUFF[_cnt++]=addcheck;

    UART_PutBuff(UART0, BUFF, _cnt);
}
