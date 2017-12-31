#ifndef Octree_H
#define Octree_H
#include "OctreeNode.h"
#include<iostream>
typedef int pcd_size;
class Octree{
public:
  Point m_middle; //punto base
  Point m_radixs; //punto alto
  Octree *father; //puntero hacia el padre
  Octree *m_child[8];
  Point *m_data;
public:
	Octree(Point a,Point b): m_middle(a), m_radixs(b), m_data(0){
    for(int i = 0; i < 8; ++i)
			m_child[i] = 0;
	}
  Octree(pcd_size x, pcd_size y, pcd_size z):m_data(0){
    Point m(x*.5f,y*.5f,z*.5f);
    this->m_middle = m;
    this->m_radixs = m;
    for(int i = 0; i < 8; ++i)
			m_child[i] = 0;
  }
  Octree(char* file){
    build_image(file);
  }
	~Octree(){
		for(int i=0; i<8; ++i)
			delete m_child[i];
	}
  bool isempty(){
    if (this)
      return false;
    return true;
  }
  void build_image(char* textfile){}
  void insert(Point& pixel){
    std::cout << this->m_middle << " , " << this->m_radixs << " , " << pixel << std::endl;
    if (this->m_child[0] == NULL){ //si no tiene hijos, es una hoja
      if (this->m_data == NULL){
        this->m_data = &pixel;
        std::cout << "NODE CREATED" << std::endl;
        return;
      }
      else if(*this->m_data != pixel){ //si no es el mismo punto
        for(int i = 0; i < 8; ++i){
          Point p_new = this->m_middle;
          p_new.x += this->m_radixs.x * (i&1 ? 0.5f : -0.5f);
          p_new.y += this->m_radixs.y * (i&2 ? 0.5f : -0.5f);
          p_new.z += this->m_radixs.z * (i&4 ? 0.5f : -0.5f);
          this->m_child[i] = new Octree(p_new, this->m_radixs * 0.5f);
          this->m_child[i]->father = this;
        }
        Point old_pixel = *this->m_data;
        this->m_data = NULL;
        this->insert(old_pixel);
        this->insert(pixel);
      }
    }
    else
      this->m_child[get_posicion_child(pixel)]->insert(pixel);
  }
  void search(Point& pixel){
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
  void set_position(Point& p, Point& a, Point& b){

  }
  void set_content(const Point& color) {this->m_data = new Point(color);}
  int get_posicion_child(const Point& p) {
    int posicion = 0;
    if (p.x >= this->m_middle.x) posicion += 1;
    if (p.y >= this->m_middle.y) posicion += 2;
    if (p.z >= this->m_middle.z) posicion += 4;
    return posicion;
  }
};

#endif
