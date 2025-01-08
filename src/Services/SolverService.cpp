#include "SolverService.hpp"
#include <cstddef>
#include <memory>
#include <stack>
#include <unordered_map>


// ... (Board, BoardSave, SearchNode class declarations as before)

struct BoardHash {
  static constexpr std::hash<std::size_t> tileHasher{};
  std::size_t operator()(const Tiles &k) const {
    return tileHasher(k.toLong()); // Use std::hash for int
  }
};

// std::hash is stateless, so no thread-related problems if you use it on more
// than one thread

struct SavedBoard{
  Tiles tiles;
  bool path;
};

using BoardMap = std::unordered_map<Tiles, Tiles, BoardHash>;
// ktu do behet lidhja prind femije. E kemi 8 + 8 byte. Would be worse if the
// kept the shared_ptr
constexpr Tiles emptyTiles = std::array<unsigned char, 16>{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

template <bool FORWARD>
std::list<Tiles> makeHistory(Tiles& node, BoardMap& finished) {
  std::list<Tiles> boards;
  auto iterator = finished.at(node);
  while (iterator != emptyTiles) {
    if constexpr(FORWARD){
      boards.push_front(iterator);
    }else{
      boards.push_back(iterator);
    }
    iterator = finished.at(iterator);
  }
  std::cout << "Final list size: " << boards.size() << "\n";
  return boards;
}

std::list<Tiles> combinePaths(
  Tiles& forward, 
  Tiles& middle,  // convergence point
  Tiles& backward,
  BoardMap& finished
){
  auto path = makeHistory<true>(forward, finished);
  auto backwardPath = makeHistory<false>(backward, finished);
  backwardPath.pop_front(); // Remove the duplicate meeting node
  path.push_back(middle);
  path.splice(path.end(), backwardPath);
  return path;
}

std::shared_ptr<SearchNode>
oneLoop(BoardMap &finished, std::stack<std::shared_ptr<SearchNode>>& queue) {
  std::stack<std::shared_ptr<SearchNode>> nextBox;
  while (!queue.empty()) {
    std::shared_ptr<SearchNode> currentNode = queue.top();
    queue.pop();
    // std::cout<< moves++<<"\n";
    finished[currentNode->board.getTiles()] =
        currentNode->parent->board.getTiles(); // lidhim rrugen me prindin

    if (currentNode->board.isGoal()) {
      std::cout << "Next box: " << nextBox.size() << "\n";
      BoardMap{}.swap(finished);
      return currentNode;
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
  return nullptr;
}

void printSizes(const std::stack<std::shared_ptr<SearchNode>>& forward, const std::stack<std::shared_ptr<SearchNode>>& backward, const BoardMap& finished){
  std::cout << "Queue size: " << forward.size() <<"\n";
  std::cout << "BackwardQueue size: " << backward.size() <<"\n";
  std::cout <<"Set size: " << finished.size() << "\n";
}

std::shared_ptr<SearchNode> logic(const Board& initial, BoardMap& finished){
  std::stack<std::shared_ptr<SearchNode>> queue{};
  // int id = 0;
  queue.push(std::make_shared<SearchNode>(nullptr, initial));

  std::stack<std::shared_ptr<SearchNode>> backwardQueue{};
  backwardQueue.push(
      std::make_shared<SearchNode>(nullptr, Board::make_init_backwards()));

  std::shared_ptr<SearchNode> finalNode = nullptr;

  while (!queue.empty() || !backwardQueue.empty()) {
    if (!queue.empty()) {
      std::shared_ptr<SearchNode> final = oneLoop(finished, queue);
      if(final != nullptr){
        printSizes(queue, backwardQueue, finished);
        return final;
      }
    }
    if (!backwardQueue.empty()) {
      std::shared_ptr<SearchNode> final = oneLoop(finished, queue);
      if(final != nullptr){
        printSizes(queue, backwardQueue, finished);
        return final;
      }
    }
  }
  return nullptr;
}


std::list<Tiles> Solver::solution() {
  BoardMap finished{};
  auto final = logic(initial, finished);
  if(final == nullptr)
    return makeHistory(final);
  return std::list<Board>{};
}