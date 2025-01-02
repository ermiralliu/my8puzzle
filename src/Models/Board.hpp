#include <functional> // For hash
#include <string> // std::string
#include <array>
#include "Board_head.hpp"

#include "../structures/PreAllocatedStack.hpp"

// compiled using wall
// it's all

namespace Models{
  using byte = unsigned char;
  using std::size_t;

template <uint N>
using Neighbors = structures::prealloc_stack<4, BoardDtos<N>>;

template <uint N> struct BoardDtos{
  Board<N> board;
  bool nextBox;
};

template <size_t SIZE> constexpr
std::array<byte, SIZE> generate_final_array(){
  std::array<byte,SIZE> initializer;
  for(size_t i=1; i<SIZE; i++){
    initializer[i-1] = static_cast<byte>(i);
  }
  initializer[SIZE-1] = 0;
  return initializer;
};

template <uint N> class Board{ 
  private:
    static constexpr std::hash<std::string> hasher {};
    // static constexpr uint N_uns = static_cast<uint> N;
  public:
    static constexpr uint SIZE = N*N;
    static constexpr std::array<byte,SIZE> FINAL = generate_final_array<SIZE>();
  
  private:  
    std::array<byte, SIZE> tiles;
    uint emptyIndex;
    size_t hash;	//caching the hashCode, so we don't recompute the string each time

  public:
    inline int getEmptyIndex() const{
      return emptyIndex;
    }
    inline size_t getHash() const{
      return hash;
    }
    inline std::array<byte, SIZE> getTiles() const{
      return tiles;
    }
  
  Board() = default;  // this should never be actually used by anyone, but i need it for copy and move semantics
  // just to be able to allocate space without playing games and whatnot

  Board(std::array<byte, SIZE> tiles, uint emptyIndex) :
    tiles{ tiles },
    emptyIndex{ emptyIndex },
    hash{ hasher(std::string(tiles.begin(), tiles.end())) }
  { }
  
  static Board<N> make_init_board(std::array<byte, SIZE> tiles); // O(SIZE) //Only used once
  
  inline std::string toString() const {
    return toString(tiles);
  }

  bool isGoal() const;

  static std::string toString(std::array<byte, SIZE> tiles);

  Neighbors<N> neighbors();
  
  BoardDtos<N> makeNeighbor(uint newEmpty) const;
  
  static int oneManhattan(std::array<byte, SIZE> tiles, uint newIndex);

  bool isSolvable() const;
  bool isSolvableOdd() const;
  bool isSolvableEven() const;

  int findInversions() const;

  inline bool operator==(const Board& other) const {
    return this->equals(other);
  }

  inline bool operator!=(const Board& other) const {
    return ! (this->equals(other));
  }
  inline bool equals(const Board& other) const {
    if (hash != other.hash) // hoping for an early return
      return false;
    return this->tiles ==  other.tiles;
  }
  // we have manhattan here, but let's just implement the comparison in the searchNode;
};

// template class Board<2>;
// template class Board<3>;  
// leaving only 3 so we don't generate duplicate compiling problems for now
template class Board<4>;
// template class Board<10>;


}