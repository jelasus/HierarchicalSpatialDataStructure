#ifndef OctreeNode_H
#define OctreeNode_H
#include "Vector3.h"

class OctreeNode{
    public:
        vector3 posicion;
    public:
        OctreeNode(){};
        OctreeNode(const vector3& posicion) : posicion(posicion) { }

        vector3 getPosicion() { return posicion; }
        void setPosicion(vector3& p) { posicion = p; }
};

#endif
