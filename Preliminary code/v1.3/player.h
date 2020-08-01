//
//  player.h
//  Penguins
//
//  Created by Dominik Kurasbediani on 2018-10-24.
//  Copyright © 2018 Dominik Kurasbediani. All rights reserved.
//

#ifndef player_h
#define player_h

#include "penguin.h"

typedef struct
{
	char name[16];
 	int numberOfPenguins;
 	//create a list of penguins (instances of Penguin struct)
 	//put them into an array called penguinList
	penguin penguinList[9];	//struct penguin penguinList[*p->numberOfPenguins];
	int playerID;
	int score;
}player;

void createPlayers(int numberOfPlayers, int playerList[numberOfPlayers][3], int penguins)
{
	// Assign the correct IDs for the correct numbers of players. Assign the initial number of available penguins for each player. Give initial score.
	// playerList[i][0] = playerID;
	// playerList[i][1] = penguinsAvailable;
	// playerList[i][2] = score;
	int penguinsAvailable = penguins, score = 0;
	for (int i = 0; i <= numberOfPlayers; i++)
	{
		playerList[i][0] = i; //playerID
		playerList[i][1] = penguinsAvailable; //penguinsAvailble
		playerList[i][2] = score; //playerScore
	}
}

void increaseScore(player player, int scoreIncreaseValue)
{
	player.score += scoreIncreaseValue;
}

void decreasePenguins(player *p)
{
	p->numberOfPenguins -= 1;
}


#endif /* player_h */
