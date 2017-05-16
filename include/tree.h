/**
 *	Giuliano Sovernigo			0948924
 *	CIS*2520_F16				A3: equations and heap
 *	11/7/2016
 *	This header file contains the code for the tree data
 *	structure manipulation.  Its code is implimented in
 *	the C file of the same name.
 */


#ifndef __GSOVERNIGO_TREE_H__
#define __GSOVERNIGO_TREE_H__

typedef enum type
{
	NUMBER,
	OPERATOR,
	VARIABLE,
}Type;

typedef union
{
	float n;
	char o;
	char* v;
}Data;

struct node
{

	Type t;
	Data d;
	struct node* left;
	struct node* right;
};

typedef struct node TreeNode;

/**
 *	makeNode
 *	creates and returns a new node.
 * 	IN:		f		- the float that will be used to make a new node from.
 * 	OUT:	newNode	- a new node that contains f, and has no children.
 * 	POST:	Treenode has been allocated, so free it eventually.
 * 	ERROR:	malloc fails (NULL returned)
 */
TreeNode* makeFloatNode(float f);

/**
 *	makeOpNode
 *	creates and returns a new node that represents an operator.
 *	IN:		c		- a character containing +,-,* or /.
 *	OUT:	newNode - a new node that contains an operator as the root, and
 *					  no children.
 *	POST:	treenode has been allocated, so free it sometime.
 *	ERROR:	c is not a valid operator, NULL RETURNED, malloc fails, same.
 */
TreeNode* makeOpNode(char c);

/**
 *	makeVarNode
 *	makes a variable node that is represents a variable in the equation.
 *	IN:		v		- a string in the form x1-99
 *	OUT:	newNode - a new treenode that contains v as its data, and has
 *					  no children.
 *	POST:	a new node has been allocated, so free it eventually.
 *	ERROR:	malloc fails, v is not in the form x1-99.
 */
TreeNode* makeVarNode(char* v);

/**
 *	numElements
 *	takes the root node from numElements and performs the calculation.
 *	IN:		root	- the root node of the above function's tree.
 *	OUT:	the number of elements in the tree, from bottom to top.
 *	POST:	an integer has been returned.
 *	ERROR: 	node is null
 */
int numElements(TreeNode* node);

/**
 *	depth
 *	returns the maximum depth of the tree.
 *	IN:		n		- the node that will have its depth measured.
 *	OUT:	depth	- the depth of node n.
 *	POST:	an integer will be returned.
 *	ERROR:	n is NULL.
 */
int depth(TreeNode* n);

/**
 *	isEmpty
 *	checks if the tree is empty.
 *	IN:		t		- the tree to be measured.
 *	OUT:	0		- if tree is not empty.
 *			1		- if tree is empty.
 *	POST:	a single integer has been returned.
 *	ERROR:	tree is null.
 */
int treeIsEmpty(TreeNode* t);

/**
 *	children
 *	sets the two passed in node pointer pointers to the children of the parent.
 *	IN:		parent		- the parent to be examined and operated on.
 *			left		- the left child pointer
 *			right		- the right child pointer
 *	OUT:	returns parent, which is either valid or void.
 *	POST:	left and right have been modified to point to parent's children
 *	ERROR:	parent is null (returns null)	
 */
TreeNode* children(TreeNode* parent, TreeNode** left, TreeNode** right);

/**
 seewr*	left
 *	returns left child of parent.
 *	IN:		parent		- the parent node that will be examined.
 *	OUT:	returns the left child of the parent node that was passed in.
 *	POST:	parent->left has been returned.
 *	ERROR:	parent is null. (returns null)
 */
TreeNode* left(TreeNode* parent);

/**
 *	right
 *	returns right child of parent.
 *	IN:		parent		- the parent node that will be examined.
 *	OUT:	returns the right child of the parent node that was passed in.
 *	POST:	parent->right has been returned.
 *	ERROR:	parent is null. (returns null)
 */
TreeNode* right(TreeNode* parent);

/**
 *	postOrder
 *	visits the trees nodes in postOrder form.  prints all members.
 *	IN:		tree		- the tree that will be visited.
 *	OUT:	0 on success, negative error code on failure.
 *	POST:	tree have been postorder printed to the screen.
 *	ERROR:	tree in null.
 */
int postOrder(TreeNode* tree);

/**
 *	preOrder
 *	preorder outputs the tree.
 *	IN:		tree		- a tree to be preorder printed.
 *	OUT:	0 on success, negative error code on failure.
 *	POST:	tree has been preorder printed to the screen.
 *	ERROR:	tree is null.
 */
int preOrder(TreeNode* tree);

/**
 *	inOrder
 *	prints the tree in inorder notation.  This also fully parenthesizes the
 *	output, causing the actual expression to be recreated.
 *	IN:		tree		- the tree to be printed.
 *	OUT:	0 on success, negative error code on failure.
 *	ERROR:	tree is null.
 */
int inOrder(TreeNode* tree);

/**
 *	printNode
 *	prints a node to the screen.
 *	IN:		n			- the node that will be printed to the screen
 *	OUT:	void
 *	POST:	n has been printed to the screen.
 *	ERROR:	n is null.
 */
void printNode(TreeNode* n);

/**
 * 	printTree
 * 	Prints a whole tree in file-tree style to the screen.  This uses printNode
 * 	so as to make it easier to read (code-wise)
 * 	IN:		tree		- the tree that will be printed to the screen
 * 			level		- unless calling on a subtree, set this to 0; it is
 * 						  used to determine how many lines to print beforehand.
 * 	OUT:	0 on success, negative error code on failure.
 * 	POST:	the tree has been printed to the screen.
 * 	ERROR:	tree is null or level is incorrect (just please use 0.)
 */
int printTree(TreeNode* tree, int level);

/**
 *  deleteTree
 *  deletes a tree, freeing all the memory associated with it.
 *  IN:		tree		- the tree to be destroyed.
 *  OUT:	void.  This function returns nothing.
 *  POST:	the contents of the tree have been deleted, and should be handled
 *  		with most caution.
 *	ERROR:	none.
 */
void deleteTree(TreeNode* tree);

#endif

