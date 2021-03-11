/******************************************************************/ 
/*													              */
/* This program is an implementation of the abstract data type    */
/* LIST. A LIST is an abstract data type in which operations (such*/
/* as retrievals, insertions, changes, and deletions) can be done */
/* anywhere in the list. This LIST abstract data type is being    */
/* used with the basic data type of linked lists. Linked lists    */
/* are dynamic data structures whose length can be increased or   */
/* decreased at run time. In the case of linked lists, the        */
/* searching algorithm that must be used is sequential search    */
/* (since you cannot directly access an element in the middle of  */
/* the linked list without first traversing through the elements  */
/* before (for singly linked list) or after (for double linked    */
/* lists). For the case of dataSet.c, we are using a circular     */
/* doubly linked list that is allowed to either traverse from the */ 
/* end (or tail end) to the beginning (or head) of the LIST or    */
/* from the beginning to the end. Since a linked list does contain*/
/* a space for data to be held, we are going to use structures    */
/* containing student records (both an integer ID and integer Age */
/* of a student who attends a college) to be held in a node in our*/
/* LIST. The structure that makes up our LIST abstract data type  */ 
/* type contains an integer variable (count) and a node pointer   */ 
/* "head" that will always point to the first node in our LIST    */ 
/* data type. Count will always tell us the current number of     */ 
/* elements within in our LIST data type and in the case of       */ 
/* dataSet.c, we are using a dummy (or sentinel) node that will   */ 
/* always act as our first node in our LIST (even if the LIST     */ 
/* itself does not have any other nodes). This dummy node limits  */ 
/* the number of special cases for the deletion/insertion of nodes*/
/* within our LIST. In essence, the dummy node makes our program  */ 
/* easier to implement and easier to understand for both the add  */
/* and remove function used in our implementation. In addition to */
/* the structure of our LIST abstract data type, there is also a  */ 
/* node structure that makes up each node within our linked list. */
/* Each node contains a data slot (which can hold a structure of a*/ 
/* student record and two node pointers that point to the previous*/
/* node in the linked list (prev) and the next node in the linked */ 
/* list (next). In addition to the function allowing the creation */ 
/* and deletion of LIST data types, dataSet.c can also search     */ 
/* through a given LIST by either age or ID of a student within   */ 
/* our LIST. Additionally, our implementation is able to add and  */ 
/* remove nodes (or student records) within our LIST as well as   */ 
/* return the maximum age gap between all students within a given */ 
/* LIST.														  */ 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "dataset.h"

/* Define a structure that will be the basis of student records within our LIST ADT. A record 
 * includes a student's unique ID number (from 1 to 2000) and a student's age (from 18 to 30). 
 * This is easily encapsulated within a structure since each student doesn't just have an ID or 
 * an Age.
 */ 
struct record
{
	//An integer variable that represents a student's ID number (from 1 to 2000).
	int ID;

	//An integer variable that represents a student's Age (from 18 to 30).
	int Age;
};

/* Define a structure that will be the basis for our LIST abstract data type. It includes one integer
 * variable that contains the current number of nodes in our LIST abstract data type and a head pointer 
 * that points to the first node in our sorted doubly linked circular list.
 */    
struct list
{	
	//An integer variable that tells us how many elements are currently in our LIST abstract data type. 
	int count;

	//The head pointer of our LIST that always points to the dummy node in our LIST abstract data type.
	struct node *head;
};

/* Define a structure that will be the basis for the nodes in our LIST abstract data type. It includes one record
 * structure that holds the data of each student's age and ID number and the two node pointers that allow our LIST
 * to be a linked list. The "next" pointer points to the next node succeeding a node in a LIST and the "prev" pointer
 * points to the previous node preceding a node in a LIST.
 */ 
struct node
{
	//The record structure that contains a student's age and unique ID number.
	RECORD studentRecord;

	//The node pointer that points to the next node succeeding a node in a LIST.
	struct node *next;

