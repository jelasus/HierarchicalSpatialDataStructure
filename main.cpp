#include "visualizate.h"
using namespace std;

int main(int argc, char** argv){
<<<<<<< HEAD
  VisualPointCloud cloudtree("/home/jesus/HierarchicalSpatialDataStructure/off_files/klingon.off");
  cout << "end";
  /*Octree a(4,4,4);
=======
 /* Octree *tree = new Octree();
  read_off_file("pear.off", tree);
  cout << "end";*/	
  Octree a(4,4,4);
>>>>>>> f9304f53d0b1e17b89c7d1951d1a78bee734399e
  pcl::PointXYZ b(0,0,0);
  pcl::PointXYZ c(4,0,0);
  pcl::PointXYZ d(0,4,0);
  pcl::PointXYZ e(4,4,0);
  pcl::PointXYZ f(0,0,4);
  pcl::PointXYZ g(4,0,4);
  pcl::PointXYZ h(0,4,4);
  pcl::PointXYZ i(4,4,4);
<<<<<<< HEAD
=======
  pcl::PointXYZ k(4,4,4);
  pcl::PointXYZ l(1.3,2.3, 3.3);
>>>>>>> f9304f53d0b1e17b89c7d1951d1a78bee734399e
  a.insert(b);
  a.insert(c);
  a.insert(d);
  a.insert(e);
  a.insert(f);
  a.insert(g);
  a.insert(h);
<<<<<<< HEAD
  a.insert(i);*/
  return 0;
=======
  a.insert(i);
  a.insert(l);
  //a.insert(k);
  Point center(3, 3,3);
  vector<pcl::PointXYZ*> Points;
  cout << endl;

  a.RadiusNeighbors(center, 3, Points);
  
  cout << "Puntos encontrados : " << endl;

  for (int i = 0; i < Points.size(); i++){
	  cout << *Points[i] << endl;
  }

  return 0;

>>>>>>> f9304f53d0b1e17b89c7d1951d1a78bee734399e
}
