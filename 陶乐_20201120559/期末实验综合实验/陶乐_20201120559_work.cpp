#include<windows.h>
#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>

#include<gl/glaux.h> // GLaux库的头文件
#include<gl/GLU.h>
#include<gl/gl.h>
#include<GL/glext.h>

//注意下面的编译指令——告诉编译器要连接的静态库
#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "glaux.lib")

GLfloat  xrot = 0;   // X 旋转量
GLfloat  yrot = 0;   // Y 旋转量
GLfloat  zrot = 0;   // Z 旋转量

//导入图片的函数
LoadTexture(const char * filename, int width, int height)
{

	GLuint texture;
	unsigned char * data;
	FILE * file;

	//读文件
	file = fopen(filename, "rb");
	if (file == NULL) return 0;

	data = (unsigned char *)malloc(width * height * 3);
	fread(data, width * height * 3, 1, file);
	fclose(file);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


	//线性滤图
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//生成纹理
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB_SCALE_EXT, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	free(data); //释放纹理
	return texture;

}

void Background()
{
    GLuint texture = LoadTexture("D:\codeblocks_workplace\teapot_final\teapot_final\photo2.bmp",640, 640);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0); glVertex2d(-1.0, -1.0);
	glTexCoord2d(1.0, 0.0); glVertex2d(+1.0, -1.0);
	glTexCoord2d(1.0, 1.0); glVertex2d(+1.0, +1.0);
	glTexCoord2d(0.0, 1.0); glVertex2d(-1.0, +1.0);
	glEnd();
        return ;
}



void DrawCube(void)         // 从这里开始进行所有的绘制
{
    		glDisable(GL_DEPTH_TEST);
	glLoadIdentity();


	//导入纹理
    GLuint texture = LoadTexture("D:\codeblocks_workplace\teapot_final\teapot_final\photo2.bmp", 640, 640);

	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
		glScalef(100, 70, 1);
		glTranslatef(0, 0, -150);
		Background();					//背景方块
	glPopMatrix();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清除屏幕和深度缓存

    glLoadIdentity();         // 重置当前的模型观察矩阵

    glTranslatef(0.0f, 0.0f, -5.0f);         // 移入屏幕 5 个单位
    glRotatef(xrot, 1.0f, 0.0f, 0.0f);         // 绕X轴旋转
    glRotatef(yrot, 0.0f, 1.0f, 0.0f);         // 绕Y轴旋转
    glRotatef(zrot, 0.0f, 0.0f, 1.0f);         // 绕Z轴旋转

    glBindTexture(GL_TEXTURE_2D, texture);      // 选择纹理
    glBegin(GL_QUADS);
    // 前面
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // 纹理和四边形的左下
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f); // 纹理和四边形的右下
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f); // 纹理和四边形的右上
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // 纹理和四边形的左上
    // 后面
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // 纹理和四边形的右下
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // 纹理和四边形的右上
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f); // 纹理和四边形的左上
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f); // 纹理和四边形的左下
    // 顶面
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // 纹理和四边形的左上
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // 纹理和四边形的左下
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f); // 纹理和四边形的右下
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f); // 纹理和四边形的右上
    // 底面
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // 纹理和四边形的右上
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f); // 纹理和四边形的左上
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f); // 纹理和四边形的左下
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // 纹理和四边形的右下
    // 右面
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f); // 纹理和四边形的右下
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f); // 纹理和四边形的右上
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f); // 纹理和四边形的左上
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f); // 纹理和四边形的左下
    // 左面
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // 纹理和四边形的左下
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // 纹理和四边形的右下
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // 纹理和四边形的右上
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // 纹理和四边形的左上
    glEnd();

    glFlush(); //glutSwapBuffers();

    xrot += 0.3f;              // X 轴旋转
    yrot += 0.2f;              // Y 轴旋转
    zrot += 0.4f;              // Z 轴旋转
}


void init(void)
{
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0};

    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0}; //设置点光源的矩阵

    GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 }; //渲染光照球

    GLfloat Light_Model_Ambient[] = { 0.2 , 0.2 , 0.2 , 1.0 };

    glClearColor (0.0, 0.0, 0.0, 0.0);

    glShadeModel (GL_SMOOTH);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);

    glLightModelfv( GL_LIGHT_MODEL_AMBIENT , Light_Model_Ambient ); //

    glEnable(GL_LIGHTING); //材料属性和光照参数去决定每个顶点的颜色值
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    	glDisable(GL_DEPTH_TEST);
	glLoadIdentity();


}

void display(void)
{

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSolidTeapot(0.5);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    // 清楚颜色数据和深度数据（清屏）
    glLoadIdentity();                                    // 重置视图
    glTranslatef(0.0f, 0.0f, -5.0f);
    DrawCube();
    glutSwapBuffers();            //交换缓冲区。显示图形

    glFlush ();
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);

    glMatrixMode (GL_PROJECTION);

    glLoadIdentity();

    if (w <= h)

        glOrtho (-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w, 1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);

    else

        glOrtho (-1.5*(GLfloat)w/(GLfloat)h, 1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    glViewport(0, 0, w, h);        //设置视口
    glMatrixMode(GL_PROJECTION);    //设置矩阵模式为投影变换矩阵，
    glLoadIdentity();                //变为单位矩阵
    gluPerspective(60, (GLfloat)w / h, 0, 1000);    //设置投影矩阵

    glMatrixMode(GL_MODELVIEW);        //设置矩阵模式为视图矩阵(模型)
    glLoadIdentity();                //变为单位矩阵

}

//键盘输入事件函数
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'x':    //当按下键盘上d时，以沿X轴旋转为主
        xrot += 1.0f;   //设置旋转增量
        glutPostRedisplay();   //重绘函数
        break;
    case 'y':
        yrot += 1.0f;
        glutPostRedisplay();
        break;
    case 'z':
        zrot += 1.0f;
        glutPostRedisplay();
        break;
    default:
        break;
    }
}

int main(int argc, char** argv)
{

    glutInit(&argc, argv);

    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize (500, 500);

    glutInitWindowPosition (100, 100);

    glutCreateWindow (argv[0]);

    init ();

    glutDisplayFunc(display);

    glutReshapeFunc(reshape);

    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;

}


