#include<iostream>

struct Father{
  int a;
  Father(){
    a = 0;
    std::cout<<"okay bro";
  }
};

struct ManyFathers{
  Father fathers[12];
  int ad;
  // ManyFathers(){
  //   ad=4;
  // };
};

int main(){
  ManyFathers fath {};
  std::cout<<"Hello world";
  std::aligned_storage_t<sizeof(ManyFathers), alignof(ManyFathers)> storage;
  // ManyFathers* fada = reinterpret_cast();
  return 0;
}