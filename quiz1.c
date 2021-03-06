#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

node_t *rev_recursive(node_t **indirect, node_t **head) {
  if (!(*indirect)->next->next) {
    *head = (*indirect)->next;
    return (*head);
  } else {
    node_t **new_indirect = &(*indirect)->next;
    node_t *tmp = rev_recursive(new_indirect, head);
    tmp->next = (*new_indirect);
    return (tmp->next);
  }
}

void reverse(node_t **head) {
  node_t **indirect = head;
  node_t *tail = *head;
  node_t *tmp = rev_recursive(indirect, head);
  tmp->next = tail;
  tail->next = NULL;
}


void print_list(node_t *head)
{
    for (node_t *current = head; current; current = current->next)
        printf("%d ", current->value);
    printf("\n");
}

node_t *pick_entry(node_t **head, node_t *entry) {
  node_t **indirect = head;

  while ((*indirect) != entry)
    indirect = &(*indirect)->next;

  *indirect = entry->next;
  entry->next = NULL;
  return entry;
}

void add_entry_(node_t **head, node_t *entry) {
  node_t **indirect = head;

  while (*indirect)
    indirect = &(*indirect)->next;

  *indirect = entry;
}

void FisherYates_shuffle(node_t **head) {
  /* Get length of linked list */
  int len = 0;
  for (node_t **indirect = head; (*indirect); indirect = &(*indirect)->next)
    len++;
  if (len == 1)
    return;

  node_t *new_head = NULL;
  srand(time(NULL));
  for (; len > 0; len--) {
    /* Roll */
    int roll = (rand() % len) + 1;

    /* Strike-out */
    node_t **strike_out = head;
    for (; roll > 1; roll--, strike_out = &(*strike_out)->next)
      /* iterate */;

    add_entry_(&new_head, pick_entry(head, *strike_out));
  }

  *head = new_head;
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
    add_entry(&head, 23);
    add_entry(&head, 156);
    add_entry(&head, 734);

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

    printf("Before shuffle : ");
    print_list(head);
    FisherYates_shuffle(&head);
    printf("after shuffle : ");
    print_list(head);
    return 0;
}
