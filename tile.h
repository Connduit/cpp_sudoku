#include <set>
#include <iostream>

class Tile {
public:
  Tile();
  Tile(int pos_x, int pos_y, int tile_value);
  int pos_x;
  int pos_y;
  int tile_value;
  std::set<int> possibilities = {1,2,3,4,5,6,7,8,9};
  void printTile();
  friend std::ostream& operator<<(std::ostream& os, const Tile& other);
  friend bool operator<(const Tile& lhs, const Tile& rhs);
  ~Tile(){};
};

//std::ostream& operator<<(std::ostream& os, const Tile& other);
//bool operator<(const Tile& lhs, const Tile& rhs)
