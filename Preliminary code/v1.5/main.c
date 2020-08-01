#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "board.h"
#include "movement.h"
#include "file_management.h"
/*#include "player.h"
#include "movement.h"*/
//#define PATHNAME "/Users/d0mi/Downloads/board_team07.txt"
//#define PATHNAME "/Users/Pawe³/0 Pawe³ - pliki/Nauka/Programowanie/C/Penguins/Board.txt"
#include "placing_penguins.h"

int main(int argc, char *argv[])
{

tile_t **board = NULL;

    if(strcmp("phase=placement", argv[1])==0)
    {
        int peng = atoi(argv[2]+9);
        //loop that reads the number of penguins provided by the command line parameter
        for(int i = 1; isdigit(atoi (argv[2]+9+i)) != 0; i++)
        {
            peng = peng * 10;
            peng += atoi(argv[2]+9+i);
        }

         ///Board.txt, inputfile and outputfile macro has to be changed to command line parameter
        char inputfile[50], outputfile[50];
        strcpy(inputfile, argv[3]);
        strcpy(outputfile, argv[4]);

        first_line_offset(inputfile);
        //read_from_file(inputfile,board); //crashes here


        int error = placing_automatic(peng, outputfile, inputfile);

        return error;
        //Program will always end here, unless it will crash somewhere
    }

    else if(strcmp("phase=movement", argv[1])==0)
		// argv[1] - phase (movement in this case)
		// argv[2] - inputfile
		// argv[3] - outputfile
	{
		char *input = strdup(argv[2]);
		char *output = strdup(argv[3]);
		automatic_movement(board, input, output);

	}

    else if(strcmp("id", argv[1])==0)
    {
        printf("team07\n");
        return 0;
    }

    else
    {
        printf("error, wrong command line parameters\n");
        return 3;
    }


//	tile_t **board = NULL;
/*
	// Interactive placement code, tested by Laura (works)
    int m = 11, n = 13, players = 2, penguins = 2;
	int myboard[m][n][4];
	int *pointer_to_myboard = &myboard[0][0][0];
	makeBoardwithPointer(m, n, pointer_to_myboard);
	char outputfile[100] = "Board.txt";

	print_boardvPawel(m, n, myboard);

	int error = placing_interactive(players, penguins, m, n, myboard, outputfile);
	if(error == 0)
    {
        return 2; //Should return 1
    }
	else if(error!=1)
    {
        return error;
    }
*/
	//Phase is ended with saving board to output file, we can go to movement phase


//test(board, PATHNAME);
//	read_from_file(PATHNAME, board, playerList, 2);
	//test_player(PATHNAME, board);
//	play(2, board, playerList);
//	save_to_file(board, PATHNAME);
//	test_movement(board, "Board.txt");
	printf(" \n");
	return 0;
}
