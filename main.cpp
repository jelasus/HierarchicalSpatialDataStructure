#include "Octree.h"
using namespace std;

int main(){
  Octree a(8,8,8);
  Point b(1,1,1);
  Point c(4,7,1);
  Point d(2,2,1);
  a.insert(b);
  a.insert(c);
  a.insert(d);
  cout << "end";
  return 0;
}
