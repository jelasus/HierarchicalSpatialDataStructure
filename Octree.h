#ifndef Octree_H
#define Octree_H
#include "OctreeNode.h"

class Octree{
    public:
        vector3 m_origen; //centro del nodo
        vector3 m_dimensiones; // ancho alto y profundidad
        Octree *m_hijos[8];
        OctreeNode *m_dato;
    public:
		Octree(vector3 origen_,vector3 dimensiones_){
            m_origen=origen_;
            m_dimensiones=dimensiones_;
            m_dato=0;
            for(int i=0; i<8; ++i)
					m_hijos[i] = 0;
		}
		~Octree() {
			for(int i=0; i<8; ++i)
				delete m_hijos[i];
		}
};

#endif
