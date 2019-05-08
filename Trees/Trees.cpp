// Trees.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<malloc.h>
typedef struct Node
{
	char data[30];
	struct Node* left;
	struct Node* right;
	struct Node* parent;
} Node;
Node* newNode(char* d)
{
	Node* n = (Node*)malloc(sizeof(Node));
	strcpy(n->data, d);
	n->left = NULL;
	n->right = NULL;
	n->parent = NULL;
	return n;
}
void intia(Node* root)
{
	root = NULL;
}
int isEmpty(Node* Root)
{
	return Root == NULL ? 1 : 0;
}
int Size(Node* Root)
{
	if (Root == NULL)
		return 0;
	else
		return  1 + Size(Root->left) + Size(Root->right);

}


Node* insert(Node* root, char* d)
{
	if (root == NULL) {
		root = newNode(d);
		root->left = NULL;
		root->parent = NULL;
		root->right = NULL;
	}
	else {
		Node* temp;

		if (strcmp(d, root->data) < 0)
		{
			temp = insert(root->left, d);
			root->left = temp;
			temp->parent = root;
		}
		else if (strcmp(d, root->data) > 0)
		{
			temp = insert(root->right, d);
			root->right = temp;
			temp->parent = root;

		}
	}
	return root;
}

int hight(Node * Root) {
	if (Root == NULL)
		return -1;
	else {

		int L = hight(Root->left);
		int R = hight(Root->right);
		return L > R ? (L + 1) : (R + 1);
	}

}
int isFound(Node* root, char* word) {

	if (root == NULL)
		return 0;
	else if (strcmp(word, root->data) == 0)
		return 1;
	else if (strcmp(word, root->data) < 0)
		return isFound(root->left, word);
	else if (strcmp(word, root->data) > 0)
		return isFound(root->right, word);

}
Node* leaf(Node* root, char* word) 
	{
	
	/*if (root == NULL)
		return root->parent;*/
	if (root->left == NULL && root->right == NULL)
		return root;
	/*else if (root->right == NULL)
		return root;*/
	else if (strcmp(word, root->data) > 0)
		if (root->right == NULL)
			return root;
		else
			return leaf(root->right, word);

	else if (strcmp(word, root->data) < 0)
		if (root->left == NULL)
			return root;
		else
		return leaf(root->left, word);
	
		
}
Node* pre(Node* root) {
	
	if (root->left != NULL) {

		root = root->left;

		while (root->right != NULL)
			root = root->right;
		return root;
	}
	else if (root->left == NULL && strcmp(root->data, root->parent->data) < 0)
	{
		while (strcmp(root->data, root->parent->data) < 0)
			if (root->parent == NULL)
				return root;
			root = root->parent;
		return root->parent;
	}
	else
		return root->parent;
}
Node* suc(Node* root) {

	if (root->right != NULL) {
		root = root->right;

		while (root->left!=NULL)
			root = root->left;
		return root;
	}
	else if (root->right == NULL && strcmp(root->data, root->parent->data) > 0)
	{

		while (strcmp(root->data, root->parent->data) > 0)
			root = root->parent;
		return root->parent;
	}
	else return root->parent;
}




int main()
{
	char Spell[100];
	Node* Root = (Node*)malloc(sizeof(Node));
	Node* Root2 = (Node*)malloc(sizeof(Node));
	Root = NULL;
	FILE* p;
	char c[100];
	p = fopen("D:\\Downloads\\EN-US-randomized-unique_updated.txt", "r");

	while (!feof(p))
	{
		fscanf(p, "%s", c);
		Root = insert(Root, c);

	}

	printf("the size = %d", Size(Root));
	printf("\nthe Hight = %d", hight(Root));
	printf("\nInput Sentence : ");
	fgets(Spell, 100, stdin);
	char* token = strtok(Spell, "\n");
	char* token2 = strtok(token, " ");
	while (token2 != NULL)
	{
		if (isFound(Root, token2)==1)
		{
			printf("%s CORRECT\n", token2);
		}
		else
		{
			Root2 = leaf(Root, token2);
			printf("%s : %s -- %s -- %s\n", token2, leaf(Root, token2)->data, suc(Root2)->data, pre(Root2)->data);
			

		}
		
		token2 = strtok(NULL, " ");

	}
	
	
	fclose(p);

}


//void printPostorder(Node * node)
//{
//	if (node == NULL)
//		return;
//
//	printPostorder(node->left);
//
//	printPostorder(node->right);
//
//	printf("%s - - ", node->data);
//}
//void printInorder(Node * node)
//{
//	if (node == NULL)
//		return;
//
//	printInorder(node->left);
//
//	printf("%s\n", node->data);
//
//	printInorder(node->right);
//}
//Node* insert(Node * root, char* d)
//{
//	Node* temp;
//	if (root == NULL) {
//		root = newNode(d);
//		root->left = NULL;
//		root->parent = NULL;
//		root->right = NULL;
//	}
//	else if (strcmp(d, root->data) < 0)
//	{
//		if (root->left == NULL) {
//			
//			root->left = newNode(d);
//			root->parent = root;
//		
//		}
//		else
//			root->left = insert(root->left, d);
//	
//
//	}
//	else if (strcmp(d, root->data) > 0)
//	{
//		if (root->right == NULL) {
//			
//			root->right = newNode(d);
//			root->right->parent = root;
//
//			
//		}
//		else
//			root->right = insert(root->right, d);
//
//	}
//	return root;
//}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
