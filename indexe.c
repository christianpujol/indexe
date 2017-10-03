/* ===
 *
 *       Filename:  index.c
 *
 *
 *        Version:  1.0
 *        Created:  13. nov. 2016 kl. 17.25 +0100
 *       Revision:  none
 *       Compiler:  gcc
 *
 *        Student:  Christian Pujol ()
 *                  pujolchr@gmail.com
 *                  christian.pujol@etud.univ-paris8.fr
 * Student Number:  15611221
 *
 * ====================================================================== */


#include    <stdlib.h>
#include    <stdio.h>
#include    <string.h>
#include    <unistd.h>
#include    <errno.h>
#include    <ctype.h>

#include    "list.h"
#include    "garbage.h"

#define DEBUG(h) fprintf(stderr,"here %d\n", (h))
#define usage fprintf


/* Typedefs */
typedef unsigned int idx;
typedef char *str;

typedef struct ndex
{
    str mot;
    list refs;
} ndex;

list indexe(list, str, idx, int, list);
void dump(list);

int compare(const void *, const void *);
int compint(const void *, const void *);

/*  Variables */
char *USAGE = "usage: %s [ -g GOFILE | -s STOPFILE ]  [FILE]\n";
char *HELP = "Try '%s -h' for more information.\n";
const str split_chars = "\\_/@$|*&?!:<>#-=+[]{}() \t\r\n.,`´;\"'";

/* ===  MAIN  =========================================================== */
int
main(int argc, str argv[])
{

    str wordFile = NULL;
    str fileToIndex = NULL;

    int stop = 0;
    int go = 0;

    initGarbage();
    atexit(freeGarbage);

    /* ------ Start of arguments parsing --------- */
    int opt;

    while ((opt = getopt(argc, argv, "hg:i:s:")) != -1) {
        switch (opt) {
            /* option h : display help  */
        case 'h':
            usage(stdout, USAGE, argv[0]);
            exit(EXIT_SUCCESS);

            /* go list filename */
        case 'g':
            wordFile = strdup(optarg);
            collectGarbage(wordFile);
            go = 2;
            break;

            /* stop list filename */
        case 's':
            wordFile = strdup(optarg);
            collectGarbage(wordFile);
            stop = 1;
            break;
        case '?':
            usage(stderr, HELP, argv[0]);
            exit(EXIT_FAILURE);
        default:
            usage(stderr, "%s:Error while parsing arguments\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    };

    /* stop ou go ? */
    go = (go > stop) ? 1 : 0;

    /* the next unprocessed argument is the file to index */
    if (fileToIndex == NULL) {
        if (optind < argc) {
            fileToIndex = strdup(argv[optind]);
            collectGarbage(fileToIndex);
        }
    }

    /* ----------- End of Cli argument  parsing ------- */

    /* Build go and stop List from file if needed --------- */

    FILE *stream;
    list wordList = NULL;

    if (wordFile != NULL) {
        stream = fopen(wordFile, "r");
        if (!stream) {
            char mesg[256];
            sprintf(mesg, "%s: %s" , argv[0], wordFile);
            perror(mesg);
            exit(errno);
        } else {
            wordList = getList(stream);
            fclose(stream);
        }
    }

    /* END of building stop/Go list */

    if (fileToIndex) {
        stream = fopen(fileToIndex, "r");

        if (!stream) {
            perror(fileToIndex);
            exit(errno);
        }
    } else {
        stream = stdin;
    }

    char ligne[BUFSIZ];
    idx x = 0;
    list index = NULL;

    while (fgets(ligne, BUFSIZ, stream)) {
        index = indexe(index, ligne, ++x, go, wordList);
    }

    fclose(stream);

    dump(index);

    return EXIT_SUCCESS;
}

/* ----------  end of function main  ---------- */


/* #==  indexe  ========================================================= */
list
indexe(list index, str ligne, idx x, int go, list wordList)
{
    idx *ref;
    list inWordList;

    str dup = strdup(ligne);
    collectGarbage(dup);

    str mot = strtok(dup, split_chars);
    if (mot) {

        ref = malloc(sizeof(idx));
        if (ref == NULL) {
            perror("malloc");
            exit(1);
        }
        collectGarbage(ref);

        *ref = x;
    }
    while (mot) {

        str p;
        /* one liner found here: http://stackoverflow.com/a/2661788/5292970 */
        for (p = mot; *p; ++p)
            *p = tolower(*p);

        inWordList = isInList(mot, wordList);

        /* on traite le mot ou pas? */
        if ((inWordList != NULL && go) || (inWordList == NULL && !go)) {
            /* Si oui on l'insere dans l'index a sa place */

            ndex *refsMots = malloc(sizeof(ndex));
            if (refsMots == NULL) {
                perror("malloc");
                exit(1);
            }
            collectGarbage(refsMots);

            refsMots->mot = mot;
            refsMots->refs = cons(ref, NULL);

            long long tmp = insertItem(refsMots, index, compare);

            if (tmp < 0) {
                /* ou on ajoute le numero de ligne a sa liste de refs si il
                 * est deja dans l' index */
                ndex *dbl;
                dbl = (ndex *) (((list) (-tmp))->car);
                list last = findLastCons(dbl->refs);
                if (*((int *) (last->car)) != x) {
                    last->cdr = cons(ref, NULL);
                }
            } else {
                index = (list) tmp;
            }
        }
        mot = strtok(NULL, split_chars);
    }

    return index;
}

/* -----  end of function indexe  ----- */

/* #==  compare  ======================================================== */
int
compare(const void *p1, const void *p2)
{
    ndex *r1 = ((ndex *) p1);
    ndex *r2 = ((ndex *) p2);

    return strcasecmp(r1->mot, r2->mot);
}

/* -----  end of function compare  ----- */

/* #==  dump  =========================================================== */
void
dump(list L)
{
    str mot;
    list refs;
    if (L == NULL) {
        return;
    }

    dump(L->cdr);

    mot = ((ndex *) L->car)->mot;
    refs = ((ndex *) L->car)->refs;
    printf("%s :", mot);

    printList(refs);

    printf("\n");
}

/* -----  end of function dump  ----- */
