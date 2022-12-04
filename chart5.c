// Itay Fhima || Shani Glick
// 312182009  || 212212484

#include "GeneralHeader.h"

Concert* getConcerts(InstrumentTree tree, int* num_of_concerts)
{//This function gets the information of the concerts
	Concert* concerts = (Concert*)malloc(sizeof(Concert));
	checkAlloc(concerts);
	int logSize, phsSize;
	logSize = 0;
	phsSize = INIT_CON_SIZE;
	char* concertData = getLine();
	while (concertData[ZERO] != EMPTY_LINE)
	{
		if (logSize == phsSize)
		{
			phsSize = phsSize * 2;
			concerts = (Concert*)realloc(concerts, phsSize * sizeof(Concert));
			checkAlloc(concerts);
		}
		getNameAndDate(concertData, &(concerts[logSize]));
		getIns(&(concerts[logSize]), tree);
		logSize++;
		concertData = getLine();
	}
	*num_of_concerts = logSize;
	return concerts;
}

void getNameAndDate(char* concertData, Concert* concert)
{//This function gets the name and date of the concert
	char* seps = " :";
	char* con_name = strtok(concertData, seps);
	int len = strlen(con_name);
	concert->name = (char*)malloc((len + 1) * sizeof(char));
	checkAlloc(concert->name);
	strcpy(concert->name, con_name);
	concert->date_of_concert.day = atoi(strtok(NULL, seps));
	concert->date_of_concert.month = atoi(strtok(NULL, seps));
	concert->date_of_concert.year = atoi(strtok(NULL, seps));
	concert->date_of_concert.hour = (float)atof(strtok(NULL, seps));
	concert->date_of_concert.min = atoi(strtok(NULL, seps));
}

void getIns(Concert* concert, InstrumentTree tree)
{//This function gets the information about the instruments that will be in concert
	int insId, num;
	char* seps = " ", * instrument, * importance;
	CIList conInsList;
	makeEmptyCIList(&conInsList);
	instrument = strtok(NULL, seps);
	insId = findInsId(tree, instrument);
	num = atoi(strtok(NULL, seps));
	importance = strtok(NULL, seps);
	while (instrument != NULL) // There are more instruments at the concert
	{
		insertDataToEndList(&conInsList, num, insId, importance, instrument);
		instrument = strtok(NULL, seps);
		if (instrument != NULL) {
			insId = findInsId(tree, instrument);
			num = atoi(strtok(NULL, seps));
			importance = strtok(NULL, seps);
		}
	}
	concert->instruments = conInsList;
}

void insertDataToEndList(CIList* lst, int num, int inst, char* importance, char* inst_name)
{
	CILNode* newNode = createNewCIListNode(num, inst, importance, inst_name, NULL);
	if (isEmpty(lst))
		lst->head = lst->tail = newNode;
	else
	{
		lst->tail->next = newNode;
		lst->tail = newNode;
	}
}

CILNode* createNewCIListNode(int num, int inst, char* importance, char* inst_name, CILNode* next)
{
	int len;
	CILNode* newNode = (CILNode*)malloc(sizeof(CILNode));
	checkAlloc(newNode);
	newNode->inst.num = num; //Number of instruments of the currnt instrument
	newNode->inst.inst = inst; //The Id of the instrument
	newNode->inst.importance = importance[ZERO]; // If this instrument is important
	len = strlen(inst_name);
	newNode->inst.inst_name = (char*)malloc((len + 1) * sizeof(char));
	checkAlloc(newNode->inst.inst_name);
	strcpy(newNode->inst.inst_name, inst_name); // The instrument name
	newNode->next = next;
	return newNode;
}

int isEmpty(CIList* lst)
{
	return lst->head == NULL;
}

void makeEmptyCIList(CIList* lst)
{
	lst->head = lst->tail = NULL;
}

char* getLine()
{//A function that gets a line of input on a single concert
	char ch;
	int logSize = 0, phsSize = INIT_SIZE;
	char* concertData = (char*)malloc(INIT_SIZE * sizeof(char));
	checkAlloc(concertData);
	ch = getchar();
	while (ch != END_OF_LINE)
	{
		if (logSize == phsSize)
		{
			phsSize = phsSize * 2;
			concertData = (char*)realloc(concertData, phsSize * sizeof(char));
			checkAlloc(concertData);
		}
		concertData[logSize] = ch;
		logSize++;
		ch = getchar();
	}
	if (logSize + ONE >= phsSize) //If there is no space left for '\0' in the string
	{
		phsSize++;
		concertData = (char*)realloc(concertData, phsSize * sizeof(char));
		checkAlloc(concertData);
	}
	concertData[logSize] = END_OF_WORD;
	return concertData;
}

void find_players_for_concerts(Concert* concerts, int num_of_concerts, MusicianColl* MusiciansCollection)
{//The function runs on each concert and sends it to a function that finds musicians for it
	int i;
	for (i = 0; i < num_of_concerts; i++)
		find_players(concerts[i], MusiciansCollection);
}

