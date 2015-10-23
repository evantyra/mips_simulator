// Evan Tyra & Patrick Sullivan

// List the full names of ALL group members at the top of your code.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
//feel free to add here any additional library names you may need 
#define SINGLE 1
#define BATCH 0
#define REG_NUM 32

/*
	Notes:
		*** Do everything in pseudocode first ***
		For reading of file:
			- Read string using fgets()
			- Feed each line into a parser
			- Parser uses strtok and a delimiter of ", " (space and comma)
			- Read and use code from token.c
			- When parsing registers check all known register values to string,
			if none match given string from delimiter, print error and exit(0)
			- If syntax 8(%t0) --> or anything like this we need to make sure
			the grammar is correct, do getchar and find any wrong sequence and
			exit(0) if there is any.
		Mimicking Parallel Programs
			- Pipeline order: IF -> ID -> EX -> MEM -> WB
			- Use latches in between pipeline stages, producer and consumer stages
			- Use these latches to make checks
			- Do in order from right to left
			- Look over notes from last year
		Register Write Hazards
			- Possibly create struct to signal whether an instruction is trying
			to write to the given register -> valid bit
			- Keep instruction at ID stage until register is valid
*/

char *progScanner(char *line) {
    char delimiters[]=" ";
    int commas;
    

    line = strtok(line, delimiters);
    printf("inputString[]=%s\n", inputString);
    instructionFields[1] = strtok(NULL, delimiters);
    printf("inputString[]=%s\n", inputString);
    instructionFields[2] = strtok(NULL, delimiters);
    printf("inputString[]=%s\n", inputString);
    printf("%s \n%s \n%s \n", 
           instructionFields[0], instructionFields[1], instructionFields[2]);
}

main (int argc, char *argv[]){
	int sim_mode=0;//mode flag, 1 for single-cycle, 0 for batch
	int c,m,n;
	int i;//for loop counter
	long mips_reg[REG_NUM];
	long pgm_c=0;//program counter
	long sim_cycle=0;//simulation cycle counter
	//define your own counter for the usage of each pipeline stage here
	
	int test_counter=0;
	FILE *input=NULL;
	FILE *output=NULL;
	printf("The arguments are:");
	
	for(i=1;i<argc;i++){
		printf("%s ",argv[i]);
	}
	printf("\n");
	if(argc==7){
		if(strcmp("-s",argv[1])==0){
			sim_mode=SINGLE;
		}
		else if(strcmp("-b",argv[1])==0){
			sim_mode=BATCH;
		}
		else{
			printf("Wrong sim mode chosen\n");
			exit(0);
		}
		
		m=atoi(argv[2]);
		n=atoi(argv[3]);
		c=atoi(argv[4]);
		input=fopen(argv[5],"r");
		output=fopen(argv[6],"w");
		
	}
	
	else{
		printf("Usage: ./sim-mips -s m n c input_name output_name (single-sysle mode)\n or \n ./sim-mips -b m n c input_name  output_name(batch mode)\n");
		printf("m,n,c stand for number of cycles needed by multiplication, other operation, and memory access, respectively\n");
		exit(0);
	}
	if(input==NULL){
		printf("Unable to open input or output file\n");
		exit(0);
	}
	if(output==NULL){
		printf("Cannot create output file\n");
		exit(0);
	}
	//initialize registers and program counter
	if(sim_mode==1){
		for (i=0;i<REG_NUM;i++){
			mips_reg[i]=0;
		}
	}
	
	//start your code from here
}