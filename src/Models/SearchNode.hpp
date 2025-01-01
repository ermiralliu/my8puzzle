#include "Board.hpp"

namespace Models{

template <int N>
struct SearchNode{
    int previous_board_id;
    int id; // -> e merr nga ajo qe ia fut
    Board<N> board;
    // int moves; // dhe kte skemi fare pse e shenojme // unnecessary cause we'll fetch the past from the database
    
  public:

    SearchNode() = default;

    SearchNode(int previous, int id, Board current, int moves) : 
      previous_board_id{previous},
      id{id},
      board{current},
      moves{moves}
    {}
      
    static int Compare(SearchNode a, SearchNode b) {  // this will just be declared as a lambda in SolverService
      int manha = a.manhattanPriority - b.manhattanPriority;
      return manha;
    }
    
    inline int manhattanPriority() const {
      return board.ManhattanDistance + moves;
    }
      // nese eshte 0, athere s'ka pas prind
  };

}


