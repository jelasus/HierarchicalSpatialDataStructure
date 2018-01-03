#include"qNode.h"
#include<iostream>
template<class T>
class Quadtree{
  private:
    qNode<T>* root;
  public:
    Quadtree(Point a, Point b){
      root = new qNode<T>(a,b);
    }
    Quadtree(coordinates x, coordinates y){
      root = new qNode<T>(Point(0,y),Point(x,0));
    }
    bool find(Point);
    void insert(Point, T);
    bool isBoundary(Point);
    qNode<T>* getRoot();
};
template<class T>
qNode<T>* Quadtree<T>::getRoot() {return root;}
template<class T>
bool Quadtree<T>::isBoundary(Point A){
  if (this->root->pointA.x <= A.x && this->root->pointA.y >= A.y && this->root->pointB.x > A.x && this->root->pointB.y < A.y) return true;
  return false;
}
template<class T>
bool Quadtree<T>::find(Point A){
  qNode<T>* q = root;
  qNode<T>* p;
  coordinates ex, ey;
  while(q){
    p = q;
    ex = q->pointB.getXmid(q->pointA);
    ey = q->pointA.getYmid(q->pointB);
    std::cout << "A(x,y): " << q->pointA.x <<","<< q->pointA.y << '\n';
    std::cout << "B(x,y): " << q->pointB.x <<","<< q->pointB.y << '\n';
    if ((q->pointA.x == A.x) && (q->pointA.y == A.y) && (q->pointB.x - 1 == A.x) && (q->pointB.y + 1 == A.y)) {std::cout << *q->data << std::endl; return true;}
    else if (A.x < ex && A.y > ey) {q = q->NW;}
    else if (A.x >= ex && A.y > ey) {q = q->NE;}
    else if (A.x < ex && A.y <= ey) {std::cout << "SW" << '\n';q = q->SW;}
    else {std::cout << "SE" << '\n';q = q->SE;}
  }
  if((!(p->NW))  && (!(p->NE))  && (!(p->SW))  && (!(p->SE)) ) return true;
  return false;
}
template<class T>
void Quadtree<T>::insert(Point A, T d){
  if(!(isBoundary(A))) return;
  qNode<T>** q = &root;
  Point a = this->root->pointA;
  Point b = this->root->pointB;
  coordinates ex = (b.x - a.x)>>1, ey = (a.y - b.y)>>1;
  while(ex >= 1 && ey >= 1 || (!((*q)->data))){
    if (!(*q)){
      if (ex == 1 && ey ==1){
        *q = new qNode<T>(d,a,b);
        return;
      }
      else
        *q = new qNode<T>(a,b);
    }
    ex = (*q)->pointB.getXmid((*q)->pointA);
    ey = (*q)->pointA.getYmid((*q)->pointB);
    if (A.x < ex && A.y > ey) {b.x -= ex; b.y += ey; q = &((*q)->NW);}
    else if (A.x >= ex && A.y > ey) {a.x += ex; b.y += ey; q = &((*q)->NE);}
    else if (A.x < ex && A.y <= ey) { a.y -= ey; b.x -= ex; q = &((*q)->SW);}
    else {a.x += ex; a.y -= ey; q = &((*q)->SE);}
  }
}
