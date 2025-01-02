#include "SolverService.hpp"
#include <unordered_set>
#include <deque>
#include <algorithm>

// ... (Board, BoardSave, SearchNode class declarations as before)

std::list<Board<N>> Solver::solution() {
    std::unordered_set<Models::Tiles<N>> finished;
    std::deque<SearchNode<N>> queue;

    queue.emplace_back(nullptr, initial);

    SearchNode<N>* finalNode = nullptr;
    int boxNumber = 0;

    while (!queue.empty()) {
        std::deque<SearchNode<N>> nextBox;
        while (!queue.empty()) {
            SearchNode currentNode = queue.back();
            queue.pop_back();

            finished.insert( currentNode.board );

            if (currentNode.board.isGoal()) {
                finalNode = &currentNode;
                return makeHistory(finalNode);
            } else {
                for (auto neighbor : currentNode.board.neighbors()) {
                    Board board = neighbor.board;
                    bool isNextBox = neighbor.isNextBox;
                    if (finished.count( board )) {
                        continue;
                    }
                    nextBox.emplace_back(&currentNode, board);
                }
            }
        }
        if (!nextBox.empty()) {
            boxNumber++;
            queue = std::move(nextBox); // Move the contents of nextBox to queue
        }
    }
    return std::list<Board<N>>();
}

std::list<Board<N>> Solver::makeHistory(SearchNode<N>* node){
    std::list<Board<N>> boards;
    boards.push_front({}); // push_front is used to add to dhe front O(1)
    // while(node != nullptr){
    //     boards.push_back(node->board);
    //     node = node->previous;
    // }
    std::reverse(boards.begin(), boards.end());
    return boards;
}