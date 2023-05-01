#include "header.h"

int main()
{
    initSystem();
    address TreeNonBinary = NULL;

    menuAwal(&TreeNonBinary);
    menuUtama(&TreeNonBinary);

    return 0;
}

#include "body.c"