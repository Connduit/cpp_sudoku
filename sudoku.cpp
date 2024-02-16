// main
#include "board.h"
#include <iostream>
#include <vector> 
#include <set>


int main(int argc, char** argv)
{
	vector<vector<int>> puzzle = {
									{0,0,1,4,0,0,9,7,0},
									{4,0,0,8,0,0,5,1,2},
									{0,0,0,0,1,0,6,4,0},
									{0,0,0,0,0,0,3,8,7},
									{1,8,2,3,0,0,4,5,9},
									{3,7,4,5,9,8,1,2,6},		
									{9,1,8,2,3,4,7,6,5},
									{0,4,3,0,0,0,0,9,1},
									{0,6,0,0,0,0,0,3,4}		
								};
	
	Board b = Board(puzzle);
	b.printBoard();
	cout << endl;

	while (!b.solved())
	{
		b.solve();
	}
	b.printBoard();
	cout << endl;

	
	return 0;
}
