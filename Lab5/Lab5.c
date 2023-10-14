﻿// Lab5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct Node* pNode;
typedef void(*pFunction)(pNode);
typedef char Item;
struct Node { pNode Left; pNode Right; Item  Data; int Size; };
//---------------------Create Node----------------------------------------
pNode NewNode(Item D)
{
    pNode  pN = malloc(sizeof(struct Node));
    pN->Left = 0;
    pN->Right = 0;
    pN->Data = D;
    pN->Size = 0;
    return pN;
}

//---------------------Direct bypass-----------------------------------------
void VisitPre(pNode root, pFunction Function)
{
    if (root)
    {
        Function(root);
        VisitPre(root->Left, Function);
        VisitPre(root->Right, Function);
    }
}

void VisitSim(pNode root, pFunction Function) {
    if (!root) return;

    VisitSim(root->Left, Function);
    Function(root);
    VisitSim(root->Right, Function);
}

int GetSize(pNode root)
{
    if (!root)return 0;
    return root->Size;
}
void FixSize(pNode root) {
    root->Size = GetSize(root->Left) + GetSize(root->Right) + 1;
}
void PrintPoly(pNode root) {
    if (!root) {
        printf("_");
        return;
    }

    printf("(%c", root->Data);
    printf(" ");
    PrintPoly(root->Left);
    printf(" ");
    PrintPoly(root->Right);
    printf(") ");
}
void Print(pNode root) {
    if (!root) return;
    printf("%d ", root->Data);
}
//---------------------�������� �����---------------------------------------
void VisitPost(pNode root, pFunction Function)
{
    if (root)
    {
        VisitPost(root->Left, Function);
        VisitPost(root->Right, Function);
        Function(root);
    }
}
//---------------------������� ����-----------------------------------------
void Insert(pNode* proot, Item D)
{
#define root (*proot)
    if (!root)
        root = NewNode(D);
    else
        if (D < root->Data)
            Insert(&(root->Left), D);
        else
            Insert(&(root->Right), D);
#undef root
}
//---------------------����� ����-------------------------------------------
pNode Find(pNode root, pNode* parent, int* LR, Item D)
{
    *parent = 0;
    *LR = 0;
    while (root)
        if (D < root->Data)
        {
            *parent = root;
            *LR = 0;
            root = root->Left;
        }
        else
            if (D > root->Data)
            {
                *parent = root;
                *LR = 1;
                root = root->Right;
            }
            else
                return root;
    return 0;
}
//---------------------����� ������� ������������---------------------------
pNode FindMinRight(pNode root, pNode* parent)
{
    while (root->Left)
    {
        *parent = root;
        root = root->Left;
    }
    return root;
}
//---------------------�������� ������ ����---------------------------------
void Delete(pNode root)
{
    if (root) free(root);
}
//---------------------�������� ���� � �������� ������----------------------
void DeleteNode(pNode* ROOT, Item D)
{
    int LR = 0;
    pNode parent = 0, root = Find(*ROOT, &parent, &LR, D);
    if (root)
    {
        if (root->Left && root->Right)
        {
            pNode MinRightParent = root;
            pNode MinRight = FindMinRight(root->Right, &MinRightParent);
            MinRight->Left = root->Left;
            MinRightParent->Left = MinRight->Right;
            MinRight->Right = root->Right;
            if (parent)
                if (LR) parent->Right = MinRight;
                else    parent->Left = MinRight;
            else
                *ROOT = MinRight;
        }
        else
            if (parent)
                if (LR) parent->Right = root->Right ? root->Right : root->Left;
                else    parent->Left = root->Right ? root->Right : root->Left;
            else
                *ROOT = root->Right ? root->Right : root->Left;
        Delete(root);
    }
}
int Height(pNode root) {
    return (root == NULL) ? 0 : 1 + max(Height(root->Left), Height(root->Right));
}
//---------------------------������� ������---------------------------------
void RotateRight(pNode* pLev0)
{
#define Lev0 (*pLev0)
    pNode Lev1 = Lev0->Left;
    Lev0->Left = Lev1->Right;
    Lev1->Right = Lev0;
    Lev0 = Lev1;
#undef Lev0
}
//---------------------------������� �����----------------------------------
void RotateLeft(pNode* pLev0)
{
#define Lev0 (*pLev0)
    pNode Lev1 = Lev0->Right;
    Lev0->Right = Lev1->Left;
    Lev1->Left = Lev0;
    Lev0 = Lev1;
#undef Lev0
}
//-------------------------������� � ������---------------------------------
void InsertRoot(pNode* proot, Item D)
{
#define root (*proot)
    if (!root)
        root = NewNode(D);
    else
        if (D < root->Data)
        {
            InsertRoot(&(root->Left), D);
            RotateRight(&(root));
        }
        else
        {
            InsertRoot(&(root->Right), D);
            RotateLeft(&(root));
        }
#undef root
}
void InsertRandom(pNode* proot, Item D) {
#define root (*proot)
    if (!root)
        root = NewNode(D);
    else if (rand() % (root->Size + 1) == 0)
        InsertRoot(proot, D);
    else if (D < root->Data)
        Insert(&(root->Left), D);
    else
        Insert(&(root->Right), D);

    FixSize(root);
#undef root
}
void TestTrees() {
    pNode bTreeRoot = NewNode(4);

    Insert(&bTreeRoot, 6);
    Insert(&bTreeRoot, 3);
    Insert(&bTreeRoot, 5);
    Insert(&bTreeRoot, 2);
    Insert(&bTreeRoot, 7);
    Insert(&bTreeRoot, 9);
    Insert(&bTreeRoot, 10);
    printf("%s", "Прямой обход\n");
    VisitPre(bTreeRoot, Print);
    printf("\n");
    printf("%s", "Обратный обход\n");
    VisitSim(bTreeRoot, Print);
    printf("\n");
    printf("%s", "Центрированный обход\n");

    VisitPost(bTreeRoot, Print);
    printf("\n");

    PrintPoly(bTreeRoot);
    printf("\n");

    printf("%d %d\n", GetSize(bTreeRoot), Height(bTreeRoot));

    //////////////////////////

    bTreeRoot = NewNode(4);

    InsertRandom(&bTreeRoot, 6);
    InsertRandom(&bTreeRoot, 3);
    InsertRandom(&bTreeRoot, 5);
    InsertRandom(&bTreeRoot, 2);
    InsertRandom(&bTreeRoot, 7);
    InsertRandom(&bTreeRoot, 9);
    InsertRandom(&bTreeRoot, 10);

    VisitPre(bTreeRoot, Print);
    printf("\n");
    VisitSim(bTreeRoot, Print);
    printf("\n");
    VisitPost(bTreeRoot, Print);
    printf("\n");

    PrintPoly(bTreeRoot);
    printf("\n");

    printf("%d %d", GetSize(bTreeRoot), Height(bTreeRoot));
}

int countVowels(pNode root) {
    if (root == NULL) 
        return 0;
    else if (root->Left == NULL && root->Right == NULL) {
        char vowelsChars[] = { 'а','о','у','э','ы','я','ё','е','ю','и' };
        int n = sizeof(vowelsChars) / sizeof(vowelsChars[0]);
        for (int i = 0; i < n; i++)
            if (root->Data == vowelsChars[i])
                return 1;
        return 0;
    }
    else 
        return countVowels(root->Left) + countVowels(root->Right);
}
int main()
{
    system("chcp 1251 > null");
    //TestTrees();
    pNode bTreeRoot = NewNode('б');

    Insert(&bTreeRoot, 'а');
    Insert(&bTreeRoot, 'с');
    Insert(&bTreeRoot, 'е');
    Insert(&bTreeRoot, 'д');
    Insert(&bTreeRoot, 'у');



    PrintPoly(bTreeRoot);
    printf("%d", countVowels(bTreeRoot));


}
