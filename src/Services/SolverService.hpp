#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "../Models/Board.hpp"
#include "../Models/SearchNode.hpp"
#include <list>

// This is where the size is set
constexpr int N = 4;

using Board = Models::Board<N>;
using SearchNode = Models::SearchNode<N>;
using Tiles = Models::Tiles<N>;


class Solver {
private:
  Board initial;
  std::uint32_t moves;
public:
  std::uint32_t getMoves() const{
    return moves;
  }
  Solver(const Board& initial) : initial(initial) {}
  std::list<Tiles> solution();
// private:
//   std::list<Board> makeHistory(std::shared_ptr<SearchNode>& node);
};
#endif