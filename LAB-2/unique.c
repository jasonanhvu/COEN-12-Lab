/*
 * File:        unique.c
 *
 * Description: This file contains the main function for testing a set
 *              abstract data type for strings.
 *
 *              The program takes two files as command line arguments, the
 *              second of which is optional. All words in the first file
 *              are inserted into the set and the counts of total words and
 *              total words in the set are printed.  If the second file is
 *              given then all words in the second file are deleted from
 *              the set and the count printed.
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include "set.h"


/* This is sufficient for the test cases in /scratch/coen12. */

# define MAX_SIZE 18000


/*
 * Function:    main
 *
 * Description: Driver function for the test application.
 */

int main(int argc, char *argv[]) {
    FILE *fp;
    char buffer[BUFSIZ];
    SET *unique;
    int words;


    // Check usage and open the first file.  

    if (argc == 1 || argc > 3) {
        fprintf(stderr, "usage: %s file1 [file2]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if ((fp = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "%s: cannot open %s\n", argv[0], argv[1]);
        exit(EXIT_FAILURE);
    }


    // Insert all words into the set.  

    words = 0;
    unique = createSet(MAX_SIZE);

    while (fscanf(fp, "%s", buffer) == 1) {
        words ++;
        addElement(unique, buffer);
    }

    printf("%d total words\n", words);
    printf("%d distinct words\n", numElements(unique));
    fclose(fp);


    /* Try to open the second file. */

    if (argc == 3) {
        if ((fp = fopen(argv[2], "r")) == NULL) {
            fprintf(stderr, "%s: cannot open %s\n", argv[0], argv[2]);
            exit(EXIT_FAILURE);
        }


        // Delete all words in the second file.  

        while (fscanf(fp, "%s", buffer) == 1)
            removeElement(unique, buffer);

        printf("%d remaining words\n", numElements(unique));
    }

    destroySet(unique);
    exit(EXIT_SUCCESS);
}
