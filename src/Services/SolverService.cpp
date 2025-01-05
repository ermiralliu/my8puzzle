#include "SolverService.hpp"
#include <cstddef>
#include <memory>
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
  std::stack<std::shared_ptr<SearchNode>> queue{};
  // int id = 0;
  queue.push(std::make_shared<SearchNode>(nullptr, initial));

  std::shared_ptr<SearchNode> finalNode = nullptr;

  while (!queue.empty()) {
    std::stack<std::shared_ptr<SearchNode>> nextBox;
    while (!queue.empty()) {
      std::shared_ptr<SearchNode> currentNode = queue.top();
      queue.pop();
      // std::cout<< moves++<<"\n";

      finished.insert(currentNode->board.getTiles());

      if (currentNode->board.isGoal()) {
        finalNode = currentNode;
        // moves = currentNode->moves;
        std::cout<< "Queue size: "<< queue.size()<< ", Set size: " << finished.size()<< "\n";
        std::cout<< "Next box: " << nextBox.size() << "\n";
        std::stack<std::shared_ptr<SearchNode>>{}.swap(queue);
        std::stack<std::shared_ptr<SearchNode>>{}.swap(nextBox);
        BoardMap{}.swap(finished);
        return makeHistory(finalNode);
      } else {
        // std::cout<< "Entered within the else \n";
        for (auto neighbor : currentNode->board.neighbors()) {
          // std::cout<< "Entered within the neighbor \n";
          Board board = neighbor.board;
          bool isNextBox = neighbor.isNextBox;
          if (finished.count(board.getTiles())) {
            continue;
          }
          auto nextSearchNode = std::make_shared<SearchNode>(currentNode, board);
          if (isNextBox)
            nextBox.push(nextSearchNode);
          else
            queue.push(nextSearchNode);
        }
      }
    }
    if (!nextBox.empty()) {
      queue = std::move(nextBox); // Move the contents of nextBox to queue
    }
  }
  return std::list<Board>();
}

std::list<Board> Solver::makeHistory(std::shared_ptr<SearchNode> node) {
  std::list<Board> boards;
  while(node != nullptr){
    boards.push_front(node->board);
    node = node->parent;
  }
  moves = boards.size()-1;
  std::cout<< "Final list size: "<<boards.size()<<"\n";
  return boards;
}