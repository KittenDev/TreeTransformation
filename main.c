#include "header.h"

int main()
{
    initSystem();
    address TreeNonBinary = NULL;
    address TreeBinary = NULL;

    menuAwal(&TreeNonBinary, &TreeBinary);
    menuUtama(&TreeNonBinary, &TreeBinary);

    return 0;
}

#include "body.c"