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
int IFMemCountDown;
int EXCountDown;
const int multiplyTime;
const int memoryAccessTime;



struct Latch
{
    char * opcode;
    int rs;
    int rt;
    int rd;

    int hasUsefulData;
};


struct Register
{
    int registerIndex;
    int registerValue;
};

struct RegisterArray
{

    struct Register registers[32];

};

void syntax(char * instruction, char * opcode)
{
    int i;
    int commaCount = 0;
    int paranLeftCount = 0;
    int paranRightCount = 0;
    int leftParanPlace;
    int rightParanPlace;
    int firstCommaPlace=0;
    int secondCommaPlace=0;

    assert(instruction != NULL);
    assert(instruction[0] !=',');
    assert(opcode != NULL);

    for(i = 0; i < strlen(instruction); i++)
    {
        if(instruction[i] == ',') {
                if(firstCommaPlace==0){
                firstCommaPlace = i;
            }
            else if (firstCommaPlace!= 0 && secondCommaPlace == 0){
                secondCommaPlace = i;
            }

            commaCount++;
        }

        else if(instruction[i] == '(')
        {
            paranLeftCount++;
            leftParanPlace = i;
        }
        else if(instruction[i] == ')') {
            paranRightCount++;
             rightParanPlace = i;
        }
    }
    printf(" opcode = %s \n", opcode);
    printf(" comma count = %i \n", commaCount);
    printf(" paran left count = %i \n", paranLeftCount);
    printf(" paran right count = %i \n", paranRightCount);

    if (strcmp("lw",opcode) == 0 || strcmp("sw",opcode) == 0)
    {
        assert(commaCount==1);
        assert(paranLeftCount==1);
        assert(paranRightCount==1);
        assert(rightParanPlace>leftParanPlace);
    }
    if (strcmp("addi",opcode) == 0 || strcmp("add",opcode) == 0 ||
        strcmp("sub",opcode) == 0 || strcmp("mult",opcode) == 0 ||
        strcmp("beq",opcode) == 0)
    {
        assert( (rightParanPlace - leftParanPlace) > 2);
        assert(paranLeftCount == 0);
        assert(paranRightCount == 0);
        assert(commaCount == 2);
    }
}

// Reads line by line and looks for syntax
char *progScanner(char* inputString)
{
    char *tempLine;
    tempLine = (char *)malloc(100*sizeof(char *));
    char *space = " ";

    char delimiters[]=", ()";

    char *copyInputString = (char *)malloc(100*sizeof(char *));
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

    for (i = 0; i < lineCount; i++) {
        printf("%s\n", instructions[i]);
    }

    return 0;
}

