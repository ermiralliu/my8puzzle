#include "Board.hpp"
#include <memory>

namespace Models{

template <int N>
struct SearchNode{
    // int previous_board_id;
    // SearchNode<N>* previousNode; // this is so i can test it rn. Will be made to id later
    std::shared_ptr<SearchNode<N>> parent;
    // int id; // -> e merr nga ajo qe ia fut
    Board<N> board;
    // int moves;
    // int moves; // dhe kte skemi fare pse e shenojme // unnecessary cause we'll fetch the past from the database
    
  public:

    SearchNode() = default;

    // SearchNode(int previous, int id, const Board<N>& current, int moves) : 
    //   previous_board_id{previous},
    //   id{id},
    //   board{current},
    //   moves{moves}
    // {}

     SearchNode(std::shared_ptr<SearchNode<N>> previous, Board<N> current) : 
      parent{previous},
      // id{id},
      board{current}
    {}

  };

}


