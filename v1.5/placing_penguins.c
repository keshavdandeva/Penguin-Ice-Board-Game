#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

    //mode: 1 - interactive, 2 - automatic

    //board[row][col][0] - numFish (up to 3, number of fish on the tile)
    //board[row][col][1] - isPenguin (0 if there's no penguin on the tile 1 if there is)
    //board[row][col][2] - active (whether it's active or not, 1 is it is, 0 if not)
    //board[row][col][3] - playerID (id of the player on the tile, 0 if there's no one)

    //tiles_empty[][0] - m coordinate
    //tiles_empty[][1] - n coordinate
    //tiles_empty[][2] - value in points of a tile that will be assigned later

int is_board_correct(int m, int n, int board[m][n][4])
{
    int i, j;
    for(i=0; i<m; i++) //Checking if the is no more than 3 fish on one tile
    {
        for(j=0; j<n; j++)
        {
            int display_value = 10 * board[i][j][0] + board[i][j][3]; //Display value is a value displayed and saved in file
            if(display_value >= 40 || display_value < 0) //Improper number of fish
            {
                int wrong_fish = (display_value - display_value%10)/10;
                printf("Skipper: Kowalski, analysis.\n");
                printf("Kowalski: There is too much or too few fish on tile [%d,%d]. Exactly: %d\n", i, j, wrong_fish);
                return 3;
            }
            else if(display_value>19 && display_value!=20 && display_value!=30) //Penguin on improper place
            {
                int team_mistake = board[i][j][3];
                int wrong_fish = (display_value - team_mistake)/10;
                printf("Skipper: Kowalski, analysis.\n");
                printf("Kowalski: There is a penguin on a tile [%d,%d] where there are %d fish. Its group number is %d. \n", i, j, wrong_fish, team_mistake);
                return 3;
            }
        }
    }
    return 0;
}

int penguins_left(int m, int n, int board[m][n][4], int penguins, int player_number)
{
    int i, j;

    for(i=0; i<m; i++) //Checking number of penguins placed already
    {
        for(j=0; j<n; j++)
        {
            if(board[i][j][3] == player_number)
            penguins -= 1;
        }
    }
    return penguins;
}

int tiles_with_one_fish(int m, int n, int board[m][n][4], int total_penguins_to_be_placed, int mode)
{
    int spaces_available = 0;
    int i, j;

    for(i=0; i<m; i++) //Checking if there is sufficient number of tiles for penguins
    {
        for(j=0; j<n; j++)
        {
            if(board[i][j][0] == 1 && board[i][j][3] == 0)
            spaces_available += 1;
        }
    }

    if(mode == 1 && total_penguins_to_be_placed > spaces_available) //Mode 1 is interactive
    {
        printf("Skipper: Kowalski, analysis.\n");
        printf("Kowalski: There are %d tiles with one fish and %d penguins to be placed. Board was generated incorrectly. \n", spaces_available, total_penguins_to_be_placed);
        return 2;
    }
    else if(mode == 2 && spaces_available < 1)//Mode 2 is automatic
    {
        printf("Skipper: Kowalski, analysis.\n");
        printf("Kowalski: There is no tile left to place a penguin. Board was generated incorrectly. \n");
        return -1;
    }

    if(mode == 1)
    {
       return 0;
    }
    else if(mode == 2)
    {
        return spaces_available;
    }
    else //Prints error
    {
        printf("Skipper: Kowalski, analysis.\n");
        printf("Kowalski: There is incorrect mode set in tiles_with_one_fish function. \n");
        exit(2);
    }

}

void print_boardvPawel(int m, int n, int board[m][n][4])
{
    int i, j;
    printf("\n\t\t");

    for(j=0; j<n; j++)
    {
        printf("n=%d \t", j);
    }

    printf("\n\n\t");

    for(i=0; i<m; i++) //Printing numbers from array to be displayed
    {
        printf("m=%d\t", i);
        for(j=0; j<n; j++)
        {
            int display_value = 10 * board[i][j][0] + board[i][j][3]; //10* number of fishes + player number id
            if (display_value < 10)
            {
                printf("0%d \t", display_value);
            }
            else
            {
                printf("%d \t", display_value);
            }
        }
        printf("\n\n\t");
    }
    printf("\n");
}

