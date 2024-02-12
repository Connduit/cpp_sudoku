#include "tile.h"
#include <vector>
#include <set>

#define SIZE 9

class Board {
public:
  Board();
  Board(std::vector<std::vector<int>> puzzle);
  std::vector<std::vector<Tile>> board;
  std::vector<Tile> getRowNeighbors(Tile tile);
  std::vector<Tile> getColNeighbors(Tile tile);
  std::vector<Tile> getGroupNeighbors(Tile tile);
  std::set<int> getNeighbors(Tile tile);
  // std::set<int> lastCandidate(Tile tile);
  void printBoard();
  void solve();
  bool solved();
};
