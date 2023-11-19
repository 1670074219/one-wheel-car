#include <menu.h>

typedef struct
{
    int menu_id;                                        // 菜单索引号
    char menu_name[30];                                 // 菜单显示名称
    void (*menu_action)(void);                          // 子菜单执行函数
    float *param;                                       // 需要传入处理的参数
} menu_item;

menu_item *current_menu_item; //现在菜单项
float change_level = 1; //数值改变大小

/***************图像显示标志位*******************/
float angle_flag = 0;
float gyro_flag = 0;
float acc_flag = 0;
float encoder_flag = 0;
float image_yuanshi_flag = 0;
float image_erzhihua_flag = 0;
float row_line = 0;
float column_line = 0;
float sideline_flag = 0;
float image_state_flag = 0;

/***************图像显示数据*******************/
extern uint8 cheku_stage;
extern float cheku_offset;
extern float cheku_out_angle;
extern float cheku_angle_set;
extern float cheku_out_encoder;
extern float cheku_out_finish_flag;
extern float cheku_out_encoder_set;
extern uint8 cheku_flag;
extern uint8 shibie_flag;
extern uint8 fache_flag;
extern float cheku_fangxiang;

/***************flash存储数组*******************/
float f32wBuff[40] = {0};
float f32wBuff1[50] = {0};
extern char txt[30];

void State_Reverse(void);
void Clear_all_flag(void);

void Save_Parameter(void)
{
    /**************pid参数******************/
    EEPROM_EraseSector(7);

    f32wBuff[0] = M.Gyro.pid.P;
    f32wBuff[1] = M.Gyro.pid.I;
    f32wBuff[2] = M.Angle.pid.P;
    f32wBuff[3] = M.Angle.pid.I;
    f32wBuff[4] = M.Angle.pid.D;
    f32wBuff[5] = M_Velocity_Kp;
    f32wBuff[6] = M_Velocity_Ki;
    f32wBuff[7] = M_Med_Angle;//balance

    f32wBuff[8] = X.Gyro.pid.P;
    f32wBuff[9] = X.Gyro.pid.I;
    f32wBuff[10] = X.Angle.pid.P;
    f32wBuff[11] = X.Angle.pid.I;
    f32wBuff[12] = X.Angle.pid.D;
    f32wBuff[13] = X_Velocity_Kp;
    f32wBuff[14] = X_Velocity_Ki;
    f32wBuff[15] = X_Med_Angle;//advance

    f32wBuff[16] = T.Gyro.pid.P;
    f32wBuff[17] = T.Gyro.pid.I;
    f32wBuff[18] = T.Angle.pid.P;
    f32wBuff[19] = T.Angle.pid.I;
    f32wBuff[20] = T.Angle.pid.D;
    if(speed != 0)
        f32wBuff[21] = speed;
    f32wBuff[22] = k_offset;//turn

    f32wBuff[23] = image_yuanshi_flag;
    f32wBuff[24] = image_erzhihua_flag;
    f32wBuff[25] = sideline_flag;
    f32wBuff[26] = row_line;
    f32wBuff[27] = column_line;
    f32wBuff[28] = image_state_flag;//image

    f32wBuff[29] = angle_flag;
    f32wBuff[30] = gyro_flag;
    f32wBuff[31] = acc_flag;
    f32wBuff[32] = encoder_flag;//state

    EEPROM_Write(7, 0, (unsigned long*)f32wBuff, 40);
    /**************pid参数******************/


    /**************element参数******************/
    EEPROM_EraseSector(8);

    f32wBuff1[0] = Duanlu_offset0;
    f32wBuff1[1] = Duanlu_angle0;
    f32wBuff1[2] = Duanlu_offset1;
    f32wBuff1[3] = Duanlu_angle1;
    f32wBuff1[19] = Duanlu_encoder_set;
    f32wBuff1[32] = duanlu_select;
    f32wBuff1[34] = x_axis_pre;
    f32wBuff1[35] = y_axis_pre;//duanlu

    f32wBuff1[4] = corss_encoder;
    f32wBuff1[5] = cross_l_turn_offset;
    f32wBuff1[6] = cross_l_turn_angle;
    f32wBuff1[7] = cross_r_turn_offset;
    f32wBuff1[8] = cross_r_turn_angle;
    f32wBuff1[28] = cross_first;
    f32wBuff1[29] = cross_second;//cross

    f32wBuff1[9] = l_angle_in;
    f32wBuff1[10] = l_angle_out;
    f32wBuff1[11] = r_angle_in;
    f32wBuff1[12] = r_angle_out;//circle

    f32wBuff1[13] = zhangai_offset0;
    f32wBuff1[14] = zhangai_angle0;
    f32wBuff1[15] = zhangai_offset1;
    f32wBuff1[16] = zhangai_angle1;
    f32wBuff1[17] = zhangai_offset2;
    f32wBuff1[18] = zhangai_angle2;
    f32wBuff1[47] = zhangai_dir;//zhangai

    //f32wBuff1[19] = Duanlu_encoder_set;//duanlu

    f32wBuff1[20] = cheku_out_finish_flag;
    f32wBuff1[21] = cheku_out_encoder_set;
    f32wBuff1[22] = cheku_offset;
    f32wBuff1[23] = cheku_angle_set;
    f32wBuff1[33] = cheku_fangxiang;//chuku_out

    f32wBuff1[24] = cheku_l_offset;
    f32wBuff1[25] = cheku_l_angle;
    f32wBuff1[26] = cheku_r_offset;
    f32wBuff1[27] = cheku_r_angle;//chuku_in

    //f32wBuff1[28] = cross_first;
    //f32wBuff1[29] = cross_second;//cross

    f32wBuff1[30] = podao_speed;
    f32wBuff1[31] = podao_encoder_set;//podao

    //f32wBuff1[32] = duanlu_select;//duanlu

    //f32wBuff1[33] = zhangai_dir;//zhangai

    //f32wBuff1[33] = cheku_fangxiang;//chuku

    //f32wBuff1[34] = x_axis_pre;
    //f32wBuff1[35] = y_axis_pre;//duanlu

    f32wBuff1[36] = element_speed.Cirque_speed;
    f32wBuff1[37] = element_speed.Cross_speed;
    f32wBuff1[38] = element_speed.DotCirque_speed;
    f32wBuff1[39] = element_speed.Duanlu_speed;
    f32wBuff1[40] = element_speed.ZhangAi_speed;
    f32wBuff1[41] = element_speed.bend_speed;
    f32wBuff1[42] = element_speed.straight_speed;

    f32wBuff1[43] = Threshold_add;

    f32wBuff1[44] = duanlu_seek_road;

    f32wBuff1[45] = Duanlu_set_angle;
    f32wBuff1[46] = Duanlu_back_speed;

    EEPROM_Write(8, 0, (unsigned long*)f32wBuff1, 50);
    /**************element参数******************/

    LED_Ctrl(LED0, ON);
    delayms(100);
    LED_Ctrl(LED0, OFF);
}

