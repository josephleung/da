#include <stdio.h>
#include <stdlib.h>
#include "3_39.h"

struct Node
{
    ElementType Element;
    PtrToNode Next;
};

int IsEmpty(Stack S)
{
    return S->Next == NULL;
}

Stack CreateStack(void)
{
    Stack S;

    S = malloc(sizeof(struct Node));
    if (S == NULL)
    {
        printf("Out of space!\n");
        return NULL;
    }
    S->Next = NULL;
    MakeEmpty(S);
    return S;
}

void MakeEmpty(Stack S)
{
    if (S == NULL)
        printf("Must use CreateStack first!\n");
    else
        while (!IsEmpty)
            Pop(S);
}

void Push(ElementType X, Stack S)
{
    PtrToNode TmpCell;

    TmpCell = malloc(sizeof(struct Node));
    if (TmpCell == NULL)
        printf("Out of space!\n");
    else
    {
        TmpCell->Element = X;
        TmpCell->Next = S->Next;
        S->Next = TmpCell;
        printf("%d pushed to stack.\n", X);
    }
}

ElementType Top(Stack S)
{
    if (!IsEmpty(S))
        return S->Next->Element;
    else
    {
        printf("Empty stack!\n");
        return 0;
    }
}

ElementType Pop(Stack S)
{
    PtrToNode FirstCell;
    ElementType TempVal;

    if (IsEmpty(S))
    {
        printf("Empty stack!\n");
        return 0;
    }
    else
    {
        FirstCell = S->Next;
        TempVal = FirstCell->Element;
        S->Next = S->Next->Next;
        free(FirstCell);
        printf("%d popped from stack\n", TempVal);
        return TempVal;
    }
}

int main(void)
{
    Stack Root = CreateStack();

    Push(12, Root);
    Push(1, Root);

    Pop(Root);
    Pop(Root);

    printf("Da!\n");
    return 0;
}