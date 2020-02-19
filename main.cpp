//
//  main.cpp
//  Cube
//
//  Created by iPhone-Dev on 6/26/18.
//  Copyright © 2018 Amin Me'marian. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include "RGBpixmap.h"
#include <math.h>
#include <fstream>
#include <stddef.h>
#include <GLUT/GLUT.h>
#include <OpenGL/gl.h>
#include <string>
#include <limits.h>
#include "Camera.h"
#define PIXEL_TOLERANCE      2
#define PICK_BUFFER_SIZE    256

#define screenHeight    400
#define screenWidth     300

#define EASY_CUBE_LEVELS    3
#define HARD_CUBE_LEVELS    7

#define EASY_CLICKS_PER_CUBE    1
#define HARD_CLICKS_PER_CUBE    2

#define EASY_TOTAL_TIME     50
#define HARD_TOTAL_TIME     80

#define EASY_TIME_PER_CUBE    2
#define HARD_TIME_PER_CUBE    1

using namespace std;

enum MENU_TYPE
{
    EASY,
    HARD,
};


int calculateNumOfCubes ( int cubeLevel );

const int easyNumOfCubes = calculateNumOfCubes(EASY_CUBE_LEVELS);
const int hardNumOfCubes = calculateNumOfCubes(HARD_CUBE_LEVELS);


unsigned int pickBuffer[PICK_BUFFER_SIZE];

bool * easy_draw_decision = new bool[easyNumOfCubes];
bool * hard_draw_decision = new bool[hardNumOfCubes];

unsigned * easy_clicks_buffer = new unsigned[easyNumOfCubes];
unsigned * hard_clicks_buffer = new unsigned[hardNumOfCubes];

bool pauseFlag = false;
bool gameFinished = false;

int renderMode = GL_RENDER;
int numberOfHits = 0;

int Xmouse = 0;
int Ymouse = 0;
int viewport[4];

int score = 0;
int level = 0; // easy = 0 , hard = 1
int leftNumOfCubes = 0;
int secondsLeft = 0;

float XAngle = 0.0f;
float ZAngle = 0.0f;
bool XRotateFlag = false;
bool xRotateFlag = false;
bool ZRotateFlag = false;
bool zRotateFlag = false;


// positive pitch key pressed
bool prollflag = false;
// negative pitch key pressed
bool nrollflag = false;

// like above
bool pyawflag = false;
bool nyawflag = false;
bool ppitchflag = false;
bool npitchflag = false;


//right key pressed
bool rightflag = false;
bool leftflag = false;

//up flag
bool upflag = false;
bool downflag = false;

bool pZoomFlag = false;
bool nZoomFlag = false;
int zoomNum = 0;

// num of keys pressed
int rightnum = 0 , leftnum = 0 , upnum = 0 , downnum = 0 , rollnum = 0 , yawnum = 0 , pitchnum = 0;

// Pi number
const float Pi = 3.14159265358979323846264338327f;


void print(int x, int y,int z, string string)
{
    glRasterPos2f(x,y);
    int len = (int) string.length();
    
    for (int i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,string[i]);
    }
};

Camera cam;
// x , y , n for the camera
float xc = 1, yc = 0.5, nc = 1;

Point3 eye(xc, yc, nc);
Point3 look(0, 0, 0);
Vector3 up(0, 1, 0);

void resetCam() {
    xc = 1;
    yc = 0.5;
    nc = 1;
    Point3 eye(xc, yc, nc);
    Point3 look(0, 0, 0);
    Vector3 up(0, 1, 0);
}

