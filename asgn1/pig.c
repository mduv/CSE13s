#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "names.h"
#include <string.h>
#include <limits.h>


int main() {

	typedef  enum { SIDE , RAZORBACK , TROTTER , SNOUTER , JOWLER } Position;
	const  Position  pig[7] = {
		SIDE ,
		SIDE ,
		RAZORBACK ,
		TROTTER ,
		SNOUTER ,
		JOWLER ,
		JOWLER
	};

	const int Points[7] = {
		0, 
		0,
		10, 
		10,
		15, 
		5,
		5 
	};


	char mapstr[7][20] = {
		"on side",
		"on side",
		"on back",
		"upright",
		"on snout",
		"on ear",
		"on ear"

	};	
	int numPlayers = 2;
	int seed = 2021;

	printf("How many players? ");
	long userInput = -1;
	scanf("%ld", &userInput);
	if (userInput < 2 || userInput > 10)
	{ 
		fprintf(stderr , "Invalid number of players. Using 2 instead .\n");
		numPlayers = 2;
	} else {
		numPlayers = userInput;
	} 

	printf("Random seed: ");
	userInput = -1;
	scanf("%ld", &userInput);


	if ((userInput < 0) || (userInput > 4294967295U))
	{
		fprintf(stderr , "Invalid random seed. Using 2021 instead .\n");
		seed = 2021; 
	} else {
		seed = userInput; 
	}

	srandom(seed);

	int roll;
	int points[10] = {0,0,0,0,0,0,0,0,0,0};


	int currentPlayer = 0;
	printf("%s rolls the pig...", names[currentPlayer]);
	while (1) {
		roll = random() % 7;
		points[currentPlayer] += Points[roll];
		printf("pig lands %s ", mapstr[roll]);
		if (pig[roll] == SIDE)
		{
			currentPlayer += 1;
			currentPlayer %= numPlayers;
			printf("\n%s rolls the pig...", names[currentPlayer]);
		} else {
			if (points[currentPlayer] >= 100)
			{
				printf("\n%s wins with 100 points!\n", names[currentPlayer]);
				break;
			}
		}
	}


}
