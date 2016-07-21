#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct queuenode {
		element item;
		struct queuenode *link;
}queuenode;

typedef struct {
		queuenode *front, *rear;
}queuetype;

void error(char *message)
{
		fprintf(stderr,"%s\n",message);
		exit(1);
}

void init(queuetype *q)
{
		q->front = q->rear = NULL;
}

int is_empty(queuetype *q)
{
		return (q->front == NULL);
}

void enqueue(queuetype *q, element item)
{
		queuenode *temp = (queuenode *)malloc(sizeof(queuenode));
		if( temp == NULL)
				error("can`t malloc in memory\n");
		else {
				temp->item = item;
				temp->link = NULL;
				if(is_empty(q)) {
						q->front = temp;
						q->rear = temp;
				}
				else {
						q->rear->link = temp;
						q->rear = temp;
				}
		}

}

element dequeue(queuetype *q)
{
		queuenode *temp = q->front;
		element item;
		if(is_empty(q))
				error("nuderflow queue");
		else{
				item = temp->item;
				q->front = q->front->link;
				if(q->front == NULL)
						q->rear = NULL;
				free(temp);
				return item;
		}
}

element peek(queuetype *q)
{
		if(is_empty(q))
				error("empty queue\n");
		else{
				return q->front->item;
		}
}

int main()
{
		queuetype q;

		init(&q);
		enqueue(&q, 1);
		enqueue(&q, 2);
		enqueue(&q, 3);
		printf("dequeue()=%d\n",dequeue(&q));
		printf("dequeue()=%d\n",dequeue(&q));
		printf("dequeue()=%d\n",dequeue(&q));

		return 0;
}
