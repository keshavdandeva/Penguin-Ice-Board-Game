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
int movesLeft(tile_t **board, player *player, char *pathname);
int phaseIsOver(player *playerList, tile_t **board, char *pathname);
int returnDirection(tile_t **board, int *move, penguin *penguin);
int isValidMove(int *move, tile_t **board, player *player, penguin *penguin);
void makeMove(int *move, tile_t **board, player *player, penguin *penguin);
int roundOver(int *moveOverList);
int play(int numberOfPlayers, tile_t **board, player *playerList, char *pathname);

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
int movesLeft(tile_t **board, player *player, char *pathname)
// returns 1 if there is at least one move available for the player
{
	int m = 0, n = 0;
	find_size(&m, &n, pathname);
	for(int i = 0; i < player->numberOfPenguins; i++) // go through all the penguins, if at least one can be moved, return 1
	{
		int move[2];
		// tile above
		move[0] = player->penguinList[i].position[0]+1;
		move[1] = player->penguinList[i].position[1];
		if (move[0] < m && isValidMove(move, board, player, &player->penguinList[i])) // checks whether its on the border and checks whether there is an available tile
		{
			return 1;
		}
		// tile below

		move[0] = player->penguinList[i].position[0]-1;
		move[1] = player->penguinList[i].position[1];
		if (move[0] > m && isValidMove(move, board, player, &player->penguinList[i]))
		{
			return 1;
		}

		// tile to the left
			move[0] = player->penguinList[i].position[0];
			move[1] = player->penguinList[i].position[1]-1;
		if (move[1] > n && isValidMove(move, board, player, &player->penguinList[i]))
		{
			return 1;
		}

		// tile to the right
		move[0] = player->penguinList[i].position[0];
		move[1] = player->penguinList[i].position[1]+1;
		if (move[1] < n && isValidMove(move, board, player, &player->penguinList[i]))
		{
			return 1;
		}
		
	}
	return 0;
}
int phaseIsOver(player *playerList, tile_t **board, char *pathname)
// determines whether the movement phase is over
{
	int size = sizeof(playerList)/sizeof(playerList[0]);
	int array[size];
	for(int i = 0; i < size; i++)
	{
		array[i] = movesLeft(board, &playerList[i], pathname);
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
	int m = move[0], n = move[1];
	if (board[m][n].active == 1) // check whether the tile is active
	{
		if(board[m][n].playerID == 0) // check whether the new tile is unoccupied
		{
			// check whether there are inactive tiles on the way
			// check whether there are penguins on the way
			int direction = returnDirection(board, move, penguin);
			// check case by case whether there is an inactive tile or a penguin on the way
			int temp[2];
			temp[0] = penguin->position[0];
			temp[1] = penguin->position[1];
			// checking tile by tile until reaches end tile
			if(direction == 1) // moving up
			{
				while (temp[0] != m)
				{
					temp[0]--;
					if (board[temp[0]][temp[1]].isPenguin || !board[temp[0]][temp[1]].active)
					{
						return 0;
					}
				}
			}
			else if(direction == 2) // moving down
			{
				while (temp[0] != m)
				{
					temp[0]++;
					if (board[temp[0]][temp[1]].isPenguin || !board[temp[0]][temp[1]].active)
					{
						return 0;
					}
				}
			}
			else if (direction == 3) // moving left
			{
				while (temp[1] != n)
				{
					temp[1]--;
					if (board[temp[0]][temp[1]].isPenguin || !board[temp[0]][temp[1]].active)
					{
						return 0;
					}
				}
			}
			else if (direction == 4) // moving right
			{
				while (temp[1] != n)
				{
					temp[1]++;
					if (board[temp[0]][temp[1]].isPenguin || !board[temp[0]][temp[1]].active)
					{
						return 0;
					}
				}
			}
		}
	}
	return 1; // if the program reaches this point, it passed all the tests, so it returns 1
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

int play(int numberOfPlayers, tile_t **board, player *playerList, char *pathname) // Main algorithm of movement phase
{
	
	while (phaseIsOver(playerList, board, pathname) != 1) // checks if the movement phase is over, run moves until it is
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

void test_movement(tile_t **board, char *pathname)
{
	int rows = 0, columns = 0;
	find_size(&rows, &columns, pathname);
	board = (tile_t**)realloc(board, rows * sizeof(tile_t *));
	//int row_count = sizeof(*arr);
	if (board == NULL)
	{
		printf("Memory failed to allocate\n");
		exit(1);
	}
	for (size_t i=0; i<rows; i++)
	{
		board[i] = (tile_t*)calloc(columns, sizeof(tile_t));
		if (board[i]==NULL)
		{
			printf("Memory failed to allocate\n");
			exit(0);
		}
	}
	player playerList[2];
	
	player *player1 = malloc(sizeof(player));
	init_player(player1);
	player1->playerID = 1;
	strcpy(player1->name, "Domi");
	
	player *player2 = malloc(sizeof(player));
	init_player(player2);
	player2->playerID = 2;
	strcpy(player2->name, "AmOur");
	
	playerList[0] = *player1;
	playerList[1] = *player2;
	read_from_file(pathname, board);
	populate_playerList(playerList, board, rows, columns, 2);
	//print_board(board, rows, columns);
	print_player(&playerList[0]);
	print_player(&playerList[1]);
	printf("%d\n", movesLeft(board, &playerList[0], pathname));
	deallocate_mem(board, columns);
	free(player1);
	free(player2);
	printf("\n");
}

#endif /* movement_h */