void place_penguin_on_tile(int automatic_m, int automatic_n, int m, int n, int board[m][n][4], int *pointer_to_board, int player_number, int mode)
{
    if(mode!=1 && mode!=2)
    {
        printf("Skipper: Kowalski, analysis.\n");
        printf("Kowalski: There is incorrect mode set in place_penguin_on_tile. \n");
        exit(2);
    }

    int m_coordinate = -1, n_coordinate = -1, imputs = 0; //Coordinates of a penguin to be placed

    if(mode == 1)
    {
        while(1)//Breaks when penguins are placed correctly
        {
            if(imputs == 0)
            {
                printf("Turn of player %d!\n\nPlease enter coordinates (m,n), where (0,0) is top left tile, separated by space, of place where you want a penguin to be placed. \n", player_number);
                printf("First digit of tile is number of fish(0-3), second digit is number/ID of player that has penguin on it(0 means unoccupied tile).\n");
                print_boardvPawel(m, n, board);//Prints board
            }
            else
            {
                printf("Turn of player %d!\n\nIncorrect input! Please enter coordinates (m,n), where (0,0) is top left tile, separated by space, of place where you want a penguin to be placed. \n", player_number);
                printf("First digit of tile is number of fish(0-3), second digit is number/ID of player that has penguin on it(0 means unoccupied tile).\n");
                print_boardvPawel(m, n, board);
            }

            scanf("%d %d", &m_coordinate, &n_coordinate);
            imputs++; //Variable used only to change message in the loop

            if(m_coordinate < 0 || n_coordinate < 0 || m_coordinate >= m || n_coordinate >= n)
            {
                system("cls");
                printf("Tile (%d,%d) is incorrect!\n", m_coordinate, n_coordinate);
                continue; //when values are incorrect they need to be entered again
            }

            int player_on_tile = board[m_coordinate][n_coordinate][3]; //Id of player standing on tile (m,n)
            int fish_on_file = board[m_coordinate][n_coordinate][0]; //Number of fish on tile (m,n)

            if(player_on_tile != 0) //Checking if there is no penguin on the tile and if there is one fish
            {
                system("cls");
                printf("Tile (%d,%d) is incorrect!\n", m_coordinate, n_coordinate);
                printf("Skipper: Kowalski, analysis.\n");
                printf("Kowalski: There is already a penguin on this tile! \n");
            }
            else if(fish_on_file != 1)
            {
                system("cls");
                printf("Tile (%d,%d) is incorrect!\n", m_coordinate, n_coordinate);
                printf("Skipper: Kowalski, analysis.\n");
                printf("Kowalski: There must be one fish on the tile! \n");
            }
            else
            {
                break; //When there are no errors we can break
            }
        }

        system("cls");
        printf("Penguin successfully placed! File saved! \n");

    }
    else if(mode == 2)
    {
        m_coordinate = automatic_m;
        n_coordinate = automatic_n;
    }

    *(pointer_to_board + 4*n*m_coordinate + 4*n_coordinate + 3) = player_number;//Putting penguin on the board
    *(pointer_to_board + 4*n*m_coordinate + 4*n_coordinate) = 0;//Removing fish from a tile

}

int fill_tiles_empty_array(int m, int n, int board[m][n][4], int spaces_available, int *pointer_to_tiles_empty)
{
    int i, j;
    int number_of_tiles = 0;//Number of tiles currently detected as good for placing

    for(i=0; i<m; i++)
    {
        for(j=0; j<n; j++)
        {
            if(board[i][j][0] == 1 && board[i][j][3] == 0)
            {
                *(pointer_to_tiles_empty + 3*number_of_tiles) = i; //Assign m coordinate
                *(pointer_to_tiles_empty + 3*number_of_tiles + 1) = j; //Assign n coordinate
                *(pointer_to_tiles_empty + 3*number_of_tiles + 2) = 0; //Set points to 0
                number_of_tiles++;
            }
        }
    }
    if(number_of_tiles != spaces_available)
    {
        printf("Skipper: Kowalski, analysis.\n");
        printf("Kowalski: Not all or too many tiles were taken into consideration while filling scorearray for automatic placing. \n");
        return 2;
    }
    return 0;
}

