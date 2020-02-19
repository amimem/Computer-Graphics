//
//  Vector3.cpp
//  Cube
//
//

#include "Vector3.hpp"

void Vector3::set(float dx, float dy, float dz) { x = dx; y = dy; z = dz; }
void Vector3::set(Vector3& v) { x = v.x; y = v.y; z = v.z; }
void Vector3::flip() { x = -x; y = -y; z = -z; } // reverse the vector
void Vector3::setDiff(Point3& a, Point3& b) { // a - b
    x = a.x - b.x; y = a.y - b.y; z = a.z - b.z;
}

void Vector3::normalize() {  // make it a unit length vector
    double sizeSq = x * x + y * y + z * z;
    if (sizeSq < 0.0000001) {
        return; // nothing if zero
    }
    float scaleFactor = 1.0 / (float)sqrt(sizeSq);
    x *= scaleFactor; y *= scaleFactor; z *= scaleFactor;
}

Vector3::Vector3(float xx, float yy, float zz) { x = xx; y = yy; z = zz; }
Vector3::Vector3(Vector3& v) { x = v.x; y = v.y; z = v.z; }
Vector3::Vector3() { x = y = z = 0; } //default constructor
float Vector3::dot(Vector3 b) { // return this . b
    return x * b.x + y * b.y + z * b.z;
}
