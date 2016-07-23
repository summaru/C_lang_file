#include <stdio.h>
#define TRUE 1
#define FALSE 0

typedef struct treenode {
		int data;
		struct treenode * left, *right;
		int is_thread;
}treenode;

/*
*                         G
*                      *     *
*                    *         *
*                  C             F
*               *     *        *   *
*             A         B     D      E
*
*/
treenode n1={'A', NULL, NULL , 1};
treenode n2={'B', NULL, NULL , 1};
treenode n3={'C', &n1 , &n2  , 0};
treenode n4={'D', NULL, NULL , 1};
treenode n5={'E', NULL, NULL , 0};
treenode n6={'F', NULL, NULL , 0};
treenode n7={'G', NULL, NULL , 0};
treenode *exp = &n7;


treenode *find_successor(treenode *p)
{
		treenode *q = p->right;
		if(q==NULL || p->is_thread == TRUE)
				return 0;


		while(q->left != NULL) q = q->left;
		return 0;
}

void thread_inorder(treenode *t)
{
		treenode *q;
		q=t;
		while(q->left != NULL) q = q->left;
		do
		{
				printf("%c", q->data);
				q = find_successor(q);
		}while(q != NULL);
}

int main()
{
		n1.right = &n3;
		n2.right = &n7;
		n3.right = &n6;

		thread_inorder(exp);

		return 0;
}
