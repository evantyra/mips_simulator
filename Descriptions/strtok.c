#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>


int main(void) {
    int i;
    char delimiters[]=" ";  // here, we chose a comma as the only delimiter.
                            // you can expand this string with other delimiters
                            //     as well.

    char ** instructionFields;
    char inputString[] = "   add ,,,   $s1, $s2, $t1";

    instructionFields = (char **)malloc(100*sizeof(char *));
    
    for (i=0; i<15; i++)
       *(instructionFields+i) = (char *) malloc(100*sizeof(char *));

    for (i = 0; i < 4; i++) {
        if (i == 0)
            instructionFields[i] = strtok(inputString, delimiters);
        else
            instructionFields[i] = strtok(NULL, delimiters);
        
        printf("%s\n",instructionFields[i]);
    }
}