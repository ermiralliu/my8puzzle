#ifndef BOARD_H
#define BOARD_H
#include <cstdlib>
#include <string.h>
#include "../Helpers/MergeSort.hpp"
#include "Board.hpp"
#include <algorithm>

namespace Models{

template <uint N>  bool Board<N>::isGoal() const {
  return tiles == Board<N>::FINAL;
};

template <uint N>  
structures::neighbors<N> Board<N>::neighbors(){
  structures::empty_indexes sides {};
  int empty_row = emptyIndex / N;
  int empty_column = emptyIndex % N;
  if (empty_column > 0)  // left
    sides.push(emptyIndex - 1);
  if (empty_column < N - 1) // right
    sides.push(emptyIndex + 1);
  if (empty_row > 0) // up
    sides.push(emptyIndex - N);
  if (empty_row < N - 1) // down
    sides.push(emptyIndex + N);
  // loop
  structures::neighbors<N> neighbors {};
  for(const auto& newEmpty : sides) {
    neighbors.push(makeNeighbor(newEmpty));
  }
  return neighbors;
};



template <uint N>
bool Board<N>::isSolvable() const{
  if constexpr (Board<N>::SIZE % 2 == 0){
    return isSolvableEven();
  } else {
    return isSolvableOdd();
  }
}

template <uint N>
std::string Board<N>::toString(std::array<byte, SIZE > tiles){
  std::string str; //preallocating all the space needed;
  str.reserve(N + SIZE + 4);
  str.append(std::to_string(N) + "\n");

  int count = 0;
  for (uint i = 0; i < N; i++){
    for (uint j = 0; j < N; j++){
      str.append(std::to_string(tiles[count++]));
    }
    str.append("\n");
  }
  return str;
}

template <uint N>
Board<N> Board<N>::makeNeighbor(int newEmpty) const { //returns a new board after the swap
  std::array<byte,SIZE> next_tiles = tiles;
  
  int manhattan_first = oneManhattan(next_tiles, newEmpty);
  next_tiles[emptyIndex] = next_tiles[newEmpty];  // futim nr e ri ne pozicionin bosh
  next_tiles[newEmpty] = 0; // levizim pozicionin bosh
  int manhattan_second = oneManhattan(next_tiles, emptyIndex); // manhattan tani qe kemi bere swap-in
  int manhattan_difference = manhattan_second - manhattan_first;  // O(1) per manhattan_difference

  return Board{
    next_tiles, // O(n) per shallow copy
    manhattanDistance + manhattan_difference,
    newEmpty
  };
}

template <uint N>
Board<N> Board<N>::make_init_board(std::array<byte, Board<N>::SIZE> tiles){ // O(n^2)
  uint size = SIZE;
  int manhattan_sum = 0;
  // int hamming_sum = 0;
  int row = -1;
  int column = -1;
  for (uint i = 0; i < size; i++){
    for (uint j = 0; j < size; j++){
      int current = static_cast<int>(tiles[ind++]);
      if (current == 0){
        row = i;
        column = j;
        continue;
      }
      int index = current - 1;
      int needed_row = index / size;
      int needed_column = index % size;
      int current_sum = std::abs(needed_row - i) + std::abs(needed_column - j);
      manhattan_sum += current_sum;
    }
  }
  return Board{tiles, manhattan_sum, static_cast<int>(row * N + column)};
};

template <uint N>
int Board<N>::oneManhattan(std::array<byte, Board<N>::SIZE> tiles, uint newIndex){ // O(1), kursejme shume kohe per femijet
  int i = newIndex / N;
  int j = newIndex % N;
  uint current = tiles[i];
  uint index = current - 1;
  int needed_row = index / N;
  int needed_column = index % N;
  int distance = std::abs(needed_row - i) + std::abs(needed_column - j);
  return distance;
}

template <uint N>
bool Board<N>::isSolvableOdd() const { // nese nr i inversions eshte odd, nuk ka zgjidhje
  auto invCount = findInversions();
  if (invCount % 2 == 0)
  {
    return true;  // sipas kushtit qe permendem ne fillim
  }
  return false;
}

template <uint N>
bool Board<N>::isSolvableEven() const { // zgjidhet vetem nese nr i inversioneve, plus rreshti i 0-s jane odd
  auto invCount = findInversions();
  uint empty_row = emptyIndex / Board<N>::SIZE;
  if ((invCount + empty_row) % 2 == 1){
    return true;
  }
  return false;
}

template <uint N>
int Board<N>::findInversions() const{ //this only gets called once, so it shouldn't be a memory bottleneck
//or
  int flattenedArray[Board<N>::SIZE-1]; // nuk e perfshijme 0-n
  { //inicializojme flattened array
    int index = 0;
    for(const auto& element : tiles){
      if (element == 0)
        continue;
      flattenedArray[index++] = element;
    }
  }
  int aux[Board<N>::SIZE-1];
  std::copy(flattenedArray, std::end(flattenedArray), std::begin(aux));
  int invCount = MergeSort::mergesort(flattenedArray, aux, 0, SIZE - 2); // duhet ta studioj kete
  return invCount;
}
// we have manhattan here, but let's just implement the comparison in the searchNode;
};
#endif