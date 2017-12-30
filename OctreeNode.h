#ifndef OctreeNode_H
#define OctreeNode_H
#include "Vector3.h"


struct Content{
  int r;
  int g;
  int b;
  Content(): r(0), g(0), b(0) {}
  Content(int _r, int _g, int _b): r(_r), g(_g), b(_b) {}
};


#endif
