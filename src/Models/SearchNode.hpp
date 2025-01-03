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

    SearchNode(int previous, int id, Board<N> current) : 
      previous_board_id{previous},
      id{id},
      board{current}
    {}

  };

}


