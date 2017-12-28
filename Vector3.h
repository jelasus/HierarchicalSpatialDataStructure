#ifndef Vector3_h_
#define Vector3_h_
#include <cmath>

class Point{
    public:
        float x;
        float y;
        float z;
    public:
        Point(){};
        Point(float x_, float y_, float z_): x(x_), y(y_), z(z_) {}
        Point operator+(const Point& r) const {return Point(x+r.x, y+r.y, z+r.z);}
        Point operator+(const int n) const {return Point(x+n,y+n,z+n);}
        Point operator-(const Point& r) const {return Point(x-r.x, y-r.y, z-r.z);}
        Point operator*(const Point& r) const {return Point(x*r.x, y*r.y, z*r.z);}
        Point operator/(const Point& r) const {return Point(x/r.x, y/r.y, z/r.z);}
        Point operator*(float r) const {return Point(x*r,y*r,z*r);}
        Point operator/(float r) const {return Point(x/r, y/r, z/r);}
        Point& operator+=(const Point& r) {
            x+=r.x;
            y+=r.y;
            z+=r.z;
            return *this;
        }
        Point& operator-=(const Point& r) {
            x-=r.x;
            y-=r.y;
            z-=r.z;
            return *this;
        }
        Point& operator*=(float r) {
            x*=r; y*=r; z*=r;
            return *this;
        }
        bool operator==(const Point& p){
          if (x == p.x && y == p.y && z == p.z) return true;
          return false;
        }
};
#endif
