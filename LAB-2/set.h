/*
 * File:        set.h
 *
 * Description: This file contains the public function and type
 *              declarations for a set abstract data type for strings.  A
 *              set is an unordered collection of distinct elements.
 *
 *              Note that this file uses the bool type, but does not define
 *              it.  You should include <stdbool.h> beforehand.
 */

# ifndef SET_H
# define SET_H

# define Max_Word_LENGTH 30

# define MAX_SIZE 18000

# define Max_Unique 18000

typedef struct set SET;

SET *createSet(int maxElts);

void destroySet(SET *sp);

int numElements(SET *sp);

bool hasElement(SET *sp, char *elt);

bool addElement(SET *sp, char *elt);

bool removeElement(SET *sp, char *elt);

# endif /* SET_H */
