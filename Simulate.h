#ifndef SIMULATE_H
#define SIMULATE_H

#include "DoubleLinkList.h"

extern DList* lists[DirNum];

/* Read from document the cars information and add to the lists */
void InitCarInfo(const char* filename);

/* The main simulate loop */
void SimLoop();

/* Clear the double link list information */
void CleanUp();

#endif 
