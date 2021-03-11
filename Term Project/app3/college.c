/*
 * File:        college.c
 *
 * Description: This file contains the main function for testing a LIST
 *              abstract data type for student records.
 *
 * 				The program creates a sorted circular doubly linked LIST ADT and 
 * 				inserts 1000 student records into the LIST with random ages varying 
 * 				from 18 to 30 years of age and ID numbers varying from 1 to 
 * 				approximately 2000 (with each student having a unique ID
 * 				number). Because the LIST is sorted in ascending order based
 * 				on a student's age, the maximum age gap is easy to calculate
 *				among a large group of students. Once this value is calculated,
 *				the result is then printed to the screen. After this, the program
 *				generates a random age (from 18-30) and a random ID (from 1 
 *				to 2000) and calls the searchAge and searchID functions to 
 *				find the randomized age and ID number within the LIST abstract 
 *				data structure. If these search functions are successful, they will
 *				print out a message saying that the given age and/or ID was found
 *				in the given Data Set. Otherwise, the program will print out messages
 *				saying that either one or both of these function were unable to find
 *				the randomized age or ID number. After both of these searches have 
 *				completed, another randomized student ID is generated (from 1 to 2000) 
 *				and is searched for and removed from the given Data Set. Either if the 
 *				specific record is found or not, the program will print a message saying
 *				if the deletion was sucessfull or not.  Finally, after all operations have
 *				completed, the memory making up the LIST is freed and the program ends.
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
    
struct list
{	 
	int count;
	struct node *head;
};

struct node
{
	RECORD studentRecord;
	struct node *next;
	struct node *prev;
}; 

int main()
{
	LIST* dataList;
	dataList = createList();
	printf("Data Set Created\n");
	srand ((int) time (NULL));
	int previousID = 0;
	for(int i = 0; i <1000; i++)
		{
			int studentAge = rand()%(13) +18;
		

			int ID = rand()%2 + 1;
			previousID = previousID + ID;
	
			addElement(dataList,studentAge,previousID);
		}
	printf("All records successfully inserted into Data Set.\n");
	int studentAgeGap = maxAgeGap(dataList);
	printf("The maximum student age gap within the Data Set is %d years old\n",studentAgeGap); 
	int testID = rand()%(1999)+1;
	int testAge = rand()%(12)+18;
	searchID(dataList,testID);
	searchAge(dataList,testAge);
	int removeID = rand()%(1999)+1;
	removeElement(dataList,removeID);	
	printf("All operations complete, freeing memory of Data Set.\n");
	destroyList(dataList);	
}