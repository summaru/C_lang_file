#include<stdio.h>
#include<stdlib.h>

typedef int element;
typedef struct listnode {
		element data;
		struct listnode *link;
}listnode;

void error (char *message)
{
		fprintf(stderr,"%s\n",message);
		exit(1);
}

void insert_node(listnode **phead, listnode *p,listnode *new_node)
{
		/*phead : pointer of headpointer of list
		* p : pre_node
		* new_node : input node
		*/
		if(*phead == NULL){ //mayde NULL list
				new_node->link = NULL;
				*phead = new_node;
		}
		else if(p == NULL){ //p == NULL, input first node
				new_node->link = *phead;
				*phead = new_node;
		}
		else {              // input next to p
				new_node->link = p->link;
				p->link = new_node;
		}
}

void remove_node(listnode **phead, listnode *p,listnode *removed)
{
		/*phead : pointer of headpointer of list
		*p : remove the pre_node of node
		*removed : removed node
		*/
		if (p == NULL)
				*phead = (*phead)->link;
		else
				p->link = removed->link;
		free(removed);
}

void display(listnode *head)
{
		listnode *p = head;
		while(p != NULL){
				printf("%d->",p->data);
				p = p->link;
		}
		printf("\n");
}

listnode *search(listnode *head,int x)
{
		listnode *p;
		p = head;
		while( p != NULL){
				if(p->data == x) return p; //search success
				p = p->link;
		}
		return 0;
}
// head1 =(a,b,c), head2= (d,e,f).....return(a,b,c,,d,e,f)
listnode *concat(listnode *head1, listnode *head2)
{
		listnode *p;
		if(head1 == NULL) return head2;
		else if(head2 == NULL) return head1;
		else {
				p = head1;
				while(p->link != NULL)
						p = p->link;
					p->link = head2;
					return head1;
		}
}
//(e1, e2, e3, e4)......return(e4, e3, e2,e1)
listnode *reverse(listnode *head)
{
		listnode *p, *q, *r;
		p =head;
		q =NULL;
		while (p != NULL){
				r = q;
				q = p;
				p = p->link;
				q->link = r;
		}
		return q; //q : headpointer of list(revrse)
}

listnode *create_node(element data, listnode *link)
{
		listnode *new_node;
		new_node = (listnode *)malloc(sizeof(listnode));
		if(new_node == NULL) error("malloc error");
		new_node->data = data;
		new_node->link = link;
		return(new_node);
}

int main()
{
		listnode *list1=NULL, *list2=NULL;
		listnode *p;

	// list1 = 30->20->10
		insert_node(&list1, NULL, create_node(10, NULL));
		insert_node(&list1, NULL, create_node(20, NULL));
		insert_node(&list1, NULL, create_node(30, NULL));
		display(list1);

	//list1 = 20->10
		remove_node(&list1, NULL, list1);
		display(list1);

	//list2 = 80->70->60
		insert_node(&list2, NULL, create_node(60, NULL));
		insert_node(&list2, NULL, create_node(70, NULL));
		insert_node(&list2, NULL, create_node(80, NULL));
		display(list2);

	// list1 = list1 + list2
		list1 = concat(list1, list2);
		display(list1);

	//list1 reverse
		list1 = reverse(list1);
		display(list1);

	//search 20 in list1
		p = search(list1, 20);
		printf("search : %d\n", p->data);

		return 0;
}