void Read_Parameter(void)
{
    /*************************pid*******************************/
    EEPROM_Read(7, 0, (unsigned long*)f32wBuff, 40);

    M.Gyro.pid.P = f32wBuff[0];
    M.Gyro.pid.I = f32wBuff[1];
    M.Angle.pid.P = f32wBuff[2];
    M.Angle.pid.I = f32wBuff[3];
    M.Angle.pid.D = f32wBuff[4];
    M_Velocity_Kp = f32wBuff[5];
    M_Velocity_Ki = f32wBuff[6];
    M_Med_Angle = f32wBuff[7];//balance

    X.Gyro.pid.P = f32wBuff[8];
    X.Gyro.pid.I = f32wBuff[9];
    X.Angle.pid.P = f32wBuff[10];
    X.Angle.pid.I = f32wBuff[11];
    X.Angle.pid.D = f32wBuff[12];
    X_Velocity_Kp = f32wBuff[13];
    X_Velocity_Ki = f32wBuff[14];
    X_Med_Angle = f32wBuff[15];//advance

    T.Gyro.pid.P = f32wBuff[16];
    T.Gyro.pid.I = f32wBuff[17];
    T.Angle.pid.P = f32wBuff[18];
    T.Angle.pid.I = f32wBuff[19];
    T.Angle.pid.D = f32wBuff[20];
    speed = f32wBuff[21];
    k_offset = f32wBuff[22];//turn

    image_yuanshi_flag = f32wBuff[23];
    image_erzhihua_flag = f32wBuff[24];
    sideline_flag = f32wBuff[25];
    row_line = f32wBuff[26];
    column_line = f32wBuff[27];
    image_state_flag = f32wBuff[28];//image

    angle_flag = f32wBuff[29];
    gyro_flag = f32wBuff[30];
    acc_flag = f32wBuff[31];
    encoder_flag = f32wBuff[32];
    /*************************pid*******************************/

    /*************************element*******************************/
    EEPROM_Read(8, 0, (unsigned long*)f32wBuff1, 50);

    Duanlu_offset0 = f32wBuff1[0];
    Duanlu_angle0 = f32wBuff1[1];
    Duanlu_offset1 = f32wBuff1[2];
    Duanlu_angle1 = f32wBuff1[3];
    Duanlu_encoder_set = f32wBuff1[19];
    duanlu_select = f32wBuff1[32];
    x_axis_pre = f32wBuff1[34];
    y_axis_pre = f32wBuff1[35];//duanlu

    corss_encoder = f32wBuff1[4];
    cross_l_turn_offset = f32wBuff1[5];
    cross_l_turn_angle = f32wBuff1[6];
    cross_r_turn_offset = f32wBuff1[7];
    cross_r_turn_angle = f32wBuff1[8];
    cross_first = f32wBuff1[28];
    cross_second = f32wBuff1[29];//cross

    l_angle_in = f32wBuff1[9];
    l_angle_out = f32wBuff1[10];
    r_angle_in = f32wBuff1[11];
    r_angle_out = f32wBuff1[12];//circle

    zhangai_offset0 = f32wBuff1[13];
    zhangai_angle0 = f32wBuff1[14];
    zhangai_offset1 = f32wBuff1[15];
    zhangai_angle1 = f32wBuff1[16];
    zhangai_offset2 = f32wBuff1[17];
    zhangai_angle2 = f32wBuff1[18];
    zhangai_dir = f32wBuff1[47];//zhangai

    //Duanlu_encoder_set = f32wBuff1[19];//duanlu

    cheku_out_finish_flag = f32wBuff1[20];
    cheku_out_encoder_set = f32wBuff1[21];
    cheku_offset = f32wBuff1[22];
    cheku_angle_set = f32wBuff1[23];
    cheku_fangxiang = f32wBuff1[33];//chuku_out

    cheku_l_offset = f32wBuff1[24];
    cheku_l_angle = f32wBuff1[25];
    cheku_r_offset = f32wBuff1[26];
    cheku_r_angle = f32wBuff1[27];//chuku_in

    //cross_first = f32wBuff1[28];
    //cross_second = f32wBuff1[29];//cross

    podao_speed = f32wBuff1[30];
    podao_encoder_set = f32wBuff1[31];//podao

    element_speed.Cirque_speed = f32wBuff1[36];
    element_speed.Cross_speed = f32wBuff1[37];
    element_speed.DotCirque_speed = f32wBuff1[38];
    element_speed.Duanlu_speed = f32wBuff1[39];
    element_speed.ZhangAi_speed = f32wBuff1[40];
    element_speed.bend_speed = f32wBuff1[41];
    element_speed.straight_speed = f32wBuff1[42];

    Threshold_add = f32wBuff1[43];

    duanlu_seek_road = f32wBuff1[44];

    Duanlu_set_angle = f32wBuff1[45];
    Duanlu_back_speed = f32wBuff1[46];
    /*************************element*******************************/
}

