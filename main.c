#include "header.h"
#include "body.c"

int main(int argc, char const *argv[])
{
    address TreeNonBinary;
    int tempPilihan;
    /* code */
    printc("Initialisasi Data Tree\n");

    printf("Tree Default:\n");
    printf("R\n");
    printf("|--O\n");
    printf("|  |--I\n");
    printf("|  |  |--M\n");
    printf("|  |  |--S\n");
    printf("|  |  |--F\n");
    printf("|--U\n");
    printf("|  |--T\n");
    printf("|  |--N\n");
    printf("|  |--E\n");

    printf("\nPilih opsi tree yang akan digunakan\n");
    printf("1. Tree Default\n");
    printf("2. Make your own Tree\n");
    ScanInteger(&tempPilihan);
    switch (tempPilihan)
    {
    case 1:
        InsertNode(&TreeNonBinary, ' ', 'R'); // Parent
        InsertNode(&TreeNonBinary, 'R', 'O');
        InsertNode(&TreeNonBinary, 'R', 'U');
        InsertNode(&TreeNonBinary, 'O', 'I');
        InsertNode(&TreeNonBinary, 'I', 'M');
        InsertNode(&TreeNonBinary, 'I', 'S');
        InsertNode(&TreeNonBinary, 'I', 'F');
        InsertNode(&TreeNonBinary, 'U', 'T');
        InsertNode(&TreeNonBinary, 'U', 'N');
        InsertNode(&TreeNonBinary, 'U', 'E');
        break;

    case 2:
        system("cls");
        printf("Masukan jumlah node pada tree : ");
        ScanInteger(&tempPilihan);
        CreateTree(&TreeNonBinary, tempPilihan);
        break;
    }

    system("cls");
    printc("Struktur Non Binary Tree");
    PrintTree(TreeNonBinary, 0);

    printf("Masukan Aksi:\n1.Insert\n2.Update\n3.Delete\n4.Search\n5.Konversi\n6.Exit");

    return 0;
}
