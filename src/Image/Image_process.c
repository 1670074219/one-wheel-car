#include "Image_process.h"

uint8 shibie_flag = 0; //ʶ��ʼflag
float offset; //ƫ��
float k_left = 0,k_right = 0; //�м����
float k_left1 = 0,k_right1 = 0;
uint8 image_yuanshi[MT9V03X_H][MT9V03X_W]; //ԭʼͼ��
uint8 image_01[MT9V03X_H][MT9V03X_W]; //��ֵ��ͼ��
float last_angle = 0,now_angle = 0; //δ֪���� ɾ�˱��� �ҵ���������call me
/*
uint8 kuandu_saidao [MT9V03X_H] = {
      //9    8    7    6    5    4    3    2    1    0
        133, 133, 131, 131, 131, 130, 129, 129, 128, 127, //119
        127, 126, 125, 125, 123, 123, 122, 121, 121, 120, //109
        119, 119, 117, 117, 116, 115, 115, 113, 113, 113, //99
        111, 111, 110, 109, 109, 107, 107, 106, 105, 104, //89
        103, 103, 102, 101, 100, 100, 98,  98,  97,  96,  //79
        96,  94,  94,  92,  92,  91,  90,  89,  88,  87,  //69
        87,  86,  85,  84,  83,  82,  81,  81,  79,  79,  //59
        78,  77,  77,  75,  75,  73,  73,  72,  71,  71,  //49
        69,  69,  68,  67,  66,  65,  64,  64,  63,  62,  //39
        61,  60,  60,  58,  58,  58,  56,  56,  54,  54,  //29
        53,  52,  51,  50,  50,  49,  48,  47,  46,  45}; //19
*/

/*
uint8 kuandu_saidao [MT9V03X_H] = {
      //9    8    7    6    5    4    3    2    1    0
        117, 116, 116, 115, 114, 113, 112, 112, 111, 111, //119
        110, 109, 109, 108, 107, 107, 105, 105, 105, 103, //109
        103, 103, 101, 101, 100, 99,  99,  97,  97,  97, //99
        95,  95,  94,  93,  93,  92,  91,  90,  90,  88, //89
        88,  86,  86,  84,  84,  83,  82,  81,  80,  80,  //79
        79,  78,  77,  76,  76,  75,  74,  73,  72,  72,  //69
        71,  70,  69,  68,  67,  67,  66,  65,  65,  64,  //59
        63,  62,  61,  60,  60,  59,  58,  56,  56,  55,  //49
        53,  52,  51,  51,  50,  49,  49,  48,  47,  47,  //39
        45,  45,  43,  43,  42,  41,  40,  40,  38,  38,  //29
        38,  36,  36,  34,  34,  34,  33,  33,  33,  33}; //19
*/

/*
uint8 kuandu_saidao [MT9V03X_H] = {
      //9    8    7    6    5    4    3    2    1    0
        111, 111, 110, 109, 109, 108, 107, 107, 106, 105, //119
        105, 104, 103, 103, 102, 101, 101, 100, 99,  99, //109
        98,  97,  97,  96,  95,  95,  94,  93,  93,  92, //99
        91,  90,  90,  89,  88,  87,  87,  86,  85,  84, //89
        84,  83,  82,  81,  80,  80,  79,  78,  78,  76,  //79
        76,  75,  74,  74,  73,  72,  72,  70,  70,  70,  //69
        68,  68,  64,  66,  66,  64,  64,  64,  62,  62,  //59
        62,  60,  60,  59,  58,  58,  57,  56,  56,  54,  //49
        54,  54,  52,  52,  51,  50,  50,  50,  48,  48,  //39
        46,  46,  46,  44,  44,  43,  42,  42,  41,  40,  //29
        40,  39,  38,  37,  36,  36,  35,  34,  34,  33}; //19
*/

uint8 kuandu_saidao [MT9V03X_H] = {
      //9    8    7    6    5    4    3    2    1    0
        110, 109, 109, 109, 107, 107, 107, 105, 105, 105, //119
        103, 103, 102, 101, 101, 100, 99,  99,  98,  97, //109
        96,  96,  95,  94,  94,  92,  92,  92,  90,  90, //99
        89,  88,  88,  87,  86,  85,  84,  84,  83,  82, //89
        82,  81,  80,  79,  79,  77,  77,  76,  75,  75,  //79
        74,  73,  72,  71,  71,  69,  69,  69,  67,  67,  //69
        66,  65,  65,  63,  63,  63,  61,  61,  60,  59,  //59
        59,  57,  57,  57,  55,  55,  55,  53,  53,  51,  //49
        51,  51,  49,  49,  48,  47,  47,  46,  45,  45,  //39
        44,  43,  43,  42,  41,  40,  39,  39,  38,  37,  //29
        36,  36,  35,  34,  34,  32,  32,  32,  30,  30}; //19 //�������

float offset_quanzhong [15] = {0.96, 0.92, 0.88, 0.83, 0.77,
                               0.71, 0.65, 0.59, 0.53, 0.47,
                               0.47, 0.47, 0.47, 0.47, 0.47,};  //ƫ��Ȩ��

struct ROAD_TYPE road_type = {
        .straight      = 0,
        .bend          = 0,
        .Ramp          = 0,
        .Cross         = 0,
        .L_Cross       = 0,
        .R_Cross       = 0,
        .LeftCirque    = 0,
        .RightCirque   = 0,
        .Fork          = 0,
        .Barn_l_out    = 0,
        .Barn_r_out    = 0,
        .Barn_l_in     = 0,
        .Barn_r_in     = 0,
        .Podao         = 0,
        .ZhangAi       = 0,
        .Duanlu        = 0
}; //Ԫ��ʶ���־

struct SPEED_DECESION element_speed = {
        .Cross_speed = 125,
        .Duanlu_speed = 125,
        .Podao_speed = 125,
        .Ramp_speed = 125,
        .ZhangAi_speed = 125,
        .bend_speed = 125,
        .straight_speed = 125,
        .Cirque_speed = 125,
        .DotCirque_speed = 125,
}; //Ԫ���ٶȹ滮