void yaw_collect() //惯性导航 yaw初始采集函数
{
    Yaw_Start = Yaw;
}

menu_item menu1[] = {
        /************************image*********************************/
        {01, "IMAGE", NULL, NULL},

        {10, "level", NULL, &change_level},
        {11, "Image_yuanshi", State_Reverse, &image_yuanshi_flag},
        {12, "Image_erzhihua", State_Reverse, &image_erzhihua_flag},
        {13, "sideline", State_Reverse, &sideline_flag},
        {14, "thre_add", NULL, &Threshold_add},
        //{15, "image_state", State_Reverse, &image_state_flag},
        {15, "b_angle", NULL, &Duanlu_set_angle},
        {16, "b_speed", NULL, &Duanlu_back_speed},
        {17, "Save", Save_Parameter, NULL},
        {18, "Return", NULL, NULL},
        /************************image*********************************/

        /************************PID*********************************/
        {02, "PID", NULL, NULL},

        {21, "Balance", NULL, NULL}, // 平衡
        {210, "level", NULL, &change_level},
        {211, "Return", NULL, NULL},
        {212, "gyro_kp", NULL, &M.Gyro.pid.P},
        {213, "gyro_ki", NULL, &M.Gyro.pid.I},
        {214, "angle_kp", NULL, &M.Angle.pid.P},
        {215, "angle_ki", NULL, &M.Angle.pid.I},
        {216, "angle_kd", NULL, &M.Angle.pid.D},
        {217, "speed_kp", NULL, &M_Velocity_Kp},
        {218, "speed_ki", NULL, &M_Velocity_Ki},
        {219, "M_Angle", NULL, &M_Med_Angle},

        {22, "Advance", NULL, NULL}, // 前进
        {220, "level", NULL, &change_level},
        {221, "Return", NULL, NULL},
        {222, "gyro_kp", NULL, &X.Gyro.pid.P},
        {223, "gyro_ki", NULL, &X.Gyro.pid.I},
        {224, "angle_kp", NULL, &X.Angle.pid.P},
        {225, "angle_ki", NULL, &X.Angle.pid.I},
        {226, "angle_kd", NULL, &X.Angle.pid.D},
        {226, "speed_kp", NULL, &X_Velocity_Kp},
        {227, "speed_ki", NULL, &X_Velocity_Ki},
        {228, "X_Angle", NULL, &X_Med_Angle},

        {23, "Turn", NULL, NULL}, // 转向
        {230, "level", NULL, &change_level},
        {231, "Return", NULL, NULL},
        {232, "gyro_kp", NULL, &T.Gyro.pid.P},
        {233, "gyro_ki", NULL, &T.Gyro.pid.I},
        {234, "angle_kp", NULL, &T.Angle.pid.P},
        {235, "angle_ki", NULL, &T.Angle.pid.I},
        {236, "angle_kd", NULL, &T.Angle.pid.D},
        {237, "Speed", NULL, &speed},
        {238, "k_offset", NULL, &k_offset},

        {24, "Save", Save_Parameter, NULL},
        {25, "CLEAR", Clear_all_flag, NULL},
        {26, "Return", NULL, NULL},
        /************************PID*********************************/

        /************************STATE*********************************/
        /*{03, "STATE", NULL, NULL},

        {30, "Return", NULL, NULL},
        {31, "Angle", State_Reverse, &angle_flag},
        {32, "Gyro", State_Reverse, &gyro_flag},
        {33, "Acc", State_Reverse, &acc_flag},
        {34, "Encoder", State_Reverse, &encoder_flag},
        {35, "Save", Save_Parameter, NULL},*/

        {03, "SPEED", NULL, NULL},
        {30, "level", NULL, &change_level},
        {31, "Return", NULL, NULL},
        {32, "cirque", NULL, &element_speed.Cirque_speed},
        {33, "dcirque", NULL, &element_speed.DotCirque_speed},
        {34, "cross", NULL, &element_speed.Cross_speed},
        {35, "duanlu", NULL, &element_speed.Duanlu_speed},
        {36, "zhangai", NULL, &element_speed.ZhangAi_speed},
        {37, "bend", NULL, &element_speed.bend_speed},
        {38, "straight", NULL, &element_speed.straight_speed},
        {39, "Save", Save_Parameter, NULL},
        /************************STATE*********************************/

        /************************ELEMENT*********************************/
        {04, "ELEMENT", NULL, NULL},

        {40, "circle", NULL, NULL},
        {400, "level", NULL, &change_level},
        {401, "Return", NULL, NULL},
        {402, "l_a_i", NULL, &l_angle_in},
        {403, "l_a_o", NULL, &l_angle_out},
        {404, "r_a_i", NULL, &r_angle_in},
        {405, "r_a_o", NULL, &r_angle_out},
        {406, "Save", Save_Parameter, NULL},
        {407, "Start", State_Reverse, &Start_Flag},

        {41, "cross", NULL, NULL},
        {410, "level", NULL, &change_level},
        {411, "Return", NULL, NULL},
        {412, "encoder", NULL, &corss_encoder},
        {413, "l_offset", NULL, &cross_l_turn_offset},
        {414, "l_angle", NULL, &cross_l_turn_angle},
        {415, "r_offset", NULL, &cross_r_turn_offset},
        {416, "r_angle", Save_Parameter, &cross_r_turn_angle},
        {417, "c_first", NULL, &cross_first},
        {418, "c_second", NULL, &cross_second},
        {419, "Save", Save_Parameter, NULL},

        {42, "podao", NULL, NULL},
        {420, "level", NULL, &change_level},
        {421, "Return", NULL, NULL},
        {422, "P_speed", NULL, &podao_speed},
        {423, "P_encoder", NULL, &podao_encoder_set},
        {424, "Save", Save_Parameter, NULL},
        {425, "Start", State_Reverse, &Start_Flag},

        {43, "zhangai", NULL, NULL},
        {430, "level", NULL, &change_level},
        {431, "Return", NULL, NULL},
        {432, "offset0", NULL, &zhangai_offset0},
        {433, "angle0", NULL, &zhangai_angle0},
        {434, "offset1", NULL, &zhangai_offset1},
        {435, "angle1", NULL, &zhangai_angle1},
        {436, "offset2", NULL, &zhangai_offset2},
        {437, "angle2", NULL, &zhangai_angle2},
        {438, "Save", Save_Parameter, NULL},
        {439, "Dir", State_Reverse, &zhangai_dir},

        {44, "duanlu", NULL, NULL},
        {440, "level", NULL, &change_level},
        {441, "Return", NULL, NULL},
        {442, "offset0", NULL, &Duanlu_offset0},
        {443, "angle0", NULL, &Duanlu_angle0},
        {444, "offset1", NULL, &Duanlu_offset1},
        {445, "angle1", NULL, &Duanlu_angle1},
        {446, "b_angle", NULL, &Duanlu_set_angle},
        {447, "b_speed", NULL, &Duanlu_back_speed},
        {448, "seekroad", State_Reverse, &duanlu_seek_road},
        {449, "Save", Save_Parameter, NULL},

        {45, "cheku_in", NULL, NULL},
        {450, "level", NULL, &change_level},
        {451, "Return", NULL, NULL},
        {452, "l_offset", NULL, &cheku_l_offset},
        {453, "l_angle", NULL, &cheku_l_angle},
        {454, "r_offset", NULL, &cheku_r_offset},
        {455, "r_angle", NULL, &cheku_r_angle},
        {456, "Save", Save_Parameter, NULL},
        {457, "Start", State_Reverse, &Start_Flag},

        {46, "cheku_out", NULL, NULL},
        {460, "level", NULL, &change_level},
        {461, "Return", NULL, NULL},
        {462, "finish", State_Reverse, &cheku_out_finish_flag},
        {463, "encoder", NULL, &cheku_out_encoder_set},
        {464, "offset", NULL, &cheku_offset},
        {465, "angle", NULL, &cheku_angle_set},
        {466, "Save", Save_Parameter, NULL},
        {467, "Start", State_Reverse, &Start_Flag},

        {47, "CLEAR", Clear_all_flag, NULL},

        {48, "START", State_Reverse, &Start_Flag},

        {49, "Return", NULL, NULL},
        /************************ELEMENT*********************************/

        {05, "INIT", NULL, NULL},
        {50, "level", NULL, &change_level},
        {51, "Return", NULL, NULL},
        {52, "D_sel", State_Reverse, &duanlu_select},
        {53, "C_first", NULL, &cross_first},
        {54, "C_second", NULL, &cross_second},
        {55, "Z_dir", State_Reverse, &zhangai_dir},
        {56, "F_dir", State_Reverse, &cheku_fangxiang},
        {57, "x_set", NULL, &x_axis_pre},
        {58, "y_set", NULL, &y_axis_pre},
        {59, "Save", Save_Parameter, NULL},

        {06, "YAW_S", yaw_collect, NULL},
        {07, "finish", State_Reverse, &cheku_out_finish_flag},
        {8, "CLEAR", Clear_all_flag, NULL},
        {9, "START", State_Reverse, &Start_Flag},
};

