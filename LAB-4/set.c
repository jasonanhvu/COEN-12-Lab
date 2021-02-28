# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include "set.h"
# include <stdbool.h>
# include "list.h"

# define EMPTY 0
# define FILLED 1
# define DELETED 2

int search(SET *sp,char *elt, bool *found);

struct set{
    int count;
    int length;
    LIST  **data;
    int (*compare)();
    unsigned (*hash)();
};

//O(n)
//creates a set with length maxElts
SET *createSet(int maxElts,int (*compare)(),unsigned (*hash)()){
    SET *sp = malloc(sizeof(SET));
    assert(sp!=NULL);
    sp->count=0;
    sp->length=maxElts/20;
    sp->data=malloc(sizeof(LIST*) * sp->length);
    sp->compare=compare;
    sp->hash=hash;
    for(int i=0;i<sp->length;i++)
        sp->data[i]=createList(compare);
    assert(sp->data!= NULL);
    return sp;
}

//O(n)
//destroys set
void destroySet(SET *sp) {
    for(int i=0;i<sp->length;i++)
      destroyList(sp->data[i]);
    free(sp);
}

//O(1)
//returns the number of elements in the set pointed to by sp
int numElements(SET *sp) {
    assert(sp!=NULL);
    return sp->count;
}

//O(1)
//adds an element
void addElement(SET *sp,void  *elt) {
    assert(sp!=NULL&&elt!=NULL);
    unsigned index=(sp->hash)(elt)%sp->length;
    if(findItem(sp->data[index],elt)==NULL) {
        addFirst(sp->data[index],elt);
        sp->count++;
    }
}

//O(n)
//removes an element from set
void removeElement(SET *sp, void  *elt) {
    assert(sp!=NULL&&elt!=NULL);
    unsigned index=(sp->hash)(elt)%sp->length;
    if(findItem(sp->data[index],elt)!=NULL){
        removeItem(sp->data[index],elt);
        sp->count--;
    }
}

//O(n)
//returns an element that has been passed if it is in the set
void  *findElement(SET *sp, void *elt) {
    assert(sp!=NULL);
    unsigned index=(sp->hash)(elt)%sp->length;
    return findItem(sp->data[index],elt);
}

//O(n)
//returns the data of the set passed
void  *getElements(SET *sp) {
    assert(sp!=NULL||sp->count!=0);
    void  **elts = malloc(sizeof(void*) * sp->count);
    assert(elts!=NULL);
    int index=0;
    for(int i=0;i<sp->length;i++)
        if(sp->data[i]!=NULL){
            void **items=getItems(sp->data[i]);
            for(int j=0;j<numItems(sp->data[i]);j++){
                elts[index]=items[j];
                index++;
            }
        }
    return elts;
}
