#include "verify.h"
#include "tree.h"
#include <stdio.h>

int main()
{
	TreeNode* tree;
	char* expression = "(((x1*5)+(18.25+5.5))/5)";

	tree = assembleTree(expression);

	printf("%s\n",expression);
	printTree(tree, 0);

	postOrder(tree);
	printf("\n");
	preOrder(tree);
	printf("\n");
	inOrder(tree);
	printf("\n");

	return 0;
}