void State_Reverse(void) //标志位反转
{
    for (int i = 0; i < sizeof(menu1) / sizeof(menu1[0]); i++)
    {
        if (menu1[i].menu_id == current_menu_item->menu_id)
        {
            *current_menu_item->param = !(*current_menu_item->param);
        }
    }
}

void Clear_all_flag(void) //清楚所有标志位
{
    Beep_OFF;
    LED_Ctrl(LED0,OFF);
    LED_Ctrl(LED1,OFF);

    if(cheku_out_finish_flag == 0)
        speed = 0;
    else
        speed = f32wBuff[21];
    offset = 0;
    Start_Flag = 0;
    start1 = 0;
    fache_flag = 0;
    //cheku_out_finish_flag = 0;

    road_type.LeftCirque = 0;//circle
    road_type.RightCirque = 0;
    huandao_stage=1;
    huandao_flag = 0;
    huandao_angle = 0;
    dont_handle_flag = 0;
    dont_handle_encoder = 0;

    road_type.Cross = 0;
    cross_count = 0;
    cross_s = 0;
    cross_turn_angle = 0;
    cross_turn_flag = 0;
    cross_flag = 0;

    road_type.ZhangAi = 0;
    zhangai_once_flag = 0;
    zhangai_flag = 0;
    zhangai_stage = 0;
    zhangai_angle = 0;

    road_type.Podao = 0;
    podao_flag = 0;
    podao_encoder = 0;

    road_type.Duanlu = 0;
    Duanlu_stage = 0;
    Duanlu_flag = 0;
    Duanlu_angle = 0;
    duanlu_white_count = 0;
    duanlu_once_flag = 0;
    dont_handle_cirque = 0;
    Duanlu_Flag1 = 0;
    duanlu_finish_stage = 0;
    duanlu_offset_limit_flag = 0;

    road_type.Barn_l_in = 0;
    road_type.Barn_r_in = 0;
    cheku_flag = 0;
    shibie_flag = 0;
    cheku_sum_flag = 0;
    cheku_angle = 0;

    cheku_stage = 0;
    cheku_out_angle = 0;
    cheku_out_encoder = 0;

    angle_integral = 0;
    x_axis = 0;
    y_axis = 0;

    LED_Ctrl(LED1, ON);
    delayms(100);
    LED_Ctrl(LED1, OFF);
}

