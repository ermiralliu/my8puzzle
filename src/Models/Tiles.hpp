#ifndef TILES_HPP
#define TILES_HPP

#include <iostream>
#include <cstdint> // For uint64_t
#include <cstring> // For memcpy
#include <array>

// also it's unsiged
// then again, it makes sense in context

// might remove the bound checking later, since they're already checked on Board functions
// and inline the get and set along with that
// -> removing the bound checking now, since if std::array doesn't do it, why would i on my own version
namespace Models {
using byte = unsigned char;

template <uint N>
struct Tiles {
private:
  std::array<byte, N* N> pattern;
public:
  constexpr Tiles(std::array<byte, N* N> initialValue) : pattern{ initialValue } {}

  static Tiles makeNext(Tiles initial, byte emptyIndex, byte newEmpty);

  inline std::array<byte, N* N> getValue() const {
    return pattern;
  }
  inline byte get(int index) {
    return pattern[index];
  }
  inline void set(int index, byte nibbleValue) {
    pattern[index] = nibbleValue;
  }

  inline bool operator==(Tiles other) const {
    return this->pattern == other.pattern;
  }

  inline bool operator!=(Tiles other) const {
    return this->pattern != other.pattern;
  }

  inline bool equals(Tiles other) const {
    return this->pattern == other.pattern;
  }

};

// specialization for boards with ROW_SIZE = 4;
// this was initially 
template<> struct Tiles<4> {
private:
  std::array<byte,8> pattern;

public:
  Tiles() = default;

  constexpr Tiles(std::array<byte,8> initialValue) : pattern{ initialValue } {} // I didn't know c++ had default values
  // I really made a constexpr constructor
  // crazy
  Tiles(std::array<byte, 16> initialTiles) {
    Tiles patt{};
    for (int i = 0; i< 16;i++)
      patt.set(i, initialTiles[i]);
  }

  static Tiles makeNext(Tiles initial, byte emptyIndex, byte newEmpty) {
    Tiles next{ initial };
    next.set(emptyIndex, initial.get(newEmpty));
    next.set(newEmpty, 0);
    return next;
  };

  inline std::array<byte,8> getValue() const {
    return pattern;
  }
  // private:

  inline void set(int index, byte nibbleValue) {
    size_t byteIndex = index / 2;
    size_t nibbleInByte = index % 2;
    uint8_t mask = 0x0F << (nibbleInByte * 4);
    pattern[byteIndex] = (pattern[byteIndex] & ~mask) | (nibbleValue << (nibbleInByte * 4));
  }

  inline byte get(int index) const {
    size_t byteIndex = index / 2;
    size_t nibbleInByte = index % 2;
    return (pattern[byteIndex] >> (nibbleInByte * 4)) & 0x0F;
  }

  inline bool operator==(Tiles other) const {
    return this->pattern == other.pattern;
  }

  inline bool operator!=(Tiles other) const {
    return this->pattern != other.pattern;
  }

  inline bool equals(Tiles other) const {
    return this->pattern == other.pattern;
  }

  uint64_t toLong(){  // this will be how this particular Tile pattern in save in the database
    uint64_t result;
    std::memcpy(&result, pattern.data(), sizeof(result));
    return result;
  } 

};
// hbl.setNibble(0, 0xA); // Set the least significant nibble to 10 (0xA)
}
#endif