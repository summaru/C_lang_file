#include <stdio.h>
#include <stdlib.h>

typedef struct treenode {
		int data;
		struct treenode *left, *right;
}treenode;
/*
*                   15
*                *      *
*              *          *
*             4            20
*           *             *   *
*          *            *       *
*         1            16        25
*/

treenode n1 = {1, NULL, NULL};
treenode n2 = {4, &n1,  NULL};
treenode n3 = {16,NULL, NULL};
treenode n4 = {25,NULL, NULL};
treenode n5 = {20, &n3, &n4 };
treenode n6 = {15, &n2, &n5 };

treenode *root = &n6;
// inorder traversal
void inorder(treenode *root)
{
		if(root)
		{
				inorder(root->left);
				printf("%d\t", root->data);
				inorder(root->right);
		}
}
//preorder traversal
void preorder(treenode *root)
{
		if(root)
		{
				printf("%d\t", root->data);
				preorder(root->left);
				preorder(root->right);
		}
}
//postorder traversal
void postorder(treenode *root)
{
		if(root)
		{
				postorder(root -> left);
				postorder(root -> right);
				printf("%d\t", root -> data);
		}
}

int main()
{
		
		fputs("inorder traversal\n",stdout);
		inorder(root);
		fputs("\npreorder traversal\n",stdout);
		preorder(root);
		fputs("\npreorder traversal\n",stdout);
		postorder(root);

		return 0;
}
