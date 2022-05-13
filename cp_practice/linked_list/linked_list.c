#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} node_t;

/*   add a node at the front   */
void push(node_t **head_ref, int new_data)
{
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

/*   add a node after a given node   */
void insertAfter(node_t *prev_node, int new_data)
{
    if (prev_node == NULL)
        return;
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node->data = new_data;
    new_node->next = prev_node->next;
    prev_node->next = new_node;
}

/*   add a node at the end   */
void append(node_t **head_ref, int new_data)
{
    node_t *last = *head_ref;
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node->data = new_data;
    new_node->next = NULL;

    if (*head_ref == NULL)
    {
        *head_ref = new_node;
        return;
    }

    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
    return;
}

void printMiddle(struct Node *head)
{
    struct Node *slow_prt = head;
    struct Node *fast_prt = head;

    printf("\nCalled function is: %s\n", __func__);

    if (head != NULL)
    {
        while (fast_prt != NULL && fast_prt->next != NULL)
        {
            fast_prt = fast_prt->next->next;
            slow_prt = slow_prt->next;
        }
        printf("The middle element is %d.\n", slow_prt->data);
    }
}

void printMiddle1(struct Node *head)
{
    printf("\nCalled function is: %s\n", __func__);
    struct Node *temp = head;
    int size = 0, mid, i = 0;
    printf("head: %d\n", head->data);
    while (temp != NULL)
    {
        if (temp != NULL)
        {
            printf("element: %d, ", temp->data);
        }
        temp = temp->next;
        size++;
    }
    printf("size: %d\n", size);

    mid = size / 2;
    temp = head;
    while (i < mid)
    {
        temp = temp->next;
        i++;
    }
    printf("middle1: %d\n", temp->data);
}

void printList(struct Node *n)
{
    printf("\nCalled function is: %s\n", __func__);
    while (n != NULL)
    {
        printf(" %d ", n->data);
        n = n->next;
    }
}

struct Node* reverseList(struct Node* head)
{
	struct Node *current, *prev, *next;
	current = head;
	prev = NULL;
	while(current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	head = prev;
	return head;
}

int main()
{
    int i = 0;

    node_t *my_list = NULL;

    append(&my_list, 1);
    append(&my_list, 11);
    push(&my_list, 2);
    push(&my_list, 22);
    push(&my_list, 222);

    node_t *prt = my_list;
    while (prt != NULL)
    {
        printf("%d item: %d\n", i, prt->data);
        prt = prt->next;
        i++;
    }

    printList(my_list);

    printMiddle(my_list);

    printMiddle1(my_list);

    my_list = reverseList(my_list);
    printList(my_list);
    return 0;
}
