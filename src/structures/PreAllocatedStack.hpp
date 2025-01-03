#ifndef PRE_STACK_HPP
#define PRE_STACK_HPP

#include <cstddef>
#include "../Models/Board_head.hpp"
#include <utility>

namespace structures{
using std::size_t;

template <size_t SIZE, class T>
struct prealloc_stack{ // The idea is that we know the limit, so we don't do checks about bounds and all that
  T array[SIZE];
  T* end_ptr;

  prealloc_stack(){
    end_ptr = array;
  }

  inline void push(T data){ // we have to be very careful here, cause it might lead to a overflow( but it wont)
    *(end_ptr) = data;
    ++end_ptr;
  }
  inline T* begin() { 
    return array; 
  }
  inline T* end() { 
    return end_ptr; 
  }
};

using empty_indexes = prealloc_stack<4,int>;

template <size_t N>
using neighbors = prealloc_stack<4, Models::Board<N>>;

}

#endif