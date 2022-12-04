// Itay Fhima || Shani Glick
// 312182009  || 212212484

#ifndef _Instruments_
#define _Instruments_

typedef struct treeNode {
	char* instrument; // שם כלי הנגינה  
	unsigned short insId; // מספר מזהה ייחודי עבור כלי נגינה שבאחריותכם לתת  
	struct treeNode* left;
	struct treeNode* right;
} TreeNode;

typedef struct tree {
	TreeNode* root;
} InstrumentTree;

InstrumentTree buildTree(char* instrumentsFile);
TreeNode* insert(TreeNode* root, char* data, int i);
TreeNode* createTnode(char* name, int Id, TreeNode* left, TreeNode* right);
int lexComper(char* str1, char* str2);
void freeTree(InstrumentTree tr);
void freeTreeRec(TreeNode* t);
int findInsId(InstrumentTree tree, char* instrument);
int findInsIdRec(TreeNode* node, char* instrument);

#endif
