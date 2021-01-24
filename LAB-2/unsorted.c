/*
 * File:       unsorted.c
 *
 * Description: First, implement a set using an unsorted array of 
 *              length m > 0, in which the first n ≤ m slots are used to hold n 
 *              strings in some arbitrary order. Use sequential search to locate 
 *              an element in the array
 *
 * Created by Jason Vu on 1/23/2021
 * Copyright (c) 2021 Jason Vu. All rights reserved.
*/

# include <assert.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include "set.h"

#define Max_Word_LENGTH 30
#define Max_Unique 18000

struct set {
    int count;
    int length;
    char* *elts;
};

SET *createSet(int maxElts) {
    SET *sp; //number of used slots
    sp = malloc(sizeof(SET));  //total number of slots
    assert(sp != NULL);   //did malloc allocate memory?
    sp->count = 0;
    sp->length = maxElts;
    sp->elts = malloc(sizeof(char*)*maxElts);
    assert(sp->elts != NULL);
    return sp;
}

static int findElement(SET *sp, char *elt);

/*  Deallocates memory for the set
 *  Big-O Notation: O(n)
 */

void destroySet(SET *sp) {
    int i;
    for (i=0; i < sp->count; i++) {
        free(sp->elts[i]);
    }
    free(sp->elts);
    free(sp);
}

/*  Returns the number of elements in array
 *  Big-O Notation: O(1)
 */

int numElements(SET *sp) {
    return sp->count;
}

/*  calls fineElement and uses linear search to locate element
 *  returns bool if element 
 *  Big-O Notation: O(n)
 */

bool hasElement(SET *sp, char *elt) {
    if (findElement(sp, elt) == -1) {
        return false;
    }
    return true;
}

/*  Calls hasElement>findElement. adds element to end of array.
 *  Big-O Notation: O(n)
 */

bool addElement(SET *sp, char *elt) {
    assert(sp->count < Max_Unique);
    if (hasElement(sp, elt) == false) {
        sp->elts[sp->count] = strdup(elt);
        assert(sp != NULL);
        sp->count++;
        return true;
    }
    return false;
}

/*  locates element: O(n)
 *  removes element: O(1) 
 */

bool removeElement(SET *sp, char *elt) {
    int i;
    i = findElement(sp,elt);
    if (i != -1) {
        free(sp->elts[i]);
        sp->elts[i] = sp->elts[sp->count-1];
        sp->count--;
        return true;
    }
    return false;
}

/*  Uses linear search to find an element in an array
 *  Big-O Notation: O(n)
 */

int findElement(SET *sp, char *elt) {
    int i;
    for (i = 0; i < sp->count; i++){
        if(strcmp(sp->elts[i], elt) == 0)
        return (i);
        }
    return (-1);
} 