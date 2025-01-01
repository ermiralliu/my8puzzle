#include <array>

namespace Models {

template <int N> // N is rowsize
struct BoardSave {
  using byte =  unsigned char;
  private:
      std::array<byte,N*N> tiles;
      size_t hash;

  public:
    BoardSave() = default;

    inline size_t getHash() const {
      return hash;
    }
    inline std::array<byte,N*N> getTiles const{
      return tiles;
    }
    inline operator==(BoardSave& bord){
      return tiles == bord.tiles;
    }

  // putting all the work on the compiler
};
//Here we don't even need to do the template struct declarations
}
