#ifndef header
#define header

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define infotype char
#define Info(P) (P)->info
#define Parent(P) (P)->ps_pr
#define FirstSon(P) (P)->ps_left
#define NextBrother(P) (P)->ps_right
#define LeftSon(P) (P)->ps_left
#define RightSon(P) (P)->ps_right

typedef struct tStructTree *address;
typedef struct tStructTree
{
    infotype info;
    address ps_pr, ps_left, ps_right;
} StructTree;

address Allocation(infotype key);

void TreeInitialization(address P);

void InsertNode(address Data, infotype Parent, infotype Input);

void DeleteNode(address Data, infotype Key);

void UpdateNode(address Data, infotype Key, infotype UpdateTo);

address SearchNode(StructTree P, infotype X);

bool IsEmpty(StructTree Data);

void Inorder(StructTree P);

void PostOrder(StructTree P);

void PreOrder(StructTree P);

void PrintTree(StructTree P, int Level);

void ConvertTree(StructTree NonBinary, address BinaryTarget);

void Balance(address Data);

address BTtoDLL(StructTree Data);

address Sort(StructTree Data);

address DLLtoBT(StructTree Data);

address GetMid(address head);

address Merge(address firstList, address secondList);

#endif