void assign_points(int m, int n, int spaces_available, int board[m][n][4], int tiles_empty[spaces_available][3], int *pointer_to_best_tile)
{
    int i, j, high_score; //high_score is the best score that was assigned to the tile - penguin will placed on the tile with the highest score

    ///Here algorithm will assign points for each position
    //tiles_empty[i][] - consecutive number of empty tile
    //tiles_empty[][0] - m coordinate
    //tiles_empty[][1] - n coordinate
    //tiles_empty[][2] - value in points of a tile that will be assigned later
    int sum_fish_in_row[m];//Total number of fish in each row
    int sum_fish_in_column[n];//Total number of fish in each column
    int places_occupied_in_row[m];
    int places_occupied_in_column[n];
    int half_spaces_available = spaces_available/2;

    for(i=0; i<m; i++)//Setting initial value to 0
    {
        sum_fish_in_row[i] = 0;
        places_occupied_in_row[m] = 0;
    }
    for(i=0; i<n; i++)//Setting initial value to 0
    {
        sum_fish_in_column[i] = 0;
        places_occupied_in_column[n] = 0;
    }

    for(i=0; i<m; i++)
    {
        for(j=0; j<n; j++)
        {
            if(board[i][j][1])
            {
                places_occupied_in_row[i]+=1;
                places_occupied_in_column[j]+=1;
            }
            sum_fish_in_row[i] += board[i][j][0];
            sum_fish_in_column[j] += board[i][j][0];
        }
    }

    for(i=0; i<spaces_available; i++)
    {
        tiles_empty[i][2] -= abs(i-half_spaces_available); //Setting penguins as much int the center as possible
        int m_pos = tiles_empty[i][0];
        int n_pos = tiles_empty[i][1];
        tiles_empty[i][2] += 10*(sum_fish_in_row[m_pos]+sum_fish_in_column[n_pos]);
        tiles_empty[i][2] -= 100*(places_occupied_in_row[m_pos]+places_occupied_in_column[n_pos]);
        if(tiles_empty[i][0] == 0 || tiles_empty[i][0] == m-1)
        {
            tiles_empty[i][2] -= 250;
        }
        if(tiles_empty[i][1] == 0 || tiles_empty[i][1] == n-1)
        {
            tiles_empty[i][2] -= 250;
        }
    }

    high_score = tiles_empty[0][2]; //Setting first element of an array as a temporary best
    *(pointer_to_best_tile) = tiles_empty[0][0];
    *(pointer_to_best_tile + 1) = tiles_empty[0][1];

    for(i=1; i<spaces_available; i++)
    {
        if(tiles_empty[i][2]> high_score)//Set new best tile and save its position
        {
            *(pointer_to_best_tile) = tiles_empty[i][0];
            *(pointer_to_best_tile + 1) = tiles_empty[i][1];
            high_score = tiles_empty[i][2];
        }
    }
}

int read_from_file_to_board(int *pointer_to_board, int m, int n, char inputfile[100], int *pointer_to_number_of_players, char *pointer_to_IDs[9], int *pointer_to_IDnumeric, int *pointer_to_pointsperteam)//Saves data from file into an array
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

    char buffID[9][20]; //Set of bufors
    int buffIDnumber, buffpoints;
    i=0;

    int was_placed = 0; //Did our team place at least one penguin?

    while(fgetc(pointer_to_file)!=EOF)
    {
        fscanf(pointer_to_file, "%s %d %d", &buffID[i], &buffIDnumber, &buffpoints);

        if(buffIDnumber!=7)//Our ID
        {
            was_placed = 1;
            *(pointer_to_number_of_players) += 1;
        }
        else
        {
            buffpoints += 1; //I add a point for placing phase to out team
        }

        *(pointer_to_IDnumeric + i) = buffIDnumber;
        *(pointer_to_pointsperteam + i) = buffpoints;
        i++;
    }

    if(was_placed == 1)
    {
        for(i=0; i<(*pointer_to_number_of_players+1); i++) //Copying IDs to the appropriate board
        {
            strcpy(pointer_to_IDs[i], buffID[i]);
        }
    }
    else
    {
        for(i=0; i<(*pointer_to_number_of_players); i++) //Copying IDs to the appropriate board
        {
            strcpy(pointer_to_IDs[i], buffID[i]);
        }
    }

    fclose(pointer_to_file);
}

