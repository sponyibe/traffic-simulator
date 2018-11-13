#include <stdio.h>
#include <math.h>
#include "Car.h"

void PrintCar(Car car, float finishTime)
{
    switch (car.direction)
    {
    case North: printf("N "); break;
    case South: printf("S "); break;
    case East: printf("E "); break;
    case West: printf("W "); break;
    }

    switch (car.proceed)
    {
    case Forward: printf("F "); break;
    case Left: printf("L "); break;
    case Right: printf("R "); break;
    }

    printf("%d\t%d\t", car.arriveTime, car.arriveTime);
    
    int tmVal = finishTime * 10;
    if (tmVal % 10 == 0)
        printf("%d\n", tmVal / 10);
    else
        printf("%.1f\n", finishTime);
}

float NeedTime(Car car)
{
    switch (car.proceed)
    {
    case Forward: return 2;
    case Left: return 2.5;
    case Right: return 1;
    }
    return 0;
}