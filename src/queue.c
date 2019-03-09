#include "instructions.h"

int isEmpty(queue **end){
	if(*end == NULL)
		return 1;
	return 0;
}
void initQueue(queue **begin, queue **end){
	*begin = NULL;
	*end = NULL; 
}

void enqueue(queue ***begin, queue ***end, int *values, int N){
	queue *newEntry = (queue*)malloc(sizeof(queue));
	int i;
	newEntry->info = (int32_t *)calloc(N, sizeof(int32_t));
	for(i = 0; i < N; i++)
		newEntry->info[i] = values[i];
	newEntry->next = NULL;
	newEntry->prev = NULL;
	if(**begin == NULL && **end == NULL){
		**begin = newEntry;
		**end = newEntry;
	}
	else{
		(**begin)->prev = newEntry;
		newEntry->next = **begin;
		**begin = newEntry;
	}
}

void dequeue(queue ***begin, queue ***end, int *rcvValues, int N){
	queue *del = **end;
	int i;
	for(i = 0; i < N; i++)
		rcvValues[i] = del->info[i];
	free(del->info);
	if(del->prev == NULL){
		free(**end);
		**end = NULL;
	}
	else{
		(**end) = del->prev;
		free(del);
	}
}
