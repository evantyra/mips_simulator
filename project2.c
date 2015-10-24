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

struct Latch
{
    int rs;
    int rt;
    int rd;
    int usefulCycleCount;
    int cyclesCountDown;
    int hasUsefulData;
};

void syntax(char * instruction, char * opcode)
{
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

    char delimiters[]=", ()";

    char *copyInputString;
    strcpy(copyInputString, inputString);

    // Concatanates each part of the string after we check that it is in the correct format
    memcpy(tempLine, strtok(inputString, delimiters), 100);
    syntax(copyInputString, tempLine);
    memcpy(&tempLine[strlen(tempLine)], space, 100);
    memcpy(&tempLine[strlen(tempLine)], strtok(NULL, delimiters), 100);
    memcpy(&tempLine[strlen(tempLine)], space, 100);
    memcpy(&tempLine[strlen(tempLine)], strtok(NULL, delimiters), 100);
    memcpy(&tempLine[strlen(tempLine)], space, 100);
    memcpy(&tempLine[strlen(tempLine)], strtok(NULL, delimiters), 100);

    return tempLine;
}

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
    int lineCount = 0;
    char *newLine;
    newLine = (char *)malloc(100*sizeof(char *));
    while(!feof(instructionFile))
    {
        fgets(newLine, 100, instructionFile);
        lineCount++;
    }
    lineCount = lineCount;
    rewind(instructionFile);

    // Initiates double array in accordance to number of lineCount in the file
    int i = 0;
    int j = 0;
    instructions = (char **)malloc(lineCount*sizeof(char *));
    for (i = 0; i < lineCount; i++) {
        *(instructions+i) = (char *)malloc(100*sizeof(char *));
    }

    // Read through file again and check for syntax errors then
    int currentLine = 0;
    while(fgets(newLine, 100, instructionFile) != NULL)
    {
        if (newLine != NULL) {
            instructions[currentLine] = progScanner(newLine);
            currentLine++;
        }
    }

    return 0;
}

