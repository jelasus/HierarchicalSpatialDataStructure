#include "visualizate.h"
using namespace std;

int main(int argc, char** argv){
  Octree *tree = new Octree();
  read_off_file("/home/jesus/HierarchicalSpatialDataStructure/x29_plane.off", tree);
  cout << "end";
  /*Octree a(4,4,4);
  pcl::PointXYZ b(0,0,0);
  pcl::PointXYZ c(4,0,0);
  pcl::PointXYZ d(0,4,0);
  pcl::PointXYZ e(4,4,0);
  pcl::PointXYZ f(0,0,4);
  pcl::PointXYZ g(4,0,4);
  pcl::PointXYZ h(0,4,4);
  pcl::PointXYZ i(4,4,4);
  a.insert(b);
  a.insert(c);
  a.insert(d);
  a.insert(e);
  a.insert(f);
  a.insert(g);
  a.insert(h);
  a.insert(i);*/
  return 0;
}