void easyDrawCubes(){
    
    glPushMatrix();
    
    if ( XRotateFlag ) {
        glRotatef(XAngle, 1.0, 0.0, 0.0);
    }
    if ( xRotateFlag ) {
        glRotatef(XAngle, 1.0, 0.0, 0.0);
    }
    if ( ZRotateFlag ) {
        glRotatef(ZAngle, 0.0, 0.0, 1.0);
    }
    if ( zRotateFlag ) {
        glRotatef(ZAngle, 0.0, 0.0, 1.0);
    }
    
    glLoadName(1);
    glutSolidCube(1.0f);
    
    glPopMatrix();
    
    //    glDisable(GL_LIGHT0);
    //glClear(GL_DEPTH_BUFFER_BIT);
    
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat mat_amb[] = {0.24725f, 0.1995f, 0.0745f};
    GLfloat mat_diff[] = {0.75164f, 0.60648f, 0.22648f};
    GLfloat mat_spec[] = {0.628281f, 0.555802f, 0.366065f};
    GLfloat mat_phong[] = {51.2f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_phong);
    
    glShadeModel(GL_SMOOTH); // is it right to be here ?

    
    int num = 1;
    for ( int i = -1 ; i <= 1 ; i++ ) {
        for ( int j = -1 ; j <= 1 ; j++ ) {
            for (int k = -1 ; k <= 1 ; k++) {
                if ( !(i == 0 && j == 0 && k == 0) ) {
                    num++;
                    glPushMatrix();

                    if ( XRotateFlag ) {
                        glRotatef(XAngle, 1.0, 0.0, 0.0);
                    }
                    if ( xRotateFlag ) {
                        glRotatef(XAngle, 1.0, 0.0, 0.0);
                    }
                    if ( ZRotateFlag ) {
                        glRotatef(ZAngle, 0.0, 0.0, 1.0);
                    }
                    if ( zRotateFlag ) {
                        glRotatef(ZAngle, 0.0, 0.0, 1.0);
                    }
                    
                    glTranslatef(i, j, k);
                    
                    if ( easy_draw_decision[num-1] ){

                        glLoadName(num);
                        glutWireCube(1.0f);
                        glutSolidCube(1.0f);
                    }
                    
                    glPopMatrix();
                }
            }
        }
    }
}

void hardDrawCubes(){
    
    
    
    glPushMatrix();
    
    if ( XRotateFlag ) {
        glRotatef(XAngle, 1.0, 0.0, 0.0);
    }
    if ( xRotateFlag ) {
        glRotatef(XAngle, 1.0, 0.0, 0.0);
    }
    if ( ZRotateFlag ) {
        glRotatef(ZAngle, 0.0, 0.0, 1.0);
    }
    if ( zRotateFlag ) {
        glRotatef(ZAngle, 0.0, 0.0, 1.0);
    }
    
    glLoadName(1);
    glutSolidCube(1.0f);
    
    glPopMatrix();
    
    //    glDisable(GL_LIGHT0);
    //glClear(GL_DEPTH_BUFFER_BIT);
    
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH); // is it right to be here ?
    
    
    int num = 1;
    for ( int i = -3 ; i <= 3 ; i++ ) {
        for ( int j = -3 ; j <= 3 ; j++ ) {
            for (int k = -3 ; k <= 3 ; k++) {
                if ( !(i == 0 && j == 0 && k == 0) ) {
                    
                    if ( i == 3 || j == 3 || k == 3 || i == -3 || j == -3 || k == -3 ) {
                        glColor3d(1.0, 0.0, 0.0);
                        
                    } else if ( i == 2 || j == 2 || k == 2 || i == -2 || j == -2 || k == -2 ) {
                        glColor3d(0.0, 1.0, 0.0);
                    } else {
                        glColor3d(0.0, 0.0, 1.0);
                    }
                    
                    num++;
                    glPushMatrix();
                    
                    if ( XRotateFlag ) {
                        glRotatef(XAngle, 1.0, 0.0, 0.0);
                    }
                    if ( xRotateFlag ) {
                        glRotatef(XAngle, 1.0, 0.0, 0.0);
                    }
                    if ( ZRotateFlag ) {
                        glRotatef(ZAngle, 0.0, 0.0, 1.0);
                    }
                    if ( zRotateFlag ) {
                        glRotatef(ZAngle, 0.0, 0.0, 1.0);
                    }
                    
                    glTranslatef(i, j, k);
                    
                    if ( hard_draw_decision[num-1] ){
                        glLoadName(num);
                        glutWireCube(1.0f);
                        glutSolidCube(1.0f);
                    }
                    glPopMatrix();
                }
            }
        }
    }
    
    
    
    
}


