#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct stacknode
{
		element item;
		struct stacknode *link;
}stacknode;

typedef struct
{
		stacknode *top;
}linkedstacktype;

void init(linkedstacktype *s)
{
		s->top = NULL;
}
int is_empty(linkedstacktype *s)
{
		return (s->top == NULL);
}
void push(linkedstacktype *s,element item)
{
		stacknode *temp = (stacknode *)malloc(sizeof(stacknode));
		if(temp == NULL){
				fprintf(stderr,"memory malloc error\n");
				return;
		}
		else{
				temp->item = item;
				temp->link = s->top;
				s->top = temp;
		}
}

element pop(linkedstacktype *s)
{
		if(is_empty(s)) {
				fprintf(stderr ,"stack = NULL\n");
				exit(1);
		}
		else{
				stacknode *temp=s->top;
				element item = temp->item;
				s->top = s->top->link;
				free(temp);
				return item;
		}
}

element peek(linkedstacktype *s)
{
		if(is_empty(s)) {
				fprintf(stderr , "stack = NULL\n");
				exit(1);
		}
		else{
				return s->top->item;
		}
}

int main()
{
		linkedstacktype s;
		init(&s);
		push(&s, 1);
		push(&s, 2);
		push(&s, 3);
		printf("%d\n", pop(&s));
		printf("%d\n", pop(&s));
		printf("%d\n", pop(&s));
		printf("%d\n", is_empty(&s));

		return 0;
}
