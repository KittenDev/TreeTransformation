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

void CreateTree(address *Data, int jmlNode)
{
    for (int i = 0; i < jmlNode; i++)
    {
        infotype inputInfo, inputParent;
        if (i == 0)
        {
            printf("Masukan karakter untuk root: ");
            ScanChar(&inputInfo);
            inputParent = ' ';
        }
        else
        {
            printf("\nMasukan karakter parent untuk node ke [%d]: ", i + 1);
            ScanChar(&inputParent);

            printf("Masukan karakter untuk node ke [%d]: ", i + 1);
            ScanChar(&inputInfo);
        }

        InsertNode(Data, inputParent, inputInfo);
    }
}

void InsertNode(address *Data, infotype Parent, infotype Input)
{
    address TempTraversal;

    if (!IsEmpty(*Data))
    {

        TempTraversal = SearchNode(*Data, Parent);
        // Menentukan apakah ia akan menjadi first son atau menjadi last son
        if (FirstSon(TempTraversal) == NULL)
        {
            FirstSon(TempTraversal) = Alokasi(Input);
        }
        else
        {
            TempTraversal = FirstSon(TempTraversal);
            while (NextBrother(TempTraversal) != NULL)
            {
                TempTraversal = NextBrother(TempTraversal);
            }
            NextBrother(TempTraversal) = Alokasi(Input);
        }
        // Menentukan apakah ia akan menjadi first son atau menjadi last son
    }
    else
    {
        *Data = Alokasi(Input);
    }
}

void DeleteNode(address Data, infotype Key)
{
    address SearchResult, ElemenPengganti, BrotherSebelum;
    SearchResult = SearchNode(Data, Key);
    if (SearchResult != NULL)
    {
        ElemenPengganti = FirstSon(SearchResult);
        if (ElemenPengganti != NULL)
        {
            Parent(ElemenPengganti) = Parent(SearchResult);
            NextBrother(ElemenPengganti) = NextBrother(SearchResult);

            if (FirstSon(Parent(SearchResult)) != SearchResult)
            {
                BrotherSebelum = FirstSon(Parent(SearchResult));
                while (NextBrother(BrotherSebelum) != NULL)
                {
                    BrotherSebelum = NextBrother(BrotherSebelum);
                }
                NextBrother(BrotherSebelum) = ElemenPengganti;
            }
            else
            {
                FirstSon(Parent(SearchResult)) = ElemenPengganti;
            }
        }
        free(SearchResult);
    }
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
    int columns = ReadResolution().X;
    if (((columns - strlen(Pesan)) / 2) > 1)
    {
        for (size_t i = 0; i < ((columns - strlen(Pesan)) / 2); i++)
        {
            printf(" ");
        }
    }
    // ^ Printf spasi sebanyak yang dibutuhkan teks agar memiliki posisi tengah

    printf("%s", Pesan);
    // ^ Print pesan yang ingin diletakan di tengah layar
}