//ͼ��ת��
void Transfer_Camera(void)
{
    for(uint8 y=0; y<MT9V03X_H; y++)
    {
        for(uint8 x=0; x<MT9V03X_W; x++)
        {
            image_yuanshi[y][x] = Image_Data[y][x];
        }
    }
}

//�������ֵ
uint8 otsuThreshold(uint8 *image, uint16 col, uint16 row)
{
#define GrayScale 256
    uint16 Image_Width  = col;
    uint16 Image_Height = row;
    int X; uint16 Y;
    uint8* data = image;
    int HistGram[GrayScale] = {0};

    uint32 Amount = 0;
    uint32 PixelBack = 0;
    uint32 PixelIntegralBack = 0;
    uint32 PixelIntegral = 0;
    sint32 PixelIntegralFore = 0;
    sint32 PixelFore = 0;
    double OmegaBack=0, OmegaFore=0, MicroBack=0, MicroFore=0, SigmaB=0, Sigma=0; // ��䷽��;
    uint8 MinValue=0, MaxValue=0;
    uint8 Threshold = 0;


    for (Y = 0; Y <Image_Height; Y++) //Y<Image_Height��ΪY =Image_Height���Ա���� �ж�ֵ��
    {
        //Y=Image_Height;
        for (X = 0; X < Image_Width; X++)
        {
        HistGram[(int)data[Y*Image_Width + X]]++; //ͳ��ÿ���Ҷ�ֵ�ĸ�����Ϣ
        }
    }
    for (MinValue = 0; MinValue < 256 && HistGram[MinValue] == 0; MinValue++) ;        //��ȡ��С�Ҷȵ�ֵ
    for (MaxValue = 255; MaxValue > MinValue && HistGram[MinValue] == 0; MaxValue--) ; //��ȡ���Ҷȵ�ֵ

    if (MaxValue == MinValue)
    {
        return MaxValue;          // ͼ����ֻ��һ����ɫ
    }
    if (MinValue + 1 == MaxValue)
    {
        return MinValue;      // ͼ����ֻ�ж�����ɫ
    }

    for (Y = MinValue; Y <= MaxValue; Y++)
    {
        Amount += HistGram[Y];        //  ��������
    }

    PixelIntegral = 0;
    for (Y = MinValue; Y <= MaxValue; Y++)
    {
        PixelIntegral += HistGram[Y] * Y;//�Ҷ�ֵ����
    }
    SigmaB = -1;
    for (Y = MinValue; Y < MaxValue; Y++)
    {
          PixelBack = PixelBack + HistGram[Y];    //ǰ�����ص���
          PixelFore = Amount - PixelBack;         //�������ص���
          OmegaBack = (double)PixelBack / Amount;//ǰ�����ذٷֱ�
          OmegaFore = (double)PixelFore / Amount;//�������ذٷֱ�
          PixelIntegralBack += HistGram[Y] * Y;  //ǰ���Ҷ�ֵ
          PixelIntegralFore = PixelIntegral - PixelIntegralBack;//�����Ҷ�ֵ
          MicroBack = (double)PixelIntegralBack / PixelBack;//ǰ���ҶȰٷֱ�
          MicroFore = (double)PixelIntegralFore / PixelFore;//�����ҶȰٷֱ�
          Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore);//g
          if (Sigma > SigmaB)//����������䷽��g
          {
              SigmaB = Sigma;
              Threshold = (uint8)Y;
          }
    }
   return Threshold;
}

//��ֵ��
uint8 Threshold;  //��ֵ
float Threshold_add = 0;
void Get01change_Dajin(void)
{
    Threshold = my_adapt_threshold(image_yuanshi[0], MT9V03X_W, MT9V03X_H);

    uint8 thre;
    for(uint8 y = 0; y < MT9V03X_H; y++)
        {
            for(uint8 x = 0; x < MT9V03X_W; x++)
            {
                if (x <= 15)
                    thre = Threshold - 15;
                else if (x >= MT9V03X_W-15)
                    thre = Threshold - 15;
                else
                    thre = Threshold;

                if (image_yuanshi[y][x] >thre + Threshold_add)         //��ֵԽ����ʾ������Խ�࣬��ǳ��ͼ��Ҳ����ʾ����
                    image_01[y][x] = 255;  //��
                else
                    image_01[y][x] = 0;  //��
            }
        }
}

//��ʴ
void Pixle_Filter()
{
    for (uint8 height = 10; height < MT9V03X_H-10; height++)
    {
        for (uint8 width = 10; width < MT9V03X_W -10; width = width + 1)
        {
            if ((image_01[height][width] == 0) && (image_01[height - 1][width] + image_01[height + 1][width] +image_01[height][width + 1] + image_01[height][width - 1] >=3*255))
            { //һ���ڵ���������ҵİ׵���ڵ����������������Ϊ��
                image_01[height][width] = 255;
            }
            else if((image_01[height][width] !=0)&&(image_01[height-1][width]+image_01[height+1][width]+image_01[height][width+1]+image_01[height][width-1]<2*255))
            {
                image_01[height][width] =0;
            }
        }
    }
}

