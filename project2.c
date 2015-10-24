// Authored by Patrick Sullivan
// Tested by Evan Tyra

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <memory.h>

int programCounter;
int canFetch;
int busyRegister [32];
struct Register A;

int lineCount;

void syntax(char * str, char * str2){
int commaCount;
int paranCount;

}

// Reads line by line and looks for syntax
char *progScanner(char* inputString)
{
    char *tempLine; 
    tempLine = (char *)malloc(100*sizeof(char *));
    char *space = " ";

    char delimiters[]=", ";

    char *copyInputString;
    strcopy(copyInputString, inputString);

    printf("inputString[]=%s\n", inputString);
    tempLine = strtok(inputString, delimiters);
    syntax(tempLine, copyInputString);
    tempLine = strcat(tempLine, space);
    tempLine = strcat(tempLine, strtok(NULL, delimiters));
    tempLine = strcat(tempLine, space);
    tempLine = strcat(tempLine, strtok(NULL, delimiters));
    tempLine = strcat(tempLine, space);
    tempLine = strcat(tempLine, strtok(NULL, delimiters));

    printf("Templine value = %s\n", tempLine);

    free(tempLine);
    return tempLine;
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
    // Initiation of variables
    FILE *instructionFile;
    char ** instructions;

    // Open instructionFile, if not there, 
    instructionFile = fopen("instructions","r");
    assert (instructionFile != NULL);

    // Reads through file once to check for number of lines
    int lines = 0;
    char *newLine;
    while(!feof(instructionFile))
    {
        fgets(newLine, 100, instructionFile);
        lines++;
    }
    lineCount = lines;
    rewind(instructionFile);

    // Initiates double array in accordance to number of lines in the file
    int i = 0;
    int j = 0;
    instructions = (char **)malloc(lines*sizeof(char *));
    for (i = 0; i < lines; i++) {
        *(instructions+i) = (char *)malloc(100*sizeof(char *));
    }

    // Read through file again and check for syntax errors then 
    int currentLine = 0;
    while(!feof(instructionFile))
    {
        newLine = fgets(newLine, 100, instructionFile);
        strcopy(instructions[i], progScanner(newLine));
        currentLine++;
    }

     for(i=0; i<lineCount; i++)
    {
        printf("field 1  = %s field 2 = %s field 3 = %s field 4 = %s \n",instructions[i][0], instructions[i][1], instructions[i][2],instructions[i][3]);
    }


    return 0;
}

