/*
 * File:        dataset.h
 *
 *
 * Description: This file contains the public function and type
 *              declarations for a LIST abstract data type for student records.
 *              A LIST is an ADT that can handle retrievals, insertions, and 
 *              deletions anywhere within the LIST data type. 
 */

# ifndef DATASET_H
# define DATASET_H

typedef struct record RECORD;

typedef struct list LIST;

typedef struct node NODE;

LIST* createList();

void searchAge(LIST*,int);

void searchID(LIST*,int);

void destroyList(LIST*);

void addElement(LIST*,int,int);

void removeElement(LIST*,int);

int maxAgeGap(LIST*);

# endif 