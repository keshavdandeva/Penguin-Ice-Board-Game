//
//  file_management.h
//  Penguins

/* Header where all of the functions regarding file I/O are described and implemented */


#ifndef file_management_h
#define file_management_h
#include "player.h"
#include "penguin.h"
#include <stdio.h>
#include <string.h>
#include "tiles.h"

int first_line_offset(char *pathname)
/* The function returns the number of characters on the first line of a file at a given pathname. Useful to find the offset for fseek. */
{
	FILE *fp;
	char ch = '\0';
	int offset = 0;
	fp = fopen(pathname, "r");
	while (ch!='\n')
	{
		if(ch == EOF) break;
		ch = fgetc(fp);
		offset++;
	}
	fclose(fp);
	return offset;
}

void find_size(int *m, int *n, char *pathname)
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

// Function used to deallocate the tile memory
void deallocate_mem(tile_t** arr, int n){
	for (size_t i = 0; i < n; i++)
		free(arr[i]);
	free(arr);
}

void read_from_file(char *pathname, tile_t **board)
{
	FILE *fp;
	fp = fopen(pathname, "r");
	char ch;
	// figuring out the size size of the board. First line of the file.
	int rows, columns;
	find_size(&rows, &columns, pathname);
	/* at this point we know the size of the board */
	fseek(fp, first_line_offset(pathname), SEEK_SET);
	char buff[100];
	//fgets(buff, 100, (FILE*)fp);

	for(int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			fscanf(fp, "%d", buff);

				board[i][j].fishNum = buff[0]/10;
				board[i][j].playerID = buff[0]%10;
				board[i][j].active = 0;
			if (board[i][j].playerID != 0) board[i][j].active = 1;
			
		}
		ch = fgetc(fp);
	}
	fclose(fp);
}
void print_board(tile_t **board, int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		for(int j = 0; j < n; j++)
		{
			printf("%d%d ", board[i][j].fishNum, board[i][j].playerID);
		}
		printf("\n");
	}
}
int save_to_file(tile_t **board, char *outputfile) //saves data to file
{
	int m,  n;
	find_size(&m, &n, outputfile);
	FILE *pointer_to_file; //Setting pointer to file
	pointer_to_file = fopen(outputfile, "w"); //Open file for writing this time

	//find_dimensions_from_board(board, &m, &n);
	
	
	fprintf(pointer_to_file ,"%d %d\n", m, n); //Saving m and n
	
	for(int i=0; i < m; i++) //Printing array
	{
		for(int j=0; j < n; j++)
		{
			fprintf(pointer_to_file, "%d%d ", board[i][j].fishNum, board[i][j].playerID);
		}
		fprintf(pointer_to_file, "\n");
	}
	return 0;
}
void test(tile_t **board, char *pathname)
/* this function is used for testing purposes */
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
	read_from_file(pathname, board);
	print_board(board, rows, columns);
//	board[0][0].fishNum = 0;
	printf("\n");
	print_board(board, rows, columns);
	save_to_file(board, pathname);
	deallocate_mem(board, columns);
//	board[0][0]->fishNum = 3;
//	printf("%d", board[0][0]->fishNum);
}



#endif /* file_management_h */
