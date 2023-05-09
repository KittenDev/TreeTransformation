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

// Variabel global untuk keperluan mempercantik visualisasi, tidak berkaitan dengan struktur
HANDLE hConsole;
CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
WORD saved_attributes;

CONSOLE_SCREEN_BUFFER_INFO csbi;
COORD WindowsSize;
// Variabel global untuk keperluan mempercantik visualisasi, tidak berkaitan dengan struktur

// Fungsi dan prosedur
address Alokasi(infotype key);
void CreateTree(address *TreeNonBinary, bool createRoot, int jmlNode);
void InsertNode(address *Data, infotype Parent, infotype Input);
void DeleteNode(address node);
void UpdateNode(address Data, infotype Key, infotype UpdateTo);
address SearchNode(address P, infotype X);
bool IsEmpty(address Data);
void Inorder(address P);
void DeleteTree(address *P);
void PostOrder(address P);
void PreOrder(address P);
void LevelOrder(address P);
void PrintTree(address P, int Level, bool binary);
void ConvertTree(address NonBinary, address *BinaryTarget);
void Balance(address *Data);
address BTtoDLL(address Data);
address Sort(address Data);
address DLLtoBT(address Data);
address GetMid(address head);
address Merge(address firstList, address secondList);
void ScanChar(char *input);
void ScanInteger(int *input, int Max, int Min);

// Fungsi terpisah untuk merepresentasikan menu menu yang ada
void menuMembuatTreeSendiri(address *TreeNonBinary);
void menuAwal(address *TreeNonBinary, address *TreeBinary);
void menuUtama(address *TreeNonBinary, address *TreeBinary);

// ================================================= Fungsi tambahan yang hanya berguna untuk mempercantik tampilan, tidak berpengaruh pada alur proses
void csrs(void);
void gotoxy(int x, int y);
void initSystem();
void printGridUI(char Pesan[]);
COORD ReadResolution();
void printc(char Pesan[]);
void printLine(char line);
void printCenterLine(char line, int StartPos);
void printHalfScreen(char Pesan[], bool isNewLine, bool cancelEnter);
// ================================================= Fungsi tambahan yang hanya berguna untuk mempercantik tampilan, tidak berpengaruh pada alur proses

#endif
