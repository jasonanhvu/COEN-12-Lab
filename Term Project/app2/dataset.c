/******************************************************************/        				   
/*													              */
/* This program is the implementation of the abstract data type   */
/* SET. For this application, we are using student records        */
/* contained within a structure with both an Age integer (from 18 */ 
/* to 30) and a unique ID integer (from 1 to 2000) within a       */ 
/* college. For this SET we will be conducting frequent search    */ 
/* operations and will care more about the efficiency in the      */ 
/* ability to locate specific student records given a student's   */ 
/* unique ID number. For this application we will be using hash   */ 
/* tables to more efficiently search for data in our SET. As with */ 
/* searching, hash tables are also used in the means of inserting */ 
/* and deleting elements from the SET. With an array of structure */
/* pointers pointing to student records, we will use a hash       */ 
/* function to more quickly find the elements we are looking for  */ 
/* within the SET itself. The structure that makes up a SET data  */ 
/* type contains two integer variables (count and length) that    */ 
/* hold the total number of possible student records (length) and */ 
/* the current number of student records (count) within the SET at*/
/* one time. The studentRecord double pointer points to the first */ 
/* student record pointer as part of our SET and is used within   */ 
/* our search student ID function to find matching ID numbers     */ 
/* between a student record and the given parameter within our    */
/* SET. Since we are using hash tables, we also have to implement */
/* an array of flags to check which spaces in our SET are empty   */ 
/* (not previously filled), removed (previously filled and then   */ 
/* deleted) and filled (currently containing an element). In      */ 
/* addition to our search function using hash tables, this program*/
/* can create a SET data type, destroy a SET data type, add a     */
/* student record into a SET, and remove a student record from a  */
/* SET.															  */ 

 
/* For hash tables an array of "flags" are used to mark which locations
 * within the SET data type are filled (with a student record pointer), removed
 * (previously deleted by the removeElement function), or empty (waiting to be filled
 * by the addElement function). These flags make it easier to tell which spots 
 * in our SET can have new elements inserted (removed or empty spots) and which spots
 * have student records that we need to look at (filled spots). These flags have
 * been defined in our program to represent "empty", "filled", and "removed" instead
 * of their character counterparts of "0", "1", and "2" to make the program easier to
 * read and understand the implementation of our hash table.
 */  
#define Empty 0
#define Filled 1
#define Removed 2


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "dataset.h"


/*
 * Define a structure that will be the basis of student records within our SET ADT. A record
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

/* Define a structure that will be the basis for our SET abstract data type. It includes two integer
 * variables that contain the length of our array of student record pointers, the current number of student
 * records, and a pointer to the first student record pointer. Additionally, a SET contains a character pointer
 * to the first flag in our array of flags used to access which elements are filled, empty, or 
 * previously removed from our SET.
 */    
struct set
{
	//An integer variable that tells us how many student records we currently have in our SET. 
	int count;
	
	//An integer variable that tells us the maximum number of student records that have been allocated to be stored in our SET.
	int length;

	//A pointer that points to the first student record pointer in our array of student record pointers. That is the reason it is a 
	//pointer to a pointer.
	RECORD** studentRecord;
	
	//A character pointer that points to the first flag (being a single character) in our array of characters that represent the flags
	//of our hash table.  
	char *flag;
}; 

/* Function: To allocate memory for a SET data type (both the structure and the array of 
 * student record pointers) with the array of student record pointers having a maximum 
 * capacity of maxElts. Additionally, as a SET data type is created with no 
 * elements currently inside it, all flags used as part of the SET are set to Empty 
 * (in this case 0).
 * 
 * Efficiency: O(m) 
 * 
 * Return Value: A pointer to the newly created SET abstract data structure.
 */
SET *createSet(int maxElts)
{	
	SET*sp = malloc(sizeof(SET));
	assert(sp!=NULL);
	sp->count = 0;
	sp->length = maxElts;
	sp->studentRecord = malloc(sizeof(RECORD*)*maxElts);
	assert(sp->studentRecord != NULL);
	sp->flag = malloc(sizeof(char)*maxElts);
	assert(sp->flag != NULL);
	for(int i = 0; i < sp->length; i++)
	{
		sp->flag[i] = Empty;
	}
	return sp;
}

