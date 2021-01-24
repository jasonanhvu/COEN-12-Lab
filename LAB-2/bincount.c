/*
 * File:        bincount.c
 *
 * Description: This file contains the main function for testing a set
 *              abstract data type for strings.
 *
 *              The program takes a single file as a command line argument.
 *              An array of sets is used to count the number of words of
 *              varying lengths.  The counts of the number of distinct
 *              words of each length are printed.
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include "set.h"


/* This is sufficient for the test cases in /scratch/coen12. */

# define MAX_UNIQUE 18000
# define MAX_WORD_LENGTH 30
# define MAX_DISPLAYED 20


/*
 * Function:    main
 *
 * Description: Driver function for the test application.
 */

int main(int argc, char *argv[]) {
    FILE *fp;
    char buffer[MAX_WORD_LENGTH];
    SET *sets[MAX_WORD_LENGTH];
    int i;


    /* Check usage and open the file. */

    if (argc != 2) {
        fprintf(stderr, "usage: %s file1 [file2]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if ((fp = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "%s: cannot open %s\n", argv[0], argv[1]);
        exit(EXIT_FAILURE);
    }


    /* Insert all words into the set of the appropriate length. 
     * Big-O Notation: O(n)
     */

    for (i = 0; i < MAX_WORD_LENGTH; i ++)
	sets[i] = createSet(MAX_UNIQUE);

    while (fscanf(fp, "%s", buffer) == 1)
        addElement(sets[strlen(buffer) - 1], buffer);

    fclose(fp);


    /* Display the counts for each word length. 
     * Big-O Notation: O(1)
     */

    for (i = 0; i < MAX_DISPLAYED; i ++) {
        printf("%5d distinct words ", numElements(sets[i]));
        printf("of length %d\n", i + 1);
    }

    exit(EXIT_SUCCESS);
}