//�������ߺ���
uint8 search_line_end = 0;                                   //������ֹ��
uint8 kuan[MT9V03X_H];                                        //�����������
uint8 m_line_x[MT9V03X_H];                                    //�����������ߵ���
uint8 r_line_y[MT9V03X_H], l_line_y[MT9V03X_H];               //�������ұ߽������
uint8 r_line_x[MT9V03X_H], l_line_x[MT9V03X_H];               //����ԭʼͼ������ұ߽������
uint8 r_second_line_x[MT9V03X_H], l_second_line_x[MT9V03X_H]; //���油��֮������ұ߽�ֵ����δ�õ���
uint8 m_second_line_x[MT9V03X_H];                             //�����������ߵ���
uint8 r_lose_value=0, l_lose_value=0;                         //���Ҷ�����������ע��Ҫ��һ������
uint8 r_search_flag[MT9V03X_H], l_search_flag[MT9V03X_H];     //�Ƿ��ѵ��ߵı�־
uint8 height, r_width, l_width;                               //ѭ��������
uint8 r_losemax,l_losemax;
void Search_Line(uint8 type)     //0Ϊ��ͨģʽ��1Ϊ������ģʽ��ֻ��������ʼ�����겻ͬ��
{
    uint8 l_flag=0,r_flag=0;
    uint8 l_search_start, r_search_start;                   //������ʼ������
    uint8 r_searchget_flage, l_searchget_flage;             //�ѵ���ʱ�ı�־λ
    r_searchget_flage=1; l_searchget_flage=1;               //��ʼ������Ĭ��Ϊ�ϴ��ѵ���
    r_lose_value=0; l_lose_value=0;                         //���Ҷ�����������ע��Ҫ��һ������


    for(height=(MT9V03X_H -1); height>search_line_end; height--)
    {
        //ȷ��ÿ�е�������ʼ������
        if (type == 0)//��ͨģʽ
        {
            if( (height>MT9V03X_H-5) || ( (l_line_x[height+1] == 0) && (r_line_x[height+1] == MT9V03X_W -1) && (height <MT9V03X_H-4) )  )   //ǰ���У��������Ҷ����ߵ���
            {
                l_search_start = MT9V03X_W/2;
                r_search_start = MT9V03X_W/2;
            }
            else if((l_line_x[height+1] !=0) && (r_line_x[height+1] !=MT9V03X_W -1) && (height <MT9V03X_H-4))   //���Ҷ�������
            {
                l_search_start = l_line_x[height+1]+7;//7
                r_search_start = r_line_x[height+1]-20;
            }
            else if((l_line_x[height+1] != 0 && r_line_x[height+1] == MT9V03X_W -1) && (height <MT9V03X_H-4))   //�󲻶���,�Ҷ���
            {
                l_search_start = l_line_x[height+1]+7;
                r_search_start = MT9V03X_W/2;
            }
            else if((l_line_x[height+1] == 0 && r_line_x[height+1] != MT9V03X_W -1) && (height <MT9V03X_H-4))   //�Ҳ�����,����
            {
                l_search_start = MT9V03X_W/2;
                r_search_start = r_line_x[height+1]-20;
            }
        }

        if( (image_01[height][MT9V03X_W/2] ==0) && (image_01[height -1][MT9V03X_W/2] ==0) && (image_01[height -2][MT9V03X_W/2] ==0) && (height <MT9V03X_H-40)) //������ֹ����
        {
            search_line_end = height+1;
            break;
        }
        else
        {
            search_line_end = 0;
        }


        for(l_width=l_search_start; l_width>1; l_width--)      //�������
        {
            if(image_01[height][l_width -2]==0 && image_01[height][l_width -1]==0 && image_01[height][l_width] !=0 && l_width>2)
            {   //�ںڰ�
                l_line_x[height] = l_width-1;
                l_line_y[height] = height;
                l_search_flag[height] = 1;
                l_searchget_flage = 1;
                break;
            }
            else if(l_width==2)
            {
                if(l_flag==0)
                {
                    l_flag=1;
                    l_losemax=height;
                }
                l_line_x[height] = 0;
                l_line_y[height] = height;
                l_search_flag[height] = 0;
                l_searchget_flage = 0;
                l_lose_value++;
                break;
            }
        }

        for(r_width=r_search_start; r_width<(MT9V03X_W -2); r_width++)      //�ұ�����
        {
            if( image_01[height][r_width ] !=0 && image_01[height][r_width +1]==0 && image_01[height][r_width +2]==0 && r_width<MT9V03X_W-3)
            {   //�׺ں�
                r_line_x[height] = r_width+1;
                r_line_y[height] = height;
                r_search_flag[height] = 1;
                r_searchget_flage = 1;
                break;
            }
            else if(r_width==MT9V03X_W -3)
            {
                if(r_flag==0)
                {
                    r_flag=1;
                    r_losemax=height;
                }
                r_line_x[height] = MT9V03X_W -1;
                r_line_y[height] = height;
                r_search_flag[height] = 0;
                r_searchget_flage = 0;
                r_lose_value++;
                break;
            }
        }
        kuan[height]=r_line_x[height] - l_line_x[height];
    }
}

//�Լ�д�Ŀ�������
uint8 My_Sqrt(sint16 x)
{
    uint8 ans=0, p=0x80;
    while(p!=0)
    {
        ans += p;
        if(ans*ans>x)
        {
            ans -= p;
        }
        p = (uint8)(p/2);
    }
    return (ans);
}

