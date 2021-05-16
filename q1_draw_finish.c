#include <stdio.h>
#include <stdlib.h>
#define PRTDBG 1

/**
* this section contains 
* the params we can tune
*/
#define MAX_CARD_COUNT 2
#define MAX_PILES_PER_ROUND 5
unsigned int num_of_piles_per_round[3] = {3, 4, 5};

#define MAX_PILE_NUM_IDX (sizeof(num_of_piles_per_round) / sizeof(num_of_piles_per_round[0]) - 1)

/**
* this section contains 
* the functions for linked list as infrastructure
*/
struct card_node
{
    unsigned int data;
    struct card_node *next;
};

struct card_node *deck;
struct card_node *piles[MAX_PILES_PER_ROUND];

struct card_node *new_card(unsigned int data)
{
    struct card_node *card = (struct card_node *)malloc(sizeof(struct card_node));
    if (card != NULL) //only fill data after a successful malloc
    {
        card->data = data;
        card->next = NULL;
    }
    return card;
}

/**
 * is_empty() - tell whether if a list is empty
 * @head: head of the input list
 *
 * Return: 0 on success; -1 on failure.
 */
int is_empty(struct card_node *head)
{
    return !head;
}

/**
 * push() - push a node to list
 * @head: head of the input list
 *
 * Return: 0 on success; -1 on failure.
 */
int push(struct card_node **head, int data)
{
    struct card_node *card = new_card(data);
    if (card != NULL)
    {
        card->next = *head;
        *head = card;
    }
    else //failed to allocate space for the node
    {
        return -1;
    }
    return 0;
}

/**
 * pop() - pop a node from list
 * @head: head of the input list
 *
 * Return: data in popped node
 */
int pop(struct card_node **head)
{
    int popped;
    if (is_empty(*head))
        return -1;
    struct card_node *temp = *head;
    *head = temp->next;
    popped = temp->data;
    free(temp);
    return popped;
}

/**
 * dump() - print all nodes in the list, for debug use
 * @head: head of the input list
 *
 * Return: none
 */
void dump(struct card_node *head)
{
    while (head)
    {
        printf("%d,", head->data);
        head = head->next;
    }
    printf("\n");
}

/**
* this section contains 
* the functions to simulate deal and combile
*/

/**
 * deal() - simulate the deal action
 * 1. Deal all the cards facedown onto a table into Y piles like you would if you were playing with a group of people (i.e. card 1 to P1, card 2 to P2, ..., card Y to PY, card Y + 1 to P1, etc).
 * @deck: head of the input list of the deck
 * @num_of_piles: how many piles we have in this round
 *
 * Return: 0 on success; -1 on failure.
 */
int deal(struct card_node **deck, unsigned int num_of_piles)
{
    unsigned int pile_idx_to_put = 0;
    unsigned int card_data = 0;

    while (!is_empty(*deck))
    {
        card_data = pop(deck);
        if (card_data == -1)
        {
            printf("err ");
            return -1;
        }

        if (push(&piles[pile_idx_to_put], card_data) == -1)
        {
            printf("err ");
            return -1;
        }

#if PRTDBG
        printf("dump deck in deal#: ");
        dump(*deck);
        printf("dump pile %d#:", pile_idx_to_put);
        dump(piles[pile_idx_to_put]);
        printf("deck is_empty: %d\n", is_empty(*deck));
        printf("\n");
#endif
        pile_idx_to_put = (pile_idx_to_put + 1) % num_of_piles;
    }

        printf("deck is_empty before final: %d\n",     is_empty(*deck));
        printf("\n");

    return 0;
}

/**
 * deal() - simulate the deal action
 * 2. Combine all the piles into a deck by placing P1 onto P2, then P1+P2 onto P3, and so on. This is a round. 
 * @deck: head of the input list of the deck
 * @num_of_piles: how many piles we have in this round
 *
 * Return: 0 on success; -1 on failure.
 */
int combine(struct card_node *deck, unsigned int num_of_piles)
{
}

int main()
{
    int num_of_piles = 3;
    int i = 0;
    for (i = 1; i <= MAX_CARD_COUNT; i++)
    {
        push(&deck, i);
    }

    printf("dump deck: ");
    dump(deck);
    printf("\n");

    deal(&deck, num_of_piles);

/*
    for (i = 0; i < num_of_piles; i++)
    {
        printf("dump pile#: %d: ", i);
        dump(piles[i]);
    }
    printf("\n");
*/

    printf("deck is_empty in main: %d\n",     is_empty(deck));
    printf("dump deck again: ");
    dump(deck);
    /*
    for (i = 0; i < 10; i++)
    {
        push(&head, i);
    }

    dump(head);

    for (i = 0; i < 10; i++)
    {
        printf("%d is popped\n", pop(&head));
    }
    */
}