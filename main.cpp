#include "Octree.h"
using namespace std;

int main(){
  Point a(8,8,8);
  Octree *tree = new Octree(a);
  Content color(0,0,0);
  Point p(1,1,1);
  tree->insert(p,color);
  Point p2(2,1,1);
  tree->insert(p2,color);
  Point p3(1,2,1);
  tree->insert(p3,color);
  Point p4(3,2,1);
  tree->insert(p4,color);
  return 0;
}
