#pragma once

int read_dimensions(int *pointer_to_m, int *pointer_to_n, char inputfile[100]);
int save_to_file(int m, int n, int board[m][n][4], char outputfile[100]);
int read_from_file(int *pointer_to_board, int m, int n, char inputfile[100]);
