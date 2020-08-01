#ifndef player_h
#define player_h
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "penguin.h"
//#include "file_management.h"
#include "tiles.h"
typedef struct
{
	char name[16];
 	int numberOfPenguins;
 	//create a list of penguins (instances of Penguin struct)
 	//put them into an array called penguinList
	penguin *penguinList;	//struct penguin penguinList[*p->numberOfPenguins];
	int playerID;
	int score;
}player, player_t;
void find_size1(int *m, int *n, char *pathname)
/* The function populates m with the number of rows and n with the number of columns. Necessary to find out the size of the board. */
{
	/* Populating M and N */
	// figuring out the size size of the board. First line of the file.
	FILE *fp;
	fp = fopen(pathname, "r");
	int rows = 0, columns = 0;
	fscanf(fp, "%d %d\n", &rows, &columns);

	/* at this point we know the size of the board */
	*m = rows;
	*n = columns;
	fclose(fp);
}
int num_of_penguins1(int playerID, tile_t **board, char *pathname)
{
	int rows = 0, cols = 0;
	find_size1(&rows, &cols, pathname);
	int num = 0;
	for(int r = 0; r < rows; r++)
	{
		for(int c = 0; c < cols; c++)
		{
			if(board[r][c].playerID == playerID)
			{
				num++;
			}
		}
	}
	return num;
}
/*void make_penguins(char *pathname, player_t *player, tile_t **board)
{
	int rows = 0, cols = 0;
	find_size1(&rows, &cols, pathname);
	printf("make_penguins: size found\n");
	printf("Size: %dx%d\n", rows, cols);
	player->penguinList = malloc(sizeof(penguin)*num_of_penguins1(player->playerID, board, pathname));
	for (int k = 1; k < num_of_penguins1(player->playerID, board, pathname); k++)
		{
		penguin *penguin = malloc(sizeof(penguin));
		printf("make_penguins: mem for a penguin allocated\n");
		penguin->position[0] = -1;
		penguin->position[1] = -1;
		printf("make_penguins: penguin #%d initialized\n", k+1);
		player->penguinList[k] = *penguin;
		printf("make_penguins:penguin put in penguinList\n" );
		printf("%d th penguin in penguinList = (%d, %d)\n", k, player->penguinList[k].position[0], player->penguinList[k].position[1]);
		for(int r = 0; r < rows; r++)
		{
			for(int c = 0; c < cols; r++)
			{
				printf("k = %d, r = %d, c = %d, playerID = %d\n", k, r, c, board[r][c].playerID);

					if (player->playerID == board[r][c].playerID)
					{

						player->penguinList[k].position[0] = r;
						player->penguinList[k].position[1] = c;
						printf("make_penguin: Position of %d penguin changed to (%d, %d)\n", k+1, r, c);

					}
					
			}

			}

		}
	}*/
/*
void free_penguins(penguin_t *penguinList)
{
	int size = sizeof(penguinList)/sizeof(penguinList[0]);
	for (int i = 0; i < size; ++i)
	{
		free(penguinList[i]);
	}
	free(penguinList);
}*/
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
}

//void test_player(char *pathname, tile_t **board)
//{
//	int rows = 0, columns = 0;
//	find_size(&rows, &columns, pathname);
//	board = (tile_t**)realloc(board, rows * sizeof(tile_t *));
//	//int row_count = sizeof(*arr);
//	if (board == NULL)
//	{
//		printf("Memory failed to allocate\n");
//		exit(1);
//	}
//	for (size_t i=0; i<rows; i++)
//	{
//		board[i] = (tile_t*)calloc(columns, sizeof(tile_t));
//		if (board[i]==NULL)
//		{
//			printf("Memory failed to allocate\n");
//			exit(0);
//		}
//	}
//	player playerList[2];
//
//	player *player1 = malloc(sizeof(player));
//	init_player(player1);
//	player1->playerID = 1;
//	strcpy(player1->name, "Domi");
//
//	player *player2 = malloc(sizeof(player));
//	init_player(player2);
//	player2->playerID = 2;
//	strcpy(player2->name, "AmOur");
//
//	playerList[0] = *player1;
//	playerList[1] = *player2;
//	read_from_file(pathname, board);
//	populate_playerList(playerList, board, rows, columns, 2);
//	//print_board(board, rows, columns);
////	print_player(&playerList[0]);
////	print_player(&playerList[1]);
////	print_player(player1);
////	print_player(player2);
//	//	board[0][0].fishNum = 0;
//	deallocate_mem(board, columns);
//	free(player1);
//	free(player2);
//	printf("\n");
//}
#endif /* player_h */
