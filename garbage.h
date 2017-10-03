/*
 * ======================================================
 *
 *       Filename:  garbage.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02. des. 2016 kl. 00.05 +0100
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

#ifndef GARBAGE_H		/*  Include guard */
#define GARBAGE_H


/* typedef */
typedef void *pointer;

/* prototype  */
void freeGarbage();
void collectGarbage(pointer);
void initGarbage();

#endif /* GARBAGE_H */
