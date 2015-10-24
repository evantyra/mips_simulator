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

void syntax(char * instruction, char * opcode)
{
    printf("reached \n");
    printf("string length = %i \n",strlen(instruction));
    printf("instruction to syntax = %s \n",instruction);
    int i;
    int commaCount=0;
    int paranLeftCount=0;
    int paranRightCount=0;
    for(i=0; i<strlen(instruction); i++)
    {
        if(instruction[i]==',')
        {
            commaCount++;

        }

        else if(instruction[i]=='(')
        {
            paranLeftCount++;
        }

        else if(instruction[i]==')')
        {
            paranRightCount++;
        }


    }
    printf(" opcode = %s \n",opcode);
    printf(" comma count = %i \n",commaCount);
    printf(" paran left count = %i \n", paranLeftCount);
    printf(" paran right count = %i \n", paranRightCount);
    if (strcmp("lw",opcode)==0||strcmp("sw",opcode)==0)
    {
        assert(commaCount==1);
        assert(paranLeftCount==1);
        assert(paranRightCount==1);

    }
    if (strcmp("addi",opcode)==0||strcmp("add",opcode)==0||strcmp("sub",opcode)==0||strcmp("mult",opcode)==0||strcmp("beq",opcode)==0)
    {
        assert(paranLeftCount==0);
        assert(paranRightCount==0);
        assert(commaCount==2);
    }
}

// Reads line by line and looks for syntax
char *progScanner(char* inputString)
{
    char *tempLine;
    tempLine = (char *)malloc(100*sizeof(char *));
    char *space = " ";

    char delimiters[]=", ";

    char *copyInputString;
    strcpy(copyInputString, inputString);

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
        strcpy(instructions[i], progScanner(newLine));
        currentLine++;
    }

     for(i=0; i<lineCount; i++)

    {
        printf("Line = %s \n", instructions[i]);
    }


    return 0;
}

