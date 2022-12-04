// Itay Fhima || Shani Glick
// 312182009  || 212212484

#include "GeneralHeader.h"

int findInsId(InstrumentTree tree, char* instrument)
{
	if (tree.root != NULL)
		return findInsIdRec(tree.root, instrument);
	else
		return NOT_FOUNDED; // in case that the tree is empty
}

int findInsIdRec(TreeNode* node, char* instrument)
{ // The function searches for the name of a instrument in tree, if it finds - the function returns its id number, if not - the function returns -1
	int leftRes, rightRes;
	if (node == NULL) // exit condition
		return NOT_FOUNDED;
	if (strcmp(node->instrument, instrument) == 0) // if this node has the 'instrumnet' name
		return node->insId;
	leftRes = findInsIdRec(node->left, instrument); 
	if (leftRes != NOT_FOUNDED)
		return leftRes;
	rightRes = findInsIdRec(node->right, instrument);
	if (rightRes != NOT_FOUNDED)
		return rightRes;
	return NOT_FOUNDED;
}