extern uint8 Duanlu_stage;
void State_Display(void) //显示数据函数
{
    char txt[30];

    /*Regression(1, 40, 90);    //拟合左线
    k_left = parameterB;
    Regression(2, 40, 90);    //拟合左线
    k_right = parameterB;*/

    if(angle_flag)
    {
        sprintf(txt,"p:%-5.2f",Pitch);
        TFTSPI_P6X8Str(1, 1, txt, u16CYAN, u16BLACK);
        sprintf(txt,"r:%-5.2f",Roll);
        TFTSPI_P6X8Str(1, 2, txt, u16CYAN, u16BLACK);
        sprintf(txt,"y:%-5.2f",Yaw);
        TFTSPI_P6X8Str(1, 3, txt, u16CYAN, u16BLACK);
    }

    if(gyro_flag)
    {
        sprintf(txt,"gx:%-5d",gyro[0]);
        TFTSPI_P6X8Str(8, 1, txt, u16CYAN, u16BLACK);
        sprintf(txt,"gy:%-5d",gyro[1]);
        TFTSPI_P6X8Str(8, 2, txt, u16CYAN, u16BLACK);
        sprintf(txt,"gz:%-5d",gyro[2]);
        TFTSPI_P6X8Str(8, 3, txt, u16CYAN, u16BLACK);
    }

    if(acc_flag)
    {
        sprintf(txt,"ax:%-6d",accel[0]);
        TFTSPI_P6X8Str(13, 1, txt, u16CYAN, u16BLACK);
        sprintf(txt,"ay:%-6d",accel[1]);
        TFTSPI_P6X8Str(13, 2, txt, u16CYAN, u16BLACK);
        sprintf(txt,"az:%-6d",accel[2]);
        TFTSPI_P6X8Str(13, 3, txt, u16CYAN, u16BLACK);
    }

    if(encoder_flag)
    {
        sprintf(txt,"Ea:%-4d",Encoder_A);
        TFTSPI_P6X8Str(1, 4, txt, u16CYAN, u16BLACK);
        sprintf(txt,"Eb:%-4d",Encoder_B);
        TFTSPI_P6X8Str(1, 5, txt, u16CYAN, u16BLACK);
        sprintf(txt,"Ec:%-4d",Encoder_C);
        TFTSPI_P6X8Str(1, 6, txt, u16CYAN, u16BLACK);
    }

    if((image_yuanshi_flag == 1)&&(image_erzhihua_flag == 0))
    {
        yuanshi_jianchai();
        TFTSPI_Road(0, 0, IMAGEH/2, MT9V03X_W/2, (unsigned char *)image_yuanshi_jianchai);
    }

    if((image_yuanshi_flag == 0)&&(image_erzhihua_flag == 1))
    {
        erzhihua_jianchai();
        TFTSPI_BinRoad(0, 0, IMAGEH/2, MT9V03X_W/2, (unsigned char *)image_01_jianchai);
    }

    if(sideline_flag)
    {
        for(int i = 119; i > 10; i--)
        {
            TFTSPI_Draw_Dot(l_line_x[i]/2,l_line_y[i]/2,u16CYAN);
            TFTSPI_Draw_Dot(r_line_x[i]/2,r_line_y[i]/2,u16PURPLE);
            TFTSPI_Draw_Dot((r_line_x[i]+l_line_x[i])/4,(r_line_y[i]+l_line_y[i])/4,u16RED);
            TFTSPI_Draw_Line(43,0,43,60,u16BLUE);
            TFTSPI_Draw_Line(0,45,90,45,u16BLUE);

            /*if(Start_Flag)
                printf("%d : %d\n",i,(r_line_x[i]-l_line_x[i]));*/
        }
    }

    if(image_state_flag)
    {
        sprintf(txt,"offset:%.2f",offset);
        TFTSPI_P6X8Str(1, 12, txt, u16CYAN, u16BLACK);
    }

    sprintf((char*)txt,"%.1f",x_axis);
    TFTSPI_P8X8Str(12,0,txt,u16CYAN,u16BLACK);
    sprintf((char*)txt,"%.1f",y_axis);
    TFTSPI_P8X8Str(12,1,txt,u16CYAN,u16BLACK);
    sprintf((char*)txt,"DS:%d",Duanlu_stage);
    TFTSPI_P8X8Str(12,2,txt,u16CYAN,u16BLACK);
    sprintf((char*)txt,"%.1f",offset);
    TFTSPI_P8X8Str(12,3,txt,u16CYAN,u16BLACK);
    sprintf((char*)txt,"%.1f",angle_integral);
    TFTSPI_P8X8Str(12,4,txt,u16CYAN,u16BLACK);
    sprintf((char*)txt,"DF:%d",duanlu_finish_stage);
    TFTSPI_P8X8Str(12,5,txt,u16CYAN,u16BLACK);
    /*sprintf((char*)txt,"CK:%d",cheku_flag);
    TFTSPI_P8X8Str(12,6,txt,u16CYAN,u16BLACK);
    sprintf((char*)txt,"B:%d",road_type.bend);
    TFTSPI_P8X8Str(12,7,txt,u16CYAN,u16BLACK);
    sprintf((char*)txt,"%d",Duanlu_stage);
    TFTSPI_P8X8Str(12,8,txt,u16CYAN,u16BLACK);
    */
    /*sprintf((char*)txt,"y:%.1f",Yaw_Start);
    TFTSPI_P8X8Str(12,0,txt,u16CYAN,u16BLACK);
    sprintf((char*)txt,"T:%d",Threshold);
    TFTSPI_P8X8Str(12,1,txt,u16CYAN,u16BLACK);
    sprintf((char*)txt,"%.1f",offset);
    TFTSPI_P8X8Str(12,2,txt,u16CYAN,u16BLACK);
    sprintf((char*)txt,"%d",cheku_flag);
    TFTSPI_P8X8Str(12,3,txt,u16CYAN,u16BLACK);*/


}

