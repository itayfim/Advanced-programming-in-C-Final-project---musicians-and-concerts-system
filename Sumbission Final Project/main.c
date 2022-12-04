// Itay Fhima || Shani Glick
// 312182009  || 212212484

#include "GeneralHeader.h"

void main(int argc, char** argv)
{
	if (argc != THREE)
	{
		printf("An error occured while entering the program parameters input.\n");
		printf("Please enter the following input: <instruments text name>, <musicians text name>.\n");
		exit(1);
	}

	InstrumentTree instrumentsTree = buildTree(argv[ONE]); // building the instruments tree from the instruments file
	int MusiciansGroupSize, MusiciansCollectionSize, num_of_concerts;
	Musician** MusiciansGroup = createMusiciansArr(instrumentsTree, argv[TWO], &MusiciansGroupSize); // creating MusiciansGroup arr, and updating it's size
	MusicianColl* MusiciansCollection = instrumentsDatabaseConstruction(MusiciansGroup, MusiciansGroupSize,
		instrumentsTree, &MusiciansCollectionSize); // creating MusicianCollection arr, and updating it's size
	Concert* Concerts = getConcerts(instrumentsTree, &num_of_concerts); // getting the concerts from the user (keyboard)
	find_players_for_concerts(Concerts, num_of_concerts, MusiciansCollection); // finding players for each concert and prints the data

	// freeying all the data in the program:
	freeTree(instrumentsTree);
	freeMusiciansGroupArr(MusiciansGroup, MusiciansGroupSize);
	freeMusiciansCollection(MusiciansCollection, MusiciansCollectionSize);
	freeConcerts(Concerts, num_of_concerts);
}

