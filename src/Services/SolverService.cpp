#include "SolverService.hpp"
// #include <cstddef>
// #include <memory>
#include <unordered_map>
#include <unordered_set>
#include <stack>

// ... (Board, BoardSave, SearchNode class declarations as before)



// std::hash is stateless, so no thread-related problems if you use it on more than one thread

using BoardMap = std::unordered_set<Tiles, BoardHash>;

// we'll not be using a searchnode and it's parents we'll be using a hashset

void clear(BoardMap& finished, std::stack<Board>& queue, std::stack<Board>& nextBox, 
std::stack<Board>& queueBackwards, std::stack<Board>& queueBackwardsNextBox){
  std::stack<Board>{}.swap(queue);
  std::stack<Board>{}.swap(nextBox);
  BoardMap{}.swap(finished);
  std::stack<Board>{}.swap(queueBackwards);
  std::stack<Board>{}.swap(queueBackwardsNextBox);
}

std::list<Tiles> Solver::solution() {

  BoardMap finished{};
  std::unordered_map<Tiles, Tiles, BoardHash> path_reconstruct {};
  std::stack<Board> queue{};
  // int id = 0;
  queue.push(initial);
  Tiles cutoff = Tiles{ std::array<unsigned char, N*N>{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} };
  path_reconstruct[initial.getTiles()] = cutoff;

  // std::shared_ptr<SearchNode> finalNode = nullptr;

  while (!queue.empty()) {
    std::stack<Board> nextBox;
    while (!queue.empty()) {
      auto currentNode = queue.top();
      queue.pop();
      // std::cout<< moves++<<"\n";

      finished.insert(currentNode.getTiles());

      if (currentNode.isGoal()) {
        auto finalBoard = currentNode.getTiles();
        // moves = currentNode->moves;
        std::cout<< "Queue size: "<< queue.size()<< ", Set size: " << finished.size()<< "\n";
        std::cout<< "Next box: " << nextBox.size() << "\n";
        std::stack<Board>{}.swap(queue);
        std::stack<Board>{}.swap(nextBox);
        BoardMap{}.swap(finished);
        return makeHistory(finalBoard,path_reconstruct,cutoff);
      } else {
        // std::cout<< "Entered within the else \n";
        for (auto neighbor : currentNode.neighbors()) {
          // std::cout<< "Entered within the neighbor \n";
          Board board = neighbor.board;
          bool isNextBox = neighbor.isNextBox;
          if (finished.count(board.getTiles())) {
            continue;
          }
          path_reconstruct[board.getTiles()] = currentNode.getTiles();
          if (isNextBox)
            nextBox.push(board);
          else
            queue.push(board);
        }
      }
    }
    if (!nextBox.empty()) {
      queue = std::move(nextBox); // Move the contents of nextBox to queue
    }
  }
  return std::list<Tiles>{};
}

std::list<Tiles> Solver::makeHistory(Tiles& node, std::unordered_map<Tiles, Tiles, BoardHash>& path_reconstruct, Tiles& nullVal) {
  std::list<Tiles> boards;
  Tiles currentBoard = node;
  while(currentBoard != nullVal){
    boards.push_front(currentBoard);
    currentBoard = path_reconstruct.at(currentBoard);
  }
  moves = boards.size()-1;
  std::cout<< "Final list size: "<<boards.size()<<"\n";
  return boards;
}