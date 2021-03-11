#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "pack.h"
#include "pqueue.h"

typedef struct node NODE;

/*
 * Function: hopNumber
 * Summary: This function takes in a leaf of a tree and traverses up the tree until it reaches the root.
 * While doing so, it counts the number of hops it takes to get there and returns how far away the specified
 * leaf is from the root.
 * Runtime: O(n)
 */
int hopNumber(struct node *leaf) {
	int hops = 0;
	while (leaf->parent!=NULL) {
		leaf = leaf->parent;
		hops++;
	}
	return hops;
}
/*
 * Function: compare
 * Summary: Like integer compare, but this time compares the data in two nodes.
 * Runtime: O(1)
 */
int compare(struct node *first, struct node *second) {
	return (first->count < second->count) ? -1 : (first->count > second->count);
}

int main(int argc, char *argv[])
{
	FILE *fp = fopen(argv[1],"r");		// Initialize pointer to file and open it to be read
	if (fp == NULL) {					// Check to see if the file exists.
  		return 0;
	}

	int occurences[257] = {0};			// initalize occurences array to all 0 with size 257 (one extra space for end of file)

	do 
	{								// we will constantly grab the next character
	  int c;
	  
      c = fgetc(fp);
      if( feof(fp) )					// we hit the end of file so we break
      {
         break;
      }
      occurences[c]++;
    } while(1);

    PQ *pqueue = createQueue(compare);

    struct node* leaves[257] = {0};			// create leaves array
    for (int i = 0; i < 257; i++) 
		{			// and initialize all its values to NULL
    	leaves[i] = NULL;
    }


    for (int i = 0; i < 256; i++) 
		{							// for each nonzero count, we create a new node for it, add ito to the pqriority queue as well as the leaves array
    	if (occurences[i]>0)
    	{
    		NODE *thenode=malloc(sizeof(struct node));
    		thenode->count = occurences[i];
    		thenode->parent = NULL;
    		addEntry(pqueue,thenode);
    		leaves[i]= thenode;
    	}
    }

    // creating a tree with a zero count for the end of file marker
    NODE *zeroCountNode = malloc(sizeof(struct node));
    zeroCountNode->count = 0;
    zeroCountNode->parent = NULL;
    addEntry(pqueue,zeroCountNode);
    leaves[256] = zeroCountNode;

  
    while (numEntries(pqueue)>1) 
		{
    	NODE *first = removeEntry(pqueue);				// the first of the lowest priority trees
    	NODE *second = removeEntry(pqueue);				// the second of the lowest priority trees
    	NODE *third = malloc(sizeof(struct node));		// the new node created that will have its count as the count of its two children (the ones we just removed)
    	third->count = first->count + second->count;
    	third->parent = NULL;
    	first->parent = third;
    	second->parent = third;
    	addEntry(pqueue, third);						// we add that new tree back into the priority queue
    }


    for (int i = 0; i < 257; i++) 
		{
    	if (leaves[i]!=NULL) 
			{
    		int numberOfHops;
    		numberOfHops = hopNumber(leaves[i]);
    		if (isprint(i))								// check if the character is printable
    		{
    			printf("%c: %d x %d bits = %d\n", i, occurences[i], numberOfHops, occurences[i]*numberOfHops);
    		}
    		else {
    			printf("%03o: %d x %d bits = %d\n", i, occurences[i], numberOfHops, occurences[i]*numberOfHops);
    		}
    		
    	}
    }
		
    pack(argv[1],argv[2],leaves);
}