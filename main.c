#include "header.h"
#include "body.c"

int main()
{
    initSystem();
    address TreeNonBinary = NULL;

    menuAwal(&TreeNonBinary);
    menuUtama(&TreeNonBinary);

    return 0;
}
