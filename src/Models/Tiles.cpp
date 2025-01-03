#include "Tiles.hpp"

namespace Models{


template <uint N>
Tiles<N> Tiles<N>::makeNext(Tiles<N> initial, byte emptyIndex, byte newEmpty){
  Tiles next{initial};
  next.pattern[emptyIndex] = next.pattern[newEmpty];  // futim nr e ri ne pozicionin bosh
  next.pattern[newEmpty] = 0; // levizim pozicionin bosh
  return next;
}


}