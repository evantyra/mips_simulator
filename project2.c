// Authored by Patrick Sullivan
// Tested by Evan Tyra

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>
int programCounter;
int canFetch;
int busyRegister [32];
struct Register A;
char *** instruct;

int lineCount;

void syntax(char * str){
int commaCount;
int paranCount;

}

void progScanner()
{
    FILE *instructionFile;
    instructionFile = fopen("instructions","r");
    assert (instructionFile != NULL);

    char * inputString = (char *) malloc(100*sizeof(char));

    int lines = 0;
    char newLine;
    while(!feof(instructionFile))
    {
        newLine = fgetc(instructionFile);
        if(newLine == '\n')
        {
            lines++;
        }
    }
    lineCount = lines;

    int i = 0;
    int j = 0;
    instruct = (char ***)malloc(lines*sizeof(char *));
    for (i = 0; i < lines; i++) {
        *(instruct+i) = (char **)malloc(4*sizeof(char *));
        for(j = 0; j < 4; j++)
        {
            *(instruct[i] + j) = (char *)malloc(100*sizeof(char *));
        }
    }

    rewind(instructionFile);
    i=0;
    while(fgets(inputString, 100, instructionFile)>0)
    {
        syntax(inputString);
        char delimiters[]=", ";


        printf("inputString[]=%s\n", inputString);
        strcpy(instruct[i][0] , strtok(inputString, delimiters));
        strcpy(instruct[i][1] , strtok(NULL, delimiters));
        strcpy(instruct[i][2] , strtok(NULL, delimiters));
        strcpy(instruct[i][3] , strtok(NULL, delimiters));
//        instruct[i][1] = strtok(NULL, delimiters);
//        instruct[i][2] = strtok(NULL, delimiters);
//        instruct[i][3] = strtok(NULL, delimiters);

        printf("field 1 = %s field 2 = %s field 3 = %s field 4 = %s \n",instruct[i][0], instruct[i][1], instruct[i][2],instruct[i][3]);
        printf(" the value of i be %i \n",i);
        i++;
    }

//    for(i=0; i<lines; i++)
//    {
//        printf("field 1  = %s field 2 = %s field 3 = %s field 4 = %s \n",instruct[i][0], instruct[i][1], instruct[i][2],instruct[i][3]);
//    }

    printf("line count of file = %i \n",lines);


}

struct Latch

{

    int rs;
    int rt;
    int rd;
    int usefulCycleCount;
    int cyclesCountDown;
    int hasUsefulData;





};

struct Register
{
    int registerIndex;
    int registerValue;
};

int main()
{
    progScanner();
    int i;
     for(i=0; i<lineCount; i++)
    {
        printf("field 1  = %s field 2 = %s field 3 = %s field 4 = %s \n",instruct[i][0], instruct[i][1], instruct[i][2],instruct[i][3]);
    }


    return 0;
}

