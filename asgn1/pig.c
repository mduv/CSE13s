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
	

	printf("%d\n", numPlayers);
	printf("%lu\n", random());
}
