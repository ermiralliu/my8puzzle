#include "Models/Board.hpp"
#include "Models/SearchNode.hpp"
#include <list>

using Models::Board;
using Models::SearchNode;


constexpr int N = 4;

class Solver {
private:
    Board<N> initial;
public:
    Solver(const Board<N>& initial) : initial(initial) {}
    std::list<Board<N>> solution();
private:
    std::list<Board<N>> makeHistory(SearchNode<N>* node);
};
