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

struct BoardHash {
  static constexpr std::hash<std::size_t> tileHasher{};
  std::size_t operator()(const Tiles& k) const {
    return tileHasher(k.toLong()); // Use std::hash for int
  }
};

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
private:
  std::list<Tiles> makeHistory(
    Tiles& node, 
    std::unordered_map<Tiles, Tiles, BoardHash>& path_reconstruct, 
    Tiles& nullVal
  );
};
#endif