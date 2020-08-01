//
//  movement.h
//  Penguins
//
//  Created by Dominik Kurasbediani on 2018-11-17.
//  Copyright © 2018 Dominik Kurasbediani. All rights reserved.
//
//

#ifndef movement_h
#define movement_h

#include <stdlib.h>
#include "player.h"
#include "file_management.h"
#include "tiles.h"
/*TODO:
 1. Implement all() - DONE and TESTED
 2. Implement annulate(); DONE and TESTED
 3. Implement turnsLeft();
 4. Implement phaseIsOver(); DONE
 5. Implement isValidMove();
 6. Implement makeMove(); DONE
 7. Implement moveOver(); DONE (gotta check when sober)
 8. Implement play(); - Almost done
 */
int movesLeft(tile_t **board, player *player);
int phaseIsOver(player *playerList, tile_t **board);
int returnDirection(tile_t **board, int *move, penguin *penguin);
int isValidMove(int *move, tile_t **board, player *player, penguin *penguin);
void makeMove(int *move, tile_t **board, player *player, penguin *penguin);
int roundOver(int *moveOverList);
int play(int numberOfPlayers, tile_t **board, player *playerList);

void annulate(int *array)
//set every element of array to 0;
{
	for (int element = 0; element < sizeof(array)/sizeof(array[0]); element++)
	{
		array[element] = 0;
	}
}

int all(int *array)
// returns 1 is all elements in an array == 1, 0 otherwise
{
	// since we are just gonna be dealing with arrays of 1s and 0s, if sum == size of the array, all elements are 1s
	int sum = 0;
	for(int i = 0; i<sizeof(array)/sizeof(array[0]); i++)
	{
		sum+=array[i];
	}
	if (sum == sizeof(array)/sizeof(array[0]))
	{
		return 1;
	}
	return 0;
}
int movesLeft(tile_t **board, player *player)
// returns 1 if there is at least one move available for the player
{
	for(int i = 0; i < player->numberOfPenguins; i++) // go through all the penguins, if at least one can be moved, return 1
	{
		int move[2];
		// tile above
		move[0] = player->penguinList[i].position[0]+1;
		move[1] = player->penguinList[i].position[1];
		if (isValidMove(move, board, player, &player->penguinList[i]))
		{
			return 1;
		}
		// tile below
		else
		{
			move[0] = player->penguinList[i].position[0]-1;
			move[1] = player->penguinList[i].position[1];
			if (isValidMove(move, board, player, &player->penguinList[i]))
			{
				return 1;
			}
			else
			{
			// tile to the left
				move[0] = player->penguinList[i].position[0];
				move[1] = player->penguinList[i].position[1]-1;
				if (isValidMove(move, board, player, &player->penguinList[i]))
				{
					return 1;
				}
				else
				{
					// tile to the right
					move[0] = player->penguinList[i].position[0];
					move[1] = player->penguinList[i].position[1]+1;
					if (isValidMove(move, board, player, &player->penguinList[i]))
					{
						return 1;
					}
				}
			}
		
		}
		
	}
	return 0;
}
int phaseIsOver(player *playerList, tile_t **board)
// determines whether the movement phase is over
{
	int size = sizeof(playerList)/sizeof(playerList[0]);
	int array[size];
	for(int i = 0; i < size; i++)
	{
		array[i] = movesLeft(board, &playerList[i]);
	}
	if (all(array))
	{
		return 1;
	}
	return 0;
}
int returnDirection(tile_t **board, int *move, penguin *penguin)
/*
 Returns a value corresponding to the direction the given penguin is moving
 returns 1 if moving up
		 2 if moving down
 		 3 if moving left
 		 4 is moving right
 */
{
	int m = 0, n = 0;
	//find_dimensions_from_board(board, &m, &n);
	if (!(move[0] < 0 || move[0] > m || move[1] < 0 || move[1] > n)) // checking whether the move is within the board
	{
		if(move[1] == penguin->position[1]) // if the x coordinate is the same, it's either moving up or down
		{
			if(move[0] < penguin->position[0]) return 1;
			else return 2;
		}
		else if (move[0] == penguin->position[0])
		{
			if (move[1] < penguin->position[1]) return 3;
			else return 4;
		}
	}
	return 0;
}
int isValidMove(int *move, tile_t **board, player *player, penguin *penguin)
// determines whether the given move is valid for a given player

{
}

void makeMove(int *move, tile_t **board, player *player, penguin *penguin) // Applies the move
{
	int m = move[0], n = move[0];
	int old_m = penguin->position[0], old_n = penguin->position[1];
	board[old_m][old_n].isPenguin = 0; // removes the penguin from the old position
	board[old_m][old_n].active = 0; // makes the old tile inactive
	board[old_m][old_n].playerID = 0; // sets the old tile's playerID to 0
	board[m][n].isPenguin = 1; // sets the new tile to have a penguin on it
	penguin->position[0] = m; // sets the penguin's new y coord;
	penguin->position[1] = n; // sets the penguin's new x coord
	player->score += board[m][n].fishNum; // adds the number of fish on the new tile to player's score
	board[m][n].playerID = player->playerID; // sets the new tile's playerID to the playerID
	board[m][n].fishNum = 0; // sets the new tiles num of fish to 0
}

int roundOver(int *moveOverList) // checks whether the move is over
{
	if (all(moveOverList) == 1)
	{
		return 1;
	}
	return 0;
}

int play(int numberOfPlayers, tile_t **board, player *playerList) // Main algorithm of movement phase
{
	
	while (phaseIsOver(playerList, board) != 1) // checks if the movement phase is over, run moves until it is
	{
		int moveOverList[numberOfPlayers];
		int playerIndex = 0;
		while (!roundOver(moveOverList))
		{
			if(playerIndex >= numberOfPlayers) break;
			
			int move[2];
			int choiceOfPenguin = 0;
			// Print the coordinates of every penguin available to the player <------ IMPLEMENT
			scanf("%d", &choiceOfPenguin);
			printf("Enter your move (m, n):\n");
			scanf("%d,%d", &move[0], &move[1]); // keyboard input of coordinates
			if (isValidMove(move, board, &playerList[playerIndex], &playerList[playerIndex].penguinList[choiceOfPenguin]) == 1)
				// if the entered move is valid, applies it
			{
				makeMove(move, board, &playerList[playerIndex], &playerList[playerIndex].penguinList[choiceOfPenguin]);
				moveOverList[playerIndex] = 1;
				playerIndex++;
				
			}
			else
			{
				printf("Invalid move");
			}
		}
			 // at this point every player made a move
		
	}// at this point moveOverList contains only 1s
		//annulate(moveOverList); //annulates moveOverList;
		// now moverOverList is all 0s
	
	// The loop exits when there are no moves left for all players
	return 1;
}
#endif /* movement_h */
