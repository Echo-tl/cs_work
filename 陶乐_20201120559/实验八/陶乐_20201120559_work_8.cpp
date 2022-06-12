//二维图像的几何变换
#include<windows.h>
#include<GL/gl.h>
#include<GL/glut.h>
#include<math.h>

GLfloat square[4][2]; //定义一个正方形顶点数组坐标

//平移，键盘左右上下键控制
void translate(GLfloat tx,GLfloat ty)
{
    for(int i=0; i<4; i++){
        square[i][0] += tx;
        square[i][1] += ty;
    }
}

//旋转(使用键盘的r/l控制顺时针/逆时针旋转
void Rotate(GLfloat degree)
{
    for(int i=0; i<4; i++){
        int temX = square[i][0];
        int temY = square[i][1];
        square[i][0] = temX*cos(degree) - temY*sin(degree);
        square[i][1] = temX*sin(degree) + temY*cos(degree);
    }
}

//比例缩放(用键盘的A键控制横坐标缩放，Z键控制y缩放)
void Scale(GLfloat sx,GLfloat sy)
{
    for(int i=0; i<4; i++){
        square[i][0] *= sx;
        square[i][1] *= sy;
    }
}

//对称(键盘X表示关于x轴对称，Y关于y轴对称)
void Symmetry(int flag)
{
    for(int i=0; i<4; i++){
        if(flag){ //flag为1关于x轴对称
            square[i][1] *= -1;
        }
        else{ //flag为0关于y轴对称
            square[i][0] *= -1;
        }
    }
}

//错切（M键向x轴负半轴错切，N键向下轴正半轴错切）
void Shear(GLfloat b,GLfloat c)
{
    for(int i=0; i<4; i++){
        int temX = square[i][0];
        int temY = square[i][1];
        square[i][0] = temX + temY*c;
        square[i][1] = temX*b +temY;
    }
}

//用户自定义长方形
void MyInit()
{
    square[0][0] = -100.0;
	square[0][1] = 100.0;
	square[1][0] = 100.0;
	square[1][1] = 100.0;
	square[2][0] = 100.0;
	square[2][1] = -100.0;
	square[3][0] = -100.0;
	square[3][1] = -100.0;
}

void display()
{
    //设置背景颜色为白色并清除颜色缓冲
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	//画坐标系
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINES);
        //画x轴
        glVertex2f(400.0,0.0);
        glVertex2f(-400.0,0.0);

        //画y轴
        glVertex2f(0.0,400.0);
        glVertex2f(0.0,-400.0);
    glEnd();
    glColor3f(0.0,1.0,0.0);
	glPointSize(4.0);

    //画长方形
    glColor4f(1.0,0.0,0.0,0.1);
	glLineWidth(2.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glBegin(GL_POLYGON);
        glVertex2f(square[0][0],square[0][1]);
        glVertex2f(square[1][0],square[1][1]);
        glVertex2f(square[2][0],square[2][1]);
        glVertex2f(square[3][0],square[3][1]);
        glEnd();

    //交换前后缓冲区
	glutSwapBuffers();
}

//键盘上特殊按键的回调函数
void SpecialKeys(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_LEFT:
            translate(-100.0,0.0);
            break;
        case GLUT_KEY_RIGHT:
            translate(100.0,0.0);
            break;
        case GLUT_KEY_UP:
			translate(0.0,100.0);
			break;
		case GLUT_KEY_DOWN:
			translate(0.0,-100.0);
			break;
    }
    glutPostRedisplay();
}

//键盘普通按键回调
void NormalKeys(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 97:	//"a"
			Scale(0.5,1.0);
			break;
		case 65:	//"A"
			Scale(2.0,1.0);
			break;
        case 100:	//"d"
			Scale(1.0,0.5);
			break;
		case 68:	//"D"
			Scale(1.0,2.0);
			break;
        case 114:	//"r"
			Rotate(15.0);
			break;
		case 82:	//"R"
			Rotate(-15.0);
			break;
        case 120:	//"x"
			Symmetry(1);
			break;
		case 121:	//"y"
			Symmetry(0);
			break;
		case 122:	//"z"
			Shear(0.0,-1.1);
			break;
		case 90:	//"Z"
			Shear(0.0,1.1);
			break;
        case 99:	//"c"
			Shear(-1.1,0.0);
			break;
		case 67:	//"C"
			Shear(1.1,0.0);
			break;
		case 27:	//"esc"
			exit(0);
    }
    glutPostRedisplay();
}

//窗口大小
void reshape(GLsizei w,GLsizei h)
{
    glViewport(0,0,w,h);//设置视口大小比例始终与窗口一致

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-400,400,-400,400);
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);//初始化OPENGL显示方式
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA);//设定OPENGL窗口位置和大小
	glutInitWindowSize (400, 400);
	glutInitWindowPosition (100, 100);

	//打开窗口
	glutCreateWindow ("长方形的平移、比例（缩放）、旋转、对称和错切二维变换");
	//调用初始化函数
    MyInit();

    //窗口大小回调函数
    glutReshapeFunc(reshape);

	//设定键盘控制的回调函数
	glutSpecialFunc(SpecialKeys);
	glutKeyboardFunc(NormalKeys);

	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
