#include <stdio.h>
#include <stdlib.h>
#include "Simulate.h"

DList* lists[DirNum];

void InitCarInfo(const char* filename)
{
    FILE* fpCar = fopen(filename, "r");
    if (!fpCar)
    {
        fprintf(stderr, "Can not open file: %s!\n", filename);
        exit(0);
    }
	int i;
    for (i = 0; i < DirNum; ++i)
    {
        lists[i] = InitList();
    }

    while (!feof(fpCar))
    {
        char sdirection[4] = { 0 }, sproceed[4] = { 0 };
        int itime = 0;
        if (fscanf(fpCar, "%s %s %d", sdirection, sproceed, &itime) != 3)
            break;
        Car car;
        car.arriveTime = itime;
        switch (sproceed[0])
        {
        case 'F': car.proceed = Forward; break;
        case 'L': car.proceed = Left; break;
        case 'R': car.proceed = Right; break;
        }
        switch (sdirection[0])
        {
        case 'S': car.direction = South; break;
        case 'N': car.direction = North; break;
        case 'E': car.direction = East; break;
        case 'W': car.direction = West; break;
        }
        InsLast(lists[car.direction], MakeNode(car));
    }

    fclose(fpCar);
}

void CleanUp()
{
	int i;
    for (i = 0; i < DirNum; ++i)
        DestroyList(lists[i]);
}

int IsCarExist()
{
	int i;
    for (i = 0; i < DirNum; ++i)
    {
        if (!IsEmpty(lists[i])) /* If any list has car, then return 1 */
            return 1;
    }
    return 0;
}

void SimLoop()
{
    float globaTime = 1;
    int lightsDir = North;

    while (1)
    {
        if (!IsCarExist())
            break;

        DList* carList = lists[lightsDir];
        float greenEnd = globaTime + 10;  /* the end time for green light this direction */
        
        /* simulate the green light for this direction */
        while (globaTime < greenEnd)
        {
            PNode firstCar = GetFirst(carList);
            if (!firstCar || firstCar->car.arriveTime >= greenEnd)   /* no first car or first car enter after the green light */
            {
                globaTime = greenEnd;
            }
            else if (firstCar->car.arriveTime > globaTime)  /* the first car enter after now but before light turn yellow */
            {
                globaTime = firstCar->car.arriveTime;
            }
            else
            {
                /* check the first car can move */
                float needtime = NeedTime(firstCar->car);
                if (greenEnd - globaTime >= needtime)   /* if time is enough then pass the intersection directly */
                {
                    globaTime += needtime;
                    PrintCar(firstCar->car, globaTime);
                    firstCar = DelFirst(carList);
                    /* delete the space allocated for the node */
                    FreeNode(firstCar);
                }
                else /* if the first car can not pass, then just wait the light turn yellow */
                {
                    globaTime = greenEnd;
                }
            }
        }

        float yellowEnd = greenEnd + 3; /* the end time for yellow light this direction */
        /* Now the light turn yellow, simulate the yellow light for this direction */
        while (globaTime < yellowEnd)
        {
            PNode firstCar = GetFirst(carList);
            if (!firstCar || firstCar->car.arriveTime >= yellowEnd)   /* no first car or the first car enter after the yellow light */
            {
                globaTime = yellowEnd;
            }
            else if (firstCar->car.arriveTime > globaTime)  /* the first car enter after current time but before safety time */
            {
                globaTime = firstCar->car.arriveTime;
            }
            else
            {
                /* check the car can move, if not move then wait till yellow light end */
                float needtime = NeedTime(firstCar->car);
                if (yellowEnd - globaTime >= needtime && firstCar->car.direction == Left)   /* only the turn left char can pass */
                {
                    globaTime += needtime;
                    PrintCar(firstCar->car, globaTime);
                    firstCar = DelFirst(carList);
                    FreeNode(firstCar);
                }
                else
                {
                    globaTime = yellowEnd;
                }
            }
        }

        globaTime = yellowEnd + 1;  /* 1 second for safety time */

        /* change to another direction */
        lightsDir++;
        lightsDir %= DirNum;
    }
}
