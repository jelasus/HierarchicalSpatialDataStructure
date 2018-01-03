<<<<<<< HEAD
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(main)

find_package(PCL 1.2 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
add_compile_options(-std=c++11)
add_executable (main main.cpp)
target_link_libraries (main ${PCL_LIBRARIES})

=======
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(cloud_viewer)

find_package(PCL 1.2 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable (cloud_viewer main.cpp)
target_link_libraries (cloud_viewer ${PCL_LIBRARIES})
>>>>>>> f9304f53d0b1e17b89c7d1951d1a78bee734399e
