//
//  player.h
//  Penguins
//
//  Created by Dominik Kurasbediani on 2018-10-24.
//  Copyright © 2018 Dominik Kurasbediani. All rights reserved.
//

#ifndef player_h
#define player_h
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "penguin.h"
#include "file_management.h"
#include "tiles.h"
typedef struct
{
	char name[16];
 	int numberOfPenguins;
 	//create a list of penguins (instances of Penguin struct)
 	//put them into an array called penguinList
	penguin penguinList[2];	//struct penguin penguinList[*p->numberOfPenguins];
	int playerID;
	int score;
}player, player_t;

void setPlayer(player *player, char *name, int numberOfPenguins, int playerID, int score)
{
	strcpy(player->name, name);
	player->numberOfPenguins = numberOfPenguins;
	player->playerID = playerID;
	player->score = score;
}

void print_player(player *player)
{
	printf("\n\nPlayer's name: %s\nPlayer's number of penguins: %d\n player's ID: %d\nPlayer's score: %d\n\n\n",
		   player->name, player->numberOfPenguins, player->playerID, player->score);
}

void init_player(player *player)
{
	strcpy(player->name, "");
	player->numberOfPenguins = 0;
//	player->penguinList = NULL;
	player->playerID = 0;
	player->score = 0;
}
void increase_penguins(player *player)
{
	player->numberOfPenguins++;
}

void populate_playerList(player *playerList, tile_t **board, int rows, int cols, int numofplayer)
{
	for(int i = 0; i < rows; i ++)
	{
		for(int j = 0; j < cols; j++)
		{
			for (int k = 0; k < numofplayer; k++)
			{
				if(board[i][j].playerID == playerList[k].playerID)
				{
					playerList[k].numberOfPenguins++;
				}
			}
		}
	}
	printf("\n");
}
void test_player(char *pathname, tile_t **board)
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
//	print_player(&playerList[0]);
//	print_player(&playerList[1]);
//	print_player(player1);
//	print_player(player2);
	//	board[0][0].fishNum = 0;
	deallocate_mem(board, columns);
	free(player1);
	free(player2);
	printf("\n");
}
#endif /* player_h */
