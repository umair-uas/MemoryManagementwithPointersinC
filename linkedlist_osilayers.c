#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  LAYER_PHYSICAL = 1,
  LAYER_DATALINK,
  LAYER_NETWORK,
  LAYER_TRANSPORT,
  LAYER_SESSION,
  LAYER_PRESENTATION,
  LAYER_APPLICATION
} OSILayer_Type;

const char* osi_layer_names[] = {
    [LAYER_PHYSICAL] = "Physical",      [LAYER_DATALINK] = "Data Link Layer",
    [LAYER_NETWORK] = "Network",        [LAYER_TRANSPORT] = "Transport",
    [LAYER_SESSION] = "Session",        [LAYER_PRESENTATION] = "Presentation",
    [LAYER_APPLICATION] = "Application"};

typedef struct OsiLayer {
  OSILayer_Type layer_type;
  const char* description;
} OsiLayer;

OsiLayer osi_layer_info[] = {
    [LAYER_PHYSICAL] =
        {LAYER_PHYSICAL,
         "Converts physical data for transmission over the medium."},
    [LAYER_DATALINK] =
        {LAYER_DATALINK,
         "Provides media access control and physical addressing."},
    [LAYER_NETWORK] =
        {LAYER_NETWORK,
         "Provides logical addressing and routing of data packets."},
    [LAYER_TRANSPORT] =
        {LAYER_TRANSPORT,
         "Provides end-to-end communication and data segmentation."},
    [LAYER_SESSION] =
        {LAYER_SESSION,
         "Maintains distinction between data of separate applications."},
    [LAYER_PRESENTATION] =
        {LAYER_PRESENTATION,
         "Handles data format conversion, encryption, and compression."},
    [LAYER_APPLICATION] = {
        LAYER_APPLICATION,
        "Provides a user interface and network services to applications."}};

typedef struct Node {
  OsiLayer layer;
  struct Node* next;

} Node;

Node* createNode(OSILayer_Type layer_type) {
  Node* newNode = malloc(sizeof(Node));
  if (newNode == NULL) {
    perror("Memory allocation for node failed\n");
    exit(EXIT_FAILURE);
  }
  newNode->layer.layer_type = layer_type;
  newNode->layer.description = osi_layer_info[layer_type].description;
  newNode->next = NULL;
  return newNode;
}

void insertNodeatFront(Node** head, OSILayer_Type layer_type) {
  Node* newNode = createNode(layer_type);
  newNode->next = *head;
  *head = newNode;
}

void insertNodeatBack(Node** head, OSILayer_Type layer_type) {
  Node* newNode = createNode(layer_type);
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

void insertAfter(Node* prevNode, OSILayer_Type layer_type) {
  if (prevNode == NULL) {
    fprintf(stderr, "Prevous node cannot be NULL. \n");
    return;
  }
  Node* newNode = createNode(layer_type);
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

void removebyValue(Node** head, OSILayer_Type layer_type) {
  if (*head == NULL) {
    return;
  }
  if ((*head)->layer.layer_type == layer_type) {
    Node* temp = *head;
    *head = (*head)->next;
    free(temp);
    return;
  }
  Node* current = *head;
  Node* previous = NULL;

  while (current != NULL && current->layer.layer_type != layer_type) {
    previous = current;
    current = current->next;
  }

  if (current == NULL) {
    return;  // value not found in the list
  }
  previous->next = current->next;
  free(current);
}

Node* search(Node** head, OSILayer_Type layer_type) {
  Node* current = *head;
  while (current != NULL) {
    if (current->layer.layer_type == layer_type) {
      return current;
    }
    current = current->next;
  }
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
Node* merge(Node* first, Node* second) {
  if (first == NULL)
    return second;
  if (second == NULL)
    return first;

  if (first->layer.layer_type <= second->layer.layer_type) {
    first->next = merge(first->next, second);
    return first;
  } else {
    second->next = merge(first, second->next);
    return second;
  }
}

void splitList(Node* source, Node** firstHalf, Node** secondHalf) {
  Node* slowPointer = source;
  Node* fastPointer = source->next;

  while (fastPointer != NULL) {
    fastPointer = fastPointer->next;
    if (fastPointer != NULL) {
      fastPointer = fastPointer->next;
      slowPointer = slowPointer->next;
    }
  }

  *firstHalf = source;
  *secondHalf = slowPointer->next;
  slowPointer->next = NULL;
}

Node* mergeSort(Node* head) {
  if (head == NULL || head->next == NULL) {
    return head;
  }

  Node* firstHalf;
  Node* secondHalf;
  splitList(head, &firstHalf, &secondHalf);

  firstHalf = mergeSort(firstHalf);
  secondHalf = mergeSort(secondHalf);

  return merge(firstHalf, secondHalf);
}

void printList(Node* nodeptr) {
  printf("+----------+----------------------+----------------------------+\n");
  printf("| Layer No |  Layer Name          | Layer Description          |\n");
  printf("+----------+----------------------+----------------------------+\n");
  Node* current = nodeptr;
  while (current != NULL) {
    printf("| %-8d | %-20s | %-26s |\n", current->layer.layer_type,
           osi_layer_names[current->layer.layer_type],
           current->layer.description);

    current = current->next;
  }
  printf("+----------+----------------------+----------------------------+\n");
}

void destroyList(Node* nodeptr) {
  while (nodeptr != NULL) {
    Node* tmp = nodeptr;
    nodeptr = nodeptr->next;
    free(tmp);
  }
}
int main() {
  Node* nodeptr = createNode(LAYER_TRANSPORT);
  insertNodeatFront(&nodeptr, LAYER_APPLICATION);
  insertNodeatFront(&nodeptr, LAYER_PHYSICAL);
  insertNodeatFront(&nodeptr, LAYER_DATALINK);
  insertNodeatBack(&nodeptr, LAYER_PRESENTATION);
  Node* layer5 = search(&nodeptr, 4);
  if (layer5 != NULL) {
    insertAfter(layer5, LAYER_SESSION);
  }
  Node* layer2 = search(&nodeptr, 2);
  insertAfter(layer2, LAYER_NETWORK);
  printList(nodeptr);
  nodeptr = mergeSort(nodeptr);
  printList(nodeptr);
  reverseList(&nodeptr);
  printf(" OSI Layers : \n");
  printList(nodeptr);
  removefromBack(&nodeptr);
  printList(nodeptr);
  destroyList(nodeptr);
  return 0;
}