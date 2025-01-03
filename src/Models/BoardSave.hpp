#include <cstdlib>
#include <array>

namespace Models {

template <std::size_t N> // N is rowsize
struct BoardSave {
  using byte =  unsigned char;
  private:
      std::array<byte,N*N> tiles;
      std::size_t hash;

  public:
    BoardSave() = default;
    
    BoardSave(std::array<byte,N*N> tiles, std::size_t hash) :
      tiles{tiles},
      hash{hash}
    { }

    inline std::size_t getHash() const {
      return hash;
    }

    inline std::array<byte,N*N> getTiles() const{
      return tiles;
    }

    inline bool operator==(BoardSave& bord){
      return tiles == bord.tiles;
    }

  // putting all the work on the compiler
};
//Here we don't even need to do the template struct declarations
}
