#include <iostream>

bool alldiff(int set[]) 
{
	//test uniqueness of each value in array
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (set[i] == set[j] && i != j) {
				//return false if found a value twice
				return false;
			}
		}
	}
	//return true if each value is unique
	return true;
}

int check_conflicts(int a[][9]) 
{
	int conflicts = 0;
	
	//check rows for conflicts
	for (int i = 0; i < 9; i++) {
		if (!alldiff(a[i])) {
			conflicts++;
		}
	}

	//check cols for conflicts
	for (int i = 0; i < 9; i++) {
		int tmp[9];
		for (int j = 0; j < 9; j++){
			tmp[j] = a[j][i];
		}
		if (!alldiff(tmp)) {
			conflicts++;
		}
	}

	//check boxes for conflicts
	//this was a horrible way to do it and im sorry
	int box1[9] = { a[0][0], a[0][1], a[0][2], a[1][0], a[1][1], a[1][2], a[2][0], a[2][1], a[2][2] };
	int box2[9] = { a[0][3], a[0][4], a[0][5], a[1][3], a[1][4], a[1][5], a[2][3], a[2][4], a[2][5] };
	int box3[9] = { a[0][6], a[0][7], a[0][8], a[1][6], a[1][7], a[1][8], a[2][6], a[2][7], a[2][8] };
	int box4[9] = { a[3][0], a[3][1], a[3][2], a[4][0], a[4][1], a[4][2], a[5][0], a[5][1], a[5][2] };
	int box5[9] = { a[3][3], a[3][4], a[3][5], a[4][3], a[4][4], a[4][5], a[5][3], a[5][4], a[5][5] };
	int box6[9] = { a[3][6], a[3][7], a[3][8], a[4][6], a[4][7], a[4][8], a[5][6], a[5][7], a[5][8] };
	int box7[9] = { a[6][0], a[6][1], a[6][2], a[7][0], a[7][1], a[7][2], a[8][0], a[8][1], a[8][2] };
	int box8[9] = { a[6][3], a[6][4], a[6][5], a[7][3], a[7][4], a[7][5], a[8][3], a[8][4], a[8][5] };
	int box9[9] = { a[6][6], a[6][7], a[6][8], a[7][6], a[7][7], a[7][8], a[8][6], a[8][7], a[8][8] };

	if (!alldiff(box1)) {
		conflicts++;
	}
	if (!alldiff(box2)) {
		conflicts++;
	}
	if (!alldiff(box3)) {
		conflicts++;
	}
	if (!alldiff(box4)) {
		conflicts++;
	}
	if (!alldiff(box5)) {
		conflicts++;
	}
	if (!alldiff(box6)) {
		conflicts++;
	}
	if (!alldiff(box7)) {
		conflicts++;
	}
	if (!alldiff(box8)) {
		conflicts++;
	}
	if (!alldiff(box9)) {
		conflicts++;
	}

	return conflicts;
}

int main(int argc, char* argv[]) {

	//This soduku solver is very inefficient and runs forever on longer problems
	//but it can solve extremely small problems
	//It runs forever because after making progress for a while
	//It is unable to find any values for any variables on the whole board that would
	//reduce the amount of conflicts it currently has and randomly resets
	//this process happens forever on larger problems like the one shown below
	//I have some hypothesis on how to fix this
	//but I am prioritizing studying for the midterm
	//so I will probably revist this later
	std::cout << "Starting sudoku solver..." << std::endl;

	//puzzle to solve
	int puzzle[9][9] = 
   {{8, 0, 0, 4, 3, 6, 5, 0, 0},
	{0, 0, 3, 0, 7, 0, 0, 0, 0}, 
	{4, 7, 6, 0, 5, 0, 0, 0, 1}, 
	{9, 0, 4, 0, 1, 0, 0, 2, 0},
	{1, 0, 8, 0, 0, 0, 3, 0, 4}, 
	{0, 2, 0, 0, 6, 0, 1, 0, 8}, 
	{2, 0, 0, 0, 4, 0, 9, 1, 3},
	{0, 0, 0, 0, 2, 0, 4, 0, 0}, 
	{0, 0, 9, 3, 8, 1, 0, 0, 6}};

	//print puzzle
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			std::cout << puzzle[i][j] << "\t";
			if (j == 8) {
				std::cout << std::endl;
			}
		}
	}

	//initialize helpers
	int puzzle_use[9][9];
	int puzzle_tmp[9][9];
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			puzzle_use[i][j] = puzzle[i][j];
			puzzle_tmp[i][j] = puzzle[i][j];
		}
	}

	int conflicts = 28;
	bool found_conflict = false;
	while (conflicts != 0) {
		//loop through every grid tile
		found_conflict = false;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				// only test values if square is editable
				if (puzzle[i][j] == 0) {
					//test each possible value
					for (int x = 0; x < 9; x++) {
						puzzle_tmp[i][j] = x;
						//if there are less total conflicts with this value, then use this value
						int tmp_val = check_conflicts(puzzle_tmp);
						if (tmp_val < conflicts) {
							conflicts = tmp_val;
							found_conflict = true;
							//loop through all because it could need to propogate randomly reset values
							for (int g = 0; g < 9; g++) {
								for (int h = 0; h < 9; h++) {
									puzzle_use[g][h] = puzzle_tmp[g][h];
								}
							}
							std::cout << "conflicts: " << conflicts << std::endl;
						}
					}

					//set puzzle tmp back to puzzle use to continue testing
					for (int g = 0; g < 9; g++) {
						for (int h = 0; h < 9; h++) {
							puzzle_tmp[g][h] = puzzle_use[g][h];
						}
					}

				}
			}
		}
		//if conflicts didnt change after going through whole board, do a random reset
		if (!found_conflict) {
			conflicts = 28;
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					if (puzzle[i][j] == 0) {
						puzzle_tmp[i][j] = (rand() % 9) + 1;
					}
				}
			}
		}
	}

	//found solution!
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			std::cout << puzzle_use[i][j] << "\t";
			if (j == 8) {
				std::cout << std::endl;
			}
		}
	}
	return 0;
}