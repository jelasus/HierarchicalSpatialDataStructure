#ifndef Octree_H
#define Octree_H
#include "OctreeNode.h"
typedef int pcd_size;
class Octree{
public:
  Point m_base; //punto base
  Point m_top; //punto alto
  Octree *m_hijos[8];
  Content *m_dato;
public:
  Octree(Point a): m_base(Point(0,0,0)), m_top(a), m_dato(0){
    for(int i = 0; i < 8; ++i)
			m_hijos[i] = 0;
	}
	Octree(Point a,Point b): m_base(a), m_top(b), m_dato(0){
    for(int i = 0; i < 8; ++i)
			m_hijos[i] = 0;
	}
  Octree(pcd_size x, pcd_size y, pcd_size z): m_base(Point(0,0,0)), m_top(Point(x,y,z)), m_dato(0){
    for(int i = 0; i < 8; ++i)
			m_hijos[i] = 0;
  }
  Octree(pcd_size x, pcd_size y, pcd_size z, char* file): m_base(Point(0,0,0)), m_top(Point(x,y,z)), m_dato(0){
    for(int i = 0; i < 8; ++i)
			m_hijos[i] = 0;
    build_image(file);
  }
	~Octree(){
		for(int i=0; i<8; ++i)
			delete m_hijos[i];
	}
  void build_image(char* textfile){}
  void insert(Point& pixel, Content& color, int& n_child){
    if (is_leaf()){ //si es un pixel
      if (m_dato == 0)
        set_content(color); //si no existe el punto, le asigna el color
      return; //no hace nada si ya existe el punto
    }
    else { //por lo tanto es un nodo interior
      n_child = get_posicion_child(pixel);
      if (this->m_hijos[n_child] == 0) // si el nodo no existe, lo crea
        this->m_hijos[n_child] = new Octree(pixel);
      this->m_hijos[n_child]->insert(pixel, color, n_child); // recursivamente hasta que encuentra el punto
    }
  }
  void search(Point pixel){

  }
private:
  enum child{
    BottomLeftFront = 0,
    TopLeftFront,
    BottomRightFront,
    TopRightFront,
    BottomLeftBack,
    TopLeftBack,
    BottomRightBack,
    TopRightBack,
  }
  bool is_leaf() {
    return m_base + 1 == m_top ? true : false;
  }
  void set_content(const Content& color) {m_dato = new Content(color);}
  int get_posicion_child(const Point& p) {
    
  }
};

#endif
