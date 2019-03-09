#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "queue.h"

typedef struct Proc{
	int32_t reg[32];
} proc;

typedef struct instruction{
	char command[5];
	int regX, regY, valX, valY;
} instruction;

void setInstr(int N, proc *cpu, int regX, int regY, int valY);
void addInstr(int N, proc *cpu, int regX, int regY, int valY);
void mulInstr(int N, proc *cpu, int regX, int regY, int valY);
void modInstr(int N, proc *cpu, int regX, int regY, int valY);
int jgzInstr(int N, proc *cpu, int regX, int regY, int valY);
void sndInstr(int N, proc *cpu, int regX, int valX, queue **begin, queue **end);
void rcvInstr(int N, proc *cpu, int regX, queue **begin, queue **end);