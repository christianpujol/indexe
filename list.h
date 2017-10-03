/*
 * ======================================================
 *
 *       Filename:  list.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  25. jan. 2017 kl. 22.07 +0100
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Christian Pujol (),
 *                  pujolchr@gmail.com
 *                  christian.pujol@etud.univ-paris8.fr
 * Student number:  15611221
 *
 * =====================================================
 */
#ifndef LIST_H
#define LIST_H

#include    <stdlib.h>
#include    <stdio.h>
#include    <string.h>

typedef struct node
{
    void *car;
    struct node *cdr;
} node, *list;

/* list functions */
list cons(void *, list);
list getList(FILE *);
list isInList(void *, list);
void printList(list);
long long insertItem(void *, list, int (*)(const void *, const void *));
list findLastCons(list);

#endif /* LIST_H  */
