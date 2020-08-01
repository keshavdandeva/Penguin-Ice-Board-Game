#ifndef movement_h
#define movement_h

#include <stdlib.h>
#include "player.h"
/*TODO:
 1. Implement all() - ez
 2. Implement annulate(); DONE
 3. Implement turnsLeft();
 4. Implement phaseIsOver(); DONE
 5. Implement isValidMove();
 6. Implement makeMove();
 7. Implement moveOver();
 8. Implement play(); - Almost done
 */
void annulate(int array) // set every element of array to 0;
{
	for (int element = 0; element < sizeof(array)/sizeof(array[0]), element++)
	{
		array[element] = 0;
	}
}

int all(int array)
{
	NULL;
}

int turnsLeft(int playerList, int board) //determines the number of turns left for a given player
{
    //returns 0 if the given player cannot make any more moves
}

int phaseIsOver(int movesLeft) // determines whether the movement phase is over
{
	if(sizeof(movesLeft) == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int isValidMove(int move, int board, Player player) // determines whether the given move is valid for a given player
{
	// check whether the tile is active
	// check whether there are inactive tiles on the way
	// check whether there are penguins on the way
}

void makeMove(int move, int board, struct Player player, struct Penguin penguin) // Applies the move if it is valid
{
	board[move[0]][move[1]][0] = 1; // signifies that the new tile now has a penguin on it
	increaseScore(player, board[move[0]][move[1]][0]); // increases the score of the player depending on the amount of the fish at the new tile
	board[move[0]][move[1]][0] = 0; // there are no more fish at the new tile
	board[move[0]][move[1]][3] = player.playerID; // changes the new tile's playerID to player.playerID
	board[penguin.position[0]][penguin[1]][1] = 0; // there is no more penguin standing on the old tile
	board[penguin.position[0]][penguin[1]][2] = 0; // the old tile is not active anymore
}

int moveOver(moveOverList) // checks whether all players have done their moves
{
    //returns 1 if moveOverList is all 1s
}

int play(int numberOfPlayers, int board, int playerList) // Main algorithm of movement phase
{
			int moveOverList[numberOfPlayers];
	while (phaseIsOver != 1) // checks if the movement phase is over, run moves until it is
	{
		while (moveOver(moveOverList) != 1) // works until move is over
		{
		for (int player = 0; player < numberOfPlayers; player++)
			{ 
			     //(we should also ask which penguin the player chooses to move)
			    //asks each player for a move if turnsLeft != 0 for the penguin of their choice
			    //if turnsLeft is 0 for player's every penguin, then their position in moveOverList turns 1 and we don't ask for a move
				int move[2];
				scanf("%d,%d", &move[0], &move[1]); // keyboard input of coordinates
				if (isValidMove(move) == 1) // if the entered move is valid, applies it
				{
					makeMove(move);
					moveOverList[player] = 1;
				}
				else
				{
					//implement;
				}
			} // at this point every player made a move
		
		} // at this point moveOverList contains only 1s
		annulate(moveOverList); //annulates moveOverList;
		// now moverOverList is all 0s
	}
	// The loop exits when there are no moves left for all players

}
#endif /* movement_h */
