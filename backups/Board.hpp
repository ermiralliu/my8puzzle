#include <cstddef>
#include <cstring> // For memcpy
#include <functional> // For hash
#include <string> // std::string
#include <vector>
#include <array>
#include <cstdlib>  // std::abs
#include "../Helpers/MergeSort.hpp"

namespace Models{
  using std::byte;

enum class Box{
  CURRENT_BOX,
  NEXT_BOX
};

template <size_t N> struct Board{ 
  private:
    static constexpr std::hash<std::string> hasher {};
  public:
    static constexpr size_t SIZE = N*N;

    static constexpr std::array<byte, SIZE> FINAL = [](){
      std::array<byte,SIZE> initializer;
      for(int i=1; i<SIZE; i++){
        initializer[i-1] = i;
      }
      initializer[SIZE-1] = 0;
      return initializer;
    }();
    
    std::array<byte, SIZE> tiles; // extra careful not to touch this //I couldn't make it const, cause reasons
    const int manhattanDistance;
    const int emptyIndex;
    const int hash;	//caching the hashCode, so we don't recompute the string each time
  
  Board(byte[] tiles, int manhattanDistance, int emptyIndex) :
    manhattanDistance{manhattanDistance}, 
    emptyIndex{emptyIndex},
    hash{hasher(std::string(tiles.begin(), tiles.end()))} 
  {
    std::memcpy(this->tiles, tiles, sizeof(this->tiles));
  }
  
  Board(byte[] tiles, int[] init) : 
    manhattanDistance{ init[0]}, 
    emptyIndex{init[1]}, 
    hash{ hasher(std::string(tiles.begin(), tiles.end())) }  
  {
    std::memcpy(this->tiles, tiles, sizeof(this->tiles));
  }
  
  Board(byte[] tiles) : Board(tiles, init(tiles)){ }  // this is the first one

  static std::array<int,3> init(std::array<byte, SIZE> tiles); // O(SIZE)
  
  inline std::string toString() {
    return toString(tiles);
  }

  bool isGoal();

  static std::string toString(std::array<byte, SIZE> tiles);

  // private:
 
  std::vector<Board> neighbors();
  Board makeNeighbor(int newEmpty);
  static int oneManhattan(std::array<byte, SIZE> tiles, int newIndex);

  bool isSolvable();
  bool isSolvableOdd();
  bool isSolvableEven();

  int findInversions();

  static bool operator<(Board one, Board two){
    return one.ManhattanDistance - two.ManhattanDistance < 0;
  }

  inline bool operator==(const BoardSave& other) const {
    if (hash != y.hash) // hoping for an early return
      return false;
    return this->tiles ==  o.tiles;
  }

  inline bool operator!=(const BoardSave& other) const {
    return ! (this == other);
  }
  // we have manhattan here, but let's just implement the comparison in the searchNode;
};

// template class Board<2>;
template class Board<3>;  // so we don't generate duplicate compiling problems for now
// template class Board<4>;
// template class Board<10>;

}