	//The node pointer that points to the previous node preceding a node in a LIST.
	struct node *prev;
}; 

/* Function: To allocate memory for a LIST data type (both the structure and the dummy
 * node that is used at the beginning of the LIST). Additionally, since the LIST starts
 * off empty (only the dummy node is the only node allocated), the dummy node must have 
 * its next and prev pointers pointing to itself.
 * 
 * Efficiency: O(1) 
 * 
 * Return Value: A pointer to the newly created LIST abstract data structure.
 */
LIST *createList()
{	
	struct list *lp;
	lp = malloc(sizeof(struct list));
	assert(lp != NULL); 
	lp->count = 0;	
	lp->head = malloc(sizeof(struct node));
	assert(lp->head != NULL);
	lp->head->next = lp->head;
	lp->head->prev = lp->head;
	return lp;
}

/* Function: To search through the LIST and find if the given studentAge 
 * exists within the LIST already using sequential search. If the given 
 * studentAge does exist, then the function prints out a statement saying 
 * that the given studentAge does exist within the LIST ADT, otherwise, 
 * the function prints a statement saying that the given studentAge does 
 * not exist within the LIST data type. Since our LIST contains a dummy 
 * node, the function must search each node within the LIST excluding the
 * dummy node.  
 *
 * Efficiency: O(n)
 * 
 * Return Type: No return value.
 */
void searchAge(LIST *lp, int studentAge)
{
	assert(lp != NULL);
	if(lp->count == 0)
	{
		printf("No records in the Data Set, cannot execute search.\n");
		return;
	}
	printf("Searching for record with Age %d in the Data Set.\n",studentAge);
	NODE *pLocate = lp->head->next;
	while(pLocate != lp->head)
	{
		if(pLocate->studentRecord.Age == studentAge)
			{
				printf("Record with Age %d was found in the Data Set.\n",pLocate->studentRecord.Age);
				return;
			}
		else
			{
				pLocate = pLocate->next;
			}
	}
	printf("Record not found in the Data Set with that specific age.\n");
}
 
/* Function: To search through the LIST and find if the given studentID 
 * exists within the LIST already using sequential search. If the given 
 * studentID does exist, then the function prints out a statement saying 
 * that the given studentID does exist within the LIST ADT, otherwise, 
 * the function prints a statement saying that the given studentID does 
 * not exist within the LIST data type. Since our LIST contains a dummy
 * node, the function must search each node within the LIST excluding the 
 * dummy node.
 *
 * Efficiency: O(n)
 * 
 * Return Type: No return value.
 */
void searchID(LIST *lp, int studentID)
{
	assert(lp != NULL);
	if(lp->count == 0)
	{
		printf("No records in the Data Set, cannot execute search.\n");
		return;
	}
	printf("Searching for record with ID %d in the Data Set.\n",studentID);
	NODE *pLocate = lp->head->next;
	while(pLocate != lp->head)
		{
			if(pLocate->studentRecord.ID == studentID)
				{
					printf("Record with ID %d was found in the Data Set.\n",pLocate->studentRecord.ID);
					return;
				}
			else
				{
					pLocate = pLocate->next;
				}
		}
	printf("Record not found in the Data Set with that specific ID.\n");
}

/* Function: Frees all the memory previously allocated from createLIST. The
 * function frees all nodes within the LIST starting from the last (or tail)
 * node and working up until the front (or head) node is reached. Once all 
 * nodes have been freed, the LIST structure itself is then freed.
 * 
 * Efficiency: O(n)
 * 
 * Return Value: No return value.
 */
void destroyList(LIST *lp)
{
	assert(lp != NULL);
	NODE *pDel;
	NODE *pPrev = lp->head->prev;
	do
	{
		pDel = pPrev;
		pPrev = pDel -> prev;
		free(pDel);
	}
	while (pDel != lp->head);
		free(lp);	
}


