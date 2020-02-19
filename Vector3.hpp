//
//  Vector3.hpp
//  Cube
//
//

#ifndef Vector3_hpp
#define Vector3_hpp

#include <stdio.h>
#include <math.h>
#include "Point3.hpp"

class Vector3 {
public:
    float x, y, z;
    void set(float dx, float dy, float dz);
    void set(Vector3& v);
    void flip();
    void setDiff(Point3& a, Point3& b);
    
    void normalize();
    
    Vector3(float xx, float yy, float zz);
    Vector3(Vector3& v);
    Vector3();
    Vector3 cross(Vector3 b) { //return this x b
        Vector3 c(y*b.z - z*b.y, z*b.x - x*b.z, x*b.y - y*b.x);
        return c;
    }
    float dot(Vector3 b);
};

#endif /* Vector3_hpp */
