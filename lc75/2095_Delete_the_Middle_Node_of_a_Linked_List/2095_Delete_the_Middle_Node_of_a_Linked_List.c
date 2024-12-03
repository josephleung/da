#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

struct ListNode
{
    int val;
    struct ListNode *next;
};

#if 0
struct ListNode *deleteMiddle(struct ListNode *head)
{
    struct ListNode *slow_pointer = head;
    struct ListNode *fast_pointer = head;
    struct ListNode *prev = NULL;

    if (head == NULL || head->next == NULL)
        return NULL;

    while (fast_pointer != NULL && fast_pointer->next != NULL)
    {
        prev = slow_pointer;
        slow_pointer = slow_pointer->next;
        fast_pointer = fast_pointer->next->next;
    }
    prev->next = slow_pointer->next;

    return head;
}

#else
struct ListNode *deleteMiddle(struct ListNode *head)
{
    struct ListNode *prev = NULL, *current = head;
    int count = 0;

    if (head == NULL || head->next == NULL)
        return NULL;

    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    current = head;
    for (int i = 0; i < count / 2; i++)
    {
        prev = current;
        current = current->next;
    }

    prev->next = current->next;

    return head;
}
#endif

void printList(struct ListNode *head)
{
    struct ListNode *temp = head;
    while (temp != NULL)
    {
        printf("%d -> ", temp->val);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main()
{
    struct ListNode *head = (struct ListNode *)malloc(sizeof(struct ListNode));
    struct ListNode *second = (struct ListNode *)malloc(sizeof(struct ListNode));
    struct ListNode *third = (struct ListNode *)malloc(sizeof(struct ListNode));
    struct ListNode *fourth = (struct ListNode *)malloc(sizeof(struct ListNode));
    struct ListNode *fifth = (struct ListNode *)malloc(sizeof(struct ListNode));
    struct ListNode *sixth = (struct ListNode *)malloc(sizeof(struct ListNode));

    head->val = 1;
    head->next = second;

    second->val = 2;
    second->next = third;

    third->val = 3;
    third->next = fourth;

    fourth->val = 4;
    fourth->next = fifth;

    fifth->val = 5;
    fifth->next = sixth;

    sixth->val = 6;
    sixth->next = NULL;

    printf("Original List: ");
    printList(head);

    head = deleteMiddle(head);

    printf("List after deleting the middle node: ");
    printList(head);
}