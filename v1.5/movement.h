#ifndef movement_h
#define movement_h

#include <time.h>
#include <stdlib.h>
#include "player.h"
#include "file_management.h"
#include "tiles.h"
#include "penguin.h"
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
int returnDirection(char *pathname, tile_t **board, int *move, penguin *penguin);
int isValidMove(char *pathname, int *move, tile_t **board, player *player, penguin *penguin);
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
		if (move[0] > 0 && move[0] < m && isValidMove(pathname, move, board, player, &player->penguinList[i])) // checks whether its on the border and checks whether there is an available tile
		{
			return 1;
		}
		// tile below

		move[0] = player->penguinList[i].position[0]-1;
		move[1] = player->penguinList[i].position[1];
		if (move[0] > 0 && move[0] < m && isValidMove(pathname, move, board, player, &player->penguinList[i]))
		{
			return 1;
		}

		// tile to the left
			move[0] = player->penguinList[i].position[0];
			move[1] = player->penguinList[i].position[1]-1;
		if (move[1] > 0 && move[1] < n && isValidMove(pathname, move, board, player, &player->penguinList[i]))
		{
			return 1;
		}

		// tile to the right
		move[0] = player->penguinList[i].position[0];
		move[1] = player->penguinList[i].position[1]+1;
		if (move[1] > 0 && move[1] < n && isValidMove(pathname, move, board, player, &player->penguinList[i]))
		{
			return 1;
		}

	}
	return 0;
}


int movesLeftPenguin(tile_t **board, penguin_t *penguin, player_t *player, char *pathname)
{
	int m = 0, n = 0;
	find_size(&m, &n, pathname);
	int move[2];
	// tile above
	move[0] = penguin->position[0]+1;
	move[1] = penguin->position[1];
	if (move[0] >= 0 && move[0] < m && isValidMove(pathname, move, board, player, penguin)) // checks whether its on the border and checks whether there is an available tile
	{
		return 1;
	}
	// tile below
	
	move[0] = penguin->position[0]-1;
	move[1] = penguin->position[1];
	if (move[0] >= 0 && move[0] < m && isValidMove(pathname, move, board, player, penguin))
	{
		return 1;
	}
	
	// tile to the left
	move[0] = penguin->position[0];
	move[1] = penguin->position[1]-1;
	if (move[1] >= 0 && move[1] < n && isValidMove(pathname, move, board, player, penguin))
	{
		return 1;
	}
	
	// tile to the right
	move[0] = penguin->position[0];
	move[1] = penguin->position[1]+1;
	if (move[1] >= 0 && move[1] < n && isValidMove(pathname, move, board, player, penguin))
	{
		return 1;
	}
	
	return 0;
}

