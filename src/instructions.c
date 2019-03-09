#include "instructions.h"

void setInstr(int N, proc *cpu, int regX, int regY, int valY){
	int i;
	if(regY == -1)
		for(i = 0; i < N; i++)
			cpu[i].reg[regX] = valY; 
	else
		for(i = 0; i < N; i++)
			cpu[i].reg[regX] = cpu[i].reg[regY];
}

void addInstr(int N, proc *cpu, int regX, int regY, int valY){
	int i;
	if(regY == -1)
		for(i = 0; i < N; i++)
			cpu[i].reg[regX] = cpu[i].reg[regX] + valY; 
	else
		for(i = 0; i < N; i++)
			cpu[i].reg[regX] = cpu[i].reg[regX] + cpu[i].reg[regY];
}

void mulInstr(int N, proc *cpu, int regX, int regY, int valY){
	int i;
	if(regY == -1)
		for(i = 0; i < N; i++)
			cpu[i].reg[regX] = cpu[i].reg[regX] * valY; 
	else
		for(i = 0; i < N; i++)
			cpu[i].reg[regX] = cpu[i].reg[regX] * cpu[i].reg[regY];
}

void modInstr(int N, proc *cpu, int regX, int regY, int valY){
	int i;
	if(regY == -1)
		for(i = 0; i < N; i++)
			cpu[i].reg[regX] = cpu[i].reg[regX] % valY; 
	else
		for(i = 0; i < N; i++)
			cpu[i].reg[regX] = cpu[i].reg[regX] % cpu[i].reg[regY];
}

int jgzInstr(int N, proc *cpu, int regX, int regY, int valY){
	int i;
	for(i = 0; i < N; i++){
		if(cpu[i].reg[regX] > 0){
			if(regY == -1)
				return valY;
			else
				return cpu[i].reg[regY];
		}
	}
	return 1; 
}

void sndInstr(int N, proc *cpu, int regX, int valX, queue **begin, queue **end){
	int i, *sndValues;
	sndValues = (int *)calloc(N, sizeof(int));
	if(regX == -1){
		for(i = 0; i < N; i++)
			sndValues[i] = valX;
	}
	else{
		for(i = 0; i < N; i++)
			sndValues[i] = cpu[i].reg[regX];
	}
	enqueue(&begin, &end, sndValues, N);
	free(sndValues);
	sndValues = NULL;
}

void rcvInstr(int N, proc *cpu, int regX, queue **begin, queue **end){
	int i, *rcvValues;
	rcvValues = (int *)calloc(N, sizeof(int));
	
	dequeue(&begin, &end, rcvValues, N);
	cpu[0].reg[regX] = rcvValues[N - 1];
	for(i = 1; i < N; i++)
		cpu[i].reg[regX] = rcvValues[i - 1];
	

	free(rcvValues);
	rcvValues = NULL;
}