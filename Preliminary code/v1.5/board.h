//
//  board.h
//  Penguins
//  A header which contains implementation of all of the functions related to the change of state
//  of the board.
//
//  Created by Dominik Kurasbediani on 2018-10-23.
//  Copyright © 2018 Dominik Kurasbediani. All rights reserved.
//

#ifndef board_h
#define board_h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "player.h"


void makeBoard(int m, int n, int board[m][n][4])
{
	//board size MxN with 3 spots for numFish, isPenguin, active, playerID;

	srand(time(NULL)); // sets the starting value to keep on changing for generating random number

	// iterate through rows
	for(int row = 0; row < m; row++)
	{
		// iterate through each item in a row
		for(int col = 0; col < n; col++)
		{
			//write down each value
			//board[row][col][0] - numFish (1 to 3, number of fish on the tile)
			//board[row][col][1] - isPenguin (0 if there's no penguin on the tile 1 if there is)
			//board[row][col][2] - active (whether it's active or not, 1 is it is, 0 if not)
			//board[row][col][3] - playerID (id of the player on the tile, 0 if there's no one)

			board[row][col][0] = rand() % 3 + 1;
			board[row][col][1] = 0;
			board[row][col][2] = 1;
			board[row][col][3] = 0;

		}
	}
}

void makeBoardwithPointer(int m, int n, int *pointer_to_board)
{
	//board size MxN with 3 spots for numFish, isPenguin, active, playerID;
	srand(time(NULL)); // sets the starting value to keep on changing for generating random number
    int row, col;
	// iterate through rows
	for(row = 0; row < m; row++)
	{
		// iterate through each item in a row
		for(col = 0; col < n; col++)
		{
			//write down each value
			//board[row][col][0] - numFish (1 to 3, number of fish on the tile)
			//board[row][col][1] - isPenguin (0 if there's no penguin on the tile 1 if there is)
			//board[row][col][2] - active (whether it's active or not, 1 is it is, 0 if not)
			//board[row][col][3] - playerID (id of the player on the tile, 0 if there's no one)

			*(pointer_to_board + 4*n*row + 4*col) = rand() % 3 + 1;//Putting fish on a tile
			*(pointer_to_board + 4*n*row + 4*col + 1) = 0;//Not penguin on tile
			*(pointer_to_board + 4*n*row + 4*col + 2) = 1;//Active
            *(pointer_to_board + 4*n*row + 4*col + 3) = 0;//Putting no penguin on the board
		}
	}
}

void placePenguin(int m, int n, int board[][n][4], int playerID)
{
	// places the penguin in the board.
	// Check if it's an available tile:
	// go to the right tile, change its id to playerID:
	board[m][n][3] = playerID;
	// Subtract one from the available number of penguins of the player:
}

void printBoard(int row, int col, int board[][col][4])
{

	for(int rowCount = 0; rowCount < row; rowCount++)
	{
		printf("\n");
		for(int i = 0; i < col; i++)
		{
			printf("+--------+");
			printf("\t");
		}
		printf("\n");
		for(int colCount = 0; colCount < col; colCount++)
		{

			printf("| \t");


			/*printf("\t%d%d%d%d%d%d\t", rowCount, colCount, board[rowCount][colCount][0],
				   board[rowCount][colCount][1], board[rowCount][colCount][2],
				   board[rowCount][colCount][3]);*/

			if(board[rowCount][colCount][2] == 0)
			{
				printf("/");
			}
			else if(board[rowCount][colCount][3] != 0)
			{
				printf("%d", board[rowCount][colCount][3]);
			}
			else if(board[rowCount][colCount][0] == 3)
			{
				printf("***");
			}
			else if (board[rowCount][colCount][0] == 2)
			{
				printf("**");
			}
			else if (board[rowCount][colCount][0] == 1)
			{
				printf("*");
			}
			else if (board[rowCount][colCount][0] == 0)
			{
				printf("0");
			}
			else if (board[rowCount][colCount][1] == 1)
			{
				printf("P");
			}
			else
			{
				printf(" ");
			}
			printf("\t");
			printf(" |\t");
		}
		printf("\n");
		for(int i = 0; i < col; i++)
		{
			printf("+________+");
			printf("\t");
		}
		printf("\n");
		//printf("\t__ \t\n");
		//printf("\n");


	}
}

#endif /* board_h */
