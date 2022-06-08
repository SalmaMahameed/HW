#include "BST.h"
#include <stdio.h>
#include "TreePrintLibrary.h"
#include <stdlib.h>
//define an parameter to check the function findIndexNFromLast
#define NSTEPS1 3
#define NSTEPS2 6
#define SAME_HEIGHT 1
#define NOT_SAME_HEIGHT 0
//macro
#define EXIT_PROGRAM_FAILED exit(1);
#define CHECK_ALLOCATION(ptr)\
if (!ptr){printf("Failed to allocate memory,exiting the program\n");EXIT_PROGRAM_FAILED};
//main functions
void initBST(BST* bst);
void insertBST(BST* bst, int value);
void printTreeInorder(BST* bst);
void destroyBST(BST* bst);
int sameHeightLeaves(BST* bst);
int findIndexNFromLast(BST* bst, int N);
//help functions
TreeNode* createNode(int value);
void addToTree(TreeNode* tree, TreeNode* newNode);
void print_inorder(TreeNode* tree);
void freeallocations(TreeNode* tree);
int ifleavessamelvl(TreeNode* tree, int lvl, int* leaflvl);
void idxNFromLast(TreeNode* tree, int N, int* idx, int* val);
//main
void main() {
	BST tree;
	initBST(&tree);
	//test each function forwarding empty tree
	printTreeInorder(&tree);
	findIndexNFromLast(&tree, NSTEPS1);
	sameHeightLeaves(&tree);
	insertBST(&tree, 4);
	destroyBST(&tree);
	//now we will test each function forwarding specific tree
	//initi & insert & print tree in order :
	insertBST(&tree, 5);
	insertBST(&tree, 2);
	insertBST(&tree, 8);
	insertBST(&tree, 1);
	insertBST(&tree, 4);
	insertBST(&tree, 9);
	print_ascii_tree(tree.root);
	printTreeInorder(&tree);
	destroyBST(&tree);
	//initi & insert & findIndexNFromLast :
	insertBST(&tree, 5);
	insertBST(&tree, 2);
	insertBST(&tree, 8);
	insertBST(&tree, 1);
	insertBST(&tree, 4);
	insertBST(&tree, 9);
	insertBST(&tree, 10);
	insertBST(&tree, 11);
	print_ascii_tree(tree.root);
	//with N=3:
	printf("The %d'th largest element in the tree: %d\n", NSTEPS1, findIndexNFromLast(&tree, NSTEPS1));
	//with N=6:
	printf("The %d'th largest element in the tree: %d\n", NSTEPS2, findIndexNFromLast(&tree, NSTEPS2));
	destroyBST(&tree);
	//initi & insert & sameHeightLeaves 1 :
	insertBST(&tree, 5);
	insertBST(&tree, 2);
	insertBST(&tree, 8);
	insertBST(&tree, 1);
	insertBST(&tree, 4);
	insertBST(&tree, 8);
	insertBST(&tree, 9);
	insertBST(&tree, 1);
	insertBST(&tree, 2);
	insertBST(&tree, 5);
	insertBST(&tree, 8);
	insertBST(&tree, 9);
	print_ascii_tree(tree.root);
	int res = sameHeightLeaves(&tree);
	res == SAME_HEIGHT ? printf("The leaves at same height\n") : printf("The leaves is not at same height\n");
	destroyBST(&tree);
	//initi & insert & sameHeightLeaves 2 :
	insertBST(&tree, 5);
	insertBST(&tree, 2);
	insertBST(&tree, 8);
	insertBST(&tree, 1);
	insertBST(&tree, 9);
	insertBST(&tree, 4);
	insertBST(&tree, 1);
	insertBST(&tree, 2);
	insertBST(&tree, 4);
	insertBST(&tree, 5);
	print_ascii_tree(tree.root);
	res = sameHeightLeaves(&tree);
	res == SAME_HEIGHT ? printf("The leaves at same height\n") : printf("The leaves is not at same height\n");
	destroyBST(&tree);
}

//functions implementation

void initBST(BST* bst) {
	bst->root = NULL;
}

void insertBST(BST* bst, int value) {
	if (bst->root != NULL)
		addToTree(bst->root, createNode(value));
	else
		bst->root = createNode(value);
}

TreeNode* createNode(int value) {
	TreeNode* tmp = (TreeNode*)malloc(sizeof(TreeNode));
	CHECK_ALLOCATION(tmp)
		tmp->element = value;
	tmp->left = tmp->right = NULL;
	return tmp;
}

void addToTree(TreeNode* tree, TreeNode* newNode) {
	if (newNode->element <= tree->element)
		if (tree->left == NULL)
			tree->left = newNode;
		else
			addToTree(tree->left, newNode);
	if (newNode->element > tree->element)
		if (tree->right == NULL)
			tree->right = newNode;
		else
			addToTree(tree->right, newNode);
}

void printTreeInorder(BST* bst) {
	if (bst->root == NULL)
		printf("Empty tree!\n");
	else {
		printf("In order: ");
		print_inorder(bst->root);
		printf("\n");
	}
}

void print_inorder(TreeNode* tree) {
	if (tree != NULL) {
		print_inorder(tree->left);
		printf("%d ", tree->element);
		print_inorder(tree->right);
	}
}

void destroyBST(BST* bst) {
	if (bst == NULL)
		return;
	if (bst->root != NULL)
		freeallocations(bst->root);
	bst->root = NULL;
}
void freeallocations(TreeNode* tree) {
	if (!tree)
		return;
	freeallocations(tree->left);
	freeallocations(tree->right);
	free(tree);
}

int sameHeightLeaves(BST* bst) {
	int lvl = 0, leaflvl = 0;
	return ifleavessamelvl(bst->root, lvl, &leaflvl);
}

int ifleavessamelvl(TreeNode* tree, int lvl, int* leaflvl) {
	if (tree == NULL)
		return 1;
	if (tree->left == NULL && tree->right == NULL) {
		if (*leaflvl == 0) {
			*leaflvl = lvl;
			return 1;
		}
		return (lvl == *leaflvl);
	}
	return (ifleavessamelvl(tree->left, lvl + 1, leaflvl) && ifleavessamelvl(tree->right, lvl + 1, leaflvl));
}

int findIndexNFromLast(BST* bst, int N) {
	int idx = 0, val;
	idxNFromLast(bst->root, N, &idx, &val);
	return val;
}

void idxNFromLast(TreeNode* tree, int N, int* idx, int* val) {
	if (tree == NULL || *idx >= N)
		return;
	idxNFromLast(tree->right, N, idx, val);
	(*idx)++;
	if (*idx == N) {
		*val = tree->element;
		return;
	}
	idxNFromLast(tree->left, N, idx, val);
}