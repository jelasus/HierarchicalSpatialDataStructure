#include"quadtree.h"
main(){
  Quadtree<int>* Quad = new Quadtree<int>(8,8);
  //Quad->insert(Point(0,1),3);
  //Quad->insert(Point(0,2),2);
  Quad->insert(Point(1,1),4);
  Quad->find(Point(1,1));
  //Quad->find(Point(0,1));
  //Quad->find(Point(0,2));
  return 0;
}
