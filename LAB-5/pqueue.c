#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "pqueue.h"
#define p(x) (((x)-1)/2)
#define l(x) (((x)*2)+1)
#define r(x) (((x)*2)+2)


struct pqueue
{
    int count;
    int length;
    void **data;
    int (*compare)();
};

PQ *createQueue(int (*compare)())
{
    PQ *pq;
    pq = malloc(sizeof(PQ));
    assert(pq != NULL);

    pq->count = 0;
    pq->length = 10;
    pq->data = malloc(sizeof(void*)*pq->length);
    pq->compare = compare;
    assert(compare != NULL);

    return pq;
}

void destroyQueue(PQ *pq)
{
    assert(pq != NULL);
    int i;
    for(i = 0; i < pq->count; i++){
		free(pq->data[i]);
	}
	free(pq->data);
	free(pq);
}

int numEntries(PQ *pq)
{
    assert(pq != NULL);
    return(pq->count);

}

void addEntry(PQ *pq, void *entry)
{
	assert(pq!=NULL && entry!=NULL);
	if (pq->count==pq->length)
	{
		pq->data=realloc(pq->data,sizeof(void*)*pq->length*2);	// since we have now completely filled the array, double its size
		pq->length = pq->length * 2;
	}
	pq->data[pq->count]=entry;									// add the element to the end of the array
	int index = pq->count;										// this will keep track of where we are in the array when swapping
	while (pq->compare(pq->data[index],pq->data[p(index)])<0) {				// reheapup by continually comparing with parent
		//swap with parent
		void* temp = pq->data[p(index)];
		pq->data[p(index)] = pq->data[index];					// if child is smaller than parent, then we swap
		pq->data[index] = temp;

		index=p(index);
	}
	pq->count++;												// increment count
}

void *removeEntry(PQ *pq)
{
void* root = pq->data[0];												// store the data of the first element for return later
	int index = 0, smallestIndex = 0;										// index will keep track of the index we are at when we swap, and smallestIndex will determine which child is hypothetically smallest (although it does not guarantee swapping)
	pq->data[index]=pq->data[pq->count-1];									// replace the first element with the last
	// int smallestIndex = 0;
	
	pq->count--;															// decrement the count
	while (l(index)<pq->count){												// while we have a left child, we will continually run this loop
		smallestIndex = l(index);
		if (r(index)<pq->count) {											// we have a right child so we now must compare between the two children
			if (pq->compare(pq->data[l(index)],pq->data[r(index)])<0){
				smallestIndex=l(index);
			} else {
				smallestIndex=r(index);
			}
		}
		
		if (pq->compare(pq->data[smallestIndex],pq->data[index])<0) {		// in either case, which ever children is hypothetically smallest. If it is smaller than the parent, then we swap
			void* temp = pq->data[smallestIndex];
			pq->data[smallestIndex] = pq->data[index];
			pq->data[index] = temp;
			index=smallestIndex;											
		}
		else {
			break;
		}
	}
	return root;				
}