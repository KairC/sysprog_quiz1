#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct __node {
    int value;
    struct __node *next;
} node_t;

void add_entry(node_t **head, int new_value)
{
    node_t **indirect = head;

    node_t *new_node = malloc(sizeof(node_t));
    new_node->value = new_value;
    new_node->next = NULL;

    // AA1;
    assert(new_node);
    while (*indirect)
        indirect = &(*indirect)->next;
    // AA2;
    *indirect = new_node;
}

node_t *find_entry(node_t *head, int value)
{
    node_t *current = head;
    for (; current && current->value != value; current = current->next)
      /* iterate */;
    return current;
}

void remove_entry(node_t **head, node_t *entry)
{
    node_t **indirect = head;

    while ((*indirect) != entry)
        indirect = &(*indirect)->next;

    *indirect = entry->next;
    free(entry);
}

void swap_pair(node_t **head) {
  for (node_t **node = head; *node && (*node)->next;
       /*BB1*/ node = &(*node)->next->next) {
    node_t *tmp = *node;
    // BB2;
    *node = (*node)->next;
    tmp->next = (*node)->next;
    (*node)->next = tmp;
  }
}

void reverse(node_t **head) {
  node_t *cursor = NULL;
  node_t **head_ptr = head;
  while (*head_ptr) {
    node_t *next = (*head_ptr)->next;
    // CCC;
    (*head_ptr)->next = cursor;
    cursor = *head_ptr;
    *head_ptr = next;
  }
  *head_ptr = cursor;
}

void print_list(node_t *head)
{
    for (node_t *current = head; current; current = current->next)
        printf("%d ", current->value);
    printf("\n");
}

int main(int argc, char const *argv[])
{
    node_t *head = NULL;

    print_list(head);

    add_entry(&head, 72);
    add_entry(&head, 101);
    add_entry(&head, 108);
    add_entry(&head, 109);
    add_entry(&head, 110);
    add_entry(&head, 111);

    print_list(head);

    node_t *entry = find_entry(head, 101);
    remove_entry(&head, entry);

    entry = find_entry(head, 111);
    remove_entry(&head, entry);

    print_list(head);

    /* swap pair.
     * See https://leetcode.com/problems/swap-nodes-in-pairs/
     */
    swap_pair(&head);
    print_list(head);

    reverse(&head);
    print_list(head);

    return 0;
}
