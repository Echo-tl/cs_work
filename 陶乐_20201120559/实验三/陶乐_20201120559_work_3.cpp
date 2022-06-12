#include<windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <graphics.h>
#include<math.h>

int max(int x1,int x2)
{
    if(x2>=x1){
        return x2;
    }
    else{
        return x1;
    }
}

int min(int x1,int x2)
{
    if(x2 <= x1){
        return x2;
    }
    else{
        return x1;
    }
}

void SetPixel(GLint x,GLint y)
{
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd( );
}

void lineBres(int x1,int y1,int x2,int y2)
{
    int x, y, dx, dy, p1, i;
    dx = x2-x1;
    dy = y2-y1;
    if(abs(dx > dy)){
        if(x1<x2){
            x = x1;
            y = y1;
        }
        else{
            x = x2;
            y = y2;
        }
        SetPixel(x, y);
        p1 =  2*abs(dy) - abs(dx);
        for (i = min(x1, x2); i < max(x1, x2); i++){
            x = x + 1;
            if(p1 >= 0){
                if(dx*dy >= 0){
                    y = y+1;
                }
                else{
                    y = y-1;
                }
                p1 = p1 + 2*(abs(dy) - abs(dx));
            }
            else{
                y = y;
                p1 = p1 + 2*abs(dy);
            }
            SetPixel(x, y);
        }
    }
    else{
        if(y1<y2){
            x = x1;
            y = y1;
        }
        else{
            x= x2;
            y = y2;
        }
        SetPixel(x, y);

		p1 = 2*abs(dx) - abs(dy);
		for (i = min(y1, y2); i < max(y1, y2); i++){
            y = y + 1;
            if(p1 >= 0){
                if(dx*dy >=0){
                    x = x+1;
                }
                else{
                    x = x-1;
                }
                p1 = p1 + 2*(abs(dy) - abs(dx));
            }
            else{
                x = x;
                p1 = p1 + 2*abs(dx);
            }
             SetPixel(x, y);
		}
    }
}
void My_Display(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, 500, 500);

    lineBres(0,0,400,200);
    lineBres(0,0,200,300);
    glFlush( );
}

int main(int argc,char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RED);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Bream_line");

    glutDisplayFunc(My_Display);
    glColor3f(0.0, 1.0, 1.0);
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
    glutMainLoop();
    return 0;
}