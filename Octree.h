#ifndef Octree_H
#define Octree_H
#include "OctreeNode.h"
#include<iostream>
#include<map>
#include<fstream>
#include<string>
#include <sstream>
typedef int pcd_size;
using namespace std;
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
  Octree(char* file): m_data(0){
    for(int i = 0; i < 8; ++i)
      m_child[i] = 0;
    read_off(file);
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
  typedef int key;
  void read_off(char* &off_file){
    ifstream file(off_file);
    string line;
    getline(file, line);
    line = line.substr(0,3);
    if(line != "OFF"){
      cout << "Error: File name is not .off extension" << endl;
      return;
    }
    map<key, Point*> l_vertex;
    int vertexs, faces;
    /////////////////////////
    getline(file,line);
    get_limits(vertexs, faces, line);
    //////////////////////////
    cout << vertexs << " " << faces << endl;
    coordinate vx, vy, vz;
    Point point1, point2;
    getline(file, line);
    get_vertex(vx, vy, vz, line);
    Point *f_point = new Point(vx,vy,vz);
    l_vertex.insert(std::pair<key,Point*>(0,f_point));
    cout << "Reading.. " << *(l_vertex[0]) << endl;
    point1 = point2 = Point(vx,vy,vz);
    for(int i = 1; i < vertexs; ++i){
      getline(file,line);
      get_vertex(vx, vy, vz, line);
      set_max(vx, vy, vz, point2);
      set_min(vx, vy, vz, point1);
      Point *p_vertex = new Point(vx, vy, vz);
      l_vertex.insert(std::pair<key,Point*>(i,p_vertex));
      cout << "Reading.. " << *(l_vertex[i]) << endl;
    }
    this->m_middle = (point1 + point2) * 0.5f;
    this->m_radixs = point2 - m_middle;
    cout << m_middle << " " << m_radixs << endl;
    cout << "inserting.. " << endl;
    for(map<key,Point*>::iterator it = l_vertex.begin(); it != l_vertex.end(); ++it){
      this->insert(*(it->second));
    }

  }
  void insert(const Point& pixel){
    cout << this->m_middle << " , " << this->m_radixs << " , " << pixel << endl;
    if (this->m_child[0] == NULL){ //si no tiene hijos, es una hoja
      if (this->m_data == NULL){
        this->m_data = const_cast<Point*>(&pixel);
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
  void set_max(const coordinate &vx, const coordinate &vy, const coordinate &vz, Point &max){
    if (vx > max.x) {max.x = vx;}
    if (vy > max.y) {max.y = vy;}
    if (vz > max.z) {max.z = vz;}
  }
  void set_min(const coordinate &vx, const coordinate &vy, const coordinate &vz, Point &min){
    if (vx < min.x) {min.x = vx;}
    if (vy < min.y) {min.y = vy;}
    if (vz < min.z) {min.z = vz;}
  }
  void get_vertex(coordinate &vx, coordinate &vy, coordinate &vz,const string &line){
    int limit1, limit2, limit3;
    limit1 = line.find(" ", 0);
    vx = stof(line.substr(0,limit1));
    limit2 = line.find(" ", limit1+1);
    vy = stof(line.substr(limit1+1,limit2- limit1 -1));
    limit3 = line.find(" ", limit2+1);
    vz = stof(line.substr(limit2+1,limit3- limit2 -limit1 -1));
  }
  void get_limits(int &vertexs, int &faces, string &line){
    int limit1, limit2;
    limit1 = line.find(" ", 0);
    vertexs = stoi(line.substr(0,limit1));
    limit2 = line.find(" ", limit1+1) - limit1 - 1;
    faces = stoi(line.substr(limit1+1,limit2));
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
