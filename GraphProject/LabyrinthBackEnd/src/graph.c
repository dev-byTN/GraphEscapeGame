#include "../include/graph.h"

ListSuccessor *createList() {
    ListSuccessor *newList = malloc(sizeof(ListSuccessor));
    newList->firstSuccessor = NULL;
    newList->size = 0;
    return newList;
}

void insertHead(ListSuccessor *list, Successor *element) {
    element->nextSuccessor = list->firstSuccessor;
    list->firstSuccessor = element;
    list->size++;
}

void insertElement(ListSuccessor *list, Successor *element) {
    if (list->firstSuccessor == NULL) {
        insertHead(list, element);
        return;
    }
    Successor *actualElement = list->firstSuccessor;

    while (actualElement->nextSuccessor != NULL) {
        actualElement = actualElement->nextSuccessor;
    }

    actualElement->nextSuccessor = element;
    list->size++;
}

void removeElement(ListSuccessor *list, Successor *element) {
    if (list->firstSuccessor == NULL) {
        return;
    }
    Successor *actualElement = list->firstSuccessor;

    if (actualElement == element) {
        list->firstSuccessor = actualElement->nextSuccessor;
        list->size--;
        return;
    }

    while (actualElement->nextSuccessor != NULL) {
        if (actualElement->nextSuccessor == element) {
            actualElement->nextSuccessor = actualElement->nextSuccessor->nextSuccessor;
            list->size--;
            return;
        }

        actualElement = actualElement->nextSuccessor;
    }
}


void freeList(ListSuccessor *list) {
    if (list == NULL) {
        return;
    }
    Successor *actualElement = list->firstSuccessor;
    Successor *nextElement;

    while (actualElement != NULL) {
        nextElement = actualElement->nextSuccessor;
        free(actualElement);
        actualElement = nextElement;
    }

    free(list);
}