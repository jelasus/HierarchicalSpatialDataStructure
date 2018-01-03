#ifndef Octree_H
#define Octree_H
#include"Vector3.h"
#include<iostream>
#include<map>
#include<fstream>
#include<string>
#include<vector>
#include<pcl/io/pcd_io.h>
#include<pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include<pcl/PCLPointCloud2.h>
typedef float pcd_size;
typedef int key;
typedef pcl::PointXYZ Data;
using namespace std;
class Octree{
public:
  Point m_middle; //punto base
  Point m_radixs; //punto alto
  Octree *father; //puntero hacia el padre
  Octree *m_child[8];
  Data *m_data;
public:
	Octree(Point a,Point b): m_middle(a), m_radixs(b), m_data(0), father(0){
    for(int i = 0; i < 8; ++i)
			this->m_child[i] = 0;
	}
  Octree(pcd_size x, pcd_size y, pcd_size z):m_data(0), father(0){
    Point m(x*.5f,y*.5f,z*.5f);
    this->m_middle = m;
    this->m_radixs = m;
    for(int i = 0; i < 8; ++i)
			this->m_child[i] = 0;
  }
  Octree(): m_data(0), father(0){
    for(int i = 0; i < 8; ++i)
      this->m_child[i] = 0;
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
  void insert(Data& pixel){
    cout << this->m_middle << " , " << this->m_radixs << " , " << pixel << endl;

    if (this->m_child[0] == NULL){ //si no tiene hijos, es una hoja
      
      if (this->m_data == NULL){
        this->m_data = &pixel;
        std::cout << "NODE CREATED" << std::endl;
        return;
      }

      else if(pixel.x == this->m_data->x && pixel.y == this->m_data->y && pixel.z == this->m_data->z){ //si es el mismo punto
        cout << "The point is already here" << endl;
        return;
      }
      
      else{
        for(int i = 0; i < 8; ++i){
          Point p_new = this->m_middle;
          p_new.x += this->m_radixs.x * (i&1 ? 0.5f : -0.5f);
          p_new.y += this->m_radixs.y * (i&2 ? 0.5f : -0.5f);
          p_new.z += this->m_radixs.z * (i&4 ? 0.5f : -0.5f);
          this->m_child[i] = new Octree(p_new, this->m_radixs * 0.5f);
          this->m_child[i]->father = this;
        }
        Data old_pixel = *this->m_data;
        this->m_data = NULL;
        this->insert(old_pixel);
        this->insert(pixel);
      }
    }
    else
      this->m_child[get_posicion_child(pixel)]->insert(pixel);
  }

  void search(Data pixel){
	  if (this->m_child[0] == NULL){
		  if (this->m_data != NULL){
			  if (pixel.x == this->m_data->x && pixel.y == this->m_data->y && pixel.z == this->m_data->z){
				  cout << "Encontrado" << endl;
				  cout << *m_data << endl;
			  }
		  }
	  }
	  else{
		  this->m_child[get_posicion_child(pixel)]->search(pixel);
	  }
  }

  void RadiusNeighbors(Point center, float radius, vector<Data*> &Points){
    Point p_min = center - radius;
    Point p_max = center + radius;
    if(m_child[0]==NULL){
      if(m_data!=NULL){
            Data *p = this->m_data;
            if(p->x > p_max.x || p->y > p_max.y || p->z > p_max.z) return;
            if(p->x < p_min.x || p->y < p_min.y || p->z < p_min.z) return;
			Points.push_back(this->m_data);
      }
    }
    else{
      for(int i=0;i<8;i++){
        Point p_max_ = m_child[i]->m_middle + m_child[i]->m_radixs;
        Point p_min_ = m_child[i]->m_middle - m_child[i]->m_radixs;

        if(p_max_.x < p_min.x || p_max_.y < p_min.y || p_max_.z < p_min.z) continue;
        if(p_min_.x > p_max.x || p_min_.y > p_max.y || p_min_.z > p_max.z) continue;

		m_child[i]->RadiusNeighbors(center, radius, Points);
      }
    }
  
  }



public:
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
    vx = std::stof(line.substr(0,limit1));
    limit2 = line.find(" ", limit1+1);
    vy = std::stof(line.substr(limit1+1,limit2- limit1 -1));
    limit3 = line.find(" ", limit2+1);
    vz = std::stof(line.substr(limit2+1,limit3- limit2 -limit1 -1));
  }
  void get_polygons(pcl::Vertices &v, std::string &line){
    int vertices, limit2, limit1;
    limit1 = line.find(" ", 0);
    vertices = std::stoi(line.substr(0,limit1));
    for(;vertices > 0; --vertices){
      limit2 = limit1 + 1;
      limit1 = line.find(" ", limit2);
      int pos = std::stoi(line.substr(limit2,limit2-limit1));
      v.vertices.push_back(pos);
    }
  }
  void get_limits(int &vertexs, int &faces, string &line){
    int limit1, limit2;
    limit1 = line.find(" ", 0);
    vertexs = std::stoi(line.substr(0,limit1));
    limit2 = line.find(" ", limit1+1) - limit1 - 1;
    faces = std::stoi(line.substr(limit1+1,limit2));
  }
  //void set_content(const Data& color) {this->m_data = new Data(color);}
  int get_posicion_child(const Data& p) {
    int posicion = 0;
    if (p.x >= this->m_middle.x) posicion += 1;
    if (p.y >= this->m_middle.y) posicion += 2;
    if (p.z >= this->m_middle.z) posicion += 4;
    return posicion;
  }
};

#endif
