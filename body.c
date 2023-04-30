#include "header.h"

address Alokasi(infotype key)
{
    address P;

    P = (address)malloc(sizeof(StructTree));

    if (!P)
    {
        printf("Memori Penuh!");
        exit(0);
    }
    else
    {
        Info(P) = key;
        Parent(P) = NULL;
        FirstSon(P) = NULL;
        NextBrother(P) = NULL;
    }

    return P;
}

void CreateTree(address *TreeNonBinary, bool createRoot, int jmlNode)
{
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    COORD cursorPos = consoleInfo.dwCursorPosition;
    char pesan[50];

    for (int i = 0; i <= jmlNode; i++)
    {
        system("cls");
        printGridUI("INPUT DATA NON BINARY TREE");
        printf("Kondisi non binary tree :\n");
        if (i > 0 || !createRoot)
            PrintTree(*TreeNonBinary, 0);

        if (i != jmlNode)
        {
            infotype inputInfo, inputParent;
            gotoxy(cursorPos.X, cursorPos.Y);
            if (i == 0 && createRoot)
            {
                printHalfScreen("Masukan karakter untuk root: ", false, true);
                ScanChar(&inputInfo);
                inputParent = ' ';
            }
            else
            {
                sprintf(pesan, "Masukan karakter parent untuk node ke [%d]: ", i + 1);
                printHalfScreen(pesan, false, true);
            Start:
                ScanChar(&inputParent);
                if (!SearchNode(*TreeNonBinary, inputParent))
                {
                    printHalfScreen("Parent tidak ditemukan, harap insert parent baru : ", false, true);
                    goto Start;
                }

                sprintf(pesan, "Masukan karakter untuk node ke [%d]: ", i + 1);
                printHalfScreen(pesan, false, false);
                ScanChar(&inputInfo);
            }

            InsertNode(TreeNonBinary, inputParent, inputInfo);
        }
    }

    gotoxy(0, 2);
    printHalfScreen("Proses insert berhasil, tekan ENTER untuk melanjutkan...", true, false);
    getch();
}

void InsertNode(address *Data, infotype Parent, infotype Input)
{
    address TempTraversal, FinalPos, ParentNode;

    if (!IsEmpty(*Data))
    {

        TempTraversal = SearchNode(*Data, Parent);
        ParentNode = TempTraversal;
        // Menentukan apakah ia akan menjadi first son atau menjadi last son
        if (FirstSon(TempTraversal) == NULL)
        {
            FirstSon(TempTraversal) = Alokasi(Input);
            FinalPos = FirstSon(TempTraversal);
        }
        else
        {
            TempTraversal = FirstSon(TempTraversal);
            while (NextBrother(TempTraversal) != NULL)
            {
                TempTraversal = NextBrother(TempTraversal);
            }
            NextBrother(TempTraversal) = Alokasi(Input);
            FinalPos = NextBrother(TempTraversal);
        }
        // Menentukan apakah ia akan menjadi first son atau menjadi last son
        Parent(FinalPos) = ParentNode;
    }
    else
    {
        *Data = Alokasi(Input);
    }
}

void DeleteNode(address *Data, infotype Key) //! MASIH NGEBUG JIKA DELETE ELEMEN TENGAH
{
    address search = SearchNode(*Data, Key); // Mencari node yang akan dihapus
    if (!search)
        return; // Jika node tidak ditemukan, langsung keluar dari fungsi

    address parent = Parent(search);           // Menyimpan pointer ke parent node yang akan dihapus
    address firstSon = FirstSon(search);       // Menyimpan pointer ke first son node yang akan dihapus
    address nextBrother = NextBrother(search); // Menyimpan pointer ke next brother node yang akan dihapus

    if (parent)
    {
        if (FirstSon(parent) == search) // Jika node yang akan dihapus adalah first son dari parent
        {
            FirstSon(parent) = firstSon; // Mengganti first son parent dengan first son node yang akan dihapus
        }
        else
        {
            address prevBrother = FirstSon(parent);
            while (NextBrother(prevBrother) != search)
            {
                prevBrother = NextBrother(prevBrother);
            }
            NextBrother(prevBrother) = firstSon; // Mengganti next brother sebelum node yang akan dihapus dengan first son node yang akan dihapus
        }

        if (firstSon)
        {
            address lastChild = firstSon;
            while (NextBrother(lastChild))
            {
                lastChild = NextBrother(lastChild);
            }

            NextBrother(lastChild) = nextBrother; // Mengganti next brother anak terakhir dari node yang akan dihapus dengan next brother node yang akan dihapus
        }
    }
    else
    {
        *Data = firstSon; // Jika node yang akan dihapus adalah root, mengganti root dengan first son node yang akan dihapus
    }

    if (firstSon)
    {
        Parent(firstSon) = parent;           // Memperbarui parent dari first son node yang akan dihapus
        NextBrother(firstSon) = nextBrother; // Memperbarui next brother dari first son node yang akan dihapus
    }

    free(search); // Menghapus memory yang dialokasikan untuk node yang dihapus
}