int movesLeftv2(tile_t **board, penguin_t *penguin, player_t *player, char *pathname)
{
	int m = 0, n = 0;
	find_size(&m, &n, pathname);
	if (penguin->position[0] > 0 && penguin->position[1] > 0 && penguin->position[0] < m && penguin->position[1] < n)
	{
		if(penguin->position[0])
		{
			
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
int returnDirection(char *pathname, tile_t **board, int *move, penguin *penguin)
{
/*
 Returns a value corresponding to the direction the given penguin is moving
 returns 1 if moving up
		 2 if moving down
 		 3 if moving left
 		 4 is moving right
 */

	int m = 0, n = 0;
	find_size(&m, &n, pathname);
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

int isValidMove(char *pathname, int *move, tile_t **board, player *player, penguin *penguin)
// determines whether the given move is valid for a given player
{
	int m = move[0], n = move[1];
	if ((board[m][n].active == 1) && (board[m][n].playerID == 0)) // check whether the tile is active
	{
		// check whether there are inactive tiles on the way
		// check whether there are penguins on the way
		int direction = returnDirection(pathname, board, move, penguin);
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
			return 1;
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
			return 1;
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
			return 1;
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
			return 1;
		}
	}
	return 0;
}
/*
int automatic(char inputfile[50])
{

    FILE *fp;
	fp = fopen(inputfile, "r");

	int rows, columns;
	find_size(&rows, &columns, inputfile);

    char ch;
    int charcount=0;
    while ((ch = getc(fp))!= 'P'||ch!=EOF)
    {
        printf("%c", ch);
        charcount++;
    }
    printf("\n%d\n",charcount);


    //reads data from board
    //sets current coordinates of the placed penguins (in the penguin structure)

    //chooses penguin to move (whichever can move atm)
    //calculates what move should it make (might count the sum of points in the current row and column up to the fi)

    //makes the move
    //makeMove(move, board, )

    //writes to the output file
}
*/
void makeMove(int move[], tile_t **board, player *player, penguin *penguin) // Applies the move
{
	int m = move[0], n = move[1];
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
/*ADDED
int m,n;
find_size(&m, &n, pathname);
print_board(board, m, n);
*/
			int move1[2] = {0, 0};
			int choiceOfPenguin;
			// Print the coordinates of every penguin available to the player <------ IMPLEMENT
/*
print_board(board, m, n); //ADDED
printf("the coordinates of the &d penguin: \n",playerList[playerIndex]); //ADDED
*/
				printf("%d, %d\n", playerList[playerIndex].penguinList[0].position[0], playerList[playerIndex].penguinList[0].position[1]);
				printf("Enter coordinates of a penguin to move:\n");
				scanf("%d", &choiceOfPenguin);
				printf("Enter your move (m, n):\n");
			fflush(stdin);
				scanf("%d %d", &move1[0], &move1[1]); // keyboard input of coordinates
			if (isValidMove(pathname, move1, board, &playerList[playerIndex], &playerList[playerIndex].penguinList[choiceOfPenguin]) == 1)
					// if the entered move is valid, applies it
				{
					makeMove(move1, board, &playerList[playerIndex], &playerList[playerIndex].penguinList[choiceOfPenguin]);
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



void rand_move_based_direction(int *move, int direction, tile_t **board, player_t *player, char *inputfile)
{
	time_t t;
	srand((unsigned) time(&t));
	
	int m = 0, n = 0;
	int old_n = 0, old_m = 0;
	int randPengNum = 0;
	while ((old_n == n) && (old_m == m))
	{
		randPengNum = rand() % num_of_penguins(7, board, inputfile);
		old_m = player->penguinList[randPengNum].position[0];
		old_n = player->penguinList[randPengNum].position[1];
	}

	if ((direction == 1) || (direction == 2)) // moving up or down
	{
		n = old_n;
		m = rand() % (old_m+1);
	}
	else if ((direction == 3) || (direction == 4)) // moving left or right
	{
		n = rand() % (old_n+1);
		m = old_m;
	}
	move[0] = m;
	move[1] = n;
}
void automatic_movement(tile_t **board, char *inputfile, char *outputfile)
{
	time_t t;
	srand((unsigned) time(&t));
	int rows = 0, columns = 0;
	find_size(&rows, &columns, inputfile);
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
	int numOfPlayers = num_of_players(inputfile);
	player_t *playerList = malloc(sizeof(player_t)*numOfPlayers);
	for (int i = 0; i < numOfPlayers; i++)
	{
		// playerList[i] = malloc(sizeof(player_t));
		playerList[i].numberOfPenguins = num_of_penguins(7, board, inputfile);
		playerList[i].penguinList = malloc(sizeof(penguin_t)*num_of_penguins(7, board, inputfile));
		if (playerList[i].penguinList == NULL)
		{
			printf("Memory failed to allocate");
			exit(1);
		}
	}
	read_from_file_automatic(inputfile, board, playerList);
	int ourPlayerIndex;
	for (int i = 0; i < numOfPlayers; i++)
	{
		make_penguins(&playerList[i], board, rows, columns);
		if (playerList[i].playerID == 7) ourPlayerIndex = i;
	}
	int randPengNum = rand() % num_of_penguins(7, board, inputfile);
	while (!movesLeftPenguin(board, &playerList[ourPlayerIndex].penguinList[randPengNum], &playerList[ourPlayerIndex], inputfile))
	{
		randPengNum = rand() % num_of_penguins(7, board, inputfile);
	}
	int randDirection = (rand() % 4) + 1;
	int randMove[2];
	rand_move_based_direction(randMove, randDirection, board, &playerList[ourPlayerIndex], inputfile);
	while(!isValidMove(inputfile, randMove, board, &playerList[ourPlayerIndex], &playerList[ourPlayerIndex].penguinList[randPengNum]))
	{
		randDirection = (rand() % 4) + 1;
		rand_move_based_direction(randMove, randDirection, board, &playerList[ourPlayerIndex], inputfile);
	}
	makeMove(randMove, board, &playerList[ourPlayerIndex], &playerList[ourPlayerIndex].penguinList[randPengNum]);
	save_to_file_automatic(board, playerList, inputfile, outputfile);
	deallocate_mem(board, columns);
	exit(1);
}

void test(char *inputfile, tile_t **board)
{
	
	int columns = 0, rows = 0;
	find_size(&rows, &columns, inputfile);
	/*								MEM ALLOCATION								 */
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
	player_t *player = malloc(sizeof(player));
	player->playerID = 7;
	player->numberOfPenguins = num_of_penguins(7, board, inputfile);
	player->penguinList = malloc(sizeof(penguin_t)*num_of_penguins(7, board, inputfile));
	if (player->penguinList == NULL)
	{
		printf("Memory failed to allocate");
		exit(1);
	}
	read_from_file(inputfile, board, player);
	make_penguins(player, board, rows, columns);
//	// read the player, implement
//	int randDirection = (rand() % 4) + 1;
//	int randMove[2];
//	int randPengNum = rand() % num_of_penguins(7, board, inputfile);
//	rand_move_based_direction(randMove, randDirection, board, player, inputfile);
//	while(!isValidMove(inputfile, randMove, board, player, &player->penguinList[randPengNum]))
//	{
//		rand_move_based_direction(randMove, randDirection, board, player, inputfile);
//	}
//	printf("Penguin at (%d, %d) wants to move to (%d, %d)\n", player->penguinList[randPengNum].position[0], player->penguinList[randPengNum].position[1], randMove[0], randMove[1]);
//	makeMove(randMove, board, player, &player->penguinList[randPengNum]);
//	deallocate_mem(board, columns);
//	free(player->penguinList);
//	free(player);
	int move[2] = {2, 1};
	int penguinIndex = 1;
	printf("Tile (%d, %d) is active = %d\n", move[0], move[1], board[move[0]][move[1]].active);
	if (movesLeftPenguin(board, &player->penguinList[penguinIndex], player, inputfile))
	{
		printf("(%d, %d) has %d fish on it\n", move[0], move[1], board[move[0]][move[1]].fishNum);
		printf("move (%d, %d) for penguin (%d, %d) = %d\n", move[0], move[1], player->penguinList[penguinIndex].position[0], player->penguinList[penguinIndex].position[1], isValidMove(inputfile, move, board, player, &player->penguinList[penguinIndex]));
	}
	else
	{
		printf("The penguin cannot move\n");
	}

}
#endif /* movement_h */
