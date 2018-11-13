#ifndef CAR_H
#define CAR_H

enum
{
    North,
    East,
    South,
    West,
    DirNum,
};

enum
{
    Forward,
    Left,
    Right,
};

typedef struct
{
    short direction;
    short proceed;
    short arriveTime;
} Car;

void  PrintCar(Car car, float completeTime);

float NeedTime(Car car);

#endif
