#ifndef __IMAGE_PROCESS_H
#define __IMAGE_PROCESS_H

#include "include.h"

#define MT9V03X_H 120
#define MT9V03X_W 180

//�������ͽṹ��
struct ROAD_TYPE
{
     sint8 straight;         //ֱ��
     sint8 bend;             //���
     sint8 Ramp;             //�µ�
     sint8 Cross;            //ʮ��
     sint8 L_Cross;          //����ʮ��
     sint8 R_Cross;          //����ʮ��
     sint8 LeftCirque;       //�󻷵�
     sint8 RightCirque;      //�һ���
     sint8 Fork;             //�����
     sint8 Barn_l_out;       //�����
     sint8 Barn_r_out;       //���ҿ�
     sint8 Barn_l_in;        //�����
     sint8 Barn_r_in;        //���ҿ�
     sint8 Podao;            //�µ�
     sint8 ZhangAi;          //�ϰ�
     sint8 Duanlu;
};
extern struct ROAD_TYPE road_type;
extern struct SPEED_DECESION element_speed;

//�������ͽṹ��
struct SPEED_DECESION
{
     float straight_speed;         //ֱ��
     float bend_speed;             //���
     float Ramp_speed;             //�µ�
     float Cross_speed;            //ʮ��
     float Cirque_speed;           //����
     float DotCirque_speed;        //��������
     float Podao_speed;            //�µ�
     float ZhangAi_speed;          //�ϰ�
     float Duanlu_speed;           //��·
};

extern float offset;
extern uint8 image_yuanshi[MT9V03X_H][MT9V03X_W];                    //ԭʼͼ��
extern uint8 image_01[MT9V03X_H][MT9V03X_W];                         //��ֵ��ͼ��
extern uint8 image_yuanshi_jianchai[MT9V03X_H/2][MT9V03X_W/2];
extern uint8 image_01_jianchai[MT9V03X_H/2][MT9V03X_W/2];
extern uint8 kuandu_saidao[MT9V03X_H];                               //Ĭ���������
extern uint8 kuan[MT9V03X_H];                                        //�����������
extern uint8 m_line_x[MT9V03X_H];                                    //�����������ߵ���
extern uint8 r_line_y[MT9V03X_H], l_line_y[MT9V03X_H];               //�������ұ߽������
extern uint8 r_line_x[MT9V03X_H], l_line_x[MT9V03X_H];               //����ԭʼͼ������ұ߽������
extern uint8 r_second_line_x[MT9V03X_H], l_second_line_x[MT9V03X_H]; //���油��֮������ұ߽�ֵ����δ�õ���
extern uint8 m_second_line_x[MT9V03X_H];                             //�����������ߵ���
extern uint8 r_lose_value, l_lose_value;                             //���Ҷ�����������ע��Ҫ��һ������
extern uint8 r_search_flag[MT9V03X_H], l_search_flag[MT9V03X_H];     //�Ƿ��ѵ��ߵı�־
extern uint8 r_losemax,l_losemax;
extern uint8 diuxian_hang, budiuxian_hang;
extern uint16 distance_L_Cross_out;
extern uint16 distance_R_Cross_out;
extern uint8 flag_L_shizi_R_turn;
extern uint8 flag_R_shizi_L_turn;
extern sint16 annulus_s1;
extern sint16 jiaodu_jifen;
extern sint16 annulus_jinku_s;
extern uint8 l_guaidain_x, l_guaidain_y;
extern uint8 r_guaidain_x, r_guaidain_y;
extern uint8 cross_left[2];  //��һ���±��ͼ���·��ĵ��yֵ
extern uint8 cross_right[2];
extern float parameterA, parameterB;

extern float trun;
extern float k_left,k_right;
extern float last_angle,now_angle;
extern float cross_first,cross_second;

extern sint16 l_line_qulv, r_line_qulv;
extern sint16 l_line_straight, r_line_straight;

extern uint8 obstacles_flag;
extern float Threshold_add;
extern uint8 Threshold;

//ͼ����
void Transfer_Camera(void);                                         //ͼ��ת��
uint8 otsuThreshold(uint8 *image, uint16 col, uint16 row);          //���
uint8 my_adapt_threshold(uint8 *image, uint16 col, uint16 row);     //�Ż���Ĵ��
void Get01change_Dajin(void);                                       //��ֵ��
void Pixle_Filter(void);                                            //��ʴ
void Search_Line(uint8 type);                                       //����:0Ϊ��ͨģʽ��1Ϊ������ģʽ��ֻ��������ʼ�����겻ͬ��
void yuanshi_jianchai(void);                                        //ԭʼͼ�����
void erzhihua_jianchai(void);                                       //��ֵ��ͼ�����

//��ѧ����
float Process_Curvity(uint8 x1, uint8 y1, uint8 x2, uint8 y2, uint8 x3, uint8 y3);    //������������
sint16 Distance_Measure(void);                                                        //���������ֳ�λ��
int Angle_Measure(void);                                                              //�����ǻ��ֳɽǶ�
uint8 My_Sqrt(sint16 x);                                                              //����
void Regression(uint8 type, uint8 startline, uint8 endline);                          //��С���˷�����б�ʺͽؾ�

//������ж�
void Mid_Col(void);                                                                   //�������
void Diuxian_weizhi_test(uint8 type, uint8 startline, uint8 endline);                 //�ж϶�����
void Bianxian_guaidian(uint8 type, uint8 startline, uint8 endline);                   //�ҹյ�
void Check_Cross_Guaidian(uint8 type);                                                //���ʮ�ֹյ�

//���ߴ���
void La_zhixian(uint8 x_down, uint8 y_down, uint8 x_up, uint8 y_up, uint8 *array);             //��ֱ��
void Hua_Xian(uint8 type, uint8 startline, uint8 endline, float parameterB, float parameterA); //����


//Ԫ��ʶ��
void Check_Zhidao(void);
void Element_Test(void);

//Ԫ�ش���
void Element_Handle(void);

//�ܴ���
void Camera_Display(void);

void check_cheku(uint8 start_point, uint8 end_point ,uint8 qiangdu);

void Calculate_Offset_d(void);
#endif /*__IMAGE_PROCESS_H*/
