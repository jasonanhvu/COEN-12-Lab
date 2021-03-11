/*
 * File:        college.c
 *
 * Description: This file contains the main function for testing a SET
 *              abstract data type for student records in a college.
 *
 * 				The program creates an array of student record pointers (with each 
 * 				record containing a student's ID number and age) both held together in
 * 				one structure. The program then inserts 1000 student records into 
 * 				the SET with random ages varying from 18 to 30 years of age and ID 
 * 				numbers varying from 1 to approximately 2000 (with each student having
 * 				a unique ID number). Because the application requires frequent searches,
 * 				the 1000 student records will be put into a hash table to allow for 
 * 				faster searching and retrieval of records. After the SET is created 
 * 				and 1000 student records are successfully inserted, the program
 *				generates a random ID (from 1 to 2000) and calls the searchID function 
 *				to find the randomized ID number within the SET data structure. If this
 *				search function is successful, it will print out a message saying that 
 *				the given ID number was found in the given Data Set, otherwise, the program
 *				will print out a message saying that it could not find the randomized ID number
 *				in the given SET. After the search operation is complete, the program again 
 *				generates a random ID number (from 1 to 2000) and tries to delete the record 
 *				containg the specific ID number. Finally, after all operations have completed, 
 *				the memory making up the SET is freed and the program ends.
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <time.h>
# include "dataset.h"



struct record
{
	int ID;

	int Age;
};



struct set
{
	int count;
	
	int length;

	RECORD** studentRecord;
	
	char *flag;
}; 


int main()
{
	SET* dataSet;
	dataSet = createSet(3000);
	printf("Data Set Created\n");
	srand ((int) time (NULL));
	int previousID = 0;
	for(int i = 0; i <1000; i++)
		{
			int studentAge = rand()%(13) + 18;
			int ID = rand()%2 + 1;
			previousID = previousID + ID;
			addElement(dataSet,previousID,studentAge);
		}
	printf("All records successfully inserted into Data Set.\n");
	int testID = rand()%(1999)+1;
	bool found = false;
	int searchLocation = searchID(dataSet, testID, &found);
	int removeID = rand()%(1999)+1;
	removeElement(dataSet,removeID);
	printf("All operations complete, freeing memory of Data Set.\n");
	destroySet(dataSet);	
}