//���㷨������������
float Process_Curvity(uint8 x1, uint8 y1, uint8 x2, uint8 y2, uint8 x3, uint8 y3)
{
    float K;
    int S_of_ABC = ((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1)) / 2;
    //����ķ��ű�ʾ����
    sint16 q1 = (sint16)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    uint8 AB = My_Sqrt(q1);
    q1 = (sint16)((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
    uint8 BC = My_Sqrt(q1);
    q1 = (sint16)((x3 - x1) * (x3 - x1) + (y3 - y1) * (y3 - y1));
    uint8 AC = My_Sqrt(q1);
    if (AB * BC * AC == 0)
    {
        K = 0;
    }
    else
        K = (float)4 * S_of_ABC / (AB * BC * AC);
    return K;
}

//�������߳��� �ж���ֱ��
uint8 length=0;
void Mid_Col(void)
{
    int i;
    for(i=MT9V03X_H;i>1;i--)
    {
        if(image_01[i][86]==0 && image_01[i-1][86]==0 && image_01[i-2][86]==0)
        {
            break;
        }
    }
    length=MT9V03X_H-i;
}

uint8 sudu_yingzi=0;    //�ٶ�����
void Check_Zhidao(void)
{//����Ҫ����������ֹ��
    uint8 inc =0, dec =0;
    sudu_yingzi =0;

    for(uint8 y =MT9V03X_H-1; y >1; y--)
    {
        if((l_line_x[y] <=l_line_x[y-1]) && l_line_x[y] !=0)   //���߲����߲ż���ֱ������
        {
            inc++;
        }

        if((r_line_x[y] >=r_line_x[y-1]) && r_line_x[y] !=MT9V03X_W -1)
        {
            dec++;
        }
    }

    if(inc>=dec)
    {
        sudu_yingzi =dec;
    }
    else
    {
        sudu_yingzi =inc;
    }
}

//�ж϶�����λ�ú���Ŀ
uint8 diuxian_hang=0, budiuxian_hang=0;
void Diuxian_weizhi_test(uint8 type, uint8 startline, uint8 endline)
{//1��2��
    diuxian_hang=0, budiuxian_hang=0;
    if(type ==1)
    {
        for(uint8 y=startline; y>=endline; y--)
        {
            budiuxian_hang += l_search_flag[y];
            diuxian_hang = (startline-endline+1) -budiuxian_hang;
        }
    }
    if(type ==2)
    {
        for(uint8 y=startline; y>=endline; y--)
        {
            budiuxian_hang += r_search_flag[y];
            diuxian_hang = (startline-endline+1) -budiuxian_hang;
        }
    }
}

//�н�����
sint16 Distance_Measure(void)
{
    sint16 distance;

    distance = Encoder_C;

    return distance;
}

//�ұ��߹յ�
uint8 l_guaidain_x=0, l_guaidain_y=0;
uint8 r_guaidain_x=0, r_guaidain_y=0;
void Bianxian_guaidian(uint8 type, uint8 startline, uint8 endline)
{ //ÿ��ֻ��һ���յ�����
    l_guaidain_x =0;
    l_guaidain_y =0;
    r_guaidain_x =0;
    r_guaidain_y =0;

    //����߹յ�
    if(type ==1)
    {
        if(l_line_x[MT9V03X_H -1] !=0)         //���¹յ����
        {
            for(uint8 y=startline; y>endline; y--)
            {
                if(fabs(l_line_x[y] -l_line_x[y+1])<4 && (l_line_x[y] -l_line_x[y-3] >8))
                {
                    l_guaidain_y = y;
                    l_guaidain_x = l_line_x[y];
                    break;
                }
            }
        }
    }

    //�ұ��߹յ�
    if(type == 2)
    {
        if(r_line_x[MT9V03X_H -1] !=MT9V03X_W -1)         //���¹յ����
        {
            for(uint8 y=startline; y>endline; y--)
            {
                if(fabs(r_line_x[y] -r_line_x[y+1]) <4 && (r_line_x[y]- r_line_x[y-3]< -8))    //�������Ҫ�����ϸ�һ��
                {
                    r_guaidain_y = y;
                    r_guaidain_x = r_line_x[y];
                    break;
                }
            }
        }
    }
}

//�������Ƿ�ͻ�� ͻ�䷵��1
uint8 Tututu(uint8 type)
{
    if (type ==1)
    {
        for(uint8 y1 =MT9V03X_H -1; y1>=30; y1=y1-4)
        {
            if(fabs(l_line_x[y1] -l_line_x[y1-1])<4 && (l_line_x[y1] -l_line_x[y1-10]) >8)
            {
                return 1;
            }
        }
    }
    else if (type ==2)
    {
        for(uint8 y1 =MT9V03X_H -1; y1>=30; y1=y1-4)
        {
            if(fabs(r_line_x[y1] -r_line_x[y1-1])<4 && (r_line_x[y1] -r_line_x[y1-10]) <-8)
            {
                return 1;
            }
        }
    }
    return 0;
}

uint8 Num=0;
//�ж�Բ������ʮ�֣�����Բ���ĵ�һ��Բ����
uint8 Cirque_or_Cross(uint8 type, uint8 startline)
{//1Ϊ��Բ����2Ϊ��Բ��
    uint8 num =0;
    if(type ==1)
    {
        for(uint8 y=startline; y<startline+10; y++)
        {
            for(uint8 x=l_line_x[y]; x>1; x--)
            {
                if(image_01[y][x] !=0)
                {
                    num ++;
                }
            }
        }
    }
    if(type ==2)
    {
        for(uint8 y=startline; y<startline+10; y++)
        {
            for(uint8 x=r_line_x[y]; x<MT9V03X_W -2; x++)
            {
                if(image_01[y][x] !=0)
                {
                    num ++;
                }
            }
        }
    }
    Num=num;
    return num;
}

sint16 Sum1;
void HDPJ_lvbo(uint8 data[], uint8 N, uint8 size)
{
    Sum1 = 0;
    for(uint8 j =0; j <size; j++)
    {
        if(j <N /2)
        {
            for(uint8 k =0; k <N; k++)
            {
                Sum1 +=data[j +k];
            }
            data[j] =Sum1 /N;
        }
        else
            if(j <size -N /2)
            {
                for(uint8 k =0; k <N /2; k++)
                {
                    Sum1 +=(data[j +k] +data[j -k]);
                }
                data[j] = Sum1 /N;
            }
            else
            {
                for(uint8 k =0; k <size -j; k++)
                {
                    Sum1 +=data[j +k];
                }
                for(uint8 k =0; k <(N -size +j); k++)
                {
                    Sum1 +=data[j -k];
                }
                data[j] = Sum1 /N;
            }
        Sum1 = 0;
    }
}

//��������ͬһ�߽��ϵ���������
void La_zhixian(uint8 x_down, uint8 y_down, uint8 x_up, uint8 y_up, uint8 *array)    //����������ĺ�������
{
    for(uint8 i=y_down; i >(y_up-1); i--)         //���Կ��ܲ���д>=
    {
        sint16 X;
        X = (y_down -i) *(x_up -x_down) /(y_down -y_up) ;
        array[i] = array[y_down] + X;
    }
}

uint8 cross_left[2]  ={0, 0};  //��һ���±��ͼ���·��ĵ��yֵ
uint8 cross_right[2] ={0, 0};
void Check_Cross_Guaidian(uint8 type)  //��ʮ�ֹյ�
{
    cross_left[0] =cross_left[1] =cross_right[0] =cross_right[1] =0;

    if (type ==1)
    {
        if(image_01[MT9V03X_H -1][4] ==0)   //���¹յ����
        {
            for(uint8 y1 =MT9V03X_H -1; y1>=2; y1--)
            {
                if(fabs(l_line_x[y1] -l_line_x[y1-1])<4 && (l_line_x[y1] -l_line_x[y1-10])>10 && l_line_x[y1-10] ==0)
                {
                    cross_left[0]  =y1;
                    break;
                }
            }

            if(cross_left[0] !=0)   //���¹յ��ҵ���,���������Ϲյ�
            {
                for(uint8 y2 =cross_left[0] -1; y2>=2; y2--)
                {
                    if(fabs(l_line_x[y2-5] -l_line_x[y2-6])<4 && l_line_x[y2] -l_line_x[y2-5]< -10 && l_line_x[y2] ==0)
                    {
                        cross_left[1]  =y2-5 -5;
                        break;
                    }
                }
            }
        }
        else  //���¹յ㲻����
        {
            for(uint8 y =MT9V03X_H -1; y>=2; y--)
            {
                if(fabs(l_line_x[y-10] -l_line_x[y-11])<4 && (l_line_x[y] -l_line_x[y-10]) <-10 && l_line_x[y] ==0)
                {
                    cross_left[0]  =0;
                    cross_left[1]  =y-10 -5;
                    break;
                }
            }
        }
    }
    else if(type ==2)
    {
        if(image_01[MT9V03X_H -1][MT9V03X_W -4] ==0)   //���¹յ����
        {
            for(uint8 y1 =MT9V03X_H -1; y1>=2; y1--)
            {
                if(fabs(r_line_x[y1] -r_line_x[y1-1])<4 && (r_line_x[y1] -r_line_x[y1-10]) <-10 && r_line_x[y1-10] ==MT9V03X_W -1)
                {
                    cross_right[0]  =y1;
                    break;
                }
            }
            if(cross_right[0] !=0)   //���¹յ��ҵ���,���������Ϲյ�
            {
                for(uint8 y2 =cross_right[0] -1; y2>=2; y2--)
                {
                    if(fabs(r_line_x[y2-5] -r_line_x[y2-6])<4 && (r_line_x[y2] -r_line_x[y2-5]) >10 && r_line_x[y2] ==MT9V03X_W -1)
                    {
                        cross_right[1]  =y2-5 -5;
                        break;
                    }
                }
            }
        }
        else  //���¹յ㲻����
        {
            for(uint8 y =MT9V03X_H -1; y>=2; y--)
            {
                if(fabs(r_line_x[y-10] -r_line_x[y-11])<4 && (r_line_x[y] -r_line_x[y-10]) >10 && r_line_x[y] ==MT9V03X_W -1)
                {
                    cross_right[0]  =0;
                    cross_right[1]  =y-10 -5;
                    break;
                }
            }
        }
    }
}


//��С���˷�����б�ʺͽؾ�
float parameterA=0, parameterB=0;
void Regression(uint8 type, uint8 startline, uint8 endline)
{//һ�󣬶��ң�0�м�
    uint8 i = 0;
    uint8 sumlines = endline - startline;
    sint16 sumX = 0;
    sint16 sumY = 0;
    float averageX = 0;
    float averageY = 0;
    float sumUp = 0;
    float sumDown = 0;

    if (type == 0)               //�������
    {
        for (i = startline; i < endline; i++)
        {
            sumX += i;
            sumY += m_line_x[i];
        }
        if (sumlines != 0)
        {
            averageX = sumX*1.0 / sumlines;     //x��ƽ��ֵ
            averageY = sumY*1.0 / sumlines;     //y��ƽ��ֵ
        }
        for (i = startline; i < endline; i++)
        {
            sumUp += (m_line_x[i] - averageY) * (i - averageX);
            sumDown += (i - averageX) * (i - averageX);
        }
        parameterB = sumUp / sumDown;
        parameterA = averageY - parameterB * averageX;
    }
    else if (type == 1)         //�������
    {
        for (i = startline; i < endline; i++)
        {
            sumX += i;
            sumY += l_line_x[i];
        }
        averageX = sumX*1.0 / sumlines;     //x��ƽ��ֵ
        averageY = sumY*1.0 / sumlines;     //y��ƽ��ֵ
        for (i = startline; i < endline; i++)
        {
            sumUp += (l_line_x[i] - averageY) * (i - averageX);
            sumDown += (i - averageX) * (i - averageX);
        }
        parameterB = sumUp / sumDown;
        parameterA = averageY - parameterB * averageX;
    }
    else if (type == 2)             //�������
    {
        for (i = startline; i < endline; i++)
        {
            sumX += i;
            sumY += r_line_x[i];
        }
        averageX = sumX*1.0 / sumlines;     //x��ƽ��ֵ
        averageY = sumY*1.0 / sumlines;     //y��ƽ��ֵ
        for (i = startline; i < endline; i++)
        {
            sumUp += (r_line_x[i] - averageY) * (i - averageX);
            sumDown += (i - averageX) * (i - averageX);
        }
        parameterB = sumUp / sumDown;
        parameterA = averageY - parameterB * averageX;
    }
}

//��С���˷�����
void Hua_Xian(uint8 type, uint8 startline, uint8 endline, float parameterB, float parameterA)
{//һ�󣬶���
    if (type == 1) //��
    {
        for (uint8 i = startline; i < endline; i++)
        {
            l_line_x[i] = (uint8)(parameterB * i + parameterA);
            if (l_line_x[i] < 0)
            {
                l_line_x[i] = 0;
            }
        }
    }
    else if (type == 2)            //��
    {
        for (int i = startline; i < endline; i++)
        {
            r_line_x[i] = (uint8)(parameterB * i + parameterA);
            if (r_line_x[i] > 187)
            {
                r_line_x[i] = 187;

            }
        }
    }
    else if (type == 0)             //��
    {
        for (int i = startline; i < endline; i++)
        {
            m_line_x[i] = (uint8)((l_line_x[i] / 2 + r_line_x[i] / 2));
            if (m_line_x[i] < 0)
            {
                m_line_x[i] = 0;
            }
            if (m_line_x[i] > 185)
            {
                m_line_x[i] = 185;
            }
        }
    }
}

//Ԫ��ʶ��
uint8 black_count = 0,podao_white_count = 0;
uint8 black_hang = 0,podao_white_hang = 0;
uint8 cheku_flag = 0;
sint16 l_line_qulv=0, r_line_qulv=0;
sint16 l_line_straight=0, r_line_straight=0;
uint8 obstacles_flag = 1;
uint8 l_youxian = 0,l_meixian = 0;
uint8 r_youxian = 0,r_meixian = 0;

uint8 duanlu_count = 0;
extern uint8 duanlu_once_flag;
void Element_Test(void) //Ԫ��ʶ��
{
    l_line_qulv = 1000*Process_Curvity(l_line_x[MT9V03X_H-10], MT9V03X_H-10, l_line_x[MT9V03X_H-25], MT9V03X_H-25, l_line_x[MT9V03X_H-40], MT9V03X_H-40);
    r_line_qulv = 1000*Process_Curvity(r_line_x[MT9V03X_H-10], MT9V03X_H-10, r_line_x[MT9V03X_H-25], MT9V03X_H-25, r_line_x[MT9V03X_H-40], MT9V03X_H-40);

    /***************������߳��ȼ��ϰ���*******************/
    Mid_Col();
    obstacles_flag = PIN_Read(P00_5);

    /***************��鳵��*******************/
    if(!cheku_flag)
    {
        check_cheku(65,60,2);//������
    }

    /***************ʶ��Ԫ��*******************/
    if(!road_type.LeftCirque && !road_type.RightCirque && !road_type.L_Cross && !road_type.Podao
            && !road_type.R_Cross && !road_type.Cross && !road_type.Barn_l_in && !road_type.Barn_r_in && !road_type.ZhangAi && !road_type.Duanlu)
    {
        //��Բ��
        if(length > 90 && l_lose_value >30 && r_lose_value <3 && fabs(r_line_qulv) <4 && !Tututu(2))
        {
            if(Cirque_or_Cross(1,l_losemax) >= 38 && road_type.LeftCirque ==0 && road_type.L_Cross ==0 && road_type.Fork==0)  //��ඪ��λ��y���·��н϶�׵�,�ж�ΪԲ��
            {
                Beep_ON;
                road_type.LeftCirque =1;
                road_type.straight = 0;
                road_type.bend = 0;
            }
        }
        //��Բ��
        else if(length > 90 && r_lose_value >30 && l_lose_value <3 && fabs(l_line_qulv) <4 && !Tututu(1))//
        {
            if(Cirque_or_Cross(2,r_losemax) > 40 && road_type.RightCirque ==0 && road_type.R_Cross ==0 && road_type.Fork==0)  //��ඪ��λ��y���·��н϶�׵�,�ж�ΪԲ��
            {
                Beep_ON;
                road_type.RightCirque =1;
                road_type.straight = 0;
                road_type.bend = 0;
            }
        }
        //���ʮ��
        else if(length > 90 && Tututu(1) && Tututu(2)/*&& r_lose_value >20 && l_lose_value > 20*/)
        {
            l_youxian = 0,l_meixian = 0;
            r_youxian = 0,r_meixian = 0;

            for(int i = 119; i > 69; i--)
            {
                if(l_line_x[i] > 25)
                    l_youxian++;
                else
                    l_meixian++;

                if(r_line_x[i] < 145)
                    r_youxian++;
                else
                    r_meixian++;
            }

            if(l_youxian > 5 && r_youxian > 5 && l_meixian > 15 && r_meixian > 15)
            {
                Beep_ON;
                road_type.Cross = 1;
                road_type.straight = 0;
                road_type.bend = 0;
            }
        }
        //�ϰ���
        else if(obstacles_flag == 0 && ((image_01[5][90] == 0 && image_01[6][90] == 0) || (image_01[10][90] == 0 && image_01[11][90] == 0) || (image_01[15][90] == 0 && image_01[16][90] == 0)))
        {
            black_count = 0;
            for(int i = 0; i < 40; i++)
            {
                if(image_01[i][90] == 0)
                    black_count++;
            }

            if(black_count > 15)
            {
                black_count = 0;

                Beep_ON;
                road_type.ZhangAi = 1;
                road_type.straight = 0;
                road_type.bend = 0;
            }
        }
        //�µ�
        else if(obstacles_flag == 0 && start1>50)
        {
            LED_Ctrl(LED0,RVS);
            for(int i = 30; i < 35; i++)
            {
                podao_white_count = 0;
                for(int j = 80; j < 100; j++)
                {
                    if(image_01[i][j] != 0)
                        podao_white_count++;
                 }

                if(podao_white_count > 5)
                    podao_white_hang++;
            }

            if(podao_white_hang >= 2 && length > 80)
            {
                LED_Ctrl(LED1,RVS);
                podao_white_hang = 0;
                podao_white_count = 0;

                Beep_ON;
                road_type.Podao = 1;
                road_type.straight = 0;
                road_type.bend = 0;
            }
        }
        //��·
        else if(duanlu_once_flag == 0 && image_01[60][90] == 0 && image_01[60][87] == 0 && image_01[60][97] == 0)
        {
            LED_Ctrl(LED0,RVS);
            if(obstacles_flag != 0)
            {
                for(int i = 115 ; i >= 95; i -= 5)
                {
                    black_count = 0;
                    for(int j = 70; j < 110; j += 4)
                    {
                        if(image_01[i][j] == 0)
                            black_count++;
                    }

                    if(black_count > 5)
                        black_hang++;
                }
            }


            if(black_hang >= 3)
            {
                black_hang = 0;
                Beep_ON;
                road_type.Duanlu = 1;
                road_type.straight = 0;
                road_type.bend = 0;
            }
        }
        //�ų�����Ԫ�أ��ж�ֱ�������
        else if(sudu_yingzi >= 85)
        {
            l_line_straight = 1000*Process_Curvity(l_line_x[MT9V03X_H-10], MT9V03X_H-10, l_line_x[MT9V03X_H-50], MT9V03X_H-50, l_line_x[MT9V03X_H-90], MT9V03X_H-90);
            r_line_straight = 1000*Process_Curvity(r_line_x[MT9V03X_H-10], MT9V03X_H-10, r_line_x[MT9V03X_H-50], MT9V03X_H-50, r_line_x[MT9V03X_H-90], MT9V03X_H-90);

            if(fabs(l_line_straight)<3 && fabs(r_line_straight)<3 && ((l_line_x[85] + r_line_x[85])/2-86) < 5)
            {
                road_type.straight =1;
                road_type.bend = 0;
            }
        }
        //���
        else
        {
            road_type.straight = 0;
            road_type.bend = 1;
        }
    }
}

//Ԫ�ش���
uint16 distance_L_Cross_out=0;
uint16 distance_R_Cross_out=0;
uint8 flag_L_shizi_R_turn=0;
uint8 flag_R_shizi_L_turn=0;

sint16 annulus_s1=0;
sint16 jiaodu_jifen =0;
sint16 annulus_jinku_s =0;

float cross_first = 0,cross_second = 0;
void  Element_Handle()
{
    /**************���**********************/
    if(road_type.Barn_l_in)
    {
        Handle_Barn_in(1);
    }
    else if(road_type.Barn_r_in)
    {
        Handle_Barn_in(2);
    }
    /***************Բ��*********************/
    else if(road_type.LeftCirque)
    {
        if(dont_handle_cirque == 1)
        {
            Dont_handle_l_cirque(); //ֱ��
        }
        else
        {
            Handle_Left_Cirque();
        }
    }
    else if(road_type.RightCirque)
    {
        if(dont_handle_cirque == 1)
        {
            Dont_handle_r_cirque(); //ֱ��
        }
        else
        {
            Handle_Right_Cirque();
        }
    }
    /*************ʮ��***********************/
    else if(road_type.Cross)
    {
        switch(cross_count)
        {
            case 0:
                if(cross_first == 1) //ʮ����ת
                    Handle_cross_l_turn();
                else if(cross_first == 2)
                    Handle_cross_r_turn();
                else
                    Handle_Cross();
                break;
            case 1:
                if(cross_second == 1) //ʮ����ת
                    Handle_cross_l_turn();
                else if(cross_second == 2)
                    Handle_cross_r_turn();
                else
                    Handle_Cross(); //ʮ��ǰ��
                break;
            default:
                Handle_Cross();
                break;
        }
    }
    else if(road_type.Podao)
    {
        Handle_Podao();
    }
    else if(road_type.ZhangAi)
    {
        speed = element_speed.ZhangAi_speed;
        Handle_ZhangAi();
    }
    else if(road_type.Duanlu)
    {
        if(duanlu_select == 0)
        {
            Handle_Duanlu1();
        }
        else
        {
            Handle_Duanlu();
        }
    }
    else if(road_type.bend)
    {
        if(duanlu_offset_limit_flag == 1)
            speed = 120;
        else
            speed = element_speed.bend_speed;
        road_type.bend = 0;
    }
    else if(road_type.straight)
    {
        if(duanlu_offset_limit_flag == 1)
            speed = 120;
        else
            speed = element_speed.straight_speed;
        road_type.straight = 0;
    }
}

void Calculate_Offset_1()
{
      offset =0;
      for(uint8 y =MT9V03X_H -1; y >=10; y--)    //���ý���ԶС��Ȩ�ؼ���ƫ��(�������)
      {
          m_line_x[y] =1.0*(l_line_x[y] +r_line_x[y])/2;    //�����벢����û����,ǧ�򲻿���ɾ
      }

      HDPJ_lvbo(m_line_x, 20, MT9V03X_H -1);   //ƽ�������˲�

      for(uint8 y =MT9V03X_H -30; y >=MT9V03X_H -40; y--)    //���ý���ԶС��Ȩ�ؼ���ƫ��(�������)
      {
          offset +=offset_quanzhong[MT9V03X_H-30 -y] *(m_line_x[y] - 86);
      }
      offset =offset/2;
      if(road_type.LeftCirque || road_type.RightCirque || road_type.Duanlu)
          offset = fclip(offset, -120, 120);
      else if(duanlu_offset_limit_flag == 1)
          offset = fclip(offset, -70, 70);
      else
          offset = fclip(offset, -140, 140);
}

void Calculate_Offset_d(void)
{
      offset =0;
      for(uint8 y =MT9V03X_H -1; y >=10; y--)    //���ý���ԶС��Ȩ�ؼ���ƫ��(�������)
      {
          m_line_x[y] =1.0*(l_line_x[y] +r_line_x[y])/2;    //�����벢����û����,ǧ�򲻿���ɾ
      }

      HDPJ_lvbo(m_line_x, 20, MT9V03X_H -1);   //ƽ�������˲�

      for(uint8 y =MT9V03X_H -60; y >=MT9V03X_H -70; y--)    //���ý���ԶС��Ȩ�ؼ���ƫ��(�������)
      {
          offset +=offset_quanzhong[MT9V03X_H-60 -y] *(m_line_x[y] - 86);
      }
      offset =offset/2;
      offset = fclip(offset, -100, 100);
}



extern float cheku_out_finish_flag;
//����ͷ����ȫ����
void Camera_Display(void)
{
    if(Camera_Flag == 2)
    {
        Transfer_Camera();                         //ͼ��ת��ɸı�ͼ���С
        Camera_Flag = 0;                           //��ͼ��ʹ����Ϻ�  ��������־λ�����򲻻Ὺʼ�ɼ���һ��ͼ��
        Get01change_Dajin();                       //��ֵ��
        Pixle_Filter();                            //��ʴ�������˲���

        if(cheku_out_finish_flag != 0)
        {
            Search_Line(0);                        //��������
            Check_Zhidao();                        //���ֱ��

            if((Start_Flag == 1)&&(shibie_flag == 0))
                Element_Test();                     //Ԫ��ʶ��

            Element_Handle();                       //Ԫ�ش���

            if(!road_type.Barn_l_in && !road_type.Barn_r_in && !cross_turn_flag && !road_type.ZhangAi && !road_type.Duanlu)
                Calculate_Offset_1();                //ƫ�����
        }
    }
}

//ԭʼͼ��ü�
uint8 image_yuanshi_jianchai[MT9V03X_H/2][MT9V03X_W/2];
void yuanshi_jianchai()
{
    short i = 0, j = 0, row = 0, line = 0;

    for (i = 0; i < MT9V03X_H; i+=2)
    {
        for (j = 0; j < MT9V03X_W; j+=2)
        {
            image_yuanshi_jianchai[row][line] = image_yuanshi[i][j];
            line++;
        }
        line = 0;
        row++;
    }
}

//��ֵ��ͼ��ü�
uint8 image_01_jianchai[MT9V03X_H/2][MT9V03X_W/2];
void erzhihua_jianchai()
{
    short i = 0, j = 0, row = 0, line = 0;

    for (i = 0; i < MT9V03X_H; i+=2)
    {
        for (j = 0; j < MT9V03X_W; j+=2)
        {
            image_01_jianchai[row][line] = image_01[i][j];
            line++;
        }
        line = 0;
        row++;
    }
}

//�Ż���Ĵ��
uint8 my_adapt_threshold(uint8 *image, uint16 col, uint16 row)   //ע�������ֵ��һ��Ҫ��ԭͼ��
{
   #define GrayScale 256
    uint16 width = col;
    uint16 height = row;
    int pixelCount[GrayScale];
    float pixelPro[GrayScale];
    int i, j, pixelSum = width * height/4;
    uint8 threshold = 0;
    uint8* data = image;  //ָ���������ݵ�ָ��
    for (i = 0; i < GrayScale; i++)
    {
        pixelCount[i] = 0;
        pixelPro[i] = 0;
    }

    uint32 gray_sum=0;
    //ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���
    for (i = 0; i < height; i+=2)
    {
        for (j = 0; j < width; j+=2)
        {
            pixelCount[(int)data[i * width + j]]++;  //����ǰ�ĵ������ֵ��Ϊ����������±�
            gray_sum+=(int)data[i * width + j];       //�Ҷ�ֵ�ܺ�
        }
    }

    //����ÿ������ֵ�ĵ�������ͼ���еı���

    for (i = 0; i < GrayScale; i++)
    {
        pixelPro[i] = (float)pixelCount[i] / pixelSum;

    }

    //�����Ҷȼ�[0,255]
    float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;


        w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
        for (j = 0; j < GrayScale; j++)
        {

                w0 += pixelPro[j];  //��������ÿ���Ҷ�ֵ�����ص���ռ����֮��   ���������ֵı���
                u0tmp += j * pixelPro[j];  //�������� ÿ���Ҷ�ֵ�ĵ�ı��� *�Ҷ�ֵ

               w1=1-w0;
               u1tmp=gray_sum/pixelSum-u0tmp;

                u0 = u0tmp / w0;              //����ƽ���Ҷ�
                u1 = u1tmp / w1;              //ǰ��ƽ���Ҷ�
                u = u0tmp + u1tmp;            //ȫ��ƽ���Ҷ�
                deltaTmp = w0 * pow((u0 - u), 2) + w1 * pow((u1 - u), 2);
                if (deltaTmp > deltaMax)
                {
                    deltaMax = deltaTmp;
                    threshold = (uint8)j;
                }
                if (deltaTmp < deltaMax)
                {
                break;
                }

         }

    return threshold;

}

uint16 X1=0,X2=0,Y1=0,Y2=0;   //��ʾһЩ����(��Ԫ�ص�ʱ��������һЩ������ֵ)
//ʶ������ߣ��жϳ��ⷽ�򣨲����������Ұ����ߣ�(��ʰ�����ߵĻ����ϸĽ���һ��)
uint8 flag_starting_line =0;
uint8 garage_direction =0;
void check_cheku(uint8 start_point, uint8 end_point ,uint8 qiangdu)
{ //garage_direction=1Ϊ�󳵿⣬garage_direction=2Ϊ�ҳ���
    uint8 times = 0;
    uint8 baise_hang = 0;                              //��ɫ�������жϳ��ⷽ��ʹ��
    flag_starting_line =0;                             //��03.18�Ļ���������������
    garage_direction =0;

    for (uint8 height =start_point; height >=end_point; height--)  //�жϰ�����
    {
        uint8 black_blocks_l =0, black_blocks_r =0;
        uint8 cursor_l =0, cursor_r =0;

        for (uint8 width_l =MT9V03X_W/2, width_r =MT9V03X_W/2; width_l >=1 && width_r<MT9V03X_W-2; width_l--,width_r++)
        {
            if (image_01[height][width_l] ==0 )  //!=0 ��ִ��
            {
                if (cursor_l >20)
                {
                    break;    //����ɫԪ�س���ջ���ȵĲ���   //���break�������
                }
                else
                {
                    cursor_l++;
                    X1=cursor_l;
                }
            }
            else
            {
                if (cursor_l >= qiangdu && cursor_l <= qiangdu+4)     //�����Χ�ǲ��Ǹ�С��(4,8) > (4,12)
                {
                    black_blocks_l++;
                    X2=black_blocks_l;
                    cursor_l =0;
                }
                else
                {
                    cursor_l =0;
                }
            }

            if (image_01[height][width_r] ==0)
            {
                if (cursor_r >= 20)
                {
                    break;    //����ɫԪ�س���ջ���ȵĲ���
                }
                else
                {
                    cursor_r++;
                }
            }
            else
            {
                if (cursor_r >= qiangdu && cursor_r <= qiangdu+4)
                {
                    black_blocks_r++;
                    cursor_r = 0;
                }
                else
                {
                    cursor_r = 0;
                }
            }
        }

        if ((black_blocks_l+black_blocks_r) >= 4 && (black_blocks_l+black_blocks_r) <= 8)
        {
            times++;
        }

        if (times >= (start_point -end_point-3))
        {
            flag_starting_line = 1;
        }
        else
        {
            flag_starting_line = 0;
        }
    }

    if(flag_starting_line ==1)         //�ѵ����������ٽ��г��ⷽ����ж�
    {
        cheku_flag = 1;       //�ѵ������߹رճ�����
        Beep_ON;
        LED_Ctrl(LED0,ON);
        for (uint8 height =start_point; height >=end_point; height--)
        {
            if(image_01[height][0] !=0)
            {
                baise_hang++;
            }
        }
        if(baise_hang >(start_point -end_point-2))       //����ɫ�࣬�������󣬷�������(1��2��)
        {
            road_type.Barn_l_in = 1;
            garage_direction = 1;
            baise_hang =0;
        }
        else
        {
            road_type.Barn_r_in = 1;
            garage_direction = 2;
            baise_hang =0;
        }
    }
}
/****************************END*****************************************/
