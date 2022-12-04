// Itay Fhima || Shani Glick
// 312182009  || 212212484

#ifndef _Musicians_
#define _Musicians_

typedef struct {
	unsigned short insId; // מספר מזהה של כלי נגינה   
	float price; // מחיר שדורש הנגן עבור נגינה בכלי זה
} MusicianPriceInstrument;

typedef struct listNode {
	MusicianPriceInstrument* data;
	struct listNode* next;
}ListNode;

typedef struct {
	ListNode* head;
	ListNode* tail;
}MPIList;

typedef struct {
	char** name; // מערך של השמות המרכיבים את שמו המלא  
	int numOfNames;
	bool chosen;
	MPIList instruments; // MusicianPriceInstrument כלי הנגינה ברשימה מקושרת של
} Musician;

typedef struct {
	Musician* musician;
	float price;
}MusiciansOnIns;

typedef struct {
	MusiciansOnIns* arr;
	int logSize, phySize;
}MusicianColl;

Musician** createMusiciansArr(InstrumentTree tree, char* fileName, int* MGsize);
Musician* createMusician(InstrumentTree tree, char* line);
Musician* allocateMusician();
ListNode* createNewListNode(int insId, float price);
MPIList makeEmptyList();
void insertNodeToTail(InstrumentTree tree, MPIList* lst, char* insName, char* price);
void addName(Musician** musician, char* name);
void freeMusiciansGroupArr(Musician** arr, int size);
void freeMusician(Musician* musician);
void checkAlloc(void* ptr);
void freeList(MPIList lst);
void checkFile(FILE* file);
bool tokenIsName(char* str1, char* str2);
bool ListIsEmpty(MPIList* lst);

MusicianColl* instrumentsDatabaseConstruction(Musician** MusiciansGroup, int MGSize, InstrumentTree tree, int* MCSize);
MusicianColl* createMC(int size);
void addPtrs(Musician* currMusician, MusicianColl** MusicianCollection);
void freeMusiciansCollection(MusicianColl* MCarr, int size);
int NumNodes(InstrumentTree tree);
int NumNodesRec(TreeNode* node);

#endif