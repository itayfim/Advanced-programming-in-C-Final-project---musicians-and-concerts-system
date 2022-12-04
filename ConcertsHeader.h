// Itay Fhima || Shani Glick
// 312182009  || 212212484

#ifndef _Concerts_
#define _Concerts_

typedef struct
{
	int day, month, year, min;
	float hour;
} Date;

typedef struct
{
	int num; // כמה מאותו כלי
	int inst;	// מספר מזהה של כלי נגינה 
	char importance;	// (1 / 0) האם לכלי נגינה זה יש תקציב עבור נגנים יקרים 
	char* inst_name; 
} ConcertInstrument;

typedef struct lnode
{
	ConcertInstrument inst;
	struct lnode* next;
}CILNode;

typedef struct list
{
	CILNode* head;
	CILNode* tail;
}CIList;

typedef struct
{
	Date date_of_concert; // ההופעה קיום תאריך
	char* name; //שם ההופעה 
	CIList instruments;  //ConcertInstrument כלי הנגינה ברשימה מקושרת של 
} Concert;

typedef struct
{
	int insId;
	int size;
	MusiciansOnIns* Preformers;
}MusicianForCon;

Concert* getConcerts(InstrumentTree tree, int* num_of_concerts);
CILNode* createNewCIListNode(int num, int inst, char* importance, char* inst_name, CILNode* next);
void getNameAndDate(char* concertData, Concert* concert);
void getIns(Concert* concert, InstrumentTree tree);
void insertDataToEndList(CIList* lst, int num, int inst, char* importance, char* inst_name);
void makeEmptyCIList(CIList* lst);
void find_players_for_concerts(Concert* concerts, int num_of_concerts, MusicianColl* MusiciansCollection);
void find_players(Concert concert, MusicianColl* MusiciansCollection);
void printConcert(Concert concert, bool notFound, MusicianForCon* musicianForCon, int sizeOfArray);
void printPlayers(Concert concert, MusicianForCon* musicianForCon, int sizeOfArray, int* sum);
void selectMusicians(MusiciansOnIns* musicianForCon, int numOfMus, MusicianColl musicianOfIns, bool* notFound);
void freeConcerts(Concert* concerts, int num_of_concerts);
void freeMusicianForCon(MusicianForCon* musicianForCon, int sizeOfArray);
void print_musician_name(Musician* musician);
int comparePriceAscending(void* elem1, void* elem2);
int comparePriceDescending(void* elem1, void* elem2);
int isEmpty(CIList* lst);
char* getLine();

#endif

