#include "header.h"
#include "body.c"

int main(int argc, char const *argv[])
{
    initSystem();
    address TreeNonBinary;

    menuAwal(&TreeNonBinary);

    system("cls");
    printc("Struktur Non Binary Tree");
    PrintTree(TreeNonBinary, 0);

    printf("Masukan Aksi:\n1.Insert\n2.Update\n3.Delete\n4.Search\n5.Konversi\n6.Exit");

    return 0;
}
