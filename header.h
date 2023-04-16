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

void InsertNode(infotype cari, infotype insert);

void DeleteNode(address tree, infotype P);

void UpdateNode(address tree, infotype P);

address SearchNode(address tree, infotype P);

bool IsEmpty(address tree);

void Inorder(address tree);

void LevelOrder(address tree);

void ConvertTree(address nonBinary, address Binary);

void Balance(address tree);

#endif
