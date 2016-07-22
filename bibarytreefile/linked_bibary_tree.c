/*
*
*
*                                    ************
*                                    *    n1    *
*                                    ************
*                                     *        *                      
*                                   *            *                          
*                                 *                *            
*                               *                    *           
*                        ***********              **********                             
*                        *    n2   *              *   n3   *            
*                        ***********              **********
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct treenode {
		int data;
		struct treenode *left, *right; // link
}treenode;

int main()
{
		treenode *n1, *n2, *n3;
		n1 = (treenode *)malloc(sizeof(treenode));
		n2 = (treenode *)malloc(sizeof(treenode));
		n3 = (treenode *)malloc(sizeof(treenode));
		n1->data = 10;
		n1->left = n2;
		n1->right = n3;
		n2->data = 20;
		n2->left = NULL;
		n2->right = NULL;
		n3->data = 30;
		n3->left = NULL;
		n3->right = NULL;

		return 0;
}
