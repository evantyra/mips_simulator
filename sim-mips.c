// Authored by Patrick Sullivan
// Tested by Evan Tyra

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <memory.h>

#define SINGLE 1
#define BATCH 0
#define REG_NUM 32

int programCounter;
struct Register *registerArray;
struct inst *instructionMem;
int multiplyTime;
int memoryAccessTime;
int executeTime;
int utilization[5];

enum opcode {ADD,ADDI,SUB,MULT,BEQ,LW,SW,HALT};

struct inst {
    enum opcode op;
    int rs;
    int rt;
    int rd;
    int Imm;
};

struct Latch {
    struct inst heldInstruction;
    int hasUsefulData;
};

struct Register {
    int value;
    int valid;
    int isBeingWrittenTo;
};

void syntax(char * instruction, char * opcode) {
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

    if (strcmp("lw",opcode) == 0 || strcmp("sw",opcode) == 0) {
        assert(commaCount==1);
        assert(paranLeftCount==1);
        assert(paranRightCount==1);
        assert(rightParanPlace>leftParanPlace);
    }
    else if (strcmp("addi",opcode) == 0 || strcmp("add",opcode) == 0 || 
        strcmp("sub",opcode) == 0 || strcmp("mult",opcode) == 0 ||
        strcmp("beq",opcode) == 0) {
        assert( (secondCommaPlace - firstCommaPlace) > 2);
        assert(paranLeftCount == 0);
        assert(paranRightCount == 0);
        assert(commaCount == 2);
    }
}

// Reads line by line and looks for syntax
char *progScanner(char* inputString) {
    char *tempLine = (char *)malloc(100*sizeof(char *));
    char *space = " ";

    char delimiters[] = ", ()";

    char *copyInputString = (char *)malloc(100*sizeof(char *));
    strcpy(copyInputString, inputString);

    // Concatanates each part of the string after we check that it is in the correct format
    memcpy(tempLine, strtok(inputString, delimiters), 100);
    if (strcmp("haltSimulation", tempLine) != 0)
        syntax(copyInputString, tempLine);
    else
        return tempLine;
    memcpy(&tempLine[strlen(tempLine)], space, 100);
    memcpy(&tempLine[strlen(tempLine)], strtok(NULL, delimiters), 100);
    memcpy(&tempLine[strlen(tempLine)], space, 100);
    memcpy(&tempLine[strlen(tempLine)], strtok(NULL, delimiters), 100);
    memcpy(&tempLine[strlen(tempLine)], space, 100);
    memcpy(&tempLine[strlen(tempLine)], strtok(NULL, delimiters), 100);

    return tempLine;
}

