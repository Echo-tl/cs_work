//三维观察、透视投影
#include <Windows.h> //Windows的头文件
#include <gl/glut.h> //包含OpenGL实用库

GLint winWidth = 600,winHeight = 600;
GLfloat x0 = 100.0,y0 = 50.0,z0 = 50.0;
GLfloat xref = 50.0,yref = 50.0,zref = 0.0;
GLfloat Vx = 0.0,Vy = 1.0,Vz = 0.0;

GLfloat xwmin = -40.0,ywmin = -60.0,xwmax = 40.0,ywmax = 60.0;

GLfloat dnear = 25.0,dfar = 125.0;

void init(void)
{
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(x0,y0,z0,xref,yref,zref,Vx,Vy,Vz);
    glMatrixMode(GL_PROJECTION);
    glFrustum(xwmin,xwmax,ywmin,ywmax,dnear,dfar);

}

void displayFcn(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,1.0,0.0);
    glPolygonMode(GL_FRONT,GL_FILL);
    glPolygonMode(GL_BACK,GL_LINE);
    glBegin(GL_QUADS);
        glVertex3f(0.0,0.0,0.0);
        glVertex3f(100.0,0.0,0.0);
        glVertex3f(100.0,100.0,0.0);
        glVertex3f(0.0,100.0,0.0);
    glEnd();
    glFlush();
}

void reshapeFcn(GLint newWidth,GLint newHeight)
{
    glViewport(0,0,newWidth,newHeight);
    winWidth = newWidth;
    winHeight = newHeight;
}

int main(int argc,char** argv)
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Perspective View of A Square");

	init();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(reshapeFcn);
	glutMainLoop();
	return 0;

}
