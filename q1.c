#include <stdio.h>
#include <stdlib.h>
#define DBGPRT 0

/**
* this section contains 
* the params we can tune
*/
#define MAX_CARD_COUNT 5
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
 * is_in_order() - tell whether if a list is empty
 * @head: head of the input list - deck
 *
 * Return: 0 not in order; -1 on failure.
 */
int is_in_order(struct card_node *head)
{
    int current_data;
    int prev_data;

    if (head == NULL || head->next == NULL) //if we don't have node or only one node, return true
        return 1;

    prev_data = head->data + 1;

    while (head)
    {
        current_data = head->data;
        if (current_data == (prev_data - 1))
        {
            head = head->next;
            prev_data = current_data;
        }
        else
            return 0;
    }
    return 1;
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
 * reverse() - reverse nodes from list
 * @head: head of the input list
 *
 * Return: none
 */
void reverse(struct card_node **head)
{
    struct card_node *current, *prev, *next;
    current = *head;
    prev = NULL;
    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
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
            printf("err poping");
            return -1;
        }

        if (push(&piles[pile_idx_to_put], card_data) == -1)
        {
            printf("err pushing");
            return -1;
        }

#if DBGPRT
        printf("dump deck during deal: ");
        dump(*deck);
        printf("dump pile #%d: ", pile_idx_to_put);
        dump(piles[pile_idx_to_put]);
        printf("deck is_empty: %d\n", is_empty(*deck));
        printf("\n");
#endif
        pile_idx_to_put = (pile_idx_to_put + 1) % num_of_piles;
    }
    return 0;
}

/**
 * combine() - simulate the deal action
 * 2. Combine all the piles into a deck by placing P1 onto P2, then P1+P2 onto P3, and so on. This is a round. 
 * @deck: head of the input list of the deck
 * @num_of_piles: how many piles we have in this round
 *
 * Return: 0 on success; -1 on failure.
 */
int combine(struct card_node **deck, unsigned int num_of_piles)
{
    unsigned int card_data = 0;
    struct card_node *temp_node;
    int i;

    for (i = 0; i < num_of_piles; i++)
    {
        while (!is_empty(piles[i]))
        {
            card_data = pop(&piles[i]);
            push(deck, card_data);
        }
    }
    reverse(deck);
}

int main()
{
    unsigned int round_num = 0;
    int num_of_piles = 3;
    int i = 0;

    //create our initial deck, card number is decending
    for (i = 1; i <= MAX_CARD_COUNT; i++)
    {
        push(&deck, i);
    }

#if DBGPRT
    printf("dump initial deck: ");
    dump(deck);
    printf("\n");
#endif

#if 0
    printf("is_in_order: %d\n", is_in_order(deck));
    push(&deck, 9);
    dump(deck);
    printf("\n");
    printf("is_in_order: %d\n", is_in_order(deck));
#endif

    do
    {
        deal(&deck, num_of_piles);
#if DBGPRT
        for (i = 0; i < num_of_piles; i++)
        {
            printf("dump pile#: %d: ", i);
            dump(piles[i]);
        }
        printf("\n");

        printf("deck is_empty in main: %d\n", is_empty(deck));
        printf("dump deck again: ");
        dump(deck);
#endif

        combine(&deck, num_of_piles);
#if DBGPRT
        for (i = 0; i < num_of_piles; i++)
        {
            printf("dump pile#: %d: ", i);
            dump(piles[i]);
        }
        printf("\n");

        printf("deck is_empty in main: %d\n", is_empty(deck));
        printf("dump deck again: ");
        dump(deck);
#endif
        round_num++;
    } while (!is_in_order(deck));

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
   printf("%d rounds\n", round_num);
}