void endScene() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, screenWidth, 0.0, screenHeight);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);
    glColor3f(1.0, 1.0, 1.0);
    if (leftNumOfCubes == 0) {
        print( screenWidth/2 - 30 , screenHeight/2 , 0 , "YOU WON!");
    } else {
        print( screenWidth/2 - 30 , screenHeight/2 , 0 , "YOU LOST!");
    }
    
    glFlush();
    glutSwapBuffers();
}

void pauseScene();

void drawScene() {

    
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, screenWidth, 0.0, screenHeight);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);
    glColor3f(1.0, 1.0, 1.0);
    
    if (level == 0) {
        if (renderMode == GL_RENDER) {
            print( 5 , screenHeight - 15 , 0, "Level : EASY");
        }
    } else if ( level == 1) {
        if (renderMode == GL_RENDER) {
            print( 5 , screenHeight - 15 , 0, "Level : HARD");
        }
    } else {
        exit(-3);
    }
    
    if (renderMode == GL_RENDER) {
        
        print( ((float) screenWidth) / 2 - 18 , screenHeight - 15 , 0, "Cubes : " + to_string(leftNumOfCubes));
        print( screenWidth - 50 , screenHeight - 15 , 0, "Time : " + to_string(secondsLeft));
    }

    
    if (level == 0 ) {
        cam.setShape(-3, 3, -4, 4, -10.0f, 10.0f, viewport, Xmouse, Ymouse, renderMode);
    } else if ( level == 1 ) {
        cam.setShape(-6, 6, -8, 8, -15.0f, 15.0f, viewport, Xmouse, Ymouse, renderMode);
    } else {
        exit(-3);
    }
    
    
    cam.set(eye, look, up);
    
    
    // if the specified keys are pressed , do the calculation and do the appropriate action
    if (prollflag) {
        cam.roll(rollnum*10);
    }
    if (nrollflag){
        cam.roll(rollnum*10);
    }
    if (ppitchflag){
        cam.pitch(pitchnum*10);
    }
    if (npitchflag){
        cam.pitch(pitchnum*10);
    }
    if (pyawflag){
        cam.yaw(yawnum*10);
    }
    if (nyawflag){
        cam.yaw(yawnum*10);
    }
    
    if (rightflag){
        cam.slide(rightnum,0.0,0.0);
    }
    if (leftflag){
        cam.slide(rightnum,0.0,0.0);
    }
    if (upflag){
        cam.slide(0.0,upnum,0.0);
    }
    if (downflag){
        cam.slide(0.0,upnum,0.0);
    }
    
    
    GLfloat position[] = {10.0f, 10.0f, 0.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    

    RGBpixmap p;
    p.readBMPFile("./red.bmp");
    p.setTexture(2018);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glBindTexture(GL_TEXTURE_2D, 2018);
    
    if (level == 0) {
        easyDrawCubes();
    } else if ( level == 1 ) {
        hardDrawCubes();
    } else {
        exit(-1);
    }

    
    if (gameFinished){
        glutDisplayFunc(endScene);
    }
    
    if (pauseFlag){
        glutDisplayFunc(pauseScene);
    }
    
    glFlush();
    
    if( renderMode == GL_RENDER ) {
        glutSwapBuffers();
    }
}

void pauseScene() {
    
    if (!pauseFlag) {
        glutDisplayFunc(drawScene);
    }
    
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, screenWidth, 0.0, screenHeight);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);
    glColor3f(1.0, 1.0, 1.0);
    print( screenWidth/2 - 30 , screenHeight/2 , 0 , "START/PAUSE");
    
    glFlush();
    glutSwapBuffers();
    
}