// Number of if and else ifs to determine whether an inputted register 
char *registerToNumber(char* registerString) {
    if (strcmp("$0", registerString) == 0 || strcmp("$zero", registerString) == 0)
        return "0";
    else if (strcmp("$1", registerString) == 0 || strcmp("$at", registerString) == 0)
        return "1";
    else if (strcmp("$2", registerString) == 0 || strcmp("$v0", registerString) == 0)
        return "2";
    else if (strcmp("$3", registerString) == 0 || strcmp("$v1", registerString) == 0)
        return "3";
    else if (strcmp("$4", registerString) == 0 || strcmp("$a0", registerString) == 0)
        return "4";
    else if (strcmp("$5", registerString) == 0 || strcmp("$a1", registerString) == 0)
        return "5";
    else if (strcmp("$6", registerString) == 0 || strcmp("$a2", registerString) == 0)
        return "6";
    else if (strcmp("$7", registerString) == 0 || strcmp("$a3", registerString) == 0)
        return "7";
    else if (strcmp("$8", registerString) == 0 || strcmp("$t0", registerString) == 0)
        return "8";
    else if (strcmp("$9", registerString) == 0 || strcmp("$t1", registerString) == 0)
        return "9";
    else if (strcmp("$10", registerString) == 0 || strcmp("$t2", registerString) == 0)
        return "10";
    else if (strcmp("$11", registerString) == 0 || strcmp("$t3", registerString) == 0)
        return "11";
    else if (strcmp("$12", registerString) == 0 || strcmp("$t4", registerString) == 0)
        return "12";
    else if (strcmp("$13", registerString) == 0 || strcmp("$t5", registerString) == 0)
        return "13";
    else if (strcmp("$14", registerString) == 0 || strcmp("$t6", registerString) == 0)
        return "14";
    else if (strcmp("$14", registerString) == 0 || strcmp("$t7", registerString) == 0)
        return "14";
    else if (strcmp("$15", registerString) == 0 || strcmp("$s0", registerString) == 0)
        return "15";
    else if (strcmp("$16", registerString) == 0 || strcmp("$s1", registerString) == 0)
        return "16";
    else if (strcmp("$17", registerString) == 0 || strcmp("$s2", registerString) == 0)
        return "18";
    else if (strcmp("$19", registerString) == 0 || strcmp("$s3", registerString) == 0)
        return "19";
    else if (strcmp("$20", registerString) == 0 || strcmp("$s4", registerString) == 0)
        return "20";
    else if (strcmp("$21", registerString) == 0 || strcmp("$s5", registerString) == 0)
        return "21";
    else if (strcmp("$22", registerString) == 0 || strcmp("$s6", registerString) == 0)
        return "22";
    else if (strcmp("$23", registerString) == 0 || strcmp("$s7", registerString) == 0)
        return "23";
    else if (strcmp("$24", registerString) == 0 || strcmp("$t8", registerString) == 0)
        return "24";
    else if (strcmp("$25", registerString) == 0 || strcmp("$t9", registerString) == 0)
        return "25";
    else if (strcmp("$26", registerString) == 0 || strcmp("$k0", registerString) == 0)
        return "26";
    else if (strcmp("$27", registerString) == 0 || strcmp("$k1", registerString) == 0)
        return "27";
    else if (strcmp("$28", registerString) == 0 || strcmp("$gp", registerString) == 0)
        return "28";
    else if (strcmp("$29", registerString) == 0 || strcmp("$sp", registerString) == 0)
        return "29";
    else if (strcmp("$30", registerString) == 0 || strcmp("$fp", registerString) == 0)
        return "30";
    else if (strcmp("$31", registerString) == 0 || strcmp("$ra", registerString) == 0)
        return "31";
    else {
        printf("Register %s is invalid - Simulator Stopped\n", registerString);
        exit(1);
    }
}