/* Function: To search through the SET and find if a specific student ID exists within the SET already using
 * a hash function along with linear probing to resolve collisions. If a student record containing the given 
 * student ID does exist, then the function returns the index where it is located within the SET and sets the
 * boolean pointer "found" to true, otherwise, after searching through all filled and removed spaces, the 
 * function returns the index "-1" and prints out that the given student ID could not be found within the SET.
 *
 * Efficency: O(n) with O(1) being the ideal case
 * 
 * Return Type: The index of within a SET of the student record pointer that points to a record with a specific
 * student ID (if found in the array of student record pointers) and thereby the index used for the removal of an 
 * element in the SET). Otherwise, "-1" if the student record cannot be found.
 */
int searchID(SET *sp, int studentID, bool *found)
{
	assert(found != NULL);
	*found = false;
	assert(sp != NULL);
	if(sp->count == 0)
	{
		printf("No records in the Data Set, cannot execute search.\n");
		return -1;
	}
	printf("Searching for record with ID %d in the Data Set.\n",studentID);
	int position = studentID % sp->length;
	for (int i = 0; i < sp->length; i++)
	{	
		int newPosition = (position + i) % sp->length;
		if(sp->flag[newPosition] == Filled)
		{
			if(sp->studentRecord[newPosition]->ID == studentID)
			{
				*found = true;
				printf("Record with ID %d was found in Data Set.\n", sp->studentRecord[newPosition]->ID);
				return newPosition;
			}
		}
	}
	printf("Record with ID %d was not found in Data Set.\n", studentID);
	return -1;
}

/* Function: Frees all the memory previously allocated from createSet. All
 * that is handled in this function is the freeing of all the pointers used 
 * within our SET (for flags, for our array of student record pointers, and 
 * finally for the SET itself). 
 * 
 * Efficiency: O(n)
 * 
 * Return Value: No return value.
 */
void destroySet(SET *sp)
{
	assert(sp!=NULL);
	for(int i=0; i < sp->count; i++)
	{
		free(sp->studentRecord[i]);
	}
	free(sp->flag);
	free(sp->studentRecord);
	free(sp);	
}


/* Function: This function allocates memory and inserts a student record pointer within the SET. The function 
 * checks to see if there is enough sapce for a new element (if "count" is not equal to "length") and then uses 
 * the hash function to get a home location where the record should go. If that location is already filled with
 * a record, then the function uses linear probing to find the first empty or removed spot within the SET. After 
 * finding either an empty or deleted space (whichever comes first) a new student record is allocated and its 
 * pointer is inserted into the SET data structure. After this is complete, the flag character is changed to 
 * filled (1) and the count of the SET is increased to reflect a new element being added to the SET.
 *
 * Efficiency: O(n) with O(1) being expected
 *
 * Return Value: No return value.
 */
void addElement(SET *sp, int studentID, int studentAge)
{		
	assert(sp != NULL);
	assert(sp->count < sp->length);
	int position = studentID % sp->length;
	for (int i = 0; i < sp->length; i++)
	{	
		int newPosition = (position + i) % sp->length;
		if (sp->flag[newPosition] == Removed)
		{	
			RECORD* newRecord = malloc(sizeof(RECORD));
			newRecord->Age = studentAge;
			newRecord->ID = studentID;
			sp->studentRecord[newPosition] = newRecord;
			sp->flag[newPosition] = Filled;
			sp->count++;
			return;
		}
		else if (sp->flag[newPosition] == Empty)
		{
			RECORD* newRecord = malloc(sizeof(RECORD));
			newRecord->Age = studentAge;
			newRecord->ID = studentID;
			sp->studentRecord[newPosition] = newRecord;
			sp->flag[newPosition] = Filled;
			sp->count++;
			return;
		}	
	}	
}

/* Function: The function uses the search function to find the student record containing the
 * student ID number being passed to it and then frees it. Once freed, the array index is set to NULL and
 * the flag character is set to Removed (2) and the count is decreased to reflect an element
 * being removed from the SET. If the search function does not find the student record containing 
 * the specific ID number to be removed, then the function returns with nothing being deleted from the SET.
 * In either case, the function prints out a message informing the user that a student record has or has
 * not been removed from the current SET data type.
 * 
 * Efficiency: O(n) with O(1) being expected
 * 
 * Return Value: No return value.
 */
void removeElement(SET *sp, int studentID)
{
	assert(sp != NULL);
	printf("Removing record with ID %d in the Data Set.\n",studentID);
	bool found = false;
	int position = searchID(sp,studentID,&found);
	if(found == false)
	{
		printf("Record with ID %d could not be removed from the Data Set.\n",studentID);
	}
	else
	{
		free(sp->studentRecord[position]);
		sp->studentRecord[position] = NULL;
		sp->flag[position] = Removed;
		sp->count--;
		printf("Record with ID %d has been removed from the Data Set.\n",studentID);
	}		
}