void find_players(Concert concert, MusicianColl* MusiciansCollection)
{//A function that creates an array of musicians for the concert as requested
	CILNode* curr = concert.instruments.head; //The first musical instrument
	int insId, numOfMus, logSize = 0, phsSize;
	bool notFound = false; //When no musicians are found it will become true
	char importance; // If the instrument is important
	MusicianForCon* musicianForCon;
	musicianForCon = (MusicianForCon*)malloc(INIT_CON_SIZE * sizeof(MusicianForCon));
	checkAlloc(musicianForCon);
	phsSize = INIT_CON_SIZE;
	while (curr != NULL && !(notFound))
	{
		if (logSize == phsSize) {
			phsSize *= 2;
			musicianForCon = (MusicianForCon*)realloc(musicianForCon, phsSize * sizeof(MusicianForCon));
			checkAlloc(musicianForCon);
		}
		importance = curr->inst.importance;
		insId = curr->inst.inst;
		//Sort the array of musicians playing the 'insId' instrument by price
		if (importance == '0')
			qsort(MusiciansCollection[insId].arr, MusiciansCollection[insId].logSize, sizeof(MusiciansOnIns), comparePriceAscending);
		else
			qsort(MusiciansCollection[insId].arr, MusiciansCollection[insId].logSize, sizeof(MusiciansOnIns), comparePriceDescending);
		numOfMus = curr->inst.num; //Number of instruments of the currnt instrument
		musicianForCon[logSize].insId = insId;
		musicianForCon[logSize].size = numOfMus;
		musicianForCon[logSize].Preformers = (MusiciansOnIns*)malloc(numOfMus * sizeof(MusiciansOnIns));
		checkAlloc(musicianForCon[logSize].Preformers);
		selectMusicians(musicianForCon[logSize].Preformers, numOfMus, MusiciansCollection[insId], &notFound);
		curr = curr->next;
		logSize++;
	}
	printConcert(concert, notFound, musicianForCon, logSize);
	freeMusicianForCon(musicianForCon, logSize);
}

int comparePriceAscending(void* elem1, void* elem2)
{
	MusiciansOnIns* a = (MusiciansOnIns*)elem1;
	MusiciansOnIns* b = (MusiciansOnIns*)elem2;
	return (a->price - b->price);
}

int comparePriceDescending(void* elem1, void* elem2)
{
	MusiciansOnIns* a = (MusiciansOnIns*)elem1;
	MusiciansOnIns* b = (MusiciansOnIns*)elem2;
	return (b->price - a->price);
}

void printConcert(Concert concert, bool notFound, MusicianForCon* musicianForCon, int sizeOfArray)
{
	int sum = 0;
	if (notFound)
		printf("Could not find musicians for the concert %s\n", concert.name);
	else
	{
		printf("%s ", concert.name);
		printf("%02d %02d %4d ", concert.date_of_concert.day, concert.date_of_concert.month, concert.date_of_concert.year);
		printf("%.0f:%02d: ", concert.date_of_concert.hour, concert.date_of_concert.min);
		printPlayers(concert, musicianForCon, sizeOfArray, &sum);
		printf("Total cost: %d.\n", sum);
	}
}

void printPlayers(Concert concert, MusicianForCon* musicianForCon, int sizeOfArray, int* sum)
{
	int i, j;
	CILNode* curr = concert.instruments.head;
	for (i = 0; i < sizeOfArray; i++)
	{
		for (j = 0; j < musicianForCon[i].size; j++)
		{
			print_musician_name(musicianForCon[i].Preformers[j].musician);
			printf("%s ", curr->inst.inst_name);
			if (i == (sizeOfArray - 1) && j == (musicianForCon[i].size - 1))
				printf("(%.0f). ", musicianForCon[i].Preformers[j].price);
			else
				printf("(%.0f), ", musicianForCon[i].Preformers[j].price);
			musicianForCon[i].Preformers[j].musician->chosen = false; //Makes the musicians available for the next concert
			*sum += musicianForCon[i].Preformers[j].price;
		}
		curr = curr->next;
	}
}

void print_musician_name(Musician* musician)
{
	int i;
	for (i = 0; i < musician->numOfNames; i++)
	{
		printf("%s ", musician->name[i]);
	}
	printf("- ");
}

void selectMusicians(MusiciansOnIns* musicianForCon, int numOfMus, MusicianColl musicianOfIns, bool* notFound)
{//A function that selects from the sorted array which musicians will perform at the concert
	int i = 0, j = 0;
	//while We did not exceed the number of musicians who requested or the number of musicians available
	while (i < numOfMus && j < musicianOfIns.logSize)
	{
		if (!((musicianOfIns.arr[j].musician)->chosen))//If the player isn't selected to play another instrument
		{
			musicianForCon[i] = musicianOfIns.arr[j];
			(musicianOfIns.arr[j].musician)->chosen = true;
			i++;
		}
		j++;
	}
	if (numOfMus != i) //If there weren't enough musicians to choose from
		*notFound = true;
}

void freeConcerts(Concert* concerts, int num_of_concerts)
{
	int i;
	CILNode* curr, * temp;
	for (i = 0; i < num_of_concerts; i++)
	{
		curr = concerts[i].instruments.head;
		while (curr != NULL)
		{
			temp = curr->next;
			free(curr); // free instrument node
			curr = temp;
		}
		free(concerts[i].name);
	}
	free(concerts);
}

void freeMusicianForCon(MusicianForCon* musicianForCon, int sizeOfArray)
{
	int i, j;
	for (i = 0; i < sizeOfArray; i++)
	{
		free(musicianForCon[i].Preformers);
	}
	free(musicianForCon);
}