int placing_interactive(int number_of_players, int penguins, int m, int n, int board[m][n][4], char outputfile[100])
{
    int player_number = 1; //ID of current player that places
    int penguins_copy = penguins; //Copy of variable, because there will be operations on it in each iteration
    int turn_number = 0; //Turns of adding penguins that have already occurred
    int *pointer_to_board = &board[0][0][0]; //Pointer to board to pass by reference to functions
    int total_penguins_to_be_placed = number_of_players*penguins; //Calculating total number of placings to be done

    if(tiles_with_one_fish(m, n, board, total_penguins_to_be_placed, 1) != 0) //Checking number of free tiles with one fish
    {
        return 2; //Returning error
    }

    if(penguins <= 0) //Checking if there are declared penguins to place
    {
        printf("Skipper: Kowalski, analysis.\n");
        printf("Kowalski: Number of penguins was not declared in command line/ was less than 1/ was in inappropriate format!\n");
        return 3;
    }

    while(1)//Adds penguins until there are no penguins left(will return 0 in this case)
    {
        while(player_number<=number_of_players) //Each player adds one penguin
        {
            penguins = penguins_copy; //Bringing back initial value of penguins (Later I do some operations on its value)

            if(is_board_correct(m, n, board) != 0) //Check if board is correct
            {
                return 3;
            }
            penguins = penguins_left(m, n, board, penguins, player_number); //Checking number of penguins left to be placed

            if(penguins < 0) //Informing the player about the number of penguins on the board
            {
                printf("Skipper: Kowalski, analysis.\n");
                printf("Kowalski: There are too many of us.\n");
                return 3;
            }
            else if(penguins == 0 && turn_number == penguins_copy)//If no penguins left to place 1 is returned
            {
                printf("Skipper: Kowalski, analysis.\n");
                printf("Kowalski: You have already placed all available penguins.\n");
                return 1;
            }
            else if(penguins == 0 && turn_number != penguins_copy)//Checking if there were exactly as many turns of placing as penguins to be placed
            {
                printf("Skipper: Kowalski, analysis.\n");
                printf("Kowalski: Number of turns of placing is not equal to number of penguins placed.\n");
                return 2;
            }
            place_penguin_on_tile(0, 0, m, n, board, pointer_to_board, player_number, 1); //Here penguin is placed, first two variables are not important

            if(save_board_to_file(m, n, penguins_copy, number_of_players, board, outputfile, 1, NULL, NULL, NULL) != 0) //Checking if saving was successful
            {
                return 2;
            }

            player_number+=1; //Letting another player place a penguin
        }
        turn_number += 1; //End of turn of placing
        player_number = 1; //Next turn of placing, will start from player 1

    }
    printf("Skipper: Kowalski, analysis.\n");
    printf("Kowalski: While loop broke without break statement. How is it even possible? \n");
    return 3;//Should never happen
}

int placing_automatic(int penguins, char outputfile[100], char inputfile[100])
{
    int m, n, i;
    int *pointer_to_m = &m;
    int *pointer_to_n = &n;

    find_size(pointer_to_m, pointer_to_n, inputfile);
    int board[m][n][4];

    //Information about current state of the board
    int player_number = 7; //Our ID
    char IDs[9][20];//Data about other teams
    int IDnumeric[9];
    int pointsperteam[9];
    int teams_placed = 0; //Number of teams, other than our, that have already placed at least one penguin
    char *pointer_to_IDs[9];

    for(i=0; i<9; i++)
    {
        pointer_to_IDs[i] = &IDs[i][0];
    }

    int *pointer_to_IDnumeric = &IDnumeric[0];
    int *pointer_to_pointsperteam  = &pointsperteam[0];
    int *pointer_to_teams_placed = &teams_placed;
    int spaces_available;
    int *pointer_to_board = &board[0][0][0]; //Pointer to board to pass by reference to functions
    int penguins_copy = penguins;

    read_from_file_to_board(pointer_to_board, m, n, inputfile, pointer_to_teams_placed, pointer_to_IDs, pointer_to_IDnumeric, pointer_to_pointsperteam);

    if(is_board_correct(m, n, board) != 0) //Check if board is correct
    {
        return 3;
    }

    spaces_available = tiles_with_one_fish(m, n, board, 1, 2);  //Checking if there is at least one free tile with one fish (1 - penguin to place, 2 - mode number)

    if(spaces_available == -1) //Returning error
    {
        return 2;
    }

    penguins = penguins_left(m, n, board, penguins, player_number);
    if(penguins == 0) //If there is less then 1 penguin to be placed program won't proceed
    {
        return 1; //We return 1 when no penguins left to be placed
    }
    else if(penguins < 0)
    {
        printf("Skipper: Kowalski, analysis.\n");
        printf("Kowalski: There is too many of us!");
        return 2;
    }

    int tiles_empty[spaces_available][3]; //Stores information about all empty tiles
    int *pointer_to_tiles_empty = &tiles_empty[0][0];
    if(fill_tiles_empty_array(m, n, board, spaces_available, pointer_to_tiles_empty)!=0) //Fills tiles_empty array
    {
        return 2;
    }

    int best_tile[2]; //Coordinates m,n of the best tile to place a penguin on
    int *pointer_to_best_tile = &best_tile[0];

    assign_points(m, n, spaces_available, board, tiles_empty, pointer_to_best_tile);//Will do the AI magic to select place to place penguin

    int m_coordinate = best_tile[0];
    int n_coordinate = best_tile[1];

    place_penguin_on_tile(m_coordinate, n_coordinate, m, n, board, pointer_to_board, player_number, 2); //Here penguin is placed

    if(save_board_to_file(m, n, penguins_copy, teams_placed, board, outputfile, 2, pointer_to_IDs, pointer_to_IDnumeric, pointer_to_pointsperteam) != 0) //Checking if saving was successful
    {
        return 2;
    }

    return 0;
}

