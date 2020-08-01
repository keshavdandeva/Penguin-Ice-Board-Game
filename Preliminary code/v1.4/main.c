//
//  main.c
//  Penguins
//
//  Created by Dominik Kurasbediani on 2018-10-23.
//  Copyright © 2018 Dominik Kurasbediani. All rights reserved.
//
// Dec 12 2018 - 4 hours -> implementation of some of movement.h, player.h, penguin.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "board.h"
#include "movement.h"
#include "file_management.h"
/*#include "player.h"
#include "movement.h"*/
#define PATHNAME "/Users/d0mi/Downloads/board_team07.txt"

int main()
{
	
	tile_t **board = NULL;

//test(board, PATHNAME);
//	read_from_file(PATHNAME, board, playerList, 2);
	//test_player(PATHNAME, board);
//	play(2, board, playerList);
//	save_to_file(board, PATHNAME);
	test_movement(board, PATHNAME);
	printf(" \n");
	return 0;
}
