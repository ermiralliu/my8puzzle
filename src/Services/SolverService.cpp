#include "SolverService.hpp"
#include <cstddef>
#include <stack>
#include <unordered_map>
#include <utility>

// ... (Board, BoardSave, SearchNode class declarations as before)

struct BoardHash {
  static constexpr std::hash<std::size_t> tileHasher{};
  std::size_t operator()(const Tiles &k) const {
    return tileHasher(k.toLong()); // Use std::hash for int
  }
};

enum class PathDirection : unsigned char{
  FORWARD,
  BACKWARD
};

struct BoardAndPath{
  Tiles pattern;
  PathDirection dir;
};

// std::hash is stateless, so no thread-related problems if you use it on more
// than one thread

using BoardMap = std::unordered_map<Tiles, BoardAndPath, BoardHash>;
// ktu do behet lidhja prind femije. E kemi 8 + 8 byte. Would be worse if the
// kept the shared_ptr
constexpr Tiles emptyTiles = std::array<unsigned char, 16>{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

template <PathDirection DIR>
std::list<Tiles> makeHistory(Tiles& node, BoardMap& finished) {
  std::list<Tiles> boards;
  auto iterator = finished.at(node);
  while (iterator.pattern != emptyTiles) {
    if constexpr(DIR == PathDirection::FORWARD){
      boards.push_front(iterator.pattern);
    }else{
      boards.push_back(iterator.pattern);
    }
    iterator = finished.at(iterator.pattern);
  }
  std::cout << "Final list size: " << boards.size() << "\n";
  return boards;
}

std::list<Tiles> combinePaths(
  Tiles& forward, 
  // Tiles& middle,  // convergence point // the middle is included by the first queue to have it, we only need the back of the current and the rest resolves itself
  Tiles& backward,
  BoardMap& finished
){
  auto path = makeHistory<PathDirection::FORWARD>(forward, finished);
  auto backwardPath = makeHistory<PathDirection::BACKWARD>(backward, finished);
  // backwardPath.pop_front(); // Remove the duplicate meeting node
  path.splice(path.end(), backwardPath);
  return path;
}

template <PathDirection DIR>
std::pair<Tiles, Tiles> //forward tiles and backward tiles
oneLoop(BoardMap &finished, std::stack<SearchNode>& queue) {
  std::stack<SearchNode> nextBox;
  while (!queue.empty()) {
    SearchNode currentNode = queue.top();
    queue.pop();
    
    auto past = finished.find(currentNode.board.getTiles());
    if (finished.end() != past && past->second.dir != DIR) {
      std::cout << "Next box: " << nextBox.size() << "\n";
      if constexpr (DIR == PathDirection::FORWARD){
        return std::pair{currentNode.parent, past->first};
      }else{
        return std::pair{past->first, currentNode.parent};
      }
      
    } else {
      finished[currentNode.board.getTiles()] = {currentNode.parent, DIR}; // lidhim rrugen me prindin
      // std::cout<< "Entered within the else \n";
      auto neighbors = (DIR == PathDirection::FORWARD) 
        ? currentNode.board.neighbors() 
        : currentNode.board.neighborsBackwards();
      for (auto& neighbor : neighbors) {
        // std::cout<< "Entered within the neighbor \n";
        Board board = neighbor.board;
        bool isNextBox = neighbor.isNextBox;
        if (finished.count(board.getTiles())) {
          continue;
        }
        SearchNode nextSearchNode = {currentNode.board.getTiles(), board};
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
  return std::pair{emptyTiles, emptyTiles};
}

void printSizes(const std::stack<SearchNode>& forward, const std::stack<SearchNode>& backward, const BoardMap& finished){
  std::cout << "Queue size: " << forward.size() <<"\n";
  std::cout << "BackwardQueue size: " << backward.size() <<"\n";
  std::cout <<"Set size: " << finished.size() << "\n";
}

std::pair<Tiles, Tiles> logic(const Board& initial, BoardMap& finished){
  std::stack<SearchNode> queue{};
  // int id = 0;
  queue.push(SearchNode{emptyTiles, initial});

  std::stack<SearchNode> backwardQueue{};
  backwardQueue.push(  {emptyTiles, Board::make_init_backwards()} );


  while (!queue.empty() || !backwardQueue.empty()) {
    if (!queue.empty()) {
      auto final = oneLoop<PathDirection::FORWARD>(finished, queue); // I'll make this better later
      if(final.first != emptyTiles){
        printSizes(queue, backwardQueue, finished);
        return final;
      }
    }
    if (!backwardQueue.empty()) {
      auto final = oneLoop<PathDirection::FORWARD>(finished, queue);
      if(final.first != emptyTiles){
        printSizes(queue, backwardQueue, finished);
        return final;
      }
    }
  }
  return std::pair{emptyTiles, emptyTiles};
}


std::list<Tiles> Solver::solution() {
  BoardMap finished{};
  auto final = logic(initial, finished);
  if(final.first != emptyTiles){
    auto list = combinePaths(final.first, final.second, finished);
    moves = list.size()-1;
    return list;
  }
  return std::list<Tiles>{};
}