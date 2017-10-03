/*
 * ========================================================
 *
 *       Filename:  garbage.c
 *
 *    Description:  function to collect and free pointer.
 *
 *        Version:  1.0
 *        Created:  02. des. 2016 kl. 00.06 +0100
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
#include    <errno.h>
#include    <stdlib.h>
#include    <stdio.h>

#include    "garbage.h"



pointer *garbages;
unsigned int GARBAGE_MAX = BUFSIZ;
unsigned int garbageIdx = 0;


/* 
 * ===  FUNCTION  ============================================================
 *         Name:  initGarbage
 *  Description:  initialize garabage array where pointers are collected
 * ===========================================================================
 */
void
initGarbage()
{
  garbages = malloc(GARBAGE_MAX * sizeof(pointer));
  if (garbages == NULL)
    {
      perror("garbage collection: ");
      exit(errno);
    }
}				/* -----  end of function initGarbage  ----- */

/* ===  FUNCTION  ============================================================
 *         Name:  collectGarbage
 *  Description:  collect in an array all pointer to be freed
 * ========================================================================= */
void
collectGarbage(pointer ptr)
{
  if (garbageIdx >= GARBAGE_MAX)
    {
      GARBAGE_MAX *= 2;
      garbages = realloc(garbages, GARBAGE_MAX * sizeof(pointer));
      if (garbages == NULL)
        {
          perror("garbage collection: ");
          exit(errno);
        }
    }
  garbages[garbageIdx++] = ptr;
}				/* -----  end of function collectGarbage  ----- */

/* 
 * ===  FUNCTION  ============================================================
 *         Name:  freeGarbage
 *  Description:  free all the pointer collected by collectGarbage()
 * ===========================================================================
 */

void
freeGarbage()
{
  int x;
  for (x = 0; x < garbageIdx; x++)
    free(garbages[x]);
  free(garbages);
}				/* -----  end of function freeGarbage  ----- */
