#ifndef __IMAGE_PROCESS_H
#define __IMAGE_PROCESS_H

#include "include.h"

#define MT9V03X_H 120
#define MT9V03X_W 180

//赛道类型结构体
struct ROAD_TYPE
{
     sint8 straight;         //直道
     sint8 bend;             //弯道
     sint8 Ramp;             //坡道
     sint8 Cross;            //十字
     sint8 L_Cross;          //入左十字
     sint8 R_Cross;          //入右十字
     sint8 LeftCirque;       //左环岛
     sint8 RightCirque;      //右环岛
     sint8 Fork;             //三岔口
     sint8 Barn_l_out;       //出左库
     sint8 Barn_r_out;       //出右库
     sint8 Barn_l_in;        //入左库
     sint8 Barn_r_in;        //入右库
     sint8 Podao;            //坡道
     sint8 ZhangAi;          //障碍
     sint8 Duanlu;
};
extern struct ROAD_TYPE road_type;
extern struct SPEED_DECESION element_speed;

//赛道类型结构体
struct SPEED_DECESION
{
     float straight_speed;         //直道
     float bend_speed;             //弯道
     float Ramp_speed;             //坡道
     float Cross_speed;            //十字
     float Cirque_speed;           //环岛
     float DotCirque_speed;        //不处理环岛
     float Podao_speed;            //坡道
     float ZhangAi_speed;          //障碍
     float Duanlu_speed;           //断路
};

extern float offset;
extern uint8 image_yuanshi[MT9V03X_H][MT9V03X_W];                    //原始图像
extern uint8 image_01[MT9V03X_H][MT9V03X_W];                         //二值化图像
extern uint8 image_yuanshi_jianchai[MT9V03X_H/2][MT9V03X_W/2];
extern uint8 image_01_jianchai[MT9V03X_H/2][MT9V03X_W/2];
extern uint8 kuandu_saidao[MT9V03X_H];                               //默认赛道宽带
extern uint8 kuan[MT9V03X_H];                                        //储存赛道宽带
extern uint8 m_line_x[MT9V03X_H];                                    //储存赛道中线的列
extern uint8 r_line_y[MT9V03X_H], l_line_y[MT9V03X_H];               //储存左右边界的行数
extern uint8 r_line_x[MT9V03X_H], l_line_x[MT9V03X_H];               //储存原始图像的左右边界的列数
extern uint8 r_second_line_x[MT9V03X_H], l_second_line_x[MT9V03X_H]; //储存补线之后的左右边界值（还未用到）
extern uint8 m_second_line_x[MT9V03X_H];                             //储存赛道中线的列
extern uint8 r_lose_value, l_lose_value;                             //左右丢线数，后面注意要走一次清零
extern uint8 r_search_flag[MT9V03X_H], l_search_flag[MT9V03X_H];     //是否搜到线的标志
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
extern uint8 cross_left[2];  //第一个下标存图像下方的点的y值
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

//图像处理
void Transfer_Camera(void);                                         //图像转存
uint8 otsuThreshold(uint8 *image, uint16 col, uint16 row);          //大津法
uint8 my_adapt_threshold(uint8 *image, uint16 col, uint16 row);     //优化后的大津法
void Get01change_Dajin(void);                                       //二值化
void Pixle_Filter(void);                                            //腐蚀
void Search_Line(uint8 type);                                       //搜线:0为普通模式，1为斑马线模式（只有搜线起始横坐标不同）
void yuanshi_jianchai(void);                                        //原始图像剪裁
void erzhihua_jianchai(void);                                       //二值化图像剪裁

//数学运算
float Process_Curvity(uint8 x1, uint8 y1, uint8 x2, uint8 y2, uint8 x3, uint8 y3);    //计算赛道曲率
sint16 Distance_Measure(void);                                                        //编码器积分成位移
int Angle_Measure(void);                                                              //陀螺仪积分成角度
uint8 My_Sqrt(sint16 x);                                                              //开方
void Regression(uint8 type, uint8 startline, uint8 endline);                          //最小二乘法计算斜率和截距

//特殊点判断
void Mid_Col(void);                                                                   //区别弯道
void Diuxian_weizhi_test(uint8 type, uint8 startline, uint8 endline);                 //判断丢线数
void Bianxian_guaidian(uint8 type, uint8 startline, uint8 endline);                   //找拐点
void Check_Cross_Guaidian(uint8 type);                                                //检查十字拐点

//补线处理
void La_zhixian(uint8 x_down, uint8 y_down, uint8 x_up, uint8 y_up, uint8 *array);             //拉直线
void Hua_Xian(uint8 type, uint8 startline, uint8 endline, float parameterB, float parameterA); //画线


//元素识别
void Check_Zhidao(void);
void Element_Test(void);

//元素处理
void Element_Handle(void);

//总处理
void Camera_Display(void);

void check_cheku(uint8 start_point, uint8 end_point ,uint8 qiangdu);

void Calculate_Offset_d(void);
#endif /*__IMAGE_PROCESS_H*/
