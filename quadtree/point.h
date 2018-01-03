typedef unsigned int coordinates;
class Point{
  public:
    coordinates x;
    coordinates y;
    Point(): x(0), y(0) {}
    Point(coordinates _x, coordinates _y): x(_x), y(_y) {}
    void setPoint(coordinates a, coordinates b);
    coordinates getX();
    coordinates getY();
    coordinates getXmid(Point);
    coordinates getYmid(Point);
};
coordinates Point::getXmid(Point b){
  coordinates X = x + b.x;
  return X>>1;
}
coordinates Point::getYmid(Point b){
  coordinates Y = y + b.y;
  return Y>>1;
}
void Point::setPoint(coordinates a, coordinates b){
  x = a;
  y = b;
}
coordinates Point::getX() {return x;}
coordinates Point::getY() {return y;}
