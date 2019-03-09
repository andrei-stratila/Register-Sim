#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "instructions.h"


char INPUT_filename[100];
char OUTPUT_filename[100];

//Timeout(running time) 
void timeout(clock_t begin_time){
	clock_t end_time = clock();
	double time = (double)(end_time - begin_time)/CLOCKS_PER_SEC;
	if(time > 2.0){
		exit(0);
	}
}

void printOutput(int N, proc *cpu){
	FILE *file;
	file = fopen(OUTPUT_filename, "w");
	if(file == NULL){
		printf("Can't open the file...");
		return;
	}
	int index, regCount;
	for(index = 0; index < N; index++){
		for(regCount = 0; regCount < 32; regCount++)
			if(cpu[index].reg[regCount] != 0)
				fprintf(file, "%d ", cpu[index].reg[regCount]);
		fprintf(file, "\n");
	}
	fclose(file);
}

int convertRegToInt(char *s){
	int val = -1, length = strlen(s);
	if(length == 3){
		val = (int)(s[1] - '0') * 10 + (int)(s[2] - '0'); 
	}
	else if(length == 2)
		val = (int)(s[1] - '0');
	return val;
}

int convertStringToInt(char *s){
	int val = 0, length = strlen(s), negativeNum = 0;
	if(s[0] == '-')
		negativeNum = 1;
	int i;
	for(i = negativeNum; i < length; i++)
		val = val * 10 + (int)(s[i] - '0');
	if(negativeNum == 1)
		val = -val;
	return val;
}

void initCPU(int N, proc *cpu){
	int index, regCount;
	for(index = 0; index < N; index++){
		cpu[index].reg[0] = index;
		for(regCount = 1; regCount < 32; regCount++)
			cpu[index].reg[regCount] = 0;
	}
}

void readInstruction(int *N, proc *cpu, int *N_instr, instruction *instr){
	FILE *file;
	file = fopen(INPUT_filename, "r");
	if(file == NULL){
		printf("Can't open the file...");
		return;
	}
	fscanf(file, "%d", &(*N));
	int i = 0;
	char command[5], X[5], Y[50];
	while(fscanf(file,"%s", command) == 1){
		strcpy(instr[i].command ,command);
		if(strcmp(command, "snd") == 0 || strcmp(command, "rcv") == 0){
			fscanf(file, "%s", X);
			if(X[0] == 'R'){
				instr[i].regX = convertRegToInt(X);
				instr[i].valX = -1;
			}
			else{
				instr[i].valX = convertStringToInt(X);
				instr[i].regX = -1;
			}
			instr[i].regY = -1;
			instr[i].valY = -1;
		}
		else{
			fscanf(file, "%s%s", X, Y);
			instr[i].regX = convertRegToInt(X);
			if(Y[0] == 'R'){
				instr[i].regY = convertRegToInt(Y);
				instr[i].valY = -1;
			}
			else{
				instr[i].valY = convertStringToInt(Y);
				instr[i].regY = -1;
			}
			instr[i].valX = -1;
		}
	
		i++;
	}
	*N_instr = i;
	fclose(file);
}

void executeInstr(int N, proc *cpu, int N_instr, instruction *instr){
	int i;
	clock_t begin_time = clock();	
	queue *begin = NULL, *end = NULL;
	for(i = 0; i < N_instr; i++){
		timeout(begin_time);
		if(strcmp(instr[i].command, "set") == 0)
			setInstr(N, cpu, instr[i].regX, instr[i].regY, instr[i].valY);
		else if(strcmp(instr[i].command, "add") == 0)
			addInstr(N, cpu, instr[i].regX, instr[i].regY, instr[i].valY);
		else if(strcmp(instr[i].command, "mul") == 0)
			mulInstr(N, cpu, instr[i].regX, instr[i].regY, instr[i].valY);
		else if(strcmp(instr[i].command, "mod") == 0)
			modInstr(N, cpu, instr[i].regX, instr[i].regY, instr[i].valY);
		else if(strcmp(instr[i].command, "jgz") == 0)
			i = i - 1 + jgzInstr(N, cpu, instr[i].regX, instr[i].regY, instr[i].valY);
		else if(strcmp(instr[i].command, "snd") == 0){
			if(isEmpty(&end) == 1)
				initQueue(&begin, &end);
			sndInstr(N, cpu, instr[i].regX, instr[i].valX, &begin, &end);
		}
		else if(strcmp(instr[i].command, "rcv") == 0){
			if(isEmpty(&end) == 1){
				printOutput(N, cpu);
				exit(0);
			}
			rcvInstr(N, cpu, instr[i].regX, &begin, &end);
		}
	}
}

int main(int argc, char **argv){
	if(argc < 2){
		printf("%s\n", "Run executable files with input and output paths as arguments...");
		return 0;
	}
	strcpy(INPUT_filename, argv[1]);
	strcpy(OUTPUT_filename, argv[2]);

	proc *cpu = NULL;
	instruction instr[100]; 
	int N = 0, N_instr = 0;

	readInstruction(&N, cpu, &N_instr, instr);
	cpu = (proc *) calloc(N, sizeof(proc));
	initCPU(N, cpu);
	
	executeInstr(N, cpu, N_instr, instr);
	
	printOutput(N, cpu);
	free(cpu);
	return 0;
}