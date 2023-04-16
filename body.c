#include "header.h"

address Allocation(infotype key) 
{
    address P;

    P = (address) malloc (sizeof(StructTree));

    if (!P)
    {
        Info(P) = key;
        Parent(P) = NULL;
        FirstSon(P) = NULL;
        NextBrother(P) = NULL;
    }
    
    return P;
}