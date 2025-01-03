#ifndef BOARD_H
#define BOARD_H
#include <cstdlib>
#include <string.h>
#include "../Helpers/MergeSort.hpp"
#include "Board.hpp"
#include <algorithm>
#include <iostream>

// actually managed to compile this successfully using -Wall

namespace Models{

template <uint N>
void print_array(const std::array<byte, N*N>& arr) {
  std::cout << "[";
  for (uint i = 0; i < arr.size(); ++i) {
    std::cout << static_cast<int>(arr[i]); // Print as int (decimal)
    if (i < arr.size() - 1) {
      std::cout << ", ";
    }
  }
  std::cout << "]" << std::endl; // Output: [72, 101, 108, 108, 111]
}

template <uint N>  
Neighbors<N> Board<N>::neighbors(){
  structures::empty_indexes sides {};
  uint empty_row = emptyIndex / N;
  uint empty_column = emptyIndex % N;
  if (empty_column > 0)  // left
    sides.push(emptyIndex - 1);
  if (empty_column < N - 1) // right
    sides.push(emptyIndex + 1);
  if (empty_row > 0) // up
    sides.push(emptyIndex - N);
  if (empty_row < N - 1) // down
    sides.push(emptyIndex + N);
  // loop
  Neighbors<N> neighbors {};
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
std::string Board<N>::toString(Tiles<N> tiles){
  std::string str; //preallocating all the space needed;
  str.reserve(N + SIZE*2 + 4);
  str.append(std::to_string(N) + "\n");

  int count = 0;
  for (uint i = 0; i < N; i++){
    for (uint j = 0; j < N; j++){
      str.append(std::to_string(tiles.get(count++)));
    }
    str.append("\n");
  }
  return str;
}

template <uint N>
BoardDtos<N> Board<N>::makeNeighbor(uint newEmpty) const { //returns a new board + a bool which is true if it needs
// to go to the next box
  
  int manhattan_first = oneManhattan(tiles, newEmpty);

  Tiles<N> next_tiles = Tiles<N>::makeNext(tiles, emptyIndex, newEmpty);
  
  int manhattan_second = oneManhattan(next_tiles, emptyIndex); // manhattan tani qe kemi bere swap-in
  bool next_box = manhattan_second - manhattan_first > 0;
  
  std::array<byte, N*N> toPrint;
  for(uint i=0; i<toPrint.size(); i++){
    toPrint[i] = tiles.get(i);
  }
  print_array<N>(toPrint);

  for(uint i=0; i<toPrint.size(); i++){
    toPrint[i] = next_tiles.get(i);
  }
  print_array<N>(toPrint);
  
  return { 
    Board {
      next_tiles,
      newEmpty
    }, 
    next_box
  };
}

template <uint N>
Board<N> Board<N>::make_init_board(std::array<byte, Board<N>::SIZE> tiles){ // O(n^2)
  uint emptyIndex;
  for(uint i=0; i< Board<N>::SIZE; ++i)
    if(tiles[i] == 0)
      emptyIndex = i;
  std::cout<< emptyIndex<<"\n";
  return Board{ Tiles<N>{tiles}, emptyIndex};
};

template <uint N>
int Board<N>::oneManhattan(Tiles<N> tiles, uint newIndex){ // O(1), kursejme shume kohe per femijet
  int i = newIndex / N;
  int j = newIndex % N;
  uint current = tiles.get(newIndex);
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
  uint empty_row = emptyIndex / N;
  if ((invCount + empty_row) % 2 == 1){
    return true;
  }
  return false;
}

template <uint N>
int Board<N>::findInversions() const{ //this only gets called once, so it shouldn't be a memory bottleneck
//or
  std::array<int, Board::SIZE-1> flattenedArray; // nuk e perfshijme 0-n
  { //inicializojme flattened array
    int index = 0;
    for(uint i=0; i< SIZE; i++){
      byte element = tiles.get(i);
      if(element == 0)
        continue;
      flattenedArray[index++] = element;  
    }
  }
  std::array<int, Board::SIZE-1> aux = flattenedArray;

  int invCount = MergeSort::mergesort(flattenedArray.data(), aux.data(), 0, SIZE - 2); // duhet ta studioj kete
  return invCount;
}
// we have manhattan here, but let's just implement the comparison in the searchNode;
};
#endif