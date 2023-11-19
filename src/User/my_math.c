/*
 * math.c
 *
 *  Created on: 2021年4月3日
 *      Author: 后
 */

#include "my_math.h"

int clip(int x, int low, int up) {
    return x > up ? up : x < low ? low : x;
}

float fclip(float x, float low, float up) {
    return x > up ? up : x < low ? low : x;
}

float invSqrt(float x) {
    float halfx = 0.5f * x;
    float y = x;
    long i = *(long*)&y;
    i = 0x5f3759df - (i>>1);
    y = *(float*)&i;
    y = y * (1.5f - (halfx * y * y));
    return y;
}

//快速计算 Sqrt(x)
float my_sqrt(float number)
{
    // long i;
    // float x, y;
    // const float f = 1.5F;
    // x = number * 0.5F;
    // y = number;
    // i = *(long *)&y;
    // i = 0x5f3759df - (i >> 1);

    // y = *(float *)&i;
    // y = y * (f - (x * y * y));
    // y = y * (f - (x * y * y));
    return invSqrt(number) * number;
}





//希尔排序法一
void shellSort16(sint16 a[],int n){
    sint16 i,j,gap,temp;
    for(gap = n/2;gap>0;gap/=2){
        for(i=gap;i<n;i+=gap){
            temp = a[i];
            for(j = i-gap;j>=0&&a[j]>temp;j-=gap){
                a[j+gap] = a[j];
            }
            a[j+gap] = temp;
        }
    }
}



