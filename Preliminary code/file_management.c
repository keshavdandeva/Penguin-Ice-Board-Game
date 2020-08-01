#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "file_management.h"

    //board[row][col][0] - numFish (up to 3, number of fish on the tile)
    //board[row][col][1] - isPenguin (0 if there's no penguin on the tile 1 if there is)
    //board[row][col][2] - active (whether it's active or not, 1 is it is, 0 if not)
    //board[row][col][3] - playerID (id of the player on the tile, 0 if there's no one)

int read_dimensions(int *pointer_to_m, int *pointer_to_n, char inputfile[100])//reads value of m and n parameters
{
    FILE *pointer_to_file; //Setting pointer to file

    int m, n;

    if ((pointer_to_file = fopen(inputfile,"r")) == NULL) //Opening the file - read only
    {
        printf("Skipper: Kowalski, analysis.\n");
        printf("Kowalski: There is no file to open.");// Program exits if the file pointer returns NULL.
        return 2;
    }

    fscanf(pointer_to_file,"%d %d", &m, &n); //Reading dimensions m x n

    *pointer_to_m = m;
    *pointer_to_n = n;

    fclose(pointer_to_file); //Closing file

    return 0;
}

int save_to_file(int m, int n, int board[m][n][4], char outputfile[100]) //saves data to file
{
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

    ///Save 3 values - ID(string), player's number, points - those come from struct player

    fclose(pointer_to_file); //Closing file

    return 0;
}

int read_from_file(int *pointer_to_board, int m, int n, char inputfile[100])//Saves data from file into an array
{
    FILE *pointer_to_file; //Setting pointer to file
    int i, j, value = 0; //Value read from the file

    if ((pointer_to_file = fopen(inputfile,"r")) == NULL) //Opening the file - read only
    {
        printf("Skipper: Kowalski, analysis.\n");
        printf("Kowalski: There is no file to open.");// Program exits if the file pointer returns NULL.
        return 2;
    }

    int m_copy = m;
    int n_copy = n; //Used to check if data from command line parameter corresponds to first line of the file

    fscanf(pointer_to_file,"%d %d", &m, &n); //Reading dimensions m x n

    if(m!=m_copy || n!=n_copy)
    {
        printf("Skipper: Kowalski, analysis.\n");
        printf("Kowalski: There is a problem with reading dimensions of a board.");// Error with reading dimensions
        return 2;
    }

    for(i=0; i<m; i++) //Reading the values from text file (there is no checking if numbers are correct)
    {
        for(j=0; j<n; j++)
        {
            fscanf(pointer_to_file, "%d", &value);
            *(pointer_to_board + 4*n*i + 4*j) = (value - (value%10))/10;
            if(value%10 != 0) //Checks Id of penguin on tile
            {
                *(pointer_to_board + 4*n*i + 4*j +1) = 0; //Is penguin = 0
            }
            else
            {
                *(pointer_to_board + 4*n*i + 4*j + 1) = 1; //Is penguin = 1
            }
            if(value==0)
            {
                *(pointer_to_board + 4*n*i + 4*j + 2) = 0; //Is active = 0
            }
            else
            {
                *(pointer_to_board + 4*n*i + 4*j + 2) = 1; //Is active = 1
            }

            *(pointer_to_board + 4*n*i + 4*j + 3) = value%10;
        }
    }

    /// If mode is automatic
    /*
    char ID[100], ID_bufor[100]; ///Max size of ID is 100, but we are allowed to make IDs as long as we want, so many be a problem
    int player_number, points;

    while(1) //Reads until the same line is read twice, so last reading does not matter
    {
        if(strcmp(ID,ID_bufor) == 0)
        {
            break;
        }
        for(i=0; i<100; i++)
        {
            ID_bufor[i] = ID[i];
        }
        fscanf(pointer_to_file,"%s %d %d", &ID, &player_number, &points); //Reading dimensions m x n
    }
    */ ///Some form of return for those values has to be implemented


    fclose(pointer_to_file); //Closing file

    return 0;
}
