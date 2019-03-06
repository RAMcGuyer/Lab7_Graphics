// Name: Ross McGuyer
// Quarter, Year: Winter, 2019
// Lab: 7
//
// This file is to be modified by the student.
// main.cpp
////////////////////////////////////////////////////////////
#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include <vector>
#include <cstdio>
#include <math.h>
#include "vec.h"
#include <iostream>

using namespace std;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

vector<vec2> cntrl_pts;

float factorial(int n){
    if(n >= 0){
      if(n > 1){
        return n * factorial(n-1);
      }
      else{
        return 1;
      }
    }
    
    return -1; //Indicates an error;	
}

float combination(int n, int k){
    if(n >= k && k>=0){
       return factorial(n) / (factorial(k) * factorial(n-k));
    }
    else{
       return -1; //Indicates an invalid combination
    }
}

float binomial(int n, int k, float t){
    float combo = combination(n, k);
    if(combo > 0){
        return combo * pow(t, k) * pow(1-t, n-k);
    }
    
    return -1; //Indicates that there was an error;  
}

void GL_render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();

    glBegin(GL_LINE_STRIP);
    glColor3f(1.0f,0.0f,0.0f);
    // just for example, remove if desired
    //glVertex2f(-.5f,-.5f);
    
    if(cntrl_pts.size() > 1){

	for(float t = 0.01f; t < 1.0f;t+=0.01f){
            	vec2 p;
		for(int i = 0; i < (int) cntrl_pts.size(); i++){
		    p += binomial(cntrl_pts.size()-1, i, t)*cntrl_pts.at(i);
		}
		glVertex2f(p[0], p[1]);
	}
    }
    glEnd();
    glFlush();
	
}
void GL_mouse(int button,int state,int x,int y)
{
    y=WINDOW_HEIGHT-y;
    GLdouble mv_mat[16];
    GLdouble proj_mat[16];
    GLint vp_mat[4];
    glGetDoublev(GL_MODELVIEW_MATRIX,mv_mat);
    glGetDoublev(GL_PROJECTION_MATRIX,proj_mat);
    glGetIntegerv(GL_VIEWPORT,vp_mat);

    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        double px,py,dummy_z; // we don't care about the z-value but need something to pass in
        gluUnProject(x,y,0,mv_mat,proj_mat,vp_mat,&px,&py,&dummy_z);
	cntrl_pts.push_back(vec2(px, py));
        glutPostRedisplay();
    }
}

//Initializes OpenGL attributes
void GLInit(int* argc, char** argv)
{
    glutInit(argc, argv);
    //glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    //glMatrixMode(GL_PROJECTION_MATRIX);
    //glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);
    glutCreateWindow("CS 130 - <Insert Name Here>");
    glutDisplayFunc(GL_render);
    glutMouseFunc(GL_mouse);
}

int main(int argc, char** argv)
{
    GLInit(&argc, argv);
    glutMainLoop();
    return 0;
}
