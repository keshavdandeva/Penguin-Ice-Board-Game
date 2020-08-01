#include <stdio.h>
#include <string.h>
#include "board.h"
#include "player.h"
#include "placing_penguins.h"
#include "file_management.h"
//#include "movement.h" - It does not compile yet.
#include "penguin.h"

int main()
{
	int m = 3, n = 4; //Should be restricted to interactive mode only
	int board[m][n][4]; //Should be restricted to interactive mode only
	int numberOfPlayers = 2; //Maybe should be a value that we can ask a user to input manually
	int playerList[numberOfPlayers][3];
	char phase[] = "placement"; //Should be read from command line

    createPlayers(numberOfPlayers, playerList, 3);
	makeBoard(m, n, board); //Should be restricted to interactive mode only + passing by value will not work

	///***Variables used to read from file/save to file and place penguins
    int penguins = 2; //Number of penguins should be read from command line
    int group_number_id = 7;
    int error = 3; //Return value of an error if something would fail

	char inputfile[100] = "Board.txt"; //Should be read from command line
    char outputfile[100] = "Board.txt";

    int *pointer_to_m = &m;
    int *pointer_to_n = &n;
    int *pointer_to_board = &board[0][0][0];
    ///***

    if(read_dimensions(pointer_to_m, pointer_to_n, inputfile) != 0) //Checking if dimensions m x n were read properly
    {
        return 2;
    }

	///*** Reading from file in automatic mode
    /*
    if(read_from_file(pointer_to_board, m, n, inputfile)!=0)
    {
        return 2; //Error message
    }
    */
	///***

	printBoard(m, n, board);

	///Actually I would avoid if statement in interactive mode, because we cannot access movement at a single run of the program.
	///Unless we want to run program twice or more times to play a single interactive game.

	if (strcmp(phase, "placement") == 0) // if gamephase == placing, do placing until it's over
	{
	    ///***This code refers only to interactive mode.
        /*
		error = placing(numberOfPlayers, penguins, m, n, board, outputfile);

		if(error != 0)
        {
            printf("Skipper: Kowalski, analysis.\n");
            printf("Kowalski: There was some error. Error number %d. \n", error);
            return error;
        }
        */
        ///***


        ///*** This code refers to automatic mode only.
        /*
        error = placing_automatic(penguins, m, n, board, outputfile);

        if(error != 0 && error != 1)
        {
            printf("Skipper: Kowalski, analysis.\n");
            printf("Kowalski: There was some error. Error number %d. \n", error);
            return error;
        }
        else if(error == 1) //When all penguins placed it will return 1
        {
            return 1;
        }
        */
        ///***

	}
	else if (strcmp(phase, "movement") == 0) // if gamephase == movement, do movement until it's over
	{
		// do movement

		/* while (phaseIsOver() != 1) {
            play();
		}*/
	}

	// print scores, determine winner
	return 0;
}

