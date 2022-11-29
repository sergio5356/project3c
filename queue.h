#ifndef QUEUE_H
#define QUEUE_H

#include "treeADT.h"


typedef struct node_q{
	struct node_q *next;
	node *n;//pointer to a tree node
	int level;//level so we know when to print this node
}node_q;


typedef struct queue{
	node_q *head;
	node_q *tail;
}queue;


queue *init_queue();

void enqueue(queue *q, node *n, int level);

node* dequeue(queue *q, int *node_level);

int is_empty(queue *q);




#endif