uint8 have_sub_menu(int menu_id) // 查看是否存在子菜单
{
    for (int i = 0; i < sizeof(menu1) / sizeof(menu1[0]); i++)
    {
        if (menu1[i].menu_id / 10 == menu_id)
        {
            return 1;
        }
    }
    return 0;
}

int show_sub_menu(int parent_id, int highlight_col) // 显示子菜单，以及当前高亮菜单
{
    TFTSPI_CLS(u16BLACK);
    int item_idx = 0;

    for (int i = 0; i < sizeof(menu1) / sizeof(menu1[0]); i++)
    {
        if (menu1[i].menu_id / 10 == parent_id)
        {
            if (item_idx == highlight_col)
            {
                current_menu_item = &menu1[i];

                TFTSPI_P6X8Str(1, item_idx+10, menu1[i].menu_name, u16YELLOW, u16BLACK);
                if(menu1[i].param != NULL)
                {
                    sprintf(txt,"%f",*menu1[i].param);
                    TFTSPI_P6X8Str(10, item_idx+10, txt, u16YELLOW, u16BLACK);
                }
            }
            else
            {
                TFTSPI_P6X8Str(1, item_idx+10, menu1[i].menu_name, u16CYAN, u16BLACK);
                if(menu1[i].param != NULL)
                {
                    sprintf(txt,"%f",*menu1[i].param);
                    TFTSPI_P6X8Str(10, item_idx+10, txt, u16CYAN, u16BLACK);
                }
            }
            item_idx++;
        }
    }

    return item_idx;
}

