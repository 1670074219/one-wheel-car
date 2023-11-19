#include "Cirque.h"
int circle_flag=0;
//�����󻷵�
uint8 huandao_stage=1;  //�����׶α�־λ
uint8 huandao_flag = 0;
float huandao_angle = 0;

float l_angle_in = 90;
float l_angle_out = 335;
void Handle_Left_Cirque()
{
    speed = element_speed.Cirque_speed;


    //�ж���Բ����λ��
    switch(huandao_stage)
    {
        case 1:
            Diuxian_weizhi_test(1, MT9V03X_H -1, MT9V03X_H -20);
            if(budiuxian_hang >=15)
            {
                Diuxian_weizhi_test(1, MT9V03X_H -20, MT9V03X_H -40);
                if(diuxian_hang >=15)
                {
                    huandao_stage = 2;  //�ڶμӰ׶Σ�1�׶Σ�������ֱ�У�
                }
            }
            break;
        case 2:
            Diuxian_weizhi_test(1,MT9V03X_H -1, MT9V03X_H -20);
            if(diuxian_hang >=5 && huandao_stage ==2)
            {
                Diuxian_weizhi_test(1, MT9V03X_H -20, MT9V03X_H -40);
                if(budiuxian_hang >=15)
                {
                    huandao_stage =3;  //�׶μӺڶΣ�2�׶Σ�������ֱ�У�
                }
            }
            break;
        case 3:
            Diuxian_weizhi_test(1, MT9V03X_H -20, MT9V03X_H -40);
            if(budiuxian_hang >=15 && huandao_stage ==3)
            {
                Diuxian_weizhi_test(1, MT9V03X_H -40, MT9V03X_H -60);
                if(diuxian_hang >=1)
                {
                    huandao_stage =4;  //�ڶμӰ׶Σ�3�׶Σ������߽�����
                    huandao_flag = 1;
                }
            }
            break;
        case 4:
            //annulus_s1 += Distance_Measure();
            if( huandao_angle > l_angle_in)   //���������ִ���һ��ֵ�����뻷�����棨���ֵ���Ը�СһЩ������·�����ã�5500
            {
                LED_Ctrl(LED0,ON);
                huandao_stage =5;     //����Բ����
                annulus_s1 =0;
            }
            break;
        case 5:
            Diuxian_weizhi_test(2,MT9V03X_H -40, MT9V03X_H -60);
            if(diuxian_hang >=10 && huandao_stage ==5)
            {
                huandao_stage =6;     //����
            }
            break;
        case 6:
            annulus_s1 += Distance_Measure();
            if(huandao_angle > l_angle_out)//����
            {
                LED_Ctrl(LED1,ON);
                huandao_stage =7;
                annulus_s1 =0;
            }
            break;
        case 7:
            annulus_s1 += Distance_Measure();
            if(annulus_s1 >5000)  //����һ�ξ��벢���߻����������(���б�־λ����)
            {
                LED_Ctrl(LED0,OFF);
                LED_Ctrl(LED1,OFF);
                road_type.LeftCirque = 0;
                huandao_stage =1;
                annulus_s1 =0;
                l_guaidain_x=0, l_guaidain_y=0;
                r_guaidain_x=0, r_guaidain_y=0;
                huandao_angle = 0;
                huandao_flag = 0;
                Beep_OFF;
                speed = f32wBuff[21];
            }
            break;
    }

    //����
    if(huandao_stage ==1)    //����߲�����
    {
        for(uint8 y =MT9V03X_H -30; y >=MT9V03X_H -40; y--)  //ֻ��80�е�������ȣ�������
        {
            l_line_x[y] = r_line_x[y] - kuandu_saidao[MT9V03X_H-1 -y]; //-5
            //r_line_x[y] = r_line_x[y];
        }
    }
    else if((huandao_stage ==2) || (huandao_stage ==3))
    {
        for(uint8 y =MT9V03X_H -30; y >=MT9V03X_H -40; y--)  //ֻ��80�е�������ȣ�������
        {
            l_line_x[y] = r_line_x[y] - kuandu_saidao[MT9V03X_H-1 -y];//-10
            //r_line_x[y] = r_line_x[y];
        }
    }
    else if(huandao_stage ==4)   //������Ȳ���
    {
        for(uint8 y =MT9V03X_H -30; y >=MT9V03X_H -40; y--)  //ֻ��80�е�������ȣ�������
        {
            r_line_x[y] = l_line_x[y] + kuandu_saidao[MT9V03X_H-1 -y];   //������һ��ƫ��������Сһ�������
//            l_line_x[y] = l_line_x[y] ;
        }
    }
    else if(huandao_stage ==5)   //�ڻ���
    {
        ;//�������
    }
    else if(huandao_stage ==6)   //������
    {
//        if(r_line_x[MT9V03X_H -1] != (MT9V03X_W-1))        //���¹յ����&&(MT9V03X_H<50)
//        {
//            for(uint8 y=MT9V03X_H -1; y>10; y--)
//            {
//                if(fabs(r_line_x[y] -r_line_x[y+1])<4 && (r_line_x[y]- r_line_x[y-6] < -6))    //�������Ҫ�����ϸ�һ��
//                {
//                    r_guaidain_y = y;   //û�������ѭ��
//                    r_guaidain_x = r_line_x[y];
//                    break;
//                }
//            }
//        }
//        else
//        {
            r_guaidain_y = MT9V03X_H -1;
            r_guaidain_x = MT9V03X_W-10;
//        }

        for(uint8 y =MT9V03X_H -40; y>10; y--)//50
        {
            if((image_01[y][50] == 0) && (image_01[y-1][50]==0) && (image_01[y-2][50]==0))
            {
                l_guaidain_y = y;
                l_guaidain_x = 50;//60
                break;
            }
        }

        La_zhixian(r_guaidain_x, r_guaidain_y, l_guaidain_x, l_guaidain_y, r_line_x);
    }
    else if(huandao_stage==7)
    {
        for(uint8 y =MT9V03X_H-1; y>20; y--)
        {
            l_line_x[y] = r_line_x[y] - kuandu_saidao[MT9V03X_H-1 -y];     //����·��ƫ��,Ϊ��׼ȷʶ�𻷵�,����ƫ����ʹ��������������-5
            //r_line_x[y] = r_line_x[y];
        }
    }
}
/*****************************�󻷵��������*****************************************/




