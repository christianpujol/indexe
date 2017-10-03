/*
 * ========================================================
 *
 *       Filename:  list.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  25. jan. 2017 kl. 22.09 +0100
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Christian Pujol (),
 *                  pujolchr@gmail.com
 *                  christian.pujol@etud.univ-paris8.fr
 * Student number:  15611221
 *
 * =======================================================
 */

#include "list.h"
#include "garbage.h"


/* #==  insertItem ======================================================== 
 * Insert item in ordered list if item not in list                       */

long long
insertItem(void *item, list Lo, int (*comp) (const void *, const void *))
{
    if (!Lo || comp(item, Lo->car) > 0) {
        Lo = cons(item, Lo);
        return (long long) Lo;
    }
    if (comp(item, Lo->car) == 0) {
        return -((long long) Lo);
    }
    list Lp = Lo;
    list L = Lp->cdr;

    while (1) {
        if (L && comp(item, L->car) == 0) {
            return -((long) L);
        }
        if (!L || comp(item, L->car) > 0) {
            Lp->cdr = cons(item, L);
            break;
        }
        Lp = L;
        L = L->cdr;
    }

    return (long long) Lo;
}

/* -----  end of function insertItem  ----- */

/* #==  findLastCons======================================================== */
list
findLastCons(list L)
{
    if (!L)
        return NULL;
    if (!(L->cdr))
        return L;
    return findLastCons(L->cdr);
}

/* -----  end of function findLastCons  ----- */

/* 0==  lenlist  =========================================================== */
unsigned int
lenList(list L)
{
    if (L == NULL)
        return 0;
    return 1 + lenList(L->cdr);
}

/* -----  end of function lenList  ----- */

/* #==  isInList  ========================================================== */
list
isInList(void *pointeur, list L)
{
    if (L == NULL)
        return NULL;
    if (strcasecmp(L->car, pointeur) == 0)
        return L;

    return isInList(pointeur, L->cdr);
}

/* -----  end of function isInList  ----- */

/* #==  cons  ============================================================== */

list
cons(void *car, list L)
{
    list new = malloc(sizeof(node));
    if (!new) {
        perror("cons : malloc :");
        exit(1);
    }
    collectGarbage(new);

    new->car = car;
    new->cdr = L;

    return new;

}

/* -----  end of function cons  ----- */

/* ===  printList  ========================================================= */
void
printList(list L)
{

    if (L == NULL)
        return;
    printf(" %i", *((int *) L->car));
    printList(L->cdr);
}

/* -----  end of function printList  ----- */


/* ===  getList  =========================================================== */
list
getList(FILE * stream)
{
    list L = NULL;
    int lu;
    char buffer[BUFSIZ];

    lu = fscanf(stream, "%s", buffer);
    while (lu != EOF) {
        L = cons(strdup(buffer), L);
        collectGarbage(L->car);

        lu = fscanf(stream, "%s", buffer);
    }

    return L;
}

/* -----  end of function getList  ----- */
