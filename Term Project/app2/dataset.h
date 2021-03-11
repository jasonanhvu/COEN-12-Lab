/*
 * File:        dataset.h
 *
 *
 * Description: This file contains the public function and type
 *              declarations for a SET abstract data type for student records.
 *              A SET is an ADT that contains only unique eleemnts (in this case,
 *              unqiue ID numbers for each stduent and is used with hash tables
 *              to make searching for specific ID numbers easier and more efficent. 
 */

# ifndef DATASET_H
# define DATASET_H

typedef struct record RECORD;

typedef struct set SET;

SET* createSet(int);

int searchID(SET*,int,bool*);

void destroySet(SET*);

void addElement(SET*,int,int);

void removeElement(SET*,int);

# endif 