void UpdateNode(address Data, infotype Key, infotype UpdateTo)
{
    address SearchResult = SearchNode(Data, Key);
    if (SearchResult != NULL)
    {
        Info(SearchResult) = UpdateTo;
    }
}

address SearchNode(address P, infotype X)
{
    if (P == NULL)
    {
        return NULL;
    }

    if (P->info == X)
    {
        return P;
    }

    address foundNode = SearchNode(FirstSon(P), X);
    if (foundNode != NULL)
    {
        return foundNode;
    }

    foundNode = SearchNode(NextBrother(P), X);
    if (foundNode != NULL)
    {
        return foundNode;
    }

    return NULL;
}

bool IsEmpty(address Data)
{
    if (Data->info != NULL)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Inorder(address P)
{
    address Son, Brother;
    if (P != NULL)
    {
        Son = LeftSon(P);
        Inorder(Son);
        printf("%c", Info(P));
        if (Son != NULL)
        {
            Brother = NextBrother(Son);
            while (Brother != NULL)
            {
                Inorder(Brother);
                Brother = NextBrother(Brother);
            }
        }
    }
}

void DeleteTree(address *P)
{
    address Son;

    if (*P != NULL)
    {
        Son = FirstSon(*P);
        while (Son != NULL)
        {
            PostOrder(Son);
            Son = NextBrother(Son);
        }
        free(*P);
    }
}

void PostOrder(address P)
{
    address Son;

    if (P != NULL)
    {
        Son = FirstSon(P);
        while (Son != NULL)
        {
            PostOrder(Son);
            Son = NextBrother(Son);
        }
        printf("%c", Info(P));
    }
}

void PreOrder(address P)
{
    address Son;
    if (P != NULL)
    {
        printf("%c", Info(P));
        Son = FirstSon(P);
        while (Son != NULL)
        {
            PreOrder(Son);
            Son = NextBrother(Son);
        }
    }
}

void PrintTree(address P, int Level)
{
    if (P != NULL)
    {
        int i = 1;
        for (i = 1; i <= Level; i++)
        {
            if (i < Level)
            {
                printf("|  ");
            }
            else
            {
                printf("|--");
            }
        }
        printf("%c\n", Info(P));
        PrintTree(LeftSon(P), Level + 1);
        PrintTree(NextBrother(P), Level);
    }
}

void ConvertTree(address NonBinary, address BinaryTarget)
{
    if (NonBinary != NULL)
    {
        BinaryTarget = Alokasi(Info(NonBinary));
        ConvertTree(FirstSon(BinaryTarget), LeftSon(NonBinary));
        if (LeftSon(BinaryTarget) != NULL)
        {
            Parent(LeftSon(BinaryTarget)) = BinaryTarget;
        }
        ConvertTree(NextBrother(BinaryTarget), RightSon(NonBinary));
        if (RightSon(BinaryTarget) != NULL)
        {
            Parent(RightSon(BinaryTarget)) = BinaryTarget;
        }
    }
}

void Balance(address Data)
{
    if (!IsEmpty(Data))
    {
        Data = BTtoDLL(Data);
        while (LeftSon(Data) != NULL)
        {
            Data = LeftSon(Data);
        }
        Data = Sort(Data);
        Data = DLLtoBT(Data);
    }
}

address BTtoDLL(address Data)
{
    address Left, Right;
    if (Data != NULL)
    {
        if (LeftSon(Data) != NULL)
        {
            Left = BTtoDLL(LeftSon(Data));
            while (RightSon(Left) != NULL)
            {
                Left = RightSon(Left);
            }
            RightSon(Left) = Data;
            LeftSon(Data) = Left;
        }
        if (RightSon(Data) != NULL)
        {
            Right = BTtoDLL(RightSon(Data));
            while (LeftSon(Right) != NULL)
            {
                Right = LeftSon(Right);
            }
            LeftSon(Right) = Data;
            RightSon(Data) = Right;
        }
    }
    return Data;
}

address Sort(address Data)
{
    address Middle, Temp;

    if (Data == NULL || RightSon(Data) == NULL)
    {
        return Data;
    }

    Middle = GetMid(Data);
    Temp = LeftSon(Middle);
    RightSon(Temp) = NULL;

    Data = Sort(Data);
    Middle = Sort(Middle);

    return Merge(Data, Middle);
}

address DLLtoBT(address Data)
{
    // Deklarasi variabel
    address Root;

    // Jika Data kosong, kembalikan NULL
    if (Data == NULL)
    {
        return NULL;
    }

    // Ambil elemen tengah dari Data
    Root = GetMid(Data);

    // Cek apakah ada sub-pohon kiri dari Root
    if (LeftSon(Root))
    {
        RightSon(LeftSon(Root)) = NULL;
        LeftSon(Root) = DLLtoBT(Data);
        if (LeftSon(Root) != NULL)
        {
            Parent(LeftSon(Root)) = Root;
        }
    }

    // Cek apakah ada sub-pohon kanan dari Root
    if (RightSon(Root))
    {
        LeftSon(RightSon(Root)) = NULL;
        RightSon(Root) = DLLtoBT(RightSon(Root));
        if (RightSon(Root) != NULL)
        {
            Parent(RightSon(Root)) = Root;
        }
    }

    // Kembalikan Root
    return Root;
}

address GetMid(address head)
{
    address slow = head;
    address fast = head;

    if (head)
    {
        while (fast && RightSon(fast))
        {
            slow = RightSon(slow);
            fast = RightSon(RightSon(fast));
        }

        return slow;
    }
}

address Merge(address firstList, address secondList)
{
    if (!firstList)
        return secondList;
    if (!secondList)
        return firstList;
    if (Info(firstList) < Info(secondList))
    {
        RightSon(firstList) = Merge(RightSon(firstList), secondList);
        LeftSon(RightSon(firstList)) = firstList;
        LeftSon(firstList) = NULL;
        return firstList;
    }
    else
    {
        RightSon(secondList) = Merge(firstList, RightSon(secondList));
        LeftSon(RightSon(secondList)) = secondList;
        LeftSon(secondList) = NULL;
        return secondList;
    }
}

void ScanChar(char *input)
{
    scanf("\n%c", input);
    while (getchar() != '\n')
        ;
}

void ScanInteger(int *input)
{
    if (scanf("%d", input) == 0) /*Apabila input yang diberikan bukan integer*/
    {
        (*input) = -99; /*input akan bernilai -99*/
    }
    while (getchar() != '\n')
        ; /*Pembersihan karakter yang tersisa sampai newline*/
}

// ================================================= Fungsi terpisah untuk merepresentasikan menu menu yang ada

void menuMembuatTreeSendiri(address *TreeNonBinary)
{
    int jmlNode;

    system("cls");

    printGridUI("INPUT DATA NON BINARY TREE");

    printHalfScreen("Masukan jumlah node pada tree : ", false, false);
    ScanInteger(&jmlNode);

    CreateTree(TreeNonBinary, true, jmlNode);
}

void menuAwal(address *TreeNonBinary)
{
    int tempPilihan;
    /* code */

    printGridUI("INITIALISASI DATA TREE");

    printf("\nTree Default:\n");
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

    gotoxy(0, 3);
    printHalfScreen("Pilih opsi tree yang akan digunakan", true, false);
    printHalfScreen("\t1. Tree Default", true, false);
    printHalfScreen("\t2. Make your own Tree", true, false);
    printHalfScreen(": ", true, false);

    ScanInteger(&tempPilihan);
    switch (tempPilihan)
    {
    case 1:
        InsertNode(TreeNonBinary, ' ', 'R'); // Parent
        InsertNode(TreeNonBinary, 'R', 'O');
        InsertNode(TreeNonBinary, 'R', 'U');
        InsertNode(TreeNonBinary, 'O', 'I');
        InsertNode(TreeNonBinary, 'I', 'M');
        InsertNode(TreeNonBinary, 'I', 'S');
        InsertNode(TreeNonBinary, 'I', 'F');
        InsertNode(TreeNonBinary, 'U', 'T');
        InsertNode(TreeNonBinary, 'U', 'N');
        InsertNode(TreeNonBinary, 'U', 'E');
        break;

    case 2:
        menuMembuatTreeSendiri(TreeNonBinary);
        break;
    }
}

void menuUtama(address *TreeNonBinary)
{
    address tempNode;
    int tempPilihan;
    char tempMasukanChar;

    while (true)
    {
        system("cls");

        printGridUI("MENU UTAMA");

        printf("Struktur Non Binary Tree:\n");
        PrintTree(*TreeNonBinary, 0);

        gotoxy(0, 2);
        printHalfScreen("Masukan Aksi:", true, false);
        printHalfScreen("\t1.Insert", true, false);
        printHalfScreen("\t2.Update", true, false);
        printHalfScreen("\t3.Delete", true, false);
        printHalfScreen("\t4.Search", true, false);
        printHalfScreen("\t5.Konversi ke binary", true, false);
        printHalfScreen("\t6.Keluar", true, false);
        printHalfScreen(": ", true, false);

        ScanInteger(&tempPilihan);
        system("cls");
        switch (tempPilihan)
        {
        case 1:

            printGridUI("INSERT NODE BARU");

            printf("Struktur Non Binary Tree:\n");
            PrintTree(*TreeNonBinary, 0);

            gotoxy(0, 3);
            printHalfScreen("Masukan jumlah node yang ingin ditambah : ", false, false);
            ScanInteger(&tempPilihan);

            CreateTree(TreeNonBinary, false, tempPilihan);
            break;

        case 2:
            printGridUI("UPDATE NODE");

            printf("Struktur Non Binary Tree:\n");
            PrintTree(*TreeNonBinary, 0);

            gotoxy(0, 3);
            printHalfScreen("Masukan node yang ingin diubah : ", false, false);
        StartOfUpdate:
            ScanChar(&tempMasukanChar);

            tempNode = SearchNode(*TreeNonBinary, tempMasukanChar);
            if (!tempNode)
            {
                printHalfScreen("Node tidak ditemukan, harap insert Node baru : ", false, true);
                goto StartOfUpdate;
            }
            printHalfScreen("Masukan karater baru untuk node tersebut: ", false, false);
            ScanChar(&tempMasukanChar);
            Info(tempNode) = tempMasukanChar;

            system("cls");

            printGridUI("HASIL UPDATE NODE");

            printf("Struktur Non Binary Tree:\n");
            PrintTree(*TreeNonBinary, 0);

            gotoxy(0, 2);

            printHalfScreen("Proses update berhasil, tekan ENTER untuk melanjutkan...", true, false);
            getch();

            break;

        case 3:
            printGridUI("DELETE NODE");

            printf("Struktur Non Binary Tree:\n");
            PrintTree(*TreeNonBinary, 0);

            gotoxy(0, 3);
            printHalfScreen("Masukan node yang ingin dihapus : ", false, false);
            ScanChar(&tempMasukanChar);

            DeleteNode(TreeNonBinary, tempMasukanChar);

            system("cls");

            printGridUI("HASIL DELETE NODE");

            printf("Struktur Non Binary Tree:\n");
            PrintTree(*TreeNonBinary, 0);

            gotoxy(0, 2);

            printHalfScreen("Proses delete berhasil, tekan ENTER untuk melanjutkan...", true, false);
            getch();
            break;

        case 4:
            printGridUI("SEARCH NODE");

            printf("Struktur Non Binary Tree:\n");
            PrintTree(*TreeNonBinary, 0);

            gotoxy(0, 3);
            printHalfScreen("Masukan node yang ingin dicari : ", false, false);
            ScanChar(&tempMasukanChar);

            tempNode = SearchNode(*TreeNonBinary, tempMasukanChar);

            if (tempNode)
            {
                printHalfScreen("Alamat digunakan :", true, false);
                printf(" %x\n", tempNode);
                printHalfScreen("Isi Node :", false, false);
                if (tempNode != NULL)
                {
                    printf(" %c\n", Info(tempNode));
                }
                else
                {
                    printf(" NULL\n");
                }
                printHalfScreen("Parent Node :", false, false);
                if (Parent(tempNode) != NULL)
                {
                    printf(" %c\n", Info(Parent(tempNode)));
                }
                else
                {
                    printf(" NULL\n");
                }
                printHalfScreen("Next Brother :", false, false);
                if (NextBrother(tempNode) != NULL)
                {
                    printf(" %c\n", Info(NextBrother(tempNode)));
                }
                else
                {
                    printf(" NULL\n");
                }
                printHalfScreen("First Son :", false, false);
                if (FirstSon(tempNode) != NULL)
                {
                    printf(" %c\n", Info(FirstSon(tempNode)));
                }
                else
                {
                    printf(" NULL\n");
                }
            }
            else
            {
                printHalfScreen("Node tidak ditemukan..\n", true, false);
            }

            printHalfScreen("tekan ENTER untuk melanjutkan...", true, false);
            getch();
            break;

        case 6:
            exit(0);
            break;
        }
    }
}

// ================================================= Fungsi terpisah untuk merepresentasikan menu menu yang ada

// ================================================= Fungsi tambahan yang hanya berguna untuk mempercantik tampilan, tidak berpengaruh pada alur proses
void csrs(void)
{
    COORD pos = {0, 1};
    SetConsoleCursorPosition(hConsole, pos);
}
void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(hConsole, c);
}

