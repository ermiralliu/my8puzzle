#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "../Models/Board.hpp"
#include "../Models/SearchNode.hpp"
#include <list>

// This is where the size is set
constexpr int N = 4;

using Board = Models::Board<N>;
using SearchNode = Models::SearchNode<N>;

class Solver {
private:
  Board initial;
  uint moves;
public:
  uint getMoves() const{
    return moves;
  }
  Solver(const Board& initial) : initial(initial) {}
  std::list<Board> solution();
private:
  std::list<Board> makeHistory(SearchNode* node);
};
#endif