void pickCubes(int button, int state, int x, int y) {
    if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !pauseFlag ) {
        Xmouse = x;
        Ymouse = y;
        
        renderMode = GL_SELECT;
        glRenderMode( GL_SELECT );
        drawScene();
        renderMode = GL_RENDER;
        numberOfHits = glRenderMode( GL_RENDER );
        
        printf( "number of pick hits = %d\n", numberOfHits );
        
        int index = 0 , numberOfPickedItems , pickedItem;
        unsigned int zmin , zmax ;
        unsigned int minsel =  UINT_MAX ;
        int minin = -1;
        
        for( int i = 0 ; i < numberOfHits ; i++ )
        {
            numberOfPickedItems = pickBuffer[index];
            index++;
            
            zmin = pickBuffer[index];
            printf("zmin: %u\n",zmin);
            if (zmin < minsel) {
                minsel = zmin;
                minin = i;
                printf("minsel: %u ,minin: %u\n",minsel , minin);
            }
            index++;
            zmax = pickBuffer[index];
            printf("zmax: %u\n",zmax);
            index++;
            
            for( int j = 0; j < numberOfPickedItems; j++ )
            {
                pickedItem = pickBuffer[index];
                index++;
                printf( "%d : %d\n", j, pickedItem );
                
            }
        }
        
        index = 0;
        for( int i = 0 ; i < numberOfHits ; i++ )
        {
            numberOfPickedItems = pickBuffer[index];
            index++;
            zmin = pickBuffer[index];
            index++;
            zmax = pickBuffer[index];
            index++;
            if (i == minin) {
                printf("zmin: %u\n",zmin);
                printf("zmax: %u\n",zmax);
                for( int j = 0; j < numberOfPickedItems; j++ ) {
                    pickedItem = pickBuffer[index];
                    index++;
                    printf( "%d : %d\n", j, pickedItem );
                    
                    if (leftNumOfCubes == 1 && pickedItem == 1) {
                        leftNumOfCubes--;
                        gameFinished = true;
                    }
                    
                    if ( (pickedItem != 1) ) {
                        
                        printf("The first item is %i\n", pickedItem);
                        
                        if ( level == 0 ) {
                            
                            
                            easy_clicks_buffer[pickedItem-1] += 1;
                            
                            if ( easy_clicks_buffer[pickedItem-1] >= EASY_CLICKS_PER_CUBE ) {
                                easy_draw_decision[pickedItem-1] = false;
                                leftNumOfCubes--;
                            }
                            
                            
                        } else if ( level == 1 ) {
                            
                            
                            hard_clicks_buffer[pickedItem-1] += 1;
                            
                            if ( hard_clicks_buffer[pickedItem-1] >= HARD_CLICKS_PER_CUBE ) {
                                hard_draw_decision[pickedItem-1] = false;
                                leftNumOfCubes--;
                            }
                            
                            
                        } else {
                            exit(-3);
                        }
                        
                    }
                }
            } else {
                for( int j = 0; j < numberOfPickedItems; j++ ) {
                    index++;
                }
            }
            
        }
        
        
        glutPostRedisplay();
    }
    
}

