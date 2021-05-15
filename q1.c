#include <stdio.h>
#include <stdlib.h>

/*
this section contains the functions for linked list as infrastructure
*/
struct cardNode
{
    unsigned int data;
    struct cardNode *next;
};

struct cardNode* newCard(unsigned int data)
{
    struct cardNode *card = (struct cardNode*)malloc(sizeof(struct cardNode));
    if(card != NULL)  //only fill data after a successful malloc
    {
        card->data = data;
        card->next = NULL;
    }
    return card;
}

int isEmpty(struct cardNode *head)
{
    return !head;
}

int push(struct cardNode** head, int data)
{
    struct cardNode *card = newCard(data);
    if(card != NULL)
    {
        card->next = *head;
        *head = card;
    }
    else  //failed to allocate space for the node
    {
        return -1;
    }
    return 0;
}

int pop(struct cardNode** head)
{
    int popped;
    if(isEmpty(*head))
        return -1;
    struct cardNode *temp = *head;
    *head = temp->next;
    popped = temp->data;
    free(temp);
    return popped;
}

void dump(struct cardNode* head)
{
    printf("dump:   ");
    while(head)
    {
        printf("%d,", head->data);
        head = head->next;
    }
    printf("\n");
}

/*
this section contains the functions to simulate deal and combile
*/
unsigned int pileCount[3] = {3, 4, 5};

int main()
{
    int i = 0;
    struct cardNode* head = NULL;

    for(i = 0; i < 10; i++)
    {
        push(&head, i);
    }

    dump(head);

    for(i = 0; i < 10; i++)
    {
        printf("%d is popped\n", pop(&head));
    }

}