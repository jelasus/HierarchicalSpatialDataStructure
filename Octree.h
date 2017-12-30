#ifndef Octree_H
#define Octree_H
#include "OctreeNode.h"
#include<iostream>
typedef int pcd_size;
class Octree{
public:
  Point m_base; //punto base
  Point m_top; //punto alto
  Octree *father; //puntero hacia el padre
  Octree *m_child[8];
  Content *m_data;
public:
  Octree(Point a): m_base(Point(0,0,0)), m_top(a), m_data(0){
    for(int i = 0; i < 8; ++i)
			m_child[i] = 0;
	}
	Octree(Point a,Point b): m_base(a), m_top(b), m_data(0){
    for(int i = 0; i < 8; ++i)
			m_child[i] = 0;
	}
  Octree(pcd_size x, pcd_size y, pcd_size z): m_base(Point(0,0,0)), m_top(Point(x,y,z)), m_data(0){
    for(int i = 0; i < 8; ++i)
			m_child[i] = 0;
  }
  Octree(pcd_size x, pcd_size y, pcd_size z, char* file): m_base(Point(0,0,0)), m_top(Point(x,y,z)), m_data(0){
    for(int i = 0; i < 8; ++i)
			m_child[i] = 0;
    build_image(file);
  }
	~Octree(){
		for(int i=0; i<8; ++i)
			delete m_child[i];
	}
/*  bool isempty(){
    if (this)
      return true;
    return false;
  }*/
  void build_image(char* textfile){}
  void insert(Point& pixel, Content& color){
    std::cout << this->m_base << " , " << this->m_top << std::endl;
    if (is_leaf()){ //si es un pixel
      if (this->m_data == 0)
        set_content(color); //si no existe el punto, le asigna el color
      return; //no hace nada si ya existe el punto
    }
    else { //por lo tanto es un nodo interior
      int posicion = get_posicion_child(pixel);
      if(!(this->m_child[posicion])){
        std::cout << "NEW NODE CREATED" << std::endl;
        Point new_base;
        Point new_top;
        set_position(pixel,new_base,new_top);
        this->m_child[posicion] = new Octree(new_base, new_top);
      }
      this->m_child[posicion]->insert(pixel,color); // recursivamente hasta que encuentra el punto
    }
  }
  void search(Point pixel){

  }
private:
  /*enum child{
    BottomLeftFront = 0,
    TopLeftFront,
    BottomRightFront,
    TopRightFront,
    BottomLeftBack,
    TopLeftBack,
    BottomRightBack,
    TopRightBack
  };*/
  bool is_leaf() {
    return (m_base + 1 == m_top) ? true : false;
  }
  void set_position(Point& p, Point& a, Point& b){
    coordinate midX = this->m_base.getXmid(this->m_top);
    coordinate midY = this->m_base.getYmid(this->m_top);
    coordinate midZ = this->m_base.getZmid(this->m_top);
    a = this->m_base;
    b = Point(midX, midY, midZ);
    if (p.x > midX){a.x = midX; b.x = this->m_top.x;}
    if (p.y > midY){a.y = midY; b.y = this->m_top.y;}
    if (p.z > midZ){a.z = midZ; b.z = this->m_top.z;}
  }
  void set_content(const Content& color) {this->m_data = new Content(color);}
  int get_posicion_child(const Point& p) {
    int posicion = 0;
    if(this->m_base.getXmid(this->m_top) < p.x) posicion |= 1;
    if(this->m_base.getYmid(this->m_top) < p.y) posicion |= 2;
    if(this->m_base.getZmid(this->m_top) < p.z) posicion |= 4;
    return posicion;
  }
};

#endif
