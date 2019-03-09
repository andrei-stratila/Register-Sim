#include <stdint.h>

typedef struct queue{
	int32_t *info;
	struct queue *next, *prev;
} queue;

void enqueue(queue ***begin, queue ***end, int *values, int N);
void dequeue(queue ***begin, queue ***end, int *rcvValues, int N);
int isEmpty(queue **end);
void initQueue(queue **begin, queue **end);
