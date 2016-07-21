#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
#define MAX_STRING 100
typedef struct {
		int student_no;
		char name[MAX_STRING];
		char address[MAX_STRING];
}element;
element stack[MAX_STACK_SIZE];

int top = -1;

int is_empty()
{
		return (top == -1);
}

int is_full()
{
		return (top == (MAX_STACK_SIZE-1));
}

void push(element item)
{
		if(is_full()) {
				fprintf(stderr,"stack overflow\n");
				return;
		}
		else stack[++top] = item;
}

element pop()
{
		if(is_empty())
		{
				fprintf(stderr,"stack nuderflow\n");
				exit(1);
		}
		else return stack[top--];
}

element peek()
{
		if(is_empty()){
				fprintf(stderr,"stack nuderflow\n");
				exit(1);
		}
		else return stack[top];
}

int main()
{
		element ie, oe;
		strcpy(ie.name, "testing name");
		strcpy(ie.address, "korea");
		ie.student_no =20162016;
		push(ie);
		oe = pop();
		printf("name : %s\n", oe.name);
		printf("address : %s\n", oe.address);
		printf("student number : %d\n", oe.student_no);

		return 0;
}