void Menu_Switch(void) //菜单执行函数 检测按键动作 cup0while
{
    uint8 level_index = 5;
    int parent_menu_id = 0;
    int highlight_col = 0; // 设定高亮行号
    int menu_item_count = show_sub_menu(parent_menu_id, highlight_col);
    float level[9] = {0.00001, 0.0001, 0.001, 0.01, 0.1, 1, 10, 100, 1000};
    //static uint8 mode = 0;

    while (1)
    {
        if (key_switch()) // 读取按键函数
        {
            if (key_state[3]) // 按下按键1减少当前行数
            {
                highlight_col--;

                if(/*(mode == 0) &&*/ (highlight_col < 0))
                {
                    highlight_col = menu_item_count - 1;
                }
                /*else if(mode != 0)
                {
                    if((strcmp(current_menu_item->menu_name, "level") == 0))
                    {
                        if(level_index<6)
                            level_index++;
                        change_level = level[level_index];
                    }
                    else if(current_menu_item->param != NULL)
                    {
                        *current_menu_item->param += change_level;
                    }
                }*/
            }

            else if (key_state[2]) // 按下按键2增加当前行数
            {
                highlight_col++;

                if(highlight_col >= menu_item_count)
                    highlight_col = 0;

/*                if((mode == 0) && (highlight_col >= menu_item_count - 1))
                {
                    highlight_col = 0;
                }*/
                /*else
                {
                    if((strcmp(current_menu_item->menu_name, "level") == 0))
                    {
                        if(level_index>0)
                            level_index--;
                        change_level = level[level_index];
                    }
                    else if(current_menu_item->param != NULL)
                    {
                        *current_menu_item->param -= change_level;
                    }
                }*/
            }

            else if (key_state[1])
            {
                if (have_sub_menu(current_menu_item->menu_id))
                {
                    highlight_col = 0;
                    parent_menu_id = current_menu_item->menu_id;
                }
                else if (strcmp(current_menu_item->menu_name, "Return") == 0) // 如果当前菜单为“Return”，则返回上一级
                {
                    if((current_menu_item->menu_id)/10 != 0)
                    {
                        highlight_col = 0;
                        parent_menu_id = (current_menu_item->menu_id)/100;
                    }
                }
                else if (current_menu_item->menu_action)
                {
                    current_menu_item->menu_action();
                }

            }
            else if(key_state[0])
            {
                //mode = !mode;
                if((strcmp(current_menu_item->menu_name, "level") == 0))
                {
                    if(level_index<8)
                        level_index++;
                    change_level = level[level_index];
                }
                else if(current_menu_item->param != NULL)
                {
                    *current_menu_item->param += change_level;
                }
            }
            else if(key_state[4])
            {
                if((strcmp(current_menu_item->menu_name, "level") == 0))
                {
                    if(level_index>0)
                        level_index--;
                    change_level = level[level_index];
                }
                else if(current_menu_item->param != NULL)
                {
                    *current_menu_item->param -= change_level;
                }
            }

            menu_item_count = show_sub_menu(parent_menu_id, highlight_col);
            key_clear_all_state();
        }

        State_Display();

        /*************************出库 采用写死 速度角度确定死**************************************/
        switch(cheku_stage)
        {
            case 0:
                if(cheku_out_finish_flag == 0)
                {
                    if(Start_Flag == 1)
                    {
                        speed = 0;
                        offset = 0;
                        delayms(2000);
                        speed = 110;
                        cheku_stage=1;
                    }
                }
                break;
            case 1:
                if(cheku_out_encoder > cheku_out_encoder_set)
                {
                    LED_Ctrl(LED0,ON);
                    cheku_stage = 2;
                }
                break;
            case 2:
                if(cheku_fangxiang == 0)
                    offset = cheku_offset; //右出库  offset = -30;左出库
                else
                    offset = -cheku_offset;


                if((cheku_out_angle > cheku_angle_set) || (cheku_out_angle < -cheku_angle_set))
                {
                    LED_Ctrl(LED0,OFF);
                    cheku_stage = 3;
                    cheku_out_angle = 0;
                    speed = f32wBuff[21];
                    cheku_out_finish_flag = 1;
                }
        }
        /*************************出库**************************************/
    }
}

