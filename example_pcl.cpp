#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>



int main(int argc, char const *argv[]) {
  pcl::PointCloud<pcl::PointXYZ> cloud;
  /*cloud.width    = 5;
  cloud.height   = 1;
  cloud.is_dense = false;
  cloud.points.resize (cloud.width * cloud.height);

  for (size_t i = 0; i < cloud.points.size (); ++i)
  {
    cloud.points[i].x = 1024 * rand () / (RAND_MAX + 1.0f);
    cloud.points[i].y = 1024 * rand () / (RAND_MAX + 1.0f);
    cloud.points[i].z = 1024 * rand () / (RAND_MAX + 1.0f);
  }*/ //resize and assign new points
  //save on disk pcl::io::savePCDFileASCII ("test_pcd.pcd", cloud);
  
  return 0;
}
