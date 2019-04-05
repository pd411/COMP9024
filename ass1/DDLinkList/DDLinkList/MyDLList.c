//
//  main.c
//  DDLinkList
//
//  Created by 彭迪 on 6/3/19.
//  Copyright © 2019 di. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>


// all the basic data structures and functions are included in this template
// you can add your own auxiliary functions as you like

// data structures representing DLList

// data type for nodes
typedef struct DLListNode {
    int  value;  // value (int) of this list item
    struct DLListNode *prev;
    // pointer previous node in list
    struct DLListNode *next;
    // pointer to next node in list
} DLListNode;

//data type for doubly linked lists
typedef struct DLList{
    int  size;      // count of items in list
    DLListNode *first; // first node in list
    DLListNode *last;  // last node in list
} DLList;

// create a new DLListNode
DLListNode *newDLListNode(int it)
{
    DLListNode *new;
    new = malloc(sizeof(DLListNode));
    assert(new != NULL);
    new->value = it;
    new->prev = new->next = NULL;
    return new;
}

// create a new empty DLList
DLList *newDLList()
{
    DLList *L;
    
    L = malloc(sizeof (struct DLList));
    assert (L != NULL);
    L->size = 0;
    L->first = NULL;
    L->last = NULL;
    return L;
}

// create a DLList from a text file
// put your time complexity analysis for CreateDLListFromFileDlist() here

// the time complexity analysis for CreateDLListFromFilDList() is O(n)
// n means length of list
DLList *CreateDLListFromFileDlist(const char *filename)
{
    // put your code here
    DLList *L = newDLList();
    int n;
    if (strcmp(filename, "stdin") == 0) {
        char s[100];
        while (fgets(s,100,stdin)!=NULL){
            if (*s == '\n'){
                break;
            }
            DLListNode *node = newDLListNode(atoi(s));
            if (L->size == 0) {
                L->first = L->last = node;
            }else{
                L->last->next = node;
                node->prev = L->last;
                L->last = node;
            }
            L->size++;
        }
    } else{
        FILE *fp = fopen(filename, "r");
        if (fp == NULL) {
            printf("Cannot open file.\n");
            return 0;
        }
        while (fscanf(fp, "%d", &n) != EOF) {
            DLListNode *node = newDLListNode(n);
            if (L->size == 0) {
                L->first = L->last = node;
            }else{
                L->last->next = node;
                node->prev = L->last;
                L->last = node;
            }
            L->size++;
        }
    }
    return L;
}

// clone a DLList
// put your time complexity analysis for cloneList() here

// the time complexity analysis for cloneList() is O(n)
// n = u->size
DLList *cloneList(DLList *u)
{
    // put your code here
    DLList *result = newDLList();
    DLListNode *node = u->first;
    for (int i = 0; i < u->size; i++) {
        DLListNode *new_node = newDLListNode(node->value);
        if (result->size == 0) {
            result->first = result->last = new_node;
        } else{
            result->last->next = new_node;
            new_node->prev = result->last;
            result->last = new_node;
        }
        result->size++;
        node = node->next;
    }
    return result;
    
}

// compute the union of two DLLists u and v

// the time complexity analysis for union() is O(n * m)
// n = v->size, m = result->size
DLList *setUnion(DLList *u, DLList *v)
{
    // put your code here
    DLList *result = cloneList(u);
    DLListNode *v_head = v->first;
    for (int i = 0; i < v->size; i++) {
        int j = 0;
        DLListNode *result_head = result->first;
        for (j = 0; j < result->size; j++) {
            if (v_head->value == result_head->value) {
                break;
            }
            result_head = result_head->next;
        }
        
        if (j == result->size) {
            DLListNode *node = newDLListNode(v_head->value);
            result->last->next = node;
            node->prev = result->last;
            result->last = node;
            result->size++;
        }
        v_head = v_head->next;
    }
    return result;
}

// compute the insection of two DLLists u and v
// put your time complexity analysis for intersection() here

// the time complexity analysis for intersection() is O(n * m)
// n = result->size, m = v->size
DLList *setIntersection(DLList *u, DLList *v)
{
    // put your code here
    DLList *result = cloneList(u);
    for (int i = 0; i < result->size; i++) {
        DLListNode *v_head = v->first;
        int isExist = 0;
        for (int j = 0; j < v->size; j++) {
            if (v_head->value == result->first->value) {
                isExist = 1;
                break;
            }
            v_head = v_head->next;
        }
        if (isExist == 0) {
            DLListNode *n = result->first->prev;
            n->next = result->first->next;
            result->first->next->prev = n;
            result->size--;
        }
        result->first = result->first->next;
    }
    while (result->first->prev) {
        result->first = result->first->prev;
    }
    return result;
}

// free up all space associated with list
// put your time complexity analysis for freeDLList() here

// the time complexity analysis for intersection() is O(n)
// n = L->size
void freeDLList(DLList *L)
{
    // put your code here
    while (L->first != NULL) {
        free(L->first);
        L->first = L->first->next;
    }
    free(L);
}


// display items of a DLList
// put your time complexity analysis for printDDList() here

// the time complexity analysis for intersection() is O(n)
// n = u->size
void printDLList(DLList *u)
{
    // put your code here
    DLListNode *node = u->first;
    while(node != NULL) {
        printf("%d ", node->value);
        node = node->next;
    }
    printf("\n");
}

int main()
{
    
    DLList *list1, *list2, *list3, *list4;
    list1=CreateDLListFromFileDlist("File1.txt");
    printDLList(list1);
    
    list2=CreateDLListFromFileDlist("File2.txt");
    printDLList(list2);

    list3=setUnion(list1, list2);
    printDLList(list3);
    
    list4=setIntersection(list1, list2);
    printDLList(list4);
    
    
    freeDLList(list1);
    freeDLList(list2);
    freeDLList(list3);
    freeDLList(list4);
    
    printf("please type all the integers of list1\n");
    list1=CreateDLListFromFileDlist("stdin");
    
    printf("please type all the integers of list2\n");
    list2=CreateDLListFromFileDlist("stdin");
    list3=cloneList(list1);
    printDLList(list3);
    list4=cloneList(list2);
    printDLList(list4);
    
    freeDLList(list1);
    freeDLList(list2);
    freeDLList(list3);
    freeDLList(list4);
    return 0;
}

