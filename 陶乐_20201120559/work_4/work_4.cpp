#include<windows.h>
#include<gl/glut.h>
#include<gl/glu.h>
#include<gl/gl.h>
#include<iostream>
#include<cmath>

//画点
void setPixel(int x,int y)
{
    glColor3f(0.0,0.0,1.0);
    glPointSize(2.0f);
    glBegin(GL_POINTS);
        glVertex2f(x,y);
    glEnd();
    glFlush();
}

//x0,y0是圆心坐标
void CirclePlot(int x0,int y0,int x,int y)
{
   //1
    setPixel((x0+x),(y0+y));//y = x 的下方
    setPixel((x0+y),(y0+x)); //y = x 的上方

    //2
    setPixel((x0+x),(y0-y));
    setPixel((x0+y),(y0-x));

    //3
    setPixel((x0-x),(y0-y));
    setPixel((x0-y),(y0-x));

    //4
    setPixel((x0-x),(y0+y));
    setPixel((x0-y),(y0+x));

}

//中点画圆算法
void Midpoint_circle(int x0,int y0,int r)
{
    int x = 0;
    int y = r;
    int d = 1-r; //d初值
    CirclePlot(x0,y0,x,y);

    while(x<y){
        if(d<=0){
            d += 2*x +3;  //y值不变
        }
        else{
            d += 2*(x-y)+5;
            y--; // y = y-1
        }
        x++;
        CirclePlot(x0,y0,x,y); //画下一个点
    }
}

void changeSize(GLsizei w, GLsizei h)
{
    if (h == 0){
            h = 1;
    }
    glViewport(0, 0, w, h);

    // 重置坐标系统
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // 建立修剪空间的范围
    if (w <= h)
        glOrtho(0.0f, 250.0f, 0.0f, 250.0f*h/w, 1.0, -1.0);
    else
        glOrtho(0.0f, 250.0f*w/h, 0.0f, 250.0f, 1.0, -1.0);

}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    int x0 = 100, y0 = 100, r = 80;
    Midpoint_circle(x0,y0,r);
}

int main(int argc,char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200,200);
    glutInitWindowSize(400,400);
    glutCreateWindow("midCircle");
    glutDisplayFunc(display);
    glutReshapeFunc(changeSize);

    glutMainLoop();
    return 0;
}
