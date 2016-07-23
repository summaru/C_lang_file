#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct listnode {
		element data;
		struct listnode *link;
}listnode;
//
void error(char* message)
{
		fprintf(stderr,"%s\n",message);
		exit(1);
}
// Dynamic program
listnode *create_node(element data, listnode *link)
{
		listnode *new_node;
		new_node = (listnode *)malloc(sizeof(listnode));
		if(new_node == NULL) error("Dynamic memory error");
		new_node->data = data;
		new_node->link = link;
		return (new_node);
}

//puts of list
void display(listnode *head)
{
		listnode *p;
		if( head == NULL) return;

		p = head;
		do
		{
				printf("%d->",p->data);
				p = p->link;
		}while(p != head);
}

void insert_first(listnode **phead, listnode *node)
{
		if( *phead == NULL){
				*phead = node;
				node -> link = node;
		}
		else {
				node->link = (*phead)->link;
				(*phead)->link = node;
		}
}

void insert_last(listnode **phead, listnode *node)
{
		if(*phead == NULL){
				*phead = node;
				node->link = node;
		}
		else{
				node->link = (*phead)->link;
				(*phead)->link = node;
				*phead = node;
		}
}

int main()
{
		listnode *list1 = NULL;

		//list1 = 50 -> 40 -> 20
		insert_first(&list1, create_node(20, NULL));
		insert_first(&list1, create_node(40, NULL));
		insert_last(&list1 , create_node(50, NULL));
		display(list1);

		return 0;
}
