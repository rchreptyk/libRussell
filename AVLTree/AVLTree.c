
#include "AVLTree.h"

struct treeNodeStruct;
typedef struct treeNodeStruct TreeNode;

struct treeNodeStruct {
	void * data;

	int height;

	TreeNode * left;
	TreeNode * right;
};

struct avltreeStruct {
	int (*compare)(void *, void *);

	TreeNode * rootNode;
	int numNodes;
};

enum direction { LEFT = 0, RIGHT = 1};

enum load { LEFTHEAVY = -1, BALANCED = 0, RIGHTHEAVY = 1};

/*static void saveIntNode(TreeNode * node, FILE * file);*/
static TreeNode * insertIntoTree(AVLTree * tree, TreeNode * node, void * data, Boolean * success);
static TreeNode * rightRotateTree(TreeNode * node);
static TreeNode * leftRotateTree(TreeNode * node);
static int isUnbalanced(int loadBalance);
static int calcLoadBalance(TreeNode * leftNode, TreeNode * rightNode);
static int nodeHeight(TreeNode * node);
static TreeNode * newTreeNode(void * data);
static void destroySubTree(TreeNode * node, void (*destroyData)(void * data));
static void destroyNode(TreeNode * node);
static void updateHeight(TreeNode * node);
static TreeNode * balanceNode(TreeNode * node);
static TreeNode * removeNode(AVLTree * tree, TreeNode * node, void * data, void ** removedData);
static void * replaceWithData(TreeNode * node, void * data);
static void * searchSubTree(AVLTree * tree, TreeNode * node, void * data);

AVLTree * AVLTree_create(int compareData(void *, void *))
{
	AVLTree * tree;

	if(compareData == NULL)
		return NULL;

	tree = malloc(sizeof(AVLTree));

	if(tree == NULL)
		return NULL;

	tree->compare = compareData;

	tree->rootNode = NULL;
	tree->numNodes = 0;
	return tree;
}

Boolean AVLTree_destroy(AVLTree * tree)
{
	if(tree == NULL)
		return false;

	destroySubTree(tree->rootNode, NULL);

	free(tree);

	return true;
}

Boolean AVLTree_destroyTreeAndData(AVLTree * tree, void (*destroyData)(void * data))
{
	if(tree == NULL || destroyData == NULL)
		return false;

	destroySubTree(tree->rootNode, destroyData);

	free(tree);

	return true;
}

Boolean AVLTree_insert(AVLTree * tree, void * data)
{
	if(tree == NULL || data == NULL)
		return false;

	Boolean success = true;

	tree->rootNode = insertIntoTree(tree, tree->rootNode, data, &success);

	if(success)
		tree->numNodes++;

	return success;
}

void * AVLTree_remove(AVLTree * tree, void * data)
{
	if(tree == NULL || data == NULL)
		return NULL;

	void * removedData = NULL;

	tree->rootNode = removeNode(tree, tree->rootNode, data, &removedData);

	if(removedData != NULL)
		tree->numNodes--;

	return removedData;
}

void * AVLTree_search(AVLTree * tree, void * data)
{
	if(tree == NULL || data == NULL)
	{
		return NULL;
	}

	return searchSubTree(tree, tree->rootNode, data);
}

Boolean AVLTree_exists(AVLTree * tree, void * data)
{
	return AVLTree_search(tree, data) != NULL;
}

void * AVLTree_getGreatestNode(AVLTree * tree)
{
	if(tree == NULL)
		return NULL;

	TreeNode * node = tree->rootNode;

	if(node == NULL)
		return NULL;

	while(node->right != NULL)
		node = node->right;

	return node->data;
}

void * AVLTree_getLeastNode(AVLTree * tree)
{
	if(tree == NULL)
		return NULL;

	TreeNode * node = tree->rootNode;

	if(node == NULL)
		return NULL;

	while(node->left != NULL)
		node = node->left;

	return node->data;
}

int AVLTree_getNumNodes(AVLTree * tree)
{
	if(tree == NULL)
		return 0;

	return tree->numNodes;
}

/**********************************/

static void * searchSubTree(AVLTree * tree, TreeNode * node, void * data)
{
	if(node == NULL)
		return NULL;

	int comparision = tree->compare(data, node->data);

	if(comparision > 0)
	{
		return searchSubTree(tree, node->right, data);
	}
	
	if(comparision < 0)
	{
		return searchSubTree(tree, node->left, data);
	}

	return node->data;
}

static TreeNode * removeNode(AVLTree * tree, TreeNode * node, void * data, void ** removedData)
{
	if(node == NULL)
		return NULL;

	int comparision = tree->compare(data, node->data);

	if(comparision > 0)
	{
		node->right = removeNode(tree, node->right, data, removedData);
	}
	
	if(comparision < 0)
	{
		node->left = removeNode(tree, node->left, data, removedData);
	}

	if(comparision == 0)
	{
		*removedData = node->data;

		if(node->left == NULL && node->right == NULL) /*leaf node*/
		{
			destroyNode(node);
			node = NULL;
			return node;
		}
		else if(node->left != NULL && node->right != NULL)
		{
			node->data = replaceWithData(node->left, data);
			node->left = removeNode(tree, node->left, data, removedData);
		}
		else if(node->left != NULL) /*only left node*/
		{
			TreeNode * leftNode = node->left;
			*removedData = node->data;
			destroyNode(node);
			node = leftNode;
		}
		else /*only right node*/
		{
			TreeNode * rightNode = node->right;
			*removedData = node->data;
			destroyNode(node);
			node = rightNode;
		}

	}

	updateHeight(node);

	node = balanceNode(node);

	return node;
}

