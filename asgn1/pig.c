#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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


	int numPlayers;
	int seed;

	int numPlayersInput = 0;
	scanf("%d", &numPlayersInput);

	if (numPlayersInput < 2 || numPlayersInput > 10)
	{ 
		fprintf(stderr , "Invalid number of players. Using 2 instead .\n");
		numPlayers = 2;
	}
	else
	{
		numPlayers = numPlayersInput;
	}
	
	int inputSeed = 0;
        scanf("%d", &inputSeed);

        if (inputSeed < 0 || inputSeed > pow(2, 31)-1)
        {
                fprintf(stderr , "Invalid random seed. Using 2021 instead .\n");
                seed = 2021;
        }
        else
        {
                seed = inputSeed;
        }

	srandom(seed);
	

	
	printf("%d\n", numPlayers);
	printf("%lu\n", random());
	
}
