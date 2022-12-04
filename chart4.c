// Itay Fhima || Shani Glick
// 312182009  || 212212484

#include "GeneralHeader.h"

MusicianColl* instrumentsDatabaseConstruction(Musician** MusiciansGroup, int MGSize, InstrumentTree tree, int* MCSize)
{ // This function creates the data base of the instruments in MusicianCollection array
	int numNodes = NumNodes(tree), i; // counting how many instruments there are in the tree
	MusicianColl* MusicianCollection = createMC(numNodes);
	for (i = 0; i < MGSize; i++)
		addPtrs(MusiciansGroup[i], &MusicianCollection); // for each musician - adding the pointers to him according to the instruments on which he knows how to play
	*MCSize = numNodes;
	return MusicianCollection;
}

void addPtrs(Musician* currMusician, MusicianColl** MusicianCollection)
{ // This function adds the pointers to the musician
	ListNode* p = currMusician->instruments.head; 
	int insId, LSize;
	while (p != NULL)
	{
		insId = p->data->insId; // each instrument ID represents the place in MC array
		LSize = (*MusicianCollection)[insId].logSize;
		if (LSize == (*MusicianCollection)[insId].phySize) // in case the array needs to be increased
		{
			(*MusicianCollection)[insId].phySize = (*MusicianCollection)[insId].phySize * TWO;
			(*MusicianCollection)[insId].arr = (MusiciansOnIns*)realloc((*MusicianCollection)[insId].arr, (*MusicianCollection)[insId].phySize * sizeof(MusiciansOnIns));
			checkAlloc((*MusicianCollection)[insId].arr);
		}
		(*MusicianCollection)[insId].arr[LSize].musician = currMusician;
		(*MusicianCollection)[insId].arr[LSize].price = p->data->price;
		(*MusicianCollection)[insId].logSize += ONE; // updating the size of MusicianOnIns arr in 'insId' place
		p = p->next;
	}
}

MusicianColl* createMC(int size)
{ // This function creates the MusicianCollection array
	int i;
	MusicianColl* res = (MusicianColl*)malloc(size * sizeof(MusicianColl));
	checkAlloc(res);
	for (i = 0; i < size; i++)
	{
		res[i].arr = (MusiciansOnIns*)malloc(sizeof(MusiciansOnIns));
		checkAlloc(res[i].arr);
		res[i].logSize = ZERO;
		res[i].phySize = ONE;
	}
	return res;
}

int NumNodes(InstrumentTree tree)
{ // This function counts how many nodes there are in the tree
	return NumNodesRec(tree.root);
}

int NumNodesRec(TreeNode* node)
{
	if (node == NULL)
		return 0;
	return 1 + NumNodesRec(node->left) + NumNodesRec(node->right);
}

void freeMusiciansCollection(MusicianColl* MCarr, int size)
{
	int i;
	for (i = 0; i < size; i++)
		free(MCarr[i].arr);
	free(MCarr);
}
