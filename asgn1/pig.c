#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "names.h"



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

	int numPlayers = 2;
	int seed = 2021;

	printf("How many players? ");
	int numPlayersInput = 0;
	scanf("%d", &numPlayersInput);

	if (numPlayersInput < 2 || numPlayersInput > 10)
	{ 
		fprintf(stderr , "Invalid number of players. Using 2 instead .\n");
	}
	else
	{
		numPlayers = numPlayersInput;
	}
	
	printf("Random seed: ");
	unsigned int inputSeed = 0;
        scanf("%u", &inputSeed);

        if (inputSeed < 0 || inputSeed > (pow(2.0, 31.0)-1))
        {
                fprintf(stderr , "Invalid random seed. Using 2021 instead .\n");
        }
        else
        {
                seed = inputSeed;
        }

	srandom(seed);
	

	int i;
	int r;
	int points[10] = {0,0,0,0,0,0,0,0,0,0};

	for (i = 0; i < numPlayers; i+=1) 
	{	
		r = random() % 7;
		printf("%s rolls the pig...pig lands on %d\n", names[i], pig[r]);
		points[i] += pig[r];
		while (pig[r] != SIDE)
		{
			r = random() % 7;
                	printf("%s rolls the pig...pig lands on %d\n", names[i], pig[r]);
			points[i] += pig[r];
		}
		if (points[i] >= 50) 
		{
			printf("%s wins with 100 points!\n", names[i]);
			break;
		}
		if (i == numPlayers-1)
		{
			i = -1;
		} 
	}

	int j = 0;
	for (j=0;j<10;j++)
	{
		printf("%d ", points[j]);
	}

}
