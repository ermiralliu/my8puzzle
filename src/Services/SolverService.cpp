#include "Models/Board.hpp"
#include "Models/BoardSave.hpp"
#include "Models/SearchNode.hpp"
#include <forward_list>
#include <iostream>
#include <unordered_set>
#include <deque>

using Models::Board;
using Models::SearchNode;
using Models::BoardSave;

constexpr int N = 4;

class SolverService {
private:

  int minimal_moves = -1;
  Board<N> initial;

  int id = 1; // I'll have to manually manage id's
  // BoardRepository boardRepository;

  // TaskService taskService;

public:
  // SolverService(Board<N> initial) : initial {initial} {}

  // void Init(Board initial, int n, TaskService es) {
  //   this.initial = initial;
  //   this.n = n;
  //   Refresh();
  //   taskService = es;
  // }

  // void Reinit(Board initial, int n) {
    
  // }

  // void Refresh() {
  //   id = 0;
  //   boardRepository.deleteAll();
  // }

  std::forward_list<Board<N>> solution() {
    auto hasher = [](BoardSave<N> node) { return node.getHash(); };
    std::unordered_set<BoardSave<N>, decltype(hasher)> finished;

    std::deque<SearchNode<N>> queue;
    queue.push_front( SearchNode<N>{0, id++, initial} );
    SearchNode<N> finalNode;

    while ( !queue.empty() ) {
      SearchNode<N> currentNode = queue.front(); // dequeue // the minimal value is the highest priority in a minPQ
      queue.pop_front();
      finished.insert( BoardSave<N>{currentNode.board.getTiles() , currentNode.board.getHash()} ); 
      // Ia vlen me shume ta fusesh ne set pasi
      // mbaron ne queue,
      if (currentNode.board.isGoal()) {
        finalNode = currentNode;
        taskService.clear();
        break;
      } else {
        // taskService.addTask([](){ boardEntityService.insertBoard(currentNode) });

        for( const auto& next_board : currentNode.board.neighbors()) {
          // int next_moves = currentNode.moves + 1;
          SearchNode<N> searchNode { currentNode.id, id++, next_board};
          
          if (finished.count( BoardSave<N>{searchNode.board.getTiles() , searchNode.board.getHash()} ))
            continue;
          ++id;
          queue.push_front(searchNode);
          // maybe a manager function here
        }
      }
    }
    // System.out.println("Queue size at the end: "+ queue.size());
    std::cout << "Queue size at the end: " << queue.size() << " Set: " << finished.size()<< "\n";
    // queue = null; // elligible for GC, although it probably doesn't help much
    // finished.Clear();
    // minimal_moves = finalNode.moves; // vendosim minimal moves
    // Refresh();
    queue.shrink_to_fit();
    std::unordered_set<BoardSave<N>, decltype(hasher)>{}.swap(finished);
    return MakeHistory(finalNode);
  }

private:

  std::forward_list<Board<N>> MakeHistory(SearchNode<N> node) {
    std::forward_list<Board<N>> history; // se dua t'i shtoj te koka boarded e meparshme, dhe LL i ka O(1), ndryshe
    // nga arrayList
    history.push_front(node.board);
    // var iterator = boardRepository.findById((long)node.previous_board_id);

    // while (iterator.isPresent()) {
    //   // var boardNode = iterator.get();
    //   // history.AddFirst(Board.fromString(boardNode.boardString, n));
    //   iterator = boardNode.getParent();
    // }
    // minimal_moves = node.moves;

    return history;
  }

  int Moves() { // minimal number of moves to solve the board
    return minimal_moves;
  }
}
