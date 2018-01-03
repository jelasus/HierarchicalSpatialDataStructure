#include"Octree.h"
<<<<<<< HEAD
#include <pcl/visualization/cloud_viewer.h>
#include<pcl/PCLPointCloud2.h>
using namespace std;
class VisualPointCloud{
  private:
    Octree* container;
    pcl::PointCloud<pcl::PointXYZ> cloud;
    vector<pcl::Vertices> polys;
  public:
    VisualPointCloud(char* file): container(new Octree()){read_off_file(file);}
    VisualPointCloud(Octree* &p_octree): container(p_octree) {}
    void visualizate_cloud_points(pcl::PointCloud<pcl::PointXYZ> &v){

    }
    void visualizate_off_file(){
      pcl::PolygonMesh mesh;
      mesh.polygons = this->polys;
      pcl::PCLPointCloud2::Ptr cloud_blob(new pcl::PCLPointCloud2);
      pcl::toPCLPointCloud2(this->cloud, *cloud_blob);
      mesh.cloud = *cloud_blob;
      boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
      viewer->setBackgroundColor (0, 0, 0);
      viewer->addPolygonMesh(mesh,"meshes",0);
      viewer->addCoordinateSystem (1.0);
      viewer->initCameraParameters ();
      while (!viewer->wasStopped ()){
        viewer->spinOnce (100);
        boost::this_thread::sleep (boost::posix_time::microseconds (100000));
      }
    }
  private:
    void read_off_file(char* off_file){
      std::ifstream file(off_file);
      std::string line;
      std::getline(file, line);
      line = line.substr(0,3);
      if(line != "OFF"){
        cout << "Error: File name is not .off extension" << endl;
        return;
      }
      int vertexs, faces;
      /////////////////////////
      getline(file,line);
      container->get_limits(vertexs, faces, line);
      //////////////////////////
      cout << vertexs << " " << faces << endl;
      coordinate vx, vy, vz;
      Point point1, point2;
      getline(file, line);
      container->get_vertex(vx, vy, vz, line);
      Data *f_point = new Data(vx,vy,vz);
      this->cloud.push_back(*f_point);
      cout << "Reading.. " << *f_point << endl;
      point1 = point2 = Point(vx,vy,vz);
      for(int i = 1; i < vertexs; ++i){
        getline(file,line);
        container->get_vertex(vx, vy, vz, line);
        container->set_max(vx, vy, vz, point2);
        container->set_min(vx, vy, vz, point1);
        Data *p_vertex = new Data(vx, vy, vz);
        this->cloud.push_back(*p_vertex);
        cout << "Reading.. " << this->cloud[i] << endl;
      }
      container->m_middle = (point1 + point2) * 0.5f;
      container->m_radixs = point2 - container->m_middle;
      cout << container->m_middle << " " << container->m_radixs << endl;
      cout << "inserting.. " << endl;
      for(int i = 0;i < vertexs; ++i){
        container->insert(this->cloud.points[i]);
      }
      for(int i = 0; i < faces; ++i){
        pcl::Vertices v;
        getline(file,line);
        container->get_polygons(v, line);
        this->polys.push_back(v);
      }
    }
  private:

};
=======
using namespace std;
void read_off_file(char* off_file, Octree* &ktree){
  std::ifstream file(off_file);
  std::string line;
  std::getline(file, line);
  cout << "line" << endl;
  line = line.substr(0,3);
  /*if(line != "OFF"){
    cout << "Error: File name is not .off extension" << endl;
    return;
  }*/
  pcl::PointCloud<pcl::PointXYZ> cloud;
  int vertexs, faces;
  /////////////////////////
  getline(file,line);
  ktree->get_limits(vertexs, faces, line);
  //////////////////////////
  cout << vertexs << " " << faces << endl;
  coordinate vx, vy, vz;
  Point point1, point2;
  getline(file, line);
  ktree->get_vertex(vx, vy, vz, line);
  Data *f_point = new Data(vx,vy,vz);
  cloud.push_back(*f_point);
  cout << "Reading.. " << *f_point << endl;
  point1 = point2 = Point(vx,vy,vz);
  for(int i = 1; i < vertexs; ++i){
    getline(file,line);
    ktree->get_vertex(vx, vy, vz, line);
    ktree->set_max(vx, vy, vz, point2);
    ktree->set_min(vx, vy, vz, point1);
    Data *p_vertex = new Data(vx, vy, vz);
    cloud.push_back(*p_vertex);
    cout << "Reading.. " << cloud[i] << endl;
  }
  ktree->m_middle = (point1 + point2) * 0.5f;
  ktree->m_radixs = point2 - ktree->m_middle;
  cout << ktree->m_middle << " " << ktree->m_radixs << endl;
  cout << "inserting.. " << endl;
  for(int i = 0;i < vertexs; ++i){
    ktree->insert(cloud.points[i]);
  }
  vector<pcl::Vertices> polys;
  for(int i = 0; i < faces; ++i){
    pcl::Vertices v;
    getline(file,line);
    ktree->get_polygons(v, line);
    polys.push_back(v);
  }

  pcl::PolygonMesh mesh;
  mesh.polygons = polys;
  pcl::PCLPointCloud2::Ptr cloud_blob(new pcl::PCLPointCloud2);
  pcl::toPCLPointCloud2(cloud, *cloud_blob);
  mesh.cloud = *cloud_blob;
  boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
  viewer->setBackgroundColor (0, 0, 0);
  viewer->addPolygonMesh(mesh,"meshes",0);
  viewer->addCoordinateSystem (1.0);
  viewer->initCameraParameters ();
  while (!viewer->wasStopped ()){
    viewer->spinOnce (100);
    boost::this_thread::sleep (boost::posix_time::microseconds (100000));
  }
}
>>>>>>> f9304f53d0b1e17b89c7d1951d1a78bee734399e
