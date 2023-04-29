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

void InsertNode(address Data, infotype Parent, infotype Input)
{
    StructTree TempTraversal;

    if (!IsEmpty(Data))
    {
        TempTraversal = FirstSon(SearchNode(Data, Parent));
        while (NextBrother(TempTraversal) != NULL)
        {
            TempTraversal = NextBrother(TempTraversal);
        }
        NextBrother(TempTraversal) = Alokasi(Input);
    }
    else
    {
        Data = Alokasi(Input);
    }
}

void DeleteNode(address Data, infotype Key)
{
    StructTree SearchResult, ElemenPengganti, BrotherSebelum;
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
    StructTree SearchResult = SearchNode(Data, Key);
    if (SearchResult != NULL)
    {
        Info(SearchResult) = UpdateTo;
    }
}

address SearchNode(StructTree P, infotype X)
{
    StructTree Son;
    if (P != NULL)
    {
        if (Info(P) != X)
        {
            printf("%c\n", Info(P));
            Son = FirstSon(P);
            while (Son != NULL)
            {
                SearchNode(Son, X);
                Son = NextBrother(Son);
            }
        }
        else
        {
            return P;
        }
    }
    return NULL;
}

bool IsEmpty(address Data)
{
    if (FirstSon(Data) != NULL)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Inorder(StructTree P)
{
    StructTree Son, Brother;
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

void PostOrder(StructTree P)
{
    StructTree Son;

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

void PreOrder(StructTree P)
{
    StructTree Son;
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

void PrintTree(StructTree P, int Level)
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