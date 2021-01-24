/* 
    HOW TO COMPILE and EXECUTE PROPERLY:
    1) Save count.c
    2) Change directory to /scratch/code
    3) Compile by running "gcc <program file name>" so in this case: "gcc count.c"
    4) Run "./a.out /scratch/coen12/books/Macbeth.txt" to get the total amount of words in the text file
*/

/* LIST OF TEXT FILES TO READ FROM:
	Bible.txt    GreenEggsAndHam.txt         Macbeth.txt  TheCountOfMonteCristo.txt  TheWarOfTheWorlds.txt  TwentyThousandLeagues.txt
	Genesis.txt  HoundOfTheBaskervilles.txt  README       TheSecretGarden.txt        TreasureIsland.txt
*/

//include necessary libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
//Defines maximum word length to be 30 characters for each individual word in the text file.
#define MAX_WORD_LENGTH 30

int main(int fileInput, char*amountOfChars[]) {

	char word[MAX_WORD_LENGTH+1];
	
	//Creates a file pointer that points to the file we are reading from.
	FILE *fileBeingPointed;

	//Creates int var to equal number of total words. Initialize with 0 due to starting out with nothing.
	int amountOfWords = 0;	

	//If only one parameter is used (e.g. a.exe) => end program
	if (fileInput == 1) {
		printf("The name of the file is missing.\n");
		return -1;
	} else if (fileBeingPointed == NULL)  { //If the file can't open, print error message =>
		printf("Error opening up text file");
		return -1;
	}
	
	//If user entered in the name of a text file in the command line, execute the program. 
	fileBeingPointed = fopen(amountOfChars[1], "r");

	//Reads the text file and puts each string into the "word" variable. 
	//As long as the word is 30 characters or less, increase word total to hold word from text file 

	while(fscanf(fileBeingPointed,"%s", word) > 0) {	
		amountOfWords++;
	}
	
	//Closes the file at this point of the code
	fclose(fileBeingPointed);

	//Prints out the total number of words in the text file in the terminal for user to view
	printf("%i total words\n", amountOfWords);
  
    return 0;
}	