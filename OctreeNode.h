#ifndef OctreeNode_H
#define OctreeNode_H
#include "Vector3.h"


struct Pixel{
  int r;
  int g;
  int b;
  Pixel(): r(0), g(0), b(0) {}
  Pixel(int _r, int _g, int _b): r(_r), g(_g), b(_b) {}
};

class Content{
    public:
        Pixel pixel;
    public:
        Content(){};
        Content(const Pixel& p) : pixel(p) { }
        Content(const Content& c): pixel(c.pixel) {}
        Pixel getPosicion() { return pixel; }
        void setPosicion(Pixel& p) { pixel = p; }
};

#endif