void handleKeypress(unsigned char key , int x, int y) {
    
    switch (key) {
        case 'R' :
            prollflag = true; // if positive roll is pressed (R)
            nrollflag = false;
            rollnum++; // increase roll number
            glutPostRedisplay();
            break;
        case 'r':
            nrollflag = true; // like above
            prollflag = false;
            rollnum--; // decrease roll number
            glutPostRedisplay();
            break;
        case 'Y':
            pyawflag = true; // like above
            nyawflag = false;
            yawnum++; // increase yaw number
            glutPostRedisplay();
            break;
        case 'y':
            nyawflag = true; // like above
            pyawflag = false;
            yawnum--; // decrease yaw number
            glutPostRedisplay();
            break;
        case 'P':
            ppitchflag = true; // like above
            npitchflag = false;
            pitchnum++; // increase pitch number
            glutPostRedisplay();
            break;
        case 'p':
            npitchflag = true; // like above
            ppitchflag = false;
            pitchnum--; // decrease pitch number
            glutPostRedisplay();
            break;
        case 'X' :
            XRotateFlag = true;
            if (XAngle >= 360) {
                XAngle -= 360;
            }
            XAngle += 5.0f;
            xRotateFlag = false;
            glutPostRedisplay();
            break;
        case 'x' :
            xRotateFlag = true;
            if (XAngle <= -360) {
                XAngle += 360;
            }
            XAngle -= 5.0f;
            XRotateFlag = false;
            glutPostRedisplay();
            break;
        case 'Z' :
            ZRotateFlag = true;
            if (ZAngle >= 360) {
                ZAngle -= 360;
            }
            ZAngle += 5.0f;
            zRotateFlag = false;
            glutPostRedisplay();
            break;
        case 'z' :
            zRotateFlag = true;
            if (ZAngle <= -360) {
                ZAngle += 360;
            }
            ZAngle -= 5.0f;
            ZRotateFlag = false;
            glutPostRedisplay();
            break;
        case 27:
            exit(0);
            break;
        case 32:
            pauseFlag = !pauseFlag;
            break;
        default:
            break;
    }
    
}

void handleSpecialKeys(int key, int x, int y) {
    
    switch(key) {
        case GLUT_KEY_UP :
            upflag = true;
            upnum++;
            downflag = false;
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN :
            downflag = true;
            upnum--;
            upflag = false;
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT :
            rightflag = true;
            rightnum++;
            leftflag = false;
            glutPostRedisplay();
            break;
        case GLUT_KEY_LEFT :
            leftflag = true;
            rightnum--;
            rightflag = false;
            glutPostRedisplay();
            break;
        case GLUT_KEY_F1:
            XAngle = 0.0f;
            ZAngle = 0.0f;
            XRotateFlag = false;
            xRotateFlag = false;
            ZRotateFlag = false;
            zRotateFlag = false;
            
            
            // positive pitch key pressed
            prollflag = false;
            // negative pitch key pressed
            nrollflag = false;
            
            // like above
            pyawflag = false;
            nyawflag = false;
            ppitchflag = false;
            npitchflag = false;
            
            
            //right key pressed
            rightflag = false;
            leftflag = false;
            
            //up flag
            upflag = false;
            downflag = false;
            
            pZoomFlag = false;
            nZoomFlag = false;
            zoomNum = 0;
            
            // num of keys pressed
            rightnum = 0 ; leftnum = 0 ; upnum = 0 ; downnum = 0 ; rollnum = 0 ; yawnum = 0 ; pitchnum = 0;
            break;
    }
    
}

int calculateNumOfCubes ( int cubeLevel ) {
    int n = cubeLevel * cubeLevel * cubeLevel ;
    return n;
}

void handleResize(int w, int h) {
    if (gameFinished) { // edit
        glViewport(0, 0, w, h);
        glutPostRedisplay();
    } else {
        glViewport(0, 0, w, h);
        cam.setShape(-w, w, -h*((float)screenHeight/(float)screenWidth), h*((float)screenHeight/(float)screenWidth), -10.0f, 10.0f, viewport, Xmouse, Ymouse, renderMode);
        glutPostRedisplay();
    }
}

void update(int value) {
    
    
    
    
    if (secondsLeft == 0) {
        gameFinished = true;
    }
    
    glutPostRedisplay();
    
    if ( !gameFinished ) {
        
        if (pauseFlag) {
            glutTimerFunc(1000, update, 0);
        } else {
            secondsLeft--;
            glutTimerFunc(1000, update, 0);
        }
    }
}

void initTimer() {
    if ( level == 0 ) {
        secondsLeft = EASY_TOTAL_TIME;
    } else if ( level == 1 ) {
        secondsLeft = HARD_TOTAL_TIME;
    } else {
        exit(-3);
    }
}

void initScore() {
    
    if ( level == 0 ) {
        leftNumOfCubes = calculateNumOfCubes(EASY_CUBE_LEVELS);
    } else if ( level == 1 ) {
        leftNumOfCubes = calculateNumOfCubes(HARD_CUBE_LEVELS);
    } else {
        exit(-3);
    }
}

