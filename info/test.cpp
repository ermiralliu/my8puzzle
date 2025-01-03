#include <tuple>
#include <iostream>

std::tuple<int, int> bah(){
  std::cout<<"Get it right";
  return std::make_tuple(1243,4142);
}

struct Mother{
  int a;
  int b;
  
  Mother():
    a{std::get<0>(bah())},
    b{std::get<1>(bah())} 
  { }
};



int main(){
  // auto baba = std::make_tuple(123,1231);
  Mother mama {};
  std::cout<< mama.a << " " << mama.b;
  return 0;
}