char *regNumberConverter(char* inputString) {
    char delimiters[] = " \n";
    char *space = " ";
    int i;

    char *returnLine = (char *)malloc(100*sizeof(char *));

    // Check for the operation type
    memcpy(returnLine, strtok(inputString, delimiters), 100);

    if (strcmp("sw", returnLine) == 0 || strcmp("lw", returnLine) == 0) {
        // Register
        memcpy(&returnLine[strlen(returnLine)], space, 100);
        memcpy(&returnLine[strlen(returnLine)], registerToNumber(strtok(NULL, delimiters)), 100);

        // Integer
        char *number = strtok(NULL, delimiters);
        for (i = 0; i < strlen(number); i++)
            if (!isdigit(number[i]))
            {
                printf ("Expected element to be number, is not - Simulator Stopped\n");
                exit(1);
            }
        memcpy(&returnLine[strlen(returnLine)], space, 100);
        memcpy(&returnLine[strlen(returnLine)], number, 100);

        // Register
        memcpy(&returnLine[strlen(returnLine)], space, 100);
        memcpy(&returnLine[strlen(returnLine)], registerToNumber(strtok(NULL, delimiters)), 100);

        return returnLine;
    }
    else if (strcmp("addi", returnLine) == 0 || strcmp("beq", returnLine) == 0) {
        // Register
        memcpy(&returnLine[strlen(returnLine)], space, 100);
        memcpy(&returnLine[strlen(returnLine)], registerToNumber(strtok(NULL, delimiters)), 100);

        // Register
        memcpy(&returnLine[strlen(returnLine)], space, 100);
        memcpy(&returnLine[strlen(returnLine)], registerToNumber(strtok(NULL, delimiters)), 100);

        // Integer
        char *number = strtok(NULL, delimiters);
        for (i = 0; i < strlen(number); i++)
            if (!isdigit(number[i]))
            {
                if (i == 0 && number[i] == '-')
                    continue;
                printf ("Expected element to be number, is not - Simulator Stopped\n");
                exit(1);
            }
        memcpy(&returnLine[strlen(returnLine)], space, 100);
        memcpy(&returnLine[strlen(returnLine)], number, 100);

        return returnLine;
    }
    else if (strcmp("haltSimulation", returnLine) == 0)
        return returnLine;

    // Register
    memcpy(&returnLine[strlen(returnLine)], space, 100);
    memcpy(&returnLine[strlen(returnLine)], registerToNumber(strtok(NULL, delimiters)), 100);

    // Register
    memcpy(&returnLine[strlen(returnLine)], space, 100);
    memcpy(&returnLine[strlen(returnLine)], registerToNumber(strtok(NULL, delimiters)), 100);

    // Register
    memcpy(&returnLine[strlen(returnLine)], space, 100);
    memcpy(&returnLine[strlen(returnLine)], registerToNumber(strtok(NULL, delimiters)), 100);

    return returnLine;
}

struct inst parser(char* inputString) {
    struct inst parsedInstruction;
    char delimiters[] = " ";
    int Imm;

    char *currentElement = (char *)malloc(100*sizeof(char *));
    memcpy(currentElement, strtok(inputString, delimiters), 100);


    if (strcmp(currentElement, "add") == 0)
        parsedInstruction.op = ADD;
    else if (strcmp(currentElement, "addi") == 0)
        parsedInstruction.op = ADDI;
    else if (strcmp(currentElement, "sub") == 0)
        parsedInstruction.op = SUB;
    else if (strcmp(currentElement, "mult") == 0)
        parsedInstruction.op = MULT;
    else if (strcmp(currentElement, "beq") == 0)
        parsedInstruction.op = BEQ;
    else if (strcmp(currentElement, "lw") == 0)
        parsedInstruction.op = LW;
    else if (strcmp(currentElement, "sw") == 0)
        parsedInstruction.op = SW;
    else if (strcmp(currentElement, "haltSimulation") == 0) {
        parsedInstruction.op = HALT;
        parsedInstruction.rd = 0;
        parsedInstruction.rs = 0;
        parsedInstruction.rt = 0;
        parsedInstruction.Imm = 0;
    }

    if (parsedInstruction.op == ADD ||
        parsedInstruction.op == SUB ||
        parsedInstruction.op == MULT) {
        parsedInstruction.rd = atoi(strtok(NULL, delimiters));
        parsedInstruction.rs = atoi(strtok(NULL, delimiters));
        parsedInstruction.rt = atoi(strtok(NULL, delimiters));
        parsedInstruction.Imm = 0;
    }
    else if (parsedInstruction.op == ADDI || parsedInstruction.op == BEQ) {
        parsedInstruction.rt = atoi(strtok(NULL, delimiters));
        parsedInstruction.rs = atoi(strtok(NULL, delimiters));
        parsedInstruction.Imm = atoi(strtok(NULL, delimiters));
        if (parsedInstruction.op == ADDI)
            if (parsedInstruction.Imm > 32767 || parsedInstruction.Imm < -32768){
                printf("Integer added number greater than 16 bits - Simulator Stopped\n");
                exit(1);
            }
        parsedInstruction.rd = 0;
    }
    else if (parsedInstruction.op == LW || parsedInstruction.op == SW) {
        parsedInstruction.rt = atoi(strtok(NULL, delimiters));
        parsedInstruction.Imm = atoi(strtok(NULL, delimiters));
        parsedInstruction.rs = atoi(strtok(NULL, delimiters));
        parsedInstruction.rd = 0;
    }