/*
 * Function: Allocates memory and searches through the LIST ADT looking for the correct space
 * to insert a node with the given age and ID number. Since we have to keep the LIST sorted
 * based on age (to allow us to easily find the maximum age gap within a college) we must first
 * find where a specific node should go within our LIST. To do this, we use sequential search 
 * to look for a node containing an age that is either equal to or greater than our given 
 * parameters. Once a node is found (or we reach the end of the LIST) we insert a new node
 * either before the node that contains an equal or higher age or we insert at the end of the 
 * LIST. In either case, we set the new node's age and ID number to the given parameters, and set
 * its "next" pointer to point to the searching node. Then, the newly allocated node's "prev"
 * pointer points to the searching node's "prev" pointer and the new node's predecessor now 
 * points to the new node. Finally, the searching node's "prev" pointer points to the new
 * node and our LIST's count value is increased by 1 to show that a new node has been added 
 * into the LIST.
 *
 * Eficiency: O(n)
 *
 * Return Type: No return value.
 */ 
void addElement(LIST *lp, int studentAge, int studentID)
{
	assert(lp != NULL);
	NODE *pNew = malloc(sizeof(struct node));
	assert(pNew != NULL);
	NODE *pLocate = lp->head->next;

	while(pLocate != lp->head)
	{
		if(pLocate->studentRecord.Age < studentAge)
		{
			pLocate = pLocate->next;
		}
		else
		{
			break;
		}
	}
	pNew->studentRecord.Age = studentAge;
	pNew->studentRecord.ID = studentID;
	pNew->next = pLocate;
	pNew->prev = pLocate->prev;
	pLocate->prev->next = pNew;
	pLocate->prev = pNew;
	lp->count++;
}
 
/* Function: The function searches the (non-empty) LIST looking for a specific node with the 
 * same ID number as the parameter being passed and deletes that specifc student record. 
 * If a match is found, the soon to be deleted node's previous node's "next" pointer will point to 
 * the successor of the soon to be deleted node and the soon to be deleted node's successor "prev" 
 * pointer will point to the soon to be deleted node's predecessor. Once this is all complete, the LIST's 
 * count value decreases by 1 to make up for a node being deleted. If the function does not find find the specific
 * node to be removed, then the function returns with nothing being removed from the LIST. If the specific studentID 
 * was found or not, the function prints out a message saying if the given ID number was found or not in the LIST.
 * 
 * Efficiency: O(n)
 * 
 * Return Value: No return value.
 */
void removeElement(LIST *lp, int studentID)
{
	assert (lp != NULL);
	assert(lp->count > 0);
	printf("Searching for and removing record with ID %d in the Data Set.\n",studentID);
	NODE *pRemove = lp->head->next;
	while(pRemove != lp->head)
	{
		if(pRemove->studentRecord.ID == studentID)
		{
			int tempID = pRemove->studentRecord.ID;
			pRemove->prev->next = pRemove->next;
			pRemove->next->prev = pRemove->prev;
			free(pRemove);
			lp->count--;
			printf("Record with ID %d has been located and removed from the Data Set.\n", tempID);
			break;	
		}
		else
		{
			pRemove = pRemove->next;
		}
	}
	if(pRemove->studentRecord.ID != studentID)
	{	
		printf("Record with ID %d could not be located and removed from the Data Set.\n",studentID);
	}
}


/* Function: The function returns the maximum age gap within our LIST. Since our
 * LIST is a sorted doubly linked circular list, we are able to simply return the difference
 * between our oldest student (located at the end of our LIST) and our youngest student (located
 * at the beginning of the LIST following our dummy node). Both of these elements are easily
 * accessible through the use of our head pointer and therefore can be calculated in O(1) time.
 * 
 * Efficiency: O(1)
 * 
 * Return Value: An integer that is the maximum age gap within our LIST.
 */
int maxAgeGap(LIST *lp)
{
	assert(lp != NULL);
	assert(lp->count > 1);
	return lp->head->prev->studentRecord.Age - lp->head->next->studentRecord.Age;
}