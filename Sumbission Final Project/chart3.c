// Itay Fhima || Shani Glick
// 312182009  || 212212484

#include "GeneralHeader.h"

Musician** createMusiciansArr(InstrumentTree tree, char* fileName, int* MGsize)
{ // This function creates the musicians array from the musicians file
	FILE* musiciansFile = fopen(fileName, "rt");
	checkFile(musiciansFile);
	Musician** res = (Musician**)malloc(sizeof(Musician*));
	checkAlloc(res);
	char line[MAX_LINE_LEN];
	int logSize = 0, phySize = 1;
	while (!feof(musiciansFile))
	{
		if (logSize == phySize) // if needed to increase the array
		{
			phySize *= TWO;
			res = (Musician**)realloc(res, phySize * sizeof(Musician*));
			checkAlloc(res);
		}
		fgets(line, MAX_LINE_LEN, musiciansFile);
		res[logSize] = createMusician(tree, line); // creating each musician
		logSize++;
	}
	fclose(musiciansFile);
	*MGsize = logSize; // updating the logical size of MusiciansGroup array for the main
	return res;
}

Musician* createMusician(InstrumentTree tree, char* line)
{ // The function receives a string of data as input, and generates the information for a particular musician as output
	Musician* musician = allocateMusician(); // create musician 
	char *token, *temp, *seps = " ,.;:?!-\t'()[]{}<>~_";
	token = strtok(line, seps);
	temp = strtok(NULL, seps);
	while (token != NULL && temp != NULL)
	{
		if (tokenIsName(token, temp))
		{
			addName(&musician, token); // concating the name to the names arr of the musician
			token = temp;
			temp = strtok(NULL, seps);
		}
		else // token is instrument, temp is price
		{
			insertNodeToTail(tree, &(musician->instruments), token, temp); // adding the instrument and the price to the instruments list of the musician
			token = strtok(NULL, seps);
			temp = strtok(NULL, seps);
		}
	}
	return musician;
}

void insertNodeToTail(InstrumentTree tree, MPIList* lst, char* insName, char* price)
{ // This function creates new node in the instruments list and connect it to the list
	int insId = findInsId(tree, insName); // finding the instrument ID
	if (insId == NOT_FOUNDED)
	{
		printf("An error has been occured, cannot find %s in the tree.\n", insName);
		return;
	}
	float prc = (float)atof(price); // converting the string to float
	ListNode* newNode = createNewListNode(insId, prc); // creating new node
	if (ListIsEmpty(lst))
		lst->head = lst->tail = newNode;
	else
	{
		lst->tail->next = newNode;
		lst->tail = newNode;
	}
}

ListNode* createNewListNode(int insId, float price)
{ // This function creates new node in the instruments list
	ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
	checkAlloc(newNode);
	newNode->data = (MusicianPriceInstrument*)malloc(sizeof(MusicianPriceInstrument));
	checkAlloc(newNode->data);
	newNode->data->insId = insId;
	newNode->data->price = price;
	newNode->next = NULL;
	return newNode;
}

void addName(Musician** musician, char* name)
{ // This function concating a new name to the musician names arr
	int size = (*musician)->numOfNames + ONE;
	(*musician)->numOfNames += ONE;
	(*musician)->name = (char**)realloc((*musician)->name, size * sizeof(char*)); // increasing the size of the names arr by 1
	checkAlloc((*musician)->name);
	(*musician)->name[size - ONE] = (char*)malloc((strlen(name) + ONE) * sizeof(char)); // allocating the place for the new name
	checkAlloc((*musician)->name[size - ONE]);
	strcpy((*musician)->name[size - ONE], name);
}

bool ListIsEmpty(MPIList* lst)
{
	if (lst->head == NULL)
		return true;
	return false;
}

bool tokenIsName(char* str1, char* str2)
{ // This function checks if str1 in a name
	if (((str1[ZERO] >= 'A' && str1[ZERO] <= 'Z') || (str1[ZERO] >= 'a' && str1[ZERO] <= 'z')) && ((str2[ZERO] >= 'A' && str2[ZERO] <= 'Z') || (str2[ZERO] >= 'a' && str2[ZERO] <= 'z')))
		return true;
	return false; // if str2 in number -> str1 is *not* a name
}

Musician* allocateMusician()
{ // This function creates a new musician ptr
	Musician* musician = (Musician*)malloc(sizeof(Musician));
	checkAlloc(musician);
	musician->name = (char**)malloc(sizeof(char*)); // at first - the size of names arr is 1
	checkAlloc(musician->name);
	musician->numOfNames = ZERO;
	musician->instruments = makeEmptyList();
	musician->chosen = false;
	return musician;
}

MPIList makeEmptyList()
{
	MPIList lst;
	lst.head = NULL;
	lst.tail = NULL;
	return lst;
}

void freeMusiciansGroupArr(Musician** arr, int size)
{
	int i;
	for (i = 0; i < size; i++)
		freeMusician(arr[i]); // freeying each musician and it's data
	free(arr);
}

void freeMusician(Musician* musician)
{
	int i;
	for (i = 0; i < musician->numOfNames; i++)
		free(musician->name[i]); // freeying each name in the names arr
	free(musician->name); // freeying the names arr
	freeList(musician->instruments); // freeying the instruments list
	free(musician); 
}

void freeList(MPIList lst)
{
	ListNode* p = lst.head, *temp;
	while (p != NULL)
	{
		free(p->data); // freeying MusicianPriceInstrument*
		temp = p;
		p = p->next;
		free(temp);
	}
}

void checkAlloc(void* ptr)
{
	if (ptr == NULL)
	{
		printf("System allocation had failed, exiting the program.\n");
		exit(1);
	}
}

void checkFile(FILE* file)
{
	if (file == NULL)
	{
		printf("An error had been occurred while opening a file, exiting the program\n");
		exit(1);
	}
}