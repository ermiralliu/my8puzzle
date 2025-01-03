#include "SolverService.hpp"
#include <cstddef>
#include <unordered_set>
#include <stack>

// ... (Board, BoardSave, SearchNode class declarations as before)
using Tiles = Models::Tiles<N>;

struct BoardHash {
  static constexpr std::hash<std::size_t> tileHasher{};
  std::size_t operator()(const Tiles& k) const {
    return tileHasher(k.toLong()); // Use std::hash for int
  }
};

// std::hash is stateless, so no thread-related problems if you use it on more than one thread

using BoardMap = std::unordered_set<Tiles, BoardHash>;

std::list<Board> Solver::solution() {

  BoardMap finished{};
  std::stack<SearchNode> queue{};
  int id = 0;
  queue.push(SearchNode{-1,id++,initial,0});

  SearchNode* finalNode = nullptr;
  int boxNumber = 0;

  while (!queue.empty()) {
    std::stack<SearchNode> nextBox;
    while (!queue.empty()) {
      SearchNode currentNode = queue.top();
      queue.pop();
      // std::cout<< moves++<<"\n";

      finished.insert(currentNode.board.getTiles());

      if (currentNode.board.isGoal()) {
        finalNode = &currentNode;
        moves = currentNode.moves;
        std::cout<< "Queue size: "<< queue.size()<< ", Set size: " << finished.size()<< "\n";
        std::cout<< "Next box: " << nextBox.size() << "\n";
        std::stack<SearchNode>{}.swap(queue);
        std::stack<SearchNode>{}.swap(nextBox);
        BoardMap{}.swap(finished);
        return makeHistory(finalNode);
      } else {
        // std::cout<< "Entered within the else \n";
        for (auto neighbor : currentNode.board.neighbors()) {
          // std::cout<< "Entered within the neighbor \n";
          Board board = neighbor.board;
          bool isNextBox = neighbor.isNextBox;
          if (finished.count(board.getTiles())) {
            continue;
          }
          SearchNode nextSearchNode{currentNode.id, id++, board, currentNode.moves+1};
          if (isNextBox)
            nextBox.push(nextSearchNode);
          else
            queue.push(nextSearchNode);
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