#pragma once
#include "file_management.h"
#include "board.h"

int is_board_correct(int m, int n, int board[m][n][4]);
int penguins_left(int m, int n, int board[m][n][4], int penguins, int player_number);
int tiles_with_one_fish(int m, int n, int board[m][n][4], int total_penguins_to_be_placed, int mode);
void print_boardvPawel(int m, int n, int board[m][n][4]);
void place_penguin_on_tile(int automatic_m, int automatic_n, int m, int n, int board[m][n][4], int *pointer_to_board, int player_number, int mode);
int placing_interactive(int number_of_players, int penguins, int m, int n, int board[m][n][4], char outputfile[100]);
int placing_automatic(int penguins, char outputfile[100], char inputfile[100]);
int fill_tiles_empty_array(int m, int n, int board[m][n][4], int spaces_available, int *pointer_to_tiles_empty);
void assign_points(int m, int n, int spaces_available, int board[m][n][4], int tiles_empty[spaces_available][3], int *pointer_to_best_tile);
int read_from_file_to_board(int *pointer_to_board, int m, int n, char inputfile[100], int *pointer_to_number_of_players, char *pointer_to_IDs, int *pointer_to_IDnumeric, int *pointer_to_pointsperteam);
