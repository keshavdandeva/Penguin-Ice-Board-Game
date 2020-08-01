#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//arg 1 = row(m), 2 = col(n)
int main(int argc, char *argv[]) {
	const char *filename = "board_team07.txt";
	int rows = atoi(argv[1]);
	int cols = atoi(argv[2]);

	int rand_fish = 0;

	srand(time(NULL));
	FILE *map = fopen(filename, "w+");
	// write row 1 with rows and cols
	fprintf(map, "%d %d\n", rows, cols);
	// write rest of the map
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			rand_fish = rand() % (3) + 1;
			fprintf(map, "%d0 ", rand_fish); // Player ID is 0 coz no players have been placed yet
		}
		fprintf(map, "\n");
	}
	// write player details add to placement phase later
	// int players = atoi(argv[3]);
	// const char *player_ids[5] = {add array with ids};
	// int player_choice_randomizer = 0;
	// for (int i = 0; i < players; ++i) {
	// 	player_choice_randomizer = rand() % (4);
	// 	fprintf(map, "%s%d0\n", player_ids[player_choice_randomizer], i+1);
	// }
	fclose(map);
	return 0;
}