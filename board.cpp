#include "board.h"
#include <iostream>
#include <algorithm>

// TODO: is this really best practice?
using std::cout;
using std::endl;

Board::Board()
{
	// TODO: init a default board? maybe default board
}

Board::Board(vector<vector<int>> puzzle)
{
	// TODO: find a way to not use the default constructor for Tile()
	vector<vector<Tile>> newBoard(9, vector<Tile>(9, Tile()));
	// vector<vector<Tile>> newBoard(SIZE, vector<Tile>(SIZE, Tile())); // change to this 
	for (int row = 0; row < SIZE; ++row)
	{
		for (int col = 0; col < SIZE; ++col)
		{
			newBoard[row][col].pos_x = row;
			newBoard[row][col].pos_y = col;
			newBoard[row][col].tile_value = puzzle[row][col];;

			if (newBoard[row][col].tile_value != 0)
			{
				newBoard[row][col].possibilities = {newBoard[row][col].tile_value};
			}
		}
	}
	this->board = newBoard;
}

void Board::printBoard()
{
	for (int row = 0; row < SIZE; ++row)
	{
		for (int col = 0; col < SIZE; ++col)
		{
			this->board[row][col].printTile() // replace with this->board[row][col] becuz of operator overloading?
			cout << " ";
		}
		cout << endl;
	}
}

vector<Tile> Board::getRowNeighbors(Tile tile)
{
	return this->board[tile.pos_x];
}

vector<Tile> Board::getColNeighbors(Tile tile)
{
	vector<Tile> colNeighbors;
	for (int row = 0; row < SIZE; ++row)
	{
		colNeighbors.push_back(this->board[row][tile.pos_y]);
	}
	return colNeighbors;
}

vector<Tile> Board::getGroupNeighbors(Tile tile)
{
	vector<Tile> groupNeighbors;
	int group_ind = (tile.pos_x/3)*3 + tile.pos_y/3;

	for (int row = 0; row < SIZE; ++row)
	{
		for (int col = 0; col < SIZE; ++col)
		{
			if (((row/3)*3 + col/3) == group_ind)
			{
				groupNeighbors.push_back(this->board[row][col]);
			}
		}
	}
	return groupNeighbors;
}

set<int> Board::getNeighbors(Tile tile)
{
	vector<Tile> rNeighbors = this->getRowNeighbors(tile);
	vector<Tile> cNeighbors = this->getColNeighbors(tile);
	vector<Tile> gNeighbors = this->getGroupNeighbors(tile);

	set<int> result;
	for (int tile = 0; tile < SIZE; ++tile)
	{
		result.insert(rNeighbors[tile].tile_value);
		result.insert(cNeighbors[tile].tile_value);
		result.insert(gNeighbors[tile].tile_value);
	}
	return result;
}

// TODO: fix this function... actual dog implementation
set<int> Board::lastCandidate(Tile tile)
{
	set<int> result;
	vector<Tile> rNeighbors = this->getRowNeighbors(tile);
	vector<Tile> cNeighbors = this->getColNeighbors(tile);
	vector<Tile> gNeighbors = this->getGroupNeighbors(tile);

	vector<int> rpNeighbors;
	vector<int> cpNeighbors;
	vector<int> gpNeighbors;

	for (int tile = 0; tile < SIZE; ++tile)
	{
		vector<int> rpvNeighbors(rNeighbors[tile].possibilities.begin(), rNeighbors[tile].possibilities.end());
		vector<int> cpvNeighbors(cNeighbors[tile].possibilities.begin(), cNeighbors[tile].possibilities.end());
		vector<int> gpvNeighbors(gNeighbors[tile].possibilities.begin(), gNeighbors[tile].possibilities.end());
		// TODO: rename variable 'ind' ?
		for (unsigned int ind = 0; ind < SIZE; ++ind)
		{
			if (rpvNeighbors.size() >= ind && rpvNeighbors.size() != 0)
				rpNeighbors.push_back(rpvNeighbors[ind]);
			if (cpvNeighbors.size() >= ind && cpvNeighbors.size() != 0)
				cpNeighbors.push_back(cpvNeighbors[ind]);
			if (gpvNeighbors.size() >= ind && gpvNeighbors.size() != 0)
				gpNeighbors.push_back(gpvNeighbors[ind]);
		}
	}

	for (auto it = tile.possibilities.begin(); it != tile.possibilities.end(); ++it)
	{
		int c1 = count(rpNeighbors.begin(), rpNeighbors.end(), *it);
		int c2 = count(cpNeighbors.begin(), cpNeighbors.end(), *it);
		int c3 = count(gpNeighbors.begin(), gpNeighbors.end(), *it);

		// TODO: remove vars c1,c2,c3 and just shove it all into the if statement?
		if (c1 == 1 || c2 == 1 || c3 == 1)
		{
			// TODO: figure out how to return *it immediately w/o making the variable 'res'
			set<int> res;
			res.insert(*it);
			return res;
		}
	}
	return result;
}

// TODO: skip over inds of tiles that are already solved for optimization?
void Board::solve()
{
	for (int row = 0; row < SIZE; ++row)
	{
		for (int col = 0; col < SIZE; ++col)
		{
			set<int> currentNeighbors = this->getNeighbors(this->board[row][col]);
			set<int> result;

			std::set_difference(this->board[row][col].possibilities.begin(), this->board[row][col].possibilities.end(), currentNeighbors.begin(), currentNeighbors.end(), std::inserter(result, result.end()));
			this->board[row][col].possibilities = result;

			set<int> lc = lastCandidate(this->board[row][col]);
			if (!lc.empty())
			{
				this->board[row][col].possibilities = lc;
			}

			if (this->board[row][col].possibilities.size() == 1)
			{
				this->board[row][col].tile_value = *this->board[row][col].possibilities.begin();
			}
		}
	}
}

bool Board::solved()
{
	for (int row = 0; row < SIZE; ++row)
	{
		for (int col = 0; col < SIZE; ++col)
		{
			if (this->board[row][col].tile_value == 0)
			{
				return false;
			}
		}
	}
	return true;
}