void initSystem()
{
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    WindowsSize.X = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    WindowsSize.Y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void printGridUI(char Pesan[])
{
    printCenterLine('|', 2);
    printc(Pesan);
    printLine('-');
}

COORD ReadResolution()
{
    COORD Result;

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    Result.X = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    Result.Y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    return Result;
}

void printc(char Pesan[])
{
    int usedPos = (WindowsSize.X - strlen(Pesan)) / 2;
    if (usedPos > 1)
    {
        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        COORD cursorPos = consoleInfo.dwCursorPosition;
        gotoxy(usedPos, cursorPos.Y + 1);
    }
    printf("%s\n", Pesan);
}

void printLine(char line)
{
    for (int i = 0; i < WindowsSize.X; i++)
    {
        printf("%c", line);
    }
    printf("\n");
}
void printCenterLine(char line, int StartPos)
{
    for (int i = StartPos; i < WindowsSize.Y - 1; i++)
    {
        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        COORD cursorPos = consoleInfo.dwCursorPosition;
        gotoxy((WindowsSize.X / 2) - 2, i);
        printf("%c", line);
    }
    gotoxy(0, 0);
}

void printHalfScreen(char Pesan[], bool isNewLine, bool cancelEnter)
{
    int usedPos = (WindowsSize.X) / 2;
    if (usedPos > 1)
    {
        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        int cursorPos = consoleInfo.dwCursorPosition.Y;
        if (isNewLine && !cancelEnter)
            cursorPos++;
        if (cancelEnter)
        {
            cursorPos--;
        }
        gotoxy(usedPos, cursorPos);
    }
    printf("%s", Pesan);
}
// ================================================= Fungsi tambahan yang hanya berguna untuk mempercantik tampilan, tidak berpengaruh pada alur proses