#include "tile.h"
#include <iostream>

// TODO: change board initialization so we never have to call/create a null tile
Tile::Tile()
{
	// null tile
	this->pos_x = -1;
	this->pos_y = -1;
	this->tile_value = -1;
}

Tile:Tile(int pos_x, int pos_y, int tile_value)
{
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	this->tile_value = tile_value;

	// TODO: turn into ternary
	if (tile_value == 0)
	{
		this->possibilities = {1,2,3,4,5,6,7,8,9};
	}
	else
	{
		this->possibilities = {tile_value};
	}
}

// TODO: remove this function cuz operator<< is overloaded
void Tile::printTile()
{
	std::cout << this->tile_value;
}

std::ostream& operator<<(std::ostream& os, const Tile& other)
{
	os << other.tile_value;
	return os;
}

bool operator<(const Tile& lhs, const Tile& rhs)
{
	return lhs.tile_value < rhs.tile_value;
}
