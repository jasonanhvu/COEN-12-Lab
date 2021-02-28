# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include <stdbool.h>
# include "list.h"

struct node{
	void* data;
	struct node *next;
	struct node *prev;
};
typedef struct node NODE;

struct list{
	int count;
	NODE *head;
	int (*compare)();
};

//O(1)
//creates a list and intialazes all varibles within LIST
LIST *createList(int (*compare)()){
	LIST *lp;
	lp=malloc(sizeof(LIST));
	assert(lp!=NULL);
	lp->count=0;
	NODE *sentinel = malloc(sizeof(NODE));
	assert(sentinel!=NULL);
	sentinel->next=sentinel;
	sentinel->prev=sentinel;
	lp->head=sentinel;
	lp->compare=compare;
	return lp;
}

//O(n)
//destroys a list
void destroyList(LIST *lp){
	assert(lp!=NULL);
	NODE *place=lp->head->next;
	while(lp->head!=place){
		NODE *temp=place;
		place=place->next;
		free(temp);
	}
	free(lp->head);
	free(lp);
}

//O(1)
//returns number of items in list
int numItems(LIST *lp){
	assert(lp!=NULL);
	return lp->count;
}

//O(1)
//add item to beginning of list
void addFirst(LIST *lp, void *item){
	assert(lp!=NULL);
	NODE *temp;
	temp=malloc(sizeof(NODE));
	assert(temp!=NULL);
	temp->data=item;
	temp->prev=lp->head;
	temp->next=lp->head->next;
	lp->head->next->prev=temp;
	lp->head->next=temp;
	lp->count++;
}

//O(1)
//add item to end of list
void addLast(LIST *lp, void *item){
	assert(lp!=NULL);
	NODE *temp;
	temp=malloc(sizeof(NODE));
	assert(temp!=NULL);
	temp->data=item;
	temp->prev=lp->head->prev;
	temp->next=lp->head;
	lp->head->prev->next=temp;
	lp->head->prev=temp;
	lp->count++;
}


//O(1)
//remove first item
void *removeFirst(LIST *lp) {
	assert(lp!=NULL&&lp->count>0);
	NODE *temp=lp->head->next;
	lp->head->next=temp->next;
	temp->next->prev=lp->head;
	lp->count--;
	void* dataTemp=temp->data;
	free(temp);
	return dataTemp;
}

//O(1)
//remove last item
void *removeLast(LIST *lp) {
	assert(lp!=NULL&&lp->count>0);
  NODE *temp = malloc(sizeof(NODE));
	temp=lp->head->prev;
	lp->head->prev=temp->prev;
	temp->prev->next=lp->head;
	lp->count--;
	void* dataTemp=temp->data;
	free(temp);
	return dataTemp;
}

//O(1)
//returns first item in list
void *getFirst(LIST *lp) {
	assert(lp!=NULL&&lp->count>0);
	return lp->head->next->data;
}

//O(1)
//returns last item in list
void *getLast(LIST *lp) {
	assert(lp!=NULL&&lp->count>0);
	return lp->head->prev->data;
}

//O(n)
//finds an items and then removes it
void removeItem(LIST *lp, void *item) {
	assert(lp!=NULL&&lp->compare!=NULL);
	if(lp->count>0) {
		NODE *place=lp->head->next;
		while(place!=lp->head){
			if((lp->compare)(place->data,item)==0) {
				place->prev->next=place->next;
				place->next->prev=place->prev;
				free(place);
				return;
			}
			place=place->next;
		}
	}
}

//O(n)
//finds an item and returns it
void *findItem(LIST *lp, void *item) {
	assert(lp!=NULL&&lp->compare!=NULL);
	if(lp->count>0) {
		NODE *place=lp->head->next;
		while(place!=lp->head){
			if((lp->compare)(place->data,item)==0)
				return place->data;
			place=place->next;
		}
	}
	return NULL;
}

//O(n)
//creates array of all items
void *getItems(LIST *lp) {
    assert(lp != NULL);
    void **elts = malloc(sizeof(void*)*lp->count);
    NODE *p = lp->head->next;
    for(int i=0; i<lp->count; i++) {
        elts[i] = p->data;
        p = p->next;
    }
    return elts;
}