static void * replaceWithData(TreeNode * node, void * data)
{
	if(node->right != NULL)
		return replaceWithData(node->right, data);

	void * newData = node->data;
	node->data = data;

	return newData;
}

static void destroySubTree(TreeNode * node, void (*destroyData)(void * data))
{
	if(node == NULL)
		return;

	destroySubTree(node->left, destroyData);
	destroySubTree(node->right, destroyData);

	if(destroyData != NULL)
		destroyData(node->data);

	destroyNode(node);
}

static void destroyNode(TreeNode * node)
{
	node->height = 0;
	node->right = NULL;
	node->left= NULL;

	free(node);
}

/*
void saveIntTree(AVLTree * tree, int num)
{
	char name[50];

	sprintf(name, "%d.opml", num);

	FILE * file = fopen(name, "w");
	fprintf(file, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n<opml version=\"1.0\">\n<head>\n<title>Tree</title>\n<ownerName></ownerName>\n</head>\n<body><outline text=\"Tree\">");

	saveIntNode(tree->rootNode, file);

	fprintf(file, "   </outline>\n</body>\n</opml>");

	fclose(file);
}

static void saveIntNode(TreeNode * node, FILE * file)
{
	if(node == NULL)
	{
		fprintf(file, "<outline text=\"No Node\"></outline>\n");
		return;
	}

	fprintf(file, "<outline text=\"Node: %d - H: %d \">\n", *(int*)(node->data), node->height);

	saveIntNode(node->left, file);
	saveIntNode(node->right, file);

	fprintf(file, "</outline>\n");
}
*/

static TreeNode * insertIntoTree(AVLTree * tree, TreeNode * node, void * data, Boolean * success)
{
	if(node == NULL)
		return newTreeNode(data);

	int comparision = tree->compare(data, node->data);

	if(comparision == 0)
	{
		*success = false;
		return node;
	}

	int direction = comparision > 0 ? RIGHT : LEFT;

	if(direction == RIGHT)
	{
		node->right = insertIntoTree(tree, node->right, data, success);
	}
	else
	{
		node->left = insertIntoTree(tree, node->left, data, success);
	}

	updateHeight(node);

	node = balanceNode(node);

	return node;
}

static TreeNode * balanceNode(TreeNode * node)
{
	int loadBalance = calcLoadBalance(node->left, node->right);

	if(isUnbalanced(loadBalance) == RIGHTHEAVY)
	{
		int rightChildBalance = calcLoadBalance(node->right->left, node->right->right);

		if(rightChildBalance > 0)
		{
			node->right = rightRotateTree(node->right);
			updateHeight(node->right);
		}

		node = leftRotateTree(node);
	}

	if(isUnbalanced(loadBalance) == LEFTHEAVY)
	{
		int leftChildBalance = calcLoadBalance(node->left->left, node->left->right);

		if(leftChildBalance < 0)
		{
			node->left = leftRotateTree(node->left);
			updateHeight(node->left);
		}

		node = rightRotateTree(node);
	}

	return node;
}

static void updateHeight(TreeNode * node)
{
	if(nodeHeight(node->left) > nodeHeight(node->right))
		node->height = nodeHeight(node->left) + 1;
	else
		node->height = nodeHeight(node->right) + 1;
}

static TreeNode * rightRotateTree(TreeNode * node)
{
	TreeNode * oldRoot = node;

	node = oldRoot->left;
	oldRoot->left = node->right;
	node->right = oldRoot;

	updateHeight(oldRoot);

	return node;
}

static TreeNode * leftRotateTree(TreeNode * node)
{
	TreeNode * oldRoot = node;

	node = oldRoot->right;
	oldRoot->right = node->left;
	node->left = oldRoot;

	updateHeight(oldRoot);

	return node;
}

static int isUnbalanced(int loadBalance)
{
	if(loadBalance < -1)
		return RIGHTHEAVY;
	if(loadBalance > 1)
		return LEFTHEAVY;

	return BALANCED;
}

static int calcLoadBalance(TreeNode * leftNode, TreeNode * rightNode)
{
	int leftHeight = nodeHeight(leftNode);
	int rightHeight = nodeHeight(rightNode);

	int heightDifference = leftHeight - rightHeight;

	return heightDifference;
}

static int nodeHeight(TreeNode * node)
{
	if(node == NULL)
		return 0;

	return node->height;
}

static TreeNode * newTreeNode(void * data)
{
	TreeNode * node;

	if(data == NULL)
		return NULL;

	node = malloc(sizeof(TreeNode));

	if(node == NULL)
		return NULL;

	node->data = data;
	
	node->left = NULL;
	node->right = NULL;

	node->height = 1;

	return node;
}
