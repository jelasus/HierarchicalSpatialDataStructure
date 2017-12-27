#include"graphNodes.h"
#include<iostream>
main(){
  Vertex<int> a(2);
  Vertex<int> b(3);
  if (a>2)
    std::cout << "a es menor que b";
  return 0;
}
