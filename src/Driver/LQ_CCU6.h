/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨�������������ܿƼ�TC387QP���İ�
����    д��chiusir
��E-mail��chiusir@163.com
������汾��V1.1 ��Ȩ���У���λʹ��������ϵ��Ȩ
�������¡�2021��5��18��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://longqiu.taobao.com
------------------------------------------------
��dev.env.��AURIX Development Studio1.4�����ϰ汾
��Target �� TC387QP
��Crystal�� 20.000Mhz
��SYS PLL�� 200/300MHz
________________________________________________________________
����iLLD_1_0_1_11_0�ײ����,

ʹ�����̵�ʱ�򣬽������û�пո��Ӣ��·����
����CIFΪTC264DA�����⣬�����Ĵ������TC264D
����Ĭ�ϳ�ʼ����EMEM��512K������û�ʹ��TC264D��ע�͵�EMEM_InitConfig()��ʼ��������
������\Libraries\iLLD\TC26B\Tricore\Cpu\CStart\IfxCpu_CStart0.c��164�����ҡ�
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ
*  ��    ע��TC264 ������CCU6ģ��  ÿ��ģ��������������ʱ��  ������ʱ���ж�
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#ifndef SRC_APPSW_TRICORE_DRIVER_LQ_CCU6_H_
#define SRC_APPSW_TRICORE_DRIVER_LQ_CCU6_H_



/**
 * 	CCU6ģ��ö��
 */
typedef enum
{
	CCU60,
	CCU61
}CCU6_t;

/**
 * 	CCU6ͨ��ö��
 */
typedef enum
{
	CCU6_Channel0,
	CCU6_Channel1,
}CCU6_Channel_t;

/*************************************************************************
*  �������ƣ�CCU6_InitConfig CCU6
*  ����˵������ʱ�������жϳ�ʼ��
*  ����˵����ccu6    �� ccu6ģ��            CCU60 �� CCU61
*  ����˵����channel �� ccu6ģ��ͨ��  CCU6_Channel0 �� CCU6_Channel1
*  ����˵����us      �� ccu6ģ��  �ж�����ʱ��  ��λus
*  �������أ���
*  �޸�ʱ�䣺2020��3��30��
*  ��    ע��
*************************************************************************/
void CCU6_InitConfig(CCU6_t ccu6, CCU6_Channel_t channel, unsigned long us);

void CCU6_DisableInterrupt(CCU6_t ccu6, CCU6_Channel_t channel);

void CCU6_EnableInterrupt(CCU6_t ccu6, CCU6_Channel_t channel);

#endif /* SRC_APPSW_TRICORE_DRIVER_LQ_CCU6_H_ */
