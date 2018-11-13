#include <stdlib.h>
#include <stdio.h>
#include "Simulate.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s carfile\n", argv[0]);
        exit(0);
    }
    
    InitCarInfo(argv[1]);
    
    // Simulate loop 
    SimLoop();

    CleanUp();
    return 0;
}

