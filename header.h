#ifndef header_H
#define header_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <conio.h>

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

void InsertNode(address* Data, infotype Parent, infotype Input);

void DeleteNode(address Data, infotype Key);

void UpdateNode(address Data, infotype Key, infotype UpdateTo);

address SearchNode(address P, infotype X);

bool IsEmpty(address Data);

void Inorder(address P);

void PostOrder(address P);

void PreOrder(address P);

void PrintTree(address P, int Level);

void ConvertTree(address NonBinary, address BinaryTarget);

void Balance(address Data);

address BTtoDLL(address Data);

address Sort(address Data);

address DLLtoBT(address Data);

address GetMid(address head);

address Merge(address firstList, address secondList);

void ScanChar (char *input);    

void ScanInteger (int *input);

#endif
