#include "SolverService.hpp"
#include <unordered_set>
#include <deque>
#include <algorithm>

// ... (Board, BoardSave, SearchNode class declarations as before)
using Tiles = Models::Tiles<4>;

// std::hash is stateless, so no thread-related problems if you use it on more than one thread
constexpr std::hash<uint64_t> tileHasher{};

std::list<Board> Solver::solution() {
  constexpr auto hashingFunction = [](Tiles tiles) {  // this should be done with an if constexpr for row_sizes other than 4
    return tileHasher(tiles.toLong());
  };
  std::unordered_set<Tiles, decltype(hashingFunction)> finished;
  std::deque<SearchNode> queue; // I'm using this as a stack, but i wanted to avoid huge reallocations and copyings
  // since this one is made of many arrays instead
  int id = 0;
  queue.emplace_back(SearchNode{-1,id++,initial});

  SearchNode* finalNode = nullptr;
  int boxNumber = 0;

  while (!queue.empty()) {
    std::deque<SearchNode> nextBox;
    while (!queue.empty()) {
      SearchNode currentNode = queue.back();
      queue.pop_back();

      finished.insert(currentNode.board.getTiles());

      if (currentNode.board.isGoal()) {
        finalNode = &currentNode;
        return makeHistory(finalNode);
      } else {
        for (auto neighbor : currentNode.board.neighbors()) {
          Board board = neighbor.board;
          bool isNextBox = neighbor.isNextBox;
          if (finished.count(board.getTiles())) {
            continue;
          }
          SearchNode nextSearchNode{currentNode.id, id++, board};
          if (isNextBox)
            nextBox.emplace_back(nextSearchNode);
          else
            queue.emplace_back(nextSearchNode);
        }
      }
    }
    if (!nextBox.empty()) {
      boxNumber++;
      queue = std::move(nextBox); // Move the contents of nextBox to queue
    }
  }
  return std::list<Board>();
}

std::list<Board> Solver::makeHistory(SearchNode* node) {
  std::list<Board> boards;
  // boards.push_front({}); // push_front is used to add to dhe front O(1)
  // while(node != nullptr){
  //     boards.push_back(node->board);
  //     node = node->previous;
  // }
  // std::reverse(boards.begin(), boards.end());
  return boards;
}