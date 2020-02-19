//
//  Point3.hpp
//  Cube
//
//

#ifndef Point3_hpp
#define Point3_hpp

#include <stdio.h>

class Point3 {
public:
    float x, y, z;
    void set(float dx, float dy, float dz);
    void set(Point3& p);
    Point3(float xx, float yy, float zz);
    Point3();
    void build4tuple(float v[]);
};

#endif /* Point3_hpp */
