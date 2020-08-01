#ifndef file_management_h
#define file_management_h
#include "player.h"
#include "penguin.h"
#include <stdio.h>
#include <string.h>
#include "tiles.h"
#include <time.h>
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
int num_of_players(char *pathname)
{
	int num = 0;
	FILE *fp;
	fp = fopen(pathname, "r");
	char ch;
	int m = 0, n = 0;
	find_size(&m, &n, pathname);
	int init_num_s = 0;
	while(init_num_s != m+1)
	{
		ch = fgetc(fp);
		if(ch =='\n') init_num_s++;
	}
	while (ch!=EOF)
	{
		ch = fgetc(fp);
		if (ch == '\n') num++;
	}
	return num;
}

int num_of_penguins(int playerID, tile_t **board, char *pathname)
{
	int rows = 0, cols = 0;
	find_size(&rows, &cols, pathname);
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
void read_from_file(char *pathname, tile_t **board, player_t *player)
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
			if (board[i][j].fishNum != 0) board[i][j].active = 1;

		}
		ch = fgetc(fp);
	}
	fclose(fp);
}

void player_info_offset_automatic(FILE *fp, int *space_plus_offset)
{
	char ch = fgetc(fp);
	int num_s = 0, num_c = 0;
	while (ch!=EOF)
	{
		ch = fgetc(fp);
		num_c++;
		if(ch == '\n') num_s++;
	}
	space_plus_offset[0] = num_s;
	space_plus_offset[1] = num_c;
}

void read_from_file_automatic(char *pathname, tile_t **board, player_t *playerList)
/* ITS ALIIIIIIIIVEEEEE */
{
	FILE *fp;
	fp = fopen(pathname, "r");
	char ch;
	// figuring out the size of the board. First line of the file.
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
			if (board[i][j].fishNum != 0) board[i][j].active = 1;

		}
		ch = fgetc(fp);
	}
	int space_plus_offset[2];

//	int num_s = 0, num_c = 0;
//	while (ch!=EOF)
//	{
//		ch = fgetc(fp);
//		num_c++;
//		if(ch == '\n') num_s++;
//	}
	player_info_offset_automatic(fp, &space_plus_offset);
	int size = space_plus_offset[0];
	fseek(fp, -space_plus_offset[1], SEEK_CUR);
	for(int i = 0; i < size; i++)
	{
		fscanf(fp, "%s %d %d\n", playerList[i].name, &playerList[i].playerID, &playerList[i].score);
	}
	fclose(fp);
}
void make_penguins(player_t *player, tile_t **board, int m, int n)
{
	int penguinCounter = 0;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (board[i][j].playerID == player->playerID)
			{
				penguin_t *penguin = malloc(sizeof(penguin_t));
				if (penguin == NULL)
				{
					printf("Memory failed to allocate \n");
					exit(1);
				}
				penguin->position[0] = i;
				penguin->position[1] = j;
				player->penguinList[penguinCounter] = *penguin;
				penguinCounter++;
			}

		}
	}
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
int save_to_file(tile_t **board, char *inputfile, char *outputfile) //saves data to file
{
	int m,  n;
	find_size(&m, &n, inputfile);
	FILE *pointer_to_file; //Setting pointer to file
	pointer_to_file = fopen(outputfile, "w+"); //Open file for writing this time
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
	fclose(pointer_to_file);
	return 0;
}

