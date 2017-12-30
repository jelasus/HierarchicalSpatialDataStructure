#ifndef Vector3_h_
#define Vector3_h_
#include <cmath>
#include<iostream>
typedef unsigned int coordinate;
class Point{
    public:
        coordinate x;
        coordinate y;
        coordinate z;
    public:
        Point(){};
        Point(const Point& o): x(o.x), y(o.y), z(o.z) {}
        Point(float x_, float y_, float z_): x(x_), y(y_), z(z_) {}
        Point operator+(const Point& r) const {return Point(x+r.x, y+r.y, z+r.z);}
        Point operator+(const int n) const {return Point(x+n,y+n,z+n);}
        Point operator-(const Point& r) const {return Point(x-r.x, y-r.y, z-r.z);}
        Point operator*(const Point& r) const {return Point(x*r.x, y*r.y, z*r.z);}
        Point operator/(const Point& r) const {return Point(x/r.x, y/r.y, z/r.z);}
        Point operator*(float r) const {return Point(x*r,y*r,z*r);}
        Point operator/(float r) const {return Point(x/r, y/r, z/r);}
        friend std::ostream& operator<<(std::ostream& stream, Point& o){
          stream << "x: " << o.x << " y: " << o.y << " z: " << o.z;
          return stream;
        }
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
        coordinate getXmid(const Point &o) {return (this->x + o.x)>>1;}
        coordinate getYmid(const Point &o) {return (this->y + o.y)>>1;}
        coordinate getZmid(const Point &o) {return (this->z + o.z)>>1;}
};
#endif
