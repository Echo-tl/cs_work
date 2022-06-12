//三维图像的平移旋转
#include<windows.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<stdio.h>
#include<GL/glext.h>


//画坐标轴
void draw_axis()
{

	glBegin(GL_LINES);
	glVertex2f(1.0f,0.0f);
	glVertex2f(-1.0f,0.0f);
	glVertex2f(0.0f,1.0f);
	glVertex2f(0.0f,-1.0f);
	glEnd();
}

//画三角形
void draw_triangle()
{

	glBegin(GL_LINE_LOOP);
	glVertex2f(0.0f,0.0f);
	glVertex2f(0.5f,0.5f);
	glVertex2f(0.5f,-0.5f);

	glEnd();
}

void display()
{
   	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(1.0f,1.0f,1.0f);
	draw_axis();

	//画出初始三角形，为白色
	glLoadIdentity();//重置当前指定的矩阵为单位矩阵.
	glColor3f(1.0f,1.0f,1.0f);
	draw_triangle();


	//平移操作，为红色
	glLoadIdentity();
	glTranslatef(-0.5f,0.0f,0.0f);
	glColor3f(1.0f,0.0f,0.0f);
	draw_triangle();

	//旋转操作，为蓝色
	glLoadIdentity();
	glRotatef(90.0f,0.0f,0.0f,0.5f);
	glColor3f(0.0f,0.0f,1.0f);
	draw_triangle();

	glFlush();
}


void reshape(GLsizei w,GLsizei h){
	glViewport(0,0,w,h);
	glLoadIdentity();
	if(w<=h){
		glOrtho(-50.0,50.0, -50.0*(GLdouble)w/(GLdouble)h,50.0*(GLdouble)w/(GLdouble)h,  -1.0,20.0f);//创建一个平行的视景，使远处的物体不会变小
	}else
	{
		glOrtho(-50.0*(GLdouble)w/(GLdouble)h,50.0*(GLdouble)w/(GLdouble)h, -50.0,50.0,  -1.0,20.0f);
	}
}

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(600,600);
	glutCreateWindow("Translate3D");



	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();
	return 0;
}