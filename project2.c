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
    for (i = 0; i < lines; i++)
    {
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
        char * copyInputString = (char *) malloc(100*sizeof(char));
        char delimiters[]=", ";
        strcpy(copyInputString,inputString);


        printf("inputString[]=%s\n", inputString);
        strcpy(instruct[i][0] , strtok(inputString, delimiters));
        syntax(copyInputString, instruct[i][0]);
        strcpy(instruct[i][1] , strtok(NULL, delimiters));
        strcpy(instruct[i][2] , strtok(NULL, delimiters));
        strcpy(instruct[i][3] , strtok(NULL, delimiters));
//        instruct[i][1] = strtok(NULL, delimiters);
//        instruct[i][2] = strtok(NULL, delimiters);
//        instruct[i][3] = strtok(NULL, delimiters);


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

