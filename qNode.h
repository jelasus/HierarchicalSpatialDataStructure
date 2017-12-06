#include"point.h"
template<class T>
class qNode{
  public:
    qNode<T>* NW;
    qNode<T>* NE;
    qNode<T>* SW;
    qNode<T>* SE;
    T* data;
    Point pointA;
    Point pointB;
    // PointA in this case is the leftmost upper point in that rectangule
    // PointB in this case thus is the rightmost most down point in that rectangule
    qNode(Point a, Point b): data(0), pointA(a), pointB(b) {}
    qNode(T d, Point a, Point b): data(new T(d)), pointA(a), pointB(b) {}
    void setData(T d) {data = new T(d);}
};
