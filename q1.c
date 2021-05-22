#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DBGPRT_LVL 1 //0 = no debug print. 1 = deck print only, 2 = 1 + pile print each time

/**
 * this section contains 
 * the params we can tune
*/
#define MAX_CARD_COUNT 20 //max allowed card count for our test
#define MAX_PILES_PER_ROUND 5
unsigned int num_of_piles_per_round[3] = {3, 4, 5};

#define MAX_PILE_NUM_IDX (sizeof(num_of_piles_per_round) / sizeof(num_of_piles_per_round[0]) - 1)

/**
 * this section contains 
 * the functions for linked list as infrastructure
 * since array is not allowed so linked list is a good choice
 * and the card deal combine process is a kind of stack: we put new card on top of old card, so we use stack
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
 * Return: 1 empty, 0 not empty
 */
int is_empty(struct card_node *head)
{
    return !head;
}

/**
 * is_in_order() - tell whether if a list is in original order
 * @head: head of the input list - deck
 *
 * Return: 0 not in order; 1 in order.
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
 * Return: data in popped node, -1 if fail
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
 * dump() - print all nodes in the list
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

#if DBGPRT_LVL == 2
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

/**
 * calc_entrophy_index() - calculate the entrophy index of the deck - randomness of the deck
 * the algorithm just compare each pair of data from head to tail and see the probability in each pair that the first data is larger than the second data
 * if the deck is random enough, we should see a number of 50%
 * in other words, more random a deck, the return value is closer to 50%
 * @head: head of the input list of the deck
 *
 * Return: entrophy index as float, closer to 50% the better
 */
float calc_entrophy_index(struct card_node *head)
{
    float entropy_index = 0;
    unsigned int total_num = 0;
    unsigned int first_is_larger_num = 0;

    while (head && head->next)
    {
        if (head->data > head->next->data)
            first_is_larger_num++;
        head = head->next;
        total_num++;
    }
    entropy_index = (float)first_is_larger_num / total_num;

#if DBGPRT_LVL == 1
    printf("first_is_larger_num: %d, total_num: %d, index:%f\n", first_is_larger_num, total_num, entropy_index);
#endif

    return entropy_index;
}

int main(int argc, char *argv[])
{
    unsigned int i = 0;
    unsigned int round_num = 0;
    unsigned int num_of_piles = 0;
    unsigned int card_num = atoi(argv[1]);
    float current_entropy_index = 1;            //this is used for bonus part, it records the "randomness" of the deck.
    float best_entrophy_index = 1;              //we set it to 1 which is the worse index we can get, it means not random at all
    unsigned int best_entrophy_index_round = 0; //record the round info of the best entrophy index

    if (card_num <= 0)
    {
        printf("invalid input. Please input a number in range of 1~%d\n", MAX_CARD_COUNT);
        return -1;
    }
    else if (card_num > MAX_CARD_COUNT)
    {
        printf("invalid input. \ninput card number = %d,  exceeds max allowed = %d \n", card_num, MAX_CARD_COUNT);
        return -1;
    }

    //create our initial deck, card number is decending
    for (i = 1; i <= card_num; i++)
    {
        push(&deck, i);
    }

#if DBGPRT_LVL >= 1
    printf("dump initial deck: ");
    dump(deck);
    printf("\n");
#endif

    do
    {
        num_of_piles = num_of_piles_per_round[round_num % (sizeof(num_of_piles_per_round) / sizeof(num_of_piles_per_round[0]))];

        //the deal action
        deal(&deck, num_of_piles);
#if DBGPRT_LVL == 2
        for (i = 0; i < num_of_piles; i++)
        {
            printf("after a deal, dump pile#: %d: ", i);
            dump(piles[i]);
        }
        printf("\n");
#endif

        //the combine action
        combine(&deck, num_of_piles);
#if DBGPRT_LVL == 2
        for (i = 0; i < num_of_piles; i++)
        {
            printf("after a combine, dump pile#: %d: ", i);
            dump(piles[i]);
        }
        printf("\n");
#endif
#if DBGPRT_LVL >= 1
        //printf("deck is_empty in main: %d\n", is_empty(deck));
        printf("dump deck for round %2d:   ", round_num + 1);
        dump(deck);
#endif

        //this part calculate the entrophy index which helps to answer the bonus question
        current_entropy_index = calc_entrophy_index(deck); //calculate our bonus part entrophy index
        if (fabs(current_entropy_index - 0.5) < fabs(best_entrophy_index - 0.5))
        {
            best_entrophy_index = current_entropy_index;
            best_entrophy_index_round = round_num + 1;
            printf("index: %f, best: %f", fabs(current_entropy_index - 0.5), best_entrophy_index);
            printf(" updated index \n\n");
        }

        round_num++;
    } while (!is_in_order(deck));

    printf("\nIt takes %d rounds to put deck back in original order. \n", round_num);
    printf("First most shuffled deck from round: %d \n", best_entrophy_index_round);
}

/**
 * bonus question comment: please see comment of function
 * float calc_entrophy_index(struct card_node *head)
 * I don't know what kind of casual card game our friend want to play.
 * But I guess a good start is tell whether if the entrophy is good enough.
 * The way I do it is:
 * the algorithm just compare each pair of data from head to tail and see the probability in each pair that the first data is larger than the second data
 * if the deck is random enough, we should see a number of 50%
 * in other words, more random a deck, the return value is closer to 50%
*/