void save_to_file_automatic(tile_t **board, player_t *playerList, char *inputfile, char *outputfile)
{
	int m,  n;
	find_size(&m, &n, inputfile);
	FILE *pointer_to_file; //Setting pointer to file
	pointer_to_file = fopen(outputfile, "w+"); //Open file for writing this time
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
	FILE *ip;
	ip = fopen(inputfile, "r");
	char ch;
	// figuring out the size of the board. First line of the file.
	int rows, columns;
	find_size(&rows, &columns, inputfile);
	/* at this point we know the size of the board */
	fseek(ip, first_line_offset(inputfile), SEEK_SET);
	char buff[100];
	//fgets(buff, 100, (FILE*)fp);
	for(int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			fscanf(ip, "%d", buff);
		}
		ch = fgetc(ip);
	}
	int space_plus_offset[2];
	player_info_offset_automatic(ip, &space_plus_offset);
	fclose(ip);
	int size = space_plus_offset[0];
	for(int i = 0; i < size; i++)
	{
		fprintf(pointer_to_file, "%s %d %d\n", playerList[i].name, playerList[i].playerID, playerList[i].score);
	}
	fclose(pointer_to_file);
}
void test_read_automatic(char *pathname, tile_t **board)
{
	int columns = 0, rows = 0;
	find_size(&rows, &columns, pathname);
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
	player_t *player1 = malloc(sizeof(player));
	player_t *player2 = malloc(sizeof(player));
	player_t *playerList = malloc(sizeof(player_t)*2);
	playerList[0] = *player1;
	playerList[1] = *player2;
	player1->playerID = 7;
	read_from_file_automatic(pathname, board, playerList);
	int i = 0;
	printf("Player with name %s ID %d has %d fish\n", playerList[i].name, playerList[i].playerID, playerList[i].score);
	i = 1;
	printf("Player with name %s ID %d has %d fish\n", playerList[i].name, playerList[i].playerID, playerList[i].score);


}

int save_board_to_file(int m, int n, int penguins, int number_of_players, int board[m][n][4], char outputfile[100], int mode, char *pointer_to_IDs[9], int *pointer_to_IDnumeric, int *pointer_to_pointsperteam) //saves data to file
{
    //mode: 1-interactive, 2-automatic
    if (mode>2 || mode<1)
    {
        return 2;
    }

    int i, j;
    FILE *pointer_to_file; //Setting pointer to file
    pointer_to_file = fopen(outputfile, "w"); //Open file for writing this time

    fprintf(pointer_to_file ,"%d %d\n", m, n); //Saving m and n

    for(i=0; i<m; i++) //Printing array
    {
        for(j=0; j<n; j++)
        {
            int display_value = 10 * board[i][j][0] + board[i][j][3];
            if(display_value < 10 && display_value >= 0)
            {
                fprintf(pointer_to_file ,"0%d ", display_value); //Saving the board
            }
            else if(display_value >= 10 && display_value < 40)
            {
                fprintf(pointer_to_file ,"%d ", display_value); //Saving the board
            }
            else
            {
                printf("Skipper: Kowalski, analysis.\n");
                printf("Kowalski: We have just tried to save negative int or int above 39 into text file!\n");
                return 2;
            }
        }
        fprintf(pointer_to_file, "\n");
    }

    //mode: 1-interactive, 2-automatic
    if(mode == 1)
    {
        for (i=0; i<number_of_players; i++)
        {
            fprintf(pointer_to_file ,"Player%d %d %d", i+1, i+1, penguins);
            if(i!=number_of_players-1)
            {
                fprintf(pointer_to_file,"\n");
            }
        }
    }
    else //mode = 2
    {
        //printf("%d", number_of_players);
        int was_placed = 0; //Checks if our penguin was already placed
        for(i=0; i<number_of_players+1; i++)
        {
            if(*(pointer_to_IDnumeric+i) == 7)
            {
                was_placed = 1;
            }

            if(number_of_players!=i)
            {
                fprintf(pointer_to_file,  "%s %d %d\n", (pointer_to_IDs[i]), *(pointer_to_IDnumeric+i), *(pointer_to_pointsperteam+i));
            }
            else if(was_placed == 1)
            {
                fprintf(pointer_to_file,  "%s %d %d", (pointer_to_IDs[i]), *(pointer_to_IDnumeric+i), *(pointer_to_pointsperteam+i));
            }
            else
            {
                fprintf(pointer_to_file,  "team07 7 1");
            }
        }
    }

    fclose(pointer_to_file); //Closing file

    return 0;
}

#endif /* file_management_h */
