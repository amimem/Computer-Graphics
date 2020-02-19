//
//  Camera.h
//  Cube
//
//

#ifndef Camera_h
#define Camera_h

#define PIXEL_TOLERANCE      2
#include "Point3.hpp"
#include "Vector3.hpp"
#include <GLUT/GLUT.h>
#include <OpenGL/gl.h>

// Camera class
class Camera{
private:
    Point3 eye;
    Vector3 u, v, n;
    double viewAngle, aspect, nearDist, farDist; // view volume shape
    void setModelViewMatrix(); // send camera position to OpenGL
    
public:
    Camera(){};
    void set(Point3 eye, Point3 look, Vector3 up);
    void roll(float angle); // roll
    void pitch(float angle); // pitch
    void yaw(float angle); // yaw
    void slide(float delU, float delV, float delN); // slide
    //void setShape(float vAng, float asp, float nearD, float farD);
    void setShape(float left, float right , float bottom , float top , float nearD, float farD, int* viewport, int Xmouse, int Ymouse, int renderMode);
};

#endif /* Camera_h */
