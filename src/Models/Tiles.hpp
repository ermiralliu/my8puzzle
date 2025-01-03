#ifndef TILES_HPP
#define TILES_HPP

#include <iostream>
#include <cstdint> // For uint64_t
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
template<> struct Tiles<4> {
private:
  uint64_t pattern;

public:
  Tiles() = default;

  constexpr Tiles(uint64_t initialValue) : pattern{ initialValue } {} // I didn't know c++ had default values
  // I really made a constexpr constructor
  // crazy
  Tiles(std::array<byte, 16> initialTiles) {
    Tiles patt{};
    for (int i = 0;i < 16;i++)
      patt.set(i, initialTiles[i]);
  }

  static Tiles makeNext(Tiles initial, byte emptyIndex, byte newEmpty) {
    Tiles next{ initial };
    next.set(emptyIndex, initial.get(newEmpty));
    next.set(newEmpty, 0);
    return next;
  };

  inline uint64_t getValue() const {
    return pattern;
  }

  // private:

  inline void set(int index, byte nibbleValue) {
    uint64_t mask = 0xFLL << (index * 4); // Create a mask for the nibble
    pattern = (pattern & ~mask) | (static_cast<uint64_t>(nibbleValue) << (index * 4));
  }

  inline byte get(int index) const {
    return static_cast<unsigned char>((pattern >> (index * 4)) & 0xF);
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
// hbl.setNibble(0, 0xA); // Set the least significant nibble to 10 (0xA)
}
#endif