    return parsedInstruction;
}

void WB() {

}

void MEM() {

}

void EX() {

}

void ID() {

}

void IF() {

}

int main(int argc, char *argv[])
{
    // Initiation of variables
    FILE *instructionFile;
    FILE *outputFile;
    char ** instructions;
    int sim_mode;
    int sim_counter = 0;
    int i;

    // Argument input checking
    if(argc==7){
        if(strcmp("-s",argv[1]) == 0){
            sim_mode=SINGLE;
        }
        else if(strcmp("-b",argv[1]) == 0){
            sim_mode=BATCH;
        }
        else{
            printf("Wrong sim mode chosen\n");
            exit(0);
        }
        
        multiplyTime = atoi(argv[2]);
        executeTime = atoi(argv[3]);
        memoryAccessTime = atoi(argv[4]);
        instructionFile = fopen(argv[5],"r");
        outputFile = fopen(argv[6],"w");
        
    }
    
    else{
        printf("Usage: ./sim-mips -s m n c input_name output_name (single-sysle mode)\n or \n ./sim-mips -b m n c input_name  output_name(batch mode)\n");
        printf("m,n,c stand for number of cycles needed by multiplication, other operation, and memory access, respectively\n");
        exit(0);
    }
    if(instructionFile == NULL){
        printf("Unable to open input or output file\n");
        exit(0);
    }
    if(outputFile == NULL){
        printf("Cannot create output file\n");
        exit(0);
    }

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

    // Initiates Register array to be all invalid and all not being written to
    registerArray= malloc(REG_NUM*sizeof(struct Register));
    for (i = 0; i < REG_NUM; i++) {
        registerArray[i].value = 0;
        registerArray[i].valid = 0;
        registerArray[i].isBeingWrittenTo = 0;
    }
    registerArray[0].valid = 1;

    // Initiation of instruction memory in accordance to number of instructions in read file
    instructionMem = malloc(lineCount*sizeof(struct inst));
    for (i = 0; i < lineCount; i++) {
        instructions[i] = regNumberConverter(instructions[i]);
        instructionMem[i] = parser(instructions[i]);
        // printf("Instruction = %d %d %d %d %d \n", instructionMem[i].op, instructionMem[i].rs,
        //        instructionMem[i].rt, instructionMem[i].rd, instructionMem[i].Imm);
    }

    // Latch and utilization counter initialization
    for (i = 0; i < 5; i++)
        utilization[i] = 0;

    while (programCounter < lineCount * 4) {

        // Waits for an enter before continuing during single mode
        if (sim_mode == SINGLE) {
            printf("Cycle: %d \n",sim_counter);

            for (i = 1; i < REG_NUM; i++){
                printf("%d  ", registerArray[i].value);
            }

            printf("%d\n", programCounter);
            programCounter++; // DEBUG WILL BE CHANGED
            sim_counter++;
            printf("press ENTER to continue\n");
            while(getchar() != '\n');
        }
    }

    if(sim_mode == BATCH){
        fprintf(outputFile, "program name: %s\n", argv[5]);
        fprintf(outputFile, "stage utilization: %f  %f  %f  %f  %f \n",
                            utilization[0], utilization[1], utilization[2],
                            utilization[3], utilization[4]);
        
        fprintf(outputFile,"register values ");
        for (i = 1; i < REG_NUM; i++){
            fprintf(outputFile, "%d  ", registerArray[i].value);
        }
        fprintf(outputFile, "%d\n", programCounter);    // DEBUG -- THIS MAY BE CHANGED
    
    }

    //close input and output files at the end of the simulation
    fclose(instructionFile);
    fclose(outputFile);

    return 0;
}