//�����һ���
float r_angle_in = -90;
float r_angle_out = -350;
void Handle_Right_Cirque()
{
    speed = element_speed.Cirque_speed;


    //�ж���Բ����λ��
    switch(huandao_stage)
    {
        case 1:
            Diuxian_weizhi_test(2, MT9V03X_H -1, MT9V03X_H -20);
            if(budiuxian_hang >=15)
            {
                Diuxian_weizhi_test(2, MT9V03X_H -20, MT9V03X_H -40);
                if(diuxian_hang >=15)
                {
                    huandao_stage =2;  //�ڶμӰ׶Σ�1�׶Σ�������ֱ�У�
                }
            }
            break;

        case 2:
            Diuxian_weizhi_test(2,MT9V03X_H -1, MT9V03X_H -20);
            if(diuxian_hang >=15 && huandao_stage ==2)
            {
                Diuxian_weizhi_test(2, MT9V03X_H -20, MT9V03X_H -40);
                if(budiuxian_hang >=15)
                {
                    huandao_stage =3;  //�׶μӺڶΣ�2�׶Σ�������ֱ�У�
                }
            }
            break;

        case 3:
            Diuxian_weizhi_test(2, MT9V03X_H -20, MT9V03X_H -40);
            if(budiuxian_hang >=15 && huandao_stage ==3)
            {
                Diuxian_weizhi_test(2, MT9V03X_H -40, MT9V03X_H -60);
                if(diuxian_hang >=1)
                {
                    huandao_stage =4;  //�ڶμӰ׶Σ�3�׶Σ������߽�����
                    huandao_flag = 1;
                }
            }
            break;
        case 4:
            //annulus_s1 += Angle_Measure();
            if(huandao_angle < r_angle_in)   //���������ִ���һ��ֵ�����뻷�����棨���ֵ���Ը�СһЩ������·�����ã�
            {
                LED_Ctrl(LED0,ON);
                huandao_stage =5;     //����Բ����
                annulus_s1 =0;
                last_angle = 0;
                now_angle = 0;

            }
            break;
        case 5:
            Diuxian_weizhi_test(1,MT9V03X_H -40, MT9V03X_H -60);
            if(diuxian_hang >=10 && huandao_stage ==5)
            {
                annulus_s1 =0;
                last_angle = 0;
                now_angle = 0;
                huandao_stage =6;     //����
            }
            break;
        case 6:
            //annulus_s1 += Angle_Measure();
            if( huandao_angle<r_angle_out)//����
            {
                LED_Ctrl(LED1,ON);
                huandao_stage =7;
                annulus_s1 =0;
                last_angle = 0;
                now_angle = 0;
            }
            break;
        case 7:
            annulus_s1 += Distance_Measure();
            if(annulus_s1 >5000)  //����һ�ξ��벢���߻����������(���б�־λ����)
            {
                LED_Ctrl(LED0,OFF);
                LED_Ctrl(LED1,OFF);
                road_type.RightCirque = 0;
                huandao_stage =1;
                annulus_s1 =0;
                l_guaidain_x=0, l_guaidain_y=0;
                r_guaidain_x=0, r_guaidain_y=0;
                huandao_angle = 0;
                huandao_flag = 0;
                Beep_OFF;
                speed = f32wBuff[21];
            }
            break;
    }

    //����
    if(huandao_stage ==1)    //����߲�����
    {
        for(uint8 y =MT9V03X_H -30; y >=MT9V03X_H -40; y--)  //ֻ��80�е�������ȣ�������
        {
            r_line_x[y] = l_line_x[y] + kuandu_saidao[MT9V03X_H-1 -y]; //+5
            //l_line_x[y] = l_line_x[y];
        }
    }
    else if((huandao_stage ==2) || (huandao_stage ==3))
    {
        for(uint8 y =MT9V03X_H -30; y >=MT9V03X_H -40; y--)  //ֻ��80�е�������ȣ�������
        {
            r_line_x[y] = l_line_x[y] + kuandu_saidao[MT9V03X_H-1 -y];//+10
            //l_line_x[y] = l_line_x[y];
        }
    }
    else if(huandao_stage ==4)   //������Ȳ���
    {
        for(uint8 y =MT9V03X_H -30; y >=MT9V03X_H -40; y--)  //ֻ��80�е�������ȣ�������
        {
            l_line_x[y] = r_line_x[y] - kuandu_saidao[MT9V03X_H-1 -y];  //������һ��ƫ��������Сһ������� +5
            //r_line_x[y] = r_line_x[y]+4;
        }
    }
    else if(huandao_stage ==5)   //�ڻ���
    {
        ;//�������
    }
    else if(huandao_stage ==6)   //������
    {
//        if(l_line_x[MT9V03X_H -1] != 0)         //���¹յ����
//        {
//            for(uint8 y=MT9V03X_H -1; y>10; y--)
//            {
//                if(fabs(l_line_x[y] -l_line_x[y+1])<4 && (l_line_x[y]- l_line_x[y-6] >6))    //�������Ҫ�����ϸ�һ��
//                {
//                    l_guaidain_y = y;   //û�������ѭ��
//                    l_guaidain_x = l_line_x[y];
//                    break;
//                }
//
//            }
//        }
//        else
//        {
            l_guaidain_y = MT9V03X_H -1;
            l_guaidain_x = 10;
//        }

        for(uint8 y =MT9V03X_H -40; y>10; y--)
        {
            if((image_01[y][MT9V03X_W - 60] == 0) && (image_01[y-1][MT9V03X_W - 60]==0) && (image_01[y-2][MT9V03X_W - 60]==0))
            {
                r_guaidain_y = y;
                r_guaidain_x = MT9V03X_W - 60;
                break;
            }
        }
        La_zhixian(l_guaidain_x, l_guaidain_y, r_guaidain_x, r_guaidain_y, l_line_x);
    }
    else if(huandao_stage==7)
    {
        for(uint8 y =MT9V03X_H-1; y>20; y--)
        {
            r_line_x[y] = l_line_x[y] + kuandu_saidao[MT9V03X_H-1 -y];     //����·��ƫ��,Ϊ��׼ȷʶ�𻷵�,����ƫ����ʹ��������������
        }
    }
}
/*****************************�һ����������*****************************************/

