//
//  Point3.cpp
//  Cube
//
//

#include "Point3.hpp"

void Point3::set(float dx, float dy, float dz) { x = dx; y = dy; z = dz; }
void Point3::set(Point3& p) { x = p.x; y = p.y; z = p.z; }
Point3::Point3(float xx, float yy, float zz) { x = xx; y = yy; z = zz; }
Point3::Point3() { x = y = z = 0; }
void Point3::build4tuple(float v[])
{    // load 4-tuple with this color: v[3] = 1 for homogeneous
    v[0] = x; v[1] = y; v[2] = z; v[3] = 1.0f;
}

