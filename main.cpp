#include "Octree.h"
#include <iostream>
using namespace std;

int main(){
    vector3 A(1,2,3);
    vector3 B(2,3,4);
    vector3 C;
    C=A+B;
    cout<<C.x<<C.y<<C.z<<endl;
    OctreeNode Nodo;
    OctreeNode Nodoo(C);
    Octree O(A,B);
    return 0;
}
