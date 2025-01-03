#ifndef BOARD_HPP
#define BOARD_HPP
#include <string> // std::string
#include <array>
#include <iostream>
#include "Board_head.hpp"
#include "Tiles.hpp"
#include "../structures/PreAllocatedStack.hpp"

// compiled using wall
// it's all



namespace Models{
  using byte = unsigned char;
  using std::size_t;


template <std::size_t N>
void print_array(const std::array<byte, N*N>& arr) {
  std::cout << "[";
  for (std::size_t i = 0; i < arr.size(); ++i) {
    std::cout << static_cast<int>(arr[i]); // Print as int (decimal)
    if (i < arr.size() - 1) {
      std::cout << ", ";
    }
  }
  std::cout << "]" << std::endl; // Output: [72, 101, 108, 108, 111]
}

template <size_t N> struct BoardDtos{
  Board<N> board;
  bool isNextBox;
};

template <size_t N>
using Neighbors = structures::prealloc_stack<4, BoardDtos<N>>;

template <size_t N> constexpr
Tiles<N> generate_final_array(){
  size_t SIZE = N*N;
  std::array<byte,N*N> initializer;
  for(size_t i=1; i<SIZE; i++){
    initializer[i-1] = static_cast<byte>(i);
  }
  initializer[SIZE-1] = 0;
  return Tiles<N>{initializer};
};

template <size_t N> class Board{ 
  // private:
  //   static constexpr std::hash<std::string> hasher {};
    // static constexpr size_t N_uns = static_cast<size_t> N;
  public:
    static constexpr size_t SIZE = N*N;
    static constexpr Tiles<N> FINAL = generate_final_array<N>();
  
  private:  
    Tiles<N> tiles;
    std::uint32_t emptyIndex;

  public:
    inline int getEmptyIndex() const{
      return emptyIndex;
    }

    inline Tiles<N> getTiles() const{
      return tiles;
    }
  
  Board() = default;  // this should never be actually used by anyone, but i need it for copy and move semantics
  // just to be able to allocate space without playing games and whatnot

  Board(Tiles<N> tiles, std::uint32_t emptyIndex) :
    tiles{ tiles },
    emptyIndex{ emptyIndex }
  { }
  
  static Board<N> make_init_board(std::array<byte, SIZE> tiles); // O(SIZE) //Only used once
  
  inline std::string toString() const {
    return toString(tiles);
  }
  
  // inline size_t getHash() const{
  //   return hasher(std::string{this->tiles.begin(), this->tiles.end()});
  // }

  inline bool isGoal() const{
    return tiles == Board<N>::FINAL;
  }

  static std::string toString(const Tiles<N>& tiles);

  Neighbors<N> neighbors();
  
  BoardDtos<N> makeNeighbor(std::uint32_t newEmpty) const;
  
  static int oneManhattan(const Tiles<N>& tiles, std::uint32_t newIndex);

  bool isSolvable() const;
  bool isSolvableOdd() const;
  bool isSolvableEven() const;

  int findInversions() const;

  inline bool operator==(const Board& other) const {
    return this->tiles ==  other.tiles;
  }

  inline bool operator!=(const Board& other) const {
    return this->tiles !=  other.tiles;
  }

  inline bool equals(const Board& other) const {
    return this->tiles ==  other.tiles;
  }
  // we have manhattan here, but let's just implement the comparison in the searchNode;
};
}

#include "Board.tpp"

#endif