void initArrays() {
    
    for ( int i = 0 ; i < easyNumOfCubes ; i++ ) {
        easy_draw_decision[i] = true;
        easy_clicks_buffer[i] = 0;
    }
    
    for ( int i = 0 ; i < hardNumOfCubes ; i++ ) {
        hard_draw_decision[i] = true;
        hard_clicks_buffer[i] = 0;
    }
    
}

void menu(int item)
{
    switch (item)
    {
        case EASY:
            XAngle = 0.0f;
            ZAngle = 0.0f;
            XRotateFlag = false;
            xRotateFlag = false;
            ZRotateFlag = false;
            zRotateFlag = false;
            
            
            // positive pitch key pressed
            prollflag = false;
            // negative pitch key pressed
            nrollflag = false;
            
            // like above
            pyawflag = false;
            nyawflag = false;
            ppitchflag = false;
            npitchflag = false;
            
            
            //right key pressed
            rightflag = false;
            leftflag = false;
            
            //up flag
            upflag = false;
            downflag = false;
            
            pZoomFlag = false;
            nZoomFlag = false;
            zoomNum = 0;
            
            // num of keys pressed
            rightnum = 0 ; leftnum = 0 ; upnum = 0 ; downnum = 0 ; rollnum = 0 ; yawnum = 0 ; pitchnum = 0;
            
            glutDisplayFunc(drawScene);
            level = 0;
            if (gameFinished) {
                glutTimerFunc(1000, update, 0);
            }
            gameFinished = false;
            pauseFlag = false;
            initArrays();
            initTimer();
            initScore();
            
            break;
        case HARD:
            XAngle = 0.0f;
            ZAngle = 0.0f;
            XRotateFlag = false;
            xRotateFlag = false;
            ZRotateFlag = false;
            zRotateFlag = false;
            
            
            // positive pitch key pressed
            prollflag = false;
            // negative pitch key pressed
            nrollflag = false;
            
            // like above
            pyawflag = false;
            nyawflag = false;
            ppitchflag = false;
            npitchflag = false;
            
            
            //right key pressed
            rightflag = false;
            leftflag = false;
            
            //up flag
            upflag = false;
            downflag = false;
            
            pZoomFlag = false;
            nZoomFlag = false;
            zoomNum = 0;
            
            // num of keys pressed
            rightnum = 0 ; leftnum = 0 ; upnum = 0 ; downnum = 0 ; rollnum = 0 ; yawnum = 0 ; pitchnum = 0;
            glutDisplayFunc(drawScene);
            level = 1;
            if (gameFinished) {
                glutTimerFunc(1000, update, 0);
            }
            gameFinished = false;
            pauseFlag = false;
            initArrays();
            initTimer();
            initScore();
            break;
        default:
            break;
    }
    
    glutPostRedisplay();
    
    return;
}

void cleanup() {
    
    delete [] easy_draw_decision;
    delete [] hard_draw_decision;
    delete [] easy_clicks_buffer;
    delete [] hard_clicks_buffer;
}

int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(screenWidth , screenHeight);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH);
    glutCreateWindow("The Cube");
    glViewport(0,0,screenWidth,screenHeight);
    glEnable(GL_DEPTH_TEST);
    glSelectBuffer(PICK_BUFFER_SIZE, pickBuffer);
    initArrays();
    initTimer();
    initScore();
    glutDisplayFunc(drawScene);
    glutMouseFunc(pickCubes); // mouse rotation
    glutKeyboardFunc(handleKeypress);
    glutSpecialFunc(handleSpecialKeys);
    glutReshapeFunc(handleResize);
    glutTimerFunc(1000, update, 0);
    glutCreateMenu(menu);
    glutAddMenuEntry("EASY LEVEL", EASY);
    glutAddMenuEntry("HARD LEVEL", HARD);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
    atexit (cleanup);
    return 0;
}
