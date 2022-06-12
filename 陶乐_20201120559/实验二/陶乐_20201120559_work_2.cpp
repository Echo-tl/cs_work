#include<windows.h>
#include<stdlib.h>
#include<math.h>
#include<Gl/glu.h>
#include<Gl/glut.h>
#include<iostream>
using namespace std;

inline int round(const float a)
{
    return int(a+0.5);
}

void SetPixel(GLint x,GLint y)
{
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd( );
}

void LineDDA(int x0,int y0,int xEnd,int yEnd)
{
    int dx = xEnd - x0, dy = yEnd - 0, steps,k;
    float xIncrement, yIncrement,x = x0, y = y0;

    if(fabs(dx)>fabs(dy))
        steps = fabs(dx); //斜率K<1
    else
        steps = fabs(dy); //斜率K>1

    xIncrement = float(dx)/float(steps);   //计算增量
    yIncrement = float(dy)/float(steps);

    SetPixel(round(x),round(y));
    for(k=0; k<steps; k++){
        x += xIncrement;
        y += yIncrement;
        SetPixel(round(x),round(y));
    }
}

void myDisplay(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, 500, 500);

    GLint x1,y1,x2,y2;
    LineDDA(0,0,500,600);
    glFlush( );
}

int main(int argc,char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RED);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("DDA_line");

    glutDisplayFunc(myDisplay);
    glColor3f(0.0, 1.0, 1.0);
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
    glutMainLoop();
    return 0;
}