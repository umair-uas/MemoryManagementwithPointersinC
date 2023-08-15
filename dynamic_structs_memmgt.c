#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  char* data;
  struct Node* next;

} Node;

Node* createNode(char* data) {
  Node* newNode = malloc(sizeof(Node));
  if (newNode == NULL) {
    perror("Memory allocation for node failed\n");
    exit(EXIT_FAILURE);
  }
  newNode->data = data;
  newNode->next = NULL;
  return newNode;
}

void insertNodeatFront(Node** head, char* data) {
  Node* newNode = createNode(data);
  newNode->next = *head;
  *head = newNode;
}

void insertNodeatBack(Node** head, char* data) {
  Node* newNode = createNode(data);
  if (*head == NULL) {
    *head = newNode;  // if the list is empty newNode becomes head
    return;
  }

  Node* current = *head;
  while (current->next != NULL) {
    current = current->next;
  }
  current->next = newNode;
}

void insertAfter(Node* prevNode, char* data) {
  if (prevNode == NULL) {
    fprintf(stderr, "Prevous node cannot be NULL. \n");
    return;
  }
  Node* newNode = createNode(data);
  newNode->next = prevNode->next;
  prevNode->next = newNode;
}

void removefromFront(Node** head) {
  if (*head == NULL) {
    return;  // empty list;
  }
  Node* temp = *head;
  *head = (*head)->next;
  free(temp);
}

void removefromBack(Node** head) {
  if (*head == NULL) {
    return;
  }
  if ((*head)->next == NULL) {
    free(*head);  // only one node,free it
    *head = NULL;
    return;
  }
  Node* current = *head;
  while (current->next->next != NULL) {
    current = current->next;
  }
  free(current->next);
  current->next = NULL;
}

void removebyValue(Node** head, char* value) {
  if (*head == NULL) {
    return;
  }
  if (strcmp((*head)->data, value) == 0) {
    Node* temp = *head;
    *head = (*head)->next;
    free(temp);
    return;
  }
  Node* current = *head;
  Node* previous = NULL;

  while (current != NULL && strcmp(current->data, value) != 0) {
    previous = current;
    current = current->next;
  }

  if (current == NULL) {
    return;  // value not found in the list
  }
  previous->next = current->next;
  free(current);
}

Node* search(Node** head, const char* value) {
  Node* current = *head;
  while (current != NULL) {
    printf("Checking node with data: %s\n", current->data);
    if (strcmp(current->data, value) == 0) {
      printf("Found node with data: %s\n", current->data);
      return current;
    }
    current = current->next;
  }
  printf("Value '%s' not found in the list\n", value);
  return NULL;
}

int countNodes(Node* head) {
  int count = 0;
  Node* current = head;
  while (current != NULL) {
    count++;
    current = current->next;
  }
  return count;
}

Node* getNthNode(Node* head, int n) {
  if (head == NULL || n < 0) {
    return NULL;
  }
  Node* current = head;
  for (int i = 0; i < n && current != NULL; i++) {
    current = current->next;
  }
  return current;
}

void reverseList(Node** head) {
  Node* prev = NULL;      // Initialize a pointer to track previous node
  Node* current = *head;  // start at the current head of the list
  Node* next;

  while (current != NULL) {
    next = current->next;  // store the next node temporarily
    current->next =
        prev;  // update the next pointer of current node to point to prev node
    prev = current;  // move the prev pointer one step forward
    current = next;  // move the current pointer one step forward
  }
  *head = prev;  // update the head of the list to the last node (new start of
                 // reversed list)
}
void printList(Node* nodeptr) {
  Node* current = nodeptr;
  while (current != NULL) {
    printf("%s -> ", current->data);
    current = current->next;
  }
  printf("NULL\n");
}

void destroyList(Node* nodeptr) {
  while (nodeptr != NULL) {
    Node* tmp = nodeptr;
    nodeptr = nodeptr->next;
    free(tmp);
  }
}
int main() {
  Node* nodeptr = createNode("AA");
  printList(nodeptr);
  insertNodeatFront(&nodeptr, "BB");
  insertNodeatBack(&nodeptr, "CC");
  printList(nodeptr);
  removefromFront(&nodeptr);
  printf("Total nodes in list: %d\n", countNodes(nodeptr));
  printList(nodeptr);
  Node* found = search(&nodeptr, "AA");
  printList(nodeptr);

  if (found) {
    insertAfter(found, "FAa");
  }

  Node* node_at_index2 = getNthNode(nodeptr, 2);
  if (node_at_index2 != NULL) {
    printf("Node at index 2: %s\n", node_at_index2->data);
  } else {
    printf("Node at index 2 not found");
  }
  printList(nodeptr);
  reverseList(&nodeptr);
  printf("Reversed list: \n");
  printList(nodeptr);
  removebyValue(&nodeptr, "FAa");
  printList(nodeptr);
  destroyList(nodeptr);
  return 0;
}