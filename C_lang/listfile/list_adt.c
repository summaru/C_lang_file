#include <stdio.h>
#include <stdlib.h>

#define MAX_LIST_SIZE 100

typedef int element;
typedef struct {
		element list[MAX_LIST_SIZE];
		int length;
}ArrayListTest;

void error(char *message)
{
		fprintf(stderr,"%s\n",message);
		exit(1);
}

void init(ArrayListTest *L)
{
		L->length = 0;
}

int is_empty(ArrayListTest *L)
{
		return L->length == 0;
}

int is_full(ArrayListTest *L)
{
		return L->length == MAX_LIST_SIZE;
}

void display(ArrayListTest *L)
{
		int i;
		for(i = 0; i<L->length;i++)
				printf("%d\n", L->list[i]);
}


void add(ArrayListTest *L, int position, element item)
{
		if(!is_full(L) && (position >= 0) && (position <= L->length))
		{
				int i;
				for(i=(L->length-1); i>=position;i--)
						L->list[i+1] = L->list[i];

				L->list[position] = item;
				L->length++;
		}
}

element delete(ArrayListTest *L, int position)
{
		int i;
		element item;

		if(position < 0 || position >= L->length)
				error("pos error");
		item = L->list[position];
		for(i=position; i<(L->length-1);i++)
				L->list[i] = L->list[i+1];
		L->length--;
		return item;
}

int main()
{
		ArrayListTest list1;

		init(&list1);
		add(&list1,0,10);
		add(&list1,0,20);
		add(&list1,0,30);
		display(&list1);

		return 0;
}
