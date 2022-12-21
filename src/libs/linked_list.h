/******************************************************************************
 * Copyright (c) 2022.                                                        *
 *                                                                            *
 *                                                                            *
 * Battleship                             ______   _______      _______.      *
 * main.c                                /      | /  _____|    /       |      *
 *                                      |  ,----'|  |  __     |   (----`      *
 * By: CorentinGS                       |  |     |  | |_ |     \   \          *
 * <c.giaufersaubert@outlook.com>       |  `----.|  |__| | .----)   |         *
 *                                       \______| \______| |_______/  (_/ -/  *
 * LICENCE: BSD-3                                                      /  /   *
 * Created: 2022/11/7 by CorentinGS                                           *
 *                                                                            *
 ******************************************************************************/

#ifndef BATTLESHIP_LINKED_LIST_H
#define BATTLESHIP_LINKED_LIST_H

#include "../common.h"

struct node_t {
    struct node_t* next;
    int value;
};

typedef struct node_t Node;

typedef struct {
    Node* first;
    Node* last;
} LinkedList;

extern void run_linkedlist_tests(void);

int value(Node* n);
Node* next(Node* n);
Node* first(LinkedList* l);
Node* last(LinkedList* l);
int is_empty(LinkedList* l);
void add_first(LinkedList* l, int value);
void add_last(LinkedList* l, int value);
void add_after(LinkedList* l, Node* n, int value);
void delete_first(LinkedList* l);
void delete_last(LinkedList* l);
void delete_after(LinkedList* l, Node* n);
void flush(LinkedList* l);
int size(LinkedList* l);
void print(LinkedList* l);

#endif
