// Itay Fhima || Shani Glick
// 312182009  || 212212484

#include "GeneralHeader.h"

InstrumentTree buildTree(char* instrumentsFileName)
{//A function that receives a file of musical instruments and inserts them into a tree
	InstrumentTree res;
	int i = 0;
	char* seps = "\n";
	FILE* instruments = fopen(instrumentsFileName, "r");
	checkFile(instruments);
	char line[MAX_LINE_LEN];
	strcpy(line, strtok(fgets(line, MAX_LINE_LEN, instruments), seps)); //Gets a single instrument
	res.root = NULL;
	while (!feof(instruments))
	{
		res.root = insert(res.root, line, i); //Inserts intrument into a tree
		i++; // instrument Id
		strcpy(line, strtok(fgets(line, MAX_LINE_LEN, instruments), seps)); //Gets another instrument
	}
	res.root = insert(res.root, line, i);
	fclose(instruments);
	return res;
}

TreeNode* insert(TreeNode* root, char* data, int i)
{//A function that inserts musical instruments into a tree in lexicographic order
	if (root == NULL)
		return createTnode(data, i, NULL, NULL);

	if (lexComper(root->instrument, data) > 0) //If the first instrument is lexically larger than the second instrument
		root->left = insert(root->left, data, i);
	else
		root->right = insert(root->right, data, i);

	return root;
}

int lexComper(char* str1, char* str2)
{//A function that checks which string is lexicogically larger than the other
	int i = 0;
	while (str1[i] != END_OF_WORD && str2[i] != END_OF_WORD && str1[i] == str2[i])
		i++; //Index run as long as the letters in the two strings are the same
	return str1[i] - str2[i];
}

TreeNode* createTnode(char* name, int Id, TreeNode* left, TreeNode* right)
{
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
	checkAlloc(root);
	int len = strlen(name);
	root->instrument = (char*)malloc((len + 1) * sizeof(char));
	checkAlloc(root->instrument);
	strcpy(root->instrument, name);
	root->insId = Id;
	root->left = left;
	root->right = right;
	return root;
}

void freeTree(InstrumentTree tr)
{
	freeTreeRec(tr.root);
}

void freeTreeRec(TreeNode* t)
{
	if (t == NULL)
		return;
	else
	{
		freeTreeRec(t->left);
		freeTreeRec(t->right);
		free(t->instrument);
		free(t);
	}
}