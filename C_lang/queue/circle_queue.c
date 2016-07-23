#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100

typedef int element;
typedef struct {
		element queue[MAX_QUEUE_SIZE];
		int front, rear;
}queuetype;

void error(char *message)
{
		fprintf(stderr,"%s\n",message);
		exit(1);
}

void init(queuetype *q)
{
		q->front = q->rear = 0;
}

int is_empty(queuetype *q)
{
		return (q->front == q->rear);
}
int is_full(queuetype *q)
{
		return ((q->rear+1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(queuetype *q,element item)
{
		if (is_full(q))
				error("overflow queue\n");
		q->rear = (q->rear+1) % MAX_QUEUE_SIZE;
		q->queue[q->rear] = item;
}

element dequeue(queuetype *q)
{
		if(is_empty(q))
				error("emptyed queue\n");
		q->front = (q->front+1) % MAX_QUEUE_SIZE;
    	return q->queue[q->front];
}

element peek(queuetype *q)
{
		if(is_empty(q))
				error("emptyed queue\n");
		return q->queue[(q->front+1) % MAX_QUEUE_SIZE];
}

int main()
{
		queuetype q;
		init(&q);
		printf("front=%d rear=%d\n",q.front, q.rear);
		enqueue(&q, 1);
		enqueue(&q, 2);
		enqueue(&q, 3);
		printf("dequeue()=%d\n",dequeue(&q));
		printf("dequeue()=%d\n",dequeue(&q));
		printf("dequeue()=%d\n",dequeue(&q));
		printf("front=%d rear=%d\n",q.front,q.rear);

		return 0;
}