uint32 dont_handle_encoder = 0;
uint16 dont_handle_flag = 0;
void Dont_handle_l_cirque(void)
{
    speed = element_speed.DotCirque_speed;
    dont_handle_flag = 1;

    for(uint8 y =MT9V03X_H -30; y >=MT9V03X_H -40; y--)  //ֻ��80�е�������ȣ�������
    {
        l_line_x[y] = r_line_x[y] - kuandu_saidao[MT9V03X_H-1 -y];
    }

    if(dont_handle_encoder > 130000)
    {
        LED_Ctrl(LED0,OFF);
        LED_Ctrl(LED1,OFF);
        Beep_OFF;
        dont_handle_encoder = 0;
        dont_handle_flag = 0;
        road_type.LeftCirque = 0;
        speed = f32wBuff[21];
    }
}

void Dont_handle_r_cirque(void)
{
    speed = element_speed.DotCirque_speed;
    dont_handle_flag = 1;

    for(uint8 y =MT9V03X_H -30; y >=MT9V03X_H -40; y--)  //ֻ��80�е�������ȣ�������
    {
        r_line_x[y] = l_line_x[y] + kuandu_saidao[MT9V03X_H-1 -y];
    }

    if(dont_handle_encoder > 130000)
    {
        LED_Ctrl(LED0,OFF);
        LED_Ctrl(LED1,OFF);
        Beep_OFF;
        dont_handle_encoder = 0;
        dont_handle_flag = 0;
        road_type.RightCirque = 0;
        speed = f32wBuff[21];
    }
}
