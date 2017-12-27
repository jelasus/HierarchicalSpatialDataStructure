#ifndef Vector3_h_
#define Vector3_h_
#include <cmath>

class vector3{
    public:
        float x;
        float y;
        float z;
    public:
        vector3(){};
        vector3(float x_, float y_, float z_){
            x=x_;
            y=y_;
            z=z_;
        }

        vector3 operator+(const vector3& r) const {
            return vector3(x+r.x, y+r.y, z+r.z);
        }

        vector3 operator-(const vector3& r) const {
            return vector3(x-r.x, y-r.y, z-r.z);
        }

        vector3 mul(const vector3& r) const {
            return vector3(x*r.x, y*r.y, z*r.z);
        }

        vector3 div(const vector3& r) const {
            return vector3(x/r.x, y/r.y, z/r.z);
        }

        vector3 operator*(float r) const {
            return vector3(x*r,y*r,z*r);
        }


        vector3 operator/(float r) const {
            return vector3(x/r, y/r, z/r);
        }

        vector3& operator+=(const vector3& r) {
            x+=r.x;
            y+=r.y;
            z+=r.z;
            return *this;
        }

        vector3& operator-=(const vector3& r) {
            x-=r.x;
            y-=r.y;
            z-=r.z;
            return *this;
        }

        vector3& operator*=(float r) {
            x*=r; y*=r; z*=r;
            return *this;
        }
};


#endif
